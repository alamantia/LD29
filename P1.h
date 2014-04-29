/* this will define the interface for most particle - interactions */
#ifndef P1_H
#define P1_h
#include "defines.h"
#include <list>
using namespace std;
class P1 {
  list<Thing *> parts; 
  public:
    int r;
    int g;
    int b;
    int segs;
    int x;
    int deg;
    int y;
    int phase;
    unsigned int last;
    bool Render(SDL_Renderer *renderer);
    void Tick();
    void Spawn();
    P1(int _x, int _y);
    P1(int _x, int _y, int _segs, int _r, int _g, int _b, int _deg);
    ~P1();
    list<Thing *> plist;
    AVector2D* CirclePosition(int segment, int sides); 
    // void b_callback(Thing *t, int type, string message)
    // void (*event_callback)(int);
    void (*event_callback)(void *,int,string);
};

#endif


