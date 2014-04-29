#include <iostream>
#include "defines.h"
#include "Window.h"

int SCREEN_WIDTH  = 500;
int SCREEN_HEIGHT = 500;

int WINDOW_HEIGHT = 500;
int WINDOW_WIDTH =  500;

void Window::Init() 
{
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
    std::cout << SDL_GetError() << std::endl;
	exit(0);
    return;
  }

 SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
  #ifdef ANDROID
   SDL_CreateWindowAndRenderer(0, 0, 0, &window, &renderer);
  if (window == nullptr){
    std::cout << SDL_GetError() << std::endl;
    return;
  }
  SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
  if (renderer == nullptr){
    std::cout << SDL_GetError() << std::endl;
    return;
  }	
  WINDOW_WIDTH = SCREEN_WIDTH;
  WINDOW_HEIGHT = SCREEN_HEIGHT;
  #else
  window = SDL_CreateWindow("LD29", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT,SDL_WINDOW_OPENGL);
  if (window == nullptr){
    std::cout << SDL_GetError() << std::endl;
  	exit(0);
	  return;
  }
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  #endif

  gameTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
  if (renderer == nullptr){
    std::cout << SDL_GetError() << std::endl;
	exit(0);  
  return;
  }
}

void Window::BeginTextureRender()
{
	SDL_SetRenderTarget(renderer, gameTexture);
}

void Window::EndTextureRender()
{
	SDL_SetRenderTarget(renderer, NULL);
}

void Window::RenderGame()
{
	SDL_Rect src;
	SDL_Rect dst;

	src.x = 0;
	src.y = 0;
	src.w = SCREEN_WIDTH;
	src.h = SCREEN_HEIGHT;
        
  dst.x = 0;
  dst.y = 20;
  dst.w = WINDOW_WIDTH;
  dst.h = WINDOW_HEIGHT;
	SDL_RenderCopy(renderer, gameTexture, &src, &dst);
}

void Window::Draw(SDL_Texture*, ...) 
{

}

void Window::Clear() 
{

}

void Window::Present() 
{

}

Window::Window() 
{
  return;
}

Window::~Window() 
{  
  return;
}
