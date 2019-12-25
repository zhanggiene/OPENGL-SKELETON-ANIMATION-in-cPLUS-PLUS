//
//  Animation.h
//  7th
//
//  Created by Zhang Zhuyan on 20/7/19.
//  Copyright © 2019 Zhang Zhuyan. All rights reserved.
//

#ifndef Animation_h
#define Animation_h
#include "Keyframe.h"
class Animation{
    
    private :
    float length;// in seconds
    vector<Keyframe> keyframe;
    string name;
public:
    Animation(float lengthInSeconds, string name,vector<Keyframe> frames) {
        this->keyframe = frames;
        this->length = lengthInSeconds;
        this->name=name;
    }
    float getLength(){
        return length;
        
    }
    vector<Keyframe> getKeyFrame(){
        return keyframe;
    }
    
    
};
#endif /* Animation_h */
