//
//  VertexArray.cpp
//  third
//
//  Created by Zhang Zhuyan on 22/6/19.
//  Copyright © 2019 Zhang Zhuyan. All rights reserved.
//

#include "VertexArray.hpp"

int VertexArray::index;
VertexArray::VertexArray(){
    
    glGenVertexArrays(1,&vaID);
    //index=0;
}
void VertexArray::bind(){
    glBindVertexArray(vaID);
    
}
void VertexArray::unbind(){
    glBindVertexArray(0);
    
}

void VertexArray::combine(const VertexBuffer& vb,const VertexBufferLayout& layout){
    bind();
    vb.bind();
    const auto& elements=layout.getElements();
    unsigned int offset=0;
    
    for (unsigned int i=0;i<elements.size();i++)
    {
        const auto& element=elements[i];
        
        glEnableVertexAttribArray(i);
        
        if(element.type==GL_FLOAT)
        {
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(),(const void*)offset);
            //std::cout<<"*********************float is  being used "<<std::endl;
            //std::cout<<"glenablevertexattribarray("<<i<<")"<<","<<"size is "<<element.count<<"stride is "<<layout.getStride()<<","<<offset<<std::endl;

        }
        else if (element.type==GL_INT)
        {
            glVertexAttribIPointer(i, element.count, element.type , layout.getStride(),(const void*)offset);
           // std::cout<<"*********************int is  being used "<<std::endl;
            //s//td::cout<<"glenablevertexattribarray("<<i<<")"<<","<<"size is "<<element.count<<"stride is "<<layout.getStride()<<","<<offset<<std::endl;
        }
        else
        {
            //std::cout<<"*********************fucked up "<<std::endl;
            
        }
        offset+=element.count*4;
        
    }
    

    
}
unsigned int VertexArray::getID(){
    return vaID;
    
}
