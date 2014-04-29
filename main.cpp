/*
	LD29 
		- JSON parser get it going
		- Clear the main game so we can get a new thing running
*/
#include <iostream>
#include <string>
#include <list>
#include <map>
#include <algorithm>
#include <functional>
#include <fstream>
#include <cerrno>

#include "Game.h"
#include "Button.h"
#include "simplexnoise.h"
#include "defines.h"
#include "Drop.h"
#include "Context.h"
#include "nxjson.h"

using namespace std;

extern  int   game_mode;
extern  float box_height;
extern  float box_width;
extern  float UNIT_HEIGHT;
extern  float UNIT_WIDTH;

int board_y = 60;
int board_x = 60;

int right_wall = RIGHT_WALL;
int left_wall  = LEFT_WALL;

bool pause = false;

// used for detecting the possible toggle states

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

int fucking_timer = 0;

extern Window *_window;
extern Audio  *_audio;
extern Camera *_camera;
extern Texture *_texture;
SDL_Renderer *renderer = nullptr;
SDL_Texture  *pics[TEXTURE_SIZE];

unsigned int last_match = 0;

float dir_speed = 15.0f;
float max_vel   = 30.0f;

float force = 80;
static bool j_is_up = true;

Thing *player;

list<Thing *> things;
list<Thing *> thingsToDrop;

bool mouse_down = false;

float mouse_x1  = 0;
float mouse_y1  = 0;

float mouse_x2 = 0;
float mouse_y2 = 0;

// add a quick explosion particle -- guide for quick tutorial animations

void AddExplosion(float x, float y)
{
  Thing *t = new Thing();
 /*
*/ 
  // add the textures we want to worth with
  t->AddTexture(pics[TEXTURE_EXPLODE_1]);
  t->AddTexture(pics[TEXTURE_EXPLODE_2]);
  t->AddTexture(pics[TEXTURE_EXPLODE_3]);
  t->AddTexture(pics[TEXTURE_EXPLODE_4]);
  t->AddTexture(pics[TEXTURE_EXPLODE_5]);

  int d = 30;

  // define the animation we wish to play
  t->AddAnimationFrame("1", 0, d);
  t->AddAnimationFrame("1", 1, d);
  t->AddAnimationFrame("1", 2, d);
  t->AddAnimationFrame("1", 3, d);
  t->AddAnimationFrame("1", 4, d);
  t->AddAnimationFrame("1", 5, d);

  // the animation is looped
  t->SetAnimationType("1", 1);
  t->SetAnimationType("1", ANIMATION_TYPE_LOOP);

  // begin the default animation
  t->StartAnimation("1");
  
  // set any callbacks we may want within the animation
  t->x = x;
  t->y = y;  

  t->w = 32;
  t->h = 32;

  t->type = LOL_BASIC_PARTICLE;
  things.push_back(t);
  return;
}

void ColorToggle(Thing *obj) {
  switch (obj->c) {
  case COLOR_1: 
    obj->c = COLOR_2;
    break;
  case COLOR_2: 
    if (obj->max_colors <= 2) {
      obj->c = COLOR_1;
      break;
    }
    obj->c = COLOR_3;
    break;
  case COLOR_3:
    if (obj->max_colors <= 3) {
      obj->c = COLOR_1;
      break;
    }
    obj->c = COLOR_4;
    break;
  case COLOR_4:
    if (obj->max_colors <= 4) {
      obj->c = COLOR_1;
      break;
    }
    obj->c = COLOR_1;
    break;
  }
}

void PlayerContactEnd(Thing *player, void *object) {
  player->t = T_NONE;
  if (object == NULL) {
    return; 
  }
  if (*(int *)object == RIGHT_WALL) {
    player->t = T_NONE;
    return;
  }
  if (*(int *)object == LEFT_WALL) {
    player->t = T_NONE;
    return;
  }
}

SDL_Texture *background;
SDL_Texture *whale_pic;
SDL_Texture *boat_pic;

// check if we are dropping a box at this location
// should also check the things to drop bits
bool boxCheck(int x, int y)
{
   return false;
}

Thing * place_shit_with_physics(int type, int x, int y, int max_colors)
{
  printf("Want to drop %i %i\n", x, y);
  return nullptr;
}

typedef struct
{
    SDL_AudioDeviceID dev;
    int soundpos;
    volatile int done;
} callback_data;

void load_shit()
{
  pics[TEXTURE_EXPLODE_1] = LoadImage(renderer, "e-0.png");
  pics[TEXTURE_EXPLODE_2] = LoadImage(renderer, "e-1.png");
  pics[TEXTURE_EXPLODE_3] = LoadImage(renderer, "e-2.png");
  pics[TEXTURE_EXPLODE_4] = LoadImage(renderer, "e-3.png");
  pics[TEXTURE_EXPLODE_5] = LoadImage(renderer, "e-4.png");
  return;
}

float push_vel = 40.0f;
void draw_game_background()
{
  SDL_Rect pos;

  pos.x = 0;
  pos.y = 0;
  pos.w = SCREEN_WIDTH;
  pos.h = WINDOW_HEIGHT;
  SDL_SetRenderDrawColor(_window->renderer, 0, 0, 0, 0);
  SDL_RenderFillRect(_window->renderer, &pos);
  
  float s_height = WINDOW_WIDTH / 6;
  
  float r = 70;
  float g = 70;
  float b = 70;

  for (float s_y = 0; s_y < WINDOW_HEIGHT; s_y += s_height) {
    pos.x = 0;
    pos.y = s_y;
    pos.w = WINDOW_WIDTH;
    pos.h = s_height;
    SDL_RenderFillRect(_window->renderer, &pos);
    r -= 5;
    g -= 5;
    b -= 5;
  }
  return;
}


