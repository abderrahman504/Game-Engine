#include "../Engine.h"
#include <GL/glew.h>
#include <GL/freeglut.h>

namespace Engine{
    static bool engine_started = false;



    void initEngine(int argc, char** argv)
    {
        engine_started = true;
        glutInit(&argc, argv);

        glutInitContextVersion(4, 3);
        glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
        glutInitWindowSize(1280, 720);
        glutInitWindowPosition(100, 50);
        glutCreateWindow("Game Engine");

        glewExperimental = GL_TRUE;
        glewInit();


        // glutMainLoop();
    }

    void setMainScene(SceneHead &sceneHead)
    {
        //implement later
    }
}