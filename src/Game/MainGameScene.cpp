#include "MainGameScene.h"
#include "Planet.h"
#include "cameraTest.cpp"
#include "MainPlayer.h"
#include "enemy.h"

using namespace Game;

SpaceShipMesh *drawSpaceship(float baseWidth, float baseHeight, float height, bool isEnemy);

Planet *createPlanet(Node3D *parent, std::string planetName, float radius, float red, float green, float blue);

Engine::Nodes::Node *MainGameScene::constructTree()
{
    Node *root = new Node();
    Skybox *sb = new Skybox(10000);
    std::vector<std::string> faces = {
        "../resources/images/star.jpeg",
        "../resources/images/star.jpeg",
        "../resources/images/star.jpeg",
        "../resources/images/star.jpeg",
        "../resources/images/star.jpeg",
        "../resources/images/star.jpeg",
    };
    sb->LoadSkyboxTextures(faces);
    sb->setName("Skybox");
    sb->position = Vector3(0, 0, 0);
    root->addChild(sb);

    // Enemy *enemy = new Enemy();
    root->setName("Solar System");
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
    // set texture of the sun

    // mercury
    Planet *mercury = createPlanet(sun, "Mercury", 20, 0.941, 0.906, 0.902);
    mercury->orbitRadius = 400;
    mercury->orbitSpeed = 30 * PI / 180;
    //    mercury->material->setTextureCoordinates(mercury->TexCoords(), mercury->TexCoordsSize());
    //    mercury->material->setTexture("../resources/images/mercury.jpg");
    //     venus
    Planet *venus = createPlanet(sun, "Venus", 25, 195 / 256.0, 141 / 256.0, 14 / 256.0);
    venus->orbitRadius = 560;
    venus->orbitSpeed = 20 * PI / 180;
    //    venus->material->setTextureCoordinates(venus->TexCoords(), venus->TexCoordsSize());
    //    venus->material->setTexture("../resources/images/venus.jpg");
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
    // Mars
    Planet *mars = createPlanet(sun, "Mars", 30, 0.78, 0.54, 0.45);
    mars->orbitRadius = 1000;
    mars->orbitSpeed = 10 * PI / 180;
    mars->material->setTextureCoordinates(mars->TexCoords(), mars->TexCoordsSize());
    mars->material->setTexture("../resources/images/mars.jpg");
    // Saturn
    Planet *saturn = createPlanet(sun, "Saturn", 60, 0.78, 0.54, 0.45);
    saturn->orbitRadius = 1400;
    saturn->orbitSpeed = 3 * PI / 180;
    saturn->material->setTextureCoordinates(saturn->TexCoords(), saturn->TexCoordsSize());
    saturn->material->setTexture("../resources/images/saturn.jpg");
    DiskMesh3D *saturn_rings = new DiskMesh3D(100, 130, 0.5, 50);
    saturn_rings->material->color = Color::fromRGBInt(115, 104, 80, 1);
    saturn_rings->material->ambient_diffuse = 0.5;
    saturn_rings->material->specular = 0;
    saturn_rings->rotateAround(Vector3::RIGHT, 10 * PI / 180);
    saturn->addChild(saturn_rings);
    // jupiter

    Planet *jupiter = createPlanet(sun, "Jupiter", 80, 0.78, 0.74, 0.45);
    jupiter->orbitRadius = 1800;
    jupiter->orbitSpeed = 1 * PI / 180;

    // neptune
    Planet *neptune = createPlanet(sun, "Neptune", 70, 0.06, 0.5, 0.7);
    neptune->orbitRadius = 2400;
    neptune->orbitSpeed = 0.5 * PI / 180;
    neptune->material->setTextureCoordinates(neptune->TexCoords(), neptune->TexCoordsSize());
    neptune->material->setTexture("../resources/images/neptune.jpeg");

    // Creating Enemy
    Enemy *enemy = new Enemy();
    enemy->position = Vector3(0, 0, 150);
    SpaceShipMesh *enemy_spaceship = drawSpaceship(5, 5, 30, true);
    enemy->addChild(enemy_spaceship);

    root->addChild(enemy);

    // Creating Player
    Camera3D *camera = new Camera3D();
    camera->active = true;
    camera->setFar(10000);
    MainPlayer *player = new MainPlayer(10, 20, 10, 10, 100, 150);
    enemy->attachEnemy((Player *)player);
    player->setName("Player");
    player->position = Vector3(0, 0, 300);
    player->addChild(camera);
    root->addChild(player);
    // player->addChild(collider);

    // Minimap Camera

    Camera3D *camera2 = new Camera3D();
    camera2->active = true;
    camera2->viewport = Engine::VIEWPORT_2;
    camera2->viewportPosition = Vector2(0.7, 0.1);
    camera2->viewportSize = Vector2(0.2, 0.2);
    camera2->setFOV(90);
    camera2->setFar(5000);
    camera2->position = Vector3(0, 3000, 0);
    camera2->rotateAround(Vector3::LEFT, PI / 2);
    root->addChild(camera2);

    return root;
}

Planet *createPlanet(Node3D *parent, std::string planetName, float radius,
                     float red, float green, float blue)
{
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

SpaceShipMesh *drawSpaceship(float baseWidth, float baseHeight, float height, bool isEnemy)
{

    SpaceShipMesh *spaceship = new SpaceShipMesh(baseWidth, baseHeight, height, 50);

    Material *spaceshipMaterial = spaceship->material;
    // set color of spaceship to be red
    if (isEnemy)
        spaceshipMaterial->color = Color::fromRGBFloat(1, 0, 0, 1);
    else
        spaceshipMaterial->color = Color::fromRGBFloat(0, 0, 1, 1);
    spaceshipMaterial->ambient_diffuse = 1;
    spaceshipMaterial->shininess = 0;
    spaceshipMaterial->specular = 0;
    spaceship->setName("Spaceship Model");
    spaceship->lookTowards(Vector3::DOWN, Vector3::FORWARD);

    SpaceShipMesh *right_wing = new SpaceShipMesh(baseWidth / 2, baseHeight / 2, height / 3, 50);
    spaceshipMaterial = right_wing->material;
    // set color of spaceship to be red
    spaceshipMaterial->color = Color::fromRGBFloat(1.0f, 1.0f, 0.0f, 1.0f);
    spaceshipMaterial->ambient_diffuse = 1;
    spaceshipMaterial->shininess = 0;
    spaceshipMaterial->specular = 0;
    right_wing->position = Vector3(5, baseWidth * 1.5, 0);
    right_wing->setName("right wing");

    SpaceShipMesh *left_wing = new SpaceShipMesh(baseWidth / 2, baseHeight / 2, height / 3, 50);
    spaceshipMaterial = left_wing->material;
    spaceshipMaterial->color = Color::fromRGBFloat(1.0f, 1.0f, 0.0f, 1.0f);
    spaceshipMaterial->ambient_diffuse = 1;
    spaceshipMaterial->shininess = 0;
    spaceshipMaterial->specular = 0;
    left_wing->position = Vector3(-5, baseWidth * 1.5, 0);
    left_wing->setName("left wing");

    spaceship->addChild(right_wing);
    spaceship->addChild(left_wing);
    // spaceship->addChild(spaceshiphead);

    return spaceship;
}