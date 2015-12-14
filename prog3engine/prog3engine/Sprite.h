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
		virtual void draw() = 0;
		virtual void tick(std::vector<Sprite*>) {}
		~Sprite();
	protected:
		Sprite(GameEngine* eng, int x, int y, int w, int h, std::string imgP);
		SDL_Rect rect;
		GameEngine* engine;
		std::string imgPath;
		bool const checkCollision(SDL_Rect* otherRect);
		void actionCollision();
	private:
		friend class FixedSprite;
		friend class ActiveSprite;
		Sprite(const Sprite&) = delete;
		const Sprite& operator=(const Sprite&) = delete;
	};
}

#endif