#ifndef NODE_GUARD
#define NODE_GUARD
#include <vector>
#include <string>

namespace Engine{
    class SceneHead;
namespace Nodes{
    
    class Node{
        friend class Engine::SceneHead;

        std::string name;
        Node* parent;
        std::vector<Node*> children;
        SceneHead* sceneHead;

        public:
        Node& getParent();
        void setParent(Node* parent);
        Node& getChildAt(int index);
        std::vector<Node*> getChildren();
        void addChild(Node* child);
        void removeChild(Node* child);
        void removeChildAt(int index);
        std::string getName();
        std::string setName(std::string name);
        SceneHead& getSceneHead();
        //Remove this node and all children from the scene tree
        void queueFree();

        private:
        //The propegate functions are initially called on the root node by SceneHead and eventually all tree nodes are called.

        //Calls children's propegateReady() then this->ready()
        void propegateReady(SceneHead* sceneHead);
        //Calls children's propegateIdle() then this->idle()
        void propegateIdle(double deltaTime); 
        //Calls children's propegateDraw() then this->draw()
        void propegateDraw(); 
        
        protected:
        virtual void ready();
        virtual void idle(double deltaTime);
        virtual void draw();

    };

}}

#endif