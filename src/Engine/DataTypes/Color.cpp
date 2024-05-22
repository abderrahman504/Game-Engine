#include "Color.h"

using namespace Engine::DataTypes;


const Color Color::WHITE(255,255,255,255);
const Color Color::BLACK(0,0,0,255);
const Color Color::RED(255,0,0,255);
const Color Color::GREEN(0,255,0,255);
const Color Color::BLUE(0,0,255,255);


Color::Color(): r(0), g(0), b(0), a(1){}
Color::Color(float r, float g, float b, float a): r(r), g(g), b(b), a(a){}
Color::Color(int r, int g, int b, int a): r(r/255.0), g(g/255.0), b(b/255.0), a(a/255.0){}
Color::Color(int rgb_hexa){
    a = (rgb_hexa & 0x000000ff) / 255.0;
    b = ((rgb_hexa & 0x0000ff00) >> 8) / 255.0;
    g = ((rgb_hexa & 0x00ff0000) >> 16) / 255.0;
    r = ((rgb_hexa & 0xff000000) >> 24) / 255.0;
}

void Color::setRGB(float r, float g, float b, float a){
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}
void Color::setRGB(int r, int g, int b, int a){
    this->r = r/255.0;
    this->g = g/255.0;
    this->b = b/255.0;
    this->a = a/255.0;
}
void Color::setRGB(int hexa){
    a = (hexa & 0x000000ff) / 255.0;
    b = ((hexa & 0x0000ff00) >> 8) / 255.0;
    g = ((hexa & 0x00ff0000) >> 16) / 255.0;
    r = ((hexa & 0xff000000) >> 24) / 255.0;
}

// void Color::setHSV(float h, float s, float v, float a){

// }
// void Color::setHSV(int h, int s, int v, int a){
//     //C = v/100.0 * s/100.0
//     //X = C * (1-)
//     //m = 
// }
// void Color::setHSV(int hexa){

// }


