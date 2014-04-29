#include "defines.h"
#include "P1.h"

extern Texture *_texture;
extern Camera *_camera;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
AVector2D* P1::CirclePosition(int segment, int sides) 
{
  AVector2D *r = new AVector2D(0.0,0.0);
  int count = 0;
  float f = 360/sides;
  float v = f*segment;
  float x = sin(DEG2RAD(v));
  float y = cos(DEG2RAD(v));
  r->x = x;
  r->y = y;  
  return r;
}

void P1::Spawn() 
{
  int seg = this->segs;
  for (int i = 0; i < seg; i++) {
   Thing *a = new Thing();
   // try to break up some of the pattern
   if (rand() % 4 == 2)
    continue;
   AVector2D *v = CirclePosition(i,seg);  
   a->a = 255;
   a->pos->x = x + (v->x * 20);
   a->pos->y = y + (v->y * 20);

   a->pos->x = x;
   a->pos->y = y;  
  
   a->r = this->r;
   a->g = this->g;
   a->b = this->b;

   a->force->x = v->x * (rand() % 20);
   a->force->y = v->y * (rand() % 20);
  
   a->w = 12;
   a->h = 12;
   plist.push_back(a);
   
   delete v; 
 }
  return;
}
void P1::Tick() 
{
  for( auto it = plist.begin(); it != plist.end();) {
    Thing *p = *it;
    p->pos->x += p->force->x;
    p->pos->y += p->force->y;
    //p->pos->y += 10;
    //if (p->pos->y >= SCREEN_HEIGHT) {
    //  it = plist.erase(it);
    //  delete p;
    //}
    ++it;  
  }
  unsigned int delta = SDL_GetTicks() - last;
  if (SDL_GetTicks() - last > 250) {
    last = SDL_GetTicks();
    Spawn();
    phase++;
  }
  //(*event_callback)(this,0,"particle_finished"); 
  return;
}

bool P1::Render(SDL_Renderer *renderer)
{
  for_each(plist.begin(), plist.end(), 
           [&](Thing *p) {		
            SDL_Texture *tex = 	_texture->GetTexture("images/brush-42.png");
            SDL_SetTextureColorMod(tex, p->r, p->g, p->b); 
          	SDL_SetTextureAlphaMod(tex, p->a);		  	
            renderTexture(tex, renderer,
                  POS_X(p->pos->x), POS_Y(p->pos->y),
                  p->w, p->h);
          p->a -= this->deg;
          if (p->a < 0) 
            p->a = 0;
    });
  Tick();
  if (phase >= 1)
    return false;
  return true;
}

P1::P1(int _x, int _y, int _segs, int _r, int _g, int _b, int _deg)
{
  phase = 0;
  r = _r;
  g = _g;
  b = _b;
  segs = _segs;
  deg = _deg;
  x = _x;
  y = _y;
  last = SDL_GetTicks();
  Spawn();
}

P1::P1(int _x, int _y) 
{ 
  phase = 0;

  r = 255;
  g = 255;
  b = 255;
  deg = 30;
  segs = 20;

  x = _x;
  y = _y;
  last = SDL_GetTicks();
  Spawn();
  return;
}

P1::~P1() 
{
  for( auto it = plist.begin(); it != plist.end();) {
    Thing *p = *it;
      it = plist.erase(it);
      delete p;
  }
  return;
}

