#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <string>
#include "Sprite.h"
#include <SDL.h>
#include <vector>
#include "TextSprite.h"
#include <map>
#include <functional>
#include "Level.h"
namespace gengine {
	class GameEngine
	{
	public:
		GameEngine(std::string title, int x, int y, int w, int h, int fps);
		void add(Sprite* sprite);
		void run();
		void loadLevel(Level*);
		void setFPS(int newFPS);
		SDL_Renderer* getRen() const;
		void addRemoveSprite(Sprite*);
		void trackKey(SDL_EventType, SDL_Keycode, std::function<void(SDL_Event)>);
		void trackEvent(std::function<void(void)>);
		void trackKeyState(SDL_Scancode, std::function<void(SDL_Event)> func);
		void handleTextInput(TextSprite&);
		const int getW() const;
		const int getH() const;
		std::vector<Sprite*> getSprites() const;
		~GameEngine();
		template <typename TYPE>
		void trackMemberKey(SDL_EventType, SDL_Keycode, TYPE *oPoint, void(TYPE::*memberPointer)(SDL_Event));
	private:
		void removeSprite(Sprite*);
		friend class Sprite;
		SDL_Window* win;
		SDL_Renderer* ren;
		std::vector<Sprite*> sprites, toBeRemoved;
		std::vector <std::function<void(void)>> trackedEvents;
		std::map<std::pair<Uint32, SDL_Keycode>, std::function<void(SDL_Event)>> trackedKeys;
		std::map<std::pair<Uint32, SDL_Keycode>, std::function<void(SDL_Event)>> memberTrackedKeys;
		std::map<SDL_Scancode, std::function<void(SDL_Event)>> trackedKeyStates;
		int frameRate;
		const int w, h;
	};


	template<typename TYPE>
	inline void GameEngine::trackMemberKey(SDL_EventType eve, SDL_Keycode key, TYPE *oPoint, void(TYPE::*memberPointer)(SDL_Event))
	{
		auto lambdaFunction = [=]() { (*oPoint.*memberPointer)(SDL_Event); };
		memberTrackedKeys.insert(std::make_pair(std::make_pair(eve, key), lambdaFunction));
	}

}
#endif

