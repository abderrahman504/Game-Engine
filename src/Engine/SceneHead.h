#ifndef SCENE_HEAD_GUARD
#define SCENE_HEAD_GUARD
#include "Nodes.h"
#include "InputServer.h"
#include "PhysicsServer.h"

using namespace Engine::Nodes;
void glutIdle();
void glutDraw();
void keyboard_key(unsigned char key, int x, int y);
void keyboard_key_up(unsigned char key, int x, int y);
void special_key(int key, int x, int y);
void special_key_up(int key, int x, int y);
void mouse_motion(int x, int y);
void mouse_key(int button, int state, int x, int y);
void mouse_key_up(int button, int state, int x, int y);
void mouse_wheel(int wheel, int direction, int x, int y);
void mouse_entry(int state);
namespace Engine{
    class SceneHead
    {
        friend void ::glutIdle();
        friend void ::glutDraw();
        friend void ::keyboard_key(unsigned char key, int x, int y);
        friend void ::keyboard_key_up(unsigned char key, int x, int y);
        friend void ::special_key(int key, int x, int y);
        friend void ::special_key_up(int key, int x, int y);
        friend void ::mouse_motion(int x, int y);
        friend void ::mouse_key(int button, int state, int x, int y);
        friend void ::mouse_wheel(int wheel, int direction, int x, int y);
        friend void ::mouse_entry(int state);

        protected:
        Node* scene_root;

        public:
        //Pass important engine objects to the scene head and constructs the scene tree.
        void Init(InputServer *inputServer, PhysicsServer *physicsServer);
        //Starts the scene
        void Start();
        InputServer& getInputServer();
        PhysicsServer& getPhysicsServer();
        //Makes the mouse cursor invisible
        void hideCursor();
        //Makes the mouse cursor visible
        void showCursor();
        //Freezes the mouse cursor in place
        void freezeCursor();
        //Unfreezes the mouse cursor
        void unfreazeCursor();

        
        protected:
        //Builds the scene tree and returns the root node
        virtual Node* constructTree() = 0;//Adding = 0 forces subclasses to override this function or an error is thrown.
        
        private:
        void onTreeReady();
        void idle();
        void draw();
        void keyboard(unsigned char key, int x, int y);
        void keyboardUp(unsigned char key, int x, int y);
        void specialKeyboard(int key, int x, int y);
        void specialKeyboardUp(int key, int x, int y);
        void mouseMotion(int x, int y);
        void mouseKey(int button, int state, int x, int y);
        void mouseWheel(int wheel, int direction, int x, int y);
        void mouseEntry(int state);
        void findNodesForFreeing();


    };
}

#endif