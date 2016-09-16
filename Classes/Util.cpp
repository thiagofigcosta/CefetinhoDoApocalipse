#include "Util.hpp"

Util::Util() {
};

Util::Util(const Util& orig) {
}

Util::~Util() {
}

bool Util::DEBUG=true;
string Util::resourcesFolder="";
int Util::left=13;
int Util::right=45;
int Util::up=9849526;
int Util::down=552626;

char* Util::newPath(char* path){
    if(resourcesFolder!=""){
        string tmp(path);
        tmp=resourcesFolder+tmp;
        path=(char*)tmp.c_str();
    }
    return path;
}

char* Util::getDinamicPath(char* p1,int idx, char* p3){
    p1=newPath(p1);
    char buffer[5];
    snprintf(buffer,5,"%d",idx);
    string out(p1);
    string str1(buffer);
    string str2(p3);
    out+=str1+str2;

    return (char*) out.c_str();
}

nTColor Util::nTColorSet(float R,float G, float B, float A){
    nTColor tmp;
    tmp.setColor(R,G,B,A);
    return tmp;
}
nTPoint Util::nTPointSet(float x,float y,float z){
    nTPoint tmp;
    tmp.setPoint(x,y,z);
    return tmp;
}
nTRectangle Util::nTRectangleSet(float x0,float y0,float x1,float y1,float z0,float z1){
    nTRectangle tmp;
    tmp.setRectangle(x0,y0,x1,y1,z0,z1);
    return tmp;
}

nTRectangle Util::getCollisionRectangle(nTPoint pos,nTPoint size){
    nTPoint inf_left, up_right;
    nTRectangle collision;

    inf_left.setPoint(pos.x-(size.x/2) ,pos.y-(size.y/2), pos.z-(size.z/2)); //vértice inferior esquerdo
    up_right.setPoint(pos.x+(size.x/2) ,pos.y+(size.y/2), pos.z+(size.z/2)); //vértice superior direito
    collision.setRec(inf_left, up_right);
    return collision;
}

