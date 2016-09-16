#include "mapEdit.hpp"


mapEdit::mapEdit() {
}

mapEdit::mapEdit(const mapEdit& orig) {
}

mapEdit::~mapEdit() {
}

nTPoint mapEdit::scale=Util::nTPointSet(0.8,0.8,1);
nTPoint mapEdit::HUDarea=Util::nTPointSet(650,500,1);
nTPoint mapEdit::size=Util::nTPointSet(0,0,1);
string mapEdit::input;
GLuint mapEdit::GLlist=glGenLists(1);
int mapEdit::currentBlock=1;
string mapEdit::blankField="_";
int mapEdit::currentBackground=0;
vector<vector<int> > mapEdit::map;
int mapEdit::index;
vector<vector<vector<int> > >mapEdit::blockPages;
vector<string> mapEdit::pageNames;
int mapEdit::pageIndex=0;
short int mapEdit::isCreating=0;
bool mapEdit::isUser=true;

void mapEdit::definePages(){
    blockPages.clear();
    pageNames.clear();
    vector<vector<int> >pageTmp;
    vector<int> rowTmp;

    pageNames.push_back("Solidos 1");
    for(int i=1;i<8;i++)
        rowTmp.push_back(i);
    pageTmp.push_back(rowTmp);
    rowTmp.clear();
    for(int i=8;i<15;i++)
        rowTmp.push_back(i);
    pageTmp.push_back(rowTmp);
    rowTmp.clear();
    for(int i=15;i<19;i++)
        rowTmp.push_back(i);
    pageTmp.push_back(rowTmp);
    rowTmp.clear();
   blockPages.push_back(pageTmp);
   pageTmp.clear();
   
   
   pageNames.push_back("Move Horizontal");
   for(int i=201;i<205;i++)
        rowTmp.push_back(i);
    pageTmp.push_back(rowTmp);
    rowTmp.clear();
    blockPages.push_back(pageTmp);
    pageTmp.clear();
   
    
   pageNames.push_back("Move Vertical");
   for(int i=251;i<255;i++)
        rowTmp.push_back(i);
    pageTmp.push_back(rowTmp);
    rowTmp.clear();
    blockPages.push_back(pageTmp);
    pageTmp.clear();
    
    
   pageNames.push_back("Invisiveis");
   for(int i=351;i<358;i++)
        rowTmp.push_back(i);
    pageTmp.push_back(rowTmp);
    rowTmp.clear();
    for(int i=358;i<363;i++)
        rowTmp.push_back(i);
    pageTmp.push_back(rowTmp);
    rowTmp.clear();
    
    blockPages.push_back(pageTmp);
    pageTmp.clear();
    
    pageNames.push_back("PowerUps");
    for(int i=476;i<483;i++)
        rowTmp.push_back(i);
    pageTmp.push_back(rowTmp);
    rowTmp.clear();
    for(int i=483;i<490;i++)
        rowTmp.push_back(i);
    pageTmp.push_back(rowTmp);
    rowTmp.clear();
    for(int i=490;i<497;i++)
        rowTmp.push_back(i);
    pageTmp.push_back(rowTmp);
    rowTmp.clear();
    for(int i=497;i<501;i++)
        rowTmp.push_back(i);
    pageTmp.push_back(rowTmp);
    rowTmp.clear();
    blockPages.push_back(pageTmp);
    pageTmp.clear();
    
    pageNames.push_back("Destrutivos");
    for(int i=326;i<328;i++)
        rowTmp.push_back(i);
    pageTmp.push_back(rowTmp);
    rowTmp.clear();
    blockPages.push_back(pageTmp);
    pageTmp.clear();
    
    pageNames.push_back("Decorativo");
    for(int i=401;i<407;i++)
        rowTmp.push_back(i);
    pageTmp.push_back(rowTmp);
    rowTmp.clear();
    blockPages.push_back(pageTmp);
    pageTmp.clear();
    
}

