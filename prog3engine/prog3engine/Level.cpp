#include "Level.h"
#include "GameEngine.h"
#include <algorithm>

namespace gengine {
	Level * gengine::Level::getInstance(GameEngine * eng, std::string imgPath)
	{
		return new Level(eng, imgPath);
	}

	Level::Level(GameEngine *eng, std::string imgPath)
	{
		background = FixedSprite::getInstance(eng, 0, 0, eng->getW(), eng->getH(), imgPath);
		sprites.push_back(background);
	}

	void gengine::Level::addSprite(Sprite *sprite)
	{
		sprites.push_back(sprite);
	}


	//Kan bli fel. What is 
	void gengine::Level::addSprites(std::vector<Sprite*> spritesToLoad)
	{
		sprites.insert(sprites.end(), spritesToLoad.begin(), spritesToLoad.end());
	}

	void gengine::Level::removeSprite(Sprite *s)
	{
		sprites.erase(std::remove(sprites.begin(), sprites.end(), s), sprites.end());
	}

	void Level::setBackground(FixedSprite *newBackground)
	{
		removeSprite(background);
		background = newBackground;
		sprites.push_back(background);

	}



	std::vector<Sprite*> Level::getSprites() const
	{
		return sprites;
	}

	void Level::deleteObjects()
	{
		for (Sprite* s : sprites) {
			delete s;
		}
		sprites.clear();
	}

	Level::~Level()
	{
		delete background;
		deleteObjects();
	}
}