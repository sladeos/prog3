#include "GameEngine.h"
#include <string>
#include <algorithm>
#include <SDL_ttf.h>
#include <iostream>


namespace gengine {
	//Constructor with initialization list
	GameEngine::GameEngine(std::string title, int x, int y, int w, int h, int FPS) : frameRate(FPS), w(w), h(h) {
		win = SDL_CreateWindow(title.c_str(), x, y, w, h, 0);
		ren = SDL_CreateRenderer(win, -1, 0);
	}

	// Ändra till delad pek!!!
	void GameEngine::add(Sprite* sprite) {
		sprites.push_back(sprite);
	}

	//Function that handles gameengine main functionality
	void GameEngine::run() {
		//Prepare for running game
		SDL_RenderClear(ren);
		for (Sprite* s : sprites)
			s->draw();
		SDL_RenderPresent(ren);
		bool goOn = true;

		const int tickInterval = 1000 / frameRate;
		Uint32 nextTick;
		int delay;

		//Running game engine loop
		while (goOn) {
			//Calculate tick interval
			nextTick = SDL_GetTicks() + tickInterval;
			SDL_Event eve;

			//Check for event
			while (SDL_PollEvent(&eve)) {
				//Check event type if event has been triggered
				switch (eve.type) {
				case SDL_QUIT: goOn = false; break;
				case SDL_MOUSEBUTTONDOWN:
					//Check if a sprite has been clicked
					for (Sprite *s : sprites) {
						TextSprite* tSprite = dynamic_cast<TextSprite*> (s);
						if (tSprite != NULL && eve.button.x >= s->getRect().x && (eve.button.x <= s->getRect().x + s->getRect().w &&
							eve.button.y >= s->getRect().y && eve.button.y <= s->getRect().y + s->getRect().h) && tSprite->getEditStatus()) {
							//Start handling editing sprite text
							handleTextInput(*tSprite);
						}
					}
				case SDL_KEYUP:
				case SDL_KEYDOWN:
					//Check for keys tracked to a function then execute
					auto it = trackedKeys.find(std::make_pair(eve.type, eve.key.keysym.sym));
					if (it != trackedKeys.end()) {
						it->second();
					}
					//Check for keys tracked to a memberfunction then execute
					auto iter = memberTrackedKeys.find(std::make_pair(eve.type, eve.key.keysym.sym));
					if (iter != memberTrackedKeys.end()) {
						iter->second();
					}

					; break;


				} // switch
			} // inre while

			//Handle tracked keystates and execute corresponding function(s)
			const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
			for (auto iter = trackedKeyStates.cbegin(); iter != trackedKeyStates.cend(); ++iter) {
				if (currentKeyStates[iter->first])
					iter->second();
			}

			//Clear renderer then advance sprites with tick, after done then draw sprites in new locations
			SDL_RenderClear(ren);
			for (Sprite* s : sprites) {
				s->tick(sprites);
				s->draw();
			}

			//Delay loop to match tick interval and remove sprites that should be removed
			SDL_RenderPresent(ren);
			delay = nextTick - SDL_GetTicks();
			if (delay > 0)
				SDL_Delay(delay);

			//Loop through sprites to be removed and remove them, clear vector.
			for (Sprite *s : toBeRemoved) {
				removeSprite(s);
			}
			toBeRemoved.clear();

			//If toBeLoaded vector is not empty the user wishes to load a level, set sprites vector to toBeLoaded.
			if (!toBeLoaded.empty()) {
				for (Sprite* sprite : sprites) {
					toBeRemoved.push_back(sprite);
				}
				sprites = toBeLoaded;
				toBeLoaded.clear();
			}
			removalOfTrackedKeys();

			for (std::function<void(void)> func : trackedEvents) {
				func();
			}

			frame++;
		} // yttre while

	}

	//Loops through sprites vector, adds them to toBeRemoved vector, sets toBeLoaded vector to level sprites.
	void GameEngine::loadLevel(Level *level)
	{
		toBeLoaded = level->getSprites();
		removalOfTrackedKeys();
		
	}

	//NOT USED?
	void GameEngine::setFPS(int newFPS) {
		frameRate = newFPS;
	}

	//Return gameengine renderer
	SDL_Renderer* GameEngine::getRen() const {
		return ren;
	}

	//Adds a sprite to be removed list, which removes the sprite from "sprites" in the end of the loop.
	void GameEngine::addRemoveSprite(Sprite * removedSprite) {
		toBeRemoved.push_back(removedSprite);
	}

	//Remove sprite 
	void  GameEngine::removeSprite(Sprite *sprite) {
		sprites.erase(std::remove(sprites.begin(), sprites.end(), sprite), sprites.end());
		delete sprite;
	}

