#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <sstream>
#include "tinyxml2.h"
#include <stdlib.h>
#include <time.h>
#include <string>


using namespace std;
using namespace tinyxml2;


class Survival {
public:

	Survival(); // constructor
	~Survival(); // destructor
	// menus
	int MainMenu(SDL_Renderer *ren, TTF_Font *font);
	int PauseMenu(SDL_Renderer *ren, TTF_Font *font);
	int ClearMenu(SDL_Renderer *ren, TTF_Font *font, string s);
	int WeaponsMenu(SDL_Renderer *ren, TTF_Font *font);
	int HowToPlay(SDL_Renderer *ren, TTF_Font *font);
	int EndMenu(SDL_Renderer *ren, TTF_Font *font, string hs);
	// start game
	void StartGame();
};

// load textures
SDL_Texture *loadTexture(SDL_Renderer *ren, char *name);

