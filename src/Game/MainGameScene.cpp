#include "MainGameScene.h"

using namespace Game;


Engine::Nodes::Node* MainGameScene::constructTree()
{
    Node* root = new Node();
    root->setName("Solar System");
    SphereMesh* sun = new SphereMesh(50, 100);
    sun->setName("Sun");
    root->addChild(sun);
    sun->Position(Vector3(0, 0, -100));

    return root;
}