#include "MainGameScene.h"
#include "Planet.h"
#include "cameraTest.cpp"
#include "MainPlayer.h"
#include "enemy.h"

#include "HealthBar.cpp"
#include "Score.cpp"

#include "MinimapCamera.h"
#include "GenerateEnemies.cpp"

#include "PickableGenrator.h"
using namespace Game;

static ConeMesh *drawSpaceship(float baseWidth, float baseHeight, float height, bool isEnemy);

Planet* createPlanet(Node3D* parent, std::string planetName, float radius, float red, float green, float blue);

Engine::Nodes::Node *MainGameScene::constructTree() {
    Node *root = new Node();

    PickabelGenerator::generate(root,10);
    // Enemy *enemy = new Enemy();

    root->setName("Solar System");
    Label *Health_label = new Label();
    Health_label->z_index = 1;
    Health_label->normalized_coordinates = true;
    Health_label->text = "Health";
    Health_label->position = Vector2(0.8f, 0.95f);
    Health_label->color = Color::fromRGBFloat(0, 0, 1, 1);
    root->addChild(Health_label);
    HealthBar *health_bar = new HealthBar();
    health_bar->z_index = 1;
    health_bar->normalized_coordinates = true;
    health_bar->position = Vector2(0.8f, 0.85f);
    health_bar->size = Vector2(0.3f, 0.05f);
    health_bar->color = Color::fromRGBFloat(0, 1, 0, 1);
    health_bar->setName("Health Bar");
    root->addChild(health_bar);
    Score *score = new Score();
    score->z_index = 1;
    score->normalized_coordinates = true;
    score->position = Vector2(0.8f, 0.8f);
    root->addChild(score);
//    Quad *quad = new Quad();
//    quad->z_index = 0;
//    quad->normalized_coordinates = true;
//    quad->position = Vector2(0.7f, 0.7f);
//    quad->size = Vector2(0.3f, 0.3f);
//    root->addChild(quad);

    SphereMesh *sun = new SphereMesh(150, 50);
    sun->material->color = Color(255, 255, 0, 255);
    sun->material->ambient_diffuse = 1;
    sun->material->specular = 1;
    sun->material->emission = 0.8;
    sun->position = Vector3(0, 0, 0);
    sun->material->setTextureCoordinates(sun->TexCoords(), sun->TexCoordsSize());
    sun->material->setTexture("../resources/images/sun.png");
    sun->setName("Sun");
    root->addChild(sun);


    Light3D *sunLight = new Light3D();
    sunLight->color = Color::fromRGBInt(255, 218, 143, 1);
    sunLight->ambient = 0.5;
    sunLight->diffuse = 0.8;
    sunLight->specular = 1;
    sunLight->setName("SunLight");
    sun->addChild(sunLight);


    sun->material->setTextureCoordinates(sun->TexCoords(), sun->TexCoordsSize());
    sun->material->setTexture("../resources/images/sun2.jpeg");

    // mercury
    Planet *mercury = createPlanet(sun, "Mercury", 20, 0.941, 0.906, 0.902);
    mercury->orbitRadius = 400;
    mercury->orbitSpeed = 30 * PI / 180;
   mercury->material->setTextureCoordinates(mercury->TexCoords(), mercury->TexCoordsSize());
   mercury->material->setTexture("../resources/images/mercury.jpg");
//     venus
    Planet *venus = createPlanet(sun, "Venus", 25, 195 / 256.0, 141 / 256.0, 14 / 256.0);
    venus->orbitRadius = 560;
    venus->orbitSpeed = 20 * PI / 180;
   venus->material->setTextureCoordinates(venus->TexCoords(), venus->TexCoordsSize());
   venus->material->setTexture("../resources/images/venus.jpg");
    // Earth

    Planet *earth = createPlanet(sun, "Earth", 35, 65 / 256.0, 175 / 256.0, 239 / 256.0);
    earth->orbitRadius = 800;
    earth->orbitSpeed = 15 * PI / 180;
    
    earth->material->setTextureCoordinates(earth->TexCoords(), earth->TexCoordsSize());
    earth->material->setTexture("../resources/images/earth.jpeg");
    // Moon
    Planet *moon = createPlanet(earth, "Moon", 10, 0.4, 0.4, 0.4);
    moon->orbitRadius = 140;
    moon->orbitSpeed = 70 * PI / 180;
    moon->material->setTextureCoordinates(moon->TexCoords(), moon->TexCoordsSize());
    moon->material->setTexture("../resources/images/moon.jpg");
    //Mars
    Planet *mars = createPlanet(sun, "Mars", 30,  0.78, 0.54, 0.45);
    mars->orbitRadius = 1000;
    mars->orbitSpeed = 10 * PI / 180;
    mars->material->setTextureCoordinates(mars->TexCoords(), mars->TexCoordsSize());
    mars->material->setTexture("../resources/images/mars.jpg");
    //Saturn
    Planet *saturn = createPlanet(sun, "Saturn", 60, 0.78, 0.54, 0.45);
    saturn->orbitRadius = 1400;
    saturn->orbitSpeed = 3 * PI / 180;
    saturn->material->setTextureCoordinates(saturn->TexCoords(), saturn->TexCoordsSize());
    saturn->material->setTexture("../resources/images/saturn.jpg");

    DiskMesh3D* saturn_rings = new DiskMesh3D(100, 130, 0.5, 50);
    saturn_rings->material->color = Color::fromRGBInt(115, 104, 80, 1);
    saturn_rings->material->ambient_diffuse = 0.5;
    saturn_rings->material->specular = 0;
    saturn_rings->rotateAround(Vector3::RIGHT, 10* PI / 180);
    saturn->addChild(saturn_rings);
    // jupiter

    Planet *jupiter = createPlanet(sun, "Jupiter", 80, 0.78, 0.74, 0.45);
    jupiter->orbitRadius = 1800;
    jupiter->orbitSpeed = 1 * PI / 180;

    jupiter->material->setTextureCoordinates(jupiter->TexCoords(), jupiter->TexCoordsSize());
    jupiter->material->setTexture("../resources/images/jupiter.jpeg");

    //neptune
    Planet *neptune = createPlanet(sun, "Neptune", 70, 0.06, 0.5, 0.7);
    neptune->orbitRadius = 2400;
    neptune->orbitSpeed = 0.5 * PI / 180;
    neptune->material->setTextureCoordinates(neptune->TexCoords(), neptune->TexCoordsSize());
    neptune->material->setTexture("../resources/images/neptune.jpeg");


    // Creating Enemy

  GenerateEnemies *enemy = new GenerateEnemies();
    root->addChild(enemy);



    // Creating Player

    Camera3D *camera = new Camera3D();
    camera->position = Vector3(0, 7, 30);
    camera->setFar(10000);

    MainPlayer *player = new MainPlayer(10, 20, 10, 10, 100, 150);
    player->setName("Player");
    player->position = Vector3(0, 0, 400);
    player->addChild(camera);
    enemy->attachEnemy((Player*)player);
    root->addChild(player);


    // Minimap Camera

    Quad* minimap_border = new Quad();
    minimap_border->color = Color::fromRGBFloat(0.3, 0.3, 0.3, 1);
    minimap_border->normalized_coordinates = true;
    minimap_border->position = Vector2(0.69, 0.09);
    minimap_border->size = Vector2(0.22, 0.22);
    root->addChild(minimap_border);

    MinimapCamera *camera2 = new MinimapCamera();
    camera2->viewport = Engine::VIEWPORT_2;
    camera2->viewportPosition = Vector2(0.7, 0.1);
    camera2->viewportSize = Vector2(0.2, 0.2);
    camera2->setFOV(90);
    camera2->setFar(10000);
    camera2->target = player;
    camera2->distance_from_target = 800;
    
    root->addChild(camera2);

    return root;
}

Planet *createPlanet(Node3D *parent, std::string planetName, float radius,
                     float red, float green, float blue) {
    Planet *planet = new Planet(radius, 100);
    Material *planetMaterial = planet->material;
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