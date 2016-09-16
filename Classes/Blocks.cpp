#include "Blocks.hpp"

Blocks::Blocks(int type,nTPoint pos,nTPoint size) {
    this->type=type;
    this->pos=pos;
    this->size=size;
    this->tex=getTextureByIndex();
    if(type>250&&type<=300){
        moveSpeed=150*((type-250)*0.6);
        this->size.y/=2;
    }
    if(type>200&&type<=250){
        moveSpeed=150*((type-200)*0.6);
        this->size.y/=2;
    }
    
}

Blocks::Blocks(const Blocks& orig) {
}

Blocks::~Blocks() {
}

nTPoint Blocks::defaultBlockSize=Util::nTPointSet(32,32,0);

GLuint Blocks::getTextureByIndex(){
    //TODO: verifica GL::textures pela textura certa do bloco
    if(this->type==1||this->type==326){
        return GL::getTextureByName("Pedra");
    }else if(this->type==2||this->type==327){
        return GL::getTextureByName("Terra");
    }else if(this->type==3){    
        return GL::getTextureByName("Grama");
    }else if(this->type==4){
        return GL::getTextureByName("Tronco Madeira");
    }else if(this->type==5||this->type==328){
        return GL::getTextureByName("Pedra Musgo");
    }else if(this->type==6||this->type==329){
        return GL::getTextureByName("Neve");
    }else if(this->type==7){
        return GL::getTextureByName("Grama neve");
    }else if(this->type==8){
        return GL::getTextureByName("Tijolo pedra musgo");
    }else if(this->type==9||this->type==330){
        return GL::getTextureByName("Arenito");
    }else if(this->type==10){
        return GL::getTextureByName("Ender portal");
    }else if(this->type==11||this->type==331){
        return GL::getTextureByName("Tijolo nether");
    }else if(this->type==12||this->type==332){
        return GL::getTextureByName("Tijolo areia");
    }else if(this->type==13||this->type==333){
        return GL::getTextureByName("Tijolo pedra");
    }else if(this->type==14||this->type==334){
        return GL::getTextureByName("Tijolo");
    }else if(this->type==15||this->type==335){
        return GL::getTextureByName("Madeira");
    }else if(this->type==16||this->type==336){
        return GL::getTextureByName("La ciano");
    }else if(this->type==17||this->type==337){
        return GL::getTextureByName("Gelo");
    }else
        
    //meio bloco    
    if(this->type==201||this->type==251){
        return GL::getTextureByName("Meio bloco pedra");
    }else if(this->type==202||this->type==252){
        return GL::getTextureByName("Meio bloco madeira");
    }else if(this->type==203||this->type==253){
        return GL::getTextureByName("Meio bloco arenito");
    }else if(this->type==204||this->type==254){
        return GL::getTextureByName("Meio bloco gelo");
    }else
        
    //spawn
    if(this->type==1000||(this->type>=2000&&this->type<=3000)||this->type>5000){
        return GL::getTextureByName("Spawn");
    }else
        
    //alavanca
    if(this->type>=451&&this->type<=475){
        return GL::getTextureByName("Alavanca");
    }else
    
        
    //baus
    if(this->type>=476&&this->type>=500){
        return GL::getTextureByName("Bau");
    }else
        
    //blocos que quebram    
    if(this->type==326){
        return GL::getTextureByName("Tijolo pedra quebrado");
    }else if(this->type==327){
        return GL::getTextureByName("Pedregulho");
    }else   
     
    //decorativos    
    if(this->type==401){
        return GL::getTextureByName("Cogumelos azuis");
    }else if(this->type==402){
        return GL::getTextureByName("Muda pinheiro");
    }else if(this->type==403){
        return GL::getTextureByName("Trigo");
    }else if(this->type==404){
        return GL::getTextureByName("Trigo2");
    }else if(this->type==405){
        return GL::getTextureByName("Muda seca");
    }else if(this->type==406){
        return GL::getTextureByName("Muda neve");
    }else{//air
        return 0;
    }
}

void Blocks::draw(){
    GL::drawTexture(Util::getCollisionRectangle(pos,size),Util::nTColorSet(1,1,1,1),tex,1);
    if(Util::DEBUG)
        cout<<"Block[id="<<type<<" pos(x="<<pos.x<<" y="<<pos.y<<"), size(x="<<size.x<<" y="<<size.y<<")]"<<endl;
}

void Blocks::move(int dir,float steeps){
    if(dir==Util::left||dir==Util::right){
      nTPoint tmp;
      tmp.setPoint(pos.x+steeps,pos.y,pos.z);
      if(Map::checkCollision(tmp,size)<3)
        pos=tmp;
      else
          moveSpeed*=-1;
    }else if(dir==Util::up){
      nTPoint tmp;
      tmp.setPoint(pos.x,pos.y-steeps,pos.z);
      if(Map::checkCollision(tmp,size)!=2)
        pos=tmp;
      else
          moveSpeed*=-1;
    }else if(dir==Util::down){
      nTPoint tmp;
      tmp.setPoint(pos.x,pos.y+steeps,pos.z);
      if(Map::checkCollision(tmp,size)!=1)
        pos=tmp;
      else
          moveSpeed*=-1;
    }
}

bool Blocks::checkIfBlocksIsDynamic(int id){
    bool out=false;
    if(id>200&&id<=350){
        out=true;
    }else if(id>376&&id<=400){
        out=true;
    }else if(id==1000){
        out=true;
    }else if(id>2000&&id<=3000){
        out=true;
    }else if(id>5000){
        out=true;
    }
    return out;
}

bool Blocks::checkIfBlocksIsMassive(int id){//ve se o bloco tem massa
    bool out=true;
    if(id==0){
        out=false;
    }else if(id>1000){
        out=false;
    }else if(id==1000){
        out=false;
    }else if(id>401&&id<=450){
        out=false;
    }
    return out;
}