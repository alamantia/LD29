/* Why isn't this a class? */
#ifdef ANDROID
#include <android/log.h>
#endif

#include <iostream>
#include <string>
#include <list>
#include <map>
#include <algorithm>
#include <functional>
#include "Thing.h"
#include "Context.h"
#include "Button.h"
#include "simplexnoise.h"
#include "defines.h"
#include "Drop.h"
#include "Context.h"
#include "Camera.h"
#include "Clouds.h"
#include "Enemy.h"
#include "Item.h"
#include "P1.h"

#include "Game.h"

#define GLIDE_MAX 100
#define DEG_ROT 8.0
#define ROT_INC 6.0
#define ROT_SEGMENTS 12
#define M_DEGRADE    0.1

extern  int   game_mode;
extern  float box_height;
extern  float box_width;
extern  float UNIT_HEIGHT;
extern  float UNIT_WIDTH;

bool game_running = false;

// used for detecting the possible toggle states

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

Clock *_clock;
extern Window *_window;
extern Audio  *_audio;
extern Camera *_camera;
extern Texture *_texture;
extern SDL_Renderer *renderer;

float rot_speed = DEG_ROT;
int tile_width  = 12;
int tile_height = 12;
int glide_end_time  = 0;
bool shooting = false;
bool shooting_mouse = false;
bool moving = false;
unsigned int moving_speed = 0;
unsigned int moving_time  = 0;
bool paused = false;
typedef  Thing * tile;

struct position_rect {
  int x;
  int y;
};

int bricks[] = {219, 178,177,176};

tile **tiles;
list<tile> gameObjects;
list<P1 *> P1s;
Thing *Player;

AVector2D  *vectorMouse;
AVector2D  *vectorAimPosition;
AVector2D  *vectorAim;
AVector2D  *vectorCurrent;
AVector2D  *vectorAimDelta;
AVector2D  *vectorPlayerDelta;
AVector2D  *vectorPlayer;

void b_callback(void *t, int type, string message)
{
  printf("Got callback %s\n", message.c_str());
  return;
}

void add_p1_bullet(int x, int y)
{
  P1 *p1 = new P1(x,y, 4, 131, 248, 184, 120);
  p1->event_callback = &b_callback;
  p1->r = 131;
  p1->g = 248;
  p1->b = 184;
  P1s.push_back(p1); 
}
void add_p1(int x, int y) 
{
#if 1 
  P1 *p1 = new P1(x,y);
  p1->event_callback = &b_callback;
  P1s.push_back(p1); 
#endif
  //_camera->Shake(1.0);
  return;
}

void add_smoke(int x, int y)
{
	static int last_player_smoke = 0;	
	if (SDL_GetTicks() - last_player_smoke < 60) 
		return;
	last_player_smoke = SDL_GetTicks();
	Thing *t = new Thing();
	t->w = 12;
	t->h = 12;
	t->x = x;
	t->y = y;
	t->r = 255;
	t->g = 255;
	t->b = 255;
	t->a = 255;
	t->time_value = SDL_GetTicks();
	t->type = LOL_SMOKE;
	gameObjects.push_back(t);
}
void draw_background()
{
  SDL_Rect pos;

  pos.x = 0;
  pos.y = 0;
  pos.w = SCREEN_WIDTH;
  pos.h = SCREEN_HEIGHT;
   SDL_RenderFillRect(_window->renderer, &pos);
  float s_height = WINDOW_WIDTH / 6;
  // "r":172,"g":124,"b":0
  float r = 12;
  float g = 12;
  float b = 12;
  SDL_SetRenderDrawColor(_window->renderer, r, g, b, 0);
  SDL_RenderFillRect(_window->renderer, &pos);
  return; 
  for (float s_y = 0; s_y < WINDOW_HEIGHT; s_y += s_height) {
    pos.x = 0;
    pos.y = s_y;
    pos.w = WINDOW_WIDTH;
    pos.h = s_height;
    SDL_RenderFillRect(_window->renderer, &pos);
  }
  return;
}

