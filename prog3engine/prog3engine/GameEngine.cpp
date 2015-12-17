#include "GameEngine.h"
#include <string>
#include <algorithm>
#include <SDL_ttf.h>
#include <iostream>


namespace gengine {
	GameEngine::GameEngine(std::string title, int x, int y, int w, int h, int FPS) : frameRate(FPS) {
		win = SDL_CreateWindow(title.c_str(), x, y, w, h, 0);
		ren = SDL_CreateRenderer(win, -1, 0);
	}

	// Ändra till delad pek!!!
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
				case SDL_MOUSEBUTTONDOWN:
					for (Sprite *s : sprites) {
						TextSprite* tSprite = dynamic_cast<TextSprite*> (s);
						if (tSprite != NULL && eve.button.x >= s->getRect().x && (eve.button.x <= s->getRect().x + s->getRect().w &&
							eve.button.y >= s->getRect().y && eve.button.y <= s->getRect().y + s->getRect().h) && tSprite->getEditStatus()) {
							handleTextInput(*tSprite);
						}
					}
				case SDL_KEYUP:
				case SDL_KEYDOWN:
				case SDL_MOUSEMOTION:
					//	std::cout << eve.key.keysym.sym << std::endl;
				case SDL_MOUSEBUTTONUP:
					for (inputActions k : trackedKeys) {
						if (k.key == eve.key.keysym.sym && k.eve == eve.type) {
							k.fPointer(eve);
						}
						; break;
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
	}

	void GameEngine::setFPS(int newFPS) {
		frameRate = newFPS;
	}

	SDL_Renderer* GameEngine::getRen() const {
		return ren;
	}

	void GameEngine::addRemoveSprite(Sprite * removedSprite) {
		toBeRemoved.push_back(removedSprite);
	}

	void  GameEngine::removeSprite(Sprite *sprite) {
		sprites.erase(std::remove(sprites.begin(), sprites.end(), sprite), sprites.end());
		delete sprite;
		sprite = NULL;
	}

	void GameEngine::trackKey(SDL_EventType eve, SDL_Keycode key, void(*fPointer)(SDL_Event)) {
		trackedKeys.push_back(inputActions{ eve, key, fPointer });

	}

	void GameEngine::trackKeyState(SDL_Scancode key, void(*fPointer)()) {
		trackedKeyStates.push_back(keyStateActions{ key, fPointer });
	}

	void GameEngine::handleTextInput(TextSprite& tSprite) {
		SDL_StartTextInput();
		bool quit = false;
		SDL_Event e;
		std::string inputText = tSprite.getText();
		int frame = 0;
		const int tickInterval = 1000 / frameRate;
		Uint32 nextTick;
		int delay;

		while (!quit) {

			nextTick = SDL_GetTicks() + tickInterval;
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
				else if (e.type == SDL_KEYDOWN) {
					if (e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0) {
						inputText.pop_back();

					}
					else if (e.key.keysym.sym == SDLK_RETURN) {
						quit = true;
					}
					//Handle copy
					else if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
					{
						SDL_SetClipboardText(inputText.c_str());
					}
					//Handle paste
					else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
					{
						inputText = SDL_GetClipboardText();

					}
				}
				else if (e.type == SDL_TEXTINPUT)
				{
					if (!((e.text.text[0] == 'c' || e.text.text[0] == 'C') && (e.text.text[0] == 'v' || e.text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL))
					{
						inputText += e.text.text;

						//Glöm inte att ta bort denna
						std::cout << inputText << std::endl;
					}
				}

			}
			tSprite.setText(inputText);
			SDL_RenderClear(ren);
			for (Sprite* s : sprites) {
				s->tick(sprites);
				s->draw();

				SDL_RenderPresent(ren);
			}//inre while
			delay = nextTick - SDL_GetTicks();
			if (delay > 0)
				SDL_Delay(delay);
		}//yttre while

	}

	GameEngine::~GameEngine()
	{
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
	}
}