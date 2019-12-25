//
//  TrackBall.hpp
//  fifth
//
//  Created by Zhang Zhuyan on 13/7/19.
//  Copyright © 2019 Zhang Zhuyan. All rights reserved.
//

#ifndef TrackBall_hpp
#define TrackBall_hpp

#include <stdio.h>
#include <SFML/Window.hpp>
#include <gtc/quaternion.hpp>
//#include <gtx/quaternion.hpp>

class Trackball
{
public:
    glm::mat4 getRotationalMatrix();
    Trackball();
    void update(sf::Vector2i& NewmousePos);
    void setDefault();
    void setActive();
    private :
    sf::Vector2i newMousePosition;  // relative to the window , not the whole screen
    sf::Vector2i oldMousePosition;
    bool active;
    
    glm::quat previousQuat;
    glm::quat addedQuat;
   // glm::vec3 center=glm::vec3(0.0,0.0,0.0);
    
    
};




#endif /* TrackBall_hpp */
