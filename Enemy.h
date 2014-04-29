#ifndef ENEMY1_H
#define ENEMY1_H

#include "defines.h"

class Enemy : public Thing {
  public:
    float speed;
    int time_fire;
    bool TakeDamage(int amount);
    void Tick();
    void Draw(SDL_Renderer *renderer);
    Enemy();
    ~Enemy();
};

#endif
