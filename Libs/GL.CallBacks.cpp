#include "GL.Callbacks.h"

bool glCallbacksReleaseMouseOffSet=false;//evita de definir o mouse solto no meio ou final da funcao update e o programa nao fazer a leitura

void drawScene(void){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    if(Scenes::current==Scenes::game)
        Scenes::drawGame();
    
    glutSwapBuffers();
}
void reshape(int width, int height){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, GL::defaultSize.x, GL::defaultSize.y, 0, -1, 1);
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

void specialKeyboard(int key, int x, int y){
  switch(key)
  {
    case GLUT_KEY_UP:
        if(Scenes::current==Scenes::game){
            player->atackDirection=Util::up;//NAO PULA!!!
            player->jump();
            if(player->pos.y<GL::currentSize.y/2*1.11+Scenes::camera.y.movedCam)//TODO:verificar se funciona
                 Scenes::camera.y.movingCam=-1;
        }
    break;

    case GLUT_KEY_DOWN:
        if(Scenes::current==Scenes::game){
            player->atackDirection=Util::down;
            if(player->pos.y>GL::currentSize.y/3*0.99+Scenes::camera.y.movedCam)//TODO:verificar se funciona
                 Scenes::camera.y.movingCam=1;
        }    
      
    break;

    case GLUT_KEY_LEFT:
        if(Scenes::current==Scenes::game){
             player->atackDirection=Util::left;
             if(glutGetModifiers()==GLUT_ACTIVE_SHIFT)
                 player->run(Util::left);
             else
                player->walk(Util::left);
             if(player->pos.x<GL::currentSize.x/2*0.99+Scenes::camera.x.movedCam)
                 Scenes::camera.x.movingCam=-1;
        }
    break;

    case GLUT_KEY_RIGHT:
        if(Scenes::current==Scenes::game){
            player->atackDirection=Util::right;
            if(glutGetModifiers()==GLUT_ACTIVE_SHIFT)
                player->run(Util::right);
            else
                player->walk(Util::right);
            if(player->pos.x>GL::currentSize.x/2*1.11+Scenes::camera.x.movedCam)
                 Scenes::camera.x.movingCam=1;
        }
      break;
}
}
void keyboard(unsigned char key, int x, int y){
    switch(key){
      case ' ':
        player->vSpeed=Entity::jumpSpeed;
      break;

      case 'Z':
      case 'z':
        player->atack(Player::melee);
      break;

      case 'X':
      case 'x':
        player->atack(Player::ranged);
      break;

      case 27:
        GL::isPaused=!GL::isPaused;
      break;

      default:break;
    }
}

void specialKeyboardUp(int key,int x,int y){
  switch(key)
  {
    case GLUT_KEY_UP:
      player->atackDirection=player->orientation;//NAO PULA!!!
    Scenes::camera.y.movingCam=0;
    break;

    case GLUT_KEY_DOWN:
      player->atackDirection=player->orientation;
      Scenes::camera.y.movingCam=0;
    break;

    case GLUT_KEY_LEFT:
      player->atackDirection=player->orientation;
      Scenes::camera.x.movingCam=0;
      if(player->hSpeed>Entity::maxRunSpeed&&player->hSpeed<0)
          player->hSpeed=0;
      else
          player->hSpeed+=Entity::maxRunSpeed;
    break;

    case GLUT_KEY_RIGHT:
      player->atackDirection=player->orientation;
      Scenes::camera.x.movingCam=0;
      if(player->hSpeed<Entity::maxRunSpeed&&player->hSpeed>0)
          player->hSpeed=0;
      else
          player->hSpeed-=Entity::maxRunSpeed;
    break;

    default:
    break;
  }
}
void keyboardUp(unsigned char key,int x,int y){

}

void update(int n){
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
