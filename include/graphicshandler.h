#ifndef GRAPHICS_GUARD
#define GRAPHICS_GUARD

#include <SDL2/SDL.h>
#include <array>
#include <string>

struct Graphicshandler {
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* boardTexture;
	SDL_Texture* wpawnTexture;
	SDL_Texture* wknightTexture;
	SDL_Texture* wbishopTexture;
	SDL_Texture* wrookTexture;
	SDL_Texture* wqueenTexture;
	SDL_Texture* wkingTexture;
	SDL_Texture* bpawnTexture;
	SDL_Texture* bknightTexture;
	SDL_Texture* bbishopTexture;
	SDL_Texture* brookTexture;
	SDL_Texture* bqueenTexture;
	SDL_Texture* bkingTexture;

	Graphicshandler();
	~Graphicshandler();

	SDL_Texture *loadImage(const char*);
  void update(const std::array<std::array<char, 8>, 8>&);
	void close();
};

#endif
