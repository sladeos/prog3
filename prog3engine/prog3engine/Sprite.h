#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include <string>
#include <vector>

namespace gengine {

	class GameEngine;

	class Sprite
	{
	public:
		const bool isBackground;
		virtual void draw() = 0;
		virtual void tick(std::vector<Sprite*>) {}
		virtual ~Sprite();
		virtual SDL_Rect getRect()const;
	protected:
		Sprite(GameEngine* eng, int x, int y, int w, int h, std::string imgP, bool isBackground);
		SDL_Rect rect;
		GameEngine* engine;
		std::string imgPath;
		bool const checkCollision(SDL_Rect* otherRect);
		virtual void actionCollision(Sprite* s) {}
	private:
		friend class FixedSprite;
		friend class ActiveSprite;
		friend class TextSprite;
		Sprite(const Sprite&) = delete;
		const Sprite& operator=(const Sprite&) = delete;
	};
}

#endif