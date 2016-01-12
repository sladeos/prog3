/* 
* This is the application of the Game Engine, it utilizes the tools that the Game Engine provides to build a simple version of Space Invaders. 
*/

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

//Functions for moving player sprite
void moveLeft() {
	player->setX(player->getX()-2);
}

void moveRight() {
	player->setX(player->getX()+2);
}

//Function to shoot, is limited to shot at a time in the class LaserSprite
void shoot() {
	LaserSprite *laser = LaserSprite::getInstance(ge, player->getX() + 50, 550, 5, 20, 0, -15, "images/laser.png");
	if(laser != nullptr){
	ge->add(laser);
	}
}

//This function will check the amount of enemies, if they equal zero the winning screen will be loaded
void endOfLevelOne() {
	//Get the sprite vector from GameEngine
	vector<Sprite*> sprites = ge->getSprites();
	int enemyCount = 0;
	//Count the EnemySprites only
	for (Sprite* s : sprites) {
		if (EnemySprite* enemy = dynamic_cast<EnemySprite*>(s)) {
			++enemyCount;
		}
	}
	//If they equal zero
	if (enemyCount == 0) {
		//Load font, textcolor and create a level + text. 
		TTF_Font *gFont = TTF_OpenFont("fonts/arial.ttf", 800);
		SDL_Color textColor = { 67, 232, 108, 255 };
		Level *finishLevel = Level::getInstance(ge, "images/finishLevel.png");
		TextSprite *endText = TextSprite::getInstance(ge, 150, 400, 300, 50, textColor, gFont, "Press n to Start a New Game", false, true);
		//Add the text to the level
		finishLevel->addSprite(endText);
		//Load level and untrack keys
		ge->loadLevel(finishLevel);
		ge->unsetAllTrackEvent();
		ge->unsetTrackKeyState(SDL_SCANCODE_SPACE);
		//Track restart first level
		ge->trackKey(SDL_KEYDOWN, SDLK_n, loadFirstLevel);
	}

}

//This function loads the Game Over screen, its triggered by an enemy touching the player
void lostGame() {
	//Load font, textcolor and create a level + text. 
	TTF_Font *gFont = TTF_OpenFont("fonts/arial.ttf", 800);
	SDL_Color textColor = { 67, 232, 108, 255 };
	Level *gameOver = Level::getInstance(ge, "images/gameOver.png");
	TextSprite *endText = TextSprite::getInstance(ge, 150, 400, 300, 50, textColor, gFont, "Press n to Start a New Game", false, true);
	//Add the text to the level
	gameOver->addSprite(endText);
	//Load level and untrack keys
	ge->loadLevel(gameOver);
	ge->unsetAllTrackEvent();
	ge->unsetAllTrackKeyState();
	//Track restart first level
	ge->trackKey(SDL_KEYDOWN, SDLK_n, loadFirstLevel);
}

//This function loads the first level along with the enemies and player. It also tracks the keys to moving functions
void loadFirstLevel() {
	//Removes the tracking of loading this level
	ge->unsetTrackKey(SDL_KEYDOWN, SDLK_SPACE);
	firstLevel = Level::getInstance(ge, "images/background.jpg");

	int xStart = 30;
	int y = 30;
	//Loop that initates the enemies and their spriteclips for animation
	for (int x = 0; x <= 6; x++) {
		//Creates the enemysprite and adds an actionFunction (lostGame which is the gameover "level"), actionFunction is triggered if enemy collides with the player
		EnemySprite *enemy = EnemySprite::getInstance(ge, xStart, y, 30, 30, 1, 0, "images/invaders.png");
		enemy->setActionFunction(lostGame);

		//Initiate spritesheet with 32 clips (This is because of the high framerate) If only 2 clips would be used, the sprites would animate very quickly
		enemy->initSpriteSheet(32);

		//Adding the spriteclips.
		for (int i = 15; i >= 0; --i) {
			enemy->addSpriteClip(i, 40, 30, 64, 64);
		}
		for (int i = 31; i >= 16; --i) {
			enemy->addSpriteClip(i, 142, 31, 64, 64);
		}
		
		//Add this instance of enemy to the level
		firstLevel->addSprite(enemy);
		//Increase the distance between the enemies on the x dimension
		xStart += 40;
	}

	//This creates a player with spritesheet
	player = PlayerSprite::getInstance(ge, 300, 600, 100, 50, 0, 0, "images/invaders.png");
	player->initSpriteSheet(1);
	player->addSpriteClip(0, 30, 338, 192, 84);
	
	//Add the player to the level and load the level
	firstLevel->addSprite(player);	
	ge->loadLevel(firstLevel);
	
	//Start tracking the player actions
	ge->trackKeyState(SDL_SCANCODE_LEFT, moveLeft);
	ge->trackKeyState(SDL_SCANCODE_RIGHT, moveRight);
	ge->trackKeyState(SDL_SCANCODE_SPACE, shoot);

	//Track the event that triggers the win.
	ge->trackEvent(endOfLevelOne);
}


//This will be run when the game is started, it sets a start screen to launch the game and tracks Space to load first level.
int main(int argc, char* argv[]) {
	try {
		//Loads a font, textcolor and creates a new instance of level
		TTF_Font *gFont = TTF_OpenFont("fonts/arial.ttf", 800);
		SDL_Color textColor = { 67, 232, 108, 255 };
		ge = new GameEngine("Space Invaders", 200, 200, 600, 700, 120);
		Level *startScreen = Level::getInstance(ge, "images/background.jpg");
		
		//Creates the text with the font and color we loaded
		TextSprite *startText = TextSprite::getInstance(ge, 150, 400, 300, 50, textColor, gFont, "Press SpaceBar To Start", false, true);

		//Adds the text to the level and then loads it, space is then tracked to loading the first level of the game. 
		startScreen->addSprite(startText);
		ge->loadLevel(startScreen);
		ge->trackKey(SDL_KEYDOWN, SDLK_SPACE, loadFirstLevel);

		
		//Starts the game loop
		ge->run();
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
	}
	return 0;
}


