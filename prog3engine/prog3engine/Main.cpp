#include <iostream>
#include <string>
#include <SDL.h>
#undef main
#include <SDL_image.h>


using namespace std;
string path = "a:/bilder/uppknapp.png";

int main(int argc, char* argv[]) {

	SDL_Init(SDL_INIT_EVERYTHING);
	
	if (SDL_Init(SDL_INIT_VIDEO) == -1) {
		cerr << "SDL_Init-fel: " << SDL_GetError() << endl;
		exit(-1);
	}
	SDL_Window* win = SDL_CreateWindow("Mitt",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		600, 500, SDL_WINDOW_SHOWN);
	if (win == nullptr) {
		cerr << "Fel: " <<SDL_GetError() <<endl;
			SDL_Quit();
		exit(-1);
	}
	SDL_Renderer* ren = SDL_CreateRenderer(win, -1,
		SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr) {
		cerr << "Fel: " << SDL_GetError() << endl;
			SDL_DestroyWindow(win);
		SDL_Quit();
		exit(-1);
	}

	SDL_Surface* bild = SDL_LoadBMP(path.c_str());
	SDL_Texture* tx = SDL_CreateTextureFromSurface(ren, bild);
	SDL_FreeSurface(bild);
	bool runOn = true;
	while (runOn) {
		SDL_Event eve;
		while (SDL_PollEvent(&eve)) {
			switch (eve.type) {
			case SDL_QUIT: runOn = false; break;
			case SDL_KEYDOWN:
				if (eve.key.keysym.sym == SDLK_END)
					runOn = true;
				break;
			} // switch
		} // inre while
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, tx, NULL, NULL);
		SDL_RenderPresent(ren);
	} // yttre while
	SDL_DestroyTexture(tx);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();

	return 0;
}