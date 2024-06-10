#include "TreeDrawer.h"
#include "../DataTypes.h"
#include "../Nodes.h"
#include "../Display.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include <stack>
#include <map>
#include <math.h>

using namespace Engine;
using namespace Engine::Nodes;
// std::map<int, Camera3D*> activeCameras = std::map<int, Camera3D*>();
// int lightCount = 0;


void applyMaterial(Material material);
Camera3D defaultCamera();
int getLightID(int lightCount);
void turnOffLights();

std::map<int, Camera3D*> findCameras(Node* root)
{
    std::map<int, Camera3D*> activeCameras = std::map<int, Camera3D*>();
    std::stack<Node*> stack;
    stack.push(root);
    while(stack.size() != 0)
    {
        Node* node = stack.top();
        stack.pop();
        Camera3D* camera = dynamic_cast<Camera3D*>(node);
        if(camera != nullptr && camera->active)
            activeCameras[camera->viewport] = camera;
        std::vector<Node*> children = node->getChildren();
        for(int i=0; i<children.size(); i++)
        {
            stack.push(children[i]);
        }
    }
    return activeCameras;
}

void getCameraOrientationAndPosition(Camera3D* camera, Vector3* pos, Vector3* forward, Vector3* up)
{
    Vector3 cameraPos = Vector3::ZERO, cameraForward = Vector3::FORWARD, cameraUp = Vector3::UP;
    Node* current = camera;
    while(current != NULL)
    {
        Node3D* node = dynamic_cast<Node3D*>(current);
        if(node != NULL){
            //Apply scaling and rotation to all
            cameraPos = cameraPos * node->scale;
            cameraForward = cameraForward * node->scale;
            cameraUp = cameraUp * node->scale;
            cameraPos = cameraPos.rotateBy(node->orientation);
            cameraForward = cameraForward.rotateBy(node->orientation);
            cameraUp = cameraUp.rotateBy(node->orientation);
            //Apply translation to cameraPos only
            cameraPos = cameraPos + node->position;
        }
        current = current->Parent();
    }
    *pos = cameraPos;
    *forward = cameraForward;
    *up = cameraUp;
}

void drawCameraViewport(Camera3D* camera, Vector2 windowSize, Node* root, bool multipleCameras)
{
    Vector3 cameraPos, cameraForward, cameraUp;
    getCameraOrientationAndPosition(camera, &cameraPos, &cameraForward, &cameraUp);
    Vector2 viewportPosition = camera->viewportPosition * windowSize;
    Vector2 viewportSize = camera->viewportSize * windowSize;
    glViewport(viewportPosition.x, viewportPosition.y, viewportSize.x, viewportSize.y);
    if(multipleCameras)
    {
        glEnable(GL_SCISSOR_TEST);
        glScissor(viewportPosition.x, viewportPosition.y, viewportSize.x, viewportSize.y);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDisable(GL_SCISSOR_TEST);
    }
    else 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-0.5*camera->getWidth(), 0.5*camera->getWidth(), -0.5*camera->getHeight(), 0.5*camera->getHeight(), camera->getNear(), camera->getFar());
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z, cameraPos.x + cameraForward.x, cameraPos.y + cameraForward.y, cameraPos.z + cameraForward.z, cameraUp.x, cameraUp.y, cameraUp.z);
}


void placeLights(Node* root)
{
    std::stack<Node*> stack;
    stack.push(root);
    int lightCount = 0;
    while(stack.size() != 0 && lightCount != 8)
    {
        Node* node = stack.top();
        stack.pop();
        Light3D* light = dynamic_cast<Light3D*>(node);
        if(light != nullptr)
        {
            //Place light in scene
            glDisable(GL_LIGHTING);
            int lightID = getLightID(++lightCount);
            Light3D* light = (Light3D*)node;
            float pos[4] = {light->GlobalPosition().x, light->GlobalPosition().y, light->GlobalPosition().z, 1};
            float amb[4] = {light->color.r*light->ambient, light->color.g*light->ambient, light->color.b*light->ambient, 1};
            float diff[4] = {light->color.r*light->diffuse, light->color.g*light->diffuse, light->color.b*light->diffuse, 1};
            float spec[4] = {light->color.r*light->specular, light->color.g*light->specular, light->color.b*light->specular, 1};
            glLightfv(lightID, GL_POSITION, pos);
            glLightfv(lightID, GL_AMBIENT, amb);
            glLightfv(lightID, GL_DIFFUSE, diff);
            glLightfv(lightID, GL_SPECULAR, spec);
            glEnable(GL_LIGHTING);
            glEnable(lightID);
        }
        std::vector<Node*> children = node->getChildren();
        for(int i=0; i<children.size(); i++)
        {
            stack.push(children[i]);
        }
    }
}

