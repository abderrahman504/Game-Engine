#include "InputServer.h"
#include <unordered_map>

using namespace Engine;
using namespace Engine::DataTypes;

enum {PRESSED, RELEASED, HELD, NONE};

typedef int KeyState;
// struct KeyState{
//     bool pressed;
//     bool prev_pressed;
// };
Vector2 mouse_pos, prev_mouse_pos;
std::unordered_map<int, KeyState> key_map = std::unordered_map<int, KeyState>();


void InputServer::init()
{
    key_map.clear();
    unsigned char c = 0;
    do
    {
        key_map[c] = NONE;
    } while(c++ != 255);

    key_map[MOUSE_LEFT] = NONE;
    key_map[MOUSE_RIGHT] = NONE;
    key_map[MOUSE_MIDDLE] = NONE;
    key_map[MOUSE_SCROLL_UP] = NONE;
    key_map[MOUSE_SCROLL_DOWN] = NONE;
    key_map[ARROW_LEFT] = NONE;
    key_map[ARROW_RIGHT] = NONE;
    key_map[ARROW_UP] = NONE;
    key_map[ARROW_DOWN] = NONE;
    mouse_pos = Vector2::ZERO;
    prev_mouse_pos = Vector2::ZERO;
}

void InputServer::keyboardInput(unsigned char key, bool down, int x, int y){
    mouse_pos = Vector2(x,y);
    key_map[key] = down ? PRESSED : RELEASED;
}
void InputServer::specialInput(int key, bool down, int x, int y){
    mouse_pos = Vector2(x,y);
    //implement later
}
void InputServer::mouseMotion(int x, int y){
    mouse_pos = Vector2(x, y);
}
void InputServer::mouseKey(int button, int state, int x, int y){
    mouse_pos = Vector2(x,y);
    //implement later
}
void InputServer::mouseWheel(int wheel, int direction, int x, int y){
    mouse_pos = Vector2(x,y);
    //implement later
}

void InputServer::onIdle()
{
    prev_mouse_pos = mouse_pos;
    //Iterate on key_map
    for(auto it = key_map.begin(); it != key_map.end(); it++)
    {
        KeyState state = it->second;
        if(state == PRESSED) it->second = HELD;
        else if(state == RELEASED) it->second = NONE;
    }
    // for(auto it = key_map.begin(); it != key_map.end(); it++)
    // {
    //     it->second.prev_pressed = it->second.pressed;
    //     it->second.pressed = false;
    // }
}

bool InputServer::isKeyJustPressed(int key){
    return key_map[key] == PRESSED;
}
bool InputServer::isKeyPressed(int key){
    return key_map[key] == HELD;
}
bool InputServer::isKeyJustReleased(int key){
    return key_map[key] == RELEASED;
}
Vector2 InputServer::getMousePosition(){
    return mouse_pos;
}
Vector2 InputServer::getMouseMotion(){
    return mouse_pos - prev_mouse_pos;
}