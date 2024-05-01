#ifndef VECTOR2_H
#define VECTOR2_H

namespace Engine{
namespace DataTypes{
    struct Vector2
    {
        float x,y;
        Vector2(float x, float y);
        Vector2 operator+(Vector2 other);
        Vector2 operator-(Vector2 other);
        Vector2 operator*(float scalar);
        Vector2 operator/(float scalar);
        float dot(Vector2 other);
        float Length();
        Vector2 Normalize();
    };
}}

#endif