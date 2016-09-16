#ifndef GL_H
#define GL_H
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "../Libs/soil/SOIL.h"
#include "Util.hpp"

class GL {
public:
    GL(string name,float FPS,GLbitfield displayMode,int windowXsize,int windowYsize,nTColor clearcolor,bool blend,vector<GLenum>&enables,int argc, char** argv);
    GL(const GL& orig);
    virtual ~GL();
    static void setFPS(float FPS);
    static float getFPS();
    static float getMs();
    static void setColor(nTColor color);
    static nTColor getColor();
    static GLuint loadTexture(string name,char* path);
    static vector<GLuint> loadTextures(string name,int nOfTex,char* path);
    static void drawRectangle(nTRectangle pos,nTColor color);
    static void drawTexture(nTRectangle pos,nTColor color,GLuint tex,int Orientation);
    static void setColorByName(string name);
    static void setFont(void* font);
    static void setFontByIndex(int idx);
    static void drawText(nTPoint point,char* text);
    static void drawPolygon(nTPoint point,float radius,int edges);
    static GLuint getTextureByName(string name);
    static bool isPaused;
    static bool buttonBehave(nTRectangle collision,nTColor pressedColor,GLuint tex,void*clickFunction(void),void*releaseFunction(void));
    static nTPoint defaultSize;
    static nTPoint currentSize;
    static bool leftMouseClicked;
    static bool leftMouseReleased;
    static nTPoint mousePos;
    static vector<GLuint> textures;
    void start();
private:
    friend ostream& operator<<(ostream &strm, const GL &gl);
    static float FPS;
    static nTColor currentColor;
    static void* currentFont;
    static vector<string> textureNames;
};
void drawScene(void);
void reshape(int width, int height);
void keyboard(unsigned char key, int x, int y);
void update(int n);
void mousePress(int button,int state,int x,int y);
void mousePassiveMotion(int x,int y);
void mouseActiveMotion(int x,int y);
#endif /* GL_H */
