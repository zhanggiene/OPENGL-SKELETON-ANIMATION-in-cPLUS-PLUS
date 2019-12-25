//
//  Model.hpp
//  fifth
//
//  Created by Zhang Zhuyan on 28/6/19.
//  Copyright © 2019 Zhang Zhuyan. All rights reserved.
//

#ifndef Model_hpp
#define Model_hpp

#include <stdio.h>
#include "shader.hpp"
#include <vector>
#include <string>
#include "Mesh.hpp"
using namespace std;


class Model
{
public:
    /*  Functions   */
    Model(char *path)
    {
        loadModel(path);
    }
    void Draw(Shader& shader);
private:
    /*  Model Data  */
    vector<Mesh> meshes;
    string directory;
    /*  Functions   */
    void loadModel(string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                         string typeName);
};
#endif /* Model_hpp */
