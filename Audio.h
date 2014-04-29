#ifndef AUDIO_H
#define AUDIO_H

#include "defines.h"

#include <string>
#include <list>

using namespace std;

class AudioSample {
 public:
  unsigned int id;
  unsigned int channel;
  Mix_Chunk*   phaser;
};

class Audio {
 public:
  Mix_Music *music;
  
  std::list <AudioSample *> samples;
  
  void PlaySound(unsigned int id);
  void LoadSound(std::string fname, unsigned int id);
  void PlayMusic(std::string fname);
 
  Audio();
  ~Audio();
};

#endif
