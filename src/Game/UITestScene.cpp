#include "../Engine.h"

using namespace Engine;

class UITestScene : public SceneHead
{
    protected:
    Nodes::Node* constructTree()
    {
        Node* root = new Node();
        root->setName("Root");

        Label* lbl1 = new Label();
        lbl1->text = "This is my first label";
        lbl1->position = Vector2(0, 0.9);
        

        Label* lbl2 = new Label();
        lbl2->text = "Middle of the screen";
        lbl2->position = Vector2(0.45, 0.45);

        Camera3D* camera = new Camera3D();

        root->addChild(camera);

        root->addChild(lbl1);
        root->addChild(lbl2);

        return root;
    }
};