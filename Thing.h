#ifndef THING_H
#define THING_H

#include "defines.h"

#include <Box2D/Box2D.h>
#include <string>
#include <list>


using namespace std;

enum TWEEN_TYPES {
  TWEEN_NONE   = 0,
  TWEEN_LINEAR = 1,
  TWEEN_CURVE_1 = 2,
};

enum ANIMATION_TYPES {
  ANIMATION_TYPE_STD,
  ANIMATION_TYPE_LOOP,
};

struct animation_frame {
  int texture;
  int duration;
};

enum FACING_DIRECTION {
  FACING_LEFT,
  FACING_RIGHT,
};

// manage the animations we need to
struct animation {
  string name;
  bool running;
  int last_tick; // rename this to something more useful
  int total_frames;
  int current_frame;
  int animation_type;
  list<struct animation_frame *>frames;
};

// should be abstracted into an animation manager of some sort

class Thing {
 public: 
  int direction;

  // start moving this to the AVector2D system
  AVector2D *pos;
  AVector2D *dir;
  AVector2D *force;
  AVector2D *effector; 

  // simple tween / curve logic
  // really need to abstract this out somewhere else! srsly
  int tween_state;
  unsigned int tween_finish;
  unsigned int tween_start;
  float tween_value;
  AVector2D *tween_dst;
  AVector2D *tween_src;

  int health;
  int damage;

	int r;
	int g;
	int b;
	int a;


  bool j;
	int subtype;
  int  t;
  int  d;
  float  x;
  float  y;
  
  int g_x;
  int g_y; 
  int  w;
  int  h;

  int  c;

  int  t_r;
  int  t_l;
  int  t_u;
  int  t_d;

  int c_d;
  int r_t;

  int d_x;
  int d_y;
	
	int 	 time_value;
  int 	 max_colors;
  bool   active;
  int    draggable;
  int    landed;
  int    type;
  int     source; 
  bool    dead;
  b2Body *body;
  
  struct animation *current_animation;

  list <SDL_Texture *> textures;
  list <struct animation *> animations;
  
  Thing();
  ~Thing()  {};
  virtual bool TakeDamage(int amount);
  unsigned int TweenTime(int dist, int speed); 
  void MoveTo(int dst_x, int dst_y, int duration_millis); 
  virtual void Draw(SDL_Renderer *renderer);
  void AddTexture(SDL_Renderer *renderer, string path);
  void AddTexture(SDL_Texture *tex);

  // Animation management features
  
  struct animation * GetAnimation(string name);
  void AddAnimationFrame(string name, int texture_index, int duration);
  void SetAnimationType(string name, int type);
  void StartAnimation(string name);
  void StopAnimation();

  void Tick();
  void MoveTo(int x, int y);
  
  Thing * getBox(int x, int y);
  SDL_Texture * GetActiveTexture();

  void draw();
  bool contains_point_box(float bx, float by);
  bool contains_point(float bx, float by);
	bool contains_thing(Thing *b);
	bool contains_rect(int rx, int ry, int rw, int rh);
  void (*event_callback)(void *,int,string);
};

#endif
