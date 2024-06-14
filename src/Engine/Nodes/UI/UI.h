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
        //Position of the node in the viewport in normalized coordinates.
        Vector2 position = Vector2::ZERO;
        
        

        UI(){
            setName("UI");
        }

    };

}}



#endif


