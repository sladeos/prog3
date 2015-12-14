#include "FixedSprite.h"
#include "GameEngine.h"
#include "SDL_image.h"
#include <string>

namespace gengine {

	FixedSprite* FixedSprite::getInstance(GameEngine * eng, int x, int y, int w, int h, std::string imgP) {
		return new FixedSprite(eng, x, y, w, h, imgP);
	}

	void FixedSprite::actionCollision()
	{
		
	}

	FixedSprite::FixedSprite(GameEngine * eng, int x, int y, int w, int h, std::string imgP) : Sprite(eng, x, y, w, h, imgP) {
		texture = IMG_LoadTexture(engine->getRen(), imgPath.c_str());
	}

	void FixedSprite::draw() {
		SDL_RenderCopy(engine->getRen(), texture, NULL, &rect);
	}

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

	FixedSprite::~FixedSprite()
	{

		SDL_DestroyTexture(texture);
	}

}
