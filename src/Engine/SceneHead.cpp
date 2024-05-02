#include "SceneHead.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <chrono>

#define FRAMERATE_CAP 140.0

using namespace Engine::Nodes;
using namespace Engine;


static InputServer *inputServer;
static PhysicsServer *physicsServer;
static SceneHead *sceneHead;

void glutIdle();
void glutDraw();
void resize(int width, int height);
void keyboard_input(unsigned char key, int x, int y);
void mouse_input(int button, int state, int x, int y);
void mouse_motion(int x, int y);

void SceneHead::Init(InputServer *inputServerParam, PhysicsServer *physicsServerParam){
    sceneHead = this;
    inputServer = inputServerParam;
    physicsServer = physicsServerParam;

    glutIdleFunc(glutIdle);
    glutDisplayFunc(glutDraw);
    glutKeyboardFunc(keyboard_input);
    glutMouseFunc(mouse_input);
    glutReshapeFunc(resize);
    glutPassiveMotionFunc(mouse_motion);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    scene_root = this->constructTree();
    this->onTreeReady();
}

void SceneHead::Start(){
    glutMainLoop();
}

void SceneHead::onTreeReady(){
    this->scene_root->propegateReady(this);
}

InputServer& SceneHead::getInputServer() {return *inputServer;}
PhysicsServer& SceneHead::getPhysicsServer(){return *physicsServer;}

void glutIdle() {sceneHead->idle();}
unsigned long long last_idle;
void SceneHead::idle()
{
    unsigned long long now = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    double delta = (now - last_idle) * 1e-9;
    last_idle = now;
    if (delta < (1.0 / FRAMERATE_CAP)) return;
    this->scene_root->propegateIdle(delta);
    glutPostRedisplay();
}

void glutDraw() {sceneHead->draw();}
void SceneHead::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    this->scene_root->propegateDraw();
    glutSwapBuffers();
}

void resize(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // gluPerspective(45.0, (double)width / (double)height, 0.1, 100.0);
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