void aim_vector()
{
	float center_x = Player->x;
	float center_y = Player->y;
	
	float x = Player->x;
	float y = Player->y - 12;

	float translate_x = x - center_x;
	float translate_y = y - center_y;

	float cosa = cos(DEG2RAD(vectorAim->x));
	float sina = sin(DEG2RAD(vectorAim->x));
	
	//printf("player %f %f\n", Player->x, Player->y);
	//printf("rotation %f %f %f\n", vectorAim->x, cosa, sina); 

	float fx =  translate_x * cosa + translate_y * sina + center_x;
	float fy = -translate_x * sina + translate_y * cosa + center_y;

	vectorCurrent->x = fx - Player->x;
	vectorCurrent->y = fy - Player->y;

	return;
}
/* use brush-5 has the current sprite */
void render_aim()
{
	float center_x = Player->x;
	float center_y = Player->y;
	
	float x = Player->x;
	float y = Player->y - 12;

	float translate_x = x - center_x;
	float translate_y = y - center_y;

	float cosa = cos(DEG2RAD(vectorAim->x));
	float sina = sin(DEG2RAD(vectorAim->x));
	
	//printf("player %f %f\n", Player->x, Player->y);
	//printf("rotation %f %f %f\n", vectorAim->x, cosa, sina); 

	float fx =  translate_x * cosa + translate_y * sina + center_x;
	float fy = -translate_x * sina + translate_y * cosa + center_y;
	
	//printf("final %f %f\n", fx, fy);
		
	SDL_SetRenderDrawColor(_window->renderer, 255,255,255,255);
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	SDL_Texture *t = _texture->GetTexture("images/brush-30.png");

	/*
	renderTexture(t,
								 _window->renderer,
								POS_X(Player->x),
								POS_Y(Player->y) - 12,
								12, 12);
	*/

	vectorCurrent->x = fx - Player->x;
	vectorCurrent->y = fy - Player->y;

	vectorAimPosition->x = fx;
	vectorAimPosition->y = fy;
  SDL_SetTextureColorMod(t, 164, 228, 252);   
	SDL_SetTextureAlphaMod(t, 100);		
	renderTextureEx(t, 
							_window->renderer,
							POS_X(fx),
							POS_Y(fy),
							12, 12,
							-vectorAim->x, 
							SDL_FLIP_NONE);
	return;
}

float node_cost(float x1, float y1, float x2, float y2)
{
    return sqrtf((powf((x2 - x1),2)) + (powf((y2 - y1),2)));
}

bool can_render(int x, int y)
{
	float _x = POS_X(x);
	float _y = POS_Y(y);
	if (_x <= -12 || _x > SCREEN_WIDTH) {
			return false;
	}
	if (_y <= -12 || _y > SCREEN_HEIGHT) {
		return false;
	}
	return true;
}

Thing * get_player()
{
  return Player;
}

Thing* passable(void *skip, int x, int y, int w, int h)
{
	for (auto it = gameObjects.begin();  it != gameObjects.end(); ++it) {
		Thing *t = *it;
    if (t == skip) 
      continue;
		if (t->type == LOL_SMOKE || t->type == LOL_PLAYER || t->type == LOL_BULLET) {
			continue;
		}
		if (!can_render(t->x, t->y)) 
			continue;	
		if (t->contains_rect(x, y, w, h)) {
			return t;
		}
	}
	return nullptr;
}

 
Thing* passable(int x, int y, int w, int h)
{
	for (auto it = gameObjects.begin();  it != gameObjects.end(); ++it) {
		Thing *t = *it;
		if (t->type == LOL_SMOKE || t->type == LOL_PLAYER || t->type == LOL_BULLET) {
			continue;
		}
		if (!can_render(t->x, t->y)) 
			continue;	
		if (t->contains_rect(x, y, w, h)) {
			return t;
		}
	}
	return nullptr;
}

#define DEGRADE 0.01 

void move_player() 
{
  if (moving == false) {
    //if (glide_end_time < SDL_GetTicks()) {
    //  return;
    //}
    return;
  }
	float speed = 1.8;
	float tx = Player->x + (vectorPlayer->x * speed);
	float ty = Player->y + (vectorPlayer->y * speed);
 
#if 1 
  // reduce the play hitbot for movement
	if (passable(tx, ty, 10, 10) != nullptr) {
    vectorPlayer->x = -(vectorPlayer->x/4);
		vectorPlayer->y = -(vectorPlayer->y/4);
		vectorPlayer->y = 0;
    vectorPlayer->x = 0;
		return;
	}
#endif

	Player->x = tx;
	Player->y = ty;	
	return;
}

