#ifndef TREE_DRAWER_GUARD
#define TREE_DRAWER_GUARD
#include "../Nodes.h"


namespace Engine{
    class TreeDrawer
    {

        public:
        void drawScene(Nodes::Node* root, DataTypes::Vector2 windowSize);
        
        private:
        void drawNode(Nodes::Node* node);
    };
}

#endif