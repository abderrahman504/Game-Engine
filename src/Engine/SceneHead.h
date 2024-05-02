#ifndef SCENE_HEAD_GUARD
#define SCENE_HEAD_GUARD
#include "Nodes.h"
#include "InputServer.h"
#include "PhysicsServer.h"

using namespace Engine::Nodes;
void glutIdle();
void glutDraw();
namespace Engine{
    class SceneHead
    {
        friend void ::glutIdle();
        friend void ::glutDraw();
        protected:
        Node* scene_root;

        public:
        //Pass important engine objects to the scene head and constructs the scene tree.
        void Init(InputServer *inputServer, PhysicsServer *physicsServer);
        //Starts the scene
        void Start();
        InputServer& getInputServer();
        PhysicsServer& getPhysicsServer();
        
        protected:
        virtual Node* constructTree() = 0;//Adding = 0 forces subclasses to override this function or an error is thrown.
        
        private:
        void onTreeReady();
        void idle();
        void draw();


    };
}

#endif