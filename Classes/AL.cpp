#include "AL.h"

AL::AL() {
    ALCdevice *device;                                                          //Create an OpenAL Device
    ALCcontext *context;                                                        //And an OpenAL Context
    device = alcOpenDevice(NULL);                                               //Open the device
    context = alcCreateContext(device, NULL);                                   //Give the device a context
    alcMakeContextCurrent(context);                                             //Make the context the current

    alListenerfv(AL_POSITION,    ListenerPos);                                  //Set position of the listener
    alListenerfv(AL_VELOCITY,    ListenerVel);                                  //Set velocity of the listener
    alListenerfv(AL_ORIENTATION, ListenerOri);
};

AL::AL(const AL& orig) {
}

AL::~AL() {
}

vector<string> AL::soundName;
vector<ALuint> AL::sounds;
vector<ALuint> AL::buffers;

bool AL::checkIfIsPlaying(int sound){
    ALint state;
    alGetSourcei(sounds[sound],AL_SOURCE_STATE,&state);
      if(AL_PLAYING != state)
          return false;
    return true;
}
void AL::stopAllSoundsExcept(vector<int>&sounds){
    bool stop;
    for(int i=0;i<this->sounds.size();i++){
        stop=true;
        for(int j=0;j<sounds.size();j++)
            if(sounds[j]==i){
                stop=false;
                break;
            }
        if(stop)alSourceStop(this->sounds[i]);
    }
}
bool AL::playSoundByName(string name){
    int i=0;
    for(string n:soundName)
        if(n==name){
            alSourcePlay(sounds[i]);
            return true;
        }else
            i++;
    return false;
}
bool AL::loadSound(char* path,string name,float vol,bool Loop){
    int currentLoading=sounds.size();
    sounds.push_back(NULL);
    buffers.push_back(NULL);
    ALboolean loop;
    if(Loop)
        loop=AL_TRUE;
    else
        loop=AL_FALSE;
    
    FILE *fp = NULL;
    fp=fopen(Util::newPath(path),"rb");
    if (!fp) return 0;

    char type[4];
    unsigned int size,chunkSize;
    short formatType,channels;
    unsigned int sampleRate,avgBytesPerSec;
    short bytesPerSample,bitsPerSample;
    unsigned int dataSize;

    fread(type,sizeof(char),4,fp);
    if(type[0]!='R' || type[1]!='I' || type[2]!='F' || type[3]!='F'){
        if(Util::DEBUG)printf("Error loading sound %d, err:1\n",currentLoading);
    }
    //return 0;

    fread(&size, sizeof(unsigned int),1,fp);
    fread(type, sizeof(char),4,fp);
    if (type[0]!='W' || type[1]!='A' || type[2]!='V' || type[3]!='E'){
        if(Util::DEBUG)printf("Error loading sound %d, err:2\n",currentLoading);
    }
    //return 0;

    fread(type,sizeof(char),4,fp);
    if (type[0]!='f' || type[1]!='m' || type[2]!='t' || type[3]!=' '){
        if(Util::DEBUG)printf("Error loading sound %d, err:3\n",currentLoading);
    }
    //return 0;

    fread(&chunkSize,sizeof(unsigned int),1,fp);
    fread(&formatType,sizeof(short),1,fp);
    fread(&channels,sizeof(short),1,fp);
    fread(&sampleRate,sizeof(unsigned int),1,fp);
    fread(&avgBytesPerSec,sizeof(unsigned int),1,fp);
    fread(&bytesPerSample,sizeof(short),1,fp);
    fread(&bitsPerSample,sizeof(short),1,fp);

    fread(type,sizeof(char),4,fp);
    if (type[0]!='d' || type[1]!='a' || type[2]!='t' || type[3]!='a'){
        if(Util::DEBUG)printf("Error loading sound %d, err:4\n",currentLoading);
    }
    //return 0;

    fread(&dataSize,sizeof(unsigned int),1,fp);

    unsigned char* buf= new unsigned char[dataSize];
    fread(buf,sizeof(unsigned char),dataSize,fp);

    ALuint frequency=sampleRate;
    ALenum format=0;
    alGenBuffers(1, &buffers[currentLoading]);
    alGenSources(1, &sounds[currentLoading]);
    if(bitsPerSample == 8){
        if(channels == 1)
            format = AL_FORMAT_MONO8;
        else if(channels == 2)
            format = AL_FORMAT_STEREO8;
    }
    else if(bitsPerSample == 16){
        if(channels == 1)
            format = AL_FORMAT_MONO16;
        else if(channels == 2)
            format = AL_FORMAT_STEREO16;
    }

    alBufferData(buffers[currentLoading], format, buf, dataSize, frequency);

    alSourcei (sounds[currentLoading], AL_BUFFER,buffers[currentLoading]);
    alSourcef (sounds[currentLoading], AL_PITCH,1.0f);
    alSourcef (sounds[currentLoading], AL_GAIN,vol);
    alSourcefv(sounds[currentLoading], AL_POSITION,SourcePos);
    alSourcefv(sounds[currentLoading], AL_VELOCITY,SourceVel);
    alSourcei (sounds[currentLoading], AL_LOOPING,loop );
    fclose(fp);
    soundName.push_back(name);
    delete[] buf;

    return 1;
}

bool AL::playSound(int sound){
    if(sound>=sounds.size())
        return false;
    alSourcePlay(sounds[sound]);
    return true;
}
bool AL::stopSound(int sound){
    if(sound>=sounds.size())
        return false;
    alSourceStop(sounds[sound]);
    return true;
}