
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <cstdio>
#include <fstream>
#include <ctime> // système de hasard
#include <cstdlib> // idem
#include "niveaux.h"
#include "personnage.h"
#include "armes.h"

FILE _iob[] = { *stdin, *stdout, *stderr };
extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}

#define largeurFenetre 1300
#define hauteurFenetre 700
#define largeurFond 8000

using namespace std;


int main(int argc, char** argv)
{

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_TIMER) != 0)
		std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;

	SDL_Window* pWindow = NULL;
	pWindow = SDL_CreateWindow("Jeu Mk1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, largeurFenetre, hauteurFenetre, SDL_WINDOW_SHOWN);

	SDL_Renderer *pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
	SDL_Surface *pFond; 

	pFond = SDL_LoadBMP("images/menu/menu2.bmp");
	SDL_Texture *pTextureM2 = SDL_CreateTextureFromSurface(pRenderer, pFond);
	pFond = SDL_LoadBMP("images/menu/sauvegarder.bmp");
	SDL_Texture *pTextureS = SDL_CreateTextureFromSurface(pRenderer, pFond);
	pFond = SDL_LoadBMP("images/menu/chargement.bmp");
	SDL_Texture *pTextureC = SDL_CreateTextureFromSurface(pRenderer, pFond);
	pFond = SDL_LoadBMP("images/menu/menu.bmp");
	SDL_Texture *pFTextureM = SDL_CreateTextureFromSurface(pRenderer, pFond);
	SDL_Rect Fdest = { 0, 0, largeurFenetre, hauteurFenetre };
	SDL_RenderCopy(pRenderer, pFTextureM, NULL, &Fdest);

	Perso perso(pRenderer, 0, false, largeurFenetre / 2 - 100 / 2, 0);
	
	int const tailleTabArme(100); 
	string tabArmes[tailleTabArme];

	std::string niveau("niveau1");

	Mix_AllocateChannels(10);


	for (int i(0); i < tailleTabArme; i++)
	{
		if (i <= 39)
			tabArmes[i] = "magnum";
		else if (i > 39 && i <= 59)
			tabArmes[i] = "a-caca-rantesept";
		else if (i > 59 && i <= 75)
			tabArmes[i] = "pistolait";
		else if (i > 75 && i <= 91)
			tabArmes[i] = "fusil a pompe";
		else if (i > 91 && i <= 97)
			tabArmes[i] = "lance-roquette";
		else if (i > 97)
			tabArmes[i] = "chat-crame";
	}


	bool quit(false);
	SDL_Event event;

	while (quit == false)
	{

		SDL_RenderPresent(pRenderer);


		const Uint8 *state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_ESCAPE])
		{
			cout << *state;
			quit = true;
		}
		 

		
		while (SDL_PollEvent(&event))	

		{
			
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (event.button.button == SDL_BUTTON_LEFT)
				{
				
					if ((event.button.x > 70) && (event.button.x < 490) && (event.button.y > 430) && (event.button.y < 570))
					{

						ifstream FluxI("images/menu/sauvegarde.txt", ios::in);

						FluxI.seekg(0, ios::end);
						int position = FluxI.tellg();

						if (position != 0) 
						{
							SDL_RenderCopy(pRenderer, pTextureM2, NULL, &Fdest);
							bool merde(true);

							while (merde == true)
							{
								SDL_RenderPresent(pRenderer);

								while (SDL_PollEvent(&event))
								{
									if (event.type == SDL_MOUSEBUTTONDOWN)
									{
										if (event.button.button == SDL_BUTTON_LEFT)
										{
											if ((event.button.x > 50) && (event.button.x < 180) && (event.button.y > 600) && (event.button.y < 665))
											{
												FluxI.seekg(0, ios::beg);
												FluxI >> niveau;
												FluxI.close();
												merde = false;
												break;

											}
											else if ((event.button.x > 370) && (event.button.x < 520) && (event.button.y > 610) && (event.button.y < 660))
											{
												merde = false;
												break;

											}
										}
									}
								}
							}
						}

						while (quit == false)
						{

							SDL_RenderCopy(pRenderer, pTextureC, NULL, &Fdest);
							SDL_RenderPresent(pRenderer);

							

							if (niveau == "niveau1")
								niveau1(pWindow, pRenderer, perso, tabArmes, tailleTabArme, quit);
							if (niveau == "niveau2")
								niveau2(pWindow, pRenderer, perso, tabArmes, tailleTabArme, quit);
							if (niveau == "niveau3")
								niveau3(pWindow, pRenderer, perso, tabArmes, tailleTabArme, quit);
							if (niveau == "niveau4")
								niveau4(pWindow, pRenderer, perso, tabArmes, tailleTabArme, quit);
							if (niveau == "niveau5")
								niveau5(pWindow, pRenderer, perso, tabArmes, tailleTabArme, quit);
							if (niveau == "niveau6")
								niveau6(pWindow, pRenderer, perso, tabArmes, tailleTabArme, quit);
							if (niveau == "niveau7")
								niveau7(pWindow, pRenderer, perso, tabArmes, tailleTabArme, quit);
							if (niveau == "niveau8")
								niveau8(pWindow, pRenderer, perso, tabArmes, tailleTabArme, quit);
							if (niveau == "niveau9")
								niveau9(pWindow, pRenderer, perso, tabArmes, tailleTabArme, quit);
							if (niveau == "XxXOverKillerDeath3000AlphaOmegaXxX")
								combatFinal(pWindow, pRenderer, perso, tabArmes, tailleTabArme, quit);

							if (quit == true)
							{
								SDL_RenderCopy(pRenderer, pTextureS, NULL, &Fdest);
								quit = false;

								while (quit == false)
								{
									SDL_RenderPresent(pRenderer);

									while (SDL_PollEvent(&event))
									{
										if (event.type == SDL_MOUSEBUTTONDOWN)
										{
											if (event.button.button == SDL_BUTTON_LEFT)
											{
												if ((event.button.x > 170) && (event.button.x < 364) && (event.button.y > 664) && (event.button.y < 764))
												{
													ofstream FluxO("images/menu/sauvegarde.txt", ios::out);

													if (niveau == "niveau1")
														FluxO << niveau;
													if (niveau == "niveau2")
														FluxO << niveau;
													if (niveau == "niveau3")
														FluxO << niveau;
													if (niveau == "niveau4")
														FluxO << niveau;
													if (niveau == "niveau5")
														FluxO << niveau;
													if (niveau == "niveau6")
														FluxO << niveau;
													if (niveau == "niveau7")
														FluxO << niveau;
													if (niveau == "niveau8")
														FluxO << niveau;
													if (niveau == "niveau9")
														FluxO << niveau;
													if (niveau == "XxXOverKillerDeath3000AlphaOmegaXxX")
														FluxO << niveau;

													FluxO.close();

													quit = true;
													break;
												}
												else if ((event.button.x > 860) && (event.button.x < 1080) && (event.button.y > 590) && (event.button.y < 670))
												{
													quit = true;
													break;
												}
											}
										}
									}
								}

								event.type = NULL;
								break;
							}
							else if (niveau == "niveau1")
								niveau = "niveau2";
							else if (niveau == "niveau2")
								niveau = "niveau3";
							else if (niveau == "niveau3")
								niveau = "niveau4";
							else if (niveau == "niveau4")
								niveau = "niveau5";
							else if (niveau == "niveau5")
								niveau = "niveau6";
							else if (niveau == "niveau6")
								niveau = "niveau7";
							else if (niveau == "niveau7")
								niveau = "niveau8";
							else if (niveau == "niveau8")
								niveau = "niveau9";
							else if (niveau == "niveau9")
								niveau = "XxXOverKillerDeath3000AlphaOmegaXxX";

							if (quit == true)
								break;
							
						}

						event.type = NULL;
						FluxI.close();

						//break;
					}
				}
			}
		}

		
	}

	SDL_Quit();

	return 0;
	
}
