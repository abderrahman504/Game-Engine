#include "Node3D.h"
#include <GL/glew.h>
#include <GL/freeglut.h>

using namespace Engine::Nodes;
using namespace Engine::DataTypes;

Node3D::Node3D() : Node(){
    position = Vector3::ZERO;
    orientation = Quaternion::FORWARD;
    scale = Vector3::ONE;
    setName("Node3D");
}


Vector3 Node3D::Position(){return position;}
void Node3D::Position(Vector3 position){this->position = position;}
Quaternion Node3D::Orientation(){return orientation;}
void Node3D::Orientation(Quaternion quaterion){this->orientation = quaterion;}
Vector3 Node3D::Scale(){return scale;}
void Node3D::Scale(Vector3 scale){this->scale = scale;}

Vector3 Node3D::getUp(){
    Quaternion result = Quaternion(0, Vector3::UP.x, Vector3::UP.y, Vector3::UP.z);
    result = orientation * result * orientation.inverse();
    return Vector3(result.i, result.j, result.k).normalize();
}
Vector3 Node3D::getForward(){
    Quaternion result = Quaternion(0, Vector3::FORWARD.x, Vector3::FORWARD.y, Vector3::FORWARD.z);
    result = orientation * result * orientation.inverse();
    return Vector3(result.i, result.j, result.k).normalize();
}
void Node3D::lookAt(Vector3 point, Vector3 up){
    lookTowards(point - position, up);
}
void Node3D::lookTowards(Vector3 direction, Vector3 up){
    Vector3 vec = Vector3::FORWARD;
    //Rotate so your face points towards direction
    rotateAround(vec.cross(direction), vec.angle_to(direction));
    //Rotate so your top points towards up
    Vector3 properUp = up - direction * up.dot(direction); 
    vec = Vector3::UP;
    rotateAround(vec.cross(properUp), vec.angle_to(properUp));
}

void Node3D::rotateAround(Vector3 axis, float angleRad){
    Quaternion newRotation = Quaternion(angleRad, axis);
    orientation = orientation * newRotation;
}

void Node3D::propegateDraw(){
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);
    float angle;
    Vector3 axis;
    orientation.angle_and_axis(&angle, &axis);
    glRotatef(angle, axis.x, axis.y, axis.z);
    glScalef(scale.x, scale.y, scale.z);
    Node::propegateDraw();
    glPopMatrix();
}