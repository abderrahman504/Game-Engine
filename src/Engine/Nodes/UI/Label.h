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

        

        Label(){
            setName("Label");
        }

    };

}}

#endif