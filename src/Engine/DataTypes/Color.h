#ifndef COLOR_GUARD
#define COLOR_GUARD

namespace Engine{
namespace DataTypes{

    struct Color
    {
        static const Color WHITE, BLACK, RED, GREEN, BLUE;
        float r,g,b,a;

        Color();
        // Color(float r, float g, float b, float a);
        Color(int r, int g, int b, int a);
        Color(int rgb_hexa);

        static Color fromRGBFloat(float r, float g, float b, float a);
        static Color fromRGBInt(int r, int g, int b, int a);
        static Color fromRGBHexa(int hexa);

        void setRGB(float r, float g, float b, float a);
        void setRGB(int r, int g, int b, int a);
        void setRGB(int hexa);

        // void setHSV(float h, float s, float v, float a);
        // void setHSV(int h, int s, int v, int a);
        // void setHSV(int hexa);


    };

}}

#endif