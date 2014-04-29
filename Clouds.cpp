#include "Clouds.h"

extern Texture *_texture;

void Clouds::Render(SDL_Renderer *renderer) 
{
  for_each(clouds.begin(), clouds.end(), 
           [renderer](Cloud *c) {				
            SDL_Texture *c_tex = nullptr;
            if (c->type == CLOUD_1) {
              c_tex = _texture->GetTexture("cloud-1.png");
            } else if (c->type == CLOUD_2) {
              c_tex = _texture->GetTexture("cloud-2.png");
            }
            renderTexture(c_tex, renderer,
                  c->pos->x, c->pos->y,
                  c->w, c->h);
                  c->pos->x += c->speed;
                  if (c->pos->x > 640) {
                    c->pos->x = 0;
                  }    
    });
 return;
}

Clouds::Clouds() {
  Cloud *c;

  c = new Cloud();
  c->speed = 2.0;
  c->pos->x = 0;
  c->pos->y = 0;
  c->type = CLOUD_1;
  c->w = 50;
  c->h = 20;
  clouds.push_back(c);


  c = new Cloud();
  c->speed = 1.0;
  c->pos->x = 120;
  c->pos->y = 120;
  c->type = CLOUD_2;
  c->w = 50;
  c->h = 20;
  clouds.push_back(c);


  c = new Cloud();
  c->speed = 1.0;
  c->pos->x = 0;
  c->pos->y = 60;
  c->type = CLOUD_1;
  c->w = 50;
  c->h = 20;
  clouds.push_back(c);


 return;
}

Clouds::~Clouds() {
  return;
}
