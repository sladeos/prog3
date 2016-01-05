
#include <SDL.h>
#include <stdexcept> 
#include <iostream>
#include <SDL_image.h>
#include "GameEngine.h"
#include "FixedSprite.h"
#include "ActiveSprite.h"
#include "TextSprite.h"
#include "Level.h"
#include <vector>
#include "EnemySprite.h"
using namespace std;
using namespace gengine;

GameEngine* ge;
Level *firstLevel;

void loadFirstLevel() {
	firstLevel = Level::getInstance(ge, "C:/images/background.jpg");
	//10 mellanrum, 30x30 storlek
	int xStart = 5;
	int y = 30;
	for (int x = 0; x <= 6; x++) {
		EnemySprite *enemy = EnemySprite::getInstance(ge, xStart, y, 30, 30, 15, 0, "c:/images/enemySpriteSheet.png");
		firstLevel->addSprite(enemy);
		xStart += 40;
		
	}
	ge->loadLevel(firstLevel);

}

int main(int argc, char* argv[]) {
	try {
		ge = new GameEngine("Space Invaders", 200, 200, 600, 700, 120);
		Level *startScreen = Level::getInstance(ge, "C:/images/background.jpg");
		TTF_Font *gFont = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 800);
		SDL_Color textColor = { 67, 232, 108, 255 };
		TextSprite *startText = TextSprite::getInstance(ge, 150, 200, 300, 150, textColor, gFont, "Press SpaceBar To Start", false);

		startScreen->addSprite(startText);
		ge->loadLevel(startScreen);
		ge->trackKey(SDL_KEYDOWN, SDLK_SPACE, loadFirstLevel);

		ge->unTrackKey(SDL_KEYDOWN, SDLK_SPACE);

		ge->run();
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
	}
	return 0;
}


