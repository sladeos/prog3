#include "ActiveSprite.h"
#include "GameEngine.h"
#include "SDL_image.h"
#include <string>
#include <SDL.h>
#include<iostream>
namespace gengine {

	ActiveSprite* ActiveSprite::getInstance(GameEngine * eng, int x, int y, int w, int h, int pathX, int pathY, std::string imgP)
	{
		return new ActiveSprite(eng, x, y, w, h, pathX, pathY, imgP);
	}

	void ActiveSprite::setXpath(int newX)
	{
		xPath = newX;
	}

	void ActiveSprite::setYpath(int newY)
	{
		yPath = newY;
	}



	void ActiveSprite::initSpriteSheet(int elementCount)
	{
		rectSpriteArray = new SDL_Rect[elementCount];
		spriteSheet = true;
	}

	void ActiveSprite::addSpriteClip(int element, int x, int y, int w, int h)
	{
		rectSpriteArray[element].x = x;
		rectSpriteArray[element].y = y;
		rectSpriteArray[element].w = w;
		rectSpriteArray[element].h = h;
	}

	void ActiveSprite::actionCollision()
	{
	}

	ActiveSprite::ActiveSprite(GameEngine * eng, int x, int y, int w, int h, int pathX, int pathY, std::string imgP) : Sprite(eng, x, y, w, h, imgP), x(x), y(y), w(w), h(h), xPath(pathX), yPath(pathY)
	{
		texture = IMG_LoadTexture(engine->getRen(), imgPath.c_str());
	}


	void ActiveSprite::draw()
	{
		if (spriteSheet) {
			if (frame == 4) {
				frame = 0;
			}
			SDL_Rect* currentClip = &rectSpriteArray[frame];
			frame++;

			SDL_RenderCopy(engine->getRen(), texture, currentClip, &rect);
		}
		else {
			SDL_RenderCopy(engine->getRen(), texture, NULL, &rect);
		}
	}

	void ActiveSprite::tick(std::vector<Sprite*> sprites) {
		for (Sprite* s : sprites) {
			if (s != this) {
				if (checkCollision(&s->rect)) {
					actionCollision();
				}
			}
		}
		x += xPath;
		y += yPath;
		rect = { getX(), getY(), getW(), getH() };
	}

	const int ActiveSprite::getX()
	{
		return x;
	}

	const int ActiveSprite::getY()
	{
		return y;
	}

	void ActiveSprite::setX(int newX)
	{
		x = newX;
	}

	void ActiveSprite::setY(int newY)
	{
		y = newY;
	}

	const int ActiveSprite::getW()
	{
		return w;
	}

	const int ActiveSprite::getH()
	{
		return h;
	}

	ActiveSprite::~ActiveSprite()
	{
		
		delete rectSpriteArray;
		SDL_DestroyTexture(texture);
	}

}
