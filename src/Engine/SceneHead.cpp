#include "SceneHead.h"
#include "SceneHeadHelpers/TreeDrawer.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <chrono>
#include <stack>
#include <stdio.h>

#define FRAMERATE_CAP 140.0

using namespace Engine::Nodes;
using namespace Engine;


static InputServer *inputServer;
static PhysicsServer *physicsServer;
static SceneHead *sceneHead;
static TreeDrawer *treeDrawer;
static std::vector<Node*> node_freeing_queue;
static unsigned long long last_idle;

void glutIdle();
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

void SceneHead::Init(InputServer *inputServerParam, PhysicsServer *physicsServerParam){
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
    //Other callbacks
    glutIdleFunc(glutIdle);
    glutDisplayFunc(glutDraw);
    glutReshapeFunc(resize);
    glutPassiveMotionFunc(mouse_motion);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    float global_ambience[4] = {0.8, 0.8, 0.8, 1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambience);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glClearColor(0,0,0, 1.0);
}

void SceneHead::Start(){
    scene_root = this->constructTree();
    this->onTreeReady();
    inputServer->init();
    last_idle = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    glutMainLoop();
}

void SceneHead::onTreeReady(){
    this->scene_root->propegateReady(this);
}

InputServer& SceneHead::getInputServer() {return *inputServer;}
PhysicsServer& SceneHead::getPhysicsServer(){return *physicsServer;}

void glutIdle() {sceneHead->idle();}
void SceneHead::idle()
{
    unsigned long long now = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    double delta = (now - last_idle) * 1e-9;
    if (delta < (1.0 / FRAMERATE_CAP)) return;
    last_idle = now;
    this->scene_root->propegateIdle(delta);
    this->findNodesForFreeing();
    free_nodes();
    glutPostRedisplay();
    inputServer->onIdle();
}

void glutDraw() {sceneHead->draw();}
void SceneHead::draw(){
    treeDrawer->drawScene(scene_root);
}

void resize(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-8, 8,  -4.5, 4.5, 1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard_key(unsigned char key, int x, int y){sceneHead->keyboard(key, x, y);}
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

