#include "Survival.h"

#define SCREENWIDTH 800
#define SCREENHEIGHT 600
#define DELTA 500 // number to use in order to slow things down 

// method for loading textures
SDL_Texture *loadTexture(SDL_Renderer *ren, char *name) {
	SDL_Surface *image = IMG_Load(name);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, image);
	SDL_FreeSurface(image);
	return texture;
}

Survival::Survival() {

}

Survival::~Survival() {

}

// main menu
int Survival::MainMenu(SDL_Renderer *ren, TTF_Font *font) {
	int x, y; // to hold the mouse's position
	const int NUMMENU = 4; // number of labels on the menu
	const char *labels[NUMMENU] = { "Start", "Choose Your Weapon", "How to Play", "Exit" }; // the labels 
	SDL_Surface *menuSurfaces[NUMMENU]; // create surfaces
	SDL_Texture *menuTextures[NUMMENU]; // create textures
	bool selected[NUMMENU] = { false, false,false,false }; // set bools to check for label selection
	SDL_Color color[2] = { {255,255,255}, {255,0,0} }; // set colors to use when hovering on and off the labels
	SDL_Surface *screen = SDL_CreateRGBSurface(0, SCREENWIDTH, SCREENHEIGHT, 32, 0, 0, 0, 0); // set a black background for the menu

	// set the surfaces and textures
	menuSurfaces[0] = TTF_RenderText_Solid(font, labels[0], color[0]);
	menuSurfaces[1] = TTF_RenderText_Solid(font, labels[1], color[0]);
	menuSurfaces[2] = TTF_RenderText_Solid(font, labels[2], color[0]);
	menuSurfaces[3] = TTF_RenderText_Solid(font, labels[3], color[0]);
	menuTextures[0] = SDL_CreateTextureFromSurface(ren, menuSurfaces[0]);
	menuTextures[1] = SDL_CreateTextureFromSurface(ren, menuSurfaces[1]);
	menuTextures[2] = SDL_CreateTextureFromSurface(ren, menuSurfaces[2]);
	menuTextures[3] = SDL_CreateTextureFromSurface(ren, menuSurfaces[3]);

	// set the positions of the labels
	SDL_Rect pos[NUMMENU];
	pos[0].x = (screen->clip_rect.w / 2) - (menuSurfaces[0]->clip_rect.w / 2);
	pos[0].y = (screen->clip_rect.h / 2) - (menuSurfaces[0]->clip_rect.h) - 100;
	pos[0].w = menuSurfaces[0]->clip_rect.w;
	pos[0].h = menuSurfaces[0]->clip_rect.h;

	pos[1].x = (screen->clip_rect.w / 2) - (menuSurfaces[1]->clip_rect.w / 2);
	pos[1].y = (screen->clip_rect.h / 2) + (menuSurfaces[1]->clip_rect.h) - 100;
	pos[1].w = menuSurfaces[1]->clip_rect.w;
	pos[1].h = menuSurfaces[1]->clip_rect.h;

	pos[2].x = (screen->clip_rect.w / 2) - (menuSurfaces[2]->clip_rect.w / 2);
	pos[2].y = (screen->clip_rect.h / 2) + (2*(menuSurfaces[2]->clip_rect.h)) - 100;
	pos[2].w = menuSurfaces[2]->clip_rect.w;
	pos[2].h = menuSurfaces[2]->clip_rect.h;

	pos[3].x = (screen->clip_rect.w / 2) - (menuSurfaces[3]->clip_rect.w / 2);
	pos[3].y = (screen->clip_rect.h / 2) +(3* (menuSurfaces[3]->clip_rect.h)) - 100;
	pos[3].w = menuSurfaces[3]->clip_rect.w;
	pos[3].h = menuSurfaces[3]->clip_rect.h;

	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00)); // fill the black screen

	SDL_Event event;

	// event handling
	while (true)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT: // free memory and quit if the player closes the window
				{
					for (int i = 0; i < NUMMENU; i++)
					{
						SDL_FreeSurface(menuSurfaces[i]);
						SDL_DestroyTexture(menuTextures[i]);
						return 3;
					}
				}

				case SDL_MOUSEMOTION: // change the color of the labels when the user hovers
				{
					x = event.motion.x;
					y = event.motion.y;

					for (int i = 0; i < NUMMENU; i++)
					{
						if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h)
						{
							if (!selected[i])
							{
								selected[i] = true;
								SDL_FreeSurface(menuSurfaces[i]);
								SDL_DestroyTexture(menuTextures[i]);
								menuSurfaces[i] = TTF_RenderText_Solid(font, labels[i], color[1]);
								menuTextures[i] = SDL_CreateTextureFromSurface(ren, menuSurfaces[i]);
							}
						}

						else
						{
							if (selected[i])
							{
								selected[i] = false;
								SDL_FreeSurface(menuSurfaces[i]);
								SDL_DestroyTexture(menuTextures[i]);
								menuSurfaces[i] = TTF_RenderText_Solid(font, labels[i], color[0]);
								menuTextures[i] = SDL_CreateTextureFromSurface(ren, menuSurfaces[i]);
							}
						}
					}
					break;
				}

				case SDL_MOUSEBUTTONDOWN: // free memory and return the approriate int depending on what the user presses
				{

					x = event.motion.x;
					y = event.motion.y;

					for (int i = 0; i < NUMMENU; i++)
					{
						if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h)
						{
							for (int j = 0; j < NUMMENU; j++)
							{
								SDL_FreeSurface(menuSurfaces[j]);
								SDL_DestroyTexture(menuTextures[j]);
							}
							return i;
						}


					}
					break;
				}



			}
		}

		SDL_RenderClear(ren);

		for (int i = 0; i < NUMMENU; i++)
		{
			SDL_RenderCopy(ren, menuTextures[i], NULL, &pos[i]);
		}

		SDL_RenderPresent(ren);
	}



}

