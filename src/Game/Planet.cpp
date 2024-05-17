#include "Planet.h"
#include "iostream"
#include <cmath>
using namespace Game;

Planet::Planet(float planetRadius, int resolution) : SphereMesh(planetRadius, resolution){}

void Planet::idle(double deltaTime)
{

    //Update planet angle every frame
    //multiply orbit speed by deltaTime to get the change in orbit angle this frame
   orbitAngle+=orbitSpeed * deltaTime;
   position.x=orbitRadius * cos(orbitAngle);
   position.z=orbitRadius * sin(orbitAngle);
   position.y=0;
}