#include "Vector3.h"
#include "Quaternion.h"
#define _USE_MATH_DEFINES
#include <cmath>

namespace Engine{
namespace DataTypes{
    const Vector3 Vector3::ZERO(0, 0, 0);
    const Vector3 Vector3::ONE(1, 1, 1);
    const Vector3 Vector3::LEFT(-1, 0, 0);
    const Vector3 Vector3::RIGHT(1, 0, 0);
    const Vector3 Vector3::UP(0, 1, 0);
    const Vector3 Vector3::DOWN(0, -1, 0);
    const Vector3 Vector3::FORWARD(0, 0, -1);
    const Vector3 Vector3::BACK(0, 0, 1);
    
    Vector3::Vector3(): x(0), y(0), z(0){}
    Vector3::Vector3(float x, float y, float z): x(x), y(y), z(z){}

    Vector3 Vector3::operator+(float scalar){
        return Vector3(x+scalar, y+scalar, z+scalar);
    }
    Vector3 Vector3::operator-(float scalar){
        return Vector3(x-scalar, y-scalar, z-scalar);
    }
    Vector3 Vector3::operator*(float scalar){
        return Vector3(x*scalar, y*scalar, z*scalar);
    }
    Vector3 Vector3::operator/(float scalar){
        return Vector3(x/scalar, y/scalar, z/scalar);
    }
    Vector3 Vector3::operator+(Vector3 other){
        return Vector3(x+other.x, y+other.y, z+other.z);
    }
    Vector3 Vector3::operator-(Vector3 other){
        return Vector3(x-other.x, y-other.y, z-other.z);
    }
    Vector3 Vector3::operator*(Vector3 other){
        return Vector3(x*other.x, y*other.y, z*other.z);
    }
    Vector3 Vector3::operator/(Vector3 other){
        return Vector3(x/other.x, y/other.y, z/other.z);
    }
    float Vector3::dot(Vector3 other){
        return x*other.x + y*other.y + z*other.z;
    }
    Vector3 Vector3::cross(Vector3 other){
        return Vector3(y*other.z - z*other.y, z*other.x - x*other.z, x*other.y - y*other.x);
    }
    //Returns the angle between this and other
    float Vector3::angleTo(Vector3 other){
        float cosine = this->normalize().dot(other.normalize());
        float sine = this->normalize().cross(other.normalize()).length();
        cosine = cosine > 1.0 ? 1.0 : cosine;
        float result = sine < 0 ? -1*acos(cosine) : acos(cosine);
        return result;
    }
    float Vector3::length(){
        return sqrt(x*x + y*y + z*z);
    }
    Vector3 Vector3::normalize(){
        return (*this)/length();
    }
    Vector3 Vector3::rotateBy(Quaternion quaternion){
        quaternion = quaternion.normalize();
        Quaternion q = quaternion * *this * quaternion.conjugate();
        return Vector3(q.i, q.j, q.k);
    }

}}