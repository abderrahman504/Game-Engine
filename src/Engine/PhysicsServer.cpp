#include "PhysicsServer.h"
#include "Nodes/Node3D/CollisionBody3D.h"
#include "Nodes/Node3D/Collider3D.h"
#include "Nodes/Node3D/SphereCollider.h"
#include "Nodes/Node.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>

#define MAX_LAYERS 16

using namespace std;
using namespace Engine;
using namespace Engine::Nodes;

struct BodyGizmo{
    CollisionBody3D* body;
    unordered_set<BodyGizmo*> collided_with = unordered_set<BodyGizmo*>();
    vector<Collider3D*> colliders = vector<Collider3D*>();
    vector<Engine::CollisionInfo> collisions = vector<Engine::CollisionInfo>();
};


vector<BodyGizmo*> bodies = vector<BodyGizmo*>();
unordered_map<int, vector<BodyGizmo*>*> layer_map = unordered_map<int, vector<BodyGizmo*>*>();
unordered_map<int, vector<BodyGizmo*>*> mask_map = unordered_map<int, vector<BodyGizmo*>*>();

//forward declared funcs
void clearCaches();
void findBodies(Node* root);
void findCollisions();
bool checkCollisionBetween(BodyGizmo* a, BodyGizmo* b);
bool checkSphereCollision(SphereCollider* a, SphereCollider* b, CollisionInfo* a_info, CollisionInfo* b_info);
void resolveCollisions(double delta);


void Engine::PhysicsServer::update(double delta, Nodes::Node* root)
{
    //Clear bodies, layer_map, mask_map since last physics update
    clearCaches();
    //Find all bodies in the scene for this frame
    findBodies(root);
    //Check for collisions between each pair of bodies
    findCollisions();
    //Resolve each collision
    resolveCollisions(delta);
}

void clearCaches()
{
    if(layer_map.size() == 0)
        for(int i=0; i < MAX_LAYERS; i++) layer_map[i] = new vector<BodyGizmo*>();
    else 
        for(auto itr = layer_map.begin(); itr != layer_map.end(); itr++) itr->second->clear();
    
    if(mask_map.size() == 0)
        for(int i=0; i < MAX_LAYERS; i++) mask_map[i] = new vector<BodyGizmo*>();
    else
        for(auto itr = mask_map.begin(); itr != mask_map.end(); itr++) itr->second->clear();
    
    for(int i = 0; i < bodies.size(); i++) delete bodies[i];
    bodies.clear();
}

void findBodies(Node* root)
{
    stack<Node*> stk = stack<Node*>();
    stk.push(root);
    while(!stk.empty())
    {
        Node* node = stk.top();
        stk.pop();
        CollisionBody3D* body = dynamic_cast<CollisionBody3D*>(node);
        if(body != nullptr)
        {
            BodyGizmo* gizmo = new BodyGizmo();
            gizmo->body = body;
            //Find body colliders
            vector<Node*> children = body->getChildren();
            for(int i=0; i < children.size(); i++){
                Collider3D* collider = dynamic_cast<Collider3D*>(children[i]);
                if(collider != nullptr) gizmo->colliders.push_back(collider);
            }
            //Add body to layer and mask hashmaps and list of bodies
            bodies.push_back(gizmo);
            int layer = body->collisionLayer;
            int mask = body->collisionMask;
            int bit_count = 0;
            while(layer != 0 || mask != 0)
            {
                if(layer & 1){//body exists at this layer
                    layer_map[bit_count]->push_back(gizmo);
                }
                if(mask & 1){//body scans for this layer
                    mask_map[bit_count]->push_back(gizmo);
                }
                layer = layer >> 1;
                mask = mask >> 1;
                bit_count++;
            }
        }
        vector<Node*> children = node->getChildren();
        for(int i= 0; i < children.size(); i++) stk.push(children[i]);
    }
}

void findCollisions()
{
    //For each mask
    for(int layer_num=0; layer_num < MAX_LAYERS; layer_num++)
    {
        //For each body in this mask
        for(int i = 0; i < mask_map[layer_num]->size(); i++)
        {
            BodyGizmo* gizmo = (*mask_map[layer_num])[i];
            //For each body in corresponding layer
            for(int j=0; j < layer_map[layer_num]->size(); j++)
            {
                BodyGizmo* other = (*layer_map[layer_num])[j];
                //Don't check collision between a body and itself.
                if(other == gizmo) continue; 
                //Check if collision between these two bodies was already detected
                bool already_collided = gizmo->collided_with.find(other) != gizmo->collided_with.end();
                if(already_collided) continue;
                //Otherwise check for collision between the bodies
                bool collided = checkCollisionBetween(gizmo, other);
                if(collided)
                {
                    gizmo->collided_with.insert(other);
                    other->collided_with.insert(gizmo);
                }
            }
        }
    }
}

void resolveCollisions(double delta)
{
    //For each body in scene
    for(auto i = bodies.begin(); i != bodies.end(); i++)
    {
        BodyGizmo* gizmo = *i;
        //For each detected collision
        for(auto j = gizmo->collisions.begin(); j != gizmo->collisions.end(); j++)
        {
            CollisionInfo info = *j;
            gizmo->body->onCollision((CollisionBody3D*)info.other_collider->Parent(), info);
        }
    }
}


bool checkCollisionBetween(BodyGizmo* a, BodyGizmo* b)
{
    bool collided = false;
    for(auto itr = a->colliders.begin(); itr != a->colliders.end(); itr++)
    {
        Collider3D* collider1 = *itr;
        bool is_sphere_collider = dynamic_cast<SphereCollider*>(collider1) != nullptr;
        for(auto itr2 = b->colliders.begin(); itr2 != b->colliders.end(); itr2++)
        {
            CollisionInfo a_info, b_info;   
            Collider3D* collider2 = *itr2;
            bool is_sphere_collider2 = dynamic_cast<SphereCollider*>(collider2) != nullptr;

            //Check type of colliders and call appropriate collision checking function
            bool res = false;
            if(is_sphere_collider2 && is_sphere_collider)
                res = checkSphereCollision((SphereCollider*)collider1, (SphereCollider*)collider2, &a_info, &b_info);
            //Add other if statements when new colliders are added to the engine

            if(res){
                collided = true;
                a->collisions.push_back(a_info);
                b->collisions.push_back(b_info);
            }
        }
    }
    return collided;
}

bool checkSphereCollision(SphereCollider* a, SphereCollider* b, CollisionInfo* a_info, CollisionInfo* b_info){
    double distance = (a->GlobalPosition() - b->GlobalPosition()).length();
    if(a->radius + b->radius > distance){//Collided
        Vector3 global_collision_pos = (a->GlobalPosition() + b->GlobalPosition()) / 2;
        a_info->global_collision_point = b_info->global_collision_point = global_collision_pos;
        a_info->my_collider = b_info->other_collider = a;
        b_info->my_collider = a_info->other_collider = b;
        //If there is any other collision info we want we should calculate it here.
        return true;
    }
    return false;
}



