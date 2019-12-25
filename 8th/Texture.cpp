//
//  Texture.cpp
//  third
//
//  Created by Zhang Zhuyan on 24/6/19.
//  Copyright © 2019 Zhang Zhuyan. All rights reserved.
//

#include "Texture.hpp"
#include "STB.h"
#include <string>
#include <iostream>

Texture::Texture(const std::string& path)
:m_FilePath(path)
{
    //stbi_set_flip_vertically_on_load(1);
    glGenTextures(1,&textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    mLocalBuffer=stbi_load(m_FilePath.c_str(), &mWidth, &mHeight, &nChannel,0);
    //
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (mLocalBuffer)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth,mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, mLocalBuffer);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(mLocalBuffer);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    glBindTexture(GL_TEXTURE_2D,0);  // unbind so we can bind more and create more object in the future.
}

void Texture::bind(unsigned int slot){
    glActiveTexture(GL_TEXTURE0+slot);                   // select slot 0 of the texture units array
    glBindTexture(GL_TEXTURE_2D,textureID);    // do the binding
    
}
