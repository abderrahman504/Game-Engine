#include "TreeDrawer.h"
#include "../DataTypes.h"
#include "../Nodes.h"
#include "../Display.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include <stack>
#include <unordered_map>
#include <math.h>

using namespace Engine;
using namespace Engine::Nodes;
std::unordered_map<int, Camera3D*> activeCameras = std::unordered_map<int, Camera3D*>();


void applyMaterial(Material material);
Camera3D defaultCamera();

void findCameras(Node* root)
{
    activeCameras.clear();
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
            cameraPos = cameraPos * node->Scale();
            cameraForward = cameraForward * node->Scale();
            cameraUp = cameraUp * node->Scale();
            cameraPos = cameraPos.rotateBy(node->Orientation());
            cameraForward = cameraForward.rotateBy(node->Orientation());
            cameraUp = cameraUp.rotateBy(node->Orientation());
            //Apply translation to cameraPos only
            cameraPos = cameraPos + node->Position();
        }
        current = current->Parent();
    }
    *pos = cameraPos;
    *forward = cameraForward;
    *up = cameraUp;
}

void drawCameraViewport(Camera3D* camera, Vector2 windowSize, Node* root)
{
    Vector3 cameraPos, cameraForward, cameraUp;
    getCameraOrientationAndPosition(camera, &cameraPos, &cameraForward, &cameraUp);
    glViewport(camera->viewportPosition.x * windowSize.x, camera->viewportPosition.y * windowSize.y, camera->viewportSize.x * windowSize.x, camera->viewportSize.y * windowSize.y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // gluPerspective(33, camera->getAspect().x / camera->getAspect().y, camera->getNear(), camera->getFar());
    glFrustum(-0.5*camera->getWidth(), 0.5*camera->getWidth(), -0.5*camera->getHeight(), 0.5*camera->getHeight(), camera->getNear(), camera->getFar());
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z, cameraPos.x + cameraForward.x, cameraPos.y + cameraForward.y, cameraPos.z + cameraForward.z, cameraUp.x, cameraUp.y, cameraUp.z);
}

void TreeDrawer::drawScene(Nodes::Node* root, Vector2 windowSize){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    findCameras(root);
    Camera3D defaultCam = defaultCamera();
    if(activeCameras.size() == 0) activeCameras[VIEWPORT_1] = &defaultCam;
    for(auto it = activeCameras.begin(); it != activeCameras.end(); it++)
    {
        Camera3D* camera = it->second;
        drawCameraViewport(camera, windowSize, root);
        drawNode(root);
    }
    glutSwapBuffers();
}

void TreeDrawer::drawNode(Node* node)
{
    //Check the type of the node
    bool isNode3D = dynamic_cast<Node3D*>(node) != nullptr;
    bool isMesh3D = dynamic_cast<Mesh3D*>(node) != nullptr;
    //If Node3D then apply its transformation before drawing
    if(isNode3D)
    {
        glPushMatrix();
        Vector3 position = ((Node3D*)node)->Position();
        Vector3 axis = Vector3::ZERO;
        float angle = 0;
        ((Node3D*)node)->Orientation().angleAndAxis(&angle, &axis);
        Vector3 scale = ((Node3D*)node)->Scale();
        glTranslatef(position.x, position.y, position.z);
        glRotatef(angle * PI / 180.0, axis.x, axis.y, axis.z);
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
    float amb[4] = {material.color[0]*material.ambient_diffuse, material.color[1]*material.ambient_diffuse, material.color[2]*material.ambient_diffuse, material.color[3]};
    float spec[4] = {1*material.specular, 1*material.specular, 1*material.specular, 1};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material.shininess);
}

Camera3D defaultCamera()
{
    //implement later
    //Create a default camera object to be used in drawing the scene if no camera is present.
    return Camera3D();
}