void render_player()
{
  SDL_SetRenderDrawColor(_window->renderer, 255, 255, 255, 255); 
  SDL_RendererFlip flip = SDL_FLIP_NONE;
  SDL_Texture *t = _texture->GetTexture("images/brush-1.png");
// 164,"g":228,"b":252	
  SDL_SetTextureColorMod(t, 164, 228, 252); 
  renderTexture(t, _window->renderer,
		POS_X(Player->x),
		POS_Y(Player->y),
		Player->w, Player->h);

	if (moving == false) {

		return;
	}

	//printf("-- MOVING %f %f\n", vectorCurrent->x, vectorCurrent->y);
	// what is our vector!!!!

	AVector2D *normal = vectorCurrent->Normal();	
	add_smoke(Player->x, Player->y);

	AVector2D *va = new AVector2D(0,0);
	va->x = vectorPlayer->x + normal->x;
	va->y = vectorPlayer->y + normal->y;	
	
	va->x = normal->x + vectorPlayer->x;
	va->y = normal->y + vectorPlayer->y;

	AVector2D *vb = va->Normal();
	vectorPlayer->x = vb->x;
	vectorPlayer->y = vb->y;
	delete va;
	delete vb;
	delete normal;
}

void render_brick(Thing *t) 
{
  SDL_SetRenderDrawColor(_window->renderer, 188, 188, 188, 255); 
  SDL_RendererFlip flip = SDL_FLIP_NONE;

	char fname[1024];
	memset(fname, 0, sizeof fname);
	sprintf(fname, "images/brush-%i.png",t->subtype);
  SDL_Texture *tex = _texture->GetTexture(fname);	
  SDL_SetTextureColorMod(tex, 188, 188,188);  
  renderTexture(tex, _window->renderer,
		POS_X(t->x),
		POS_Y(t->y),
		t->w, t->h);	
	return;
}

void render_bullet(Thing *t)
{
  SDL_SetRenderDrawColor(_window->renderer, 255, 255, 255, 255); 
  SDL_RendererFlip flip = SDL_FLIP_NONE;

	char fname[1024];
	memset(fname, 0, sizeof fname);
	sprintf(fname, "images/brush-37.png",t->subtype);
  SDL_Texture *tex = _texture->GetTexture(fname);

	//":"131","r":248,"g":184,"b":248	
  if (t-> source == SOURCE_PLAYER) {
    SDL_SetTextureColorMod(tex, 131, 248, 184); 
  } else {
    SDL_SetTextureColorMod(tex, 248, 184, 248);
  }
  renderTexture(tex, _window->renderer,
		POS_X(t->x),
		POS_Y(t->y),
		t->w, t->h);	
	unsigned int speed = 6;	
	t->x += t->dir->x * speed;
	t->y += t->dir->y * speed;
	return;
}

void fire_enemy_bullet(int x, int y, int type, AVector2D *direction) 
{
  Thing *t = new Thing();
	t->type = LOL_BULLET;
	t->subtype = 0;
	t->x = x;
  t->source = SOURCE_ENEMY;
	t->y = y;
	t->w = 12;
	t->h = 12;
	AVector2D *normal = direction->Normal();	
	t->dir->x = normal->x;
	t->dir->y = normal->y;
	gameObjects.push_back(t);
	delete normal;	
	return;
}

void fire_bullet() 
{
	static int last_player_bullet = 0;
	if (SDL_GetTicks() - last_player_bullet < 60) 
		return;
  last_player_bullet = SDL_GetTicks();

	SDL_PumpEvents();
	SDL_Cursor* mouse = SDL_GetCursor();
	int mX;
	int mY;
	SDL_GetMouseState(&mX,&mY);
	
	if (shooting_mouse) {
		AVector2D *mousePosition = convert_window_point(mX, mY, 0,0);
		AVector2D *vectorMouseAim = new AVector2D(mX - Player->x, (mY - 20) - Player->y);
		// translate to the position we want and fire as needed
		printf("Mouse fire %i, %i\n", mX, mY);
		printf("Mouse fire %f, %f\n", mousePosition->x, mousePosition->y - 20);
		AVector2D *vectorMouseAimNormal = vectorMouseAim->Normal();

		Thing *t = new Thing();
		t->type = LOL_BULLET;
		t->subtype = 0;
		t->x = Player->x;
		t->y = Player->y;
		t->w = 12;
		t->h = 12;
  	t->source = SOURCE_PLAYER;
		t->dir->x = vectorMouseAimNormal->x;
		t->dir->y = vectorMouseAimNormal->y;
		gameObjects.push_back(t);
	

		delete mousePosition;
		delete vectorMouseAimNormal;
		delete vectorMouseAim;
		return;
	}

	Thing *t = new Thing();
	t->type = LOL_BULLET;
	t->subtype = 0;
	t->x = vectorAimPosition->x;
	t->y = vectorAimPosition->y;
	t->w = 12;
	t->h = 12;
  t->source = SOURCE_PLAYER;
	AVector2D *normal = vectorCurrent->Normal();	
	t->dir->x = normal->x;
	t->dir->y = normal->y;
	gameObjects.push_back(t);
	delete normal;	
	return;
}

