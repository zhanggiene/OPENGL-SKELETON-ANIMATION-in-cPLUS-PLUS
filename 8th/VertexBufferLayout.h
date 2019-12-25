//
//  VertexBufferLayout.h
//  third
//
//  Created by Zhang Zhuyan on 23/6/19.
//  Copyright © 2019 Zhang Zhuyan. All rights reserved.
//

#ifndef VertexBufferLayout_h
#define VertexBufferLayout_h
#include <stdio.h>
#include <vector>
#include <GL/glew.h>

template<typename T>
struct identity { typedef T type; };



struct VertexBufferElements
{
    unsigned int type;
    unsigned int count;
    bool normalized;
    

};

class VertexBufferLayout{
private:
    unsigned int mStride;
    std::vector<VertexBufferElements> mElements;
    
    template <typename T>
    void push(unsigned int count, identity<T>){
        printf("something bad");
    }
    
    void push(unsigned int count, identity<float>){
        mElements.push_back({GL_FLOAT, count, GL_FALSE});
        mStride += sizeof(GL_FLOAT) * count;
    }
    void push(unsigned int count, identity<int>){
        mElements.push_back({GL_INT, count, GL_FALSE});
        mStride += sizeof(GL_INT) * count;
    }
    

    
    
    
public:
    VertexBufferLayout();
    template <typename T> void push(unsigned int count, identity<T>());

    const std::vector<VertexBufferElements> getElements()const;
    template <typename T>
    void push(unsigned int count){
        push(count, identity<T>());
    }
    
    //************this is a really smart to pass in type in argument, i dont really understand yet, i get the code from online. 
    
    
    
    
    
    const unsigned int getStride() const;
};





#endif /* VertexBufferLayout_h */
