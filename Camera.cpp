#include "Camera.h"
#include "defines.h"
#include "simplexnoise.h"

Camera::Camera()
{
  x = 0;
  y = 0;
  state = CAMERA_NORMAL;
}

void Camera::DoShake() {
  /*
  float scaled_raw_noise_2d( const float loBound,
                        const float hiBound,
                        const float x,
                        const float y);
  */
  float range = 4;
  x  =  o_x + scaled_raw_noise_2d(-range, range,  rand(), rand() % 120);
  y  =  o_y + scaled_raw_noise_2d(-range, range,  rand() % 120, 120);  
}

void Camera::Reset() {
	state = CAMERA_NORMAL;
	x = 0;
	y = 0;	
}
void Camera::ShakeIfNot(float duration) {
  return;
}

void Camera::Shake(float duration) {
  if (state == CAMERA_SHAKE)
    return;
  state = CAMERA_SHAKE;
  shake_end = SDL_GetTicks() + (duration * 40);
  o_x = x;
  o_y = y;
  return;
}

void Camera::Tick() {
  if (state == CAMERA_SHAKE) {
    int diff = (shake_end - SDL_GetTicks());
    if (diff <= 0) {
      printf("Stop shake\n");
      x = o_x;
      y = o_y;
      state = CAMERA_NORMAL;
      return;
    }
    DoShake();
    printf("Camera %i\n", diff);
  }
  return;
}

int Camera::PositionX(int _x) {
  return _x - x;
}

int Camera::PositionY(int _y) {
  return _y - y;
}

