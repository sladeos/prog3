#include "EnemySprite.h"
#include <SDL.h>
#include <SDL_image.h>
#include "GameEngine.h"
#include <iostream>
GameEngine *engine1;
int EnemySprite::groupY, EnemySprite::groupXpath;
EnemySprite::EnemySprite(GameEngine * eng, int x, int y, int w, int h, int pathX, int pathY, std::string imgP):ActiveSprite(eng,x,y,w,h,pathX,pathY, imgP)
{
	engine1 = engine;
	texture = IMG_LoadTexture(eng->getRen(), imgPath.c_str());
	groupY = y;
	groupXpath = pathX;
}


EnemySprite * EnemySprite::getInstance(GameEngine * eng, int x, int y, int w, int h, int pathX, int pathY, std::string imgP)
{
	return new EnemySprite(eng, x, y, w, h, pathX, pathY, imgP);
}

void EnemySprite::actionCollision()
{
	engine->addRemoveSprite(this);
}

void EnemySprite::tickAction()
{
	if (y >= 650) {
		std::cout << "REACH";
		Level *love = Level::getInstance(engine, "C:/images/background1.png");
		engine->loadLevel(love);
	}
	if (y != groupY) {
		y = groupY;
	}

	if (xPath != groupXpath) {
		xPath = groupXpath;
	}
	
	if (xPath > 0 && x >= engine->getW()-60) {
		groupXpath = -5;
		groupY += 50;
		
	}
	else if (xPath < 0 && x <= 20 ) {
		groupXpath = 5;
		xPath = groupXpath;
		groupY += 50;
		y = groupY;
	}
	
}


EnemySprite::~EnemySprite()
{
	
	delete rectSpriteArray;
	SDL_DestroyTexture(texture);
}
