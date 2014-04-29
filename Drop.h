#ifndef DROP_H
#define DROP_H

enum DROP_MODES {
  DROP_MODE_NORMAL      = 0,
  DROP_MODE_WAVE_RIGHT  = 1,
  DROP_MODE_WAVE_LEFT   = 2,
  DROP_MODE_TRI         = 3,
  DROP_MODE_MULTI       = 4,
  DROP_MODE_BLINK       = 5,
  DROP_MODE_SINGLE_FILL = 6,
  DROP_MODE_DOUBLE      = 7,
};

typedef struct _drop_script {
  int drop_type;     
  int drop_length;  
  int drop_tick;     
  int release_time;  
} drop_script;

drop_script random_drop_script();
drop_script get_drop_script();
void reset_drop();

void drop_machine();

#endif
