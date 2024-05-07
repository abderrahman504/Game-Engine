#include "TreeDrawer.h"

#include "../DataTypes.h"
#include "../Nodes.h"

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include <math.h>

using namespace Engine;
using namespace Engine::Nodes;

void TreeDrawer::drawScene(Nodes::Node* root){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    drawNode(root);
    glutSwapBuffers();
}

void TreeDrawer::drawNode(Nodes::Node* node)
{
    //Check the type of the node
    bool isNode3D = dynamic_cast<Nodes::Node3D*>(node) != nullptr;
    bool isMesh3D = dynamic_cast<Nodes::Mesh3D*>(node) != nullptr;
    //If Node3D then apply its transformation before drawing
    if(isNode3D)
    {
        glPushMatrix();
        Vector3 position = ((Node3D*)node)->Position();
        Vector3 axis = Vector3::ZERO;
        float angle = 0;
        ((Node3D*)node)->Orientation().angle_and_axis(&angle, &axis);
        Vector3 scale = ((Node3D*)node)->Scale();
        glTranslatef(position.x, position.y, position.z);
        glRotatef(angle * PI / 180.0, axis.x, axis.y, axis.z);
        glScalef(scale.x, scale.y, scale.z);
    }
    //If Mesh3D then draw its vertices
    if(isMesh3D)
    {
        Mesh3D* mesh = (Mesh3D*)node;
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
