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
        void drawSceneUI(Nodes::Node* root, Nodes::Camera3D* camera);
        void drawNodeUI(Nodes::UI* node, Vector2 view_plane_dims);
    };
}

#endif