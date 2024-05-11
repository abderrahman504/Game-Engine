#ifndef QUATERNION_H
#define QUATERNION_H

namespace Engine{
namespace DataTypes{
    struct Vector3;

    struct Quaternion
    {
        static const Quaternion FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN; 
        float w,i,j,k;
        Quaternion();
        Quaternion(float w, float i, float j, float k);
        Quaternion(float angleRad, Vector3 axis);
        Quaternion operator*(Quaternion q);
        Quaternion operator*(float f);
        Quaternion operator/(float f);
        Quaternion operator*(Vector3 v);
        Quaternion operator+(Quaternion q);
        Quaternion operator-(Quaternion q);
        //Returns the axis and angle a point would rotate around if this quaternion is applied to it.
        void angleAndAxis(float* angleRad, Vector3* axis);
        Quaternion conjugate();
        float magnitude();
        Quaternion normalize();
        Quaternion inverse();
    };
    
}}


#endif