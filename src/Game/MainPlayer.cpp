//
// Created by AhmedSamir on 12/06/2024.
//

#include "MainPlayer.h"


using namespace Game;

void MainPlayer::idle(double deltaTime) {
    Engine::InputServer &inputServer = getSceneHead().getInputServer();

    
    if(inputServer.isKeyJustPressed(27)){ //ESC button
        getSceneHead().unfreezeCursor();
        getSceneHead().showCursor();
    } 
    else if(inputServer.isKeyJustPressed(MOUSE_LEFT)){
        getSceneHead().freezeCursor();
        getSceneHead().hideCursor();
    }
    
    Vector3 moveDir = Vector3::ZERO;
    if (inputServer.isKeyPressed('w')) moveDir = moveDir + Vector3::FORWARD;
    if (inputServer.isKeyPressed('s')) moveDir = moveDir + Vector3::BACK;
    if (inputServer.isKeyPressed('a')) moveDir = moveDir + Vector3::LEFT;
    if (inputServer.isKeyPressed('d')) moveDir = moveDir + Vector3::RIGHT;
    if (inputServer.isKeyPressed(' ')) moveDir = moveDir + Vector3::UP;
    if (inputServer.isKeyPressed('c')) moveDir = moveDir + Vector3::DOWN;
    if (inputServer.isKeyPressed('q')) rotateAround(Vector3::UP, 0.01);
    if (inputServer.isKeyPressed('e')) rotateAround(Vector3::UP, -0.01);
    // if (inputServer.isKeyPressed('r')) shoot();

    moveDir = moveDir.normalize();

    if(moveDir.length() <= 0)
    {
        // Slow the player down
        velocity = velocity - velocity.normalize() * acceleration * deltaTime;
        if(velocity.length() < acceleration * deltaTime)
            velocity = Vector3::ZERO;
    }
    else
    {
        //Accelerate in given direction
        moveDir = moveDir.rotateBy(orientation);
        velocity = velocity + moveDir * acceleration * deltaTime;
        if(velocity.length() > max_speed)
            velocity = velocity.normalize() * max_speed;
    }
    position = position + velocity * deltaTime;



    // rotate the player as the mouse moves
        Vector3 forward = getForward();
        float travel_angle = forward.angleTo(look_direction);
        Vector3 spin_vec = forward.cross(look_direction);

        //Figure out whether to rotate faster towards the player or slow down
        if(rotation_speed == 0 && travel_angle != 0)
        {
            //accelerate rotation
            rotation_speed += rotation_acceleration * deltaTime;
            if(rotation_speed > max_rotation_speed)
                rotation_speed = max_rotation_speed;
        }
        else
        {
            float travel_time = travel_angle / rotation_speed;
            float halting_time = rotation_speed / rotation_acceleration;
            if(travel_time < halting_time)
            {
                //decelerate rotation
                rotation_speed -= rotation_acceleration * deltaTime;
                if(rotation_speed < 0)
                    rotation_speed = 0;
            }
            else
            {
                //accelerate rotation
                rotation_speed += rotation_acceleration * deltaTime;
                if(rotation_speed > max_rotation_speed)
                    rotation_speed = max_rotation_speed;
            }
        }
        if(rotation_speed != 0)
        {
            float rotation = rotation_speed * deltaTime;
            if(rotation > travel_angle)
                rotation = travel_angle;
            rotateAround(spin_vec, rotation);
            lookTowards(getForward(), Vector3::UP);
        }

    //if mouse left button is pressed shoot
    if (inputServer.isKeyJustPressed(MOUSE_LEFT)) {
        shoot();
    }

}

void MainPlayer::shoot() {
    Bullet *bullet = new Bullet(0.5, 100, 200, 5, 10,ammo,true);
    bullet->collisionLayer = 4; //Bullet exists on layer 3
    bullet->collisionMask = 2; //Bullet scans for layer 2
    bullet->position = position + getForward() * 1;
    bullet->orientation = orientation;
    bullet->lookTowards(getForward(), Vector3::UP);
    bullet->moveDir = getForward();
    this->Parent()->addChild(bullet);
    SphereCollider *collider = new SphereCollider(0.5);

    collider->setName("Bullet");
    bullet->addChild(collider);
    bullet->shooter = true;
}


void MainPlayer::onCollision(Engine::Nodes::CollisionBody3D *other, Engine::CollisionInfo info) {
    std::cout << "Collision between player and " << other->getName() << "\n";

    if (other->getName() == "Bullet") {
        Bullet *bullet = dynamic_cast<Bullet *>(other);
        if (bullet->Parent()==nullptr) return;
        if (bullet->shooter) return;
        else{
            health -= bullet->getDamage();
            bullet->destroy();
            if (health <= 0) {
                // destroy();
                std::cout<<"Player is dead"<<std::endl;
            }
            std::cout<<"Player Health: "<<health<<std::endl;
        }
    }

    // if (other->getName() == "Enemy") {
    //     health -= 10;
    //     if (health <= 0) {
    //         destroy();
    //     }
    // }

    // if (other->getName() == "Pickable") {
    //     std::cout<<health<<std::endl;
    //     std::cout<<ammo<<std::endl;
    //     std::cout<<score<<std::endl;
    // }

}

void MainPlayer::destroy() {
    
    queueFree();
}




void MainPlayer::setScore(int score) {
    this->score = score;
}
int MainPlayer::getScore(){
    return score;
}
void MainPlayer::addScore(int score){
    this->score += score;
}
void MainPlayer::addHealth(int health){
    this->health += health;
}
void MainPlayer::setAmmo(int ammo){
    this->ammo = ammo;
}
    