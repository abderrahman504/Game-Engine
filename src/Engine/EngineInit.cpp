#include "../Engine.h"
#include <GL/glew.h>
#include <GL/freeglut.h>

namespace Engine{
    static bool engine_started = false;
    PhysicsServer* physicsServer;
    InputServer* inputServer;


    void initEngine(int argc, char** argv)
    {
        engine_started = true;
        std::cout<<"Engine initialized"<<std::endl;
        glutInit(&argc, argv);

        glutInitContextVersion(4, 3);
        glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
        glutInitWindowSize(1120, 630);
        glutInitWindowPosition(100, 50);
        glutCreateWindow("Game Engine");

        glewExperimental = GL_TRUE;
        glewInit();

        physicsServer = new PhysicsServer();
        inputServer = new InputServer();
    }

    void setMainScene(SceneHead *sceneHead)
    {
        sceneHead->Init(inputServer, physicsServer);
        sceneHead->Start();
    }
}