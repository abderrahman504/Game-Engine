#include "Mesh3D.h"
using namespace Engine::Nodes;

Mesh3D::Mesh3D(){
    setName("Mesh3D");
}
Mesh3D::~Mesh3D(){
    if(vertices != nullptr){
        for(int i = 0; i < countPrimatives; i++){
            delete[] vertices;
            delete[] indeces[i];
        }
        delete[] vertices;
        delete[] indeces;
        delete[] countIndeces;
    }
}
float* Mesh3D::Vertices(){return vertices;}
unsigned int** Mesh3D::Indeces(){return indeces;}
int* Mesh3D::CountIndeces(){return countIndeces;}
int Mesh3D::CountPrimatives(){return countPrimatives;}