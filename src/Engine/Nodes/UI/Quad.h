#ifndef QUAD_GUARD
#define QUAD_GUARD
#include "UI.h"

namespace Engine{
namespace Nodes{

    class Quad : public UI
    {
        public:

        bool normalized_size = false;
        Vector2 size = Vector2(20, 20);
        Color color = Color::WHITE;

        Quad(){
            setName("Quad");
        }
    };

}}


#endif