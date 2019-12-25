//
//  Animator.h
//  7th
//
//  Created by Zhang Zhuyan on 20/7/19.
//  Copyright © 2019 Zhang Zhuyan. All rights reserved.
//

#ifndef Animator_h
#define Animator_h
#include "Model.h"
#include "Animation.h"


class Animator()
{
private:
    Model mModel;
float animationTime=0f;
Animation currentAnimation;
public
    doAnimation(Animation animation)// it is like select which animation to use.
    {
        this.animationTime=0f;
        this.currentAnimation=animation;
        
    }
    void update() // to be used everyframe. 
    {
        
        
        
        
    }
    
    
    
    
}
#endif /* Animator_h */
