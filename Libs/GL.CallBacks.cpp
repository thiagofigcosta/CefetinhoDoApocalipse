#include "GL.Callbacks.h"

bool glCallbacksReleaseMouseOffSet=false;//evita de definir o mouse solto no meio ou final da funcao update e o programa nao fazer a leitura

void drawScene(void){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    GL::drawRectangle(Util::nTRectangleSet(0,0,50,50,0,0),Util::nTColorSet(1,1,0,1));
    GL::setColorByName("black");
    GLuint te=GL::loadTexture("sa","Textures/minecraftterrain.png");
    GL::drawTexture(Util::nTRectangleSet(20,20,80,80,0,0),GL::getColor(),te,1);
    cout<<te<<endl;

    glutSwapBuffers();
}
void reshape(int width, int height){
    //TODO: colocar (0,0) do sistema de coordenadas no canto superior esquerdo
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, GL::defaultSize.x, 0, GL::defaultSize.y, -1, 1);
    float windowAspectRatio = ((float)width)/height;
    float worldAspectRatio = ((float) GL::defaultSize.x)/ GL::defaultSize.y;
    float xViewport,yViewport;
    if (windowAspectRatio < worldAspectRatio) {
        xViewport = width / worldAspectRatio;
        yViewport = (height - xViewport)/2;
        glViewport(0, yViewport, width, xViewport);
        GL::currentSize.x=width;
        GL::currentSize.y=xViewport-yViewport;
    }else if (windowAspectRatio > worldAspectRatio) {
        yViewport = ((float)height) * worldAspectRatio;
        xViewport = (width - yViewport)/2;
        glViewport(xViewport, 0, yViewport, height);
        GL::currentSize.x=height-xViewport;
        GL::currentSize.y=yViewport;
    } else {
        glViewport(0, 0, width, height);
        GL::currentSize.x=width;
        GL::currentSize.y=height;
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void keyboard(unsigned char key, int x, int y){
    //TODO:fazer acoes do teclado

}
Player *pl=new Player(5,2,2,Util::nTPointSet(50,30,0),Util::nTPointSet(20,60,0),NULL,1);
Mechanics *world=new Mechanics();
void update(int n){
    world->applyGravity();
    cout<<*pl;

    if(glCallbacksReleaseMouseOffSet){
        GL::leftMouseReleased=false;
        glCallbacksReleaseMouseOffSet=false;
    }
    if(GL::leftMouseReleased)glCallbacksReleaseMouseOffSet=true;
    glutPostRedisplay();
    glutTimerFunc(GL::getMs(), update, 0);
}
void mousePress(int button,int state,int x,int y){
    if(button==GLUT_LEFT_BUTTON){
        if(state==GLUT_DOWN){
            GL::leftMouseClicked=true;
            GL::leftMouseReleased=false;
          }
      if(state==GLUT_UP){
            GL::leftMouseClicked=false;
            GL::leftMouseReleased=true;
        }
    }
}
void mousePassiveMotion(int x,int y){
    //TODO:atualizar GL::mousePos com base nos tamanhos do mundo em GL
}
void mouseActiveMotion(int x,int y){
    //TODO:atualizar GL::mousePos com base nos tamanhos do mundo em GL
}
 
