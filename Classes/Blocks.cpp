#include "Blocks.hpp"

Blocks::Blocks(int type,nTPoint pos,nTPoint size) {
    this->type=type;
    this->pos=pos;
    this->size=size;
    this->tex=getTextureByIndex();
    if(type>250&&type<=300){
        moveSpeed=150*((type-250)*0.6);
        this->size.y/=2;
        this->pos.y-=size.y/4;
    }
    if(type>200&&type<=250){
        moveSpeed=150*((type-200)*0.6);
        this->size.y/=2;
        this->pos.y-=size.y/4;
    }  
}

Blocks::Blocks(const Blocks& orig) {
}

Blocks::~Blocks() {
}

nTPoint Blocks::defaultBlockSize=Util::nTPointSet(32,32,0);

GLuint Blocks::getTextureByIndex(){
    return GL::getTextureByName(getTexNameByIndex(this->type)); 
}

string Blocks::getTexNameByIndex(int BlockType){
    if(BlockType==1||BlockType==351){
        return string("Pedra");
    }else if(BlockType==2||BlockType==352){
        return string("Terra");
    }else if(BlockType==3){    
        return string("Grama");
    }else if(BlockType==4){
        return string("Tronco Madeira");
    }else if(BlockType==5||BlockType==353){
        return string("Pedra Musgo");
    }else if(BlockType==6||BlockType==354){
        return string("Neve");
    }else if(BlockType==7){
        return string("Grama neve");
    }else if(BlockType==8){
        return string("Tijolo pedra musgo");
    }else if(BlockType==9||BlockType==355){
        return string("Arenito");
    }else if(BlockType==10){
        return string("Ender portal");
    }else if(BlockType==11||BlockType==356){
        return string("Tijolo nether");
    }else if(BlockType==12||BlockType==357){
        return string("Tijolo areia");
    }else if(BlockType==13||BlockType==358){
        return string("Tijolo pedra");
    }else if(BlockType==14||BlockType==359){
        return string("Tijolo");
    }else if(BlockType==15||BlockType==360){
        return string("Madeira");
    }else if(BlockType==16||BlockType==361){
        return string("La ciano");
    }else if(BlockType==17||BlockType==362){
        return string("Gelo");
    }else if(BlockType==18){
        if(Scenes::current==Scenes::mapEdit)
            return string("block");
        return string("Invisivel");
    }else
        
    //meio bloco    
    if(BlockType==201||BlockType==251){
        return string("Meio bloco pedra");
    }else if(BlockType==202||BlockType==252){
        return string("Meio bloco madeira");
    }else if(BlockType==203||BlockType==253){
        return string("Meio bloco arenito");
    }else if(BlockType==204||BlockType==254){
        return string("Meio bloco gelo");
    }else
        
    //spawn
    if(BlockType==1000||(BlockType>=2000&&BlockType<=3000)||(BlockType>5000&&BlockType<60000)){
        return string("Spawn");
    }else
        
    //alavanca
    if(BlockType>=451&&BlockType<=475){
        return string("Alavanca");
    }else
    
        
    //baus
    if(BlockType>=476&&BlockType<=500){
        return string("Bau");
    }else
        
    //blocos que quebram    
    if(BlockType==326){
        return string("Tijolo pedra quebrado");
    }else if(BlockType==327){
        return string("Pedregulho");
    }else   
     
    //decorativos    
    if(BlockType==401){
        return string("Cogumelos azuis");
    }else if(BlockType==402){
        return string("Muda pinheiro");
    }else if(BlockType==403){
        return string("Trigo");
    }else if(BlockType==404){
        return string("Trigo2");
    }else if(BlockType==405){
        return string("Muda seca");
    }else if(BlockType==406){
        return string("Muda neve");
    }else{//air
        return string("");
    }
}

void Blocks::draw(){
    GL::drawTexture(Util::getCollisionRectangle(pos,size),Util::nTColorSet(1,1,1,1),tex,1);
}

void Blocks::move(int dir,float steeps){
    vector <mapCollision> var;
    bool condition=true;
    if(dir==Util::left||dir==Util::right){
      pos.setPoint(pos.x+steeps,pos.y,pos.z);
      var=Map::checkCollision(pos,size);
        for(int i=0; i<var.size(); i++){
          if(var[i].collision.firstObj>=3)
            condition=false;
        }
        if(!condition){
          pos.x-=steeps;
          moveSpeed*=-1;
          }

    }else if(dir==Util::up){
      pos.setPoint(pos.x,pos.y-steeps,pos.z);
      var=Map::checkCollision(pos,size);
      for(int i=0; i<var.size(); i++){
        if(var[i].collision.firstObj==2)
          condition=false;
      }
      if(!condition){
        pos.y+=steeps;
          moveSpeed*=-1;
        }
    }else if(dir==Util::down){
      pos.setPoint(pos.x,pos.y+steeps,pos.z);
      var=Map::checkCollision(pos,size);
      for(int i=0; i<var.size(); i++){
        if(var[i].collision.firstObj==1){
          condition=false;
        }
      }
      if(!condition){
        pos.y-=steeps;
          moveSpeed*=-1;
        }
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