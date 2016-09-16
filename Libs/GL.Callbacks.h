#ifndef GL  CALLBACKS_H
#define GLCALLBACKS_H
#include "../Classes/GL.hpp"
#include "../Classes/Util.hpp"
#include "../Classes/Player.hpp"

void drawScene(void);
void reshape(int width, int height);
void keyboard(unsigned char key, int x, int y);
void update(int n);
void mousePress(int button,int state,int x,int y);
void mousePassiveMotion(int x,int y);
void mouseActiveMotion(int x,int y);
#endif	// GL.CALLBACKS_H

