#include "importLibs.h"

int main(int argc, char** argv) {
    
    loadMaps(1);
    al=new AL(1,1);
    loadSounds();
    
    
    clearColor.setColor(0,0,0,0);
    enables.push_back(GL_DEPTH_TEST);
    enables.push_back(GL_BLEND);
    enables.push_back(GL_ALPHA_TEST);

    GL *gl=new GL("The.COM Games",30,GLUT_DOUBLE | GLUT_RGBA|GLUT_DEPTH|GLUT_STENCIL|GLUT_ALPHA,
         800,600,clearColor,true,enables,argc,argv);
    
    player=new Player(5,2,2,Util::nTPointSet(50,30,0),Util::nTPointSet(20,60,0),NULL,1);
    loadTextures();
    
    if(Util::DEBUG)
    for(int i=0;i<maps[0].map.size();i++){
        for(int j=0;j<maps[0].map[0].size();j++)
            cout<<maps[0].map[i][j];
        cout<<endl;
    }
    
    gl->start();
    return 0;
}
