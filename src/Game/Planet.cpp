#include "Planet.h"
#include "iostream"
#include <cmath>
using namespace Game;

Planet::Planet(float planetRadius, int resolution) : SphereMesh(planetRadius, resolution){}

void Planet::idle(double deltaTime)
{
    std::cout<<deltaTime;
    //Update planet angle every frame
    //multiply orbit speed by deltaTime to get the change in orbit angle this frame
    orbitAngle+=orbitSpeed * deltaTime;
    position.x=orbitRadius * cos(orbitAngle);
    position.y=orbitRadius * sin(orbitAngle);

    //Increase the orbit angle and calculate the position based on the angle and radius
    //Assume the planet orbits the origin point, which is where the sun is.

}