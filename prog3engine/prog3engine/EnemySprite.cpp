#include "EnemySprite.h"
#include <SDL.h>
#include <SDL_image.h>
#include "GameEngine.h"
#include <iostream>
#include "LaserSprite.h"
#include "PlayerSprite.h"

namespace gengine {
	
	int EnemySprite::groupY, EnemySprite::groupXpath;

	//Constructor
	EnemySprite::EnemySprite(GameEngine * eng, int x, int y, int w, int h, int pathX, int pathY, std::string imgP) :ActiveSprite(eng, x, y, w, h, pathX, pathY, imgP)
	{
		texture = IMG_LoadTexture(eng->getRen(), imgPath.c_str());
		groupY = y;
		groupXpath = pathX;
	}


	EnemySprite * EnemySprite::getInstance(GameEngine * eng, int x, int y, int w, int h, int pathX, int pathY, std::string imgP)
	{
		return new EnemySprite(eng, x, y, w, h, pathX, pathY, imgP);
	}

	//If collision is triggered, this function will be run
	void EnemySprite::actionCollision(Sprite *s)
	{
		//If collided with a LaserSprite, this sprite will be set for removal
		if (LaserSprite* enemy = dynamic_cast<LaserSprite*>(s)) {
			engine->addRemoveSprite(this);
		}
		//If collided with the player, trigger the actionFunction which in this case is gameover
		else if (PlayerSprite* enemy = dynamic_cast<PlayerSprite*>(s)) {
			actionFunction();
		}
	}

	//setter for actionfunction
	void EnemySprite::setActionFunction(std::function<void(void)> actionFunc)
	{
		actionFunction = actionFunc;
	}

	//What will happen on each tick
	void EnemySprite::tickAction()
	{
		
		//If this sprite is not aligned with group on Y dimension, then align it.
		if (y != groupY) {
			y = groupY;
		}
		//If this sprite is not aligned with group on the X path movement, then align it.
		if (xPath != groupXpath) {
			xPath = groupXpath;
		}

		//If the sprite is moving to the right and has touched the side of the window, then change the direction of the group and move the group downwards
		if (xPath > 0 && x >= engine->getW() - 60) {
			groupXpath = -1;
			groupY += 50;
		//If the sprite is moving to the left and has touched the side of the window, then change the direction of the group and move the group downwards,
		//and this sprite aswell (Because it will be the first in the loop and needs manual adjustment, or it will be left behind)
		} else if (xPath < 0 && x <= 20) {
			
			groupXpath = 1;
			xPath = groupXpath;
			groupY += 50;
			y = groupY;
		}

	}


	EnemySprite::~EnemySprite()
	{
	}
}