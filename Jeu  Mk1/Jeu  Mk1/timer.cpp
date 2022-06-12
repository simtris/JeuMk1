#include <SDL2/SDL.h>
#include <SDL2/SDL_version.h>
#include <string>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include "timer.h"

void timer::start()
{
	//On demarre le timer
	started = true;

	//On r�cup�re le temps du timer par d�faut qui sera le temps de d�part
	startTicks = SDL_GetTicks();
}

int timer::get_ticks()
{
	//Si le timer est en marche
	if (started == true)
	{

		//On retourne le temps courant ( qui est donc le temps d'arriv� ) moins le temps de d�part
		return SDL_GetTicks() - startTicks;

	}

	//Si le timer n'est pas en marche
	return 0;
}