#include "graphicshandler.h"
#include <array>
#include <SDL2/SDL.h>

int SCREEN_WIDTH = 1000;
int SCREEN_HEIGHT = 999;

Graphicshandler::Graphicshandler() {
	//Initialize all SDL subsystems
	SDL_Init(SDL_INIT_EVERYTHING);

	//Set up the window
	window = SDL_CreateWindow("Chess:)", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
														SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


	boardTexture = loadImage("assets/chessboard.bmp");
	wpawnTexture = loadImage("assets/wpawn.bmp");
	wknightTexture = loadImage("assets/wknight.bmp");
	wbishopTexture = loadImage("assets/wbishop.bmp");
	wrookTexture = loadImage("assets/wrook.bmp");
	wqueenTexture = loadImage("assets/wqueen.bmp");
	wkingTexture = loadImage("assets/wking.bmp");
	bpawnTexture = loadImage("assets/bpawn.bmp");
	bknightTexture = loadImage("assets/bknight.bmp");
	bbishopTexture = loadImage("assets/bbishop.bmp");
	brookTexture = loadImage("assets/brook.bmp");
	bqueenTexture = loadImage("assets/bqueen.bmp");
	bkingTexture = loadImage("assets/bking.bmp");
}

void Graphicshandler::update(const std::array<std::array<char, 8>, 8>& board) {
	// Render background board
	SDL_RenderCopy(renderer, boardTexture, NULL, NULL);

	for (int y = 0; y != 8; y++) {
		for (int x = 0; x != 8; x++) {
			SDL_Rect dest = {.x = x*101 + 91, .y = y*101 + 91, .w = 107, .h = 107};
			switch (board[y][x]) {
			case 'P': SDL_RenderCopy(renderer, bpawnTexture, NULL, &dest); break;
			case 'p': SDL_RenderCopy(renderer, wpawnTexture, NULL, &dest); break;
			case 'N': SDL_RenderCopy(renderer, bknightTexture, NULL, &dest); break;
			case 'n': SDL_RenderCopy(renderer, wknightTexture, NULL, &dest); break;
			case 'B': SDL_RenderCopy(renderer, bbishopTexture, NULL, &dest); break;
			case 'b': SDL_RenderCopy(renderer, wbishopTexture, NULL, &dest); break;
			case 'R': SDL_RenderCopy(renderer, brookTexture, NULL, &dest); break;
			case 'r': SDL_RenderCopy(renderer, wrookTexture, NULL, &dest); break;
			case 'Q': SDL_RenderCopy(renderer, bqueenTexture, NULL, &dest); break;
			case 'q': SDL_RenderCopy(renderer, wqueenTexture, NULL, &dest); break;
			case 'K': SDL_RenderCopy(renderer, bkingTexture, NULL, &dest); break;
			case 'k': SDL_RenderCopy(renderer, wkingTexture, NULL, &dest); break;
			default: break;
			}
		}
	}
	SDL_RenderPresent(renderer);
}

SDL_Texture* Graphicshandler::loadImage(const char* filename) {
	SDL_Surface* loadingSurface;
	loadingSurface = SDL_LoadBMP(filename);
	auto out = SDL_CreateTextureFromSurface(renderer, loadingSurface);
	SDL_FreeSurface(loadingSurface);
	return out;
}

void Graphicshandler::close() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(boardTexture);
	SDL_DestroyTexture(wpawnTexture);
	SDL_DestroyTexture(wknightTexture);
	SDL_DestroyTexture(wbishopTexture);
	SDL_DestroyTexture(wrookTexture);
	SDL_DestroyTexture(wqueenTexture);
	SDL_DestroyTexture(wkingTexture);
	SDL_DestroyTexture(bpawnTexture);
	SDL_DestroyTexture(bknightTexture);
	SDL_DestroyTexture(bbishopTexture);
	SDL_DestroyTexture(brookTexture);
	SDL_DestroyTexture(bqueenTexture);
	SDL_DestroyTexture(bkingTexture);
	//Quit SDL subsystems
	SDL_Quit();
}

Graphicshandler::~Graphicshandler() {
	close();
}
