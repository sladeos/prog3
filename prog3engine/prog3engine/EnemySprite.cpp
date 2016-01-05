#include "EnemySprite.h"
#include <SDL.h>
#include <SDL_image.h>
#include "GameEngine.h"
#include <iostream>
GameEngine *engine1;

EnemySprite::EnemySprite(GameEngine * eng, int x, int y, int w, int h, int pathX, int pathY, std::string imgP):ActiveSprite(eng,x,y,w,h,pathX,pathY, imgP)
{
	engine1 = engine;
	texture = IMG_LoadTexture(eng->getRen(), imgPath.c_str());
}


EnemySprite * EnemySprite::getInstance(GameEngine * eng, int x, int y, int w, int h, int pathX, int pathY, std::string imgP)
{
	return new EnemySprite(eng, x, y, w, h, pathX, pathY, imgP);
}

void EnemySprite::actionCollision()
{

}

void EnemySprite::tickAction()
{
	if (y >= 650) {
		std::cout << "REACH";
		Level *love = Level::getInstance(engine, "C:/images/background1.png");
		engine->loadLevel(love);
	}

	if (x >= engine->getW()-30) {
		xPath = -15;
		y += 50;

	}
	else if (x <= 30) {
		xPath = 15;
		y += 50;
	}
}


EnemySprite::~EnemySprite()
{
	delete rectSpriteArray;
	SDL_DestroyTexture(texture);
}
