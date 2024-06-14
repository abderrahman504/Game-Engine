#include "Mesh3D.h"
using namespace Engine::Nodes;

void Mesh3D::Scale(float scaleFactor) {
    // Iterate through all vertices and scale them
    for (int i = 0; i < countPrimitives; ++i) {
        for (int j = 0; j < countIndeces[i]; ++j) {
            int vertexIndex = indeces[i][j];
            vertices[vertexIndex * 3] *= scaleFactor;        // Scale X coordinate
            vertices[vertexIndex * 3 + 1] *= scaleFactor;    // Scale Y coordinate
            vertices[vertexIndex * 3 + 2] *= scaleFactor;    // Scale Z coordinate
        }
    }
}

Mesh3D::Mesh3D(){
    setName("Mesh3D");
}
Mesh3D::~Mesh3D(){
    if(vertices != nullptr){
        for(int i = 0; i < countPrimitives; i++){
            delete[] vertices;
            delete[] indeces[i];
        }
        if(texCoords != nullptr){
            delete[] texCoords;
        }
        delete[] vertices;
        delete[] indeces;
        delete[] countIndeces;
        delete material;

    }
}
float* Mesh3D::Vertices(){return vertices;}
unsigned int** Mesh3D::Indeces(){return indeces;}
int* Mesh3D::CountIndeces(){return countIndeces;}
int Mesh3D::CountPrimitives(){return countPrimitives;}
int Mesh3D::TexCoordsSize(){return texCoordsSize;}
float* Mesh3D::TexCoords(){return texCoords;}


bool Mesh3D::LoadOBJ(const char* path) {
    std::vector<float> vertice;
    std::vector<unsigned int> indices;
    std::vector<float> texCoord;
    std::vector<float> normal;

    std::stringstream ss;
    std::ifstream in_file(path);
	std::string line = "";
	std::string prefix = "";
    GLint temp_glint = 0;

	//File open error check
	if (!in_file.is_open())
	{
		throw "ERROR::OBJLOADER::Could not open file.";
	}
    while (std::getline(in_file, line))
    {
        ss.clear();
        ss.str(line);
        ss >> prefix;
        if(prefix == "v"){
            float x, y, z;
            ss >> x >> y >> z;
            vertice.push_back(x);
            vertice.push_back(y);
            vertice.push_back(z);
        }
        else if(prefix == "vt"){
            float x, y;
            ss >> x >> y;
            texCoord.push_back(x);
            texCoord.push_back(y);
        }
        else if(prefix == "vn"){
            float x, y, z;
            ss >> x >> y >> z;
            normal.push_back(x);
            normal.push_back(y);
            normal.push_back(z);
        }
        else if(prefix == "f"){
            int counter = 0;
			while (ss >> temp_glint)
			{
				if (counter == 0)
					indices.push_back(temp_glint-1);
				// else if (counter == 1)
					// indices.push_back(temp_glint);
				// else if (counter == 2)
				// 	vertex_normal_indicies.push_back(temp_glint);

				//Handling characters
				if (ss.peek() == '/')
				{
					++counter;
					ss.ignore(1, '/');
				}
				else if (ss.peek() == ' ')
				{
					++counter;
					ss.ignore(1, ' ');
				}

				//Reset the counter
				if (counter > 2)
					counter = 0;
			}	
        }
    }

    countPrimitives = indices.size();
    countIndeces = new int[countPrimitives];
    indeces = new unsigned int*[countPrimitives];
    for (int i = 0; i < countPrimitives; i++) {
        indeces[i] = new unsigned int[3];
        countIndeces[i] = 3;
    }
    vertices = new float[vertice.size()];
    texCoords = new float[texCoord.size()];
    texCoordsSize = texCoord.size();
    for (int i = 0; i < vertice.size(); i++) {
        vertices[i] = vertice[i];
    }
    for (int i = 0; i < texCoord.size(); i++) {
        texCoords[i] = texCoord[i];
    }
    for (int i = 0; i < indices.size(); i++) {
        indeces[i][0] = indices[i];
        indeces[i][1] = indices[i + 1];
        indeces[i][2] = indices[i + 2];
    }
    return true;
    


}




