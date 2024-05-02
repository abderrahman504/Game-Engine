#include "Node.h"

using namespace Engine::Nodes;
using namespace Engine;

Node::Node(){
    parent = nullptr;
    sceneHead = nullptr;
    children = std::vector<Node*>();
    name = "Node";
}
Node::~Node(){
    for(int i = 0; i < children.size(); i++){
        delete children[i];
    }
}
Node& Node::Parent(){return *parent;}
Node& Node::getChildAt(int index){return *children[index];}
std::vector<Node*> Node::getChildren(){
    std::vector<Node*> childrenCopy;
    for(int i = 0; i < children.size(); i++){
        childrenCopy.push_back(children[i]);
    }
    return childrenCopy;
}
void Node::addChild(Node* child){
    for(int i = 0; i < children.size(); i++) if(children[i] == child) return;
    children.push_back(child);
}
void Node::removeChild(Node* child){
    for(int i = 0; i < children.size(); i++){
        if(children[i] == child){
            children.erase(children.begin() + i);
            return;
        }
    }
}
void Node::removeChildAt(int index){children.erase(children.begin() + index);}
std::string Node::getName(){
    std::string nameCopy = name;
    return nameCopy;
}
std::string Node::setName(std::string name){
    this->name = name;
    return name;
}
SceneHead& Node::getSceneHead(){
    return *sceneHead;
}
void Node::queueFree(){
    //implement later
}


void Node::propegateReady(SceneHead* sceneHead){
    for(int i = 0; i < children.size(); i++){
        children[i]->propegateReady(sceneHead);
    }
    ready();
}
void Node::propegateIdle(double deltaTime){
    for(int i = 0; i < children.size(); i++){
        children[i]->propegateIdle(deltaTime);
    }
    idle(deltaTime);
}
void Node::propegateDraw(){
    for(int i = 0; i < children.size(); i++){
        children[i]->propegateDraw();
    }
}


void Node::ready(){}
void Node::idle(double deltaTime){}