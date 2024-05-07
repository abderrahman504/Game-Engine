#include "SceneHead.h"
#include "SceneHeadHelpers/TreeDrawer.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <chrono>
#include <stack>

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
void keyboard_input(unsigned char key, int x, int y);
void mouse_input(int button, int state, int x, int y);
void mouse_motion(int x, int y);
void free_nodes();

void SceneHead::Init(InputServer *inputServerParam, PhysicsServer *physicsServerParam){
    sceneHead = this;
    inputServer = inputServerParam;
    physicsServer = physicsServerParam;
    treeDrawer = new TreeDrawer();

    glutIdleFunc(glutIdle);
    glutDisplayFunc(glutDraw);
    glutKeyboardFunc(keyboard_input);
    glutMouseFunc(mouse_input);
    glutReshapeFunc(resize);
    glutPassiveMotionFunc(mouse_motion);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void SceneHead::Start(){
    scene_root = this->constructTree();
    this->onTreeReady();
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
    last_idle = now;
    if (delta < (1.0 / FRAMERATE_CAP)) return;
    this->scene_root->propegateIdle(delta);
    this->findNodesForFreeing();
    free_nodes();
    glutPostRedisplay();
}

void glutDraw() {sceneHead->draw();}
void SceneHead::draw(){
    treeDrawer->drawScene(scene_root);
}

void resize(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-8, 8,  -4.5, 4.5, 5, 500.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard_input(unsigned char key, int x, int y)
{
    //implement later
}

void mouse_input(int button, int state, int x, int y)
{
    //implement later
}

void mouse_motion(int x, int y)
{
    //implement later
}


void SceneHead::findNodesForFreeing()
{
    std::stack<Node*> node_stack = std::stack<Node*>();
    node_stack.push(sceneHead->scene_root);
    while(!node_stack.empty())
    {
        Node* current_node = node_stack.top();
        node_stack.pop();
        if(current_node->queuedForDeletion)
        {
            node_freeing_queue.push_back(current_node);
        }
        else{
            for(int i = 0; i < current_node->children.size(); i++)
            {
                node_stack.push(current_node->children[i]);
            }
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

