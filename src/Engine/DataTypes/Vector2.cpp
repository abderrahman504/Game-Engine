#include "Vector2.h"
#define _USE_MATH_DEFINES
#include <cmath>

namespace Engine{
namespace DataTypes{

    const Vector2 Vector2::ONE = Vector2(1,1);
    const Vector2 Vector2::UP = Vector2(0,1);
    const Vector2 Vector2::DOWN = Vector2(0,-1);
    const Vector2 Vector2::LEFT = Vector2(-1,0);
    const Vector2 Vector2::RIGHT = Vector2(1,0);

    Vector2::Vector2(float x, float y): x(x), y(y){}
    Vector2 Vector2::operator+(Vector2 other)
    {
        return Vector2(x + other.x, y + other.y);
    }
    Vector2 Vector2::operator-(Vector2 other)
    {
        return Vector2(x - other.x, y - other.y);
    }
    Vector2 Vector2::operator*(float scalar)
    {
        return Vector2(x * scalar, y * scalar);
    }
    Vector2 Vector2::operator/(float scalar)
    {
        return Vector2(x / scalar, y / scalar);
    }
    float Vector2::dot(Vector2 other)
    {
        return x * other.x + y * other.y;
    }
    float Vector2::length()
    {
        return sqrt(x*x + y*y);
    }
    Vector2 Vector2::normalize()
    {
        return *this / length();
    }

}}