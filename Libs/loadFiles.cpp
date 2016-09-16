#include "loadFiles.h"

bool loadTextures(){
    bool out = true;
    GL::loadTexture("paraboloide hiperbolico<3","Textures/paraboloideHiperbolico.png");//n precisa de if
    //HUD
    if(!GL::loadTexture("Ballon","Textures/HUD/defaultBallon.png")) out=false;
    if(!GL::loadTexture("Whisp","Textures/HUD/Tutorials/whisp.png")) out=false;
    if(!GL::loadTexture("-","Textures/HUD/Buttons/arrowMinus.png")) out=false;
    if(!GL::loadTexture("+","Textures/HUD/Buttons/arrowPlus.png")) out=false;
    if(!GL::loadTexture("CameraDefault","Textures/HUD/Buttons/camera.png")) out=false;
    if(!GL::loadTexture("Back","Textures/HUD/Buttons/back.png")) out=false;
    if(!GL::loadTexture("Zoom-","Textures/HUD/Buttons/lupa-.png")) out=false;
    if(!GL::loadTexture("Zoom+","Textures/HUD/Buttons/lupa+.png")) out=false;
    if(!GL::loadTexture("Background-","Textures/HUD/Buttons/background-.png")) out=false;
    if(!GL::loadTexture("Background+","Textures/HUD/Buttons/background+.png")) out=false;
    if(!GL::loadTexture("Save","Textures/HUD/Buttons/save.png")) out=false;    
    if(!GL::loadTexture("Get Block","Textures/HUD/Buttons/getBlock.png")) out=false;
    if(!GL::loadTexture("decomCelebrations","Textures/logo/GameLogo.png")) out=false;
    if(!GL::loadTexture("theCOM","Textures/logo/thecom.png")) out=false;
    if(!GL::loadTexture("cefetLogo","Textures/logo/cefet.png")) out=false;
    if(!GL::loadTexture("decomLogo","Textures/logo/decom.png")) out=false;
    if(!GL::loadTexture("legendsLogo","Textures/logo/mainLogo.png")) out=false;
    if(!GL::loadTexture("optionsIcon","Textures/HUD/Buttons/options.png")) out=false;
    if(!GL::loadTexture("quitIcon","Textures/HUD/Buttons/quit.png")) out=false;
    if(!GL::loadTexture("playIcon","Textures/HUD/Buttons/play.png")) out=false;
    if(!GL::loadTexture("mapEditIcon","Textures/HUD/Buttons/mapEdit.png")) out=false;
    if(!GL::loadTexture("optionsIcon","Textures/HUD/Buttons/options.png")) out=false;
    
    //blocos fisicos
    if(!GL::loadTexture("Pedra","Textures/blocks/2.png")) out=false;
    if(!GL::loadTexture("Terra","Textures/blocks/3.png"))out=false;
    if(!GL::loadTexture("Grama","Textures/blocks/4.png"))out=false;
    if(!GL::loadTexture("Tronco Madeira","Textures/blocks/21.png"))out=false;
    if(!GL::loadTexture("Pedra Musgo","Textures/blocks/37.png"))out=false;
    if(!GL::loadTexture("Neve","Textures/blocks/66.png"))out=false;
    if(!GL::loadTexture("Grama neve","Textures/blocks/68.png"))out=false;
    if(!GL::loadTexture("Tijolo pedra musgo","Textures/blocks/100.png"))out=false;
    if(!GL::loadTexture("Arenito","Textures/blocks/179.png"))out=false;
    if(!GL::loadTexture("Ender portal","Textures/blocks/180.png"))out=false;
    if(!GL::loadTexture("Tijolo nether","Textures/blocks/185.png"))out=false;
    if(!GL::loadTexture("Tijolo areia","Textures/blocks/190.png"))out=false;
    if(!GL::loadTexture("Tijolo pedra","Textures/blocks/54.png"))out=false;
    if(!GL::loadTexture("Tijolo","Textures/blocks/8.png"))out=false;
    if(!GL::loadTexture("Madeira","Textures/blocks/5.png"))out=false;
    if(!GL::loadTexture("La ciano","Textures/blocks/169.png"))out=false;
    if(!GL::loadTexture("Gelo","Textures/blocks/67.png"))out=false;
    if(!GL::loadTexture("Invisivel","Textures/blocks/-1.png"))out=false;
    if(!GL::loadTexture("block","Textures/blocks/215.png"))out=false;
    
    //blocos que movem   
    if(!GL::loadTexture("Meio bloco pedra","Textures/blocks/211.png"))out=false;
    if(!GL::loadTexture("Meio bloco madeira","Textures/blocks/212.png"))out=false;
    if(!GL::loadTexture("Meio bloco arenito","Textures/blocks/213.png"))out=false;
    if(!GL::loadTexture("Meio bloco gelo","Textures/blocks/214.png"))out=false;
    
    //blocos que quebram
    if(!GL::loadTexture("Tijolo pedra quebrado","Textures/blocks/101.png"))out=false;
    if(!GL::loadTexture("Pedregulho","Textures/blocks/17.png"))out=false;
    
    //baus
    if(!GL::loadTexture("Bau","Textures/blocks/28.png"))out=false;
    
   //blocos especiais
    if(!GL::loadTexture("Spawn","Textures/blocks/65.png"))out=false;
    if(!GL::loadTexture("Alavanca","Textures/blocks/96.png"))out=false;
    if(!GL::loadTexture("Ar","Textures/blocks/216.png"))out=false;

    
   //blocos decorativos
    if(!GL::loadTexture("Cogumelos azuis","Textures/blocks/29.png"))out=false;
    if(!GL::loadTexture("Muda pinheiro","Textures/blocks/63.png"))out=false;
    if(!GL::loadTexture("Trigo","Textures/blocks/94.png"))out=false;
    if(!GL::loadTexture("Trigo2","Textures/blocks/95.png"))out=false;
    if(!GL::loadTexture("Muda seca","Textures/blocks/55.png"))out=false;
    if(!GL::loadTexture("Muda neve","Textures/blocks/111.png"))out=false;
    
    //backgrounds
    if((GL::loadTextures("background",2,"Textures/backgrounds/")).size()!=2)out=false;

    
    //Player
    //Air
    if((GL::loadTextures("cefetinhoAtkMeleeAirDown",1,"Textures/characters/cefetinho/atack/melee/air/down/")).size()!=1)out=false;
        if((GL::loadTextures("cefetinhoAtkMeleeAirFront",1,"Textures/characters/cefetinho/atack/melee/air/front/")).size()!=1)out=false;
        if((GL::loadTextures("cefetinhoAtkMeleeAirUp",1,"Textures/characters/cefetinho/atack/melee/air/up/")).size()!=1)out=false;
      //ground
        if((GL::loadTextures("cefetinhoAtkMeleeGroundFront",1,"Textures/characters/cefetinho/atack/melee/ground/front/")).size()!=1)out=false;
        if((GL::loadTextures("cefetinhoAtkMeleeGroundUp",1,"Textures/characters/cefetinho/atack/melee/ground/up/")).size()!=1)out=false;
    //ranged
      //air
        if((GL::loadTextures("cefetinhoAtkRangedAirDown",1,"Textures/characters/cefetinho/atack/ranged/air/down/")).size()!=1)out=false;
        if((GL::loadTextures("cefetinhoAtkRangedAirFront",1,"Textures/characters/cefetinho/atack/ranged/air/front/")).size()!=1)out=false;
        if((GL::loadTextures("cefetinhoAtkRangedAirUp",1,"Textures/characters/cefetinho/atack/ranged/air/up/")).size()!=1)out=false;
      //ground
        if((GL::loadTextures("cefetinhoAtkRangedGroundFront",4,"Textures/characters/cefetinho/atack/ranged/ground/front/")).size()!=4)out=false;
        if((GL::loadTextures("cefetinhoAtkRangedGroundUp",1,"Textures/characters/cefetinho/atack/ranged/ground/up/")).size()!=1)out=false;
          //damage
            if((GL::loadTextures("cefetinhoDmgAir",1,"Textures/characters/cefetinho/damage/air/")).size()!=1)out=false;
            if((GL::loadTextures("cefetinhoDmgGround",1,"Textures/characters/cefetinho/damage/ground/")).size()!=1)out=false;
          if((GL::loadTextures("cefetinhoDie",4,"Textures/characters/cefetinho/die/")).size()!=4)out=false;
          if((GL::loadTextures("cefetinhoIdle",5,"Textures/characters/cefetinho/idle/")).size()!=5)out=false;
          if((GL::loadTextures("cefetinhoJump",1,"Textures/characters/cefetinho/jump/")).size()!=1)out=false;
          //move
            if((GL::loadTextures("cefetinhoMoveRun",4,"Textures/characters/cefetinho/move/run/")).size()!=4)out=false;
            if((GL::loadTextures("cefetinhoMoveWalk",4,"Textures/characters/cefetinho/move/walk/")).size()!=4)out=false;
          if((GL::loadTextures("cefetinhoSpawn",7,"Textures/characters/cefetinho/spawn/")).size()!=7)out=false;
        //graduacao
          //atack
            //melee
              //air
                if((GL::loadTextures("graduacaoAtkMeleeAirDown",1,"Textures/characters/graduacao/atack/melee/air/down/")).size()!=1)out=false;
                if((GL::loadTextures("graduacaoAtkMeleeAirFront",1,"Textures/characters/graduacao/atack/melee/air/front/")).size()!=1)out=false;
                if((GL::loadTextures("graduacaoAtkMeleeAirUp",1,"Textures/characters/graduacao/atack/melee/air/up/")).size()!=1)out=false;
              //ground
                if((GL::loadTextures("graduacaoAtkMeleeGroundFront",1,"Textures/characters/graduacao/atack/melee/ground/front/")).size()!=1)out=false;
                if((GL::loadTextures("graduacaoAtkMeleeGroundUp",1,"Textures/characters/graduacao/atack/melee/ground/up/")).size()!=1)out=false;
            //ranged
              //air
                if((GL::loadTextures("graduacaoAtkRangedAirDown",1,"Textures/characters/graduacao/atack/ranged/air/down/")).size()!=1)out=false;
                if((GL::loadTextures("graduacaoAtkRangedAirFront",1,"Textures/characters/graduacao/atack/ranged/air/front/")).size()!=1)out=false;
                if((GL::loadTextures("graduacaoAtkRangedAirUp",1,"Textures/characters/graduacao/atack/ranged/air/up/")).size()!=1)out=false;
              //ground
                if((GL::loadTextures("posgradAtkRangedGroundFront",4,"Textures/characters/graduacao/atack/ranged/ground/front/")).size()!=4)out=false;
                if((GL::loadTextures("posgradAtkRangedGroundUp",1,"Textures/characters/graduacao/atack/ranged/ground/up/")).size()!=1)out=false;
          //damage
            if((GL::loadTextures("graduacaoDmgAir",1,"Textures/characters/graduacao/damage/air/")).size()!=1)out=false;
            if((GL::loadTextures("graduacaoDmgGround",1,"Textures/characters/graduacao/damage/ground/")).size()!=1)out=false;
          if((GL::loadTextures("graduacaoDie",4,"Textures/characters/graduacao/die/")).size()!=4)out=false;
          if((GL::loadTextures("graduacaoIdle",5,"Textures/characters/graduacao/idle/")).size()!=5)out=false;
          if((GL::loadTextures("graduacaoJump",1,"Textures/characters/graduacao/jump/")).size()!=1)out=false;
          //move
            if((GL::loadTextures("graduacaoMoveRun",4,"Textures/characters/graduacao/move/run/")).size()!=4)out=false;
            if((GL::loadTextures("graduacaoMoveWalk",4,"Textures/characters/graduacao/move/walk/")).size()!=4)out=false;
          if((GL::loadTextures("graduacaoSpawn",7,"Textures/characters/graduacao/spawn/")).size()!=7)out=false;
        //posgrad
        //atack
          //melee
            //air
              if((GL::loadTextures("posgradAtkMeleeAirDown",1,"Textures/characters/posgrad/atack/melee/air/down/")).size()!=1)out=false;
              if((GL::loadTextures("posgradAtkMeleeAirFront",1,"Textures/characters/posgrad/atack/melee/air/front/")).size()!=1)out=false;
              if((GL::loadTextures("posgradAtkMeleeAirUp",1,"Textures/characters/posgrad/atack/melee/air/up/")).size()!=1)out=false;
            //ground
              if((GL::loadTextures("posgradAtkMeleeGroundFront",1,"Textures/characters/posgrad/atack/melee/ground/front/")).size()!=1)out=false;
              if((GL::loadTextures("posgradAtkMeleeGroundUp",1,"Textures/characters/posgrad/atack/melee/ground/up/")).size()!=1)out=false;
          //ranged
            //air
              if((GL::loadTextures("posgradAtkRangedAirDown",1,"Textures/characters/posgrad/atack/ranged/air/down/")).size()!=1)out=false;
              if((GL::loadTextures("posgradAtkRangedAirFront",1,"Textures/characters/posgrad/atack/ranged/air/front/")).size()!=1)out=false;
              if((GL::loadTextures("posgradAtkRangedAirUp",1,"Textures/characters/posgrad/atack/ranged/air/up/")).size()!=1)out=false;
            //ground
              if((GL::loadTextures("posgradAtkRangedGroundFront",4,"Textures/characters/posgrad/atack/ranged/ground/front/")).size()!=4)out=false;
              if((GL::loadTextures("posgradAtkRangedGroundUp",1,"Textures/characters/posgrad/atack/ranged/ground/up/")).size()!=1)out=false;
        //damage
          if((GL::loadTextures("posgradDmgAir",1,"Textures/characters/posgrad/damage/air/")).size()!=1)out=false;
          if((GL::loadTextures("posgradDmgGround",1,"Textures/characters/posgrad/damage/ground/")).size()!=1)out=false;
        if((GL::loadTextures("posgradDie",4,"Textures/characters/posgrad/die/")).size()!=4)out=false;
        if((GL::loadTextures("posgradIdle",5,"Textures/characters/posgrad/idle/")).size()!=5)out=false;
        if((GL::loadTextures("posgradJump",1,"Textures/characters/posgrad/jump/")).size()!=1)out=false;
        //move
          if((GL::loadTextures("posgradMoveRun",4,"Textures/characters/posgrad/move/run/")).size()!=4)out=false;
          if((GL::loadTextures("posgradMoveWalk",4,"Textures/characters/posgrad/move/walk/")).size()!=4)out=false;
        if((GL::loadTextures("posgradSpawn",7,"Textures/characters/posgrad/spawn/")).size()!=7)out=false;
    return out;
}
bool loadStrings(){
    bool out=true;
    //TODO:carregar strings de idiomas. retorna falso se nao carregou algum arquivo
    if(languageIdx==0){
        //define pt-br
    }
    return out;
}

