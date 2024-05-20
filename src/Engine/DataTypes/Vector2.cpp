#include "Vector2.h"
#define _USE_MATH_DEFINES
#include <cmath>

namespace Engine{
namespace DataTypes{

    const Vector2 Vector2::ZERO(0,0);
    const Vector2 Vector2::ONE(1,1);
    const Vector2 Vector2::UP(0,1);
    const Vector2 Vector2::DOWN(0,-1);
    const Vector2 Vector2::LEFT(-1,0);
    const Vector2 Vector2::RIGHT(1,0);

    Vector2::Vector2(): x(0), y(0){}
    Vector2::Vector2(float x, float y): x(x), y(y){}
    Vector2 Vector2::operator+(float scalar)
    {
        return Vector2(x + scalar, y + scalar);
    }
    Vector2 Vector2::operator-(float scalar)
    {
        return Vector2(x - scalar, y - scalar);
    }
    Vector2 Vector2::operator*(float scalar)
    {
        return Vector2(x * scalar, y * scalar);
    }
    Vector2 Vector2::operator/(float scalar)
    {
        return Vector2(x / scalar, y / scalar);
    }
    Vector2 Vector2::operator+(Vector2 other)
    {
        return Vector2(x + other.x, y + other.y);
    }
    Vector2 Vector2::operator-(Vector2 other)
    {
        return Vector2(x - other.x, y - other.y);
    }
    Vector2 Vector2::operator*(Vector2 other)
    {
        return Vector2(x * other.x, y * other.y);
    }
    Vector2 Vector2::operator/(Vector2 other)
    {
        return Vector2(x / other.x, y / other.y);
    }
    float Vector2::dot(Vector2 other)
    {
        return x * other.x + y * other.y;
    }
    float Vector2::cross(Vector2 other)
    {
        return x * other.y - y * other.x;
    }
    float Vector2::angleTo(Vector2 other)
    {
        float cosine = this->normalize().dot(other.normalize());
        float sine = this->normalize().cross(other.normalize());
        return sine < 0 ? -1*acos(cosine) : acos(cosine);
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