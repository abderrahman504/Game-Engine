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
    sun->Position(Vector3(0, 0, -100));
    sun->setName("Sun");
    root->addChild(sun);
    //Create 8 planet objects and make them children of the sun
    //For each planet you need to set its material, orbit radius and orbit speed. Don't worry about setting position.
    //You can create another planet object for the moon and make it a child of earth.
    return root;
}