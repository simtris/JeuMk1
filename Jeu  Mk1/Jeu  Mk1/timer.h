#include <SDL2/SDL.h>
#include <SDL2/SDL_version.h>
#include <string>
#include <string.h>
#include <iostream>
#include <stdio.h>


class timer
{
private:
	//Le temps quand le timer est lanc�
	int startTicks;

	//Le status du Timer
	bool started;

public:


	// D�finit le temps de d�part
	void start();

	//recup�re le nombre de millisecondes depuis que le timer a �t� lanc�
	int get_ticks();


};