void mapEdit::load(int idx){
    index=idx;
    map.clear();
    map=maps[idx].map;
    currentBackground=maps[idx].backgroundId;
    size.y=map.size();
    size.x=map[0].size();
}

void mapEdit::reset(){
    size=Util::nTPointSet(0,0,1);
    scale=Util::nTPointSet(0.8,0.8,1);
    currentBlock=0;
    currentBackground=0;
    pageIndex=0;
    input="";
    isCreating=0;
    isUser=true;
}

void mapEdit::save(){
    nTMap tmp;
    tmp.backgroundId=currentBackground;
    tmp.map=map;
    if(index>=maps.size()||isUser)
        maps.push_back(tmp);
    else
        maps[index]=tmp;
    
    if(isUser){
        saveMap("Maps/user.map",index);
    }else{
        char buffer[5];
        snprintf(buffer,5,"%d",index);
        string str(buffer);
        saveMap((char*)("Maps/map"+str+".map").c_str(),index);
    }
}

void mapEdit::drawLines(){  
    nTColor tmp=GL::getColor();
    GL::setColor(GL::getColorByName("white"));
    glLineWidth(1);
    for(int i=0;i<=size.y;i++){
        glBegin(GL_LINE_STRIP);
        for(int j=0;j<=size.x;j++)
            glVertex3f(j*Blocks::defaultBlockSize.x*scale.x,i*Blocks::defaultBlockSize.y*scale.y,-0.5);
        glEnd();
    }
    for(int j=0;j<=size.x;j++){
        glBegin(GL_LINE_STRIP);
        for(int i=0;i<=size.y;i++)
            glVertex3f(j*Blocks::defaultBlockSize.x*scale.x,i*Blocks::defaultBlockSize.y*scale.y,-0.5);
        glEnd();
    }
    GL::setColor(GL::getColorByName("blue"));
    
    glLineWidth(2.5);
    glBegin(GL_LINE_LOOP);
        glVertex3f(0,0,-0.49);
        glVertex3f((size.x)*Blocks::defaultBlockSize.x*scale.x,-0,0.49);
        glVertex3f((size.x)*Blocks::defaultBlockSize.x*scale.x,(size.y)*Blocks::defaultBlockSize.y*scale.y,-0.49);
        glVertex3f(0,(size.y)*Blocks::defaultBlockSize.y*scale.y,-0.49);
    glEnd(); 
    GL::setColor(tmp);
}

void mapEditButton(int x,int y){
    x/=mapEdit::scale.x;
    y/=mapEdit::scale.y;
    if(x>=Scenes::camera.x.movedCam/mapEdit::scale.x&&x<(mapEdit::HUDarea.x+Scenes::camera.x.movedCam)/mapEdit::scale.x&&y>=Scenes::camera.y.movedCam/mapEdit::scale.y&&y<(mapEdit::HUDarea.y+Scenes::camera.y.movedCam)/mapEdit::scale.y){
        int i=round(((y-Blocks::defaultBlockSize.y/2)/Blocks::defaultBlockSize.y)-(1/2));
        int j=round(((x-Blocks::defaultBlockSize.x/2)/Blocks::defaultBlockSize.x)-(1/2));
        if(mapEdit::currentBlock<60000)
            mapEdit::map[i][j]=mapEdit::currentBlock;
        else
            mapEdit::currentBlock=mapEdit::map[i][j];
    }
}

void mapEraseButton(int x,int y){
    x/=mapEdit::scale.x;
    y/=mapEdit::scale.y;
    if(x>=Scenes::camera.x.movedCam/mapEdit::scale.x&&x<(mapEdit::HUDarea.x+Scenes::camera.x.movedCam)/mapEdit::scale.x&&y>=Scenes::camera.y.movedCam/mapEdit::scale.y&&y<(mapEdit::HUDarea.y+Scenes::camera.y.movedCam)/mapEdit::scale.y){
        int i=round(((y-Blocks::defaultBlockSize.y/2)/Blocks::defaultBlockSize.y)-(1/2));
        int j=round(((x-Blocks::defaultBlockSize.x/2)/Blocks::defaultBlockSize.x)-(1/2));
        mapEdit::map[i][j]=0;
    }
}

