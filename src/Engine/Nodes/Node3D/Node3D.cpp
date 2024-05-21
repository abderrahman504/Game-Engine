#include "Node3D.h"
#include <GL/glew.h>
#include <GL/freeglut.h>

using namespace Engine::Nodes;
using namespace Engine::DataTypes;

Node3D::Node3D() : Node(){
    setName("Node3D");
}


Vector3 Node3D::Position(){return position;}
void Node3D::Position(Vector3 position){this->position = position;}
Quaternion Node3D::Orientation(){return orientation;}
void Node3D::Orientation(Quaternion quaterion){this->orientation = quaterion.normalize();}
Vector3 Node3D::Scale(){return scale;}
void Node3D::Scale(Vector3 scale){this->scale = scale;}

Vector3 Node3D::getUp(){
    Quaternion result = orientation * Vector3::UP * orientation.conjugate();
    return Vector3(result.i, result.j, result.k).normalize();
}
Vector3 Node3D::getForward(){
    Quaternion result = orientation * Vector3::FORWARD * orientation.conjugate();
    return Vector3(result.i, result.j, result.k).normalize();
}
void Node3D::lookAt(Vector3 point, Vector3 up){
    lookTowards(point - position, up);
}
void Node3D::lookTowards(Vector3 direction, Vector3 up){
    if(direction.cross(up).length() == 0)
    {
        printf("lookTowards() was passed the same vector for direction and up: ");
        printf("direction=(%f,%f,%f), up=(%f,%f,%f)\n", direction.x, direction.y, direction.z, up.x, up.y, up.z);
        return;
    }
    orientation = Quaternion::IDENTITY;
    Vector3 currentForward = Vector3::FORWARD;
    //Rotate so your face points towards direction
    float angle = currentForward.angleTo(direction);
    Vector3 normal = currentForward.cross(direction).normalize();
    rotateAround(normal, abs(angle));
    
    //Rotate so your top points towards up
    Vector3 currentUp = getUp();
    Vector3 left = up.cross(direction);
    Vector3 actualUp = direction.cross(left);

    // Vector3 actualUp = up - direction * up.dot(direction);
    angle = currentUp.angleTo(actualUp);
    normal = currentUp.cross(actualUp).normalize();
    rotateAround(normal, abs(angle));
}
void Node3D::rotateAround(Vector3 axis, float angleRad){
    Quaternion newRotation = Quaternion(angleRad, axis);
    // orientation = (orientation * newRotation).normalize();
    orientation = (newRotation * orientation).normalize();
}