// similar to other menus
int Survival::HowToPlay(SDL_Renderer *ren, TTF_Font *font) {

	int x, y;
	const int NUMMENU = 8;
	const char *labels[NUMMENU] = { "Welcome to Survival! Choose your weapon and fight off the zombie hordes!", "Every level, Zombies spawn and attack you. Press the left mouse button to shoot them", "the big ones take three hits to kill instead of one, but be careful, you die in one hit!", "The number of zombies increases every level to a maximum of 100 zombies at level 10.", "small zombies award you with 5 points and big ones award 10 points.","Check your highscore at the end of the survival!", "press Esc during the game to pause. Good luck Surviving!", "Back"};
	SDL_Surface *menuSurfaces[NUMMENU];
	SDL_Texture *menuTextures[NUMMENU];
	bool selected = false;
	SDL_Color color[2] = { { 255,255,255 },{ 255,0,0 } };
	SDL_Surface *screen = SDL_CreateRGBSurface(0, SCREENWIDTH, SCREENHEIGHT, 32, 0, 0, 0, 0);

	for (int i = 0; i < NUMMENU; i++)
	{
		menuSurfaces[i] = TTF_RenderText_Solid(font, labels[i], color[0]);
		menuTextures[i] = SDL_CreateTextureFromSurface(ren, menuSurfaces[i]);
	}



	SDL_Rect pos[NUMMENU];

	pos[0].x = (screen->clip_rect.w / 2) - (menuSurfaces[0]->clip_rect.w / 2);
	pos[0].y = (screen->clip_rect.h / 2) - (menuSurfaces[0]->clip_rect.h) - 100;
	pos[0].w = menuSurfaces[0]->clip_rect.w;
	pos[0].h = menuSurfaces[0]->clip_rect.h;

	for (int i = 1; i < (NUMMENU - 1) ; i++)
	{
		pos[i].x = (screen->clip_rect.w / 2) - (menuSurfaces[i]->clip_rect.w / 2);
		pos[i].y = (screen->clip_rect.h / 2) + (i * (menuSurfaces[i]->clip_rect.h)) - 100;
		pos[i].w = menuSurfaces[i]->clip_rect.w;
		pos[i].h = menuSurfaces[i]->clip_rect.h;
	}

	pos[7].x = (screen->clip_rect.w / 2) - (menuSurfaces[7]->clip_rect.w / 2);
	pos[7].y = (screen->clip_rect.h / 2) + (8 * (menuSurfaces[7]->clip_rect.h)) - 100;
	pos[7].w = menuSurfaces[7]->clip_rect.w;
	pos[7].h = menuSurfaces[7]->clip_rect.h;
	

	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));

	SDL_Event event;


	while (true)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
			{
				for (int i = 0; i < NUMMENU; i++)
				{
					SDL_FreeSurface(menuSurfaces[i]);
					SDL_DestroyTexture(menuTextures[i]);
					return 0;
				}
			}

			case SDL_MOUSEMOTION:
			{
				x = event.motion.x;
				y = event.motion.y;

				if (x >= pos[7].x && x <= pos[7].x + pos[7].w && y >= pos[7].y && y <= pos[7].y + pos[7].h)
				{
					if (!selected)
					{
						selected = true;
						SDL_FreeSurface(menuSurfaces[7]);
						SDL_DestroyTexture(menuTextures[7]);
						menuSurfaces[7] = TTF_RenderText_Solid(font, labels[7], color[1]);
						menuTextures[7] = SDL_CreateTextureFromSurface(ren, menuSurfaces[7]);
					}
				}

				else
				{
					if (selected)
					{
						selected = false;
						SDL_FreeSurface(menuSurfaces[7]);
						SDL_DestroyTexture(menuTextures[7]);
						menuSurfaces[7] = TTF_RenderText_Solid(font, labels[7], color[0]);
						menuTextures[7] = SDL_CreateTextureFromSurface(ren, menuSurfaces[7]);
					}
				}
			
				break;
			}

			case SDL_MOUSEBUTTONDOWN:
			{

				x = event.motion.x;
				y = event.motion.y;

				
				if (x >= pos[7].x && x <= pos[7].x + pos[7].w && y >= pos[7].y && y <= pos[7].y + pos[7].h)
				{
					for (int j = 0; j < NUMMENU; j++)
					{
						SDL_FreeSurface(menuSurfaces[j]);
						SDL_DestroyTexture(menuTextures[j]);
					}
					return 1;
				}


				

				break;
			}



			}
		}

		SDL_RenderClear(ren);

		for (int i = 0; i < NUMMENU; i++)
		{
			SDL_RenderCopy(ren, menuTextures[i], NULL, &pos[i]);
		}

		SDL_RenderPresent(ren);
	}

}

// similar to other menus
int Survival::WeaponsMenu(SDL_Renderer *ren, TTF_Font *font) {


	int x, y;
	const int NUMMENU = 4;
	const char *labels[NUMMENU] = { "Throwing knife", "Arrow", "Shuriken" , "Back" };
	SDL_Surface *menuSurfaces[NUMMENU];
	SDL_Texture *menuTextures[NUMMENU];
	bool selected[NUMMENU] = { false, false,false,false };
	SDL_Color color[2] = { { 255,255,255 },{ 255,0,0 } };
	SDL_Surface *screen = SDL_CreateRGBSurface(0, SCREENWIDTH, SCREENHEIGHT, 32, 0, 0, 0, 0);

	for (int i = 0; i < NUMMENU; i++)
	{
		menuSurfaces[i] = TTF_RenderText_Solid(font, labels[i], color[0]);
		menuTextures[i] = SDL_CreateTextureFromSurface(ren, menuSurfaces[i]);
	}



	SDL_Rect pos[NUMMENU];


	for (int i = 0; i < (NUMMENU - 1); i++)
	{
		pos[i].x = (screen->clip_rect.w / 2) - (menuSurfaces[i]->clip_rect.w / 2);
		pos[i].y = (screen->clip_rect.h / 2) + ((i-1) * (menuSurfaces[i]->clip_rect.h)) - 100;
		pos[i].w = menuSurfaces[i]->clip_rect.w;
		pos[i].h = menuSurfaces[i]->clip_rect.h;
	}

	pos[3].x = (screen->clip_rect.w / 2) - (menuSurfaces[3]->clip_rect.w / 2);
	pos[3].y = (screen->clip_rect.h / 2) + (3 * (menuSurfaces[3]->clip_rect.h)) - 100;
	pos[3].w = menuSurfaces[3]->clip_rect.w;
	pos[3].h = menuSurfaces[3]->clip_rect.h;


	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));

	SDL_Event event;


	while (true)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
			{
				for (int i = 0; i < NUMMENU; i++)
				{
					SDL_FreeSurface(menuSurfaces[i]);
					SDL_DestroyTexture(menuTextures[i]);
					return 4;
				}
			}

			case SDL_MOUSEMOTION:
			{
				x = event.motion.x;
				y = event.motion.y;

				for (int i = 0; i < NUMMENU; i++)
				{
					if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h)
					{
						if (!selected[i])
						{
							selected[i] = true;
							SDL_FreeSurface(menuSurfaces[i]);
							SDL_DestroyTexture(menuTextures[i]);
							menuSurfaces[i] = TTF_RenderText_Solid(font, labels[i], color[1]);
							menuTextures[i] = SDL_CreateTextureFromSurface(ren, menuSurfaces[i]);
						}
					}

					else
					{
						if (selected[i])
						{
							selected[i] = false;
							SDL_FreeSurface(menuSurfaces[i]);
							SDL_DestroyTexture(menuTextures[i]);
							menuSurfaces[i] = TTF_RenderText_Solid(font, labels[i], color[0]);
							menuTextures[i] = SDL_CreateTextureFromSurface(ren, menuSurfaces[i]);
						}
					}
				}

				break;
			}

			case SDL_MOUSEBUTTONDOWN:
			{

				x = event.motion.x;
				y = event.motion.y;

				for (int i = 0; i < NUMMENU; i++)
				{
					if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h)
					{
						for (int j = 0; j < NUMMENU; j++)
						{
							SDL_FreeSurface(menuSurfaces[j]);
							SDL_DestroyTexture(menuTextures[j]);
						}
						return i;
					}


				}



				break;
			}



			}
		}

		SDL_RenderClear(ren);

		for (int i = 0; i < NUMMENU; i++)
		{
			SDL_RenderCopy(ren, menuTextures[i], NULL, &pos[i]);
		}

		SDL_RenderPresent(ren);
	}
	
}

