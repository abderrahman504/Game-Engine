#ifndef UI_GUARD
#define UI_GUARD
#include "../Node.h"
#include "../../DataTypes.h"

using namespace Engine::DataTypes;

namespace Engine{
namespace Nodes{

    class UI : public Node
    {

        public:
        bool normalized_coordinates = false;
        //Position of the node in the screen. Can be specified in normalized coordinates or pixel coordinates.
        Vector2 position = Vector2::ZERO;
        //Color of this UI node if applicable.
        Color color = Color::WHITE;
        //Used to specify the order of UI elements.
        int z_index = 0;
        
        

        UI(){
            setName("UI");
        }

    };

}}



#endif


