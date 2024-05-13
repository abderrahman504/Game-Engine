#include "Transform3D.h"
#include "Quaternion.h"

using namespace Engine::DataTypes;

Transform3D identity();

const Transform3D Transform3D::IDENTITY = identity();
const Transform3D Transform3D::ZERO = Transform3D();

Transform3D::Transform3D(){
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++) matrix[i][j] = 0;
}
Transform3D::Transform3D(float matrix[4][4]){
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++) this->matrix[i][j] = matrix[i][j];
}

Transform3D Transform3D::translation(Vector3 position){
    Transform3D trans = Transform3D::IDENTITY;
    trans.matrix[0][3] = position.x;
    trans.matrix[1][3] = position.y;
    trans.matrix[2][3] = position.z;
    return trans;
}
Transform3D Transform3D::rotation(Vector3 axis, float angle){
    return rotation(Quaternion(angle, axis));
}
Transform3D Transform3D::rotation(Quaternion quaternion){
    float i2 = quaternion.i * quaternion.i;
    float j2 = quaternion.j * quaternion.j;
    float k2 = quaternion.k * quaternion.k;
    float ij = quaternion.i * quaternion.j;
    float ik = quaternion.i * quaternion.k;
    float jk = quaternion.j * quaternion.k;
    float iw = quaternion.i * quaternion.w;
    float jw = quaternion.j * quaternion.w;
    float kw = quaternion.k * quaternion.w;
    float mat[4][4];
    mat[0][0] = 1-2*j2-2*k2;
    mat[0][1] = 2*ij-2*kw;
    mat[0][2] = 2*ik+2*jw;
    mat[0][3] = 0;
    mat[1][0] = 2*ij+2*kw;
    mat[1][1] = 1-2*i2-2*k2;
    mat[1][2] = 2*jk-2*iw;
    mat[1][3] = 0;
    mat[2][0] = 2*ik-2*jw;
    mat[2][1] = 2*jk+2*iw;
    mat[2][2] = 1-2*i2-2*j2;
    mat[2][3] = 0;
    mat[3][0] = 0;
    mat[3][1] = 0;
    mat[3][2] = 0;
    mat[3][3] = 1;
    return Transform3D(mat);
}
Transform3D Transform3D::scaling(Vector3 scale){
    Transform3D trans = Transform3D::IDENTITY;
    trans.matrix[0][0] = scale.x;
    trans.matrix[1][1] = scale.y;
    trans.matrix[2][2] = scale.z;
    return trans;
}

Transform3D Transform3D::operator*(Transform3D other){
    float mat[4][4];
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++){
            mat[i][j] = 0;
            for(int k=0; k<4; k++) mat[i][j] += matrix[i][k] * other.matrix[k][j];
        }
    return Transform3D(mat);
}
Transform3D Transform3D::operator+(Transform3D other){
    float mat[4][4];
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++) mat[i][j] = matrix[i][j] + other.matrix[i][j];
    return Transform3D(mat);
}
Transform3D Transform3D::operator-(Transform3D other){
    float mat[4][4];
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++) mat[i][j] = matrix[i][j] - other.matrix[i][j];
    return Transform3D(mat);
}


