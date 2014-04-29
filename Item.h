#ifndef ITEM_H
#define ITEM_H
#include "Thing.h"
#include "defines.h"

class Item : public Thing {
  public:
    void Tick();
    void Draw(SDL_Renderer *renderer);
    Item();
    ~Item();
};

#endif

