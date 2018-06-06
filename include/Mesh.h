//
// Created by Hython on 2018/5/22.
//

#ifndef GLUT_LEARNING_MESH_H
#define GLUT_LEARNING_MESH_H
#include "glm/glm.hpp"
#include "Shader.h"
#include <string>
#include <vector>
#include <memory>

using std::string;
using std::vector;
using std::allocator;
struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture {
    unsigned int id;
    string type;
    string path;
};

class Mesh {
public:
    /*  Mesh Data  */
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;
    /*  Functions  */
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
    void Draw(Shader shader);
private:
    /*  Render data  */
    unsigned int VAO, VBO, EBO;
    /*  Functions    */
    void setupMesh();
};

#endif //GLUT_LEARNING_MESH_H
