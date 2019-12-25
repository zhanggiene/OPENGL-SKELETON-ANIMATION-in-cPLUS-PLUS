//
//  VertexArray.hpp
//  third
//
//  Created by Zhang Zhuyan on 22/6/19.
//  Copyright © 2019 Zhang Zhuyan. All rights reserved.
//

#ifndef VertexArray_hpp
#define VertexArray_hpp

#include <stdio.h>
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.h"
#include <iostream>
class VertexArray
{
private:
    unsigned int vaID;
    
public:
    VertexArray();
    void combine( const VertexBuffer& vb,const VertexBufferLayout& layout);
    // & means reference, it is like pointer, but easier to use.
    // we basically want to bind buffer data and attribute together, 
    void bind();
    void unbind();
    static int index;
    unsigned int getID();
};

 




#endif /* VertexArray_hpp */
