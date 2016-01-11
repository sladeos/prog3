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
void loadFirstLevel();
void lostGame();


void moveLeft() {
	player->setX(player->getX()-2);
}

void moveRight() {
	player->setX(player->getX()+2);
}

void shoot() {
	LaserSprite *laser = LaserSprite::getInstance(ge, player->getX() + 50, 550, 5, 20, 0, -15, "images/laser.png");
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
		TTF_Font *gFont = TTF_OpenFont("fonts/arial.ttf", 800);
		SDL_Color textColor = { 67, 232, 108, 255 };
		Level *finishLevel = Level::getInstance(ge, "images/finishLevel.png");
		TextSprite *endText = TextSprite::getInstance(ge, 150, 400, 300, 50, textColor, gFont, "Press n to Start a New Game", false, true);
		finishLevel->addSprite(endText);
		ge->loadLevel(finishLevel);
		ge->unsetAllTrackEvent();
		ge->unsetTrackKeyState(SDL_SCANCODE_SPACE);
		ge->trackKey(SDL_KEYDOWN, SDLK_n, loadFirstLevel);
	}

}

void lostGame() {
	TTF_Font *gFont = TTF_OpenFont("fonts/arial.ttf", 800);
	SDL_Color textColor = { 67, 232, 108, 255 };
	Level *gameOver = Level::getInstance(ge, "images/gameOver.png");
	TextSprite *endText = TextSprite::getInstance(ge, 150, 400, 300, 50, textColor, gFont, "Press n to Start a New Game", false, true);
	gameOver->addSprite(endText);
	ge->loadLevel(gameOver);
	ge->unsetAllTrackEvent();
	ge->unsetAllTrackKeyState();
	ge->trackKey(SDL_KEYDOWN, SDLK_n, loadFirstLevel);
}

void loadFirstLevel() {
	ge->unsetTrackKey(SDL_KEYDOWN, SDLK_SPACE);
	firstLevel = Level::getInstance(ge, "images/background.jpg");
	//10 mellanrum, 30x30 storlek
	int xStart = 30;
	int y = 30;
	for (int x = 0; x <= 6; x++) {
		EnemySprite *enemy = EnemySprite::getInstance(ge, xStart, y, 30, 30, 1, 0, "images/invaders.png");
		enemy->setActionFunction(lostGame);
		enemy->initSpriteSheet(32);
		for (int i = 15; i >= 0; --i) {

		enemy->addSpriteClip(i, 40, 30, 64, 64);
		}
		for (int i = 31; i >= 16; --i) {
			enemy->addSpriteClip(i, 142, 31, 64, 64);
		}

		firstLevel->addSprite(enemy);
		xStart += 40;
	}
	
	player = PlayerSprite::getInstance(ge, 300, 600, 100, 50, 0, 0, "images/invaders.png");
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
		TTF_Font *gFont = TTF_OpenFont("fonts/arial.ttf", 800);
		SDL_Color textColor = { 67, 232, 108, 255 };
		ge = new GameEngine("Space Invaders", 200, 200, 600, 700, 120);
		Level *startScreen = Level::getInstance(ge, "images/background.jpg");
		
		TextSprite *startText = TextSprite::getInstance(ge, 150, 400, 300, 50, textColor, gFont, "Press SpaceBar To Start", false, true);

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


