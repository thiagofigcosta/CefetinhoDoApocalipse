#include "importLibs.h"

//erase v
void eraseMe(){
vector<string> tmp;
vector<int> tmp2;
tmp.push_back("cefetinhoIdle");
tmp.push_back("cefetinhoMoveWalk");
tmp.push_back("cefetinhoMoveRun");
tmp.push_back("cefetinhoJump");
tmp.push_back("cefetinhoAtkMeleeGroundFront");
tmp.push_back("cefetinhoAtkRangedGroundFront");
tmp.push_back("cefetinhoDmgGround");
tmp.push_back("cefetinhoDie");
tmp2.push_back(5);
tmp2.push_back(4);
tmp2.push_back(4);
tmp2.push_back(1);
tmp2.push_back(1);
tmp2.push_back(4);
tmp2.push_back(1);
tmp2.push_back(4);
playerAnim.push_back(tmp);
playerAnimSize.push_back(tmp2);
enemyAnim.push_back(tmp);
enemyAnimSize.push_back(tmp2);
}
//erase ^

int main(int argc, char** argv) {
    eraseMe();
   
    
    mapEdit::definePages();
    vector<GLenum> enables;
    clearColor.setColor(0,0,0,0);
    enables.push_back(GL_DEPTH_TEST);
    enables.push_back(GL_BLEND);
    enables.push_back(GL_ALPHA_TEST);
    GL *gl=new GL("The.COM Games",30,GLUT_DOUBLE | GLUT_RGBA|GLUT_DEPTH|GLUT_STENCIL|GLUT_ALPHA,
         800,600,clearColor,true,enables,argc,argv);
    
    if(!loadMaps(2)) if(Util::DEBUG) cout<<"erro ao carregar mapas"<<endl;
    
    al=new AL(1,1);
    
    if(!loadSounds()) if(Util::DEBUG) cout<<"erro ao carregar sons"<<endl;
    
    if(!loadTextures()) if(Util::DEBUG) cout<<"erro ao carregar texturas"<<endl;
    
    player=new Player(5,2,2,Util::nTPointSet(0,0,0),Util::nTPointSet(28,60,0),Entity::getAnimationVector(playerAnim[0],playerAnimSize[0]),1);
    
    gl->start();
    return 0;
}
