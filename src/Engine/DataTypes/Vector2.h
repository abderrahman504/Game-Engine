#ifndef VECTOR2_H
#define VECTOR2_H

namespace Engine{
namespace DataTypes{
    struct Vector2
    {
        static const Vector2 ZERO, ONE, LEFT, RIGHT, UP, DOWN; 
        float x,y;
        Vector2();
        Vector2(float x, float y);
        Vector2 operator+(float scalar);
        Vector2 operator-(float scalar);
        Vector2 operator*(float scalar);
        Vector2 operator/(float scalar);
        Vector2 operator+(Vector2 other);
        Vector2 operator-(Vector2 other);
        Vector2 operator*(Vector2 other);
        Vector2 operator/(Vector2 other);
        float dot(Vector2 other);
        float cross(Vector2 other);
        //Returns the angle between this and `other` in radians
        float angleTo(Vector2 other);
        float length();
        Vector2 normalize();
    };
}}

#endif