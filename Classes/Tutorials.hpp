#ifndef TUTORIALS_H
#define TUTORIALS_H

#include "Util.hpp"
#include "GL.hpp"

class Tutorials {
public:
  Tutorials(string text,int key);
  Tutorials(const Tutorials& orig);
  virtual ~Tutorials();
  void draw();
  void refresh(string text,int key);
  void drawWhispText(string text);
  static bool showTutorials;
  static int pressedKey;
  
  static string initHelp;
  static string atackHelp;
  static string jumpHelp;
  static string powerupHelp;
  static string rangedAtkHelp;
  static string bossHelp;
  static string gradHelp;
  static string posHelp;
  static string winHelp;
  static bool isPaused;
  
private:
  GLuint GLlist;
  bool isCalled;
  string text;
  int key;
};

#endif /* TUTORIALS_H */