// static std::vector<Vertex> loadOBJ(const char* file_name)
// {
// 	//Vertex portions
// 	std::vector<glm::fvec3> vertex_positions;
// 	std::vector<glm::fvec2> vertex_texcoords;
// 	std::vector<glm::fvec3> vertex_normals;

// 	//Face vectors
// 	std::vector<GLint> vertex_position_indicies;
// 	std::vector<GLint> vertex_texcoord_indicies;
// 	std::vector<GLint> vertex_normal_indicies;

// 	//Vertex array
// 	std::vector<Vertex> vertices;

// 	std::stringstream ss;
// 	std::ifstream in_file(file_name);
// 	std::string line = "";
// 	std::string prefix = "";
// 	glm::vec3 temp_vec3;
// 	glm::vec2 temp_vec2;
// 	GLint temp_glint = 0;

// 	//File open error check
// 	if (!in_file.is_open())
// 	{
// 		throw "ERROR::OBJLOADER::Could not open file.";
// 	}

// 	//Read one line at a time
// 	while (std::getline(in_file, line))
// 	{
// 		//Get the prefix of the line
// 		ss.clear();
// 		ss.str(line);
// 		ss >> prefix;

// 		if (prefix == "#")
// 		{

// 		}
// 		else if (prefix == "o")
// 		{

// 		}
// 		else if (prefix == "s")
// 		{

// 		}
// 		else if (prefix == "use_mtl")
// 		{

// 		}
// 		else if (prefix == "v") //Vertex position
// 		{
// 			ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
// 			vertex_positions.push_back(temp_vec3);
// 		}
// 		else if (prefix == "vt")
// 		{
// 			ss >> temp_vec2.x >> temp_vec2.y;
// 			vertex_texcoords.push_back(temp_vec2);
// 		}
// 		else if (prefix == "vn")
// 		{
// 			ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
// 			vertex_normals.push_back(temp_vec3);
// 		}
// 		else if (prefix == "f")
// 		{
// 			int counter = 0;
// 			while (ss >> temp_glint)
// 			{
// 				//Pushing indices into correct arrays
// 				if (counter == 0)
// 					vertex_position_indicies.push_back(temp_glint);
// 				else if (counter == 1)
// 					vertex_texcoord_indicies.push_back(temp_glint);
// 				else if (counter == 2)
// 					vertex_normal_indicies.push_back(temp_glint);

// 				//Handling characters
// 				if (ss.peek() == '/')
// 				{
// 					++counter;
// 					ss.ignore(1, '/');
// 				}
// 				else if (ss.peek() == ' ')
// 				{
// 					++counter;
// 					ss.ignore(1, ' ');
// 				}

// 				//Reset the counter
// 				if (counter > 2)
// 					counter = 0;
// 			}	
// 		}
// 		else
// 		{

// 		}
// 	}

// 	//Build final vertex array (mesh)
// 	vertices.resize(vertex_position_indicies.size(), Vertex());

// 	//Load in all indices
// 	for (size_t i = 0; i < vertices.size(); ++i)
// 	{
// 		vertices[i].position = vertex_positions[vertex_position_indicies[i] - 1];
// 		vertices[i].texcoord = vertex_texcoords[vertex_texcoord_indicies[i] - 1];
// 		vertices[i].normal = vertex_normals[vertex_normal_indicies[i] - 1];
// 		vertices[i].color = glm::vec3(1.f, 1.f, 1.f);
// 	}

// 	//DEBUG
// 	std::cout << "Nr of vertices: " << vertices.size() << "\n";

// 	//Loaded success
// 	std::cout << "OBJ file loaded!" << "\n";
// 	return vertices;
// }
