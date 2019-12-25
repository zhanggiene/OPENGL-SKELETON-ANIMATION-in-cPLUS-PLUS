//
//  Shader.hpp
//  second
//
//  Created by Zhang Zhuyan on 16/6/19.
//  Copyright © 2019 Zhang Zhuyan. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <stdio.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm.hpp> 
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
class Shader {
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    unsigned int ID;
    void use();
 
    void setBool(const std::string &name, bool value) const;
// provid the name of the uniform and the value u want to set.
    // ------------------------------------------------------------------------
    void setInt(const std::string &name, int value) const;

    // ------------------------------------------------------------------------
    void setVec3f(const std::string &name, glm::vec3 value) const;
    void setFloat(const std::string &name, float value) const;

    void setMatrix(const std::string &name, glm::mat4 value) const;
    void setMatrixArray(const std::string &name, int number,glm::mat4 mattrixArray[number]) const;
private:
    void checkCompileErrors(unsigned int shader, std::string type);
    
    
    
    
    
    
};










#endif /* Shader_hpp */
