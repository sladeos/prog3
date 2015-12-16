#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <string>
#include "Sprite.h"
#include <SDL.h>
#include <vector>
#include "TextSprite.h"

namespace gengine {
	class GameEngine
	{
	public:
		GameEngine(std::string title, int x, int y, int w, int h, int fps);
		void add(Sprite* sprite);
		void run();
		void loadLevel();
		void setFPS(int newFPS);
		SDL_Renderer* getRen() const;
		void addRemoveSprite(Sprite*);
		void trackKey(SDL_EventType, SDL_Keycode, void(*fPointer)(SDL_Event));
		void trackKeyState(SDL_Scancode, void(*fPointer)());
		void handleTextInput(TextSprite&);
		~GameEngine();
	private:
		void removeSprite(Sprite*);
		friend class Sprite;
		SDL_Window* win;
		SDL_Renderer* ren;
		std::vector<Sprite*> sprites, toBeRemoved;
		struct inputActions { SDL_EventType eve; SDL_Keycode key; void(*fPointer)(SDL_Event); } ;
		struct keyStateActions { SDL_Scancode key; void(*fPointer)(); };
		std::vector<inputActions> trackedKeys;
		std::vector<keyStateActions> trackedKeyStates;
		int frameRate;
	};
}

#endif

