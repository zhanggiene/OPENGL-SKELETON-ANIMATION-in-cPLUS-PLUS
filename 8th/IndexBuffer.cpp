//
//  IndexBuffer.cpp
//  second
//
//  Created by Zhang Zhuyan on 21/6/19.
//  Copyright © 2019 Zhang Zhuyan. All rights reserved.
//

#include "IndexBuffer.hpp"

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

IndexBuffer::IndexBuffer(const void* data,const unsigned long count)
:mCount(count)
{
    
    glGenBuffers(1, &mBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(unsigned int), data, GL_STATIC_DRAW);
    
    
    
}

void IndexBuffer::bind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBufferID);
    
    
}
void IndexBuffer::unbind(){
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


