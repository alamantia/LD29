#pragma once

#include <string>

#include "Thing.h"
#include "defines.h"

using namespace std;

enum BUTTON_STAES {
	BUTTON_UNSELECTED,
	BUTTON_SELECTED,
	BUTTON_CLICKED,
	BUTTON_PRESSED,
  BUTTON_UNFOCUS,
};

class Button :
	public Thing
{
 public:
  string id;
  bool touching;
  int finger;
  int state;
  
  bool draggable;

  string defaultImagePath;
  string defaultBgPath;

  SDL_Texture *selected_bg;
  SDL_Texture *default_bg;
  SDL_Texture *default_image;
  SDL_Texture *selected_image;
  
  void Draw(SDL_Renderer *renderer);
  void Event(SDL_Event event);
  
  Button(string _id);
  ~Button(void);
};



