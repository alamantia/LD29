#include "Enemy.h"
#include "Game.h"
#include "defines.h"
#include "simplexnoise.h"

extern Window *_window;
extern Audio  *_audio;
extern Camera *_camera;
extern Texture *_texture;
extern SDL_Renderer *renderer;


void Enemy::Tick()
{
  int segs = 9;
  float octaves = 20;
  float persistence = 0.4;
  float scale = 0.02;
  Thing *Player = get_player();
   if (!can_render(this->x, this->y)) {
    return;
  }
  //float nx = scaled_octave_noise_2d(octaves, persistence, scale, 0, segs, x, rand());
  //float ny = scaled_octave_noise_2d(octaves, persistence, scale, 0, segs, rand(), y);
  // WHERE TO GO!? just pick a point on a circle and be done
  if ( (SDL_GetTicks() - time_value) > 1000) {
    time_value = SDL_GetTicks();
    float nx = scaled_octave_noise_2d(octaves, persistence, scale, 0, segs, SDL_GetTicks(), SDL_GetTicks());
    AVector2D *v = AVector2D::CirclePoint(floor(nx), segs);
    AVector2D *normal = v->Normal();
    dir->x = normal->x;
    dir->y = normal->y;
    delete normal;
    delete v;
  }
  float tx =  floor( ((dir->x * speed) + this->x)  + 0.5);
  float ty =  floor (((dir->y * speed) + this->y) + 0.5);
  Thing *pass = passable(this, tx, ty, 10, 10);
  if (pass == nullptr || pass == this) {
      this->x = tx;
      this->y = ty;
  } else {
    time_value = 0;
  }
  if (SDL_GetTicks() - time_fire > 1200) {
    time_fire = SDL_GetTicks();
    // should do on the stack!
    AVector2D *pv = new AVector2D(Player->x, Player->y);
    AVector2D *ov = new AVector2D(this->x, this->y);
    AVector2D *dv = pv->Sub(ov);
    fire_enemy_bullet(this->x, this->y, 0, dv);    
    delete dv;
    delete pv;
    delete ov; 
  }
  return;
}

bool Enemy::TakeDamage(int amount)
{
  health -= amount;
  if (health <= 0) {
    return false;
  }
  return true;
}

void Enemy::Draw(SDL_Renderer *renderer)
{
  SDL_SetRenderDrawColor(renderer, 252, 0, 0, 255); 
  SDL_RendererFlip flip = SDL_FLIP_NONE;
	char fname[1024];
	memset(fname, 0, sizeof fname);
	sprintf(fname, "images/brush-%i.png",2);
  SDL_Texture *tex = _texture->GetTexture(fname);	
  SDL_SetTextureColorMod(tex, 0, 0,252);  
  renderTexture(tex, renderer,
		POS_X(this->x),
		POS_Y(this->y),
		this->w, this->h);	
  Tick();
  return;
}

Enemy::Enemy() 
{
  time_fire = 0;
  int r = (rand() % 4);
  switch (r) {
    case 1:
    speed = 3;
    break;
    case 2: 
     speed = 2.0;
     break;
    case 3:
      speed = 1.5;
      break;
    default:
      speed = 1.25;
      break;
  }
  health = 10;
  return;
}
