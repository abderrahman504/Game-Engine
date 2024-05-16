#include "MainGameScene.h"
#include "Planet.h"
#include "cameraTest.cpp"

using namespace Game;
SpaceShipMesh * drawSpaceship(float baseWidth, float baseHeight, float height, int resolution,Vector3 *vector3);
Planet* createPlanet(Planet* parent,std::string planetName,
                  float radius,float red,float green,
                  float blue,float xPos
        ,float yPos,float zPos);

Engine::Nodes::Node* MainGameScene::constructTree()
{
    Node* root = new Node();
    root->setName("Solar System");
    Planet* sun = new Planet(30, 100);
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
   Planet* earth= createPlanet(sun,"Earth",15,65/256.0,175/256.0,239/256.0,100.0,0.0,0.0);
  earth->orbitRadius=100;
  earth->orbitSpeed=PI * 0.298;
    //Moon
  Planet* moon=  createPlanet(earth,"Moon",10,0.2,0.2,0.2,0.0,0.0,0.0);
  moon->orbitRadius=50;
  moon->orbitSpeed=PI * 0.4;
    // venus
   Planet* venus= createPlanet(sun,"Venus",15,195/256.0,141/256.0,14/256.0,130.0,0.0,0.0);
 venus->orbitRadius=130;
 venus->orbitSpeed=PI * 0.35;
  // mercury
 Planet* mercury=   createPlanet(sun,"Mercury",5,0.941,0.906,0.902,50.0,0.0,0.0);
mercury->orbitRadius=50;
mercury->orbitSpeed=PI * 0.479;
  // jupiter
   Planet* jupiter= createPlanet(sun,"Jupiter",20,0.902,0.486,0.431,160.0,0.0,0.0);
jupiter->orbitRadius=160;
jupiter->orbitSpeed=PI * 0.131;
    //neptune
   Planet* neptune= createPlanet(sun,"Neptune",20,0.902,0.486,0.431,200.0,0.0,0.0);
   neptune->orbitRadius=200;
   neptune->orbitSpeed=PI*0.054;
    //Mars
   Planet* mars= createPlanet(sun,"Mars",20,1,0,0,250.0,0.0,0.0);
mars->orbitRadius=250;
mars->orbitSpeed=PI * 0.24;
    //Saturn
  Planet* saturn=  createPlanet(sun,"Saturn",20,1,0.655,0.655,300.0,0.0,0.0);
saturn->orbitRadius=300;
saturn->orbitSpeed=PI * 0.096;
    SpaceShipMesh* spaceship = drawSpaceship(10, 10, 20, 100, new Vector3(-12, -8, -12));
//    root->addChild(spaceship);




    //Create 8 planet objects and make them children of the sun
    //For each planet you need to set its material, orbit radius and orbit speed. Don't worry about setting position.
    //You can create another planet object for the moon and make it a child of earth.
    CameraTest* cameraParent = new CameraTest();
    Camera3D* camera = new Camera3D();
    camera->active = true;
    cameraParent->addChild(camera);
    cameraParent->addChild(spaceship);
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

Planet* createPlanet(Planet* parent,std::string planetName,
                  float radius,float red,float green,
                  float blue,float xPos
                  ,float yPos,float zPos)
{
    Planet* planet = new Planet(radius, 100);
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


SpaceShipMesh * drawSpaceship(float baseWidth, float baseHeight, float height, int resolution,Vector3 *vector3)
{
    SpaceShipMesh* spaceship =new SpaceShipMesh(baseWidth, baseHeight, height, resolution);

    Material* spaceshipMaterial = spaceship->material;
    // set color of spaceship to be red
    spaceshipMaterial->color[0] = 1;
    spaceshipMaterial->color[1] = 0;
    spaceshipMaterial->color[2] = 0;
    spaceshipMaterial->ambient_diffuse = 1;
    spaceshipMaterial->shininess = 0;
    spaceshipMaterial->specular = 0;
    spaceship->Position(*vector3);
    spaceship->setName("Spaceship");

    SpaceShipMesh* spaceship1= new SpaceShipMesh(baseWidth/1.5, baseHeight/3,height/2, resolution);
    spaceshipMaterial = spaceship1->material;
    // set color of spaceship to be red
    spaceshipMaterial->color[0] = 1;
    spaceshipMaterial->color[1] = 1;
    spaceshipMaterial->color[2] = 0;
    spaceshipMaterial->ambient_diffuse = 1;
    spaceshipMaterial->shininess = 0;
    spaceshipMaterial->specular = 0;
    spaceship1->Position(Vector3(5, 0,height/5.5));

    spaceship1->setName("right wing");
    SpaceShipMesh* spaceship2 = new SpaceShipMesh(baseWidth/1.5, baseHeight/3,height/2, resolution);
    spaceshipMaterial = spaceship2->material;
    // set color of spaceship to be red
    spaceshipMaterial->color[0] = 1;
    spaceshipMaterial->color[1] = 1;
    spaceshipMaterial->color[2] = 0;
    spaceshipMaterial->ambient_diffuse = 1;
    spaceshipMaterial->shininess = 0;
    spaceshipMaterial->specular = 0;
    spaceship2->Position(Vector3(-5, 0, height/5.5));
    spaceship2->setName("left wing");

    SphereMesh* spaceshiphead = new SphereMesh(height/10, resolution);
    spaceshipMaterial = spaceshiphead->material;
    // set color of spaceship to be red
    spaceshipMaterial->color[0] = 1;
    spaceshipMaterial->color[1] = 1;
    spaceshipMaterial->color[2] = 0;
    spaceshipMaterial->ambient_diffuse = 1;
    spaceshipMaterial->shininess = 0;
    spaceshipMaterial->specular = 0;
    spaceshiphead->Position(Vector3(0, 1.2, -7.5));
    spaceshiphead->setName("head");



    spaceship->addChild(spaceship1);
    spaceship->addChild(spaceship2);
    spaceship->addChild(spaceshiphead);

    return spaceship;

}