#include "Texture.h"

Texture::Texture(SDL_Renderer *_renderer) {
  renderer = _renderer;
}

SDL_Texture * Texture::GetTexture(string fname)
{
  for (int i = 0; i < textures.size(); i++) {
    Tex *t = textures[i];
    if (fname.compare(t->fname) == 0) {
      return t->texture;
    }
  }
  // looks like we have to allocate the texture
  Tex *t = new Tex();
  t->fname = fname;
  t->texture = LoadImage(renderer, fname);
  textures.push_back(t);
  return t->texture;
}

