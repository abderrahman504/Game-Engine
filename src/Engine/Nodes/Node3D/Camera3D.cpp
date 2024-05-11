#include "Camera3D.h"
#include <math.h>

using namespace Engine::Nodes;
using namespace Engine::DataTypes;



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


float Camera3D::getLeft(){return left;}
float Camera3D::getRight(){return right;}
float Camera3D::getUp(){return up;}
float Camera3D::getDown(){return down;}
float Camera3D::getNear(){return near;}
float Camera3D::getFar(){return far;}


void Camera3D::updateDims(){
    //Applying fov or width
    float width;
    if(projection = PERSPECTIVE)
        width = 2 * near * tan(0.5 * fov_or_width);
    else
        width = fov_or_width;
    //Applying aspect ratio
    float height = width / (aspect.x / aspect.y);
    //Setting the dimensions
    left = -0.5 * width;
    right = 0.5 * width;
    up = 0.5 * height;
    down = -0.5 * height;
}