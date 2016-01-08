#include "PlayerSprite.h"
#include <SDL.h>
#include <SDL_image.h>
#include "GameEngine.h"
#include <iostream>

namespace gengine {

	PlayerSprite::PlayerSprite(GameEngine * eng, int x, int y, int w, int h, int pathX, int pathY, std::string imgP) :ActiveSprite(eng, x, y, w, h, pathX, pathY, imgP)
	{
		texture = IMG_LoadTexture(eng->getRen(), imgPath.c_str());

	}

	PlayerSprite * PlayerSprite::getInstance(GameEngine * eng, int x, int y, int w, int h, int pathX, int pathY, std::string imgP)
	{
		return new PlayerSprite(eng, x, y, w, h, pathX, pathY, imgP);
	}

	void PlayerSprite::actionCollision()
	{

	}

	void PlayerSprite::tickAction()
	{
		if (x < 0) {
			x = 0;
		}
		else if (x>engine->getW()) {
			x = engine->getW();
		}

	}
	PlayerSprite::~PlayerSprite()
	{
	}
}