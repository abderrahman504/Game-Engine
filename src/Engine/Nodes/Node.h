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
        Node* parent = nullptr;
        std::vector<Node*> children = std::vector<Node*>();
        SceneHead* sceneHead;
        bool queuedForDeletion = false;

        public:
        Node();
        ~Node();
        Node& Parent();
        Node& getChildAt(int index);
        std::vector<Node*> getChildren();
        void addChild(Node* child);
        void removeChild(Node* child);
        void removeChildAt(int index);
        std::string getName();
        std::string setName(std::string name);
        SceneHead& getSceneHead();
        //Queues this node and its children for deletion at the end of the current frame
        void queueFree();

        private:
        //The propegate functions are initially called on the root node by SceneHead and eventually all tree nodes are called.

        //Calls children's propegateReady() then this->ready()
        void propegateReady(SceneHead* sceneHead);
        //Calls children's propegateIdle() then this->idle()
        void propegateIdle(double deltaTime); 
        
        protected:
        //Calls children's propegateDraw() then this->draw()
        virtual void ready();
        virtual void idle(double deltaTime);

    };

}}

#endif