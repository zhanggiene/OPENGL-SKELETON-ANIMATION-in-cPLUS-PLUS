//
//  main.cpp
//  first_meshing
//
//  Created by Zhang Zhuyan on 2/6/19.
//  Copyright © 2019 Zhang Zhuyan. All rights reserved.
//
#include <GL/glew.h>  // inlude this first, as it overlapps with SFML.
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
//#include <SFML/Graphics.hpp>  dont include SFML/GRAPHICS unless u are doing some SFML transformation

#include <glm.hpp>
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>
#include "shader.hpp"
#include "VertexBufferLayout.h"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Mesh.h"
#include <assimp/Importer.hpp>
#include "Mesh.h"
#include "Model.h"
#include <iostream>
#include "Camera.hpp"
#include "TrackBall.hpp"
#include "Plane.h"

// is the arms also moving with hand ?????
using namespace sf;
int main( int argc, char** argv )
{
    float y=0.0f;
    float x=0;
    sf::Clock clock;
    int widthScreen=2080;
    int heightScreen=1760;
    Trackball trackball;
    glm::vec3 lightPosition(10.0f,20.0f,-15.0f);
    glm::vec3 cameraFront(0.0,0.0,-1.0);
    //renderwindows become window,
    sf::ContextSettings settings;
    settings.depthBits = 32;
    settings.stencilBits = 0;
    settings.antialiasingLevel = 0;
    settings.majorVersion = 4;
    settings.minorVersion = 1; // it means 4.1
    Window window(sf::VideoMode(widthScreen,heightScreen),"parade",sf::Style::Default, settings);
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    window.setActive(); // active the windows for OpenGL rendering,
    //draw using OpenGL commands go here.
    
     glEnable(GL_DEPTH_TEST);    // GL depth test is disabled by default.
    
    
    glewInit(); //  rememebr to include this code to initialise glew.
    Camera camera;
    Plane plane;
   
    
    
    
    
    Shader lightProgram("LightShader.txt","fragmentShaderLight.txt");
    Shader ObjProgram("ObjShader.txt","fragmentShader.txt");

    Shader depthProgram("depthShader.txt","depthFragment.txt");
    Shader planeProgram("planeShader.txt","planeFrag.txt");
    
    float cube_vertices[] = {
        -1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end
        1.0f, 1.0f,-1.0f, // triangle 2 : begin
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f, // triangle 2 : end
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f

    };
    //light
    VertexArray VAO=VertexArray();
    VertexBuffer VBO=VertexBuffer(cube_vertices,sizeof(cube_vertices));
    VertexBufferLayout vertex_position=VertexBufferLayout();
    vertex_position.push<float>(3);
    VAO.combine(VBO, vertex_position);
    
    

   // Model ourModel("/Users/zhangzhuyan/F/resources/nanosuit.obj");
    Model ourModel("/Users/zhangzhuyan/Desktop/coding/c++/computer\ graphics/8th/8th/resources/encik-marching.dae");
    while (window.isOpen())
    {
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); // clear color must be at the start of drawing.
        sf::Vector2i localPosition=sf::Mouse::getPosition(window);
        sf::Event event;
        glm::vec3 cameraChanges(0.0,0.0,0.0);
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            
            //std::cout::
        }
        camera.mouseUpdate(localPosition);
        camera.KeyBoardUpdate();
      
        //get ready all the matrix.
       float radius = 10.0f;
        float cameraHeight=10.f;
        sf::Time elapsed1 = clock.getElapsedTime();
        float  sec  = elapsed1.asSeconds();
        float camX = sin(sec) * radius;
        float camZ = cos(sec) * radius;
        float y_axis=-sin(sec)*cameraHeight;
        glm::vec3 cameraPosition(camX,y_axis,camZ);
        
        glm::mat4 view(1.0f);
        //view = glm::lookAt(cameraPosition,glm::vec3(0.0,0.0,0.0), glm::vec3(0.0, 1.0, 0.0));
        view =camera.worldToViewMattrix();
        glm::mat4 projection=glm::mat4(1.0f);
        projection=glm::perspective(glm::radians(90.0f),(float)widthScreen/(float)heightScreen,0.1f,100.0f);
       //glm::mat4 projection = glm::ortho(0, widthScreen, heightScreen, 0, 0, 1000);
        
        
        
        glm::mat4 modelLight=glm::mat4(1.0f);
        x+=0.001;
        lightPosition=glm::vec3(sin(x),lightPosition.y,lightPosition.z);
        modelLight = glm::translate(modelLight,lightPosition);
        modelLight=glm::scale(modelLight, glm::vec3(0.2));
        
        glm::mat4 model=glm::mat4(1.0f);
        if (!(sf::Mouse::isButtonPressed(Mouse::Button::Left)))
        {
            trackball.setDefault();
        }
        else{
            trackball.setActive();
            sf::Vector2i mousePosition=sf::Mouse::getPosition(window);
            trackball.update(mousePosition);
            
        }
        //model=glm::rotate(model,glm::radians(180),glm::vec3(0.0f,1.0f,0.0f));
        //model = glm::rotate(model, glm::radians(180), glm::vec3(1.0f, 0.3f, 0.5f));
        model=model*trackball.getRotationalMatrix();
        model=glm::scale(model, glm::vec3(5));
        
        model=glm::translate(model,glm::vec3(0,-y,0));
        y+=0.01;
        
        
        
        
        
        
        
        ObjProgram.use();
        ObjProgram.setMatrix("view",view);
        ObjProgram.setMatrix("projection",projection);
        
       ObjProgram.setVec3f("lightColor",glm::vec3(1));
        ObjProgram.setVec3f("lightPos",lightPosition);
        
        
        //ourModel.randomCheck();
    
        for (int i=0;i<10;i++) // colown
        {
            for (int j=0;j<10;j++)   // row
            {
                model = glm::translate(model,glm::vec3((float)i*0.5,(float)j*0.5,0));
                ObjProgram.setMatrix("model",model);
                ourModel.Draw(ObjProgram);
                model = glm::translate(model,-glm::vec3((float)i*0.5,(float)j*0.5,0));
                
            
            }
            
        }
        lightProgram.use();
        VAO.bind();
        lightProgram.setMatrix("view",view);
        lightProgram.setMatrix("projection",projection);
        lightProgram.setMatrix("model",modelLight);
        glDrawArrays(GL_TRIANGLES,0,36);
        VAO.unbind();
        planeProgram.use();
        plane.Draw(planeProgram);
        
        
        window.display();            //sleep(seconds(5));
        //std::cout<<std::fmod(0.3,0.4)<<std::endl;
        
    }
    
    
    
    
    return 0;
    
    
}

// function, in put is rows and colomn, output is draw all these model.


