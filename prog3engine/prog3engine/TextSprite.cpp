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

	//Constructor with initialization list
	TextSprite::TextSprite(GameEngine * eng, int x, int y, int w, int h, SDL_Color color, TTF_Font *font, std::string text, bool editable) : Sprite(eng, x, y, w, h, text), x(x), y(y), w(w), h(h), color(color), font(font), text(text), editable(editable)
	{
		SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
		texture = SDL_CreateTextureFromSurface(engine->getRen(), textSurface);
		SDL_FreeSurface(textSurface);
	}

	//Function for setting sprite text
	void TextSprite::setText(std::string newText)
	{
		text = newText;
	}

	//Returns the text 
	std::string TextSprite::getText() const
	{
		return text;
	}

	//Draw the sprite
	void TextSprite::draw()
	{
		//Destroys old texture and redraws with text variable
		SDL_DestroyTexture(texture);
		SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
		texture = SDL_CreateTextureFromSurface(engine->getRen(), textSurface);
		SDL_RenderCopy(engine->getRen(), texture, NULL, &rect);
		SDL_FreeSurface(textSurface);
	}

	//Destructor
	TextSprite::~TextSprite()
	{
		TTF_CloseFont(font);
		SDL_DestroyTexture(texture);
	}
	//getters and setters for editable (Determine if its possible to edit the sprite text)
	bool TextSprite::getEditStatus() const
	{
		return editable;
	}

	void TextSprite::setEditStatus(bool newEditStatus)
	{
		editable = newEditStatus;
	}

}