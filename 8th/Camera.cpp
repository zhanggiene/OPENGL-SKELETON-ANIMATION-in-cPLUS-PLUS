//
//  Camera.cpp
//  fifth
//
//  Created by Zhang Zhuyan on 4/7/19.
//  Copyright © 2019 Zhang Zhuyan. All rights reserved.
//

#include "Camera.hpp"
#include <iostream>
#include <SFML/Window.hpp>

Camera::Camera():
UP{glm::vec3(0.0,1.0,0.0)},
cameraPos{glm::vec3(0.0,5.0,10.0)},

cameraFront{glm::vec3(0.0f, 0.0f, -1.0f)}, // check overleaf document to know about the orientation of opengl axis. 
cameraSpeed{0.1},
RightAngle(0.0f),
UpAngle(0.0f),
orientation(glm::quat(1.0f,0,0,0)),
first(true)
{
}
void Camera::KeyBoardUpdate()
{
    
    glm::quat qF = orientation * glm::quat(0, 0, 0, -1) * glm::conjugate(orientation);
    
    // math fomular, explained in overleaf.
    
    cameraFront = { qF.x, qF.y, qF.z };
    glm::vec3 Right = glm::normalize(glm::cross(cameraFront, glm::vec3(0, 1, 0)));

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
       cameraPos += cameraSpeed * cameraFront;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        cameraPos -= cameraSpeed * cameraFront;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        cameraPos -= Right * cameraSpeed; // the result of cross product is right hand rule, the product goes to right.
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        cameraPos += Right * cameraSpeed;
    
}
void Camera::mouseUpdate(sf::Vector2i& NewmousePos)
{
    
    x=NewmousePos.x;
    y=NewmousePos.y;
    if(first)
    {
        lastX=x;
        lastY=y;
        first=false;
        
    }
    int xoffset=x-lastX;
    int yoffset=y-lastY;
    lastX=x;
    lastY=y;
    float sensitivity=0.1;
    float xoffset_f=sensitivity*xoffset;
    float yoffset_f=sensitivity*yoffset;
    RightAngle+=xoffset_f;
    UpAngle+=yoffset_f;
    glm::quat aroundY = glm::angleAxis(glm::radians(-RightAngle), glm::vec3(0, 1, 0));
    
// use right hand rule, if xoffset_f is positive, it rotate to left, so we make it negative
    glm::quat aroundX = glm::angleAxis(glm::radians(-UpAngle), glm::vec3(1, 0, 0));
    orientation = aroundX*aroundY;
    
    
    
    
}


glm::mat4 Camera::worldToViewMattrix()
{
    glm::mat4 view;
    //glm::quat reverseOrient = glm::conjugate(orientation);
    view = glm::lookAt(cameraPos,cameraPos+cameraFront, glm::vec3(0.0, 1.0, 0.0));
    // when u move the camara, u need to move the point that the camera is looking at also. 
    return view;
    
    
}

