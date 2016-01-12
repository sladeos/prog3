#include "PlayerSprite.h"
#include <SDL.h>
#include <SDL_image.h>
#include "GameEngine.h"
#include <iostream>

namespace gengine {

	//Consturctor
	PlayerSprite::PlayerSprite(GameEngine * eng, int x, int y, int w, int h, int pathX, int pathY, std::string imgP) :ActiveSprite(eng, x, y, w, h, pathX, pathY, imgP)
	{
		texture = IMG_LoadTexture(eng->getRen(), imgPath.c_str());

	}

	PlayerSprite * PlayerSprite::getInstance(GameEngine * eng, int x, int y, int w, int h, int pathX, int pathY, std::string imgP)
	{
		return new PlayerSprite(eng, x, y, w, h, pathX, pathY, imgP);
	}

	//Do this on collision (nothing)
	void PlayerSprite::actionCollision(Sprite *s)
	{

	}
	//On tick do this
	void PlayerSprite::tickAction()
	{
		//If this player is below x, then reset it to x (To make sure player cant move outside the screen)
		if (x < 0) {
			x = 0;
		//Same logic but for the right side, get width of window and check if player is outside it, and if he is, 
		//reset him to the width of the window - 100 because of this size of the player
		} else if (x > engine->getW() - 100) {
			x = engine->getW() - 100;
		}

	}
	PlayerSprite::~PlayerSprite()
	{
		SDL_DestroyTexture(texture);
	}
}