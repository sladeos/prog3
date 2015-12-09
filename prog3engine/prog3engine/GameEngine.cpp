#include "GameEngine.h"
#include <string>

namespace gengine {
	GameEngine::GameEngine(std::string title, int x, int y, int w, int h) {
		win = SDL_CreateWindow(title.c_str(), x, y, w, h, 0);
		ren = SDL_CreateRenderer(win, -1, 0);

	}

	// (Eng) Change to shared pointer!!!
	// (SWE) Ändra till delad pek!!!
	void GameEngine::add(Sprite* sprite) {
		sprites.push_back(sprite);
	}

	void GameEngine::run() {
		SDL_RenderClear(ren);
		for (Sprite* s : sprites)
		s->draw();
		SDL_RenderPresent(ren);

		bool goOn = true;
		while (goOn) {
			SDL_Event eve;
			while (SDL_PollEvent(&eve)) {
				switch (eve.type) {
				case SDL_QUIT: goOn = false; break;

					// Saker som händer

				} // switch
			} // inre while

			SDL_RenderClear(ren);
			for (Sprite* s : sprites)
			s->draw();
			SDL_RenderPresent(ren);

		} // yttre while
	}

	SDL_Renderer* GameEngine::getRen() const {
		return ren;
	}

	GameEngine::~GameEngine()
	{
	}
}