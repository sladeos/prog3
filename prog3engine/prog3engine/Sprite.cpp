#include "Sprite.h"
#include "GameEngine.h"

namespace gengine {

	Sprite::Sprite(GameEngine * eng, int x, int y, int w, int h, std::string imgP) :engine(eng), rect{ x,y,w,h }, imgPath(imgP)
	{
		eng->add(this);
	}

	bool const Sprite::checkCollision(SDL_Rect * otherRect)
	{
		//The sides of the rectangles
		int leftA, leftB;
		int rightA, rightB;
		int topA, topB;
		int bottomA, bottomB;

		//Calculate the sides of rect A
		leftA = rect.x;
		rightA = rect.x + rect.w;
		topA = rect.y;
		bottomA = rect.y + rect.h;

		//Calculate the sides of rect B
		leftB = otherRect->x;
		rightB = otherRect->x + otherRect->w;
		topB = otherRect->y;
		bottomB = otherRect->y + otherRect->h;
		//If any of the sides from A are outside of B
		if (bottomA <= topB)
		{
			return false;
		}

		if (topA >= bottomB)
		{
			return false;
		}

		if (rightA <= leftB)
		{
			return false;
		}

		if (leftA >= rightB)
		{
			return false;
		}

		//If none of the sides from A are outside B
		return true;
	}

	 SDL_Rect Sprite::getRect() const
	{
		return rect;
	}

	Sprite::~Sprite()
	{
	}




}