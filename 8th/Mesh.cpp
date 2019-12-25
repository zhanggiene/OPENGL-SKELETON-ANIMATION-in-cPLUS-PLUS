//
//  Mesh.cpp
//  fifth
//
//  Created by Zhang Zhuyan on 27/6/19.
//  Copyright © 2019 Zhang Zhuyan. All rights reserved.
//

#include "Mesh.hpp"

Mesh::Mesh(vector<Vertex>& vertices,vector<GLuint>& indices,vector<Texture>& textures)
{
    this->vertices=vertices;
    this->indices=indices;
    this->textures=textures;
    setupMesh();
    }
void Mesh::setupMesh()
{
    VertexArray VAO=VertexArray();
    VertexBuffer VBO=VertexBuffer(&vertices[0],vertices.size()*sizeof(Vertex));
    VertexBufferLayout vertex_position=VertexBufferLayout();
    vertex_position.push<float>(3);
    vertex_position.push<float>(3);
    
    VAO.combine(VBO, vertex_position);
    IndexBuffer IBO(indices.data(),indices.size());
    VBO.unbind();
    VAO.unbind();
    IBO.unbind();
    
    
}

void Mesh::Draw(Shader& shader)
{
    unsigned int diffuseNr=1;
    unsigned int specularNr=1;
    for (int i=0;i<textures.size();i++)
    {
        glActiveTexture(GL_TEXTURE0+i);
        string number;
        string name=textures[i].type;
        if (name=="texture_diffuse")
        {
            number=std::to_string(diffuseNr++);
        }
        else if (name=="texture_specular")
        {
            number=std::to_string(specularNr++);
        }
        shader.setFloat(("material." + name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    glActiveTexture(GL_TEXTURE0);
    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    
    
}
    
    

