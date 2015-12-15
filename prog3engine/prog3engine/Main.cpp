#include <SDL.h>
#undef main
#include <stdexcept> 
#include <iostream>
#include <SDL_image.h>
#include "GameEngine.h"
#include "FixedSprite.h"
#include "ActiveSprite.h"
using namespace std;
using namespace gengine;

ActiveSprite* as1;

void bitchtits1() {
	
	as1->setY(as1->getY() + 5);
	
}

void bitchtits2() {
	
	as1->setY(as1->getY() - 5);
}

void bitchtits3() {

	as1->setX(as1->getX() - 5);
}

void bitchtits4() {
	
	as1->setX(as1->getX() + 5);
}

int main(int argc, char* argv[]) {

	try {
		GameEngine* ge = new GameEngine("Hej", 200, 200, 600, 1000, 60);
		as1 = ActiveSprite::getInstance(ge, 100, 100, 200, 200, 0, 0, "C:/Users/Sebbe/Pictures/dump/test.jpg");
		ActiveSprite* baller = ActiveSprite::getInstance(ge, 400, 400, 200, 300, -5, 0, "C:/Users/Sebbe/Pictures/dump/wtf-44.jpg");
	
		ge->trackKeyState(SDL_SCANCODE_DOWN, bitchtits1);
		ge->trackKeyState(SDL_SCANCODE_UP, bitchtits2);
		ge->trackKeyState(SDL_SCANCODE_LEFT, bitchtits3);
		ge->trackKeyState(SDL_SCANCODE_RIGHT, bitchtits4);

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