// similar to other menus
int Survival::PauseMenu(SDL_Renderer *ren, TTF_Font *font) {

	int x, y;
	const int NUMMENU = 3;
	const char *labels[NUMMENU] = { "Change Weapon", "Resume", "Exit"};
	SDL_Surface *menuSurfaces[NUMMENU];
	SDL_Texture *menuTextures[NUMMENU];
	bool selected[NUMMENU] = { false, false,false };
	SDL_Color color[2] = { { 255,255,255 },{ 255,0,0 } };
	SDL_Surface *screen = SDL_CreateRGBSurface(0, SCREENWIDTH, SCREENHEIGHT, 32, 0, 0, 0, 0);

	for (int i = 0; i < NUMMENU; i++)
	{
		menuSurfaces[i] = TTF_RenderText_Solid(font, labels[i], color[0]);
		menuTextures[i] = SDL_CreateTextureFromSurface(ren, menuSurfaces[i]);
	}



	SDL_Rect pos[NUMMENU];

	for (int i = 0; i < NUMMENU; i++)
	{
		pos[i].x = (screen->clip_rect.w / 2) - (menuSurfaces[i]->clip_rect.w / 2);
		pos[i].y = (screen->clip_rect.h / 2) + ((i - 1) * (menuSurfaces[i]->clip_rect.h)) - 100;
		pos[i].w = menuSurfaces[i]->clip_rect.w;
		pos[i].h = menuSurfaces[i]->clip_rect.h;
	}



	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));

	SDL_Event event;


	while (true)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
			{
				for (int i = 0; i < NUMMENU; i++)
				{
					SDL_FreeSurface(menuSurfaces[i]);
					SDL_DestroyTexture(menuTextures[i]);
					return 2;
				}
			}

			case SDL_MOUSEMOTION:
			{
				x = event.motion.x;
				y = event.motion.y;

				for (int i = 0; i < NUMMENU; i++)
				{
					if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h)
					{
						if (!selected[i])
						{
							selected[i] = true;
							SDL_FreeSurface(menuSurfaces[i]);
							SDL_DestroyTexture(menuTextures[i]);
							menuSurfaces[i] = TTF_RenderText_Solid(font, labels[i], color[1]);
							menuTextures[i] = SDL_CreateTextureFromSurface(ren, menuSurfaces[i]);
						}
					}

					else
					{
						if (selected[i])
						{
							selected[i] = false;
							SDL_FreeSurface(menuSurfaces[i]);
							SDL_DestroyTexture(menuTextures[i]);
							menuSurfaces[i] = TTF_RenderText_Solid(font, labels[i], color[0]);
							menuTextures[i] = SDL_CreateTextureFromSurface(ren, menuSurfaces[i]);
						}
					}
				}

				break;
			}

			case SDL_MOUSEBUTTONDOWN:
			{

				x = event.motion.x;
				y = event.motion.y;

				for (int i = 0; i < NUMMENU; i++)
				{
					if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h)
					{
						for (int j = 0; j < NUMMENU; j++)
						{
							SDL_FreeSurface(menuSurfaces[j]);
							SDL_DestroyTexture(menuTextures[j]);
						}
						return i;
					}


				}



				break;
			}



			}
		}

		SDL_RenderClear(ren);

		for (int i = 0; i < NUMMENU; i++)
		{
			SDL_RenderCopy(ren, menuTextures[i], NULL, &pos[i]);
		}

		SDL_RenderPresent(ren);
	}

}


// similar to other menus
int Survival::EndMenu(SDL_Renderer *ren, TTF_Font *font, string hs) {

	int x, y;
	const int NUMMENU = 4;
	const char *conversion = hs.c_str();
	const char *labels[NUMMENU] = { "Game Over!", "Highscore:", conversion, "Exit" };
	SDL_Surface *menuSurfaces[NUMMENU];
	SDL_Texture *menuTextures[NUMMENU];
	bool selected = false;
	SDL_Color color[2] = { { 255,255,255 },{ 255,0,0 } };
	SDL_Surface *screen = SDL_CreateRGBSurface(0, SCREENWIDTH, SCREENHEIGHT, 32, 0, 0, 0, 0);

	for (int i = 0; i < NUMMENU; i++)
	{
		menuSurfaces[i] = TTF_RenderText_Solid(font, labels[i], color[0]);
		menuTextures[i] = SDL_CreateTextureFromSurface(ren, menuSurfaces[i]);
	}



	SDL_Rect pos[NUMMENU];

	pos[0].x = (screen->clip_rect.w / 2) - (menuSurfaces[0]->clip_rect.w / 2);
	pos[0].y = (screen->clip_rect.h / 2) + ((0 - 1) * (menuSurfaces[0]->clip_rect.h)) - 100;
	pos[0].w = menuSurfaces[0]->clip_rect.w;
	pos[0].h = menuSurfaces[0]->clip_rect.h;

	pos[1].x = (screen->clip_rect.w / 2) - (menuSurfaces[1]->clip_rect.w / 2);
	pos[1].y = (screen->clip_rect.h / 2) + ((1 - 1) * (menuSurfaces[1]->clip_rect.h)) - 100;
	pos[1].w = menuSurfaces[1]->clip_rect.w;
	pos[1].h = menuSurfaces[1]->clip_rect.h;

	pos[2].x = ((screen->clip_rect.w / 2) - (menuSurfaces[2]->clip_rect.w / 2))+ (pos[1].w);
	pos[2].y = pos[1].y;
	pos[2].w = menuSurfaces[2]->clip_rect.w;
	pos[2].h = menuSurfaces[2]->clip_rect.h;

	pos[3].x = (screen->clip_rect.w / 2) - (menuSurfaces[3]->clip_rect.w / 2);
	pos[3].y = (screen->clip_rect.h / 2) + ((3 - 1) * (menuSurfaces[3]->clip_rect.h)) - 100;
	pos[3].w = menuSurfaces[3]->clip_rect.w;
	pos[3].h = menuSurfaces[3]->clip_rect.h;


	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));

	SDL_Event event;


	while (true)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
			{
				for (int i = 0; i < NUMMENU; i++)
				{
					SDL_FreeSurface(menuSurfaces[i]);
					SDL_DestroyTexture(menuTextures[i]);
					return 2;
				}
			}

			case SDL_MOUSEMOTION:
			{
				x = event.motion.x;
				y = event.motion.y;

				
				
				if (x >= pos[3].x && x <= pos[3].x + pos[3].w && y >= pos[3].y && y <= pos[3].y + pos[3].h)
				{
					if (!selected)
					{
						selected = true;
						SDL_FreeSurface(menuSurfaces[3]);
						SDL_DestroyTexture(menuTextures[3]);
						menuSurfaces[3] = TTF_RenderText_Solid(font, labels[3], color[1]);
						menuTextures[3] = SDL_CreateTextureFromSurface(ren, menuSurfaces[3]);
					}
				}

				else
				{
					if (selected)
					{
						selected = false;
						SDL_FreeSurface(menuSurfaces[3]);
						SDL_DestroyTexture(menuTextures[3]);
						menuSurfaces[3] = TTF_RenderText_Solid(font, labels[3], color[0]);
						menuTextures[3] = SDL_CreateTextureFromSurface(ren, menuSurfaces[3]);
					}
				}
			

			break;
		}

			case SDL_MOUSEBUTTONDOWN:
			{

				x = event.motion.x;
				y = event.motion.y;

				
				
				if (x >= pos[3].x && x <= pos[3].x + pos[3].w && y >= pos[3].y && y <= pos[3].y + pos[3].h)
				{
					for (int i = 0; i < NUMMENU; i++)
					{
						SDL_FreeSurface(menuSurfaces[i]);
						SDL_DestroyTexture(menuTextures[i]);
					}
					return 2;
				}

				break;
			}



			}
		}

		SDL_RenderClear(ren);

		for (int i = 0; i < NUMMENU; i++)
		{
			SDL_RenderCopy(ren, menuTextures[i], NULL, &pos[i]);
		}

		SDL_RenderPresent(ren);
	}

}

