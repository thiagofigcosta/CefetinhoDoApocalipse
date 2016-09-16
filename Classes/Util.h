#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>
#include <math.h>
using namespace std;

typedef struct color{
        float R,G,B,A;
        void setColor(float R_,float G_, float B_, float A_){
            R=R_;G=G_;B=B_;A=A_;
        };
}nTColor;

typedef struct point{
        float x,y,z;
        void setPoint(float x_,float y_,float z_){
            x=x_;y=y_;z=z_;
        };
}nTPoint;

typedef struct rectangle{
        nTPoint p0,p1;
        void setRec(nTPoint p0_,nTPoint p1_){
            p0=p0_;p1=p1_;
        };
        void setRectangle(float x0_,float y0_,float x1_,float y1_,float z0_,float z1_){
            p0.x=x0_;p0.y=y0_;p1.x=x1_;p1.y=y1_;
            p0.z=z0_;p1.z=z1_;
        };
}nTRectangle;



class Util {
public:
    Util();
    Util(const Util& orig);
    virtual ~Util();
    static char* newPath(char* path);
    static bool DEBUG;
    static char* getDinamicPath(char* p1,int idx, char* p3);
    
    static nTColor nTColorSet(float R,float G, float B,float A);
    static nTPoint nTPointSet(float x,float y,float z);
    static nTRectangle nTRectangleSet(float x0,float y0,float x1,float y1,float z0,float z1);
private:
    static string resourcesFolder;
};

#endif /* UTIL_H */

