#include "Survival.h"

int main(int argc, char *argv[]) {

	// make new game and run it
	Survival *newgame = new Survival();
	newgame->StartGame();
	// free memory
	delete newgame;

	return 0;
}
