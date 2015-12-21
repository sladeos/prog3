#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include "Sprite.h"
#include "FixedSprite.h"
namespace gengine {
	class Level
	{
	public:
		static Level* getInstance(GameEngine* eng, std::string background);
		void addSprite(Sprite*);
		void addSprites(std::vector<Sprite*>);
		void removeSprite(Sprite*);
		void setBackground(FixedSprite*);
		
		std::vector<Sprite*> getSprites() const;
		~Level();
	private:
		Level(GameEngine* eng,  std::string background);
		std::vector<Sprite*> sprites;
		FixedSprite *background;
		void deleteObjects();
	};
}
#endif

