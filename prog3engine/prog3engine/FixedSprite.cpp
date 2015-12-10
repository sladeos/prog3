#include "FixedSprite.h"
#include "GameEngine.h"
#include "SDL_image.h"
#include <string>

namespace gengine {

	FixedSprite* FixedSprite::getInstance(GameEngine * eng, int x, int y, int w, int h, std::string imgP) {
		return new FixedSprite(eng, x, y, w, h, imgP);
	}

	FixedSprite::FixedSprite(GameEngine * eng, int x, int y, int w, int h, std::string imgP) : Sprite(eng, x, y, w, h, imgP) {
		texture = IMG_LoadTexture(engine->getRen(), imgPath.c_str());
	}

	void FixedSprite::draw() {
		SDL_RenderCopy(engine->getRen(), texture, NULL, &rect);
	}

	FixedSprite::~FixedSprite()
	{
		SDL_DestroyTexture(texture);
	}

}
