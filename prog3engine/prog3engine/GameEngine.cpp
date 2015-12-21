#include "GameEngine.h"
#include <string>
#include <algorithm>
#include <SDL_ttf.h>
#include <iostream>


namespace gengine {
	GameEngine::GameEngine(std::string title, int x, int y, int w, int h, int FPS) : frameRate(FPS), w(w), h(h) {
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
					auto it = trackedKeys.find(std::make_pair(eve.type, eve.key.keysym.sym));
					if (it != trackedKeys.end()) {
						it->second(eve);
					}

					auto iter = memberTrackedKeys.find(std::make_pair(eve.type, eve.key.keysym.sym));
					if (iter != memberTrackedKeys.end()) {
						iter->second(eve);
					}
					; break;


				} // switch
			} // inre while

			const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
			for (auto iter = trackedKeyStates.cbegin(); iter != trackedKeyStates.cend(); ++iter) {
				if (currentKeyStates[iter->first])
					iter->second(eve);
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

			for (std::function<void(void)> func : trackedEvents) {
				func();
			}
		} // yttre while
	}

	void GameEngine::loadLevel(Level *level)
	{
		for (Sprite* s : sprites) {
			delete s;
		}
		sprites.clear();
		sprites = level->getSprites();
		
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

	void GameEngine::trackKey(SDL_EventType eve, SDL_Keycode key, std::function<void(SDL_Event)> func) {
		trackedKeys.insert(std::make_pair(std::make_pair(eve, key), func));
	}

	void GameEngine::trackEvent(std::function<void(void)> func)
	{
		trackedEvents.push_back(func);
	}

	void GameEngine::trackKeyState(SDL_Scancode key, std::function<void(SDL_Event)> func) {
		trackedKeyStates.insert(std::make_pair(key, func));
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

	const int GameEngine::getW() const
	{
		return w;
	}


	const int GameEngine::getH() const
	{
		return h;
	}

	std::vector<Sprite*> GameEngine::getSprites() const
	{
		return sprites;
	}

	GameEngine::~GameEngine()
	{
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
	}
}