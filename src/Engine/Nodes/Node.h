#ifndef NODE_GUARD
#define NODE_GUARD
#include <vector>

namespace Engine{
namespace Nodes{
    
    class Node{
        Node& parent;
        std::vector<Node*> children;

        public:
        void setParent(Node* parent);
        void addChild(Node* child);
        void removeChild(Node* child);
        void removeChildAt(int index);
        Node* getChildAt(int index);
        Node* getParent();

        //Calls this->idle() and propegateIdle() on all children
        void propegateIdle(double deltaTime); 
        //Calls this->idle() and propegateIdle() on all children
        void propegateDraw(); 
        
        private:
        virtual void idle(double deltaTime);
        virtual void draw();

    };

}}

#endif