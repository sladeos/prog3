#include "Sprite.h"
#include "GameEngine.h"

namespace gengine {

	Sprite::Sprite(GameEngine * eng, int x, int y, int w, int h, std::string imgP) :engine(eng), rect{ x,y,w,h}, imgPath(imgP)
	{
		eng->add(this);
	}

	Sprite::~Sprite()
	{
	}

	
}