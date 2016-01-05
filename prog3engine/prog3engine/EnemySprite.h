#ifndef ENEMYSPRITE_H
#define ENEMYSPRITE_H


#include "ActiveSprite.h"
using namespace gengine;
class EnemySprite :	public ActiveSprite
{

public:
	static EnemySprite* getInstance(GameEngine* eng, int x, int y, int w, int h, int pathX, int pathY, std::string imgP);
	void actionCollision();
	void tickAction();
	~EnemySprite();
private:
	EnemySprite(GameEngine* eng, int x, int y, int w, int h, int pathX, int pathY, std::string imgP);
};

#endif