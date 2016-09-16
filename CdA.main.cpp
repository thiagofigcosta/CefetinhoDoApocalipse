#include <iostream>
#include <cstdlib>
#include <vector>
#include <string> 
#include "Classes/GL.h"
#include "Classes/AL.h"
#include "Classes/Util.h"
   
int main(int argc, char** argv) {
    nTColor clearColor;
    vector<GLenum> enables;
    
    AL *al=new AL();
    al->loadSound("test.wav","teste",1,true);
    al->playSoundByName("teste");
     
     
    clearColor.setColor(0,0,0,0);
    enables.push_back(GL_DEPTH_TEST);
    enables.push_back(GL_BLEND);
    
    GL *gl=new GL("Cefetinhos do Apocalipse",30,GLUT_DOUBLE | GLUT_RGBA|GLUT_DEPTH|GLUT_STENCIL|GLUT_ALPHA,
            800,600,clearColor,true,enables,argc,argv);
    gl->start();
    return 0;
}

