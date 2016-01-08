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
#include "PlayerSprite.h"
#include "LaserSprite.h"

using namespace std;
using namespace gengine;

GameEngine* ge;
Level *firstLevel;
PlayerSprite *player;

void moveLeft() {
	player->setX(player->getX()-2);
}

void moveRight() {
	player->setX(player->getX()+2);
}

void shoot() {
	LaserSprite *laser = LaserSprite::getInstance(ge, player->getX() + 50, 550, 5, 20, 0, -15, "c:/images/laser.png");
	if(laser != nullptr){
	ge->add(laser);
	}
}

void endOfLevelOne() {
	vector<Sprite*> sprites = ge->getSprites();
	int enemyCount = 0;
	for (Sprite* s : sprites) {
		if (EnemySprite* enemy = dynamic_cast<EnemySprite*>(s)) {
			++enemyCount;
		}
	}
	if (enemyCount == 0) {
		Level *finishLevel = Level::getInstance(ge, "C:/images/finishLevel.png");
		ge->loadLevel(finishLevel);
		ge->unsetAllTrackEvent();
	}

}


void loadFirstLevel() {
	ge->unsetTrackKey(SDL_KEYDOWN, SDLK_SPACE);
	firstLevel = Level::getInstance(ge, "C:/images/background.jpg");
	//10 mellanrum, 30x30 storlek
	int xStart = 30;
	int y = 30;
	for (int x = 0; x <= 6; x++) {
		EnemySprite *enemy = EnemySprite::getInstance(ge, xStart, y, 30, 30, 1, 0, "c:/images/invaders.png");
		enemy->initSpriteSheet(4);
		enemy->addSpriteClip(0, 40, 30, 64, 64);
		enemy->addSpriteClip(1, 40, 30, 64, 64);
		enemy->addSpriteClip(2, 142, 31, 64, 64);
		enemy->addSpriteClip(3, 142, 31, 64, 64);
		firstLevel->addSprite(enemy);
		xStart += 40;
	}
	
	player = PlayerSprite::getInstance(ge, 300, 600, 100, 50, 0, 0, "c:/images/invaders.png");
	player->initSpriteSheet(1);
	player->addSpriteClip(0, 30, 338, 192, 84);
	
	firstLevel->addSprite(player);

	
	ge->loadLevel(firstLevel);

	ge->trackKeyState(SDL_SCANCODE_LEFT, moveLeft);
	ge->trackKeyState(SDL_SCANCODE_RIGHT, moveRight);
	ge->trackKeyState(SDL_SCANCODE_SPACE, shoot);
	ge->trackEvent(endOfLevelOne);
}

int main(int argc, char* argv[]) {
	try {
		ge = new GameEngine("Space Invaders", 200, 200, 600, 700, 100);
		Level *startScreen = Level::getInstance(ge, "C:/images/background.jpg");
		TTF_Font *gFont = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 800);
		SDL_Color textColor = { 67, 232, 108, 255 };
		TextSprite *startText = TextSprite::getInstance(ge, 150, 200, 300, 150, textColor, gFont, "Press SpaceBar To Start", false, true);

		startScreen->addSprite(startText);
		ge->loadLevel(startScreen);
		ge->trackKey(SDL_KEYDOWN, SDLK_SPACE, loadFirstLevel);

		

		ge->run();
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
	}
	return 0;
}


