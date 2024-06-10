#ifndef PYRAMID_MESH_GUARD
#define PYRAMID_MESH_GUARD
#include "Mesh3D.h"


namespace Engine{
namespace Nodes{

    class PyramidMesh : public Mesh3D
    {

        protected:
        float height;
        float base_width;
        float base_length;

        public:
        PyramidMesh(float height, float base_width, float base_length);
        float Height();
        float BaseWidth();
        float BaseLength();
    };

}}

#endif