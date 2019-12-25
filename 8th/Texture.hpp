//
//  Texture.hpp
//  third
//
//  Created by Zhang Zhuyan on 24/6/19.
//  Copyright © 2019 Zhang Zhuyan. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <stdio.h>
#include <string>
#include <SFML/OpenGL.hpp>
class Texture
{
    public :
    Texture(const std::string& path);
    void bind(unsigned int slot=0);
    void unbind();
private:
    std::string m_FilePath;
    unsigned int textureID;
    int mWidth,mHeight,nChannel;   // later STB will feedback height and width of image
    unsigned char* mLocalBuffer;// pointer to image.
    
    
    
};
#endif /* Texture_hpp */
