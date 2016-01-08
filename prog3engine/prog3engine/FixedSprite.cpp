#include "FixedSprite.h"
#include "GameEngine.h"
#include "SDL_image.h"
#include <string>

namespace gengine {

	
	FixedSprite* FixedSprite::getInstance(GameEngine * eng, int x, int y, int w, int h, std::string imgP, bool isBackground) {
		return new FixedSprite(eng, x, y, w, h, imgP, isBackground);
	}

	//Perform on collision
	void FixedSprite::actionCollision()
	{
		
	}

	//Constructor of Fixedsprite
	FixedSprite::FixedSprite(GameEngine * eng, int x, int y, int w, int h, std::string imgP, bool isBackground) : Sprite(eng, x, y, w, h, imgP, isBackground) {
		texture = IMG_LoadTexture(engine->getRen(), imgPath.c_str());
	}

	//Draw sprite
	void FixedSprite::draw() {
		SDL_RenderCopy(engine->getRen(), texture, NULL, &rect);
	}

	//Advance sprite by checking collision
	void FixedSprite::tick(std::vector<Sprite*> sprites)
	{
		for (Sprite* s : sprites) {
			if (s != this) {
				if (checkCollision(&s->rect)) {
					actionCollision();
				}
			}
		}
	}

	//Destructor
	FixedSprite::~FixedSprite()
	{

		SDL_DestroyTexture(texture);
	}

}