void mapEditSetBlock(int x,int y){
    x-=Scenes::camera.x.movedCam;
    y-=Scenes::camera.y.movedCam;
    if(x>=(mapEdit::HUDarea.x)){
        int i=floor((y-100+16)/25);
        int j=floor((x-663+16)/25);
        mapEdit::currentBlock=mapEdit::blockPages[mapEdit::pageIndex][i][j];
    }
}

void mapEdit::draw(){
    glNewList(GLlist,GL_COMPILE_AND_EXECUTE);
    char buffer[5];
    snprintf(buffer,5,"%d",currentBackground);
    string mapID(buffer);
    GL::drawTexture(Util::nTRectangleSet(Scenes::camera.x.movedCam,mapEdit::HUDarea.y+Scenes::camera.y.movedCam,mapEdit::HUDarea.x+Scenes::camera.x.movedCam,Scenes::camera.y.movedCam,-0.9,-0.9),Util::nTColorSet(1,1,1,1),GL::getTextureByName("background"+mapID),1);
    drawPanel();
    drawLines();
    Blocks *bl;
    nTPoint tmp,tmp1;
    for(int i=0;i<size.y;i++){
        for(int j=0;j<size.x;j++){
                tmp=Util::nTPointSet(Blocks::defaultBlockSize.x*(j+(1/2))+Blocks::defaultBlockSize.x/2,Blocks::defaultBlockSize.y*(i+(1/2))+Blocks::defaultBlockSize.y/2,Blocks::defaultBlockSize.z);
                tmp1=Blocks::defaultBlockSize;
                tmp.x*=scale.x;
                tmp.y*=scale.y;
                tmp1.x*=scale.x;
                tmp1.y*=scale.y;
                GL::buttonBehave(Util::getCollisionRectangle(tmp,tmp1),Util::nTColorSet(0.38,0.38,0.38,0.8),0,*mapEditButton,NULL,*mapEraseButton,NULL);
            if(map[i][j]){
                tmp.z-=0.1;
                tmp1.z-=0.1;
                bl = new Blocks(map[i][j],tmp,tmp1);
                bl->draw();
                delete bl;
            }
        }
    }
    glEndList();
}

void mapEditSetAir(int x,int y){
    mapEdit::currentBlock=0;
}

void mapEditGetBlock(int x,int y){
    mapEdit::currentBlock=60000;
}

void mapEditZoomIn(int x,int y){
    if(mapEdit::scale.x<1.99){
        mapEdit::scale.x+=0.01;
        mapEdit::scale.y+=0.01;
    }
}

void mapEditZoomOut(int x,int y){
    if(mapEdit::scale.x>0.01){
        mapEdit::scale.x-=0.01;
        mapEdit::scale.y-=0.01;
    }
}

void mapEditBackgroundUp(int x,int y){
    mapEdit::currentBackground++;
    char buffer[5];
    snprintf(buffer,5,"%d",mapEdit::currentBackground);
    string mapID(buffer);
    if(GL::getTextureByName("background"+mapID)==0)
         mapEdit::currentBackground=0;
}

void mapEditBackgroundDown(int x,int y){
    mapEdit::currentBackground--;
    char buffer[5];
    snprintf(buffer,5,"%d",mapEdit::currentBackground);
    string mapID(buffer);
    if(GL::getTextureByName("background"+mapID)==0)
         mapEdit::currentBackground++;
}

void mapEditCamera(int x,int y){
    Scenes::putCameraOnOrigin();
}

void mapEditPageUp(int x,int y){
    mapEdit::pageIndex++;
    if(mapEdit::pageIndex>=mapEdit::blockPages.size())
        mapEdit::pageIndex=0;
}

