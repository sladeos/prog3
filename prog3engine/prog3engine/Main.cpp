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
	std::cout << "bitchtits1";

}


void leftFunc() {
	int x = as1->getX();
	as1->setX(x - 3);
}

void rightFunc() {
	int x = as1->getX();
	as1->setX(x + 3);
}

void upFunc() {
	int y = as1->getY();
	as1->setY(y - 3);
}

void downFunc() {
	int y = as1->getY();
	as1->setY(y + 3);
}




int main(int argc, char* argv[]) {

	try {
		GameEngine* ge = new GameEngine("Hej", 200, 200, 600, 1000, 60);


		//as1 = ActiveSprite::getInstance(ge, 100, 100, 200, 200, 0, 0, "C:/images/gubbe.bmp");
		//ActiveSprite* baller = ActiveSprite::getInstance(ge, 400, 400, 200, 300, -1, 0, "C:/images/bg.bmp");
		as1 = ActiveSprite::getInstance(ge, 100, 100, 200, 200, 0, 0, "C:/Users/slade/Pictures/wut/1406247020421.jpg");
		ActiveSprite* baller = ActiveSprite::getInstance(ge, 400, 400, 200, 300, -1, 0, "C:/Users/slade/Pictures/wut/84081257.jpg");

		/*
		as1 = ActiveSprite::getInstance(ge, 100, 100, 200, 200, 0, 0, "Sladenånting");
		ActiveSprite* baller = ActiveSprite::getInstance(ge, 400, 400, 200, 300, -1, 0, "A:/Bilder/gubbe.bmp");

		as1 = ActiveSprite::getInstance(ge, 100, 100, 200, 200, 0, 0, "Sebbenånting");
		ActiveSprite* baller = ActiveSprite::getInstance(ge, 400, 400, 200, 300, -1, 0, "A:/Bilder/gubbe.bmp");
		*/




		SDL_Color textColor = { 150, 133, 255, 255 };
		TTF_Font *gFont = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 24);
		TextSprite* text = TextSprite::getInstance(ge, 300, 300, 200, 300, textColor, gFont, "D", true);



		//Free function register
		ge->trackKey(SDL_KEYDOWN, SDLK_F7, bitchtits1);

		//Member Pointer register
		void(ActiveSprite::*mPek)();
		mPek = &ActiveSprite::printShit;
		ge->trackMemberKey(SDL_KEYDOWN, SDLK_UP, as1, mPek);



		ge->trackKeyState(SDL_SCANCODE_LEFT, leftFunc);
		ge->trackKeyState(SDL_SCANCODE_RIGHT, rightFunc);
		ge->trackKeyState(SDL_SCANCODE_UP, upFunc);
		ge->trackKeyState(SDL_SCANCODE_DOWN, downFunc);



		baller->initSpriteSheet(4);
		baller->addSpriteClip(0, 0, 0, 64, 205);
		baller->addSpriteClip(1, 64, 0, 64, 205);
		baller->addSpriteClip(2, 128, 0, 64, 205);
		baller->addSpriteClip(3, 196, 0, 64, 205);



		ge->run();
		delete baller;
		delete as1;
		delete ge;


	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
	}

	return 0;
}