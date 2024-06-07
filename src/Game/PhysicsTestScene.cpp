#include "../Engine.h"
#include "ControllableBody.cpp"

using namespace Engine;

class PhysicsTestScene : public SceneHead{

    public:
    Nodes::Node* constructTree()
    {
        Node* root = new Node();
        root->setName("Root");
        Camera3D* camera = new Camera3D();
        camera->active = true;
        camera->position = Vector3(0, 200, 0);
        camera->lookTowards(Vector3::DOWN, Vector3::FORWARD);
        camera->setNear(5);
        camera->setFar(1000);
        camera->viewport = VIEWPORT_1;
        root->addChild(camera);

        ControllableBody* controllable = new ControllableBody();
        controllable->setName("Controllable");
        controllable->collisionLayer = 0x0001;
        controllable->collisionMask = 0x0001;
        SphereMesh* myMesh = new SphereMesh(30, 50);
        myMesh->material->color[0] = 1;
        SphereCollider* myCollider = new SphereCollider(30);
        controllable->addChild(myMesh);
        controllable->addChild(myCollider);
        root->addChild(controllable);
        controllable->position = Vector3(-50, 0, 0);

        CollisionBody3D* otherBody = new CollisionBody3D();
        otherBody->setName("Body");
        otherBody->collisionLayer = 0x0001;
        otherBody->collisionMask = 0x0001;
        SphereMesh* otherMesh = new SphereMesh(50, 50);
        otherMesh->material->color[1] = 1;
        SphereCollider* otherCollider = new SphereCollider(50);
        otherBody->addChild(otherMesh);
        otherBody->addChild(otherCollider);
        root->addChild(otherBody);
        otherBody->position = Vector3(20, 0, -10);



        return root;
    }
};