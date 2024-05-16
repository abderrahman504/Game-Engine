#include "Node3D.h"
#include "../../Display.h"
#include "../../DataTypes.h"

using namespace Engine::DataTypes;

namespace Engine{
namespace Nodes{

    class Camera3D : public Node3D
    {
        public:
        int viewport = VIEWPORT_1;
        Vector2 viewportPosition = Vector2::ZERO; //The position of the viewport in the game window. A value between 0 and 1.
        Vector2 viewportSize = Vector2::ONE; // The size of the viewport as a fraction of the window size.
        bool active = true;
        int projection = PERSPECTIVE;

        private:
        Vector2 aspect = Vector2(16,9);
        float fov_or_width = 80;
        float width;
        float height;
        float near = 1;
        float far = 3000;

        public:
        Camera3D();
        //Sets the aspect ratio of the camera display face. Will change the vertical axis length to satisfy `aspect`.
        void setAspect(Vector2 aspect);
        //Sets the horizontal field of view of the camera. Only applicable in Perspective projection
        void setFOV(float fov);
        //Sets the width of the camera. Only applicable in Orthogonal projection.
        void setWidth(float w);
        //Sets the near value of the camera. Will maintain aspect and fov.
        void setNear(float near);
        //Sets the far value of the camera
        void setFar(float far);

        float getFOV();
        Vector2 getAspect();
        float getWidth();
        float getHeight();
        float getNear();
        float getFar();


        private:
        void updateDims();

    };
}}
