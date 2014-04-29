// there is no sane reason so much of this is in memory
#ifndef AVECTOR_2D
#define AVECTOR_2D
#include <math.h>

#define DEG2RAD(a) ((a) * M_PI / 180.0)
#define RAD2DEG(a) ((a) * 180.0 / M_PI)
#define DMS2DD(d,m,s) ((d) + ((m) / 60.0) + ((s) / 3600.0))

using namespace std;

enum VECTOR2D_MODE {
  VECTOR2D_MODE_NONE,
  VECTOR2D_MODE_LINEAR,
  VECTOR2D_MODE_CUBIC,
};

class AVector2D {
  int mode;
  float interp_1d(float v1, float v2, float t);
  void interp_2d(float x1, float y1, float x2, float y2, float t);
 public:
  float x;
  float y;
  float z;  
  AVector2D(float _x, float _y) {
    x = _x;
    y = _y;
    mode = VECTOR2D_MODE_NONE;
    return;
  }

  static AVector2D* CirclePoint(int segment, int sides) 
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

	float Length() {
		return sqrt( (this->x * this->x) + (this->y * this->y));
	}
	AVector2D * Normal() {
		float len = this->Length();
		return new AVector2D(this->x/len, this->y/len);
	}
	AVector2D * Cross(AVector2D *b) {
		return nullptr;
	}
  AVector2D * Sub(AVector2D *b) {
   return new AVector2D(this->x - b->x, this->y - b->y);
  };
};

#endif
