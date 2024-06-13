#ifndef LABEL_GUARD
#define LABEL_GUARD
#include "UI.h"
#include <string>


namespace Engine{
namespace Nodes{

    class Label : public UI
    {
        public:
        std::string text = "";

        Color color = Color::WHITE;

        Label(){
            setName("Label");
        }

    };

}}

#endif