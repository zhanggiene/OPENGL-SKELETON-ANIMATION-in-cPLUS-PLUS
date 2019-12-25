//
//  TrackBall.cpp
//  fifth
//
//  Created by Zhang Zhuyan on 13/7/19.
//  Copyright © 2019 Zhang Zhuyan. All rights reserved.
//

#include "TrackBall.hpp"
#include <iostream>
#include <sstream>
Trackball::Trackball():
newMousePosition{0,0},oldMousePosition{0,0},previousQuat(glm::angleAxis(glm::radians((float)0), glm::vec3(0.f, 1.f, 0.f))){}


//commom mistake for debugging : the default value for quaternion is not glm::quat(0,0,0)
// it is glm::angleAxis(glm::radians((float)0), glm::vec3(0.f, 1.f, 0.f))
glm::mat4 Trackball::getRotationalMatrix(){
    if (!active)
    {
        return glm::mat4_cast(previousQuat);
    }
    else
    {
        int diff=oldMousePosition.y-newMousePosition.y;
         // std::cout<<"new mouse position is "<<newMousePosition.x<<"       ";
        //std::cout<<"old mouse position is "<<oldMousePosition.x<<"       ";
       // std::cout<<"diff is  "<<diff<<"       ";
        float angle=diff;
        addedQuat = glm::angleAxis(glm::radians((float)angle), glm::vec3(1.f, 0.f, 0.f));
        // i am simplfy the trackball because it will only rotate around y axis. 
        //std::cout<<"numerical angle is "<<angle<<"       ";
        previousQuat=addedQuat*previousQuat;
        glm::mat4 rotate = glm::mat4_cast(previousQuat);
        //std::cout<<"rotation angle is "<<previousQuat.w<<"       ";
       return rotate;
    }
    
    
    
}

void Trackball::setDefault(){
    active=false;
    newMousePosition=sf::Vector2i(0,0);
    oldMousePosition=sf::Vector2i(0,0);
}
void Trackball::setActive(){
    active=true;
    
}

void Trackball::update(sf::Vector2i& Newmousepos)
{
    if (oldMousePosition.x==0&&oldMousePosition.y==0)
    {
        oldMousePosition=Newmousepos;
        
    }
    else{
        oldMousePosition=newMousePosition;
    }
    newMousePosition=Newmousepos;
    
}
