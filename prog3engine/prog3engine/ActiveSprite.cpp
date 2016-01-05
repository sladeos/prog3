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

	//Set path in X dimension for sprite to move in 
	void ActiveSprite::setXpath(int newX)
	{
		xPath = newX;
	}

	//Set path in Y dimension for sprite to move in 
	void ActiveSprite::setYpath(int newY)
	{
		yPath = newY;
	}

	//Initialize sprite sheet for sprites
	void ActiveSprite::initSpriteSheet(int elementCount)
	{
		spriteSheetCount = elementCount;
		rectSpriteArray = new SDL_Rect[elementCount];
		spriteSheet = true;
	}

	//Add sprite clip to use on sprite sheet
	void ActiveSprite::addSpriteClip(int element, int x, int y, int w, int h)
	{
		rectSpriteArray[element].x = x;
		rectSpriteArray[element].y = y;
		rectSpriteArray[element].w = w;
		rectSpriteArray[element].h = h;
	}

	//What to happen when collided with other sprite
	void ActiveSprite::actionCollision()
	{

	}

	//Activesprite constructor with initialization list
	ActiveSprite::ActiveSprite(GameEngine * eng, int x, int y, int w, int h, int pathX, int pathY, std::string imgP) : Sprite(eng, x, y, w, h, imgP), x(x), y(y), w(w), h(h), xPath(pathX), yPath(pathY)
	{
		texture = IMG_LoadTexture(engine->getRen(), imgPath.c_str());
	}

	//Draw sprite
	void ActiveSprite::draw()
	{
		//If sprite sheet exists then use it 
		if (spriteSheet) {
			//IS THIS CORRECT? DOESNT THIS IMPLY 4 FRAMES ONLY?
			if (frame == spriteSheetCount) {
				frame = 0;
			}

			SDL_Rect* currentClip = &rectSpriteArray[frame];
			frame++;

			SDL_RenderCopy(engine->getRen(), texture, currentClip, &rect);
		}
		//Else draw without spritesheet
		else {
			SDL_RenderCopy(engine->getRen(), texture, NULL, &rect);
		}
	}

	//Advance sprite using tick, check for collision and advance moving path.
	void ActiveSprite::tick(std::vector<Sprite*> sprites) {
		for (Sprite* s : sprites) {
			if (s != this) {
				if (checkCollision(&s->rect)) {
					actionCollision();
				}
			}
		}
		tickAction();
		x += xPath;
		y += yPath;
		rect = { getX(), getY(), getW(), getH() };
	}

	//Getters and setters below
	int ActiveSprite::getX() const
	{
		return x;
	}

	int ActiveSprite::getY() const
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

	int ActiveSprite::getW() const
	{
		return w;
	}

	int ActiveSprite::getH() const
	{
		return h;
	}

	//Destructor
	ActiveSprite::~ActiveSprite()
	{

		delete rectSpriteArray;
		SDL_DestroyTexture(texture);
	}

}
