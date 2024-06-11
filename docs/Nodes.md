This file aimes to provide a useful description of every node class in the engine.


### `Node`
This is most basic and all other node classes inherit from it. All this class has is methods for adding and removing it from a tree and variables for storing its children and parent. All nodes have a reference to the SceneHead.

### `Node3D` : `Node`
The base node class for making a 3D object. All 3D classes inherit this class. Stores position, rotation, and scale information to be used when drawing this object and its children.

### `Mesh3D` : `Node3D`
Stores vertex and material information about the mesh to be drawn which is used by the SceneHead to draw the mesh. 

### `Light3D` : `Node3D`
Stores lighting information to be used the SceneHead to light the scene.

### `CollisionBody3D` : `Node3D`
The most basic class that can be involved in physics calculations. Needs to have a `Collider3D` as a child to work properly. Used for collision detection but not for movement.  
Has variables for collision layer and collision mask. collision layer and mask variables are bit flags used to set multiple layers and masks for a body. 

Two bodies can collide only if their colliders overlap __and__ one of  an object's masks is __*x*__ and one of the other object's layers __*x*__. 

By default every body is on layer 1 and mask 1. There are 16 supported collision layers.  

### `Collider3D` : `Node3D`
The base class for all 3D colliders. You can't actually use this class for a collider. Use one of its subclasses. 

### `SphereCollider` : `Collider3D`
A sphere shaped collider. You can use this as a child of a `CollisionBody3D`.

### `Camera3D` : `Node3D`
A class for specifying the position and orientation of the camera in the world. `SceneHead` will look for an instance of this class in the tree to know where to place the viewing area. If no cameras exist in the scene then the viewing area will be default to `glFrustem(-100, 100, -100, 100, 20, 500)` and `gluLookAt(0,0,0, 0,0,-1, 0,1,0)` - effectively placing the camera at the origin and looking to the negative z-axis.

