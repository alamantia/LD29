#include "Audio.h"

void Audio::PlayMusic(std::string fname)
{
  return;
}

void Audio::PlaySound(unsigned int id)
{
  AudioSample *sample = NULL;
  for (auto i = samples.begin(); i != samples.end(); ++i) {
    AudioSample *t = *i;
    if (t->id == id) {
      sample = t;
      break;
    }
  }
  if (sample == NULL)
    return;
  if (sample->channel > -1) {
    
  }
  Mix_PlayChannel(-1, sample->phaser, 0);
  printf("Playing\n");
  return;
}

void Audio::LoadSound(std::string fname, unsigned int id)
{
  AudioSample *sample = new AudioSample();
  sample->id = id;
  sample->channel = -1;
  sample->phaser = Mix_LoadWAV(fname.c_str());
  samples.push_back(sample);
  return;
}

Audio::Audio() 
{
  printf("Starting audio\n");
  int audio_rate;
  int audio_channels = 2;
  int audio_buffers = 4096;
  unsigned short audio_format = AUDIO_S16;
  
  audio_rate = MIX_DEFAULT_FREQUENCY;
  audio_format = MIX_DEFAULT_FORMAT;
  audio_channels = 2;
  
  if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, 16) < 0) {
    printf("Unable to open audio! %s\n", SDL_GetError());
  }
  return;
}

Audio::~Audio() 
{
  Mix_CloseAudio();
  return;
}


