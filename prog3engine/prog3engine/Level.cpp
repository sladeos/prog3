#include "Level.h"
#include "GameEngine.h"
#include <algorithm>

namespace gengine {
	Level * gengine::Level::getInstance(GameEngine * eng, std::string imgPath)
	{
		return new Level(eng, imgPath);
	}

	//Constructor
	Level::Level(GameEngine *eng, std::string imgPath)
	{
		background = FixedSprite::getInstance(eng, 0, 0, eng->getW(), eng->getH(), imgPath, true);
		sprites.push_back(background);
	}

	//Add a sprite to the level
	void gengine::Level::addSprite(Sprite *sprite)
	{
		sprites.push_back(sprite);
	}

	//Add sprites (This function takes a vector) 
	void gengine::Level::addSprites(std::vector<Sprite*> spritesToLoad)
	{
		sprites.insert(sprites.end(), spritesToLoad.begin(), spritesToLoad.end());
	}

	//Removes a sprite from the level
	void gengine::Level::removeSprite(Sprite *s)
	{
		sprites.erase(std::remove(sprites.begin(), sprites.end(), s), sprites.end());
	}

	//Set the background for the level
	void Level::setBackground(FixedSprite *newBackground)
	{
		removeSprite(background);
		background = newBackground;
		sprites.push_back(background);

	}

	//Return the list of sprites that can be loaded with this level
	std::vector<Sprite*> Level::getSprites() const
	{
		
		return sprites;
	}

	//Delete the sprites in this level
	void Level::deleteObjects()
	{
		for (Sprite* s : sprites) {
			delete s;
		}
		sprites.clear();
	}
	//Destructor
	Level::~Level()
	{
		deleteObjects();
		delete background;
	
	}
}