#include <SDL.h>
#undef main
#include <stdexcept> 
#include <iostream>
#include <SDL_image.h>
#include "GameEngine.h"
#include "FixedSprite.h"
#include "ActiveSprite.h"
#include "TextSprite.h"
using namespace std;
using namespace gengine;

ActiveSprite* as1;

void bitchtits1() {

	as1->setYpath(-1);

}
void bitchtits11() {

	as1->setYpath(0);

}


void bitchtits2() {

	as1->setYpath(1);

}

void bitchtits22() {

	as1->setYpath(0);

}

void bitchtits3() {

	as1->setXpath(-1);

}

void bitchtits33() {
	as1->setXpath(0);
}

void bitchtits4() {
	as1->setXpath(1);

}

void bitchtits44() {
	as1->setXpath(0);

}

int main(int argc, char* argv[]) {

	try {
		GameEngine* ge = new GameEngine("Hej", 200, 200, 600, 1000, 60);
		as1 = ActiveSprite::getInstance(ge, 100, 100, 200, 200, 0, 0, "A:/Bilder/gubbe.bmp");
		ActiveSprite* baller = ActiveSprite::getInstance(ge, 400, 400, 200, 300, -1, 0, "A:/Bilder/gubbe.bmp");

		SDL_Color textColor = { 150, 133, 255, 255};
		TTF_Font *gFont = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 24);

		TextSprite* text = TextSprite::getInstance(ge, 300, 300, 200, 300, textColor, gFont, "Det brinner");

	
		ge->trackKey(SDL_KEYDOWN, SDLK_UP, bitchtits1);
		ge->trackKey(SDL_KEYUP, SDLK_UP, bitchtits11);
		ge->trackKey(SDL_KEYDOWN, SDLK_DOWN, bitchtits2);
		ge->trackKey(SDL_KEYUP, SDLK_DOWN, bitchtits22);
		ge->trackKey(SDL_KEYDOWN, SDLK_LEFT, bitchtits3);
		ge->trackKey(SDL_KEYUP, SDLK_LEFT, bitchtits33);
		ge->trackKey(SDL_KEYDOWN, SDLK_RIGHT, bitchtits4);
		ge->trackKey(SDL_KEYUP, SDLK_RIGHT, bitchtits44);

		baller->initSpriteSheet(4);
		baller->addSpriteClip(0, 0, 0, 64, 205);
		baller->addSpriteClip(1, 64, 0, 64, 205);
		baller->addSpriteClip(2, 128, 0, 64, 205);
		baller->addSpriteClip(3, 196, 0, 64, 205);



		ge->run();
		delete baller;
		//delete fs1;
		//delete as1;
		delete ge;


	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
	}

	return 0;
}