Transform3D Transform3D::inverse(){
    float m[16];
    float inv[16], det;
    int i;
    for(int row=0; row<4; row++)
        for(int col=0; col<4; col++)
            m[row*4 + col] = matrix[row][col];

    
    inv[0] = m[5]  * m[10] * m[15] - 
             m[5]  * m[11] * m[14] - 
             m[9]  * m[6]  * m[15] + 
             m[9]  * m[7]  * m[14] +
             m[13] * m[6]  * m[11] - 
             m[13] * m[7]  * m[10];

    inv[4] = -m[4]  * m[10] * m[15] + 
              m[4]  * m[11] * m[14] + 
              m[8]  * m[6]  * m[15] - 
              m[8]  * m[7]  * m[14] - 
              m[12] * m[6]  * m[11] + 
              m[12] * m[7]  * m[10];

    inv[8] = m[4]  * m[9] * m[15] - 
             m[4]  * m[11] * m[13] - 
             m[8]  * m[5] * m[15] + 
             m[8]  * m[7] * m[13] + 
             m[12] * m[5] * m[11] - 
             m[12] * m[7] * m[9];

    inv[12] = -m[4]  * m[9] * m[14] + 
               m[4]  * m[10] * m[13] +
               m[8]  * m[5] * m[14] - 
               m[8]  * m[6] * m[13] - 
               m[12] * m[5] * m[10] + 
               m[12] * m[6] * m[9];

    inv[1] = -m[1]  * m[10] * m[15] + 
              m[1]  * m[11] * m[14] + 
              m[9]  * m[2] * m[15] - 
              m[9]  * m[3] * m[14] - 
              m[13] * m[2] * m[11] + 
              m[13] * m[3] * m[10];

    inv[5] = m[0]  * m[10] * m[15] - 
             m[0]  * m[11] * m[14] - 
             m[8]  * m[2] * m[15] + 
             m[8]  * m[3] * m[14] + 
             m[12] * m[2] * m[11] - 
             m[12] * m[3] * m[10];

    inv[9] = -m[0]  * m[9] * m[15] + 
              m[0]  * m[11] * m[13] + 
              m[8]  * m[1] * m[15] - 
              m[8]  * m[3] * m[13] - 
              m[12] * m[1] * m[11] + 
              m[12] * m[3] * m[9];

    inv[13] = m[0]  * m[9] * m[14] - 
              m[0]  * m[10] * m[13] - 
              m[8]  * m[1] * m[14] + 
              m[8]  * m[2] * m[13] + 
              m[12] * m[1] * m[10] - 
              m[12] * m[2] * m[9];

    inv[2] = m[1]  * m[6] * m[15] - 
             m[1]  * m[7] * m[14] - 
             m[5]  * m[2] * m[15] + 
             m[5]  * m[3] * m[14] + 
             m[13] * m[2] * m[7] - 
             m[13] * m[3] * m[6];

    inv[6] = -m[0]  * m[6] * m[15] + 
              m[0]  * m[7] * m[14] + 
              m[4]  * m[2] * m[15] - 
              m[4]  * m[3] * m[14] - 
              m[12] * m[2] * m[7] + 
              m[12] * m[3] * m[6];

    inv[10] = m[0]  * m[5] * m[15] - 
              m[0]  * m[7] * m[13] - 
              m[4]  * m[1] * m[15] + 
              m[4]  * m[3] * m[13] + 
              m[12] * m[1] * m[7] - 
              m[12] * m[3] * m[5];

    inv[14] = -m[0]  * m[5] * m[14] + 
               m[0]  * m[6] * m[13] + 
               m[4]  * m[1] * m[14] - 
               m[4]  * m[2] * m[13] - 
               m[12] * m[1] * m[6] + 
               m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] + 
              m[1] * m[7] * m[10] + 
              m[5] * m[2] * m[11] - 
              m[5] * m[3] * m[10] - 
              m[9] * m[2] * m[7] + 
              m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] - 
             m[0] * m[7] * m[10] - 
             m[4] * m[2] * m[11] + 
             m[4] * m[3] * m[10] + 
             m[8] * m[2] * m[7] - 
             m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] + 
               m[0] * m[7] * m[9] + 
               m[4] * m[1] * m[11] - 
               m[4] * m[3] * m[9] - 
               m[8] * m[1] * m[7] + 
               m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] - 
              m[0] * m[6] * m[9] - 
              m[4] * m[1] * m[10] + 
              m[4] * m[2] * m[9] + 
              m[8] * m[1] * m[6] - 
              m[8] * m[2] * m[5];

    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    if (det == 0)
        return Transform3D::ZERO;

    det = 1.0 / det;
    float invOut[4][4];
    for (i = 0; i < 16; i++)
        invOut[i%4][i/4] = inv[i] * det;

    return Transform3D(invOut);
}


Transform3D identity(){
    float mat[4][4];
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++) mat[i][j] = i==j ? 1 : 0;
    return Transform3D(mat);
}