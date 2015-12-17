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
		template<typename TYPE>
		void trackKey(SDL_EventType, SDL_Keycode, TYPE*, void TYPE::*());
		void trackKeyState(SDL_Scancode, void(*fPointer)());
		void handleTextInput(TextSprite&);
		~GameEngine();
		//template <typename TYPE>
		//void trackKey(SDL_EventType, SDL_Keycode, TYPE *oPoint, void TYPE::*mPointer(SDL_Event));
		//template <typename TYPE>
		//void trackKeyState(SDL_Scancode, TYPE *oPoint, void TYPE::*mPointer();

	private:
		void removeSprite(Sprite*);
		friend class Sprite;
		SDL_Window* win;
		SDL_Renderer* ren;
		std::vector<Sprite*> sprites, toBeRemoved;
		struct inputActions { SDL_EventType eve; SDL_Keycode key; void(*fPointer)(SDL_Event); } ;
		template<typename TYPE>
		struct memberInputActions { SDL_EventType eve; SDL_Keycode key; TYPE *objP; void Sprite::* memP(SDL_Event); };
		struct keyStateActions { SDL_Scancode key; void(*fPointer)(); };
		std::vector<inputActions> trackedKeys;
		template<typename TYPE>
		std::vector<memberInputActions<TYPE>> memberTrackedKeys;
		std::vector<keyStateActions> trackedKeyStates;
		int frameRate;
	};

	
	

	
}

#endif

