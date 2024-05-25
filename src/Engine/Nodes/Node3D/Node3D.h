#ifndef NODE3D_GUARD
#define NODE3D_GUARD
#include "../Node.h"
#include "../../DataTypes.h"

using namespace Engine::DataTypes;

namespace Engine{
namespace Nodes{
class Node3D : public Node
{
    
    public:
    Vector3 position = Vector3::ZERO;
    Quaternion orientation = Quaternion::IDENTITY;
    Vector3 scale = Vector3::ONE;
    Node3D();
    
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