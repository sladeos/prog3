#include "LaserSprite.h"
#include <SDL.h>
#include <SDL_image.h>
#include "GameEngine.h"
#include <iostream>

namespace gengine {
	LaserSprite::LaserSprite(GameEngine * eng, int x, int y, int w, int h, int pathX, int pathY, std::string imgP) :ActiveSprite(eng, x, y, w, h, pathX, pathY, imgP)
	{
		texture = IMG_LoadTexture(eng->getRen(), imgPath.c_str());

	}

	LaserSprite * LaserSprite::getInstance(GameEngine * eng, int x, int y, int w, int h, int pathX, int pathY, std::string imgP)
	{
		return new LaserSprite(eng, x, y, w, h, pathX, pathY, imgP);
	}

	void LaserSprite::actionCollision()
	{
		engine->addRemoveSprite(this);
	}

	void LaserSprite::tickAction()
	{
		if (y < 0) {
			engine->addRemoveSprite(this);
		}

	}


	LaserSprite::~LaserSprite()
	{
	}
}