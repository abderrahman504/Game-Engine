#ifndef CYLINDER_MESH_GUARD
#define CYLINDER_MESH_GUARD
#include "Mesh3D.h"

namespace Engine{
namespace Nodes{
    class CylinderMesh : public Mesh3D
    {
        protected:
        float radius;
        float height;


        public:
        CylinderMesh(float radius, float height, int resolution);
        float Radius();
        float Height();
    };
}}

#endif