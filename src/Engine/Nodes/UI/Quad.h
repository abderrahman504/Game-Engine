#ifndef QUAD_GUARD
#define QUAD_GUARD
#include "UI.h"

namespace Engine{
namespace Nodes{

    class Quad : public UI
    {
        public:

        Vector2 size = Vector2(20, 20);

        Quad(){
            setName("Quad");
        }
    };

}}


#endif