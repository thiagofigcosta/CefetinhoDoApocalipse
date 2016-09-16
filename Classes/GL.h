#ifndef GL_H
#define GL_H
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "../Libs/soil/SOIL.h"
#include "Util.h"
using namespace std;


    
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
    static void loadTexture(GLuint &tex,char* path);
    static void loadTextures(vector<GLuint> &tex,int nOfTex,char* path);
    static void drawRectangle(nTRectangle pos,nTColor color);
    static void drawTexture(nTRectangle pos,nTColor color,GLuint tex,int Orientation);
    static void setColorByName(string name);
    static void setFont(void* font);
    static void setFontByIndex(int idx);
    static void drawText(nTPoint point,char* text);
    static void drawPolygon(nTPoint point,float radius,int edges);
    void start();
private:
    static float FPS;
    static nTColor currentColor;
    static void* currentFont;
};
void drawScene(void);
void reshape(int width, int height);
void keyboard(unsigned char key, int x, int y);
void update(int n);
void mousePress(int button,int state,int x,int y);
void mousePassiveMotion(int x,int y);
void mouseActiveMotion(int x,int y);
#endif /* GL_H */

