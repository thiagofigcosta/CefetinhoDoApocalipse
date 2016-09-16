#include "GL.hpp"
#include "../Libs/GL.Callbacks.h"

GL::GL(string name,float FPS,GLbitfield displayMode,int windowXsize,int windowYsize,nTColor clearcolor,bool blend,vector<GLenum>&enables,int argc, char** argv) {
    this->FPS=FPS;
    glutInit(&argc, argv);
    glutInitDisplayMode(displayMode);
    glutInitWindowSize(windowXsize, windowYsize);
    defaultSize.setPoint(windowXsize,windowYsize,0);
    currentSize=defaultSize;
    glutInitWindowPosition(0, 0);
    glutCreateWindow(name.c_str());
    glClearColor(clearcolor.R, clearcolor.G, clearcolor.B, clearcolor.A);
    for(GLenum en:enables)
        glEnable(en);
    if(blend)
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glutSpecialUpFunc(specialKeyboardUp);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(specialKeyboard);
    glutDisplayFunc(drawScene);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, update, -1);
    glutPassiveMotionFunc(mousePassiveMotion);
    glutMotionFunc(mouseActiveMotion);
    glutMouseFunc(mousePress);
};

GL::GL(const GL& orig) {
}

GL::~GL() {
}

float GL::FPS;
nTColor GL::currentColor=Util::nTColorSet(1,1,1,1);
void* GL::currentFont=GLUT_BITMAP_TIMES_ROMAN_24;
vector<GLuint> GL::textures;
vector<string> GL::textureNames;
nTPoint GL::defaultSize;
nTPoint GL::currentSize;
bool GL::isPaused=false;
bool GL::leftMouseClicked=false;
bool GL::leftMouseReleased=false;
nTPoint GL::mousePos;

