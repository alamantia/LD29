#ifndef GAME_H
#define GAME_H

#include "defines.h"

// stuff to put into a future game class
void render_game();
void setup_game();
void handle_event(SDL_Event e);

// end
Thing* passable(int x, int y, int w, int h);
void update_subtype(Thing *t);
void add_brick(int x, int y);
bool can_render(int x, int y);
Thing * get_player();
void fire_enemy_bullet(int x, int y, int type, AVector2D *direction);
void gen_world();
Thing* passable(void *skip, int x, int y, int w, int h);

#endif

