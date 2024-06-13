//
// Created by AhmedSamir on 12/06/2024.
//

#include "MainPlayer.h"


using namespace Game;


void MainPlayer::shoot() {
    Bullet *bullet = new Bullet(0.5, 0.5, 100, 200, 5, 50);
    bullet->position = position + getForward() * 4;
    bullet->orientation = orientation;
    bullet->lookTowards(getForward(), Vector3::UP);
    bullet->moveDir = getForward();
    this->Parent()->addChild(bullet);

    SoundManager::setVolume(255);
    SoundManager::setPlayDuration(100);
    SoundManager::loadAndPlay("../resources/sounds/laser-gun-81720.mp3");
}

void MainPlayer::idle(double deltaTime) {
    Engine::InputServer &inputServer = getSceneHead().getInputServer();
    Vector3 moveDir = Vector3::ZERO;
    if (inputServer.isKeyPressed('w')) moveDir = moveDir + Vector3::FORWARD;
    if (inputServer.isKeyPressed('s')) moveDir = moveDir + Vector3::BACK;
    if (inputServer.isKeyPressed('a')) moveDir = moveDir + Vector3::LEFT;
    if (inputServer.isKeyPressed('d')) moveDir = moveDir + Vector3::RIGHT;
    if (inputServer.isKeyPressed(' ')) moveDir = moveDir + Vector3::UP;
    if (inputServer.isKeyPressed('c')) moveDir = moveDir + Vector3::DOWN;
    if (inputServer.isKeyPressed('q')) rotateAround(Vector3::UP, 0.01);
    if (inputServer.isKeyPressed('e')) rotateAround(Vector3::UP, -0.01);
    if (inputServer.isKeyPressed('r')) shoot();
    if (moveDir.length() != 0) {
        moveDir = moveDir.normalize().rotateBy(orientation);
        float speed = 150;
        position = position + moveDir * speed * deltaTime;
    }
    Vector2 mouseDir = inputServer.getMouseMotion();

    if (mouseDir.length() != 0) {
        float speed = 10 * PI / 180.0;
        float xAngle = speed * deltaTime * -1 * mouseDir.x;
        float yAngle = speed * deltaTime * mouseDir.y;

        rotateAround(Vector3::UP, xAngle);
        Vector3 right = getUp().cross(getForward());
        rotateAround(right, yAngle);
        if (getForward().dot(Vector3::UP) == 0)
            rotateAround(right, -0.01);
        lookTowards(getForward(), Vector3::UP);
    }

    //if mouse left button is pressed shoot
    if (inputServer.isKeyJustPressed(MOUSE_LEFT)) {
        shoot();
    }

}


void MainPlayer::onCollision(Engine::Nodes::CollisionBody3D *other, Engine::CollisionInfo info) {
    std::cout << "Collision with " << other->getName() << std::endl;
    if (other->getName() == "Bullet") {
        Bullet *bullet = dynamic_cast<Bullet *>(other);
        bullet->destroy();
        if (bullet->Parent()->getName() == "Player") return;
        health -= bullet->getDamage();
        if (health <= 0) {
            destroy();
        }
    }
    if (other->getName() == "Enemy") {
        health -= 10;
        if (health <= 0) {
            destroy();
        }
    }
}

void MainPlayer::destroy() {

    std::vector < Engine::Nodes::Node * > children = getChildren();
    for (int i = 0; i < children.size(); i++) {
        if (children[i]->getName() == "Bullet") {
            Bullet *bullet = dynamic_cast<Bullet *>(children[i]);
            bullet->destroy();
        }
    }
    this->Parent()->removeChild(this);

    delete this;
}

