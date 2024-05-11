#include "Quaternion.h"
#include "Vector3.h"
#define _USE_MATH_DEFINES
#include <cmath>


namespace Engine{
namespace DataTypes{

    const Quaternion Quaternion::FORWARD = Quaternion(0, Vector3(0,0,0));
    const Quaternion Quaternion::LEFT = Quaternion(90, Vector3(0,1,0));
    const Quaternion Quaternion::RIGHT = Quaternion(90, Vector3(0,-1,0));
    const Quaternion Quaternion::UP = Quaternion(90, Vector3(1,0,0));
    const Quaternion Quaternion::DOWN = Quaternion(90, Vector3(-1,0,0));

    Quaternion::Quaternion(): w(1), i(0), j(0), k(0){}
    Quaternion::Quaternion(float w, float i, float j, float k): w(w), i(i), j(j), k(k){}
    
    Quaternion::Quaternion(float angle, Vector3 axis)
    {
        this->w = cos(angle / 2);
        this->i = axis.x * sin(angle / 2);
        this->j = axis.y * sin(angle / 2);
        this->k = axis.z * sin(angle / 2);
    }
    Quaternion Quaternion::operator*(Quaternion q)
    {
        float w = this->w*q.w - this->i*q.i - this->j*q.j - this->k*q.k;
        float i = this->w*q.i + this->i*q.w + this->j*q.k - this->k*q.j;
        float j = this->w*q.j - this->i*q.k + this->j*q.w + this->k*q.i;
        float k = this->w*q.k + this->i*q.j - this->j*q.i + this->k*q.w;
        return Quaternion(w, i, j, k);
    }
    Quaternion Quaternion::operator*(float f){
        return Quaternion(w*f, i*f, j*f, k*f);
    }
    Quaternion Quaternion::operator/(float f){
        return Quaternion(w/f, i/f, j/f, k/f);
    }
    Quaternion Quaternion::operator*(Vector3 v){
        Quaternion res = Quaternion(0, v.x, v.y, v.z);
        return *this * res;
    }
    Quaternion Quaternion::operator+(Quaternion q){
        return Quaternion(w + q.w, i + q.i, j + q.j, k + q.k);
    }
    Quaternion Quaternion::operator-(Quaternion q){
        return Quaternion(w - q.w, i - q.i, j - q.j, k - q.k);
    }
    void Quaternion::angleAndAxis(float* angleRad, Vector3* axis)
    {
        Quaternion unit = this->normalize();
        *angleRad = acos(unit.w) * 2;
        double sine = (sin(*angleRad / 2));
        if (sine == 0.0){
            axis->x = axis->y = axis->z = 0;
        }
        else{
            axis->x = unit.i / sine;
            axis->y = unit.j / sine;
            axis->z = unit.k / sine;
        }
    }
    Quaternion Quaternion::conjugate(){
        return Quaternion(w, -i, -j, -k);
    }
    float Quaternion::magnitude(){
        return sqrt(w*w + i*i + j*j + k*k);
    }
    Quaternion Quaternion::normalize(){
        float mag = magnitude();
        return Quaternion(w/mag, i/mag, j/mag, k/mag);
    }
    Quaternion Quaternion::inverse(){
        return conjugate() / magnitude();
    }

}}
