#ifndef WINDOW_H
#define WINDOW_H


#include "defines.h"

class Window {
 public:
  void Init();
  void Draw(SDL_Texture*, ...);
  void Clear();
  void Present();
  void RenderGame();
  
  void BeginTextureRender();
  void EndTextureRender();

  Window();
  ~Window();

  SDL_Window   *window;
  SDL_Renderer *renderer;
  SDL_Texture  *gameTexture;
};

#endif
