#include "loadFiles.h"

bool loadTextures(){
    //TODO: carregar todas as texturas, carregar todos os idiomas de uma vez e depois so decidir qual textura vai usar. retorna falso se nao carregou algum arquivo
    //blocos fisicos
    GL::loadTexture("Pedra","Textures/blocks/2.png");
    GL::loadTexture("Terra","Textures/blocks/3.png");
    GL::loadTexture("Grama","Textures/blocks/4.png");
    GL::loadTexture("Tronco Madeira","Textures/blocks/21.png");
    GL::loadTexture("Pedra Musgo","Textures/blocks/37.png");
    GL::loadTexture("Neve","Textures/blocks/66.png");
    GL::loadTexture("Grama neve","Textures/blocks/68.png");
    GL::loadTexture("Tijolo pedra musgo","Textures/blocks/100.png");
    GL::loadTexture("Arenito","Textures/blocks/179.png");
    GL::loadTexture("Ender portal","Textures/blocks/180.png");
    GL::loadTexture("Tijolo nether","Textures/blocks/185.png");
    GL::loadTexture("Tijolo areia ","Textures/blocks/189.png");
    GL::loadTexture("Tijolo pedra","Textures/blocks/54.png");
    GL::loadTexture("Tijolo","Textures/blocks/8.png");
    GL::loadTexture("Madeira","Textures/blocks/5.png");
    GL::loadTexture("La ciano","Textures/blocks/169.png");
    GL::loadTexture("Gelo","Textures/blocks/67.png");
    
    //blocos que movem   
    GL::loadTexture("Meio bloco pedra","Textures/blocks/211.png");
    GL::loadTexture("Meio bloco madeira","Textures/blocks/212.png");
    GL::loadTexture("Meio bloco arenito","Textures/blocks/213.png");
    GL::loadTexture("Meio bloco gelo","Textures/blocks/214.png");
    
    //blocos que quebram
    GL::loadTexture("Tijolo pedra quebrado","Textures/blocks/101.png");
    GL::loadTexture("Pedregulho","Textures/blocks/17.png");
    
    //baus
    GL::loadTexture("Bau","Textures/blocks/28.png");
    
   //blocos especiais
    GL::loadTexture("Spawn","Textures/blocks/65.png");
    GL::loadTexture("Alavanca","Textures/blocks/96.png");
    
   //blocos decorativos
    GL::loadTexture("Cogumelos azuis","Textures/blocks/29.png");
    GL::loadTexture("Muda pinheiro","Textures/blocks/63.png");
    GL::loadTexture("Trigo","Textures/blocks/94.png");
    GL::loadTexture("Trigo2","Textures/blocks/95.png");
    GL::loadTexture("Muda seca","Textures/blocks/55.png");
    GL::loadTexture("Muda neve","Textures/blocks/111.png");
}
bool loadStrings(){
    //TODO:carregar strings de idiomas. retorna falso se nao carregou algum arquivo
    if(languageIdx==0){
        //define pt-br
    }
}

bool loadMaps(int nOfMaps){
    bool out=true;
    for(int i=0;i<nOfMaps;i++)
        if(!loadMap(Util::getDinamicPath("Maps/map",i,".map")))
            out=false;
    return out;
}

bool loadMap(char* path){
    nTMap tmp;
    ifstream mapFILE(path);
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
    ofstream mapFILE(path);
    if(mapFILE.is_open()){
        mapFILE<<maps[idx].backgroundId<<endl;
        for(int i=0;i<maps[idx].map.size();i++){
            for(int j=0;j<maps[idx].map[i].size();j++)
                mapFILE<<maps[idx].map[i][j]<<'\'';
            mapFILE<<endl;
        }
        mapFILE.close();
    }else{
        if(Util::DEBUG)
        cout<<"Erro ao salvar o arquivo "<<path<<endl;
        return false;
  }
}
bool loadSounds(){
    //TODO:carregar sons. retorna falso se nao carregou algum arquivo
    al->loadSound("Sounds/test.wav","teste",1,true);
}
bool loadSettings(){
    //TODO:carregar e definir configuracoes
}
bool saveSettings(){
    //TODO:salvar configuracoes
}
