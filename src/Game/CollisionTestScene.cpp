#include "../Engine.h"
#include "ControllableBody.cpp"


using namespace Engine;
using namespace Engine::DataTypes;
using namespace Engine::Nodes;


class CollisionTestScene : public SceneHead
{
    protected:
    Node* constructTree()
    {
        Node* root = new Node();

        Camera3D* camera = new Camera3D();
        camera->position = Vector3(0, 200, 0);
        camera->lookTowards(Vector3::DOWN, Vector3::FORWARD);
        camera->setNear(1);
        camera->setFar(1000);


        CollisionBody3D* body1 = new ControllableBody();
        body1->position = Vector3(-10, 0, -20);
        body1->setName("Controllable");
        SphereCollider* collider = new SphereCollider(10);
        SphereMesh* mesh = new SphereMesh(10, 50);
        mesh->material->color = Color::RED;
        mesh->material->emission = 1;

        body1->addChild(collider);
        body1->addChild(mesh);

        CollisionBody3D* body2 = new CollisionBody3D();
        body2->position = Vector3(20, 0, 20);
        body2->setName("Body2");
        collider = new SphereCollider(10);
        mesh = new SphereMesh(10, 50);
        mesh->material->color = Color::GREEN;
        mesh->material->emission = 1;

        body2->addChild(collider);
        body2->addChild(mesh);

        root->addChild(body1);
        root->addChild(body2);
        root->addChild(camera);
        


        return root;
    }
};