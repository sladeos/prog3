#include <SDL.h>
#include <stdexcept> 
#include <iostream>
#include <SDL_image.h>
#include "GameEngine.h"
#include "FixedSprite.h"
#include "ActiveSprite.h"
using namespace std;
using namespace gengine;

int main(int argc, char* argv[]) {

	try {
		GameEngine* ge = new GameEngine("Hej", 200, 200, 600, 1000, 5);
		//FixedSprite* fs1 = FixedSprite::getInstance(ge, 100, 100, 300, 300, "C:/Users/slade/Pictures/Wut/1397288854346.png");
		//ActiveSprite* as1 = ActiveSprite::getInstance(ge, 300, 300, 200, 200, 1,1, "C:/Users/slade/Pictures/Wut/1397288854346.png");
		ActiveSprite* baller = ActiveSprite::getInstance(ge, 300, 300, 200, 300, 0, 0, "C:/Users/slade/Desktop/foo.png");
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