bool loadMaps(int nOfMaps){
    bool out=true;
    for(int i=0;i<nOfMaps;i++)
        if(!loadMap(Util::newPath(Util::getDinamicPath("Maps/map",i,".map"))))
            out=false;
    return out;
}

bool loadMap(char* path){
    nTMap tmp;
    ifstream mapFILE(Util::newPath(path));
    if(mapFILE.is_open()){
        string tmp2;
        vector<int> tmp3;
        getline(mapFILE,tmp2);
        istringstream (tmp2) >> tmp.backgroundId;
        while(mapFILE.good()){//!mapFILE.eof()
            while(getline(mapFILE,tmp2)){
                int tmp4;
                string tmp5;
                for(int i=0;i<tmp2.size();i++){
                    if(tmp2[i]!='\'')
                        tmp5+=tmp2[i];
                    else{
                        istringstream (tmp5) >> tmp4;
                        tmp3.push_back(tmp4);
                        tmp5.clear();
                    }
                }
                tmp.map.push_back(tmp3);
                tmp3.clear();
            }
        }
        maps.push_back(tmp);
        mapFILE.close();
        return true;
    }else{
        if(Util::DEBUG)
        cout<<"Erro ao carregar o arquivo "<<path<<endl;
        return false;
  }
}
bool saveMap(char* path,int idx){
    if(idx>=maps.size()){
        cout<<"Erro no index "<<idx<<"do map"<<endl;
        return false;
    }
    ofstream mapFILE(Util::newPath(path));
    if(mapFILE.is_open()){
        mapFILE<<maps[idx].backgroundId<<endl;
        for(int i=0;i<maps[idx].map.size();i++){
            for(int j=0;j<maps[idx].map[i].size();j++)
                mapFILE<<maps[idx].map[i][j]<<'\'';
            mapFILE<<endl;
        }
        mapFILE.close();
        return true;
    }else{
        if(Util::DEBUG)
        cout<<"Erro ao salvar o arquivo "<<path<<endl;
        return false;
  }
}
bool loadSounds(){
    bool out=true;
    //TODO:carregar sons. retorna falso se nao carregou algum arquivo
    if(!al->loadSound("Sounds/test.wav","teste",1,true)) out=false;
    if(!al->loadSound("Sounds/hey.wav","heyListen",2,false)) out=false;
    
    return out;
}
bool loadSettings(){
    //TODO:carregar e definir configuracoes
}
bool saveSettings(){
    //TODO:salvar configuracoes
}
