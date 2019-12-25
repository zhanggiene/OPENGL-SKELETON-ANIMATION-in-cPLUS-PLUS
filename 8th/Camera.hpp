//
//  Camera.hpp
//  fifth
//
//  Created by Zhang Zhuyan on 4/7/19.
//  Copyright © 2019 Zhang Zhuyan. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <stdio.h>
#include <GL/glew.h> 
#include <gtx/transform.hpp>
#include <SFML/Window.hpp>
#include <gtc/quaternion.hpp>
class Camera{
private:
    glm::vec3 UP=glm::vec3(0.0f, 1.0f,  0.0f);
    glm::vec3 cameraPos=glm::vec3(0.0f, 0.0f,3.0f);
    glm::quat orientation; // orientation of the camera.
    float RightAngle;  // how much angle the camera is tilted towards right.
    float UpAngle;     // how much angle is tilted towards up. 
    int lastX;
    int lastY;
    int x;
    int y;
    glm::vec3 cameraFront;
    float cameraSpeed;
    bool first;
public:
    Camera();
    glm::mat4 worldToViewMattrix();
    void KeyBoardUpdate();
    void mouseUpdate(sf::Vector2i& NewmousePos);
};




#endif /* Camera_hpp */