// similar to other menus
int Survival::ClearMenu(SDL_Renderer *ren, TTF_Font *font, string s) {

	int x, y;
	const int NUMMENU = 4;
	const char *conversion = s.c_str();
	const char *labels[NUMMENU] = { "Level Clear!", "Score:", conversion, "Continue" };
	SDL_Surface *menuSurfaces[NUMMENU];
	SDL_Texture *menuTextures[NUMMENU];
	bool selected = false;
	SDL_Color color[2] = { { 255,255,255 },{ 255,0,0 } };
	SDL_Surface *screen = SDL_CreateRGBSurface(0, SCREENWIDTH, SCREENHEIGHT, 32, 0, 0, 0, 0);

	for (int i = 0; i < NUMMENU; i++)
	{
		menuSurfaces[i] = TTF_RenderText_Solid(font, labels[i], color[0]);
		menuTextures[i] = SDL_CreateTextureFromSurface(ren, menuSurfaces[i]);
	}

	SDL_Rect pos[NUMMENU];

	pos[0].x = (screen->clip_rect.w / 2) - (menuSurfaces[0]->clip_rect.w / 2);
	pos[0].y = (screen->clip_rect.h / 2) + ((0 - 1) * (menuSurfaces[0]->clip_rect.h)) - 100;
	pos[0].w = menuSurfaces[0]->clip_rect.w;
	pos[0].h = menuSurfaces[0]->clip_rect.h;

	pos[1].x = (screen->clip_rect.w / 2) - (menuSurfaces[1]->clip_rect.w / 2);
	pos[1].y = (screen->clip_rect.h / 2) + ((1 - 1) * (menuSurfaces[1]->clip_rect.h)) - 100;
	pos[1].w = menuSurfaces[1]->clip_rect.w;
	pos[1].h = menuSurfaces[1]->clip_rect.h;

	pos[2].x = ((screen->clip_rect.w / 2) - (menuSurfaces[2]->clip_rect.w / 2)) + (pos[1].w);
	pos[2].y = pos[1].y;
	pos[2].w = menuSurfaces[2]->clip_rect.w;
	pos[2].h = menuSurfaces[2]->clip_rect.h;

	pos[3].x = (screen->clip_rect.w / 2) - (menuSurfaces[3]->clip_rect.w / 2);
	pos[3].y = (screen->clip_rect.h / 2) + ((3 - 1) * (menuSurfaces[3]->clip_rect.h)) - 100;
	pos[3].w = menuSurfaces[3]->clip_rect.w;
	pos[3].h = menuSurfaces[3]->clip_rect.h;


	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));

	SDL_Event event;


	while (true)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
			{
				for (int i = 0; i < NUMMENU; i++)
				{
					SDL_FreeSurface(menuSurfaces[i]);
					SDL_DestroyTexture(menuTextures[i]);
					return 1;
				}
			}

			case SDL_MOUSEMOTION:
			{
				x = event.motion.x;
				y = event.motion.y;



				if (x >= pos[3].x && x <= pos[3].x + pos[3].w && y >= pos[3].y && y <= pos[3].y + pos[3].h)
				{
					if (!selected)
					{
						selected = true;
						SDL_FreeSurface(menuSurfaces[3]);
						SDL_DestroyTexture(menuTextures[3]);
						menuSurfaces[3] = TTF_RenderText_Solid(font, labels[3], color[1]);
						menuTextures[3] = SDL_CreateTextureFromSurface(ren, menuSurfaces[3]);
					}
				}

				else
				{
					if (selected)
					{
						selected = false;
						SDL_FreeSurface(menuSurfaces[3]);
						SDL_DestroyTexture(menuTextures[3]);
						menuSurfaces[3] = TTF_RenderText_Solid(font, labels[3], color[0]);
						menuTextures[3] = SDL_CreateTextureFromSurface(ren, menuSurfaces[3]);
					}
				}


				break;
			}

			case SDL_MOUSEBUTTONDOWN:
			{

				x = event.motion.x;
				y = event.motion.y;



				if (x >= pos[3].x && x <= pos[3].x + pos[3].w && y >= pos[3].y && y <= pos[3].y + pos[3].h)
				{
					for (int i = 0; i < NUMMENU; i++)
					{
						SDL_FreeSurface(menuSurfaces[i]);
						SDL_DestroyTexture(menuTextures[i]);
					}
					return 0;
				}

				break;
			}

			}
		}

		SDL_RenderClear(ren);

		for (int i = 0; i < NUMMENU; i++)
		{
			SDL_RenderCopy(ren, menuTextures[i], NULL, &pos[i]);
		}

		SDL_RenderPresent(ren);
	}
}

