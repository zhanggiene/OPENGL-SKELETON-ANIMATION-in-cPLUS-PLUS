//
//  Keyframe.h
//  7th
//
//  Created by Zhang Zhuyan on 20/7/19.
//  Copyright © 2019 Zhang Zhuyan. All rights reserved.
//

#ifndef Keyframe_h
#define Keyframe_h
#include "JointTransform.h"
#include <glm.hpp>
class Keyframe
{
private:
    float timeStamp;
    std::map<std::string,JointTransform> pose;
    public :
    Keyframe(float timeStamp, map<std::string, JointTransform> jointKeyFrames)
    {
        this->timeStamp = timeStamp;
        this->pose = jointKeyFrames;
    }
    float getTimeStamp()
    {
        return timeStamp;
    }
    bool isTimeStamp(float time)
    {
        return time==timeStamp;
        
    }
    
    map<std::string, JointTransform> getPose()
    {
        return pose;
        
    }
    
    
    
    
    
    
    
    
    
};
#endif /* Keyframe_h */