void TreeDrawer::drawScene(Nodes::Node* root, Vector2 windowSize){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    std::map<int, Camera3D*> activeCameras = findCameras(root);

    // lightCount = 0;
    // turnOffLights();
    findCameras(root);
    Camera3D defaultCam = defaultCamera();

    if(activeCameras.size() == 0) activeCameras[VIEWPORT_1] = &defaultCam;
    for(auto it = activeCameras.begin(); it != activeCameras.end(); it++)
    {
        Camera3D* camera = it->second;
        drawCameraViewport(camera, windowSize, root, activeCameras.size() > 1);
        placeLights(root);
        drawNode(root);
    }
    glutSwapBuffers();
}

void TreeDrawer::drawNode(Node* node)
{
    //Check the type of the node
    bool isNode3D = dynamic_cast<Node3D*>(node) != nullptr;
    bool isMesh3D = dynamic_cast<Mesh3D*>(node) != nullptr;
    bool isLight3D = dynamic_cast<Light3D*>(node) != nullptr;
    //If Node3D then apply its transformation before drawing
    if(isNode3D)
    {
        glPushMatrix();
        Vector3 position = ((Node3D*)node)->position;
        Vector3 axis = Vector3::ZERO;
        float angle = 0;
        ((Node3D*)node)->orientation.angleAndAxis(&angle, &axis);
        Vector3 scale = ((Node3D*)node)->scale;
        glTranslatef(position.x, position.y, position.z);
        glRotatef(angle * 180 / PI, axis.x, axis.y, axis.z);
        glScalef(scale.x, scale.y, scale.z);
    }
    //If Mesh3D then draw its vertices
    if(isMesh3D)
    {
        Mesh3D* mesh = (Mesh3D*)node;
        Material* material = mesh->material;
        applyMaterial(*material);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, mesh->Vertices());
        glMultiDrawElements(GL_TRIANGLE_STRIP, mesh->CountIndeces(), GL_UNSIGNED_INT, (const void**)mesh->Indeces(), mesh->CountPrimitives());
        glDisableClientState(GL_VERTEX_ARRAY);
    }
    

    std::vector<Nodes::Node*> children = node->getChildren();
    for (int i=0; i<children.size(); i++)
    {
        drawNode(children[i]);
    }
    //Undo node3d transformation
    if(isNode3D) glPopMatrix();
}


void applyMaterial(Material material)
{
    float amb[4] = {material.color.r*material.ambient_diffuse, material.color.g*material.ambient_diffuse, material.color.b*material.ambient_diffuse, material.color.a};
    float spec[4] = {1*material.specular, 1*material.specular, 1*material.specular, 1};
    float emi[4] = {material.color.r*material.emission, material.color.g*material.emission, material.color.b*material.emission, material.color.a};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, amb);
    glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
    glMaterialf(GL_FRONT, GL_SHININESS, material.shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, emi);
}

Camera3D defaultCamera()
{
    return Camera3D();
}

int getLightID(int lightCount)
{
    switch(lightCount)
    {
        case 1: return GL_LIGHT0;
        case 2: return GL_LIGHT1;
        case 3: return GL_LIGHT2;
        case 4: return GL_LIGHT3;
        case 5: return GL_LIGHT4;
        case 6: return GL_LIGHT5;
        case 7: return GL_LIGHT6;
        case 8: return GL_LIGHT7;
        default: return GL_LIGHT7;
    }
}

void turnOffLights(){
    for(int i=1; i<=8; i++)
    {
        glDisable(getLightID(i));
    }
}