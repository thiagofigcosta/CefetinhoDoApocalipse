#ifndef AL_H
#define AL_H
#include <AL/al.h>
#include <AL/alc.h>
#include "Util.h"

class AL {
public:
    AL();
    AL(const AL& orig);
    virtual ~AL();
    bool checkIfIsPlaying(int sound);
    void stopAllSoundsExcept(vector<int>&sounds);
    bool playSoundByName(string name);
    bool playSound(int sound);
    bool stopSound(int sound);
    bool loadSound(char* path,string name,float vol,bool Loop);
private:
    static vector<string> soundName;
    static vector<ALuint> sounds;
    static vector<ALuint> buffers;
    ALfloat ListenerPos[3] = { 0.0, 0.0, 0.0 };
    ALfloat ListenerVel[3] = { 0.0, 0.0, 0.0 };
    ALfloat ListenerOri[6] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 };
    ALfloat SourcePos[3] = { 0.0, 0.0, 0.0 };
    ALfloat SourceVel[3] = { 0.0, 0.0, 0.0 };
};

#endif /* AL_H */

