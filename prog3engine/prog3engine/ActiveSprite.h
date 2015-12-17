#ifndef ACTIVESPRITE_H
#define ACTIVESPRITE_H

#include "Sprite.h"
#include <string>
#include <SDL.h>
#include <vector>

namespace gengine {
	class ActiveSprite : public Sprite
	{
	public:
		static ActiveSprite* getInstance(GameEngine* eng, int x, int y, int w, int h, int pathX, int pathY, std::string imgP);
		~ActiveSprite();
		void draw();
		void tick(std::vector <Sprite*>);
		int getX() const;
		int getY() const;
		void setX(int x);
		void setY(int y);
		int getW() const;
		int getH() const;
		void setXpath(int newX);
		void setYpath(int newY);
		void initSpriteSheet(int elementCount);
		void addSpriteClip(int element, int x, int y, int w, int h);
		virtual void actionCollision();
	protected:
		SDL_Texture* texture;
		int x, y, w, h, xPath, yPath;
		SDL_Rect* rectSpriteArray;
		int frame;
		bool spriteSheet = false;
		ActiveSprite(GameEngine* eng, int x, int y, int w, int h, int pathX, int pathY, std::string imgP);
	private:

	};
}

#endif

