#ifndef NODE3D_GUARD
#define NODE3D_GUARD
#include "../Node.h"
#include "../../DataTypes.h"

using namespace Engine::DataTypes;

namespace Engine{
namespace Nodes{
class Node3D : public Node
{
    protected:
    Vector3 position;
    Quaternion orientation;
    Vector3 scale;
    
    public:
    Node3D();
    Vector3 Position();
    void Position(Vector3 position);
    Quaternion Orientation();
    void Orientation(Quaternion quaterion);
    Vector3 Scale();
    void Scale(Vector3 scale);

    //Gets the up direction of this node3d relative to its parent.
    Vector3 getUp();
    //Gets the forward direction of this node3d relative to its parent.
    Vector3 getForward();
    //Orients the node3d to look at position ```point``` with its up direction facing ```up```.
    void lookAt(Vector3 point, Vector3 up);
    //Orients the node3d to look towards ```direction``` with its up direction facing ```up```.
    void lookTowards(Vector3 direction, Vector3 up);
    //Rotates the node3d around ```axis``` by ```angle``` radians.
    void rotateAround(Vector3 axis, float angleRad);
};

}}

#endif