void render_smoke(Thing *t)
{
  SDL_SetRenderDrawColor(_window->renderer, t->r, t->g, t->b, 0); 
  SDL_RendererFlip flip = SDL_FLIP_NONE;
  SDL_Texture *tex = _texture->GetTexture("images/brush-4.png");
	SDL_SetTextureAlphaMod(tex, t->a);		
  renderTexture(tex, _window->renderer,
		POS_X(t->x),
		POS_Y(t->y),
		t->w, t->h);
	if (t->a > 10) {
		t->a -= 10;
	} else {
		t->a = 0;
	} 	
	SDL_SetTextureAlphaMod(tex, 255);		
	return;
}

void dead() 
{
	game_running = false;
  for (auto it = gameObjects.begin(); it != gameObjects.end();) {
        Thing *t = *it;
        it = gameObjects.erase(it);
        delete t;
  }
  Context::context()->total_health   = 5;
  Context::context()->current_health = 5;

  delete Player;
	delete _clock;
	delete vectorAim;
	delete vectorAimDelta;	
	delete vectorPlayerDelta;
	delete vectorCurrent;
	delete vectorPlayer;
	delete vectorAimPosition;
  setup_game();
  return;
}

void handle_bullets()
{
	list<Thing *> removeList;	
	for (auto it = gameObjects.begin(); it != gameObjects.end();) {
		Thing *t = *it;
		if (t->type != LOL_BULLET ) {
			++it;
			continue;
		}
		if (!can_render(t->x, t->y)) {
			++it;
			continue;
		}
  
    // check if bullet is hitting player .. take damage.
    if (t->source == SOURCE_ENEMY) { // future upgrades will change this but eh won't finish that in time
      if (Player->contains_rect(t->x, t->y, 10, 10)) {
          Context::context()->current_health -= 1;  
          // hit effects flash the bg red or something.. particles/shake?
          _camera->Shake(1);
          removeList.push_back(t);  
          ++it;
          continue;
      }
    }
		Thing *x = passable(t->x, t->y, 12, 12);
		if (x != nullptr) {
      if (x->type == LOL_ENEMY) {
        if (t->source != SOURCE_PLAYER) {
            ++it;
           continue;
        }
        bool hr = x->TakeDamage(10);
         if (hr == false) {
			    auto findIter = std::find(gameObjects.begin(), gameObjects.end(), x);
			      if (findIter != gameObjects.end()) {
				      add_p1(t->x, t->y);
				      removeList.push_back(x);
			    }
          add_p1_bullet(t->x, t->y);          
        }
        removeList.push_back(t);
        ++it;
        continue;
      }
  
      if (x->type == LOL_BRICK) {
        it = gameObjects.erase(it);
			  x->health -= 10;
        update_subtype(x);
        if (x->health  > 0) {
          if (t->source == SOURCE_PLAYER) {  
            add_p1_bullet(t->x, t->y);
          }
          removeList.push_back(t);
          ++it;
          continue;
        }
			  auto findIter = std::find(gameObjects.begin(), gameObjects.end(), x);
			  if (findIter != gameObjects.end()) {
				  add_p1(t->x, t->y);
				  removeList.push_back(x);
			  }
        removeList.push_back(t);
        ++it;
        continue;
      }
    }
   ++it;
	}
	for (auto it = removeList.begin(); it != removeList.end();++it) {
		  auto where = remove(gameObjects.begin(), gameObjects.end(), *it);
  		gameObjects.erase(where, gameObjects.end());
      //delete *it;
	}
  
}
void render_game()
{
	if (game_running == false)
		return;
	_camera->x = Player->x - SCREEN_WIDTH/2;
	_camera->y = Player->y - SCREEN_HEIGHT/2;

  SDL_RenderClear(_window->renderer);
  _window->BeginTextureRender();
  draw_background();
	for_each(gameObjects.begin(), gameObjects.end(), 
           [](Thing *thing) {	
						if (thing->type == LOL_BULLET || thing->type == LOL_ENEMY_BULLET) {
							render_bullet(thing);
						}
						if (!can_render(thing->x, thing->y)) {
							return;
						}	
						if (thing->type == LOL_SMOKE) {
							render_smoke(thing);
						}
						if (thing->type == LOL_BRICK) {
							render_brick(thing);
						}
            if (thing->type == LOL_ENEMY) {
              thing->Draw(_window->renderer);
            } 
	   });
  
  for (auto it = P1s.begin(); it != P1s.end();) {
    P1 *p1 = *it;
    if(!p1->Render(_window->renderer)) {
      it = P1s.erase(it);
      delete p1;
      continue; 
    } 
    ++it;
  } 
  handle_bullets();	
	render_player();
	move_player();
	render_aim();
	vectorAim->x += vectorAimDelta->x;
	_window->EndTextureRender();
  _clock->Tick();

	if (shooting == true) {
		fire_bullet();
	}

	_camera->x = Player->x - SCREEN_WIDTH/2;
	_camera->y = Player->y - SCREEN_HEIGHT/2;
	_camera->Tick();
  if (Context::context()->current_health <= 0) {
    dead();
  }
  return;
}

