#include "GameEngine.h"
#include <string>
#include <algorithm>
namespace gengine {
	GameEngine::GameEngine(std::string title, int x, int y, int w, int h, int FPS): frameRate(FPS) {
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
		int frame = 0;
		const int tickInterval = 1000 / frameRate;
		Uint32 nextTick;
		int delay;
		while (goOn) {
			nextTick = SDL_GetTicks() + tickInterval;
			SDL_Event eve;
			while (SDL_PollEvent(&eve)) {
				switch (eve.type) {
				case SDL_QUIT: goOn = false; break;

					// Saker som händer

				} // switch
			} // inre while

			SDL_RenderClear(ren);
			for (Sprite* s : sprites){
			s->tick(sprites);
			s->draw();
			}
			SDL_RenderPresent(ren);
			delay = nextTick - SDL_GetTicks();
			if (delay > 0)
				SDL_Delay(delay);
			for (Sprite *s : toBeRemoved) {
				removeSprite(s);
			}
			toBeRemoved.clear();


		} // yttre while
	}

	void GameEngine::setFPS(int newFPS)
	{
		frameRate = newFPS;
	}

	SDL_Renderer* GameEngine::getRen() const {
		return ren;
	}

	void GameEngine::addRemoveSprite(Sprite * removedSprite)
	{
		toBeRemoved.push_back(removedSprite);
	}

	void  GameEngine::removeSprite(Sprite *sprite)
	{
		sprites.erase(std::remove(sprites.begin(), sprites.end(), sprite), sprites.end());
		delete sprite;
	}

	GameEngine::~GameEngine()
	{
	}
}