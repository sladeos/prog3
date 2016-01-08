#ifndef LASERPRITE_H
#define LASERSPRITE_H


#include "ActiveSprite.h"
namespace gengine {
	class LaserSprite :public ActiveSprite
	{

	public:
		static LaserSprite* getInstance(GameEngine* eng, int x, int y, int w, int h, int pathX, int pathY, std::string imgP);
		void actionCollision(Sprite *s);
		void tickAction();
		~LaserSprite();
	private:
		LaserSprite(GameEngine* eng, int x, int y, int w, int h, int pathX, int pathY, std::string imgP);
		static int instances;
	};
}
#endif