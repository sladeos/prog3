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
		void trackKey(SDL_EventType, SDL_Keycode, std::function<void()>);
		void trackEvent(std::function<void(void)>);
		void trackKeyState(SDL_Scancode, std::function<void()> func);
		template <typename TYPE>
		void trackMemberKey(SDL_EventType, SDL_Keycode, TYPE *oPoint, void(TYPE::*memberPointer)());
		void handleTextInput(TextSprite&);
		const int getW() const;
		const int getH() const;
		int getFrame() const;
		std::vector<Sprite*> getSprites() const;
		void unsetTrackKey(Uint32, SDL_Keycode);
		void unsetTrackKeyState(SDL_Scancode);
		void unsetTrackMemberKey(Uint32, SDL_Keycode);

		void unsetAllTrackKey();
		void unsetAllTrackKeyState();
		void unsetAllTrackMemberKey();
		void unsetAllTrackEvent();

		~GameEngine();
	private:
		void removeSprite(Sprite*);
		void removalOfTrackedKeys();
		friend class Sprite;
		SDL_Window* win;
		SDL_Renderer* ren;
		std::vector<Sprite*> sprites, toBeRemoved, toBeLoaded;
		std::vector <std::function<void(void)>> trackedEvents;
		std::map<std::pair<Uint32, SDL_Keycode>, std::function<void()>> trackedKeys;

		std::map<std::pair<Uint32, SDL_Keycode>, std::function<void()>> memberTrackedKeys;
		std::map<SDL_Scancode, std::function<void()>> trackedKeyStates;
		int frameRate, frame = 0;
		const int w, h;
		bool toUnsetTrackKey = false, toUnsetTrackEvent = false, toUnsetKeyState = false, toUnsetTrackMemberKey = false;
		std::vector<std::pair<Uint32, SDL_Keycode>> trackKeyUnset, trackMemberKeyUnset;
		std::vector<SDL_Scancode> trackKeyStateUnset;
	};


	template<typename TYPE>
	inline void GameEngine::trackMemberKey(SDL_EventType eve, SDL_Keycode key, TYPE *oPoint, void(TYPE::*memberPointer)())
	{
		auto lambdaFunction = [=]() { (*oPoint.*memberPointer)(); };
		memberTrackedKeys.insert(std::make_pair(std::make_pair(eve, key), lambdaFunction));
	}

}
#endif

