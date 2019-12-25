//
//  VertexBufferLayout.cpp
//  third
//
//  Created by Zhang Zhuyan on 22/6/19.
//  Copyright © 2019 Zhang Zhuyan. All rights reserved.
//

#include "VertexBufferLayout.h"

VertexBufferLayout::VertexBufferLayout()
{
    mStride=0;
}



const std::vector<VertexBufferElements> VertexBufferLayout::getElements()const {
    
    return mElements;}
  


const unsigned int VertexBufferLayout::getStride() const {
    
    return mStride;
    
}

