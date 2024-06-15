#include "InputServer.h"
#include <unordered_map>
#include <GL/glew.h>
#include <GL/freeglut.h>

using namespace Engine;
using namespace Engine::DataTypes;

enum {PRESSED, RELEASED, HELD, NONE};

typedef int KeyState;
static Vector2 mouse_pos, prev_mouse_pos;
static bool mouse_just_entered;
static std::unordered_map<int, KeyState> key_map = std::unordered_map<int, KeyState>();
static Vector2 win_size;
static bool just_warped_mouse;

void InputServer::init()
{
    just_warped_mouse = false;
    key_map.clear();
    unsigned char c = 0;
    do{
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
    mouse_just_entered = false;
}

void InputServer::keyboardInput(unsigned char key, bool down, int x, int y){
    key_map[key] = down ? PRESSED : RELEASED;
}
void InputServer::specialInput(int key, bool down, int x, int y){
    //implement later
}
void InputServer::mouseMotion(int x, int y){
    if(mouse_just_entered)
    {
        mouse_just_entered = false;
        prev_mouse_pos = Vector2(x, y);
    }
    if(just_warped_mouse)
    {
        just_warped_mouse = false;
        return;
    }
    mouse_pos = Vector2(x, y);
}
void InputServer::mouseKey(int button, int state, int x, int y){
    switch(button)
    {
        case GLUT_LEFT_BUTTON: 
            key_map[MOUSE_LEFT] = state == GLUT_DOWN ? PRESSED : RELEASED;
            break;
        case GLUT_RIGHT_BUTTON:
            key_map[MOUSE_RIGHT] = state == GLUT_DOWN ? PRESSED : RELEASED;
            break; 
        case GLUT_MIDDLE_BUTTON:
            key_map[MOUSE_MIDDLE] = state == GLUT_DOWN ? PRESSED : RELEASED;
            break;
    }
}
void InputServer::mouseWheel(int wheel, int direction, int x, int y){
    if (direction > 0)
        key_map[MOUSE_SCROLL_UP] = RELEASED;
    else
        key_map[MOUSE_SCROLL_DOWN] = RELEASED;
}
void InputServer::mouseEntry(int state){
    mouse_just_entered = state == GLUT_ENTERED;
    if(state == GLUT_LEFT && cursor_frozen)
    {
        Vector2 mouse_offset = getMouseMotion();
        prev_mouse_pos = Vector2(win_size.x / 2, win_size.y / 2);
        mouse_pos = prev_mouse_pos + mouse_offset;
        glutWarpPointer(mouse_pos.x, mouse_pos.y);
        just_warped_mouse = true;
    }
}

void InputServer::onIdle(Vector2 window_size)
{
    win_size = window_size;
    //place mouse at center of window if cursor_frozen is true
    // if(cursor_frozen)
    // {
    //     Vector2 mouse_offset = getMouseMotion();
    //     glutWarpPointer(window_size.x / 2, window_size.y / 2);
    //     just_warped_mouse = true;
    //     mouse_pos = Vector2(window_size.x / 2, window_size.y / 2);
    // }
    prev_mouse_pos = mouse_pos;
    //Iterate on key_map
    for(auto it = key_map.begin(); it != key_map.end(); it++)
    {
        if(it->second == PRESSED) it->second = HELD;
        else if(it->second == RELEASED) it->second = NONE;
    }
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
    // printf("Mouse motion: <%f, %f>\n", mouse_pos.x - prev_mouse_pos.x, mouse_pos.y - prev_mouse_pos.y);
    return mouse_pos - prev_mouse_pos;
}

bool InputServer::isMousePressed(int button){
    switch(button)
    {
        case MOUSE_LEFT: return key_map[MOUSE_LEFT] == HELD;
        case MOUSE_RIGHT: return key_map[MOUSE_RIGHT] == HELD;
        case MOUSE_MIDDLE: return key_map[MOUSE_MIDDLE] == HELD;
        case MOUSE_SCROLL_UP: return key_map[MOUSE_SCROLL_UP] == RELEASED;
        case MOUSE_SCROLL_DOWN: return key_map[MOUSE_SCROLL_DOWN] == RELEASED;
    }
    return false;
}