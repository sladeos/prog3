#include "TextSprite.h"
#include "GameEngine.h"
#include "SDL_image.h"
#include <string>
#include <SDL.h>
#include<iostream>

namespace gengine {

	TextSprite * TextSprite::getInstance(GameEngine * eng, int x, int y, int w, int h, SDL_Color color, TTF_Font *font, std::string text)
	{
		return new TextSprite(eng, x, y, w, h, color, font, text);
	}

	TextSprite::TextSprite(GameEngine * eng, int x, int y, int w, int h, SDL_Color color, TTF_Font *font, std::string text) : Sprite(eng, x, y, w, h, text), x(x), y(y), w(w), h(h), color(color), font(font), text(text)
	{
		SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
		texture = SDL_CreateTextureFromSurface(engine->getRen(), textSurface);
	}

	void TextSprite::setText(std::string newText)
	{
	}

	std::string TextSprite::getText() const
	{
		return std::string();
	}

	void TextSprite::draw()
	{
		SDL_RenderCopy(engine->getRen(), texture, NULL, &rect);
	}

	

	TextSprite::~TextSprite()
	{
		TTF_CloseFont(font);
		SDL_DestroyTexture(texture);
	}

}