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

void bitchtits1(SDL_Event eve) {
	as1->setXpath(5);
}




int main(int argc, char* argv[]) {

	try {
		GameEngine* ge = new GameEngine("Hej", 200, 200, 600, 1000, 60);


		as1 = ActiveSprite::getInstance(ge, 100, 100, 200, 200, 0, 0, "C:/images/gubbe.bmp");
		ActiveSprite* baller = ActiveSprite::getInstance(ge, 400, 400, 200, 300, -1, 0, "C:/images/bg.bmp");
		//as1 = ActiveSprite::getInstance(ge, 100, 100, 200, 200, 0, 0, "C:/Users/slade/Pictures/wut/1406247020421.jpg");
		//ActiveSprite* baller = ActiveSprite::getInstance(ge, 400, 400, 200, 300, -1, 0, "C:/Users/slade/Pictures/wut/84081257.jpg");

		/*
		as1 = ActiveSprite::getInstance(ge, 100, 100, 200, 200, 0, 0, "Sladenånting");
		ActiveSprite* baller = ActiveSprite::getInstance(ge, 400, 400, 200, 300, -1, 0, "A:/Bilder/gubbe.bmp");

		as1 = ActiveSprite::getInstance(ge, 100, 100, 200, 200, 0, 0, "Sebbenånting");
		ActiveSprite* baller = ActiveSprite::getInstance(ge, 400, 400, 200, 300, -1, 0, "A:/Bilder/gubbe.bmp");
		*/




		SDL_Color textColor = { 150, 133, 255, 255};
		TTF_Font *gFont = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 24);

		TextSprite* text = TextSprite::getInstance(ge, 300, 300, 200, 300, textColor, gFont, "D", true);


		//ge->setMemberFunc(&ActiveSprite::getH);
		ge->trackKey(SDL_KEYUP, SDLK_UP, bitchtits1);
		ge->trackKey(SDL_KEYDOWN, SDLK_DOWN, bitchtits1);
		
		/*
		ge->trackKey(SDL_KEYUP, SDLK_DOWN, bitchtits22);
		ge->trackKey(SDL_KEYDOWN, SDLK_LEFT, bitchtits3);
		ge->trackKey(SDL_MOUSEMOTION, false, bitchtits1);
		ge->trackKey(SDL_KEYUP, SDLK_LEFT, bitchtits33);
		ge->trackKey(SDL_KEYDOWN, SDLK_RIGHT, bitchtits4);
		ge->trackKey(SDL_KEYUP, SDLK_RIGHT, bitchtits44);
		*/

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