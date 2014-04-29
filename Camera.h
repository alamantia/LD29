#ifndef CAMERA_H
#define CAMERA_H
/*
  we really need some decent camera effects to make this game not crap
  panning.
  
  stalling.
  
  shaking.

  the usual
*/

enum CSTATES {
  CAMERA_NORMAL,
  CAMERA_SHAKE,
};

class Camera {
 public:
  int tick_start;
  float duration;
  int shake_end;
  int state; 
  int x;
  int y;
  int o_x;
  int o_y;
  int PositionX(int x);
  int PositionY(int y);
  void Tick();
  void Shake(float duration);  
  void ShakeIfNot(float duration);  
  void DoShake();
  
  Camera();

  
};

#endif
