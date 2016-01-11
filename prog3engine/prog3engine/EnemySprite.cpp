#include "EnemySprite.h"
#include <SDL.h>
#include <SDL_image.h>
#include "GameEngine.h"
#include <iostream>
#include "LaserSprite.h"
#include "PlayerSprite.h"

namespace gengine {

	int EnemySprite::groupY, EnemySprite::groupXpath;

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

	void EnemySprite::actionCollision(Sprite *s)
	{
		if (LaserSprite* enemy = dynamic_cast<LaserSprite*>(s)) {
			engine->addRemoveSprite(this);
		}
		else if (PlayerSprite* enemy = dynamic_cast<PlayerSprite*>(s)) {
			actionFunction();
		}
	}

	void EnemySprite::setActionFunction(std::function<void(void)> actionFunc)
	{
		actionFunction = actionFunc;
	}

	void EnemySprite::tickAction()
	{
		if (y >= 650) {
			Level *love = Level::getInstance(engine, "C:/images/background1.png");
			engine->loadLevel(love);
		}
		if (y != groupY) {
			y = groupY;
		}

		if (xPath != groupXpath) {
			xPath = groupXpath;
		}

		if (xPath > 0 && x >= engine->getW() - 60) {
			groupXpath = -1;
			groupY += 50;

		}
		else if (xPath < 0 && x <= 20) {
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