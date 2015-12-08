#include <SDL.h>
#undef main
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <sstream>
using namespace std;

const int WIDTH = 600, HEIGHT = 400;

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	SDL_Window* win = SDL_CreateWindow("1st", 100, 100, WIDTH, HEIGHT, 0);
	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_PRESENTVSYNC);
	TTF_Font* f = TTF_OpenFont("c:/windows/fonts/arial.ttf", 36);
	SDL_Color textColor = { 0xFF,0xFF,0xFF };
	SDL_Surface* rubrSurf = TTF_RenderText_Solid(f, "Varv:", textColor);
	SDL_Texture* rubrText = SDL_CreateTextureFromSurface(ren, rubrSurf);
	SDL_Rect rubrRect = { WIDTH - 200, HEIGHT - 100, rubrSurf->w, rubrSurf->h };
	SDL_FreeSurface(rubrSurf);

	SDL_Surface* bild = SDL_LoadBMP("A:/Bilder/gubbe.bmp");
	int x = 0, y = 0;
	int w = bild->w;
	int h = bild->h;
	Uint32 white = SDL_MapRGB(bild->format, 255, 255, 255);
	SDL_SetColorKey(bild, SDL_RLEACCEL, white);
	SDL_Texture* tx = SDL_CreateTextureFromSurface(ren, bild);
	SDL_FreeSurface(bild);

	cout << SDL_GetBasePath() << endl;

	SDL_Texture* tx2 = IMG_LoadTexture(ren, "A:/Bilder/ebbug.png");

	SDL_Surface* bg = SDL_LoadBMP("A:/Bilder/bg.bmp");
	SDL_Texture* bgtx = SDL_CreateTextureFromSurface(ren, bg);
	SDL_FreeSurface(bg);

	const int TIDPERVARV = 50;
	int dx = 1;
	bool goOn = true;
	bool moving = false;
	int varv = 0;
	SDL_Texture* varvText = nullptr;
	SDL_Rect varvRect = { WIDTH - 100, HEIGHT - 100, 0, 0 };

	while (goOn) {
		Uint32 nextVarv = SDL_GetTicks() + TIDPERVARV;
		SDL_Event eve;
		while (SDL_PollEvent(&eve)) {
			switch (eve.type) {
			case SDL_QUIT:
				goOn = false; break;
			case SDL_KEYDOWN:
				if (eve.key.keysym.sym == SDLK_END)
					goOn = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (eve.button.x >= x && eve.button.x <= x + w && eve.button.y >= y &&
					eve.button.y <= y + h && eve.button.button == SDL_BUTTON_LEFT)
					moving = true;
				break;
			case SDL_MOUSEMOTION:
				if (moving) {
					x += eve.motion.xrel;
					y += eve.motion.yrel;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				moving = false;
				break;
			} // switch
		} // inre
		if (x < 0 || x >= WIDTH - w)
			dx = -dx;
		x += dx;

		if (varv % 10 == 0) {
			ostringstream oss;
			oss << varv;
			string varvStr = oss.str();
			// Ovanstående tre rader kan i C++11 göras enklare som: 
			// string varvStr = to_string(varv);
			SDL_Surface* varvSurf = TTF_RenderText_Solid(f, varvStr.c_str(), textColor);
			if (varvText != nullptr)
				SDL_DestroyTexture(varvText);
			varvText = SDL_CreateTextureFromSurface(ren, varvSurf);
			varvRect.w = varvSurf->w;
			varvRect.h = varvSurf->h;
			SDL_FreeSurface(varvSurf);
		}

		varv++;

		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, bgtx, NULL, NULL);
		SDL_Rect dest = { x,y,w,h };
		if (dx == 1)
			SDL_RenderCopy(ren, tx2, NULL, &dest);
		else
			SDL_RenderCopy(ren, tx, NULL, &dest);

		SDL_RenderCopy(ren, rubrText, NULL, &rubrRect);
		SDL_RenderCopy(ren, varvText, NULL, &varvRect);

		SDL_RenderPresent(ren);

		if (!SDL_TICKS_PASSED(SDL_GetTicks(), nextVarv))
			SDL_Delay(nextVarv - SDL_GetTicks());
	} // yttre
	if (varvText != nullptr)
		SDL_DestroyTexture(varvText);
	SDL_DestroyTexture(rubrText);
	SDL_DestroyTexture(tx2);
	SDL_DestroyTexture(tx);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	TTF_Quit();
	SDL_Quit();
	return 0;
}