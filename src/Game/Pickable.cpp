#include "Pickable.h"


using namespace Game;



Pickable::Pickable(Vector3 position,char * path, float radius, int resolution, float maxLifeTime, float damage, int type) : Engine::Nodes::CollisionBody3D(){
    this->maxLifeTime = maxLifeTime;
    this->radius = radius;
    this->lifeTime = 0;
    this->setName("Pickable");
    this->health = damage;
    this->mesh = new Engine::Nodes::SphereMesh(radius, resolution);
    Material *material = new Material();
    material->color = Color::fromRGBFloat(255,255,255,1);
    material->ambient_diffuse = 1;
    material->shininess = 0;
    material->specular = 0;
    
    this->mesh->material = material;
    addChild(this->mesh);
    Collider3D* collider = new SphereCollider(radius);
    addChild(collider);
    this->position = position;
    this->mesh->material->setTextureCoordinates(mesh->TexCoords(), mesh->TexCoordsSize());
    this->mesh->material->setTexture(path);
    this->type = type;

    
}

void Pickable::idle(double deltaTime) {
    lifeTime += deltaTime;
    if(lifeTime > maxLifeTime)
    {
        destroy();
    }
}

void Pickable::onCollision(Engine::Nodes::CollisionBody3D *other, Engine::CollisionInfo info) {

    std::cout << "Picable Collision with  " << other->getName()<< "and type " <<type<< std::endl;
    if(other->getName() == "Player")
    {
        
        if(type == 0 || type ==1  || type ==2 )
        {
            MainPlayer *player = dynamic_cast<MainPlayer*>(other);
            player->setAmmo(type);
            SoundManager::setVolume(1024);
            SoundManager::setPlayDuration(200);
            SoundManager::loadAndPlay("../resources/sounds/pick.mp3");
        }
        else if(type == 3)
        {

            MainPlayer *player = dynamic_cast<MainPlayer*>(other);
            player->addHealth(health);
            SoundManager::setVolume(1024);
            SoundManager::setPlayDuration(1000);
            SoundManager::loadAndPlay("../resources/sounds/levelup.mp3");

        }
        else if(type == 4)
        {
            MainPlayer *player = dynamic_cast<MainPlayer*>(other);
            player->addScore(health);
            SoundManager::setVolume(255);
            SoundManager::setPlayDuration(200);
            SoundManager::loadAndPlay("../resources/sounds/coin.mp3");
        }
        destroy();
    }


}

void Pickable::destroy() {
    this->Parent()->removeChild(this);
    queueFree();
}