void do_inertia()
{
	aim_vector();
	AVector2D *normal = vectorCurrent->Normal();
	printf("V %f %f\n", normal->x, normal->y);
	//vectorPlayer->x = normal->x - vectorPlayer->x;
	//vectorPlayer->y = normal->y - vectorPlayer->y;
	delete normal;	
	return;
}

void handle_event(SDL_Event e)
{
	if (!game_running)
		return;
	// Touch (most touch processing is in the UI hander side

	// Mouse

   SDL_MouseButtonEvent me = e.button;
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
  if (e.type == SDL_MOUSEBUTTONUP) {
    if (me.button == SDL_BUTTON_LEFT) {
			shooting_mouse = false;
			shooting = false;
    }
  }


	// Keyboard
	if (e.type == SDL_KEYUP) {
		int keycode = e.key.keysym.sym;
		if (keycode == SDLK_RIGHT || keycode == SDLK_LEFT || keycode == SDLK_a || keycode == SDLK_d) {
	    //rot_speed = DEG_ROT;
  		vectorAimDelta->x = 0;
		}
		if (keycode == SDLK_UP || keycode == SDLK_w) {
			//do_inertia();
      glide_end_time = SDL_GetTicks() + GLIDE_MAX;
			moving = false;
		}
    if (keycode == SDLK_LSHIFT) {
      rot_speed = DEG_ROT;
    }
		if (keycode == SDLK_SPACE) {
			shooting = false;
		}
	}
  if (e.type == SDL_KEYDOWN) {
    int keycode = e.key.keysym.sym;
    switch (keycode) {
    case SDLK_LSHIFT: {
      rot_speed = 8;
      break;
    }
    case SDLK_SPACE: {
    	shooting = true;
		  break;
    }
		case SDLK_p: {
      paused = !paused;
    }
    case SDLK_d:
    case SDLK_RIGHT: {
			vectorAimDelta->x = -(rot_speed); 
      break;
    }
    case SDLK_a:
    case SDLK_LEFT: {
			vectorAimDelta->x = rot_speed;
      break;
    }	
		case SDLK_w:
    case SDLK_UP: {  
    	moving_time = SDL_GetTicks();
			moving = true;		
			break;
    }
    default:
      break;
    }
  }
}

void preload_textures()
{
	for (int i = 0; i < 248; i++) {
		char fname[1024];
		memset(fname, 0, sizeof fname);
		sprintf(fname, "images/brush-%i.png",i);
		_texture->GetTexture(fname);	
	}
	return;
}

void player_callback(void *t, int type, string message)
{
  printf("Got player callback\n");
  return;
}


void update_subtype(Thing *t)
{
  if (t->health <= 100) {
    t->subtype = bricks[0];
  }
  if (t->health <= 75) {
    t->subtype = bricks[1];
  }
  if (t->health <= 50) {
    t->subtype = bricks[2];
  }
  if (t->health <= 25) {
    t->subtype = bricks[3];
  }
}

