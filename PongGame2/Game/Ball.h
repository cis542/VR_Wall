#ifndef BALL_H
#define BALL_H

#include <string>
#include <vector>
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <glload/gl_3_3.h>
#include <GL/freeglut.h>
#include "../framework/framework.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Ball{

    glm::vec3 velocity;
    glm::vec3 position;

public: 

    Ball(glm::vec3 v, glm::vec3 p);

    ~Ball();

    //Set the velocity of the ball
    void setVelocity(glm::vec3& vel);
    //Update the position vector. Returns the position vector
    glm::vec3 updatePosition(float dt);
    //Returns the current position vector
    glm::vec3 getPosition () const;
    //Returns current velocity vector
    glm::vec3 getVelocity () const;

    //Calulate the perspective frustrum scale for calculation in the perspective matrix
    float CalcFrustumScaleBall(float fFovDeg);
    //Performs operations like loading the required fragment and vertex shaders in the program variable for compilation,
    //calculatig the perspective matrix
    void  InitializeProgramBall();
    //Initialize the buffer objects for the vertex  and index data
    void  InitializeVertexBuffer();

    //Initialize the shader program, generate the data buffers for the shader, enable the vertex attrib array for the vertex and color data
    void  initBall();
    //Create and draw an instance of the Ball
    void  displayBall();
    //OpenGL Window reshape function
    void  reshapeBall (int w, int h);
    //OpenGL Keyboard function
    void  keyboardBall(unsigned char key, int x, int y);
    //OpenGL Mouse function
    void  mouse_funcBall(int x,int y);

};

#endif //BALL_H
