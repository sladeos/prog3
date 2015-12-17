#include "TextSprite.h"
#include "GameEngine.h"
#include "SDL_image.h"
#include <string>
#include <SDL.h>
#include<iostream>

namespace gengine {

	TextSprite * TextSprite::getInstance(GameEngine * eng, int x, int y, int w, int h, SDL_Color color, TTF_Font *font, std::string text, bool editable)
	{
		return new TextSprite(eng, x, y, w, h, color, font, text, editable);
	}

	TextSprite::TextSprite(GameEngine * eng, int x, int y, int w, int h, SDL_Color color, TTF_Font *font, std::string text, bool editable) : Sprite(eng, x, y, w, h, text), x(x), y(y), w(w), h(h), color(color), font(font), text(text), editable(editable)
	{
		SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
		texture = SDL_CreateTextureFromSurface(engine->getRen(), textSurface);
		SDL_FreeSurface(textSurface);
	}

	void TextSprite::setText(std::string newText)
	{
		text = newText;
	}

	std::string TextSprite::getText() const
	{
		return text;
	}

	void TextSprite::draw()
	{
		SDL_DestroyTexture(texture);
		SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
		texture = SDL_CreateTextureFromSurface(engine->getRen(), textSurface);
		SDL_RenderCopy(engine->getRen(), texture, NULL, &rect);
		SDL_FreeSurface(textSurface);
	}

	TextSprite::~TextSprite()
	{
		TTF_CloseFont(font);
		SDL_DestroyTexture(texture);
	}

	bool TextSprite::getEditStatus() const
	{
		return editable;
	}

	void TextSprite::setEditStatus(bool newEditStatus)
	{
		editable = newEditStatus;
	}

}