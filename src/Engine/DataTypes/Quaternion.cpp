#include "Quaternion.h"
#define _USE_MATH_DEFINES
#include <cmath>


namespace Engine{
namespace DataTypes{
    
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
    void Quaternion::angle_and_axis(float* angle, Vector3* axis)
    {
        *angle = acos(w) * 2;
        double sine = (sin(*angle / 2));
        if (sine == 0.0){
            axis->x = axis->y = axis->z = 0;
        }
        else{
            axis->x = i / sine;
            axis->y = j / sine;
            axis->z = k / sine;
        *angle = *angle * 180 / M_PI;
        }
    }

}}
