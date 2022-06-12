#include <SDL2/SDL.h>
#include <SDL2/SDL_version.h>
#include <string>
#include <string.h>
#include <iostream>
#include <stdio.h>


class timer
{
private:
	//Le temps quand le timer est lancé
	int startTicks;

	//Le status du Timer
	bool started;

public:


	// Définit le temps de départ
	void start();

	//recupére le nombre de millisecondes depuis que le timer a été lancé
	int get_ticks();


};