#include "SkyBox.h"

const GLfloat SkyBox::skyboxVertices[] = {
    // Coordinates scaled by 5000
    -5000.0f, -5000.0f,  5000.0f, // 7
     5000.0f, -5000.0f,  5000.0f, // 6
     5000.0f, -5000.0f, -5000.0f, // 5
    -5000.0f, -5000.0f, -5000.0f, // 4
    -5000.0f,  5000.0f,  5000.0f, // 3
     5000.0f,  5000.0f,  5000.0f, // 2
     5000.0f,  5000.0f, -5000.0f, // 1
    -5000.0f,  5000.0f, -5000.0f  // 0
};


const GLfloat SkyBox::TextureCoords[6][4][2] = {
    // Right face
    {
        {1.0f, 0.0f}, // Vertex 6
        {1.0f, 1.0f}, // Vertex 5
        {0.0f, 1.0f}, // Vertex 1
        {0.0f, 0.0f} // Vertex 2
    },
    
    // Left Face
    {   {0.0f, 0.0f}, // Vertex 0
        {1.0f, 0.0f}, // Vertex 3
        {1.0f, 1.0f}, // Vertex 7
        {0.0f, 1.0f} // Vertex 4
    },

    // Top face
    {       
        {0.0f, 1.0f}, // Vertex 4
        {1.0f, 1.0f}, // Vertex 5
        {1.0f, 0.0f}, // Vertex 6
        {0.0f, 0.0f} // Vertex 7
    }, 

    // Bottom face
    {
        {1.0f, 0.0f}, // Vertex 0
        {0.0f, 0.0f}, // Vertex 1
        {0.0f, 1.0f}, // Vertex 2
        {1.0f, 1.0f} // Vertex 3
    },
    
    // Back face
    {
        {1.0f, 0.0f}, // Vertex 0
        {0.0f, 0.0f}, // Vertex 1
        {0.0f, 1.0f}, // Vertex 5
        {1.0f, 1.0f}, // Vertex 4
    },
    
    // Front face
    {
        {0.0f, 0.0f}, // Vertex 2
        {1.0f, 0.0f}, // Vertex 3
        {1.0f, 1.0f}, // Vertex 7
        {0.0f, 1.0f}  // Vertex 6
    }
};


const GLuint SkyBox::skyboxIndices[] =  {
        // Right
        1, 2, 6,
        6, 5, 1,
        // Left
        0, 4, 7,
        7, 3, 0,
        // Top
        4, 5, 6,
        6, 7, 4,
        // Bottom
        0, 3, 2,
        2, 1, 0,
        // Back
        0, 1, 5,
        5, 4, 0,
        // Front
        3, 7, 6,
        6, 2, 3
};

SkyBox::SkyBox() {
    // Initialize faces with texture file paths
    faces = {
        "../resources/images/right.jpg",
        "../resources/images/left.jpg",
        "../resources/images/top.jpg",
        "../resources/images/bottom.jpg",
        "../resources/images/back.jpg",
        "../resources/images/front.jpg"
    };
    isdrawn = false;

}
