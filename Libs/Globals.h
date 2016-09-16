#ifndef GLOBALS_H
#define GLOBALS_H
#include "../Classes/Util.hpp"
#include "../Classes/Player.hpp"
#include "../Classes/AL.hpp"
#include "../Classes/GL.hpp"
//TODO: definir aqui todas as variaveis globais e objetos,definir aqui vetores de animacao
extern vector<nTMap> maps;

extern Player *player;
extern Mechanics *world;

extern nTColor clearColor;
extern vector<GLenum> enables;

extern AL *al;
extern GL *gl;

extern int languageIdx;

#endif	// GLOBALS_H