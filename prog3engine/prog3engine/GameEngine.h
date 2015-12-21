#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <string>
#include "Sprite.h"
#include <SDL.h>
#include <vector>
#include "TextSprite.h"
#include <map>
#include <functional>
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
		void trackKey(SDL_EventType, SDL_Keycode, std::function<void()>);
		void trackKeyState(SDL_Scancode, std::function<void(void)> func);
		void handleTextInput(TextSprite&);
		~GameEngine();
		template <typename TYPE>
		void trackMemberKey(SDL_EventType, SDL_Keycode, TYPE *oPoint, void(TYPE::*memberPointer)());
	private:
		void removeSprite(Sprite*);
		friend class Sprite;
		SDL_Window* win;
		SDL_Renderer* ren;
		std::vector<Sprite*> sprites, toBeRemoved;
		std::map<std::pair<Uint32, SDL_Keycode>, std::function<void()>> trackedKeys;
		std::map<std::pair<Uint32, SDL_Keycode>, std::function<void(void)>> memberTrackedKeys;
		std::map<SDL_Scancode, std::function<void(void)>> trackedKeyStates;
		int frameRate;
	};


	template<typename TYPE>
	inline void GameEngine::trackMemberKey(SDL_EventType eve, SDL_Keycode key, TYPE *oPoint, void(TYPE::*memberPointer)())
	{
		auto lambdaFunction = [=]() { (*oPoint.*memberPointer)(); };
		memberTrackedKeys.insert(std::make_pair(std::make_pair(eve, key), lambdaFunction));
	}

}
#endif

