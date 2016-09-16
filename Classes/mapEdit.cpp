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

void mapEdit::definePages(){
    //TODO: criar paginas com blocos e strings com nomes e botoes de pagina
}

void mapEdit::reset(){
    size=Util::nTPointSet(0,0,1);
    input="";
}

void mapEdit::save(){
    nTMap tmp;
    tmp.backgroundId=currentBackground;
    tmp.map=map;
    maps.push_back(tmp);
    saveMap("Maps/map",index);
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

void mapEditButton(int x,int y){//TODO: erro
    if(x>=0&&x<mapEdit::HUDarea.x&&y>=0&&y<mapEdit::HUDarea.y){
        int i=y/Blocks::defaultBlockSize.y-1;
        int j=x/Blocks::defaultBlockSize.x-1;
        mapEdit::map[i][j]=mapEdit::currentBlock;
    }
}

void mapEdit::draw(){
    glNewList(GLlist,GL_COMPILE_AND_EXECUTE);
    char buffer[5];
    snprintf(buffer,5,"%d",currentBackground);
    string mapID(buffer);
    GL::drawTexture(Util::nTRectangleSet(Scenes::camera.x.movedCam,Scenes::camera.y.movedCam,mapEdit::HUDarea.x+Scenes::camera.x.movedCam,mapEdit::HUDarea.y+Scenes::camera.y.movedCam,-0.9,-0.9),Util::nTColorSet(1,1,1,1),GL::getTextureByName("background"+mapID),1);
    drawPanel();
    drawLines();
    Blocks *bl;
    nTPoint tmp,tmp1;
    for(int i=0;i<size.y;i++){
        for(int j=0;j<size.x;j++){
                tmp=Util::nTPointSet(Blocks::defaultBlockSize.x*(i+(1/2))+Blocks::defaultBlockSize.x/2,Blocks::defaultBlockSize.y*(j+(1/2))+Blocks::defaultBlockSize.y/2,Blocks::defaultBlockSize.z);
                tmp1=Blocks::defaultBlockSize;
                tmp.x*=scale.x;
                tmp.y*=scale.y;
                tmp1.x*=scale.x;
                tmp1.y*=scale.y;
                GL::buttonBehave(Util::getCollisionRectangle(tmp,tmp1),Util::nTColorSet(0.38,0.38,0.38,0.8),0,*mapEditButton,(void(*)(int, int))NULL);
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

void mapEditZoomIn(int x,int y){
    if(mapEdit::scale.x<0.99){
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
    Scenes::current=Scenes::menu;
}

void mapEditLeave(int x,int y){
    Scenes::current=Scenes::menu;
}

void mapEdit::drawPanel(){
    GL::drawRectangle(Util::nTRectangleSet(Scenes::camera.x.movedCam,GL::defaultSize.y+Scenes::camera.y.movedCam,GL::defaultSize.x+Scenes::camera.x.movedCam,HUDarea.y+Scenes::camera.y.movedCam,0,0),GL::getColorByName("grey"));
    GL::drawRectangle(Util::nTRectangleSet(HUDarea.x+Scenes::camera.x.movedCam,GL::defaultSize.y+Scenes::camera.y.movedCam,GL::defaultSize.x+Scenes::camera.x.movedCam,Scenes::camera.y.movedCam,0,0),GL::getColorByName("grey"));
    
    GL::buttonBehave(Util::nTRectangleSet(20+Scenes::camera.x.movedCam,550+Scenes::camera.y.movedCam,40+Scenes::camera.x.movedCam,570+Scenes::camera.y.movedCam,1,1),GL::getColorByName("mouseSelected"),GL::getTextureByName("Ar"),*mapEditSetAir,(void(*)(int, int))NULL);
    GL::buttonBehave(Util::nTRectangleSet(60+Scenes::camera.x.movedCam,550+Scenes::camera.y.movedCam,80+Scenes::camera.x.movedCam,570+Scenes::camera.y.movedCam,1,1),GL::getColorByName("mouseSelected"),GL::getTextureByName("Zoom-"),*mapEditZoomOut,(void(*)(int, int))NULL);
    GL::buttonBehave(Util::nTRectangleSet(90+Scenes::camera.x.movedCam,550+Scenes::camera.y.movedCam,110+Scenes::camera.x.movedCam,570+Scenes::camera.y.movedCam,1,1),GL::getColorByName("mouseSelected"),GL::getTextureByName("Zoom+"),*mapEditZoomIn,(void(*)(int, int))NULL);
    GL::buttonBehave(Util::nTRectangleSet(130+Scenes::camera.x.movedCam,550+Scenes::camera.y.movedCam,150+Scenes::camera.x.movedCam,570+Scenes::camera.y.movedCam,1,1),GL::getColorByName("mouseSelected"),GL::getTextureByName("Background-"),*mapEditBackgroundDown,(void(*)(int, int))NULL);
    GL::buttonBehave(Util::nTRectangleSet(160+Scenes::camera.x.movedCam,550+Scenes::camera.y.movedCam,180+Scenes::camera.x.movedCam,570+Scenes::camera.y.movedCam,1,1),GL::getColorByName("mouseSelected"),GL::getTextureByName("Background+"),*mapEditBackgroundUp,(void(*)(int, int))NULL);
    GL::buttonBehave(Util::nTRectangleSet(200+Scenes::camera.x.movedCam,550+Scenes::camera.y.movedCam,220+Scenes::camera.x.movedCam,570+Scenes::camera.y.movedCam,1,1),GL::getColorByName("mouseSelected"),GL::getTextureByName("CameraDefault"),*mapEditCamera,(void(*)(int, int))NULL);
    GL::buttonBehave(Util::nTRectangleSet(240+Scenes::camera.x.movedCam,550+Scenes::camera.y.movedCam,260+Scenes::camera.x.movedCam,570+Scenes::camera.y.movedCam,1,1),GL::getColorByName("mouseSelected"),GL::getTextureByName("Save"),*mapEditSave,(void(*)(int, int))NULL);
    GL::buttonBehave(Util::nTRectangleSet(280+Scenes::camera.x.movedCam,550+Scenes::camera.y.movedCam,300+Scenes::camera.x.movedCam,570+Scenes::camera.y.movedCam,1,1),GL::getColorByName("mouseSelected"),GL::getTextureByName("Back"),*mapEditLeave,(void(*)(int, int))NULL);
    GL::buttonBehave(Util::nTRectangleSet(770+Scenes::camera.x.movedCam,40+Scenes::camera.y.movedCam,790+Scenes::camera.x.movedCam,60+Scenes::camera.y.movedCam,1,1),GL::getColorByName("mouseSelected"),GL::getTextureByName("-"),*mapEditPageDown,(void(*)(int, int))NULL);
    GL::buttonBehave(Util::nTRectangleSet(660+Scenes::camera.x.movedCam,40+Scenes::camera.y.movedCam,680+Scenes::camera.x.movedCam,60+Scenes::camera.y.movedCam,1,1),GL::getColorByName("mouseSelected"),GL::getTextureByName("+"),*mapEditPageUp,(void(*)(int, int))NULL);
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