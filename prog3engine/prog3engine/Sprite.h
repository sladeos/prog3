#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include <string>

namespace gengine {

	class GameEngine;

	class Sprite
	{
	public:
		virtual void draw() = 0;
		virtual void tick() {}
		~Sprite();
	protected:
		Sprite(GameEngine* eng, int x, int y, int w, int h, std::string imgP);
		SDL_Rect rect;
		GameEngine* engine;
		std::string imgPath;
	private:
		Sprite(const Sprite&) = delete;
		const Sprite& operator=(const Sprite&) = delete;
		// SDL_Texture image;
	};
}

#endif