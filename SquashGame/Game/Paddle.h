#ifndef PADDLE_H
#define PADDLE_H

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

class Paddle{

public: 

     Paddle();

    ~Paddle();


     //Calulate the perspective frustrum scale for calculation in the perspective matrix
    float CalcFrustumScalePaddle(float fFovDeg);
    //Performs operations like loading the required fragment and vertex shaders in the program variable for compilation,
    //calculatig the perspective matrix
    void  InitializeProgramPaddle();
    //Initialize the buffer objects for the vertex  and index data
    void  InitializeVertexBuffer();

    //Initialize the shader program, generate the data buffers for the shader, enable the vertex attrib array for the vertex and color data
    void  initPaddle();
    //Create and draw an instance of the Ball
    void  displayPaddle();
    //OpenGL Window reshape function
    void  reshapePaddle (int w, int h);
    //OpenGL Keyboard function
    void  keyboardPaddle(unsigned char key, int x, int y);
    //OpenGL Mouse function
    void  mouse_funcPaddle(int x,int y);

};

#endif //PADDLE_H
