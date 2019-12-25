//
//  Mesh.hpp
//  fifth
//
//  Created by Zhang Zhuyan on 27/6/19.
//  Copyright © 2019 Zhang Zhuyan. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <stdio.h>
//#include <GL/glew.h>  // inlude this first, as it overlapps with SFML.
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <string>
#include <glm.hpp>
#include <vector>
#include "shader.hpp"
#include "VertexBufferLayout.h"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
using namespace std;

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoordinate;
};




struct Texture
{
    GLuint id;
    string type;
};

class Mesh
{
public:
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<Texture> textures;
    Mesh(vector<Vertex>& vertices,vector<GLuint>& indices,vector<Texture>& textures);
    //vertices.data() memory layout is the same as use manually supply data like in the first few tutorial. 
    
    
    void Draw(Shader& shader);
private:
    /*  Render data  */
    unsigned int VAO, VBO, IBO;   // because we gonna have one VAO,VBO,IBO per object
    /*  Functions    */
    void setupMesh();
    
    
};







#endif /* Mesh_hpp */
