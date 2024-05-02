#ifndef VECTOR3_H
#define VECTOR3_H

namespace Engine{
namespace DataTypes{
    struct Vector3
    {
        static const Vector3 ZERO,ONE, LEFT, RIGHT, UP, DOWN, FORWARD, BACK; 
        float x,y,z;
        Vector3();
        Vector3(float x, float y, float z);
        Vector3 operator+(Vector3 other);
        Vector3 operator-(Vector3 other);
        Vector3 operator*(float scalar);
        Vector3 operator/(float scalar);
        float dot(Vector3 other);
        Vector3 cross(Vector3 other);
        //Returns the angle between this and other
        float angle_to(Vector3 other);
        float length();
        Vector3 normalize();
    };
}}

#endif