#include "LaserSprite.h"
#include <SDL.h>
#include <SDL_image.h>
#include "GameEngine.h"
#include <iostream>

namespace gengine {
	int LaserSprite::instances = 0;
	//Constructor
	LaserSprite::LaserSprite(GameEngine * eng, int x, int y, int w, int h, int pathX, int pathY, std::string imgP) : ActiveSprite(eng, x, y, w, h, pathX, pathY, imgP)
	{
		texture = IMG_LoadTexture(eng->getRen(), imgPath.c_str());

	}

	LaserSprite * LaserSprite::getInstance(GameEngine * eng, int x, int y, int w, int h, int pathX, int pathY, std::string imgP)
	{
		//If there is no instances of laser
		if(instances == 0){
			//Then increment the static variable and return a LaserSprite object
			++instances;
		return new LaserSprite(eng, x, y, w, h, pathX, pathY, imgP);
		//If there is, then return a nullptr
		} else{
			return nullptr;
		}
	}
	
	//On collision set this object for removal 
	void LaserSprite::actionCollision(Sprite *s)
	{
		engine->addRemoveSprite(this);
	}

	//On tick 
	void LaserSprite::tickAction()
	{
		//Check if object is outside the screen on the Y dimension
		if (y < 0) {
			//If yes, then set for removal
			engine->addRemoveSprite(this);
		}

	}

	//Destructor
	LaserSprite::~LaserSprite()
	{
		SDL_DestroyTexture(texture);
		//Decrement the static variable to allow for new lasersprites to be created
		--instances;
	}
}