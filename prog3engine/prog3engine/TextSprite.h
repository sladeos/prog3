#ifndef TEXTSPRITE_H
#define TEXTSPRITE_H

#include "Sprite.h"
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

namespace gengine {

	class TextSprite : public Sprite
	{
	public:
		static TextSprite* getInstance(GameEngine* eng, int x, int y, int w, int h, SDL_Color color, TTF_Font *font, std::string text, bool editable);
		void setText(std::string newText);
		const std::string getText();
		void draw();
		~TextSprite();
		const bool getEditStatus();
		void setEditStatus(bool);
	protected:
		SDL_Texture* texture;
		SDL_Color color;
		TTF_Font *font;
		int x, y, w, h;
		std::string text;
		TextSprite(GameEngine* eng, int x, int y, int w, int h, SDL_Color color, TTF_Font *font, std::string text, bool editable);
	private:
		bool editable;
	};

}

#endif
