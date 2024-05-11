#ifndef TRANSFORM_3D_GUARD
#define TRANSFORM_3D_GUARD
#include "Vector3.h"
#include "Quaternion.h"

namespace Engine{
namespace DataTypes{

    struct Transform3D{
        float matrix[4][4] = {};
        static const Transform3D IDENTITY;
        static const Transform3D ZERO;


        Transform3D();
        Transform3D(float[4][4]);

        static Transform3D translation(Vector3 position);
        static Transform3D rotation(Vector3 axis, float angle);
        static Transform3D rotation(Quaternion quaternion);
        static Transform3D scaling(Vector3 scale);

        Transform3D operator*(Transform3D other);
        Transform3D operator+(Transform3D other);
        Transform3D operator-(Transform3D other);


        Transform3D inverse();
        

    };

}}

#endif