// start the game
void Survival::StartGame() {

	bool isRunning = true; // check to see if the game is running

	// initialize SDL, image, font, music
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();

	// create sound bites
	Mix_Music *bMusic = NULL;

	Mix_Chunk *throwSound = NULL;
	Mix_Chunk *hitSound = NULL;
	Mix_Chunk *zombieSound = NULL;

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	bMusic = Mix_LoadMUS("Menu.mp3");
	throwSound = Mix_LoadWAV("throw.mp3");
	hitSound = Mix_LoadWAV("hit.mp3");
	zombieSound = Mix_LoadWAV("spook.mp3");

	// load xml file
	XMLDocument doc;
	doc.LoadFile("GameInfo.xml");

	// make the window and the renderer
	SDL_Window *win;
	SDL_Renderer *ren;
	SDL_CreateWindowAndRenderer(SCREENWIDTH, SCREENHEIGHT, NULL, &win, &ren);


	// the counter text for remaining zombies
	TTF_Font *font = TTF_OpenFont("OpenSans-Bold.ttf", 16);
	SDL_Color color = { 255, 0, 0 };
	SDL_Surface *zombieCountSurface = TTF_RenderText_Solid(font, "Remaining:", color);
	SDL_Texture *zombieCountTexture = SDL_CreateTextureFromSurface(ren, zombieCountSurface);
	SDL_Rect zombieTextRect = { SCREENWIDTH / 2 + 200, 0, 100, 50 };


	const int WEAPONSREN = 5; // the max amonut of weapons rendered on the screen at once
	const int ZOMBIESREN = 4; // the max amount of small zombies rendered on the screen at once

	int zombieCounterInt = 10; // the initial amount of zombies to clear

	// the initial counter stream
	ostringstream counter;
	counter.str("");

	counter << zombieCounterInt;

	// the counter for remaining zombies
	SDL_Surface *counterSurface = TTF_RenderText_Solid(font, counter.str().c_str(), color);
	SDL_Texture *counterTexture = SDL_CreateTextureFromSurface(ren, counterSurface);
	SDL_Rect counterRect = { SCREENWIDTH / 2 + 320, 0, 50, 50 };

	// load textures and set rectangles
	SDL_Texture *bg = loadTexture(ren, "BG.png");
	SDL_Texture *player = loadTexture(ren, "Link.png");
	SDL_Texture *knife = loadTexture(ren, "knife.png");
	SDL_Texture *arrow = loadTexture(ren, "arrow.png");
	SDL_Texture *shuriken = loadTexture(ren, "Shuriken.png");
	SDL_Texture *zombies = loadTexture(ren, "zombies.png");

	SDL_Rect background = { 0,0,SCREENWIDTH, SCREENHEIGHT };
	SDL_Rect bgSrc = { 0,0,500,450 };

	SDL_Rect knives[WEAPONSREN];
	SDL_Rect arrows[WEAPONSREN];
	SDL_Rect shurikens[WEAPONSREN];

	for (int i = 0; i < WEAPONSREN; i++)
	{
		knives[i].h = 36;
		knives[i].w = 18;
		arrows[i].h = 32;
		arrows[i].w = 14;
		shurikens[i].h = 32;
		shurikens[i].w = 32;
	}

	// create animations
	const int pWalkAnims = 5; //Total number of animations in the sequence
	const int zAnims = 6;

	int pWalkAnimWidth = 450; //Width of single sequence
	int pWalkAnimHeight = 360 / 4; //Height of single sequence

	int zAnimWidth = 738;
	int zAnimHeight = 160 / 2;


	SDL_Rect pWalkLeftRectSrc[pWalkAnims]; //Sprite sheet Rect Source array
	SDL_Rect zWalkRectSrc[zAnims];

	int walkLoop = 0; //element counter of array
	int zLoop = 0;

	for (int x = 0; x < pWalkAnimWidth; x = x + (pWalkAnimWidth / pWalkAnims))
	{
		pWalkLeftRectSrc[walkLoop].x = x;
		pWalkLeftRectSrc[walkLoop].y = 0;
		pWalkLeftRectSrc[walkLoop].w = pWalkAnimWidth / pWalkAnims;
		pWalkLeftRectSrc[walkLoop].h = pWalkAnimHeight;
		walkLoop++;
	}
	walkLoop = 0;

	for (int x = 0; x < zAnimWidth; x = x + (zAnimWidth / zAnims))
	{
		zWalkRectSrc[zLoop].x = x;
		zWalkRectSrc[zLoop].y = 0;
		zWalkRectSrc[zLoop].w = zAnimWidth / zAnims;
		zWalkRectSrc[zLoop].h = zAnimHeight;
		zLoop++;
	}
	zLoop = 0;

	

	SDL_Rect pWalkRightRectSrc[pWalkAnims];
	SDL_Rect zDeathRectSrc[zAnims];


	for (int x = 0; x < pWalkAnimWidth; x = x + (pWalkAnimWidth / pWalkAnims))
	{
		pWalkRightRectSrc[walkLoop].x = x;
		pWalkRightRectSrc[walkLoop].y = pWalkAnimHeight;
		pWalkRightRectSrc[walkLoop].w = pWalkAnimWidth / pWalkAnims;
		pWalkRightRectSrc[walkLoop].h = pWalkAnimHeight;
		walkLoop++;
	}
	walkLoop = 0;

	for (int x = 0; x < zAnimWidth; x = x + (zAnimWidth / zAnims))
	{
		zDeathRectSrc[zLoop].x = x;
		zDeathRectSrc[zLoop].y = zAnimHeight;
		zDeathRectSrc[zLoop].w = zAnimWidth / zAnims;
		zDeathRectSrc[zLoop].h = zAnimHeight;
		zLoop++;
	}
	zLoop = 0;

	SDL_Rect pWalkUpRectSrc[pWalkAnims];


	for (int x = 0; x < pWalkAnimWidth; x = x + (pWalkAnimWidth / pWalkAnims))
	{
		pWalkUpRectSrc[walkLoop].x = x;
		pWalkUpRectSrc[walkLoop].y = pWalkAnimHeight * 2;
		pWalkUpRectSrc[walkLoop].w = pWalkAnimWidth / pWalkAnims;
		pWalkUpRectSrc[walkLoop].h = pWalkAnimHeight;
		walkLoop++;
	}
	walkLoop = 0;

	SDL_Rect pWalkDownRectSrc[pWalkAnims];


	for (int x = 0; x < pWalkAnimWidth; x = x + (pWalkAnimWidth / pWalkAnims))
	{
		pWalkDownRectSrc[walkLoop].x = x;
		pWalkDownRectSrc[walkLoop].y = pWalkAnimHeight * 3;
		pWalkDownRectSrc[walkLoop].w = pWalkAnimWidth / pWalkAnims;
		pWalkDownRectSrc[walkLoop].h = pWalkAnimHeight;
		walkLoop++;
	}
	walkLoop = 0;

	SDL_Rect pRectDst;

	pRectDst.w = pWalkAnimWidth / pWalkAnims;
	pRectDst.h = pWalkAnimHeight;
	pRectDst.x = (SCREENWIDTH / 2) - (pRectDst.w / 2);
	pRectDst.y = (SCREENHEIGHT / 2) - (pRectDst.h / 2);

	std::srand(time(NULL)); // set RNG seed

	SDL_Rect smallZRectDst[ZOMBIESREN];

	for (int i = 0; i < ZOMBIESREN; i++)
	{
		smallZRectDst[i].w = zAnimWidth / zAnims;
		smallZRectDst[i].h = zAnimHeight;
	}

	smallZRectDst[0].x = rand() % SCREENWIDTH;
	smallZRectDst[0].y = 0 - smallZRectDst[0].h;
	smallZRectDst[1].x = 0 - (smallZRectDst[1].w);
	smallZRectDst[1].y = rand() % SCREENHEIGHT;
	smallZRectDst[2].x = rand() % SCREENWIDTH;
	smallZRectDst[2].y = SCREENHEIGHT;
	smallZRectDst[3].x = SCREENWIDTH;
	smallZRectDst[3].y = rand() % SCREENHEIGHT;
	
	SDL_Rect bigZRectDst = { SCREENWIDTH,rand() % SCREENHEIGHT,(zAnimWidth / zAnims) * 3, zAnimHeight * 3 };


	SDL_Rect *pWalkClip;
	SDL_Rect *zClip;
	SDL_Rect *zDeathClips[ZOMBIESREN];
	SDL_Rect *bigZDeathClip;

	int pWalkFrame = 0;
	int zFrame = 0;
	int zDeathFrames[ZOMBIESREN] = { 0,0,0,0 };
	int zDeathFrame = 0;

	// checks for where the player is facing
	bool isFacingRight = false;
	bool isFacingLeft = false;
	bool isFacingUp = false;
	bool isFacingDown = false;

	// more booleans.
	bool isZombieDying[ZOMBIESREN] = { false,false,false,false };
	bool isBigZombieDying = false;
	bool isMovingUp = false;
	bool isMovingDown = false;
	bool isMovingLeft = false;
	bool isMovingRight = false;
	bool zombieFlip[ZOMBIESREN] = { false, false, false, false };
	bool bigZombieFlip = false;

	bool hasBeenHit[ZOMBIESREN] = { false,false,false,false };
	bool hasBigBeenHit = false;
	bool hasLinkDied = false;
	bool isRespawning[ZOMBIESREN] = { false,false,false,false };
	bool isBigRespawning = false;

	bool drawWeapon[WEAPONSREN] = { false, false, false, false, false };
	bool weaponRight[WEAPONSREN] = { false, false, false, false, false };
	bool weaponLeft[WEAPONSREN] = { false, false, false, false, false };
	bool weaponUp[WEAPONSREN] = { false, false, false, false, false };
	bool weaponDown[WEAPONSREN] = { false, false, false, false, false };

	bool changeCount = false; // check to see if it is necessary to create a new texture to hold a new value for zombies remaining

	int bigZHitCounter = 0; // the big zombie needs three hits to die

	// the level and the current score
	int levelCount = 1;
	int score = 0;


	XMLElement *ePlayerInfo = doc.FirstChildElement("player");

	XMLElement *ePlayerHs = ePlayerInfo->FirstChildElement("highscore");

	int hsInt = atoi(ePlayerHs->GetText());

	string scoreChar = to_string(score);

	string hsChar = to_string(hsInt);

	int randomSpawn = 0;

	const int maxLevel = 10;


	const char *weapon = doc.FirstChildElement("player")->FirstChildElement("weapon")->GetText();

	string weaponChoice = weapon;

	int weaponCounter = 0;

	bool hasStarted = false;
	const float playerVel = 0.035;
	const float weaponVel = 0.15;
	const float smallZombieVel = 0.03;
	const float bigZombieVel = 0.01;
	float playerPosX = float (pRectDst.x);
	float playerPosY = float (pRectDst.y);
	float weaponPosX[] = { 0,0,0,0,0 };
	float weaponPosY[] = { 0,0,0,0,0 };

	float smallzombiesPosX[ZOMBIESREN];
	float smallzombiesPosY[ZOMBIESREN];

	for (int i = 0; i < ZOMBIESREN; i++)
	{
		smallzombiesPosX[i] = int(smallZRectDst[i].x);
		smallzombiesPosY[i] = int(smallZRectDst[i].y);
	}

	float bigZombiePosX = int(bigZRectDst.x);
	float bigZombiePosY = int(bigZRectDst.y);
	
	double angles[] = { 0,0,0,0,0 };

	int m;
	int n = 1;
	int o = 0;

	XMLElement *eWeaponInfo = ePlayerInfo->FirstChildElement("weapon");


	// main menu
	do
	{
		if (Mix_PlayingMusic() == 0)
		{
			Mix_PlayMusic(bMusic, -1);
		}
		m = MainMenu(ren, font);

		if (m == 2)
		{
			n = HowToPlay(ren, font);
		}

		else if (m == 1)
		{
			o = WeaponsMenu(ren, font);

			if (o == 0)
			{
				weaponChoice = "knife";
				eWeaponInfo->SetText("knife");
			}

			else if (o == 1)
			{
				weaponChoice = "arrow";
				eWeaponInfo->SetText("arrow");
			}

			else if (o == 2)
			{
				weaponChoice = "shuriken";
				eWeaponInfo->SetText("shuriken");
			}
		}

	} while (m != 0 && m != 3 && n != 0 && o != 4);
	

	if (m == 3 || n == 0 || o == 4)
	{
		isRunning = false;
	}

	SDL_Event event;

	int w = 0;
	int z = 0;

	Mix_PauseMusic();


	// GAME LOOP 
	while (isRunning)
	{
		SDL_RenderClear(ren);


		if (hasLinkDied || levelCount > maxLevel)
		{


			if (Mix_PausedMusic() == 1)
			{
				Mix_ResumeMusic();
			}

			if (score > hsInt)
			{

				hsInt = score;

				hsChar = to_string(hsInt);
				ePlayerHs->SetText(hsChar.c_str());

			}


			w = EndMenu(ren, font, hsChar);
			isRunning = false;
		}

		if (zombieCounterInt == 0) {

			if (levelCount <= maxLevel)
			{

				if (Mix_PausedMusic() == 1)
				{
					Mix_ResumeMusic();
				}
				z = ClearMenu(ren, font, scoreChar);
			}
			zombieCounterInt = 10 * levelCount;
			SDL_FreeSurface(counterSurface);
			SDL_DestroyTexture(counterTexture);

			counter << zombieCounterInt;

			counterSurface = TTF_RenderText_Solid(font, counter.str().c_str(), color);
			counterTexture = SDL_CreateTextureFromSurface(ren, counterSurface);

			if (Mix_PausedMusic() != 1)
			{
				Mix_PauseMusic();
			}
			if (z == 1)
			{
				isRunning = false;
			}

			hasStarted = false;
			pRectDst.x = (SCREENWIDTH / 2) - (pRectDst.w / 2);
			pRectDst.y = (SCREENHEIGHT / 2) - (pRectDst.h / 2);

			playerPosX = float(pRectDst.x);
			playerPosY = float(pRectDst.y);
			
			smallZRectDst[0].x = rand() % SCREENWIDTH;
			smallZRectDst[0].y = 0 - smallZRectDst[0].h;
			smallZRectDst[1].x = 0 - (smallZRectDst[1].w);
			smallZRectDst[1].y = rand() % SCREENHEIGHT;
			smallZRectDst[2].x = rand() % SCREENWIDTH;
			smallZRectDst[2].y = SCREENHEIGHT;
			smallZRectDst[3].x = SCREENWIDTH;
			smallZRectDst[3].y = rand() % SCREENHEIGHT;

			bigZRectDst.x = SCREENWIDTH;
			bigZRectDst.y = rand() % SCREENHEIGHT;

			bigZombiePosX = float(bigZRectDst.x);
			bigZombiePosY = float(bigZRectDst.y);

			for (int i = 0; i < ZOMBIESREN; i++)
			{
				isZombieDying[i] = false;
				zombieFlip[i] = false;
				hasBeenHit[i] = false;
				isRespawning[i] = false;

				smallzombiesPosX[i] = float(smallZRectDst[i].x);
				smallzombiesPosY[i] = float(smallZRectDst[i].y);
			}

			for (int i = 0; i < WEAPONSREN; i++)
			{
				drawWeapon[i] = false;
			}
		}

		SDL_RenderCopy(ren, bg, &bgSrc, &background);

		for (int i = 0; i < ZOMBIESREN; i++)
		{
			if (isRespawning[i])
			{
				smallzombiesPosX[i] = int(smallZRectDst[i].x);
				smallzombiesPosY[i] = int(smallZRectDst[i].y);
				isRespawning[i] = false;
			}
		}

		if (isBigRespawning)
		{
			bigZombiePosX = int(bigZRectDst.x);
			bigZombiePosY = int(bigZRectDst.y);
			isBigRespawning = false;
		}

		if (!hasStarted) {
			isFacingDown = true;
		}


		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{

			case SDL_QUIT:
			{
				isRunning = false;
			}
			case SDL_KEYDOWN:
			{
				hasStarted = true;
				switch (event.key.keysym.sym)
				{
				case SDLK_LEFT:
				{
					isFacingDown = false;
					isMovingDown = false;
					isFacingRight = false;
					isMovingRight = false;
					isFacingUp = false;
					isMovingUp = false;
					isFacingLeft = true;
					isMovingLeft = true;
					break;
				}

				case SDLK_RIGHT:
				{

					isFacingDown = false;
					isMovingDown = false;
					isFacingRight = true;
					isMovingRight = true;
					isFacingUp = false;
					isMovingUp = false;
					isFacingLeft = false;
					isMovingLeft = false;
					break;
				}

				case SDLK_UP:
				{
					isFacingDown = false;
					isMovingDown = false;
					isFacingRight = false;
					isMovingRight = false;
					isFacingUp = true;
					isMovingUp = true;
					isFacingLeft = false;
					isMovingLeft = false;
					break;
				}

				case SDLK_DOWN:
				{
					isFacingDown = true;
					isMovingDown = true;
					isFacingRight = false;
					isMovingRight = false;
					isFacingUp = false;
					isMovingUp = false;
					isFacingLeft = false;
					isMovingLeft = false;
					break;
				}

				case SDLK_ESCAPE:
				{

					int p;
					int q = 0;
					do
					{

						if (Mix_PausedMusic() == 1)
						{
							Mix_ResumeMusic();
						}

						p = PauseMenu(ren, font);

						if (p == 2)
						{
							isRunning = false;
						}

						else if (p == 0)
						{
							q = WeaponsMenu(ren, font);

							if (q == 4)
							{
								isRunning = false;
							}

							else if (q == 0)
							{
								weaponChoice = "knife";
								eWeaponInfo->SetText("knife");
							}

							else if (q == 1)
							{
								weaponChoice = "arrow";
								eWeaponInfo->SetText("arrow");
							}

							else if (q == 2)
							{
								weaponChoice = "shuriken";
								eWeaponInfo->SetText("shuriken");
							}
						}
					} while (p != 2 && p != 1 && q != 4);
					
					if (Mix_PausedMusic() != 1)
					{
						Mix_PauseMusic();
					}

					break;
				}

				default:
				{
					break;
				}

				}

				break;
			}

			case SDL_KEYUP:
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_LEFT:
				{
					isMovingLeft = false;
					break;
				}

				case SDLK_RIGHT:
				{

					isMovingRight = false;
					break;
				}

				case SDLK_UP:
				{
					isMovingUp = false;
					break;
				}

				case SDLK_DOWN:
				{
					isMovingDown = false;
					break;
				}

				default:
				{
					break;
				}

				}
				break;
			}

			case SDL_MOUSEBUTTONDOWN:
			{

				drawWeapon[weaponCounter] = true;

				Mix_PlayChannel(-1, throwSound, 0);

				if (isFacingRight)
				{
					weaponRight[weaponCounter] = true;
					weaponLeft[weaponCounter] = false;
					weaponDown[weaponCounter] = false;
					weaponUp[weaponCounter] = false;
					knives[weaponCounter].x = pRectDst.x + pRectDst.w + 5;
					knives[weaponCounter].y = pRectDst.y + ((pRectDst.h / 2) - (arrows[weaponCounter].h/2));
				}

				else if (isFacingLeft)
				{
					weaponRight[weaponCounter] = false;
					weaponLeft[weaponCounter] = true;
					weaponDown[weaponCounter] = false;
					weaponUp[weaponCounter] = false;
					knives[weaponCounter].x = pRectDst.x - 5;
					knives[weaponCounter].y = pRectDst.y + ((pRectDst.h / 2) - (knives[weaponCounter].h / 2));
				}
				
				else if (isFacingDown)
				{
					weaponRight[weaponCounter] = false;
					weaponLeft[weaponCounter] = false;
					weaponDown[weaponCounter] = true;
					weaponUp[weaponCounter] = false;
					knives[weaponCounter].x = pRectDst.x + ((pRectDst.w/2) - (knives[weaponCounter].w/2));
					knives[weaponCounter].y = pRectDst.y + pRectDst.h + 5;
				}

				else if (isFacingUp)
				{
					weaponRight[weaponCounter] = false;
					weaponLeft[weaponCounter] = false;
					weaponDown[weaponCounter] = false;
					weaponUp[weaponCounter] = true;
					knives[weaponCounter].x = pRectDst.x + ((pRectDst.w / 2) - (knives[weaponCounter].w / 2));
					knives[weaponCounter].y = pRectDst.y - 5;
				}

				weaponPosX[weaponCounter] = float(knives[weaponCounter].x);
				weaponPosY[weaponCounter] = float(knives[weaponCounter].y);

				weaponCounter++;

				if (weaponCounter > 4)
				{
					weaponCounter = 0;
				}

				break;
			}



			default:
			{
				break;
			}



			}

		}



		if (isFacingDown == true) {


			if (isMovingDown == true) {
				pWalkFrame++;
				if ((pRectDst.y + pRectDst.h) < SCREENHEIGHT)
				{
					playerPosY += playerVel;
				}
				if (pWalkFrame / DELTA >= pWalkAnims) {
					pWalkFrame = 0;
				}
			}
			else {
				pWalkFrame = 0;
			}
			pWalkClip = &pWalkDownRectSrc[pWalkFrame / DELTA];
		}

		else if (isFacingUp == true) {
			if (isMovingUp == true) {
				pWalkFrame++;
				if (pRectDst.y > 0)
				{
					playerPosY -= playerVel;
				}
				if (pWalkFrame / DELTA >= pWalkAnims) {
					pWalkFrame = 0;
				}
			}
			else {
				pWalkFrame = 0;
			}
			pWalkClip = &pWalkUpRectSrc[pWalkFrame / DELTA];
		}

		else if (isFacingLeft == true) {
			if (isMovingLeft == true) {
				pWalkFrame++;
				if (pRectDst.x > 0)
				{
					playerPosX -= playerVel;
				}
				if (pWalkFrame / DELTA >= pWalkAnims) {
					pWalkFrame = 0;
				}
			}
			else {
				pWalkFrame = 0;
			}
			pWalkClip = &pWalkLeftRectSrc[pWalkFrame / DELTA];
		}

		else if (isFacingRight == true) {
			if (isMovingRight == true) {
				pWalkFrame++;
				if ((pRectDst.x + pRectDst.w) < SCREENWIDTH)
				{
					playerPosX += playerVel;
				}
				if (pWalkFrame / DELTA >= pWalkAnims) {
					pWalkFrame = 0;
				}
			}
			else {
				pWalkFrame = DELTA * 4;
			}
			pWalkClip = &pWalkRightRectSrc[pWalkFrame / DELTA];
		}


		pRectDst.x = int(playerPosX);
		pRectDst.y = int(playerPosY);


		for (int i = 0; i < WEAPONSREN; i++)
		{
			if (weaponRight[i])
			{
				weaponPosX[i] += weaponVel;
				angles[i] = 90;
			}

			else if (weaponLeft[i])
			{
				weaponPosX[i] -= weaponVel;
				angles[i] = 270;
			}

			else if (weaponDown[i])
			{
				weaponPosY[i] += weaponVel;
				angles[i] = 180;
			}

			else if (weaponUp[i])
			{
				weaponPosY[i] -= weaponVel;
				angles[i] = 0;
			}

			knives[i].x = int(weaponPosX[i]);
			knives[i].y = int(weaponPosY[i]);

			if (drawWeapon[i])
			{
				if ((knives[i].x < (0 - knives[i].w)) || (knives[i].x > SCREENWIDTH) || (knives[i].y > SCREENHEIGHT) || ((knives[i].y) < (0 - knives[i].h)))
				{
					drawWeapon[i] = false;
				}
			}
		}

		for (int i = 0; i < WEAPONSREN; i++)
		{
			if (drawWeapon[i])
			{
				if (weaponChoice == "knife")
				{
					SDL_RenderCopyEx(ren, knife, NULL, &knives[i], angles[i], NULL, SDL_FLIP_NONE);
				}
				
				else if (weaponChoice == "arrow")
				{
					SDL_RenderCopyEx(ren, arrow, NULL, &knives[i], angles[i], NULL, SDL_FLIP_NONE);
				}

				else if (weaponChoice == "shuriken")
				{
					SDL_RenderCopyEx(ren, shuriken, NULL, &knives[i], angles[i], NULL, SDL_FLIP_NONE);
				}
			}
		}

		if (hasStarted)
		{

			for (int i = 0; i < WEAPONSREN; i++)
			{
				if ((drawWeapon[i]) && (knives[i].x >= bigZRectDst.x) && (knives[i].x <= (bigZRectDst.x + bigZRectDst.w)) && (knives[i].y >= bigZRectDst.y) && (knives[i].y <= (bigZRectDst.y + bigZRectDst.w)))
				{
					drawWeapon[i] = false;
					hasBigBeenHit = true;
					bigZHitCounter++;

					if (bigZHitCounter == 3)
					{
						isBigZombieDying = true;
						bigZHitCounter = 0;
						changeCount = true;
					}
				}

				else
				{
					hasBigBeenHit = false;
				}

				
			}

			if (!isBigZombieDying)
			{
				zFrame++;
				if (zFrame / (DELTA) >= zAnims) {
					zFrame = 0;
				}

				if ((bigZombiePosX < playerPosX))
				{
					bigZombiePosX += bigZombieVel;

					if (bigZombiePosX < (playerPosX - pRectDst.w / 2))
					{
						bigZombieFlip = false;
					}
				}

				else if (bigZombiePosX > playerPosX)
				{
					bigZombiePosX -= bigZombieVel;

					if (bigZombiePosX > (playerPosX + pRectDst.w / 2))
					{
						bigZombieFlip = true;
					}


				}

				else if (bigZombiePosX == playerPosX)
				{
					bigZombieFlip = false;
				}

				if (bigZombiePosY < playerPosY)
				{
					bigZombiePosY += bigZombieVel;
				}

				else if (bigZombiePosY > playerPosY)
				{
					bigZombiePosY -= bigZombieVel;
				}

				

				zClip = &zWalkRectSrc[zFrame / (DELTA)];


				bigZRectDst.x = int(bigZombiePosX);
				bigZRectDst.y = int(bigZombiePosY);

				if ((bigZRectDst.x >= (pRectDst.x - bigZRectDst.w)) && (bigZRectDst.x <= (pRectDst.x + pRectDst.w)) && (bigZRectDst.y >= (pRectDst.y - bigZRectDst.h)) && (bigZRectDst.y <= (pRectDst.y + pRectDst.h)))
				{
					Mix_PlayChannel(-1, zombieSound, 0);
				}

				if (!bigZombieFlip)
				{
					SDL_RenderCopy(ren, zombies, zClip, &bigZRectDst);
				}

				else
				{
					SDL_RenderCopyEx(ren, zombies, zClip, &bigZRectDst, 0, NULL, SDL_FLIP_HORIZONTAL);
				}
			}

			else
			{
				zDeathFrame++;

				if ((zDeathFrame / DELTA) >= zAnims)
				{
					zDeathFrame = 0;
					score += 10;
					Mix_PlayChannel(-1, hitSound, 0);
					zombieCounterInt--;
					isBigZombieDying = false;
					isBigRespawning = true;
					bigZRectDst.x = rand() % SCREENWIDTH;

					randomSpawn = rand() % 2;

					if (randomSpawn == 0)
					{
						bigZRectDst.y = 0 - bigZRectDst.h;
					}

					else
					{
						bigZRectDst.y = SCREENHEIGHT;
					}


				}

				bigZDeathClip = &zDeathRectSrc[zDeathFrame / DELTA];

				if (!bigZombieFlip)
				{
					SDL_RenderCopy(ren, zombies, bigZDeathClip, &bigZRectDst);
				}

				else
				{
					SDL_RenderCopyEx(ren, zombies, bigZDeathClip, &bigZRectDst, 0, NULL, SDL_FLIP_HORIZONTAL);
				}

			}
		}
	
		for (int i = 0; i < ZOMBIESREN; i++)
		{



			if (hasStarted)
			{

				for (int j = 0; j < WEAPONSREN; j++)
				{
					if ((drawWeapon[j]) && (knives[j].x >= smallZRectDst[i].x) && (knives[j].x <= (smallZRectDst[i].x + smallZRectDst[i].w)) && (knives[j].y >= smallZRectDst[i].y) && (knives[j].y <= (smallZRectDst[i].y + smallZRectDst[i].h)))
					{
						drawWeapon[j] = false;
						hasBeenHit[i] = true;
						isZombieDying[i] = true;


					}

					else
					{
						hasBeenHit[i] = false;
					}

					
				}

				if (!isZombieDying[i])
				{
					if (smallzombiesPosX[i] < playerPosX)
					{
						if (smallzombiesPosY[i] != playerPosY)
						{
							smallzombiesPosX[i] += smallZombieVel / 2;
						}
						else
						{
							smallzombiesPosX[i] += smallZombieVel;
						}
						if ((smallzombiesPosX[i] < (playerPosX - (pRectDst.w / 2))))
						{
							zombieFlip[i] = false;
						}
					}
					else if (smallzombiesPosX[i] > playerPosX)
					{

						if (smallzombiesPosY[i] != playerPosY)
						{
							smallzombiesPosX[i] -= smallZombieVel / 2;
						}
						else
						{
							smallzombiesPosX[i] -= smallZombieVel;
						}
						if ((smallzombiesPosX[i] > (playerPosX + (pRectDst.w / 2))))
						{
							zombieFlip[i] = true;
						}
					}
					else if (smallzombiesPosX[i] == playerPosX)
					{
						zombieFlip[i] = false;
					}

					if (smallzombiesPosY[i] <= playerPosY)
					{
						if (smallzombiesPosX[i] != playerPosX)
						{
							smallzombiesPosY[i] += smallZombieVel / 2;
						}
						else
						{
							smallzombiesPosY[i] += smallZombieVel;
						}

					}

					else if (smallzombiesPosY[i] > playerPosY)
					{
						if (smallzombiesPosX[i] != playerPosX)
						{
							smallzombiesPosY[i] -= smallZombieVel / 2;
						}
						else
						{
							smallzombiesPosY[i] -= smallZombieVel;
						}
					}

					zClip = &zWalkRectSrc[zFrame / (DELTA)];


					smallZRectDst[i].x = int(smallzombiesPosX[i]);
					smallZRectDst[i].y = int(smallzombiesPosY[i]);



					if (!zombieFlip[i])
					{
						SDL_RenderCopy(ren, zombies, zClip, &smallZRectDst[i]);
					}

					else
					{
						SDL_RenderCopyEx(ren, zombies, zClip, &smallZRectDst[i], 0, NULL, SDL_FLIP_HORIZONTAL);
					}
				}

				else
				{
					zDeathFrames[i]++;

					if ((zDeathFrames[i] / DELTA) >= zAnims)
					{
						zDeathFrames[i] = 0;
						score += 5;
						Mix_PlayChannel(-1, hitSound, 0);
						zombieCounterInt--;
						changeCount = true;
						isZombieDying[i] = false;
						isRespawning[i] = true;
						smallZRectDst[i].x = rand() % SCREENWIDTH;

						randomSpawn = rand() % 2;

						if (randomSpawn == 0)
						{
							smallZRectDst[i].y = 0 - smallZRectDst[i].h;
						}

						else
						{
							smallZRectDst[i].y = SCREENHEIGHT;
						}
						

					}

					zDeathClips[i] = &zDeathRectSrc[zDeathFrames[i] / DELTA];

					if (!zombieFlip[i])
					{
						SDL_RenderCopy(ren, zombies, zDeathClips[i], &smallZRectDst[i]);
					}

					else
					{
						SDL_RenderCopyEx(ren, zombies, zDeathClips[i], &smallZRectDst[i], 0, NULL, SDL_FLIP_HORIZONTAL);
					}

				}
			}
		}

		
		
		for (int i = 0; i < ZOMBIESREN; i++)
		{
			if ((pRectDst.x >= smallZRectDst[i].x) && (pRectDst.x <= (smallZRectDst[i].x + smallZRectDst[i].w)) && (pRectDst.y >= smallZRectDst[i].y) && (pRectDst.y <= (smallZRectDst[i].y + smallZRectDst[i].h)))
			{
				hasLinkDied = true;
			}
		}

		if ((pRectDst.x >= bigZRectDst.x) && (pRectDst.x <= (bigZRectDst.x + bigZRectDst.w)) && (pRectDst.y >= bigZRectDst.y) && (pRectDst.y <= (bigZRectDst.y + bigZRectDst.h)))
		{
			hasLinkDied = true;
		}

		if (zombieCounterInt == 0) {
			levelCount++;
		}

		scoreChar = to_string(score);

		if (changeCount)
		{

			SDL_FreeSurface(counterSurface);
			SDL_DestroyTexture(counterTexture);

			counter << zombieCounterInt;

			counterSurface = TTF_RenderText_Solid(font, counter.str().c_str(), color);
			counterTexture = SDL_CreateTextureFromSurface(ren, counterSurface);

			

			changeCount = false;


		}

		
		SDL_RenderCopy(ren, counterTexture, NULL, &counterRect);
		counter.str("");
		

		SDL_RenderCopy(ren, zombieCountTexture, NULL, &zombieTextRect);
		SDL_RenderCopy(ren, player, pWalkClip, &pRectDst);

		if (isRunning)
		{
			SDL_RenderPresent(ren);
		}



	}


	doc.SaveFile("GameInfo.xml");

	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);

	SDL_FreeSurface(zombieCountSurface);
	SDL_FreeSurface(counterSurface);

	Mix_FreeMusic(bMusic);
	Mix_FreeChunk(throwSound);
	Mix_FreeChunk(hitSound);
	Mix_FreeChunk(zombieSound);

	throwSound = NULL;
	hitSound = NULL;
	zombieSound = NULL;

	bMusic = NULL;

	SDL_DestroyTexture(counterTexture);
	SDL_DestroyTexture(zombieCountTexture);
	SDL_DestroyTexture(player);
	SDL_DestroyTexture(bg);
	SDL_DestroyTexture(knife);
	SDL_DestroyTexture(arrow);
	SDL_DestroyTexture(shuriken);

	IMG_Quit();
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();




}