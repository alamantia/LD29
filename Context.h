#ifndef CONTEXT_H
#define CONTEXT_H

#include "defines.h"
#include "UserInterface.h"
#include "Game.h"
class Context
{
private:
	static Context* _context;
public:
	static Context *context();
	UserInterface *userInterface;
	Game	*Game;
  int total_health;
  int current_health;
	Context(void);
	~Context(void);
};

#endif
