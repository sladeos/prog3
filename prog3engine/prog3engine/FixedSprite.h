#ifndef FIXEDSPRITE_H
#define FIXEDSPRITE_H

#include "Sprite.h"
#include "SDL.h"

namespace gengine {
	class FixedSprite : public Sprite
	{
	public:
		void draw();
		void tick(std::vector <Sprite*>);
		static FixedSprite* getInstance(GameEngine* eng, int x, int y, int w, int h, std::string imgP, bool isBackground);
		virtual void actionCollision();
		~FixedSprite();
	protected:
		FixedSprite(GameEngine* eng, int x, int y, int w, int h, std::string imgP, bool isBackground);
		SDL_Texture* texture;
	private:
	

	};
}

#endif