void GL::setFPS(float FPS){
    GL::FPS=FPS;
}
float GL::getFPS(){
    return FPS;
}
float GL::getMs(){
    return 1000/FPS;
}
void GL::start(){
    glutMainLoop();
}
GLuint GL::loadTexture(string name,char* path){
    GLuint temp=SOIL_load_OGL_texture(Util::newPath(path),SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    textures.push_back(temp);
    textureNames.push_back(name);
    return temp;
}
vector<GLuint> GL::loadTextures(string name,int nOfTex,char* path){
    vector<GLuint> tex;
    for(int i=0;i<nOfTex;i++){
        tex.push_back(NULL);
        tex[i]=SOIL_load_OGL_texture(Util::newPath(Util::getDinamicPath(path,i,".png")),SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
        textures.push_back(tex[i]);
        textureNames.push_back(Util::getDinamicPath((char*)name.c_str(),i,""));
    }
    return tex;
}
void GL::setColor(nTColor color){
    GL::currentColor=color;
    glColor4f(color.R,color.G,color.B,color.A);
}
nTColor GL::getColor(){
    return GL::currentColor;
}
void GL::drawRectangle(nTRectangle pos,nTColor color){
    nTColor tmp=getColor();
    setColor(color);
    glBegin(GL_POLYGON);
        glVertex3f(pos.p0.x, pos.p0.y, pos.p0.z);
        glVertex3f(pos.p1.x, pos.p0.y, pos.p0.z);
        glVertex3f(pos.p1.x, pos.p1.y, pos.p0.z);
        glVertex3f(pos.p0.x, pos.p1.y, pos.p0.z);
    glEnd();
    setColor(tmp);
}
void GL::drawTexture(nTRectangle pos,nTColor color,GLuint tex,int Orientation){
    nTColor tmp=getColor();
    setColor(color);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_ALPHA_TEST);
    glBindTexture(GL_TEXTURE_2D, tex);
    glBegin(GL_QUADS);
    if(Orientation<0){
      glTexCoord2f(1, 0); (pos.p0.x, pos.p0.y, pos.p0.z);
      glTexCoord2f(0, 0); (pos.p1.x, pos.p0.y, pos.p0.z);
      glTexCoord2f(0, 1); (pos.p1.x, pos.p1.y, pos.p0.z);
      glTexCoord2f(1, 1); (pos.p0.x, pos.p1.y, pos.p0.z);
    }else{
      glTexCoord2f(0, 0); (pos.p0.x, pos.p0.y, pos.p0.z);
      glTexCoord2f(1, 0); (pos.p1.x, pos.p0.y, pos.p0.z);
      glTexCoord2f(1, 1); (pos.p1.x, pos.p1.y, pos.p0.z);
      glTexCoord2f(0, 1); (pos.p0.x, pos.p1.y, pos.p0.z);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_ALPHA_TEST);
    setColor(tmp);
}
void GL::setColorByName(string name){
  float R=1,G=1,B=1;
  if(name=="black"){
      R=0;G=0;B=0;
  }else if(name=="red"){
      R=1;G=0;B=0;
  }else if(name=="green"){
      R=0;G=1;B=0;
  }else if(name=="blue"){
      R=0;G=0;B=1;
  }else if(name=="yellow"){
      R=1;G=1;B=0;
  }else if(name=="magenta"){
      R=1;G=0;B=1;
  }else if(name=="cyan"){
      R=0;G=1;B=1;
  }else if(name=="grey"){
      R=0.6;G=0.6;B=0.6;
  }else if(name=="violet"){   //mish 153,112,205 ou 99,70,CD
      R=0.6;G=0.4392156;B=0.80392156;
  }
  setColor(Util::nTColorSet(R,G,B,1));
}
void GL::setFont(void* font){
    currentFont=font;
}
void GL::setFontByIndex(int idx){
    switch(idx){
        default:
            setFont(GLUT_BITMAP_TIMES_ROMAN_24);
        break;
        case 1:
            setFont(GLUT_BITMAP_8_BY_13);
        break;
        case 2:
            setFont(GLUT_BITMAP_9_BY_15);
        break;
        case 3:
            setFont(GLUT_BITMAP_TIMES_ROMAN_10);
        break;
        case 4:
            setFont(GLUT_BITMAP_HELVETICA_10);
        break;
        case 5:
            setFont(GLUT_BITMAP_HELVETICA_12);
        break;
        case 6:
            setFont(GLUT_BITMAP_HELVETICA_18);
        break;
    }
}
void GL::drawText(nTPoint point,char* text){
    string tmp(text);
    glRasterPos3f(point.x,point.y,point.z);
    for (int i = 0;i<tmp.size();i++) {
       glutBitmapCharacter(currentFont, text[i]);
    }
}
void GL::drawPolygon(nTPoint point,float radius,int edges){
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(point.x,point.y,point.z);
    for(int i=0;i<=edges;i++){
        glVertex3f(cos(2*M_PI*i/edges)*radius+point.x,sin(2*M_PI*i/edges)*radius+point.y,point.z);
    }
    glEnd();
}
GLuint GL::getTextureByName(string name){
    int i=0;
    for(string n:textureNames)
        if(n==name){
            return textures[i];
        }else
            i++;
    return 0;
}
bool GL::buttonBehave(nTRectangle collision,nTColor pressedColor,GLuint tex,void*clickFunction(void),void*releaseFunction(void)){
    //TODO: fazer funcao do botao, antes de chamar as funcoes de click e release do botao verificar se elas sao NULL
}
ostream& operator<<(ostream &strm, const GL &gl) {
    if(Util::DEBUG)
        return strm <<"GL:["<<"FPS("<<gl.FPS<<"),"<<"CurrentColor("<<"R:"<<gl.currentColor.R<<" G:"<<gl.currentColor.G<<" B:"<<gl.currentColor.B<<" A:"<<gl.currentColor.A<<"),"<<
                "Loaded Texutres("<<gl.textures.size()<<"),"<<"ScreenSize("<<"x:"<<gl.currentSize.x<<" y:"<<gl.currentSize.y<<"),"<<"Is paused("<<gl.isPaused<<"),"<<"]\n";
    return strm;
}