void add_brick(int x, int y) 
{
	Thing *t = new Thing();
	t->type = LOL_BRICK;
	t->x = x;
	t->y = y;
	t->w = 12;
	t->h = 12;
  // subtype is used to indicate health
	t->subtype = bricks[rand() % (sizeof(bricks)/(sizeof(int)))];
  if (t->subtype == bricks[0]) {
      t->health = 100;
  }
  if (t->subtype == bricks[1]) {
      t->health = 75;
  }
  if (t->subtype == bricks[2]) {
    t->health = 50;
  }
  if (t->subtype == bricks[3]) {
    t->health = 25;
  }
	gameObjects.push_back(t);
	return;
}

void add_brick(int x, int y, int index) 
{
	Thing *t = new Thing();
	t->type = LOL_BRICK;
	t->x = x;
	t->y = y;
	t->w = 12;
	t->h = 12;
  // subtype is used to indicate health
	t->subtype = bricks[index];
  if (t->subtype == bricks[0]) {
      t->health = 100;
  }
  if (t->subtype == bricks[1]) {
      t->health = 75;
  }
  if (t->subtype == bricks[2]) {
    t->health = 50;
  }
  if (t->subtype == bricks[3]) {
    t->health = 25;
  }
	gameObjects.push_back(t);
	return;
}

// should probably make then stronger once they are beyond a specific point
void add_enemy(int x, int y, float v)
{
  Enemy *t = new Enemy();
  t->x = x;
  t->y = y;
  t->w = 12;
  t->h = 12;
  t->type = LOL_ENEMY;
  gameObjects.push_back(t);
}

void add_item(int x, int y, float v)
{

}

void gen_world()
{
	for (int x = -1000; x < 1000; x += 12) {
		for (int y = -1000; y < 1000; y += 12) {

/*
float scaled_octave_noise_2d(  const float octaves,
                            const float persistence,
                            const float scale,
                            const float loBound,
                            const float hiBound,
                            const float x,
                            const float y);
*/
      float pX = SCREEN_WIDTH/2;
      float pY = SCREEN_HEIGHT/2;

      float octaves = 20;
      float persistence = 0.5;
      float scale = 0.01;
      float v = scaled_octave_noise_2d(octaves, persistence, scale, 0, 10, x, y);
//      printf("%f\n", v);
			if (v <= 5.0) {
        if (v <= 2.0) {
          add_enemy(x, y, v);  
          continue;     
        }
        if (v <= 2.0) {
          add_item(x, y, v);
          continue;
        }
        continue;
      }
      if (v >= 8.5) {
        add_brick(x, y, 0);
        continue;
      } 
      if (v >= 7.0) {
        add_brick(x, y, 1);
        continue;
      }
      if (v >= 6.0) {
        add_brick(x, y, 2);
        continue;
      }
      if (v >= 5.0) {
        add_brick(x, y, 3);
        continue;
      }
      //add_brick(x,y);
		}
	}
	return;
}

void setup_game()
{
	_clock = new Clock();
	vectorAim 				= new AVector2D(0,0);
	vectorAimDelta		= new AVector2D(0,0);	
	vectorPlayerDelta = new AVector2D(0,0);
	vectorCurrent 		= new AVector2D(0,0);
	vectorPlayer			= new AVector2D(0,0);
	vectorAimPosition = new AVector2D(0,0);
	
	tile_width  =  12;
  tile_height =  12;  

  printf("Tiles (%i %i)\n", 
	tile_width,
	tile_height);
	
	preload_textures();  
  Player = new Thing();
  Player->type = LOL_PLAYER;
  Player->x = SCREEN_WIDTH/2;
  Player->y = SCREEN_HEIGHT/2;
  Player->w = tile_width;
  Player->h = tile_height;
  Player->event_callback = &player_callback;
 	_camera->x = 0;
	_camera->y = 0; 
  // generate stuff
  //gen_monsters(); // moved to gen_world
  //gen_items();    // moved to gen_world
	gen_world();
	_camera->Reset();
	game_running = true;
	//add_brick(0,0);
	return;
}

void Game::render_game()
{
	return;
}

void Game::setup_game()
{
	return;
}

void Game::handle_event(SDL_Event e)
{
	return;
}

Game::Game()
{
	return;
}

Game::~Game()
{
	return;
}
