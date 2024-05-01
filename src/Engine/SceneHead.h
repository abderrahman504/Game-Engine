#ifndef SCENE_HEAD_GUARD
#define SCENE_HEAD_GUARD
#include "Nodes.h"
#include "InputServer.h"
#include "PhysicsServer.h"

using namespace Engine::Nodes;
namespace Engine{
    class SceneHead
    {
        protected:
        Node* scene_root;

        public:
        //Pass important engine objects to the scene head
        void Init(InputServer &inputServer, PhysicsServer &physicsServer);
        virtual void Idle();
        virtual void Draw();
        virtual void Resize(int width, int height);
        
        void KeyboardInput(unsigned char key, int x, int y);


        void MouseInput(int button, int state, int x, int y);

    };
}

#endif