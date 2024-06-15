//
// Created by AhmedSamir on 12/06/2024.
//

#include "Bullet.h"

using namespace Game;

Bullet::Bullet(float radius, int resolution, float speed,float maxLifeTime, float damage,int type,bool sound) : Engine::Nodes::CollisionBody3D(){
    this->speed = speed;
    this->maxLifeTime = maxLifeTime;
    this->radius = radius;
    this->height = height;
    this->lifeTime = 0;
    this->setName("Bullet");
    this->damage = damage;
    this->mesh = new Engine::Nodes::SphereMesh(radius, resolution);
    Material *material = new Material();
    material->color = Color::fromRGBFloat(255,255,255,1);
    material->ambient_diffuse = 1;
    material->shininess = 0;
    material->specular = 0;
    this->mesh->material = material;
    addChild(this->mesh);
    Collider3D* collider = new SphereCollider(radius > 0.5*height ? radius : 0.5*height);
    addChild(collider);
    
    this->mesh->material->setTextureCoordinates(mesh->TexCoords(), mesh->TexCoordsSize());
    this->type = type;
    this->mesh->material->setTexture(BULLETS_DATA[type].txtPath);

    if (sound){
    SoundManager::setVolume(255);
    SoundManager::setPlayDuration(150);
    SoundManager::loadAndPlay(BULLETS_DATA[type].soundPath);}

}


void Bullet::destroy(){
    // this->Parent()->removeChild(this);
    queueFree();
}


void Bullet::idle(double deltaTime) {
    lifeTime += deltaTime;
    if(lifeTime > maxLifeTime)
    {
        destroy();
    }
    position = position + moveDir * speed * deltaTime;
}



float Bullet::getDamage() {
    return damage;
}
