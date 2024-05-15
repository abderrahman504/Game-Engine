#include "MainGameScene.h"
#include "Planet.h"
#include "cameraTest.cpp"

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
    sun->Position(Vector3(0, 0, -300));
    sun->setName("Sun");
    root->addChild(sun);
    SphereMesh* sun2 = new SphereMesh(50, 100);
    sunMaterial = sun2->material;
    sunMaterial->color[0] = 0.2;
    sunMaterial->color[1] = 0.5;
    sunMaterial->color[2] = 0.8;
    sunMaterial->ambient_diffuse = 1;
    sunMaterial->shininess = 0;
    sunMaterial->specular = 0;
    sun2->Position(Vector3(50, 0, 0));
    sun2->setName("Sun");
    root->addChild(sun2);
    //Create 8 planet objects and make them children of the sun
    //For each planet you need to set its material, orbit radius and orbit speed. Don't worry about setting position.
    //You can create another planet object for the moon and make it a child of earth.
    CameraTest* cameraParent = new CameraTest();
    Camera3D* camera = new Camera3D();
    camera->active = true;
    cameraParent->addChild(camera);
    root->addChild(cameraParent);
    Camera3D* camera2 = new Camera3D();
    camera2->active = true;
    camera2->viewport = Engine::VIEWPORT_2;
    camera2->viewportPosition = Vector2(0.7,0.1);
    camera2->viewportSize = Vector2(0.2,0.2);
    camera2->setFOV(90);
    camera2->Position(Vector3(50, 500, 0));
    camera2->lookTowards(Vector3::DOWN, Vector3::FORWARD);
    root->addChild(camera2);

    return root;
}