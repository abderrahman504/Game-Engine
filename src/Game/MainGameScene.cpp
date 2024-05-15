#include "MainGameScene.h"
#include "Planet.h"
#include "cameraTest.cpp"

using namespace Game;
SphereMesh* createPlanet(SphereMesh* sun,std::string planetName,
                  float radius,float red,float green,
                  float blue,float xPos
        ,float yPos,float zPos);

Engine::Nodes::Node* MainGameScene::constructTree()
{
    Node* root = new Node();
    root->setName("Solar System");
    SphereMesh* sun = new SphereMesh(30, 100);
    Material* sunMaterial = sun->material;
    sunMaterial->color[0] = 255/256.0;
    sunMaterial->color[1] = 255/256.0;
    sunMaterial->color[2] = 0.0;
    sunMaterial->ambient_diffuse = 1;
    sunMaterial->shininess = 0;
    sunMaterial->specular = 0;
    sun->Position(Vector3(0, 0, -300));
    sun->setName("Sun");
    root->addChild(sun);
    // Earth
   SphereMesh* earth= createPlanet(sun,"Earth",15,65/256.0,175/256.0,239/256.0,100.0,0.0,0.0);

    //Moon
    createPlanet(earth,"Moon",10,0.2,0.2,0.2,0.0,50.0,0.0);

    // venus
    createPlanet(sun,"Venus",15,195/256.0,141/256.0,14/256.0,200.0,0.0,0.0);

  // mercury
    createPlanet(sun,"Mercury",5,0.941,0.906,0.902,50.0,0.0,0.0);

  // jupiter
    createPlanet(sun,"Jupiter",20,0.902,0.486,0.431,-80.0,0.0,0.0);

    //neptune
    createPlanet(sun,"Neptune",20,0.902,0.486,0.431,-150.0,0.0,0.0);
    //Mars
    createPlanet(sun,"Mars",20,1,0,0,-250.0,0.0,0.0);

    //Saturn
    createPlanet(sun,"Saturn",20,1,0.655,0.655,-350.0,0.0,0.0);


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

SphereMesh* createPlanet(SphereMesh* parent,std::string planetName,
                  float radius,float red,float green,
                  float blue,float xPos
                  ,float yPos,float zPos)
{
    SphereMesh* planet = new SphereMesh(radius, 100);
    Material* planetMaterial = planet->material;
    // Earth
    planetMaterial = planet->material;
    planetMaterial->color[0] = red;
    planetMaterial->color[1] = green;
    planetMaterial->color[2] = blue;
    planetMaterial->ambient_diffuse = 1;
    planetMaterial->shininess = 0;
    planetMaterial->specular = 0;
    planet->Position(Vector3(xPos, yPos, zPos));
    planet->setName(planetName);
    parent->addChild(planet);
    return planet;
}
