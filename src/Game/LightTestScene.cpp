#include "../Engine.h"
#include "ControllableNode.cpp"
#include "cameraTest.cpp"

using namespace Engine;
using namespace Engine::Nodes;
using namespace Engine::DataTypes;

class LightTestScene : public SceneHead
{
    protected:
    Node* constructTree()
    {
        Node* root = new Node();
        root->setName("Root");
        //Create mesh that reflects light
        SphereMesh* object = new SphereMesh(10, 50);
        object->material->color = Color::fromRGBFloat(0.2, 0.2, 1, 1);
        object->material->ambient_diffuse = 0.6;
        object->material->specular = 0.3;
        object->material->shininess = 80;

        //Create light
        SphereMesh* lightMarker = new SphereMesh(3, 30);
        lightMarker->material->color = Color::fromRGBFloat(1,1,1,1);
        lightMarker->material->ambient_diffuse = 0;
        lightMarker->material->specular = 0;
        lightMarker->material->emission = 0.7;
        lightMarker->position = (Vector3(0, 20, -100));
        Light3D* light = new Light3D();
        light->color = Color::fromRGBFloat(1,1,1,1);
        light->ambient = 0.3;
        light->diffuse = 0.6;
        light->specular = 1;

        //Create several spheres surrounding it
        for(int i=0; i < 10; i++)
        {
            SphereMesh* sphere = new SphereMesh(7, 30);
            sphere->material->color = Color::fromRGBFloat(1, 0.2, 0.2, 1);
            sphere->material->ambient_diffuse = 0.6;
            sphere->material->specular = 0.3;
            sphere->material->shininess = 80;
            sphere->position = (lightMarker->position + Vector3(50*cos(i*2*PI/10), -10, 50*sin(i*2*PI/10)));
            root->addChild(sphere);
        }

        //Create camera
        Camera3D* camera = new Camera3D();
        camera->active = true;
        camera->setNear(5);
        camera->setFar(2000);

        //Create two controllable nodes for controlling the camera and the sphere
        Game::CameraTest* cameraCont = new Game::CameraTest();
        cameraCont->setName("Camera Controller");
        cameraCont->position = (Vector3(0, 0, 0));


        ControllableNode* SphereCont = new ControllableNode();
        SphereCont->setName("Sphere Controller");
        SphereCont->position = (Vector3(0, 10, -120));
        SphereCont->forward = 'i';
        SphereCont->back = 'k';
        SphereCont->left = 'j';
        SphereCont->right = 'l';
        SphereCont->up = 'm';
        SphereCont->down = 'n';


        root->addChild(lightMarker);
        root->addChild(cameraCont);
        root->addChild(SphereCont);
        lightMarker->addChild(light);
        cameraCont->addChild(camera);
        SphereCont->addChild(object);

        return root;
    }
};