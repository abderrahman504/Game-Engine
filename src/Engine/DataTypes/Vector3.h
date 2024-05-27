#ifndef VECTOR3_H
#define VECTOR3_H

namespace Engine{
namespace DataTypes{
    struct Quaternion;
    struct Vector3
    {
        static const Vector3 ZERO,ONE, LEFT, RIGHT, UP, DOWN, FORWARD, BACK; 
        float x,y,z;
        Vector3();
        Vector3(float x, float y, float z);
        Vector3 operator+(float scalar);
        Vector3 operator-(float scalar);
        Vector3 operator*(float scalar);
        Vector3 operator/(float scalar);
        Vector3 operator+(Vector3 other);
        Vector3 operator-(Vector3 other);
        Vector3 operator*(Vector3 other);
        Vector3 operator/(Vector3 other);
        float dot(Vector3 other);
        Vector3 cross(Vector3 other);
        //Returns the shorter angle between this vector and `other` in radians. Always in range [0,180].
        float angleTo(Vector3 other);
        float length();
        Vector3 normalize();
        Vector3 rotateBy(Quaternion quaternion);
    };
}}

#endif