void draw_retry_shit() 
{
  return;
}

unsigned int last_tick = 0;
void draw_shit()
{
  if (SDL_GetTicks() - last_tick < 1000/60)
    return;
  last_tick = SDL_GetTicks();
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  render_game();
  Context::context()->userInterface->Draw(renderer);
  _window->RenderGame();
  SDL_RenderPresent(renderer);
}

void mouse_event(string id, int type)
{
  if (id == "jump-button") {
    if (type == BUTTON_CLICKED) {
    }
    return;
  } 
  
  if (id == "activate-button") {
    if (type == BUTTON_CLICKED) {
    }
  } 
  if (id == "right-button") {
    if (type == BUTTON_SELECTED) {
    } else {
    }
    return;
  }
  if (id == "left-button") {
    if (type == BUTTON_SELECTED) {
     } else {
    } 
  }
  return;
}

void keyboard_shit(int keyCode)
{
  switch (keyCode) {
  case SDLK_SPACE:
    break;
  case SDLK_LEFT: {
    break;
  }
  case SDLK_UP:
    break;
  case SDLK_DOWN:
    break;
  case SDLK_RIGHT:  {
    break;
  }
  default:
    break;
  }
  return;
}

void run_shit() 
{
  SDL_Event e;
  bool quit = false;
  while (!quit) {
    while (SDL_PollEvent(&e)) {
      Context::context()->userInterface->Event(e);
      handle_event(e);
      if (e.type == SDL_QUIT) {
        quit = true;
      }
      if (e.type == SDL_KEYDOWN) {
        keyboard_shit(e.key.keysym.sym);
      }
      if (e.type == SDL_KEYUP) {
        int keycode = e.key.keysym.sym;
        if (keycode == SDLK_UP) {
          j_is_up = true;
        }
        if (keycode == SDLK_RIGHT) {
        
      } 
        if (keycode == SDLK_LEFT) {
        } 
      }
      
      if (e.type == SDL_MOUSEBUTTONUP) {
        SDL_MouseButtonEvent evt = e.button;
        if (evt.button == SDL_BUTTON_LEFT) {
          //AddExplosion(evt.x, evt.y);
          mouse_down = false;
        }
      }
      
      if (e.type == SDL_MOUSEBUTTONDOWN) {
        SDL_MouseButtonEvent evt = e.button;
        if (evt.button == SDL_BUTTON_LEFT) {
          pause = !pause;
          mouse_down = true;
          mouse_x1 = evt.x;
          mouse_y1 = evt.y;
          mouse_x2 = evt.x;
          mouse_y2 = evt.y;
        }
      }
      
      if (e.type == SDL_MOUSEMOTION) {
        SDL_MouseMotionEvent evt = e.motion;
        mouse_x2 = evt.x;
        mouse_y2 = evt.y;
      }
    }
    draw_shit();
  }
  return;
}

void noise_test(void)
{
  unsigned int width  = 2;
  unsigned int height = 2;
  float bias =  219.0f;
  float *result = (float *) malloc( (width * height) * sizeof(float) );
  for (int x = 0; x < width; x++)
    for (int y = 0; y < height; y++) {
      float res = raw_noise_2d(x + bias , y + bias);
    }
  free (result);   
  return;
}


std::string load_file(const char *fname)
{	
	string data;
	ifstream in(fname, ios::in | ios::binary);
	if (!in) {
		printf("can't open file");
		return "";
	}
	in.seekg(0, ios::end);
	data.reserve(in.tellg());
	in.seekg(0, ios::beg);
	data.assign( (istreambuf_iterator<char>(in)),
							 (istreambuf_iterator<char>()) ) ;
	return data;
}

void test_json() 
{
	printf("Testing json\n");
	string data = load_file("test.json");
	printf("%s\n", data.c_str());
	
	const nx_json *json = nx_json_parse((char *)data.c_str(), 0);
	if (!json) {
		printf("could not parse json\n");
		return;
	}	
	
	printf("some-int=%ld\n", nx_json_get(json, "some-int")->int_value);
  printf("KEY=%s\n", nx_json_get(nx_json_get(json, "obj"), "KEY")->text_value);

  const nx_json* arr=nx_json_get(json, "array");
  int i;
  for (i=0; i<arr->length; i++) {
    const nx_json* item=nx_json_item(arr, i);
    printf("arr[%d]=(%d) %ld %lf %s\n", i, (int)item->type, item->int_value, item->dbl_value, item->text_value);
  }
  nx_json_free(json);

	return;
}

int main(int argc, char** argv) {
  UNIT_WIDTH  = 32;
  UNIT_HEIGHT = 32;

	test_json();

  _window = new Window();
  _window->Init();

  Context::context();

  _camera = new Camera();
  _audio  = new Audio();
  _texture = new Texture(_window->renderer);
  renderer = _window->renderer;
  load_shit();
  setup_game();
  run_shit();  
  return 0;
}

