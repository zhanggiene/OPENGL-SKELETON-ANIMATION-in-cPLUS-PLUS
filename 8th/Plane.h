//
//  Plane.h
//  8th
//
//  Created by Zhang Zhuyan on 5/8/19.
//  Copyright © 2019 Zhang Zhuyan. All rights reserved.
//

#ifndef Plane_h
#define Plane_h
#include "shader.hpp"
#include "VertexBufferLayout.h"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"


class Plane

{
    
private:
    float planeVertices[48] = {
        // positions            // normals         // texcoords
        1000.0f, -110.5f,  -800.0f,
        -800.0f, -110.5f,  -800.0f,
        -800.0f, -110.5f, 800.0f,
        
        1000.0f, -110.5f,  -800.0f,
        -800.0f, -110.5f, 800.0f,
        1000.0f, -110.5f, 800.0f,
    };
    /*  Render data  */
    unsigned int VAO;
    
    /*  Functions    */
    // initializes all the buffer objects/arrays
    void setupMesh()
    {
        //std::cout<<"set up mesh now";
        
        VertexArray VAO_obj=VertexArray();
        VertexBuffer VBO_obj=VertexBuffer(planeVertices,sizeof(float)*sizeof(planeVertices));
        VertexBufferLayout vertex_position=VertexBufferLayout();
        vertex_position.push<float>(3);
        
        VAO_obj.combine(VBO_obj, vertex_position);
        VAO=VAO_obj.getID();// VAO is stored in public domain and it is important for drawing , so we need to pass it to public domain. it is the bug that i took very long to find.
        VAO_obj.unbind();
    }
        
        
    public:
        Plane()
        {
            setupMesh();
            
        }
        void Draw(Shader& shader)
        {
         
            
            glBindVertexArray(VAO);
             glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);
            
            // always good practice to set everything back to defaults once configured
    
    
}
};
#endif /* Plane_h */
