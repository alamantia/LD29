#include "defines.h"
void move_stop();
void move_right();
void move_left();
void move_jump();
void move_activate();
void place_brick(int x, int y);
void add_p1(int x, int y); 
void setup_game();
void render_game();
void tick_game();
void place_box_tile(int x, int y);
void place_box_tile(int x, int y, int max_colors);
void handle_event(SDL_Event e);

