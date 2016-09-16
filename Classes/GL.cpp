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
    glutMouseWheelFunc(mouseWheel);
    Map::staticGLlist=glGenLists(1);
    Map::dynamicGLlist=glGenLists(1);
    Scenes::camera.setCam(10);
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
unsigned long int GL::framesInGame=0;
nTPoint GL::mousePos;
GLuint GL::GLlist=glGenLists(1);



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
    if(temp==0){
        if(Util::DEBUG) cout<<"falha ao carregar textura "<<Util::newPath(path)<<endl;
    }else{
        int i=0;
        for(string n:textureNames)
            if(n==name){
                textures[i]=temp;
                return temp;
            }else
                i++;
        textures.push_back(temp);
        textureNames.push_back(name);
    }
    return temp;
}
vector<GLuint> GL::loadTextures(string name,int nOfTex,char* path){
    vector<GLuint> tex;
    GLuint tmp;
    for(int i=0;i<nOfTex;i++){
        tmp=SOIL_load_OGL_texture(Util::newPath(Util::getDinamicPath(path,i,".png")),SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
        if(tmp){
            tex.push_back(NULL);
            tex[i]=tmp;
            textures.push_back(tex[i]);
            textureNames.push_back(Util::getDinamicPath((char*)name.c_str(),i,""));
        }else{if(Util::DEBUG)cout<<"erro em:"<<path<<endl;}
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
    glBindTexture(GL_TEXTURE_2D, tex);
    glBegin(GL_QUADS);
    if(Orientation<=0){
      glTexCoord2f(1, 1); glVertex3f(pos.p0.x, pos.p0.y, pos.p0.z);
      glTexCoord2f(0, 1); glVertex3f(pos.p1.x, pos.p0.y, pos.p0.z);
      glTexCoord2f(0, 0); glVertex3f(pos.p1.x, pos.p1.y, pos.p0.z);
      glTexCoord2f(1, 0); glVertex3f(pos.p0.x, pos.p1.y, pos.p0.z);
    }else{
      glTexCoord2f(0, 1); glVertex3f(pos.p0.x, pos.p0.y, pos.p0.z);
      glTexCoord2f(1, 1); glVertex3f(pos.p1.x, pos.p0.y, pos.p0.z);
      glTexCoord2f(1, 0); glVertex3f(pos.p1.x, pos.p1.y, pos.p0.z);
      glTexCoord2f(0, 0); glVertex3f(pos.p0.x, pos.p1.y, pos.p0.z);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
    setColor(tmp);
}
nTColor GL::getColorByName(string name){
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
  }else if(name=="white"){   
      R=1;G=1;B=1;
  }else if(name=="mouseSelected"){   
      R=0.3;G=0.3;B=0.3;
  }
  return Util::nTColorSet(R,G,B,1);
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
void GL::drawText(nTPoint point,char* text,nTColor color){
    nTColor tmp2=getColor();
    setColor(color);
    string tmp(text);
    glRasterPos3f(point.x,point.y,point.z);
    for (int i = 0;i<tmp.size();i++) {
       glutBitmapCharacter(currentFont, text[i]);
    }
    setColor(tmp2);
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

vector<GLuint> GL::getTexturesByName(string name,int nOfTex){
    vector<GLuint> out;
    GLuint tmp;
    for(int i=0;i<nOfTex;i++){
        tmp=getTextureByName(Util::getDinamicPath((char*)name.c_str(),i,""));
        if(tmp)
            out.push_back(tmp);
    }
    return out;
}
bool GL::buttonBehave(nTRectangle collision,nTColor pressedColor,GLuint tex,void(*clickFunction)(int,int),void(*releaseFunction)(int,int)){
    if(GL::mousePos.x>=collision.p0.x&&GL::mousePos.x<=collision.p1.x&&GL::mousePos.y>=collision.p0.y&&GL::mousePos.y<=collision.p1.y){
        if(tex)
            GL::drawTexture(collision,pressedColor,tex,1);
        else
            GL::drawRectangle(collision,pressedColor);
        if(GL::leftMouseClicked){
            if(*clickFunction!=NULL){
                clickFunction((int)GL::mousePos.x,(int)GL::mousePos.y);
            }        
            return true;
        }else if(GL::leftMouseReleased){
            if(*releaseFunction!=NULL){
                 releaseFunction((int)GL::mousePos.x,(int)GL::mousePos.y);
            }
            GL::leftMouseReleased=0;
            return true;
        }   
    }else{
        if(tex)
            GL::drawTexture(collision,GL::getColorByName("white"),tex,1);
    }
    return false;
}
ostream& operator<<(ostream &strm, const GL &gl) {
    if(Util::DEBUG)
        return strm <<"GL:["<<"FPS("<<gl.FPS<<"),"<<"CurrentColor("<<"R:"<<gl.currentColor.R<<" G:"<<gl.currentColor.G<<" B:"<<gl.currentColor.B<<" A:"<<gl.currentColor.A<<"),"<<
                "Loaded Texutres("<<gl.textures.size()<<"),"<<"ScreenSize("<<"x:"<<gl.currentSize.x<<" y:"<<gl.currentSize.y<<"),"<<"Is paused("<<gl.isPaused<<"),"<<"]\n";
    return strm;
}

void GL::drawPause(){
    glNewList(GLlist,GL_COMPILE_AND_EXECUTE);
    GL::setFontByIndex(6);
    string text="Pausado";
    int maxChars=50;
    for(int i=0;i<text.size();i+=maxChars){
        GL::drawTexture((Util::nTRectangleSet(
        300+Scenes::camera.x.movedCam,
        260+Scenes::camera.y.movedCam,
        500+Scenes::camera.x.movedCam,
        320+Scenes::camera.y.movedCam,0.95,0.95)),
        Util::nTColorSet(1,1,1,1),
        GL::getTextureByName("Ballon"),1);
        GL::drawText(Util::nTPointSet(360+Scenes::camera.x.movedCam,Scenes::camera.y.movedCam+300+(i/maxChars)*25,1),(char*)(text.substr(i,maxChars)).c_str(),GL::getColorByName("violet"));
    }
    glEndList();
}