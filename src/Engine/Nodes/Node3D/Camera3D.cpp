#include "Camera3D.h"
#include <math.h>

using namespace Engine::Nodes;
using namespace Engine::DataTypes;


Camera3D::Camera3D() : Node3D(){
    setName("Camera3D");
    updateDims();
}

void Camera3D::setAspect(Vector2 aspect){
    this->aspect = aspect;
    updateDims();
}

void Camera3D::setFOV(float fov){
    if(projection != PERSPECTIVE) return;
    this->fov_or_width = fov;
    updateDims();
}

void Camera3D::setWidth(float w){
    if(projection != ORTHO) return;
    this->fov_or_width = w;
    updateDims();
}

void Camera3D::setNear(float near){
    this->near = near;
    updateDims();
}

float Camera3D::getFOV(){return fov_or_width;}
Vector2 Camera3D::getAspect(){return aspect;}
float Camera3D::getWidth(){return width;}
float Camera3D::getHeight(){return height;}
float Camera3D::getNear(){return near;}
float Camera3D::getFar(){return far;}


void Camera3D::updateDims(){
    //Applying fov or width
    if(projection = PERSPECTIVE)
        width = 2 * near * tan(0.5 * fov_or_width);
    else
        width = fov_or_width;
    //Applying aspect ratio
    height = width / (aspect.x / aspect.y);
}