void mapEditPageDown(int x,int y){
    mapEdit::pageIndex--;
    if(mapEdit::pageIndex<0)
        mapEdit::pageIndex=mapEdit::blockPages.size()-1;
}

void mapEditSave(int x,int y){
    mapEdit::save();
}

void mapEditLeave(int x,int y){
    Scenes::current=Scenes::menu;
}

void mapEdit::drawPanel(){
    GL::drawRectangle(Util::nTRectangleSet(Scenes::camera.x.movedCam,GL::defaultSize.y+Scenes::camera.y.movedCam,GL::defaultSize.x+Scenes::camera.x.movedCam,HUDarea.y+Scenes::camera.y.movedCam,0,0),GL::getColorByName("grey"));
    GL::drawRectangle(Util::nTRectangleSet(HUDarea.x+Scenes::camera.x.movedCam,GL::defaultSize.y+Scenes::camera.y.movedCam,GL::defaultSize.x+Scenes::camera.x.movedCam,Scenes::camera.y.movedCam,0,0),GL::getColorByName("grey"));
    
    GL::buttonBehave(Util::nTRectangleSet(20+Scenes::camera.x.movedCam,570+Scenes::camera.y.movedCam,50+Scenes::camera.x.movedCam,533+Scenes::camera.y.movedCam,1,1),GL::getColorByName("mouseSelected"),GL::getTextureByName("Ar"),*mapEditSetAir,NULL,NULL,NULL);
    GL::buttonBehave(Util::nTRectangleSet(70+Scenes::camera.x.movedCam,570+Scenes::camera.y.movedCam,100+Scenes::camera.x.movedCam,533+Scenes::camera.y.movedCam,1,1),GL::getColorByName("mouseSelected"),GL::getTextureByName("Zoom-"),*mapEditZoomOut,NULL,NULL,NULL);
    GL::buttonBehave(Util::nTRectangleSet(110+Scenes::camera.x.movedCam,570+Scenes::camera.y.movedCam,140+Scenes::camera.x.movedCam,533+Scenes::camera.y.movedCam,1,1),GL::getColorByName("mouseSelected"),GL::getTextureByName("Zoom+"),*mapEditZoomIn,NULL,NULL,NULL);
    GL::buttonBehave(Util::nTRectangleSet(150+Scenes::camera.x.movedCam,570+Scenes::camera.y.movedCam,180+Scenes::camera.x.movedCam,533+Scenes::camera.y.movedCam,1,1),GL::getColorByName("mouseSelected"),GL::getTextureByName("Background-"),*mapEditBackgroundDown,NULL,NULL,NULL);
    GL::buttonBehave(Util::nTRectangleSet(190+Scenes::camera.x.movedCam,570+Scenes::camera.y.movedCam,220+Scenes::camera.x.movedCam,533+Scenes::camera.y.movedCam,1,1),GL::getColorByName("mouseSelected"),GL::getTextureByName("Background+"),*mapEditBackgroundUp,NULL,NULL,NULL);
    GL::buttonBehave(Util::nTRectangleSet(230+Scenes::camera.x.movedCam,570+Scenes::camera.y.movedCam,280+Scenes::camera.x.movedCam,533+Scenes::camera.y.movedCam,1,1),GL::getColorByName("mouseSelected"),GL::getTextureByName("CameraDefault"),*mapEditCamera,NULL,NULL,NULL);
    GL::buttonBehave(Util::nTRectangleSet(290+Scenes::camera.x.movedCam,570+Scenes::camera.y.movedCam,320+Scenes::camera.x.movedCam,533+Scenes::camera.y.movedCam,1,1),GL::getColorByName("mouseSelected"),GL::getTextureByName("Get Block"),*mapEditGetBlock,NULL,NULL,NULL);
    GL::buttonBehave(Util::nTRectangleSet(330+Scenes::camera.x.movedCam,570+Scenes::camera.y.movedCam,360+Scenes::camera.x.movedCam,533+Scenes::camera.y.movedCam,1,1),GL::getColorByName("mouseSelected"),GL::getTextureByName("Save"),*mapEditSave,NULL,NULL,NULL);
    GL::buttonBehave(Util::nTRectangleSet(370+Scenes::camera.x.movedCam,570+Scenes::camera.y.movedCam,400+Scenes::camera.x.movedCam,533+Scenes::camera.y.movedCam,1,1),GL::getColorByName("mouseSelected"),GL::getTextureByName("Back"),*mapEditLeave,NULL,NULL,NULL);
    GL::buttonBehave(Util::nTRectangleSet(770+Scenes::camera.x.movedCam,60+Scenes::camera.y.movedCam,790+Scenes::camera.x.movedCam,40+Scenes::camera.y.movedCam,1,1),GL::getColorByName("mouseSelected"),GL::getTextureByName("-"),NULL,*mapEditPageDown,NULL,NULL);
    GL::buttonBehave(Util::nTRectangleSet(660+Scenes::camera.x.movedCam,60+Scenes::camera.y.movedCam,680+Scenes::camera.x.movedCam,40+Scenes::camera.y.movedCam,1,1),GL::getColorByName("mouseSelected"),GL::getTextureByName("+"),NULL,*mapEditPageUp,NULL,NULL);
    GL::setFontByIndex(5);
    GL::drawText(Util::nTPointSet(500+Scenes::camera.x.movedCam,530+Scenes::camera.y.movedCam,1),"Bloco Atual",GL::getColorByName("black"));
    if(currentBlock<60000&&currentBlock!=0)
        GL::drawTexture(Util::nTRectangleSet(500+Scenes::camera.x.movedCam,570+Scenes::camera.y.movedCam,530+Scenes::camera.x.movedCam,533+Scenes::camera.y.movedCam,1,1),GL::getColorByName("white"),GL::getTextureByName(Blocks::getTexNameByIndex(currentBlock)),1);
    else if(currentBlock==0)
        GL::drawTexture(Util::nTRectangleSet(500+Scenes::camera.x.movedCam,570+Scenes::camera.y.movedCam,530+Scenes::camera.x.movedCam,533+Scenes::camera.y.movedCam,1,1),GL::getColorByName("white"),GL::getTextureByName("Ar"),1);
    else
        GL::drawTexture(Util::nTRectangleSet(500+Scenes::camera.x.movedCam,570+Scenes::camera.y.movedCam,530+Scenes::camera.x.movedCam,533+Scenes::camera.y.movedCam,1,1),GL::getColorByName("white"),GL::getTextureByName("Get Block"),1);

    GL::setFontByIndex(2);
    int dx=GL::mousePos.x+Scenes::camera.x.movedCam;
    int dy=GL::mousePos.y+Scenes::camera.y.movedCam;
    int blockID=0;
    if(dx>=(mapEdit::HUDarea.x)){
        int di=floor((dy-100+16)/25);
        int dj=floor((dx-663+16)/25);
        if(di>=0&&di<blockPages[mapEdit::pageIndex].size())
        if(dj>=0&&dj<blockPages[mapEdit::pageIndex][0].size())
            blockID=mapEdit::blockPages[mapEdit::pageIndex][di][dj];
    }
    string strT=Blocks::getTexNameByIndex(blockID);
    if(strT!=""){
        nTPoint poinT=GL::mousePos;
        poinT.x-=10*strT.size();
        poinT.z=1;
        GL::drawText(poinT,(char*)strT.c_str(),GL::getColorByName("black")); 
    }
    GL::setFontByIndex(0);
    if(!isUser)
        GL::drawText(Util::nTPointSet(500+Scenes::camera.x.movedCam,590+Scenes::camera.y.movedCam,1),"MODO DESENVOLVEDOR",GL::getColorByName("violet"));
    GL::setFontByIndex(3);
    GL::drawText(Util::nTPointSet(686+Scenes::camera.x.movedCam,55+Scenes::camera.y.movedCam,1),(char*)pageNames[pageIndex].c_str(),GL::getColorByName("yellow"));
        for(int i=0;i<blockPages[pageIndex].size();i++){
        for(int j=0;j<blockPages[pageIndex][i].size();j++){
            nTRectangle tmp;
            if(blockPages[pageIndex][i][j]>=201&&blockPages[pageIndex][i][j]<=300)
                tmp=Util::getCollisionRectangle(Util::nTPointSet(663+25*j,100+25*i,1),Util::nTPointSet(16,8,0));
            else
                tmp=Util::getCollisionRectangle(Util::nTPointSet(663+25*j,100+25*i,1),Util::nTPointSet(16,16,0));
            tmp.p0.x+=Scenes::camera.x.movedCam;tmp.p1.x+=Scenes::camera.x.movedCam;
            tmp.p0.y+=Scenes::camera.y.movedCam;tmp.p1.y+=Scenes::camera.y.movedCam;
            GL::buttonBehave(tmp,GL::getColorByName("mouseSelected"),GL::getTextureByName(Blocks::getTexNameByIndex(blockPages[pageIndex][i][j])),*mapEditSetBlock,(void(*)(int, int))NULL,NULL,NULL);           
        }
    }

}

