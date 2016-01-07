#ifndef PLAYERSPRITE_H
#define PLAYERSPRITE_H


#include "ActiveSprite.h"
using namespace gengine;
class PlayerSprite : public ActiveSprite
{

public:
	static PlayerSprite* getInstance(GameEngine* eng, int x, int y, int w, int h, int pathX, int pathY, std::string imgP);
	void actionCollision();
	void tickAction();
	~PlayerSprite();
private: 
	PlayerSprite(GameEngine* eng, int x, int y, int w, int h, int pathX, int pathY, std::string imgP);
};

#endif