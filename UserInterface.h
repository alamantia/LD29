#ifndef INTERFACE_H
#define INTERFACE_H

#include "defines.h"
#include "Button.h"

#include <list>
#include <vector>

using namespace std;


class UserInterface
{
public:
	list<Button *> buttons;
	void Draw(SDL_Renderer *renderer);
	void Event(SDL_Event e);
	void AddButton(string _id, float x, float y, float w, float h, string img);
	void DrawButtons(SDL_Renderer *renderer);
	UserInterface(void);
	~UserInterface(void);
};

#endif
