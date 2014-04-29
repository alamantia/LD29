// sad attempt at doing some UI within SDL

#include <functional>
#include <algorithm>
#include "UserInterface.h"
#include "Button.h"
#include "Texture.h"
#include "Camera.h"
#include "Context.h"

extern int WINDOW_HEIGHT;
extern int WINDOW_WIDTH;

extern Texture *_texture;
extern Camera  *_camera;

void UserInterface::Draw(SDL_Renderer *renderer)
{
  SDL_Rect dst;
	dst.x = 0;
	dst.y = WINDOW_HEIGHT-40;
	dst.w = WINDOW_WIDTH;
	dst.h = 40; 
  //renderTexture(_texture->GetTexture("footer.png"), renderer, POS_X(dst.x), POS_Y(dst.y), dst.w,dst.h);
	//DrawButtons(renderer);
 //                    Context::context()->userInterface->Draw(renderer);
  
  int max_health     = Context::context()->total_health;
  int current_health = Context::context()->current_health;

  /* draw the health bar */
  for (int i = 0; i < max_health; i++) {
    int x = i * 12;
    SDL_Texture *tex = _texture->GetTexture("images/brush-3.png");
    SDL_SetTextureColorMod(tex, 95, 95,95);    
    if (i <= (current_health-1)) {
      SDL_SetTextureColorMod(tex, 242, 0,0);
    }  
    renderTexture(tex, renderer, x, 4, 12, 12);
  }
  
	return;
}

void UserInterface::DrawButtons(SDL_Renderer *renderer)
{
  SDL_Texture *bg_off;
  SDL_Texture *bg_on;
  
  bg_off = _texture->GetTexture("button.png"); 
  bg_on = _texture->GetTexture("button.png");
  
  for_each(buttons.begin(), buttons.end(), 
	   [renderer](Button *button) { 
	     button->Draw(renderer);
	   });
  return;
}

void UserInterface::AddButton(string _id, float x, float y, float w, float h, string img)
{
	Button *button = new Button(_id);
	button->x = x;
	button->y = y;
	button->w = w;
	button->h = h;
	button->defaultImagePath = img;
	buttons.push_back(button);
	return;
}

UserInterface::UserInterface(void)
{  
  float button_width   = 40;
  float button_height  = 40;
  float button_padding = 10;
     
  AddButton("activate-button",  
	    WINDOW_WIDTH- ((button_width + button_padding) * 2), 
	    WINDOW_HEIGHT-button_height,
	    button_width, 
	    button_height,
	    "up_arrow.png"
	    );
  
  /* 
  AddButton("jump-button",  
	    WINDOW_WIDTH-(button_width + button_padding), 
	    WINDOW_HEIGHT-button_height,
	    button_width, 
	    button_height,
	    "up_arrow.png"
	    );
  
  AddButton("left-button",  0, 
	    WINDOW_HEIGHT-button_height, 
	    button_width, 
	    button_height,
	    "left_arrow.png"
	    );

  AddButton("right-button", 
	    (button_width + button_padding), 
	    WINDOW_HEIGHT-button_height,
	    button_width, 
	    button_height,
	    "right_arrow.png"
	    );
*/
}

void UserInterface::Event(SDL_Event e)
{ 
  
  for_each(buttons.begin(), buttons.end(), 
           [e](Button *button) { 
             button->Event(e);
           });
}

UserInterface::~UserInterface(void)
{

}

