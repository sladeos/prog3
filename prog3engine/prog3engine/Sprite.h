#pragma once

#include <SDL.h>

class Sprite
{
public:
	Sprite();
	void draw();
	void tick();
	~Sprite();
private:
	int posX;
	int posY;
	int width;
	int height;
	// SDL_Texture image;
};

