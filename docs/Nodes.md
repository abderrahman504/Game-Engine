This file aimes to provide a useful description of every node class in the engine.


### Node
This is most basic and all other node classes inherit from it. All this class has is methods for adding and removing it from a tree and variables for storing its children and parent. All nodes have a reference to the SceneHead.

### Node3D : Node
The base node class for making a 3D object. All 3D classes inherit this class. Stores position, rotation, and scale information to be used when drawing this object and its children.

### Mesh3D : Node3D
Stores vertex and material information about the mesh to be drawn which is used by the SceneHead to draw the mesh. 

### Light3D : Node3D
Stores lighting information to be used the SceneHead to light the scene.

### PhysicsBody3D : Node3D
The most basic class that can be involved in ```PhysicsServer``` calculations. Needs to have a ```CollisionBox3D``` as a child to work properly. Used for collision detection but not for movement. Has variables for collision layer and collision mask.

### KenimaticBody3D : PhysicsBody3D
Stores a velocity variable to be used by the ```PhysicsServer``` to move it. Can collide with other ```PhyiscsBody3D``` objects and reacts appropriately.

### CollisionBox3D : Node3D
A simple collider in the shape of a box. Can specify width, length, and height. Cannot rotate for now to make collision detection simple. 

### Camera3D : Node3D
A class for specifying the position and orientation of the camera in the world. ```SceneHead``` will look for an instance of this class in the tree to know where to place the viewing area. If no cameras exist in the scene then the viewing area will be default to ```glFrustem(-100, 100, -100, 100, 20, 500)``` and ```gluLookAt(0,0,0, 0,0,-1, 0,1,0)``` - effectively placing the camera at the origin and looking to the negative z-axis.

