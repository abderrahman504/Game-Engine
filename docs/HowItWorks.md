# What Happens Inside the Engine?
All you need for the engine to start your game is call ```initEngine()``` and ```setMainScene()``` and it will immediately start. ```initEngine()``` is very short and not much happens there so we'll look at ```setMainScene()```.  

## `setMainScene()`
```mermaid
--- 
title: setMainScene() 
---
graph LR
    init["SceneHead.Init()"] --> start["SceneHead.Start()"]
```
Here we call ```SceneHead.Init()``` and pass a pointer to the input and physics servers. This method calls all the ```glut*Func()``` functions to connect the scenehead to the callback functions generated by OpenGL. It also creates a ```TreeDrawer```, enables depth testing and sets the background color.  
```mermaid
--- 
title: SceneHead.Start() 
---
graph LR
    build["SceneHead.constructTree()"] --> ready["SceneHead.OnTreeReady()"] --> loop["Enter game loop"]
```
Next we call `SceneHead.Start()` which calls `constructTree()` (which you hopefully overrided in your custom `SceneHead` class), then `onTreeReady()` which recursively calls `ready()` on every node in the scene tree from leaves to the root. Lastly we call `glutMainLoop()` which enters the game loop.

## `SceneHead.idle()`
```mermaid
--- 
title: SceneHead.idle() 
---
graph LR
    delta["Measure deltaTime"] --> idle["Call Node.idle()"] --> free["Satisfy queueFree() requests"] --> draw["TreeDrawer.draw()"]
```
Here is where most of the complex work happens so strap in.  
First we calculate the time since the last idle was called (how much time has passed since the last frame) then call `idle()` recursively on all nodes in the tree.  
Next we search the tree for any nodes that requested to be freed and we delete them and their children from the scene.  
Next we call `glutPostRedisplay()` which invokes `SceneHead.draw()`. Drawing the tree is delegated to `TreeDrawer.drawScene()`

## `TreeDrawer.drawScene()`
Scene drawing is still a work in progress. Right now it iterates through all the nodes in the tree and draws them, ignoring mesh material, lights, and cameras.  
Here is how it **Should** work:
First thing that must be done is determine where the camera(s) and viewports should be placed, so the drawer searches the tree for all active camera objects.  
For each active camera it determines its global position, orientation, and scale in the world by applying The 3D transformations of its parent nodes on 3 vectors: 
- cameraPos: Stores the global position of the camera. Starts at Vector3.ZERO.
- cameraForward: Stores the forward direction of the camera. Starts at Vector3.FORWARD.
- cameraUp: Stores the up direction of the camera. Starts at Vector3.UP.

After these 3 vectors are calculated for a specific camera, `gluLookAt()` is called to position the camera in the world then `drawNode()` is called on the root of the tree which recursively draws all nodes in the tree, then `glLoadIdentity()` is called to reset the modelview matrix.    
This process is repeated for all active cameras, drawing to different viewports each time.