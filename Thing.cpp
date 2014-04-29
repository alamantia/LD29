#include "defines.h"

float interp_1d(float v1, float v2, float t)
{
  return v1 + (v2-v1) * t;
}

void interp_2d(float x1, float y1, float x2, float y2, float t)
{
  return;
}

void Thing::draw()
{
  return;
}

bool Thing::contains_rect(int rx, int ry, int rw, int rh)
{
	bool xBlocked = false;
	bool yBlocked = false;
	AVector2D *va = new AVector2D(this->x, this->y);
	AVector2D *vb = new AVector2D(rx, ry);
	AVector2D *vr = va->Sub(vb);	
	//printf("result %f %f\n", vr->x, vr->y);

	if (vr->x <= rw && vr->x >= 0)
		xBlocked = true;
	if (vr->x >= -rw && vr->x <= 0) 
		xBlocked = true;

	if (vr->y <= rh && vr->y >= 0)
		yBlocked = true;
	if (vr->y >= -rh && vr->y <= 0) 
		yBlocked = true;



	delete va;
	delete vb;
  delete vr;
	if (xBlocked) {
		//return true;
	}
	if (xBlocked && yBlocked)
		return true;	
	return false;
}

bool Thing::contains_thing(Thing *b)
{
	return false;
}

bool Thing::contains_point_box(float bx, float by)
{
  float _x;
  float _y;
	float dp_x =  bx - x;
  float dp_y =  by - y;
	if (dp_x <= w && dp_x >= 0) {
	 if (dp_y <= h && dp_y >= 0) {
		return true;
	 }
  }

  return false;
}

bool Thing::contains_point(float bx, float by)
{
  float dp_x =  bx - x;
  float dp_y =  by - y;
  if (dp_x <= w && dp_x >= 0) {
	 if (dp_y <= h && dp_y >= 0) {
		return true;
	 }
  }
  return false;
}

void Thing::AddTexture(SDL_Renderer *renderer, string path)
{
  SDL_Texture *tex =  LoadImage(renderer, path);
  textures.push_back(tex);
  return;
}

struct animation * Thing::GetAnimation(string name)
{
  for (auto it = animations.begin(); it != animations.end(); ++it) {
    struct animation *animation = *it;
	printf("Trying to find %s have %s\n", name.c_str(), animation->name.c_str());
    if (animation->name == name) {
      return animation;
    }
  }
  return nullptr;
}

void Thing::AddAnimationFrame(string name, int texture_index, int duration)
{
  struct animation *animation = GetAnimation(name);

  if (animation == nullptr) {
	animation = new struct animation();
	animation->name = name;
	animation->current_frame = 0;
	animation->last_tick      = SDL_GetTicks();
	animation->last_tick      = SDL_GetTicks();
	animations.push_back(animation);
  }

  struct animation_frame *frame  = new struct animation_frame();
  frame->texture = texture_index;
  frame->duration = duration;
  animation->frames.push_back(frame);
  return;
}

void Thing::SetAnimationType(string name, int type) 
{
  struct animation *animation = GetAnimation(name);
  return;
}

// add the texture to the object (make sure that references are managed correctly)
void Thing::AddTexture(SDL_Texture *tex)
{
  textures.push_back(tex);
  return;
}

SDL_Texture * Thing::GetActiveTexture()
{
  SDL_Texture *x = nullptr;
  if (current_animation == nullptr) {
	  return nullptr;
  }
  if (current_animation == nullptr || current_animation->running == false) {
    return nullptr;
  }
  auto tI = current_animation->frames.begin();
  std::advance (tI, current_animation->current_frame);
  struct animation_frame *frame = *tI;
  auto iter = textures.begin();
  std::advance(iter, frame->texture);
  x = *iter;
  return x;
} 

void Thing::StartAnimation(string name) 
{
  struct animation *animation = GetAnimation(name);
  
  if (animation == nullptr) {
	  printf(" 1 Could not find animation\n");
	  exit(0);
	}
 
  current_animation                 = animation;
  current_animation->running        = true;
  current_animation->last_tick      = SDL_GetTicks();
  current_animation->current_frame  = 0;
  current_animation->total_frames   = current_animation->frames.size();
  return;
}

void Thing::StopAnimation()
{ 
  current_animation->running = false;
  current_animation = nullptr;
  return;
} 

unsigned int Thing::TweenTime(int dist, int speed)
{
  return 0;
}
// update the animation system and locate the SDL_Texture we need
// mostly used to get the animation system moving

// need to move to the interpolation system as well
// the best method would be just to pass a function pointer or something to call when things are finished up. 
void Thing::Tick()
{  
  if (tween_state == TWEEN_LINEAR) {  
      // basic interpolation
      unsigned int c = SDL_GetTicks();
      unsigned int d = tween_finish - tween_start;
      unsigned int dt = c - tween_start;
      float p = (float)dt/(float)d;
       x = interp_1d(tween_src->x, tween_dst->x, p);
       y = interp_1d(tween_src->y, tween_dst->y, p);
      if (p >= 1.0) {
        if (event_callback != nullptr) {
          event_callback(this, TWEEN_LINEAR, "tween");
        }
        tween_state = TWEEN_NONE;
        x = tween_dst->x;
        y = tween_dst->y;
      }
  }
  if (current_animation != nullptr) { 
    auto iter = current_animation->frames.begin();
    std::advance (iter, current_animation->current_frame);
    struct animation_frame *frame = *iter;
    int delta = SDL_GetTicks() - current_animation->last_tick;
    if (delta > frame->duration) {
      current_animation->current_frame++;
      if ( current_animation->current_frame >=  current_animation->frames.size() -1 ) {
        current_animation->current_frame = 0;
	      // animation did finish .. do something (or loop?)
        // what texture do we fall back on to?
	      current_animation->running = false;
      } 
      current_animation->last_tick = SDL_GetTicks();
    }
  }
  return;  
}

// s = 5 c = 10  f = 15
//
// 
// return v1 + (v2-v1) * t; 
// how far a long with the process are we as a percentage?
//  
//  p = c / (s + f)   
//  var d = (f - s)  = 10
//  var dt = (c - s) = 5 
//  var p  = (dt / d) = 5 / 10 = 0.5

void Thing::MoveTo(int dst_x, int dst_y,int duration_millis)
{
  if (tween_dst != nullptr) {
    delete tween_dst;
  }
  tween_state = TWEEN_LINEAR; 
  tween_dst = new AVector2D(dst_x, dst_y);
  tween_src = new AVector2D(this->x, this->y);
  tween_start = SDL_GetTicks();
  tween_finish = SDL_GetTicks() + duration_millis;
  return;
}

/* some drawing routines .. mostly used for the animation - particle system - move somewhere else   */
/* draw the texture and animate it directly                                                         */
void Thing::Draw(SDL_Renderer *renderer)
{
  if (type == LOL_BASIC_PARTICLE) {
    Tick();
    return;
  }
  if (type == LOL_PHYSICS_PARTICLE) {
    Tick();
    return;
  }
  return;
}

bool Thing::TakeDamage(int amount)
{
  return true;
}

Thing::Thing()   
{ 
  tween_state = TWEEN_NONE;
  tween_dst = nullptr; 
	subtype = 0; 
  g_x 		= -1;
  g_y 		= -1;
  type  	= LOL_NONE; 
  active 	= true;
  time_value = 0;
  dead 		= false; 
  current_animation = nullptr; 
  pos = new AVector2D(0,0);
  dir = new AVector2D(0,0);
  force = new AVector2D(0,0);
  effector = new AVector2D(0,0);
};





