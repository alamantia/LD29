// storage point for various globals .. shit gamejam code
#include <iostream>
#include "defines.h"

Window *_window;
Audio  *_audio;
Camera *_camera;
Texture *_texture;



// game texture width - height
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

// game window width -height
extern int WINDOW_HEIGHT;
extern int WINDOW_WIDTH;

int game_mode = 1;

float box_height = 30;
float box_width  = 30;

float UNIT_HEIGHT = 32;
float UNIT_WIDTH  = 32;

void setup() 
{
  return;
}

/*
   if (e.type == SDL_MOUSEBUTTONDOWN) {
    if (me.button == SDL_BUTTON_LEFT) {
			shooting = true;
			shooting_mouse= true;
      printf("Click at %i,%i\n", me.x, me.y);
      // converts window coords to game texture coords
			// we need to convert WINDOW position to screen POSITION first! 
			//float y_real = (float)me.y / (float)(WINDOW_HEIGHT - 40);
			float y_real = (float)me.y / (float)(WINDOW_HEIGHT + 20);
      float y_screen = SCREEN_HEIGHT * y_real;
      float x_real = (float) me.x / (float) WINDOW_WIDTH;
      float x_screen = SCREEN_WIDTH * x_real;
			int	  game_x = (int)floor(x_screen + 0.5);
			int		game_y = (int)floor(y_screen + 0.5);
    }
  }
*/

// convert a point to game texture from screen position
// x1,y1 window
// x2,y2 screen / game
AVector2D * convert_window_point(int x1, int y1, int x2, int y2)
{
	AVector2D *p = new AVector2D(0,0);
	
	float y_real = (float)y1 / (float)(WINDOW_HEIGHT);
  float y_screen = SCREEN_HEIGHT * y_real;

	float x_real = (float) x1 / (float) WINDOW_WIDTH;
	float x_screen = SCREEN_WIDTH * x_real;

	p->x = floor(x_screen + 0.5);
	p->y = floor(y_screen + 0.5);
	return p;
}

SDL_Texture* LoadImage(SDL_Renderer *renderer, std::string file){
  SDL_Texture* tex = nullptr;
  tex = IMG_LoadTexture(renderer, file.c_str());
  if (tex == nullptr) {
    
  }
  return tex;
}

void ApplySurface(int x, int y, SDL_Texture *tex, SDL_Renderer *rend){
  SDL_Rect pos;
  pos.x = x;
  pos.y = y;
  SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);
  SDL_RenderCopy(rend, tex, NULL, &pos);
}

/*
int SDL_RenderCopy(SDL_Renderer*   renderer,
                   SDL_Texture*    texture,
                   const SDL_Rect* srcrect,
                   const SDL_Rect* dstrect)
                   
                   
int SDL_RenderCopyEx(SDL_Renderer*          renderer,
                     SDL_Texture*           texture,
                     const SDL_Rect*        srcrect,
                     const SDL_Rect*        dstrect,
                     const double           angle,
                     const SDL_Point*       center,
                     const SDL_RendererFlip flip)

                     SDL_FLIP_NONE
                     do not flip
                     SDL_FLIP_HORIZONTAL
                     flip horizontally
                     SDL_FLIP_VERTICAL
                     flip vertically
                     
*/

void renderTextureEx(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h, double angle, SDL_RendererFlip flip){
  SDL_Rect dst;
  SDL_Point center;
  dst.x = x;
  dst.y = y;
  dst.w = w;
  dst.h = h;
  center.x = 0;
  center.y = 0;
  SDL_RenderCopyEx(ren, tex, NULL, &dst, angle, NULL, flip);
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h){
  SDL_Rect dst;
  dst.x = x;
  dst.y = y;
  dst.w = w;
  dst.h = h;
  SDL_RenderCopy(ren, tex, NULL, &dst);
}

