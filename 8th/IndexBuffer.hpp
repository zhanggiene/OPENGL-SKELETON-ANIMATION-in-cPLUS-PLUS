//
//  IndexBuffer.hpp
//  second
//
//  Created by Zhang Zhuyan on 21/6/19.
//  Copyright © 2019 Zhang Zhuyan. All rights reserved.
//

#ifndef IndexBuffer_hpp
#define IndexBuffer_hpp

#include <stdio.h>

class IndexBuffer
{
public:
    IndexBuffer(const void* data,const unsigned long count);
    // count is how many number 
    void bind();
    void unbind();
private:
    unsigned int mBufferID;
    unsigned long mCount;
    
    
    
    
    
    
    
};





#endif /* IndexBuffer_hpp */
