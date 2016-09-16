#include "Tutorials.hpp"
#include "Scenes.hpp"


Tutorials::Tutorials(string text,int key){
  this->text=text;
  this->key=key;
  this->isCalled=true;
  this->isPaused=false;
  // this->draw();
  AL::playSoundByName("heyListen");
  pressedKey=0;
  GLlist=glGenLists(1);
};

Tutorials::Tutorials(const Tutorials& orig) {
}

Tutorials::~Tutorials() {
}
//string declarations:
  //ao iniciar o jogo(pela primeira vez?)
  string Tutorials::initHelp="Bem Vindo a sua vida academica!!!                 Eu represento o DECOM, vim para te ajudar em sua  jornada, para comecar, use as setas do teclado    para se orientar;";
  //ao aparecer(por completo?) o primeiro inimigo na tela   [zero=new Tutorials (Tutorials::atackHelp,'z');]
  string Tutorials::atackHelp="Em sua jornada voce precisara vencer diversas     materias e provas dificeis para prosseguir,       experimente segurar uma seta direcional e usar a  sua espada do poder para atacar nesta direcao,    utilizando a tecla [ Z ] ;";
  //ao aparecer(por completo?) o primeiro obstaculo no mapa [zero=new Tutorials (Tutorials::jumpHelp,' ');]
  string Tutorials::jumpHelp="Voce pode atacar em qualquer direcao enquanto     estiver no ar , para pular pressione [ ESPACO ] e para correr pressione [ SHIFT ] ;";
  //ao pegar o primeiro powerup                             [zero=new Tutorials (Tutorials::powerupHelp,' ');]
  string Tutorials::powerupHelp="Parabens! voce pegou o seu primeiro power-up,     power-ups sao ferramentas que auxiliam em seus    estudos, fortalecendo sua espada do poder,        facilitando bastante na hora de vencer as materias a frente, pressione [ ESPACO ] para continuar;";
  //ao atingir 75 de coeficiente                            [zero=new Tutorials (Tutorials::rangedAtkHelp,'x');]
  string Tutorials::rangedAtkHelp="Voce atingiu 75 em seu coeficiente de rendimento, o minimo necessario para usar seu ataque especial,pressione [ X ] para lancar uma poderosa onda de  poder em qualquer direcao;";
  //ao surgir o primeiro boss                               [zero=new Tutorials (Tutorials::bossHelp,' ');]
  string Tutorials::bossHelp="Cuidado! voce chegou ao primeiro boss, para       concluir o estagio atual,voce precisa vence-lo,   utilize todo seu poder para passar por este       desafio, pressione [ ESPACO ] para continuar;";
  //ao entrar para graduacao                                [zero=new Tutorials (Tutorials::gradHelp,' ');]
  string Tutorials::gradHelp="Checkpoint! Parabens! passando pelo ENEM voce     concluiu o tecnico e entrou para a graduacao,     outros desafios estao a frente, pressione         [ ESPACO ] para continuar;";
  //ao entrar para a pos graduacao                          [zero=new Tutorials (Tutorials::posHelp,' ');]
  string Tutorials::posHelp="Checkpoint! Parabens! ao concluir seu TCC voce    se formou e agora vai encarar a pos-graduacao,    pressione [ ESPACO ] para continuar;";
  //ao vencer o jogo                                        [zero=new Tutorials (Tutorials::winHelp,' ');]
  string Tutorials::winHelp="PARABENS!!! Voce concluiu a pos-graduacao,        vencendo este jogo, lembre-se: conhecimento e     poder!!! Pressione [ ESPACO ] ;";
//===================
bool Tutorials::showTutorials=true;
int Tutorials::pressedKey;
bool Tutorials::isPaused=false;

void Tutorials::drawWhispText(string text){
  GL::setFontByIndex(6);
  int maxChars=50;
  for(int i=0;i<text.size();i+=maxChars){
      GL::drawText(Util::nTPointSet(320+Scenes::camera.x.movedCam,Scenes::camera.y.movedCam+90+(i/maxChars)*25,0.99),(char*)(text.substr(i,maxChars)).c_str(),GL::getColorByName("yellow"));
      }
}
void Tutorials::draw(){
    if(GL::isPaused)
        return;
  if(showTutorials){
    if(isCalled){
      if(pressedKey!=key){
        isPaused=true;
        glNewList(GLlist,GL_COMPILE_AND_EXECUTE);
        GL::drawTexture((Util::nTRectangleSet(Scenes::camera.x.movedCam,
        300+Scenes::camera.y.movedCam,
        800+Scenes::camera.x.movedCam,
        Scenes::camera.y.movedCam,0.9,0.9)),
        Util::nTColorSet(1,1,1,1),
        GL::getTextureByName("Whisp"),1);
        drawWhispText(text);
        glEndList();
      }else{
        // cout<<"\n\npressed\n\n";
        isCalled=false;
        isPaused=false;
        pressedKey=0;
      }
    }
  }
}

void Tutorials::refresh(string text,int key){
  this->text=text;
  this->key=key;
  this->isCalled=true;
  // this->draw();
  AL::playSoundByName("heyListen");
  this->isPaused=true;
  pressedKey=0;
}