void mapEdit::askForSize(){
    glNewList(GLlist,GL_COMPILE_AND_EXECUTE);
    GL::setFontByIndex(0);
    GL::drawText(Util::nTPointSet(200,150,1),"Digite os valores e apos digitar precione enter:",GL::getColorByName("blue"));
    GL::setFontByIndex(6);
    GL::drawText(Util::nTPointSet(200,200,1),"Digite o numero de linhas do mapa(19):",GL::getColorByName("blue"));
    GL::drawText(Util::nTPointSet(200,250,1),"Digite o numero de colunas do mapa:",GL::getColorByName("blue"));
    if(size.y==0){
        if(input=="")
            GL::drawText(Util::nTPointSet(520,200,1),(char*)blankField.c_str(),GL::getColorByName("red"));
        else
            GL::drawText(Util::nTPointSet(520,200,1),(char*)input.c_str(),GL::getColorByName("red"));
    }else{
        char buffer[10];
        snprintf(buffer,10,"%f",size.y);
        GL::drawText(Util::nTPointSet(520,200,1),buffer,GL::getColorByName("blue"));
        if(input=="")
            GL::drawText(Util::nTPointSet(520,250,1),(char*)blankField.c_str(),GL::getColorByName("red"));
        else
            GL::drawText(Util::nTPointSet(520,250,1),(char*)input.c_str(),GL::getColorByName("red"));
    }
    glEndList();
}

void mapEdit::askForLoad(){
    glNewList(GLlist,GL_COMPILE_AND_EXECUTE);
    GL::setFontByIndex(0);
    GL::drawText(Util::nTPointSet(200,150,1),"Digite os valores e apos digitar precione enter:",GL::getColorByName("blue"));
    GL::setFontByIndex(6);
        char buffer[10];
        snprintf(buffer,10,"%ld",maps.size()-1);
        string maxMap(buffer);
    GL::drawText(Util::nTPointSet(200,200,1),(char*)("Digite qual mapa quer carregar(0-"+maxMap+"):").c_str(),GL::getColorByName("blue"));
        if(input=="")
            GL::drawText(Util::nTPointSet(520,200,1),(char*)blankField.c_str(),GL::getColorByName("red"));
        else
            GL::drawText(Util::nTPointSet(520,200,1),(char*)input.c_str(),GL::getColorByName("red"));
    glEndList();
}
    
void mapEdit::setMapSize(){
    index=maps.size();
    map.clear();
    vector<int> tmp;
    for(int i=0;i<size.y;i++){
        for(int j=0;j<size.x;j++)
            tmp.push_back(0);
        map.push_back(tmp);
        tmp.clear();
    }
} 