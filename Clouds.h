#include "defines.h"
#include <vector>
#include <list>

#include "AVector2D.h"
using namespace std;
enum CLOUDS {
  CLOUD_1,
  CLOUD_2,
  CLOUD_3,
  CLOUD_4,
  CLOUD_5,
};
class Cloud {
public:
  AVector2D *pos;
  int   index;
  int   type;
  float speed;
  int w;
  int h;
  Cloud() {
    type = CLOUD_1;
    pos = new AVector2D(0.0,0.0);
  }
};

class Clouds {
  public:
    list <Cloud *> clouds;
    void Render(SDL_Renderer *renderer);
    Clouds();
    ~Clouds();
};

