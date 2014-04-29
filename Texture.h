/*
  Texture Manager (used for loading and managing textures)
  this should make animation .. etc ..etc much simpler
*/
#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <vector>

#include "defines.h"

using namespace std;

class Tex {
 public:
  string fname;
  SDL_Texture *texture;
};

class Texture {
  SDL_Renderer *renderer;
  vector <Tex *> textures;
 public:
  void LoadTexture(string fname);
  SDL_Texture * GetTexture(string fname);
  Texture(SDL_Renderer *_renderer);
  ~Texture();
};

#endif
