#pragma once

#include <string>
#include "Sprite.h"
#include <SDL.h>
#include <vector>

class GameEngine
{
public:
	GameEngine(std::string title, int x, int y, int w, int h);
	void add();
	void run();
	void loadLevel();
	~GameEngine();
private:
	SDL_Window* win;
	SDL_Renderer* ren;
	std::vector<Sprite*> sprites;
	int frameRate;
};

