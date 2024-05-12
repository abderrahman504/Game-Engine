#include "Planet.h"


using namespace Game;

Planet::Planet(float planetRadius, int resolution) : SphereMesh(planetRadius, resolution){}

void Planet::idle(double deltaTime)
{
    //Update planet angle every frame
    //multiply orbit speed by deltaTime to get the change in orbit angle this frame
    //Increase the orbit angle and calculate the position based on the angle and radius
    //Assume the planet orbits the origin point, which is where the sun is.
}