#include "SceneHead.h"
#include "SceneHeadHelpers/TreeDrawer.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <chrono>
#include <stack>
#include "simpledrawtext.h"
#include <stdio.h>

#define FRAMERATE_CAP 140.0
#define PHYSICS_FRAME_CAP 60.0
bool isGameStarted = false;
SimpleDrawText sdt;
using namespace Engine::Nodes;
using namespace Engine;


static InputServer *inputServer;
static PhysicsServer *physicsServer;
static SceneHead *sceneHead;
static TreeDrawer *treeDrawer;
static std::vector<Node*> node_freeing_queue;
static unsigned long long last_idle;
static unsigned long long last_physics;
static Vector2 windowSize;

void glutIdle();
void displayText();
void glutDraw();
void resize(int width, int height);
void keyboard_key(unsigned char key, int x, int y);
void keyboard_key_up(unsigned char key, int x, int y);
void special_key(int key, int x, int y);
void special_key_up(int key, int x, int y);
void mouse_key(int button, int state, int x, int y);
void mouse_motion(int x, int y);
void mouse_wheel(int wheel, int direction, int x, int y);
void free_nodes();


void displayText(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    sdt.drawText("Main Menu", 250, 500, 1, 0, 0,0.3);
    sdt.drawText("Press '1' to start the game", 250, 400, 1, 0, 0,0.2);
    sdt.drawText("Press '0' to exit the game", 250, 300, 1, 0, 0,0.2);
    sdt.render();

    glutSwapBuffers();

}
void SceneHead::Init(InputServer *inputServerParam, PhysicsServer *physicsServerParam){
    std::cout<<"scene head entered"<<std::endl;
    sceneHead = this;
    inputServer = inputServerParam;
    physicsServer = physicsServerParam;
    treeDrawer = new TreeDrawer();
    //Input callbacks
    glutKeyboardFunc(keyboard_key);
    glutKeyboardUpFunc(keyboard_key_up);
    glutSpecialUpFunc(special_key_up);
    glutPassiveMotionFunc(mouse_motion);
    glutMouseWheelFunc(mouse_wheel);
    glutMouseFunc(mouse_key);
    glutPassiveMotionFunc(mouse_motion);
    glutMotionFunc(mouse_motion);
    glutEntryFunc(mouse_entry);
    //Other callbacks
    glutIdleFunc(glutIdle);
    glutDisplayFunc(glutDraw);
    glutReshapeFunc(resize);
    // glutSetCursor(GLUT_CURSOR_NONE);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glClearColor(0, 0, 0, 1.0);

    //Setting global lighting
    float global_ambience[4] = {0.2, 0.2, 0.2, 1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambience);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
}

void SceneHead::Start(){
    scene_root = this->constructTree();
    this->onTreeReady();
    inputServer->init();
    last_idle = std::chrono::high_resolution_clock::now().time_since_epoch().count();
   glutMainLoop();

}

InputServer& SceneHead::getInputServer() {return *inputServer;}
PhysicsServer& SceneHead::getPhysicsServer(){return *physicsServer;}

void SceneHead::hideCursor(){
    glutSetCursor(GLUT_CURSOR_NONE);
}

void SceneHead::showCursor(){
    glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
}

void SceneHead::freezeCursor(){
    inputServer->cursor_frozen = true;
}

void SceneHead::unfreezeCursor(){
    inputServer->cursor_frozen = false;
}


void SceneHead::onTreeReady(){
    this->scene_root->propegateReady(this);
}

void glutIdle() {
    if(isGameStarted)
        sceneHead->idle();
}
void SceneHead::idle()
{
    unsigned long long now = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    double delta = (now - last_idle) * 1e-9;
    double physics_delta = (now - last_physics) * 1e-9;
    
    if (delta >= (1.0 / FRAMERATE_CAP)){
        //Run idle frame
        last_idle = now;
        this->scene_root->propegateIdle(delta);
        //Run physics frame
        if(physics_delta >= (1.0 / PHYSICS_FRAME_CAP)){
            last_physics = now;
            physicsServer->update(physics_delta, scene_root);
            scene_root->propegatePhysics(physics_delta);
        }
        //Check for nodes that need freeing and free them
        this->findNodesForFreeing();
        free_nodes();
        //Draw scene
        glutPostRedisplay();
        //Reset input for next frame
        inputServer->onIdle(windowSize);
    }
}

void glutDraw() {
    if(!isGameStarted) displayText();
    else sceneHead->draw();
}
void SceneHead::draw(){
    treeDrawer->drawScene(scene_root, windowSize);
}

void resize(int width, int height)
{
    windowSize = Vector2(width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(33.6, 16.0 / 9.0, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard_key(unsigned char key, int x, int y){
    if(key=='1'){
        isGameStarted=true;
        glEnable(GL_LIGHTING);
        glEnable(GL_DEPTH_TEST);
        glutPostRedisplay();
    }
    else if(key=='0'){
        exit(0);
    }

    sceneHead->keyboard(key, x, y);
}
void SceneHead::keyboard(unsigned char key, int x, int y){inputServer->keyboardInput(key, true, x, y);}

void keyboard_key_up(unsigned char key, int x, int y){sceneHead->keyboardUp(key, x, y);}
void SceneHead::keyboardUp(unsigned char key, int x, int y){inputServer->keyboardInput(key, false, x, y);}

void special_key(int key, int x, int y){sceneHead->specialKeyboard(key, x, y);}
void SceneHead::specialKeyboard(int key, int x, int y){inputServer->specialInput(key, true, x, y);}

void special_key_up(int key, int x, int y){sceneHead->specialKeyboardUp(key, x, y);}
void SceneHead::specialKeyboardUp(int key, int x, int y){inputServer->specialInput(key, false, x, y);}

void mouse_motion(int x, int y){sceneHead->mouseMotion(x, y);}
void SceneHead::mouseMotion(int x, int y){inputServer->mouseMotion(x, y);}

void mouse_key(int button, int state, int x, int y){sceneHead->mouseKey(button, state, x, y);}
void SceneHead::mouseKey(int button, int state, int x, int y){inputServer->mouseKey(button, state, x, y);}

void mouse_wheel(int wheel, int direction, int x, int y){sceneHead->mouseWheel(wheel, direction, x, y);}
void SceneHead::mouseWheel(int wheel, int direction, int x, int y){inputServer->mouseWheel(wheel, direction, x, y);}
void mouse_entry(int state){sceneHead->mouseEntry(state);}
void SceneHead::mouseEntry(int state){inputServer->mouseEntry(state);}


void SceneHead::findNodesForFreeing()
{
    std::stack<Node*> node_stack = std::stack<Node*>();
    node_stack.push(sceneHead->scene_root);
    while(!node_stack.empty())
    {
        Node* current_node = node_stack.top();
        node_stack.pop();
        if(current_node->queuedForDeletion)
            node_freeing_queue.push_back(current_node);
        else{
            for(int i = 0; i < current_node->children.size(); i++)
                node_stack.push(current_node->children[i]);
        }
    }
}

void free_nodes()
{
    for(int i = 0; i < node_freeing_queue.size(); i++)
    {
        delete node_freeing_queue[i];
    }
    node_freeing_queue.clear();
}
