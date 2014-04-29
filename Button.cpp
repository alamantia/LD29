#include "defines.h"
#include "Button.h"

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

// render a button
void Button::Draw(SDL_Renderer *renderer)
{
	SDL_Rect dst;
	SDL_Texture *tex;
        
	if (default_image == nullptr) {
	  default_image = LoadImage(renderer, defaultImagePath);
	}
	
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	
	switch (state) {
        case BUTTON_SELECTED: 
          tex = default_image;
          break;
        case BUTTON_UNSELECTED:
          tex = default_image;
          break;
        }
	renderTexture(tex, renderer, dst.x, dst.y, dst.w, dst.h);
}

// really light, simple button event processing loop .. UI elements .. etc
void Button::Event(SDL_Event event)
{
  if (event.type == SDL_FINGERDOWN) {
    if (touching == true) {
      if (finger != event.tfinger.fingerId) {
        return;
      } 
    }
    touching = true;
    finger = event.tfinger.fingerId;
    float x = event.tfinger.x;
    float y = event.tfinger.y;
  
    float screen_x = floor(SCREEN_WIDTH  * x);
    float screen_y = floor(SCREEN_HEIGHT * y);
    if (this->contains_point(screen_x, screen_y)) {
      mouse_event(id, BUTTON_SELECTED);
    }
  }
  
  if (event.type == SDL_FINGERMOTION) {
    float x = event.tfinger.x;
    float y = event.tfinger.y;
    float screen_x = floor(SCREEN_WIDTH  * x);
    float screen_y = floor(SCREEN_HEIGHT * y);
    if (finger != event.tfinger.fingerId) 
      return; 
  if (touching == false)
    return; 
  if (!this->contains_point(screen_x, screen_y)) {
      touching = false;   
      mouse_event(id, BUTTON_UNFOCUS);
    } else {
      touching = true;
      mouse_event(id, BUTTON_SELECTED);
    }
  }
  if (event.type == SDL_FINGERUP) {
    if (touching == false) {
      return;
    }
    finger = 0;      
    
    float x = event.tfinger.x;
    float y = event.tfinger.y;
  
    float screen_x = floor(SCREEN_WIDTH  * x);
    float screen_y = floor(SCREEN_HEIGHT * y);
    if (this->contains_point(screen_x, screen_y)) {
      touching = false;
      finger = 0;
      mouse_event(id, BUTTON_CLICKED);
    } 
   }
#ifdef ANDROID
  return; 
#endif

#ifdef IOS
  return;
#endif

  SDL_MouseButtonEvent e = event.button;
   
  if (!this->contains_point(e.x, e.y)) {
    if (state == BUTTON_SELECTED) {
      if (event.type == SDL_MOUSEMOTION) {
        state = BUTTON_UNSELECTED;
        mouse_event(id, BUTTON_UNSELECTED);
      }
    }
  }
  
  if (event.type == SDL_MOUSEMOTION) {
    if (this->contains_point(e.x, e.y)) {
      
    }
  }
  
  if (event.type == SDL_MOUSEBUTTONDOWN) {
    if (e.button == SDL_BUTTON_LEFT) {
      if (this->contains_point(e.x, e.y)) {          
	      state = BUTTON_SELECTED;
	      mouse_event(id, BUTTON_SELECTED);
	      return;
      }
    }
  }
  
  if (event.type == SDL_MOUSEBUTTONUP) {
    if (e.button == SDL_BUTTON_LEFT) {
      if (this->contains_point(e.x, e.y)) {          
	      if (state == BUTTON_SELECTED) {
	      mouse_event(id, BUTTON_CLICKED);
	    }
	    state = BUTTON_UNSELECTED;
      }
    }
  }
  // mouse_event(id, state);
}

Button::Button(string _id)
{
  id = _id;
  finger = 0;
  touching = false;
  default_image = nullptr;
  state = BUTTON_UNSELECTED;
  default_bg = nullptr;
  selected_bg = nullptr;
  draggable = 0;
}

Button::~Button(void)
{

}

