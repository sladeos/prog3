#include "System.h"
#include <SDL.h>
#include <stdexcept>
#include <string>
#include <SDL_ttf.h>

namespace gengine {

	System sys;
	
	System::System()
	{
		//initialize SDL
		if (TTF_Init() == -1) {
			throw std::runtime_error(std::string("Fel: ") + TTF_GetError());
		} else if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
			throw std::runtime_error(std::string("Fel: ") + SDL_GetError());
	}

	//Destructor
	System::~System()
	{
		SDL_Quit();
		TTF_Quit();
	}

}