#include "Context.h"

Context* Context::_context = NULL; 

Context *Context::context() 
{
	if (_context == NULL) {
		_context = new Context();
		_context->userInterface = new UserInterface();
    _context->total_health = 4;
    _context->current_health = 4;
	}
	return _context;
}

Context::Context(void)
{

}

Context::~Context(void)
{

}


