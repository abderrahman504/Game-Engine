# Game-Engine
A game making framework made in C++ with OpenGL and includes a 3D space fighting game.

## Check the following .MD files in docs/
- **HowToRun.md** for help on how to compile and run the project.
- **HowToContribute.md** for help on how to add new files to the engine code.
- **HowToUseEngine.md** for help on how to use the engine classes to make a game. 


## Engine Overview
To start the engine you need to call ```initEngine()``` from Engine.h. This function creates engine singletons like ```InputServer``` and ```PhysicsServer```.

Next you need to call ```setMainScene()``` with a pointer to a ```SceneHead``` object that represents your game. This will start the scene.

The base ```SceneHead``` is responsible for managing all nodes in the scene tree starting from ```scene_root```. Once every frame it goes through all nodes in the tree and draws and calls their idle and input functions.


