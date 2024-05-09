#ifndef INPUT_SERVER_GUARD
#define INPUT_SERVER_GUARD
#include <GL/freeglut.h>
#include <GL/glew.h>


enum {MOUSE_LEFT = 256, MOUSE_RIGHT, MOUSE_MIDDLE, MOUSE_SCROLL_UP, MOUSE_SCROLL_DOWN, ARROW_LEFT, ARROW_RIGHT, ARROW_UP, ARROW_DOWN};

namespace Engine{
    class SceneHead;
    class InputServer
    {
        friend class SceneHead;
        private:
        void keyboardInput(unsigned char key, int x, int y);
        void specialInput(int key, int x, int y);
        void mouseMotion(int x, int y);
        void mouseKey(int button, int state, int x, int y);
        void onIdle();
        void init();

        public:
        bool isKeyJustPressed(int key);
        bool isKeyPressed(int key);
        bool isKeyJustReleased(int key);
        Vector2 getMousePosition();
        Vector2 getMouseMotion();
    };
}

#endif