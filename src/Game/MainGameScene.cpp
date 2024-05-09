#include "MainGameScene.h"

using namespace Game;


Engine::Nodes::Node* MainGameScene::constructTree()
{
    Node* root = new Node();
    root->setName("Solar System");
    SphereMesh* sun = new SphereMesh(50, 100);
    Material* sunMaterial = sun->material;
    sunMaterial->color[0] = 1;
    sunMaterial->color[1] = 0.8;
    sunMaterial->color[2] = 0.2;
    sunMaterial->ambient_diffuse = 1;
    sunMaterial->shininess = 0;
    sunMaterial->specular = 0;
    sun->setName("Sun");
    root->addChild(sun);
    sun->Position(Vector3(0, 0, -100));

    return root;
}