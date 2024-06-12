#ifndef UI_GUARD
#define UI_GUARD
#include "../Node.h";
#include "../../DataTypes.h"

using namespace Engine::DataTypes;

namespace Engine{
namespace Nodes{

    class UI : public Node
    {

        public:
        //Position of the node in the viewport in normalized coordinates.
        Vector2 position = Vector2::ZERO;
        //Size of the node in the viewport in normalized coordinates.
        Vector2 size = Vector2::ZERO;
        
        Vector2 scale = Vector2::ONE;
        //Angle of the node with the positive x-axis in radians
        float rotation = 0;

    };

}}



#endif


