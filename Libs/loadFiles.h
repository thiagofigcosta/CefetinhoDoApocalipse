#ifndef LOADFILES_H
#define LOADFILES_H
#include "Globals.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "../Classes/Util.hpp"
#include "../Classes/AL.hpp"
#include "../Classes/GL.hpp"

//TODO:definir aqui a struct de configuracoes
bool loadMaps(int nOfMaps);
bool loadTextures();
bool loadStrings();
bool loadMap(char* path);
bool loadSounds();
bool saveMap(char* path,int idx);
bool loadSettings();
bool saveSettings();

#endif	// LOADFILES_H
