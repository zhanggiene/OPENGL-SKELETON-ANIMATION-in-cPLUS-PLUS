//
//  DepthBuffer.hpp
//  8th
//
//  Created by Zhang Zhuyan on 9/8/19.
//  Copyright © 2019 Zhang Zhuyan. All rights reserved.
//

#ifndef DepthBuffer_hpp
#define DepthBuffer_hpp

#include <stdio.h>
#include <GL/glew.h> 
class ShadowMapFBO
{
public:
    ShadowMapFBO();
    
    ~ShadowMapFBO();
    
    bool Init(unsigned int WindowWidth, unsigned int WindowHeight);
    
    void BindForWriting();//We will call it before the first render pass...
    
    void BindForReading(GLenum TextureUnit);
    
private:
    GLuint m_fbo;
    GLuint m_shadowMap;
};

#endif /* DepthBuffer_hpp */
