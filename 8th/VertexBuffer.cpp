//
//  VertexBuffer.cpp
//  second
//
//  Created by Zhang Zhuyan on 21/6/19.
//  Copyright © 2019 Zhang Zhuyan. All rights reserved.
//

#include "VertexBuffer.hpp"
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

VertexBuffer::VertexBuffer(const void* data,const unsigned long size){
    
    glGenBuffers(1, &mBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, mBufferID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    
    
    
}

void VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, mBufferID);
    
}
void VertexBuffer::unbind()const {
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


