#ifndef QUATERNION_H
#define QUATERNION_H
#include "Vector3.h"

namespace Engine{
namespace DataTypes{
    
    struct Quaternion
    {
        static const Quaternion FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN; 
        float w,i,j,k;
        Quaternion();
        Quaternion(float w, float i, float j, float k);
        Quaternion(float angleRad, Vector3 axis);
        Quaternion operator*(Quaternion q);
        //Returns the axis and angle a point would rotate around if this quaternion is applied to it.
        void angle_and_axis(float* angleRad, Vector3* axis);
    };
    
}}


#endif