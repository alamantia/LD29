#ifndef DEFINES_H
#define DEFINES_H
#ifndef  _WIN32

#ifdef ANDROID
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#else
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"
#endif

#else
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#endif
#include <math.h>
#include <algorithm>
#include <functional>
#include "AVector2D.h"
#include "Audio.h"
#include "Window.h"
#include "Camera.h"
#include "Thing.h"
#include "Texture.h"
#include "Clock.h"

#define POS_X(x) _camera->PositionX((x))
#define POS_Y(y) _camera->PositionY((y))

#define BOX_SCALE 8
#define TEXTURE_SIZE 64
#define nullptr NULL 

#define BOX_WIDTH  8
#define BOX_HEIGHT 12

#define BOARD_Y 60
#define BOARD_X 60

#define DEG2RAD(a) ((a) * M_PI / 180.0)
#define RAD2DEG(a) ((a) * 180.0 / M_PI)
#define DMS2DD(d,m,s) ((d) + ((m) / 60.0) + ((s) / 3600.0))

/* defines */
void drop_box_wave(int step, int direction, float speed);
void drop_box();

enum STATEZ {
  STATE_ENABLED,
  STATE_DISABLED,
};

enum TEXTURES {
  TEXTURE_PLAYER_1,
  TEXTURE_PLAYER_LIFT,
  TEXTURE_CUBE_1,
  TEXTURE_CUBE_2,
  TEXTURE_CUBE_3,
  TEXTURE_CUBE_4,

  TEXTURE_EXPLODE_1,
  TEXTURE_EXPLODE_2,
  TEXTURE_EXPLODE_3,
  TEXTURE_EXPLODE_4,
  TEXTURE_EXPLODE_5,
};

enum COLORZ {
  COLOR_1,
  COLOR_2,
  COLOR_3,
  COLOR_4,
};

enum SOURCE {
  SOURCE_PLAYER,
  SOURCE_ENEMY,
};
enum PICZ {
  PIC_BOAT, 
  PIC_WHALE,
  PIC_BG,
  PIC_BOX_1,
};

enum WALLZ {
  RIGHT_WALL = 0xB00B13,
  LEFT_WALL  = 0xB00B,
};

enum LOLZ {
  LOL_NONE,
  LOL_ENEMY,
	LOL_BRICK,
  LOL_ITEM,
  LOL_PLAYER,
  LOL_BULLET,
  LOL_ENEMY_BULLET,
  LOL_HARPOON_1,
	LOL_SMOKE,
  LOL_WHALE,
  LOL_BOX,
	LOL_TRAIL,
  LOL_BASIC_PARTICLE,
  LOL_PHYSICS_PARTICLE,
};

enum DIR {
  DIR_LEFT,
  DIR_RIGHT,
  DIR_NONE,
};

enum TZ {
  T_NONE,
  T_LEFT,
  T_RIGHT,
};

SDL_Texture* LoadImage(SDL_Renderer *renderer, std::string file);
void ApplySurface(int x, int y, SDL_Texture *tex, SDL_Renderer *rend);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
void renderTextureEx(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h, double angle, SDL_RendererFlip flip);

void mouse_event(string id, int type);

#endif
