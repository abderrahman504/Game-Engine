#include "DiskMesh3D.h"
#include <math.h>

using namespace Engine::Nodes;

void buildVertices(float r1, float r2, float thickness, int resolution, float **vertices, unsigned int ***indeces, int **countIndeces, int *countPrimitives);

DiskMesh3D::DiskMesh3D(float r1, float r2, float thickness, int resolution)
{
    this->r1 = r1;
    this->r2 = r2;
    this->thickness = thickness;
    buildVertices(r1, r2, thickness, resolution, &vertices, &indeces, &countIndeces, &countPrimitives);
    setName("DiskMesh3D");
}

float DiskMesh3D::InnerRadius(){return r1;}
float DiskMesh3D::OuterRadius(){return r2;}
float DiskMesh3D::Thickness(){return thickness;}


void buildVertices(float r1, float r2, float thickness, int resolution, float **vertices, unsigned int ***indeces, int **countIndeces, int *countPrimitives)
{
    *countPrimitives = 4; //The top and bottom sides are 2 triangle strips. The inner and outer walls of the disk are 2 triangle strips.
    *countIndeces = new int[4];
    *indeces = new unsigned int*[4];
    //Top and Bottom side indeces
    (*indeces)[0] = new unsigned int[2* (resolution+1)];
    (*countIndeces)[0] = 2* (resolution+1);
    (*indeces)[1] = new unsigned int[2* (resolution+1)];
    (*countIndeces)[1] = 2* (resolution+1);

    //Wall indeces
    (*indeces)[2] = new unsigned int[2* (resolution+1)];
    (*countIndeces)[2] = 2* (resolution+1);
    (*indeces)[3] = new unsigned int[2* (resolution+1)];
    (*countIndeces)[3] = 2* (resolution+1);

    //Verteces allocation: each side has 2*(resolution+1) verteces. There are 2 sides
    *vertices = new float[4 * (resolution+1) * 3];
    
    //Setting verteces
    //[0 : 2*resolution-1] are bottom side verteces
    //[2*resolution : 4*resolution-1] are top side verteces]
    for(int i=0; i < resolution; i++)
    {
        float angle = 2 * PI * i / resolution;
        //bottom side
        (*vertices)[2*i*3 + 0] = r1 * cos(angle);
        (*vertices)[2*i*3 + 1] = -thickness / 2;
        (*vertices)[2*i*3 + 2] = r1 * sin(angle);

        (*vertices)[(2*i+1)*3 + 0] = r2 * cos(angle);
        (*vertices)[(2*i+1)*3 + 1] = -thickness / 2;
        (*vertices)[(2*i+1)*3 + 2] = r2 * sin(angle);

        //top side
        (*vertices)[2*(resolution+i)*3 + 0] = r1 * cos(angle);
        (*vertices)[2*(resolution+i)*3 + 1] = thickness / 2;
        (*vertices)[2*(resolution+i)*3 + 2] = r1 * sin(angle);

        (*vertices)[(2*(resolution+i)+1)*3 + 0] = r2 * cos(angle);
        (*vertices)[(2*(resolution+i)+1)*3 + 1] = thickness / 2;
        (*vertices)[(2*(resolution+i)+1)*3 + 2] = r2 * sin(angle);
    }


    //setting indeces
    for(int i=0; i <= resolution; i++)
    {
        int i_mod = i % resolution;
        //Top side
        (*indeces)[0][2*i] = 2*i_mod;
        (*indeces)[0][2*i + 1] = 2*i_mod + 1;

        //Bottom side
        (*indeces)[1][2*i] = 2*resolution + 2*i_mod;
        (*indeces)[1][2*i + 1] = 2*resolution + 2*i_mod + 1;

        //Inner Wall
        (*indeces)[2][2*i] = 2 * i_mod;
        (*indeces)[2][2*i + 1] = 2*resolution +  2*i_mod;

        //Outer Wall
        (*indeces)[3][2*i] = 2 * i_mod + 1;
        (*indeces)[3][2*i + 1] = 2*resolution + 2*i_mod + 1;
    }

}