#include "GameEngine.h"
#include <string>
#include <algorithm>
#include <SDL_ttf.h>

namespace gengine {
	GameEngine::GameEngine(std::string title, int x, int y, int w, int h, int FPS) : frameRate(FPS) {
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
				case SDL_KEYUP:
				case SDL_KEYDOWN:
				case SDL_MOUSEBUTTONDOWN:
				case SDL_MOUSEBUTTONUP:
					for (inputActions k : trackedKeys) {
						if (k.key == eve.key.keysym.sym && k.eve == eve.type) {
							k.fPointer();
						}
					}

					; break;

					// Saker som händer

				} // switch
			} // inre while

			const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
			for (keyStateActions k : trackedKeyStates) {
				if (currentKeyStates[k.key]) {
					k.fPointer();
				}
			}

			SDL_RenderClear(ren);
			for (Sprite* s : sprites) {
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

	void GameEngine::trackKey(SDL_EventType eve, SDL_Keycode key, void(*fPointer)())
	{
		trackedKeys.push_back(inputActions{ eve, key, fPointer });

	}

	void GameEngine::trackKeyState(SDL_Scancode key, void(*fPointer)())
	{
		trackedKeyStates.push_back(keyStateActions{ key, fPointer });
	}

	GameEngine::~GameEngine()
	{
	}
}