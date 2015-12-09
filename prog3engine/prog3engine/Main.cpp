#include <SDL.h>
#include <stdexcept> 
#undef main
#include <iostream>
#include <SDL_image.h>
#include "GameEngine.h"
#include "Sprite.h"
#include "FixedSprite.h"
using namespace std;
using namespace gengine;

int main(int argc, char* argv[]) {

	try {

		GameEngine* ge = new GameEngine("Hej", 200, 200, 500, 300);
		FixedSprite* fs1 = FixedSprite::getInstance(ge, 100, 100, 300, 300, "A:/Bilder/ridbildWP_20150829_18_35_49_Pro.jpg");

		ge->run();

		delete fs1;
		delete ge;


	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
	}
	
	return 0;
}