	void gengine::GameEngine::removalOfTrackedKeys()
	{
		if (!trackKeyUnset.empty()) {
			for (std::pair<Uint32, SDL_Keycode> pair : trackKeyUnset) {
				trackedKeys.erase(pair);
			}
			trackKeyUnset.clear();

		}
		if (!trackKeyStateUnset.empty()) {
			for (SDL_Scancode code : trackKeyStateUnset) {
				trackedKeyStates.erase(code);
			}
			trackKeyStateUnset.clear();
		}
		if (!trackMemberKeyUnset.empty()) {
			for (std::pair<Uint32, SDL_Keycode> pair : trackMemberKeyUnset) {
				memberTrackedKeys.erase(pair);
			}
			trackMemberKeyUnset.clear();
		}

		if (toUnsetTrackKey) {
			trackedKeys.clear();
			toUnsetTrackKey = false;
		}

		if (toUnsetTrackEvent) {
			trackedEvents.clear();
			toUnsetTrackEvent = false;
		}
		if (toUnsetKeyState) {
			trackedKeyStates.clear();
			toUnsetKeyState = false;
		}
		if (toUnsetTrackMemberKey) {
			memberTrackedKeys.clear();
			toUnsetTrackMemberKey = false;
		}
	}

	//Function for adding tracking function to a key
	void GameEngine::trackKey(SDL_EventType eve, SDL_Keycode key, std::function<void()> func) {
		trackedKeys.insert(std::make_pair(std::make_pair(eve, key), func));
	}

	//tracking an event to a function
	void GameEngine::trackEvent(std::function<void(void)> func)
	{
		trackedEvents.push_back(func);
	}

	//Function for adding tracking keystate
	void GameEngine::trackKeyState(SDL_Scancode key, std::function<void()> func) {
		trackedKeyStates.insert(std::make_pair(key, func));
	}

	//Handling writing to a sprite with text
	void GameEngine::handleTextInput(TextSprite& tSprite) {
		//Preparations
		SDL_StartTextInput();
		bool quit = false;
		SDL_Event e;
		std::string inputText = tSprite.getText();
		const int tickInterval = 1000 / frameRate;
		Uint32 nextTick;
		int delay;

		//Writing loop
		while (!quit) {
			//Calculate ticks
			nextTick = SDL_GetTicks() + tickInterval;
			//Check for events
			while (SDL_PollEvent(&e) != 0)
			{
				//Check event type
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
				//if keydown
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
				//if textinput
				else if (e.type == SDL_TEXTINPUT)
				{
					if (!((e.text.text[0] == 'c' || e.text.text[0] == 'C') && (e.text.text[0] == 'v' || e.text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL))
					{
						inputText += e.text.text;
					}
				}
			}
			//Add text to sprite, tick and redraw
			tSprite.setText(inputText);
			SDL_RenderClear(ren);
			for (Sprite* s : sprites) {
				s->tick(sprites);
				s->draw();

				SDL_RenderPresent(ren);
			}//inre while
			//Delay ticks to match interval
			delay = nextTick - SDL_GetTicks();
			if (delay > 0)
				SDL_Delay(delay);


		}//yttre while
	}

	//Get width
	const int GameEngine::getW() const
	{
		return w;
	}

	//Get height
	const int GameEngine::getH() const
	{
		return h;
	}

	int GameEngine::getFrame() const
	{
		return frame;
	}

	//Return vector containing sprites
	std::vector<Sprite*> GameEngine::getSprites() const
	{
		return sprites;
	}
	void gengine::GameEngine::unsetTrackKey(Uint32 event, SDL_Keycode keycode)
	{

		trackKeyUnset.push_back(std::make_pair(event, keycode));
	}
	void gengine::GameEngine::unsetTrackKeyState(SDL_Scancode scancode)
	{
		trackKeyStateUnset.push_back(scancode);
	}
	void gengine::GameEngine::unsetTrackMemberKey(Uint32 event, SDL_Keycode keycode)
	{
		trackMemberKeyUnset.push_back(std::make_pair(event, keycode));
	}
	void gengine::GameEngine::unsetAllTrackKey()
	{
		toUnsetTrackKey = true;
	}
	void gengine::GameEngine::unsetAllTrackKeyState()
	{
		toUnsetKeyState = true;
	}
	void gengine::GameEngine::unsetAllTrackMemberKey()
	{
		toUnsetTrackMemberKey = true;
	}
	void gengine::GameEngine::unsetAllTrackEvent()
	{
		toUnsetTrackEvent = true;
	}
	//Destructor
	GameEngine::~GameEngine()
	{
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
	}
}