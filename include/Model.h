//
// Created by Hython on 2018/5/22.
//

#ifndef GLUT_LEARNING_MODEL_H
#define GLUT_LEARNING_MODEL_H
#include "Mesh.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
class Model {
public:
    /*  Functions   */
    Model(const string path)
    {
        loadModel(path);
    }
    void Draw(Shader shader);
private:
    /*  Model Data  */
    vector<Texture> textures_loaded;
    vector<Mesh> meshes;
    string directory;
    /*  Functions   */
    void loadModel(string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                         string typeName);
};


unsigned int TextureFromFile(const char *path, const string &directory);

#endif //GLUT_LEARNING_MODEL_H
