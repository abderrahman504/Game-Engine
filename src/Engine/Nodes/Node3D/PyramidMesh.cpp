#include "PyramidMesh.h"
#include <math.h>

using namespace Engine::Nodes;

void buildPyramidVertices(float height, float base_width, float base_length, float **vertices, unsigned int ***indeces, int **countIndeces, int *countPrimitives);

PyramidMesh::PyramidMesh(float height, float base_width, float base_length)
{
    this->height = height;
    this->base_width= base_width;
    this->base_length = base_length;
    buildPyramidVertices(height, base_width, base_length, &vertices, &indeces, &countIndeces, &countPrimitives);
    setName("PyramidMesh");
}

float PyramidMesh::Height(){return height;}
float PyramidMesh::BaseWidth(){return base_width;}
float PyramidMesh::BaseLength(){return base_length;}


void buildPyramidVertices(float height, float base_width, float base_length, float **vertices, unsigned int ***indeces, int **countIndeces, int *countPrimitives)
{
    *countPrimitives = 5; //A four sided pyramid is composed of 4 triangular faces and a square base
    *countIndeces = new int[5];
    *indeces = new unsigned int*[5];
    //Base indeces
    (*indeces)[0] = new unsigned int(4);
    (*countIndeces)[0] = 4;
    //Face indeces
    for (int i =  1; i < 5; i++){
        (*indeces)[i] = new unsigned int[3];
        (*countIndeces)[i] = 3;
    }
    *vertices = new float[5 * 3];
    
    //Setting verteces
    Vector3 corner = Vector3(0.5 * base_width, -1 * height / 5, 0.5 * base_length);
    //Top of pyramid
    (*vertices)[0] = 0;
    (*vertices)[1] = height + corner.y;
    (*vertices)[2] = 0;

    //Base of pyramid
    (*vertices)[1*3 + 0] = corner.x;
    (*vertices)[1*3 + 1] = corner.y;
    (*vertices)[1*3 + 2] = corner.z;

    (*vertices)[2*3 + 0] = -1*corner.x;
    (*vertices)[2*3 + 1] = corner.y;
    (*vertices)[2*3 + 2] = corner.z;

    (*vertices)[3*3 + 0] = -1*corner.x;
    (*vertices)[3*3 + 1] = corner.y;
    (*vertices)[3*3 + 2] = -1*corner.z;

    (*vertices)[4*3 + 0] = corner.x;
    (*vertices)[4*3 + 1] = corner.y;
    (*vertices)[4*3 + 2] = -1*corner.z;

    //setting indeces
    //Base is 2 triangle strips
    (*indeces)[0][0] = 1;
    (*indeces)[0][1] = 2;
    (*indeces)[0][2] = 4;
    (*indeces)[0][3] = 4;

    //Faces
    (*indeces)[1][0] = 0;
    (*indeces)[1][1] = 1;
    (*indeces)[1][2] = 2;

    (*indeces)[2][0] = 0;
    (*indeces)[2][1] = 2;
    (*indeces)[2][2] = 3;

    (*indeces)[3][0] = 0;
    (*indeces)[3][1] = 3;
    (*indeces)[3][2] = 4;

    (*indeces)[4][0] = 0;
    (*indeces)[4][1] = 4;
    (*indeces)[4][2] = 1;

}