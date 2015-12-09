#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <string>
#include "Sprite.h"
#include <SDL.h>
#include <vector>

namespace gengine {
	class GameEngine
	{
	public:
		GameEngine(std::string title, int x, int y, int w, int h);
		void add(Sprite* sprite);
		void run();
		void loadLevel();
		SDL_Renderer* getRen() const;
		~GameEngine();
	private:
		friend class Sprite;
		SDL_Window* win;
		SDL_Renderer* ren;
		std::vector<Sprite*> sprites;
		int frameRate;
	};
}

#endif

