//
//  Mesh.h
//  fifth
//
//  Created by Zhang Zhuyan on 28/6/19.
//  Copyright © 2019 Zhang Zhuyan. All rights reserved.
//

#ifndef Mesh_h
#define Mesh_h



#include <glm.hpp>
#include "shader.hpp"
#include "VertexBufferLayout.h"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"


#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;
#define NUM_BONES_PER_VERTEX 4

/*struct VertexBoneData {
    
    int boneID[NUM_BONES_PER_VERTEX]={0};
    
    float weights[NUM_BONES_PER_VERTEX]={0};
    
};*/
struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
   // VertexBoneData boneVertex;
    int boneID[4]={0,0,0,0,};
    
    float weights[4]={0,0,0,0};
};
struct Material {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess=0.5;
};



class Mesh {
public:
    /*  Mesh Data  */
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    Material material;
    unsigned int VAO;
    
    /*  Functions  */
    // constructor
    Mesh(vector<Vertex>& vertices, vector<unsigned int>& indices,Material &material)
    {
        
        this->vertices = vertices;
        this->indices = indices;
        this->material=material;
        
        
        
        setupMesh();
    }
    
    void Draw(Shader& shader)
    {
        
        for(int i=0;i<vertices.size();i++){
            
            for (int j=0;j<4;j++)
            {
                
               //std::cout<<i<<" has bone iD "<<vertices[i].boneID[j]<<"with weight "<<vertices[i].weights[j]<<std::endl;
            }
            
            
        }
        // bind appropriate textures
        
        // draw mesh
       // std::cout<<"size of vertex is "<<vertices.size()<<std::endl;
        //std::cout<<position 
       shader.setVec3f("material.ambient",material.ambient);
        shader.setVec3f("material.diffuse",  material.diffuse);
        //std::cout<<"diffuse is********************* "<<material.diffuse.x<<std::endl;
        shader.setVec3f("material.specular", material.specular);
        shader.setFloat("material.shininess", material.shininess);
        
       
        
        
        
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        
        // always good practice to set everything back to defaults once configured.
        glActiveTexture(GL_TEXTURE0);
    }
    
private:
    /*  Render data  */
    unsigned int VBO;
    
    /*  Functions    */
    // initializes all the buffer objects/arrays
    void setupMesh()
    {
      //std::cout<<"set up mesh now";
        
        VertexArray VAO_obj=VertexArray();
        VertexBuffer VBO_obj=VertexBuffer(&vertices[0],vertices.size()*sizeof(Vertex));
        VertexBufferLayout vertex_position=VertexBufferLayout();
        vertex_position.push<float>(3);
        vertex_position.push<float>(3);
        vertex_position.push<int>(4);
        vertex_position.push<float>(4);
        
        VAO_obj.combine(VBO_obj, vertex_position);
        VAO=VAO_obj.getID();// VAO is stored in public domain and it is important for drawing , so we need to pass it to public domain. it is the bug that i took very long to find. 
        
        IndexBuffer IBO(&indices[0],indices.size());
        IBO.bind();
        VAO_obj.unbind();
        
        
        
        
        
    }
    
    
    
    
    
    
    
    
    
};

#endif /* Mesh_h */
