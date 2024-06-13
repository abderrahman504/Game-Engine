#ifndef SPHERE_MESH_GUARD
#define SPHERE_MESH_GUARD
#include "Mesh3D.h"

namespace Engine{
namespace Nodes{
    class SphereMesh : public Mesh3D
    {
    protected:
        float radius;

    public:
        SphereMesh(float radius, int resolution);
        float Radius();


    };
}}

#endif