//
//  jointTransform.h
//  7th
//
//  Created by Zhang Zhuyan on 20/7/19.
//  Copyright © 2019 Zhang Zhuyan. All rights reserved.
//

#ifndef jointTransform_h
#define jointTransform_h
#include <glm.hpp>
#include <GL/glew.h>






glm::vec3 interpolateVector(glm::vec3 start, glm::vec3 end, float progression);
class JointTransform{
    
    
    public :
    glm::vec3 translation;
    glm::quat rotation;
    glm::vec3 scaling;
    
    //default constructor:
    JointTransform():
    translation{glm::vec3(1.0f)},rotation{glm::quat(1.0f,0.0,0.0,0.0)}{}
    
    JointTransform(glm::vec3 Translation,glm::quat Rotation,glm::vec3 Scaling)
    {
        this->translation=Translation;
        this->rotation=Rotation;
        this->scaling=Scaling;
        
    }
    
        glm::mat4 getLocalCombinedMatrix()
    {
            glm::mat4 combinedMatrix=glm::mat4(1.0f);
            glm::translate(combinedMatrix,translation);
            glm::mat4 rotate = glm::mat4_cast(rotation);
            glm::mat4 ScalingM = glm::scale(glm::mat4(1.0f), scaling);
            // the order is rotation first , then translation.TRS
            return combinedMatrix*rotate*ScalingM;
            
        }
    
    JointTransform interpolate(JointTransform two, float progression){
        //std::cout<<"hi i am being used"<<std::endl;
        //std::cout<<" "<<this->translation.x<<" "<<this->translation.y<<" "<<this->translation.z<<std::endl;
        
        
        return JointTransform(interpolateVector(this->translation, two.translation,progression),glm::slerp(this->rotation,two.rotation,progression),interpolateVector(this->scaling, two.scaling,progression));
        
        
    }
    
    
    
        
};


glm::vec3 interpolateVector(glm::vec3 start, glm::vec3 end, float progression) {
    
    // root of the problem , start and the end is the same. 
   // std::cout<<"start x is "<<start.x<<" end x is  "<<end.x<<" the progression is "<<progression<<std::endl;
    float x = start.x + (end.x - start.x) * progression;
    float y = start.y + (end.y - start.y) * progression;
    float z = start.z + (end.z - start.z) * progression;
    //std::cout<<" "<<x<<" "<<y<<" "<<z<<"the progression is "<<progression<<std::endl;
    return glm::vec3(x, y, z);
}

std::ostream& operator<< (std::ostream &out, JointTransform const& data) {
    out <<"translation is "<< data.translation.x <<" , "<< data.translation.y <<" , "<<data.translation.z <<" , ";
    out <<"rotation is "<< data.rotation.w <<" , "<< data.rotation.x <<" , "<<data.rotation.y <<" , "<<data.rotation.z<<std::endl;
   // out << data.getcylinders() << ':';
    // and so on...
    return out;
}


    

#endif /* jointTransform_h */
