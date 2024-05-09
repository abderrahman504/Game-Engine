#include "InputServer.h"
#include "DataTypes.h"
#include <unordered_map>

using namespace Engine;
using namespace Engine::DataTypes;

Vector2 mouse_pos, prev_mouse_pos;
std::unordered_map<int, KeyState> key_map = std::unordered_map<int, KeyState>();

struct KeyState{
    bool pressed;
    bool prev_pressed;
};

void InputServer::init()
{
    key_map.clear();
    unsigned char c = 0;
    do
    {
        key_map[c] = KeyState{false, false};
    } while(c++ != 255);

    key_map[MOUSE_LEFT] = KeyState{false, false};
    key_map[MOUSE_RIGHT] = KeyState{false, false};
    key_map[MOUSE_MIDDLE] = KeyState{false, false};
    key_map[MOUSE_SCROLL_UP] = KeyState{false, false};
    key_map[MOUSE_SCROLL_DOWN] = KeyState{false, false};
    key_map[ARROW_LEFT] = KeyState{false, false};
    key_map[ARROW_RIGHT] = KeyState{false, false};
    key_map[ARROW_UP] = KeyState{false, false};
    key_map[ARROW_DOWN] = KeyState{false, false};
    mouse_pos = Vector2::ZERO;
    prev_mouse_pos = Vector2::ZERO;
}

void InputServer::keyboardInput(unsigned char key, int x, int y){
    key_map[key].pressed = true;
}
void InputServer::specialInput(int key, int x, int y){
    //implement later
}
void InputServer::mouseMotion(int x, int y){
    mouse_pos = Vector2(x, y);
}
void InputServer::mouseKey(int button, int state, int x, int y){
    //implement later
}

void InputServer::onIdle()
{
    prev_mouse_pos = mouse_pos;
    //Iterate on key_map
    for(auto it = key_map.begin(); it != key_map.end(); it++)
    {
        it->second.prev_pressed = it->second.pressed;
        it->second.pressed = false;
    }
}

bool InputServer::isKeyJustPressed(int key){
    return key_map[key].pressed && !key_map[key].prev_pressed;
}
bool InputServer::isKeyPressed(int key){
    return key_map[key].pressed;
}
bool InputServer::isKeyJustReleased(int key){
    return key_map[key].prev_pressed && !key_map[key].pressed;
}
Vector2 InputServer::getMousePosition(){
    return mouse_pos;
}
Vector2 InputServer::getMouseMotion(){
    return mouse_pos - prev_mouse_pos;
}