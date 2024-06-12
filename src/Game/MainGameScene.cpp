#include "MainGameScene.h"
#include "Planet.h"
#include "cameraTest.cpp"

using namespace Game;
SpaceShipMesh * drawSpaceship(float baseWidth, float baseHeight, float height, int resolution,Vector3 vector3);
Planet* createPlanet(Node3D* parent,std::string planetName,float radius,float red,float green,float blue);

Engine::Nodes::Node* MainGameScene::constructTree()
{
	Node* root = new Node();
	root->setName("Solar System");
	SphereMesh* sun = new SphereMesh(150, 50);
	sun->material->color = Color(255, 255, 0, 255);
	sun->material->ambient_diffuse = 1;
	sun->material->specular = 1;
    sun->material->emission = 0.8;
	sun->position = Vector3(0, 0, 0);
	sun->setName("Sun");
	root->addChild(sun);

    Light3D* sunLight = new Light3D();
    sunLight->color = Color::fromRGBInt(255, 218, 143, 1);
    sunLight->ambient = 0;
    sunLight->diffuse = 0.8;
    sunLight->specular = 1;
    sunLight->setName("SunLight");
    sun->addChild(sunLight);

	// mercury
	Planet* mercury = createPlanet(sun,"Mercury",20,0.941,0.906,0.902);
	mercury->orbitRadius = 400;
	mercury->orbitSpeed = 30 * PI / 180;
    // venus
	Planet* venus = createPlanet(sun,"Venus",25,195/256.0,141/256.0,14/256.0);
	venus->orbitRadius = 560;
	venus->orbitSpeed = 20 * PI / 180;
    // Earth
	Planet* earth = createPlanet(sun,"Earth",35,65/256.0,175/256.0,239/256.0);
	earth->orbitRadius = 800;
	earth->orbitSpeed = 15 * PI / 180;
    //Moon
	Planet* moon = createPlanet(earth,"Moon",10,0.4,0.4,0.4);
	moon->orbitRadius = 140;
	moon->orbitSpeed = 70 * PI / 180;
    //Mars
	Planet* mars = createPlanet(sun,"Mars",30,1,0,0);
	mars->orbitRadius = 1000;
	mars->orbitSpeed = 10 * PI / 180;
    //Saturn
	Planet* saturn = createPlanet(sun,"Saturn",60,0.78,0.54,0.45);
	saturn->orbitRadius = 1400;
	saturn->orbitSpeed = 3 * PI / 180;
  	// jupiter
   	Planet* jupiter = createPlanet(sun,"Jupiter",80,0.78,0.74,0.45);
	jupiter->orbitRadius = 1800;
	jupiter->orbitSpeed = 1 * PI / 180;
    //neptune
   	Planet* neptune = createPlanet(sun,"Neptune",70,0.06,0.5,0.7);
	neptune->orbitRadius = 2400;
	neptune->orbitSpeed = 0.5 *  PI / 180;

     SpaceShipMesh* spaceship = new SpaceShipMesh(10, 10, 20, 100);
    Material* spaceshipMaterial = spaceship->material;
    // set color of spaceship to be red
    spaceshipMaterial->color = Color::fromRGBFloat(1, 0, 0, 1);
    spaceshipMaterial->ambient_diffuse = 1;
    spaceshipMaterial->shininess = 0;
    spaceshipMaterial->specular = 0;
    spaceship->position = Vector3(0, 0, 200);
    spaceship->setName("Spaceship");
   	 root->addChild(spaceship);

	//Controllable Camera
    CameraTest* cameraParent = new CameraTest();
    Camera3D* camera = new Camera3D();
    camera->active = true;
    camera->setFar(10000);
    cameraParent->setName("Controllable");
    cameraParent->addChild(camera);
	cameraParent->position = Vector3(0, 0, 200);
    root->addChild(cameraParent);
    

	//Minimap Camera
    Camera3D* camera2 = new Camera3D();
    camera2->active = true;
    camera2->viewport = Engine::VIEWPORT_2;
    camera2->viewportPosition = Vector2(0.7,0.1);
    camera2->viewportSize = Vector2(0.2,0.2);
    camera2->setFOV(90);
    camera2->setFar(5000);
    camera2->position = Vector3(0, 3000, 0);
    camera2->rotateAround(Vector3::LEFT, PI / 2);
    root->addChild(camera2);

    return root;
}

Planet* createPlanet(Node3D* parent,std::string planetName, float radius,
float red,float green,float blue)
{
    Planet* planet = new Planet(radius, 100);
    Material* planetMaterial = planet->material;
    // Earth
    planetMaterial = planet->material;
    planetMaterial->color = Color::fromRGBFloat(red, green, blue, 1);
    planetMaterial->ambient_diffuse = 0.8;
    planetMaterial->shininess = 100;
    planetMaterial->specular = 1;
    planet->setName(planetName);
    parent->addChild(planet);
    return planet;
}


SpaceShipMesh * drawSpaceship(float baseWidth, float baseHeight, float height, int resolution,Vector3 vector3)
{
    SpaceShipMesh* spaceship =new SpaceShipMesh(baseWidth, baseHeight, height, resolution);

    Material* spaceshipMaterial = spaceship->material;
    // set color of spaceship to be red
    spaceshipMaterial->color = Color::fromRGBFloat(1, 0, 0, 1);
    spaceshipMaterial->ambient_diffuse = 1;
    spaceshipMaterial->shininess = 0;
    spaceshipMaterial->specular = 0;
    spaceship->position = vector3;
    spaceship->setName("Spaceship");

    SpaceShipMesh* spaceship1= new SpaceShipMesh(baseWidth/1.5, baseHeight/3,height/2, resolution);
    spaceshipMaterial = spaceship1->material;
    // set color of spaceship to be red
    spaceshipMaterial->color = Color::fromRGBFloat(1.0f, 1.0f, 0.0f, 1.0f);
    spaceshipMaterial->ambient_diffuse = 1;
    spaceshipMaterial->shininess = 0;
    spaceshipMaterial->specular = 0;
    spaceship1->position = Vector3(5, 0,height/5.5);

    spaceship1->setName("right wing");
    SpaceShipMesh* spaceship2 = new SpaceShipMesh(baseWidth/1.5, baseHeight/3,height/2, resolution);
    spaceshipMaterial = spaceship2->material;
    // set color of spaceship to be red
    spaceshipMaterial->color = Color::fromRGBFloat(1.0f, 1.0f, 0.0f, 1.0f);
    spaceshipMaterial->ambient_diffuse = 1;
    spaceshipMaterial->shininess = 0;
    spaceshipMaterial->specular = 0;
    spaceship2->position = Vector3(-5, 0, height/5.5);
    spaceship2->setName("left wing");

    SphereMesh* spaceshiphead = new SphereMesh(height/10, resolution);
    spaceshipMaterial = spaceshiphead->material;
    // set color of spaceship to be red
    spaceshipMaterial->color = Color::fromRGBFloat(1.0f, 1.0f, 0.0f, 1.0f);
    spaceshipMaterial->ambient_diffuse = 1;
    spaceshipMaterial->shininess = 0;
    spaceshipMaterial->specular = 0;
    spaceshiphead->position = Vector3(0, 1.2, -7.5);
    spaceshiphead->setName("head");

    spaceship->addChild(spaceship1);
    spaceship->addChild(spaceship2);
    spaceship->addChild(spaceshiphead);

    return spaceship;
}