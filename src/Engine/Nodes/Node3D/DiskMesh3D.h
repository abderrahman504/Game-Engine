#ifndef DISK_3D_MESH_GUARD
#define DISK_3D_MESH_GUARD
#include "Mesh3D.h"


namespace Engine{
namespace Nodes{

    class DiskMesh3D : public Mesh3D
    {

        protected:
        float r1;
        float r2;
        float thickness;

        public:
        DiskMesh3D(float inner_radius, float outer_radius, float thickness, int resolution);
        float InnerRadius();
        float OuterRadius();
        float Thickness();
    };

}}

#endif