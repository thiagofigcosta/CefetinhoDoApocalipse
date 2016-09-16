#include "GL.Callbacks.h"

bool glCallbacksReleaseMouseOffSet=false;//evita de definir o mouse solto no meio ou final da funcao update e o programa nao fazer a leitura

void drawScene(void){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    if(GL::framesInGame>=100000000000)
            GL::framesInGame=0;
    if(Scenes::current==Scenes::game)
        Scenes::drawGame();
    else if(Scenes::current==Scenes::mapEdit)
        Scenes::drawMapEdit();
    else if(Scenes::current==Scenes::menu)
        Scenes::drawMenu();
    
    GL::drawText(GL::mousePos,"0",GL::getColorByName("green"));
    glutSwapBuffers();
}
float windowAspectRatio,worldAspectRatio,xViewport,yViewport;
int WindowWidth,WindowHeight;
void reshape(int width, int height){
    WindowWidth=width;
    WindowHeight=height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, GL::defaultSize.x, GL::defaultSize.y, 0, -1, 1);
    windowAspectRatio = ((float)width)/height;
    worldAspectRatio = ((float) GL::defaultSize.x)/ GL::defaultSize.y;
    xViewport,yViewport;
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
        if(Scenes::current==Scenes::game&&!GL::isPaused){
            Tutorials::pressedKey=GLUT_KEY_UP;
            player->atackDirection=Util::up;//NAO PULA!!!
            player->jump();
            if((player->pos.y<GL::currentSize.y/2*1.11+Scenes::camera.y.movedCam)||Scenes::freeCam)//TODO:verificar se funciona
                 Scenes::camera.y.movingCam=-1;
        }else if(Scenes::current==Scenes::mapEdit)
            Scenes::camera.y.movingCam=-1;
    break;

    case GLUT_KEY_DOWN:
        if(Scenes::current==Scenes::game&&!GL::isPaused){
            Tutorials::pressedKey=GLUT_KEY_UP;
            player->atackDirection=Util::down;
            if((player->pos.y>GL::currentSize.y/3*0.99+Scenes::camera.y.movedCam)||Scenes::freeCam)//TODO:verificar se funciona
                 Scenes::camera.y.movingCam=1;
        }  else if(Scenes::current==Scenes::mapEdit)
            Scenes::camera.y.movingCam=1;  
      
    break;

    case GLUT_KEY_LEFT:
        if(Scenes::current==Scenes::game&&!GL::isPaused){
            Tutorials::pressedKey=GLUT_KEY_UP;
             player->atackDirection=Util::left;
             if(glutGetModifiers()==GLUT_ACTIVE_SHIFT)
                 player->run(Util::left);
             else
                player->walk(Util::left);
             if(((player->pos.x<GL::currentSize.x/2*0.99+Scenes::camera.x.movedCam)&&(Scenes::camera.x.movedCam>GL::defaultSize.x/2))||Scenes::freeCam)
                    Scenes::camera.x.movingCam=-1;
        }else if(Scenes::current==Scenes::mapEdit)
            Scenes::camera.x.movingCam=-1;
    break;

    case GLUT_KEY_RIGHT:
        if(Scenes::current==Scenes::game&&!GL::isPaused){
            Tutorials::pressedKey=GLUT_KEY_UP;
            player->atackDirection=Util::right;
            if(glutGetModifiers()==GLUT_ACTIVE_SHIFT)
                player->run(Util::right);
            else
                player->walk(Util::right);
            if((player->pos.x>GL::currentSize.x/2*1.11+Scenes::camera.x.movedCam)||Scenes::freeCam)
                 Scenes::camera.x.movingCam=1;
        }else if(Scenes::current==Scenes::mapEdit)
            Scenes::camera.x.movingCam=1;
      break;
}
}
void keyboard(unsigned char key, int x, int y){
    switch(key){
      case ' ':
        if(!GL::isPaused){
            player->vSpeed=Entity::jumpSpeed;
            Tutorials::pressedKey=' ';
        }
      break;

      case 'Z':
      case 'z':
          if(!GL::isPaused){
            Tutorials::pressedKey='z';
            player->atack(Player::melee);
          }
      break;

      case 'X':
      case 'x':
          if(!GL::isPaused){
            Tutorials::pressedKey='x';
            player->atack(Player::ranged);
          }
      break;
      
      case 27:
         if(!GL::isPaused){
            Tutorials::pressedKey=27;
         }
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
    switch(key){
        case '0':
              if(Scenes::current==Scenes::mapEdit)
                  mapEdit::input+=key;
        break;
        case '1':
              if(Scenes::current==Scenes::mapEdit)
                  mapEdit::input+=key;
        break;
        case '2':
              if(Scenes::current==Scenes::mapEdit)
                  mapEdit::input+=key;
        break;
        case '3':
              if(Scenes::current==Scenes::mapEdit)
                  mapEdit::input+=key;
        break;
        case '4':
              if(Scenes::current==Scenes::mapEdit)
                  mapEdit::input+=key;
        break;
        case '5':
              if(Scenes::current==Scenes::mapEdit)
                  mapEdit::input+=key;
        break;
        case '6':
              if(Scenes::current==Scenes::mapEdit)
                  mapEdit::input+=key;
        break;
        case '7':
              if(Scenes::current==Scenes::mapEdit)
                  mapEdit::input+=key;
        break;
        case '8':
              if(Scenes::current==Scenes::mapEdit)
                  mapEdit::input+=key;
        break;
        case '9':
              if(Scenes::current==Scenes::mapEdit)
                  mapEdit::input+=key;
        break;
        
        case 13://enter
            if(Scenes::current==Scenes::mapEdit){
                float tmp;
                istringstream (mapEdit::input) >> tmp;
                mapEdit::input="";
                if(tmp>=19&&tmp<65000&&(mapEdit::size.y==0||mapEdit::size.x==0)){
                    if(mapEdit::size.y==0){
                        mapEdit::size.y=tmp;
                    }else{
                        mapEdit::size.x=tmp;
                        mapEdit::setMapSize();
                    }
                }
            }
        break;
        
        case 8://backSpace
            if(Scenes::current==Scenes::mapEdit)
                if(mapEdit::input.size())
                    mapEdit::input.erase(mapEdit::input.begin()+mapEdit::input.size()-1);
        break;
    }
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
    
    if ((button == 3) || (button == 4)){
       if (state == GLUT_UP) return; // Disregard redundant GLUT_UP events
            
       }
}
void mousePassiveMotion(int x,int y){
    //TODO:atualizar GL::mousePos com base nos tamanhos do mundo em GL
   /*
    if (windowAspectRatio < worldAspectRatio) {
         GL::mousePos.x=x*(float)GL::defaultSize.x/(float)WindowWidth+Scenes::camera.x.movedCam;
         GL::mousePos.y=((xViewport)-(GL::defaultSize.y-y+yViewport-(GL::defaultSize.y-y)/xViewport))*(float)GL::defaultSize.y/(float)(xViewport-yViewport)*0.87+Scenes::camera.y.movedCam;
         cout<<"y:"<<y<<"xV"<<xViewport<<"   yV"<<yViewport<<"   result"<<GL::mousePos.y<<endl;
        //glViewport(0, yViewport, width, xViewport);
    }else if (windowAspectRatio > worldAspectRatio) {
         GL::mousePos.x=x*(float)GL::defaultSize.x/(float)(yViewport-xViewport)+Scenes::camera.x.movedCam;
         GL::mousePos.y=y*(float)GL::defaultSize.y/(float)WindowHeight+Scenes::camera.y.movedCam;
        //yViewport = ((float)height) * worldAspectRatio;
        //xViewport = (width - yViewport)/2;
        //glViewport(xViewport, 0, yViewport, height);
        //GL::currentSize.x=height-xViewport;
        //GL::currentSize.y=yViewport;
    }else{
         GL::mousePos.x=x*(float)GL::defaultSize.x/(float)GL::currentSize.x+Scenes::camera.x.movedCam;
        GL::mousePos.y=y*(float)GL::defaultSize.y/(float)GL::currentSize.y+Scenes::camera.y.movedCam;
    
    }*/
        GLdouble model[16];
        GLdouble proj[16]; 
        GLint view[4];       
        glGetDoublev(GL_MODELVIEW_MATRIX, model);
        glGetDoublev(GL_PROJECTION_MATRIX, proj);
        glGetIntegerv(GL_VIEWPORT, view);
        double tX=0,tY=0,tZ=0;
        int newY=view[3]-view[1]-y-view[1];
        int newX=x-view[0]*3;
        gluProject((double)newX, (double)newY, 0 , model, (const GLdouble*)proj, view, &tX,&tY,&tZ);     
        GL::mousePos.setPoint(tX+Scenes::camera.x.movedCam,tY+Scenes::camera.y.movedCam,tZ);
}
void mouseActiveMotion(int x,int y){
    //TODO:atualizar GL::mousePos com base nos tamanhos do mundo em GL
    GL::mousePos.x=x*(float)GL::defaultSize.x/(float)GL::currentSize.x;
    GL::mousePos.y=y*(float)GL::defaultSize.y/(float)GL::currentSize.y+Scenes::camera.y.movedCam;
}

void mouseWheel(int button, int dir, int x, int y){
    if (dir > 0){
        // Zoom in
        if(Scenes::current=Scenes::mapEdit){
            if(mapEdit::scale.x<0.99){
                mapEdit::scale.x+=0.01;
                mapEdit::scale.y+=0.01;
            }
        }            
    }else{
        // Zoom out
        if(Scenes::current=Scenes::mapEdit){
            if(mapEdit::scale.x>0.01){
                mapEdit::scale.x-=0.01;
                mapEdit::scale.y-=0.01;
            }
        }    
    }
}