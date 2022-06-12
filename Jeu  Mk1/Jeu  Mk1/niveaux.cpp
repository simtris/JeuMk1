#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <ctime> // système de hasard
#include <cstdlib> // idem
#include "personnage.h"
#include "armes.h"
#include "niveaux.h"

#define largeurFenetre 1300
#define hauteurFenetre 700
#define largeurFond 8000

using namespace std;

bool checkCollision(SDL_Rect A, SDL_Rect B)
{
	int gaucheA, gaucheB;
	int droiteA, droiteB;
	int hautA, hautB;
	int basA, basB;

	//Calcul les cotes du rectangle A
	gaucheA = A.x;
	droiteA = A.x + A.w;
	hautA = A.y;
	basA = A.y + A.h;

	//Calcul les cotes du rectangle B
	gaucheB = B.x;
	droiteB = B.x + B.w;
	hautB = B.y;
	basB = B.y + B.h;



	if (basA <= hautB) // Dans ce cas pas de collision
		return false;

	if (hautA >= basB) // idem
		return false;

	if (gaucheA >= droiteB) // idem
		return false;

	if (droiteA <= gaucheB) // idem
		return false;

	return true;
}

void niveau1(SDL_Window *pWindow, SDL_Renderer *pRenderer, Perso &perso, string tabArmes[], int tailleTabArme, bool &overQuit)
{

	SDL_Surface *pFond;
	pFond = SDL_LoadBMP("images/niveaux/foret/fond.bmp");
	SDL_Texture *pFTexture = SDL_CreateTextureFromSurface(pRenderer, pFond);
	SDL_Rect Fdest = { 0, 0, largeurFond, hauteurFenetre };

	SDL_Surface *pSprites = SDL_LoadBMP("images/sprites/boiteArme/boiteArme.bmp");
	Uint32 colorkey = SDL_MapRGB(pSprites->format, 255, 255, 255);
	SDL_SetColorKey(pSprites, SDL_RLEACCEL | SDL_TRUE, colorkey);
	SDL_Texture *pTextureSprites = SDL_CreateTextureFromSurface(pRenderer, pSprites);
	SDL_Rect destCase1 = { 1000, 555, 35, 42 };

	SDL_Surface *pPlat = SDL_LoadBMP("images/niveaux/foret/platforme.bmp");
	SDL_Texture *pTexturePlat = SDL_CreateTextureFromSurface(pRenderer, pPlat);

	int const tailletabCine(9);
	SDL_Texture *TabCine[tailletabCine];
	SDL_Surface *Cine;
	Cine = SDL_LoadBMP("images/niveaux/foret/cinematiques2/1.bmp");
	TabCine[0] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/foret/cinematiques2/2.bmp");
	TabCine[1] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/foret/cinematiques2/3.bmp");
	TabCine[2] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/foret/cinematiques2/4.bmp");
	TabCine[3] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/foret/cinematiques2/5.bmp");
	TabCine[4] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/foret/cinematiques2/6.bmp");
	TabCine[5] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/foret/cinematiques2/7.bmp");
	TabCine[6] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/foret/cinematiques2/8.bmp");
	TabCine[7] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/foret/cinematiques2/9.bmp");
	TabCine[8] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	
	int const nbreEnnemisBase(7);
	Perso *tabEnnemis[nbreEnnemisBase];


	int const nbrePlatform(7);
	SDL_Rect tabPlatform[nbrePlatform];

	for (int i(0); i < nbrePlatform; i++)
	{
		tabPlatform[i].w = 347;
		tabPlatform[i].h = 44;
	}


	tabEnnemis[0] = new Perso(pRenderer, 100, true, 1440, 400, "bucherons canadiens");
	tabEnnemis[1] = new Perso(pRenderer, 100, true, 2000, 0, "bucherons canadiens");
	tabEnnemis[2] = new Perso(pRenderer, 100, true, 2560, 0, "bucherons canadiens");
	tabEnnemis[3] = new Perso(pRenderer, 100, true, 3380, 0, "bucherons canadiens");
	tabEnnemis[4] = new Perso(pRenderer, 100, true, 3700, 400, "bucherons canadiens");
	tabEnnemis[5] = new Perso(pRenderer, 100, true, 4650, 400, "bucherons canadiens");
	tabEnnemis[6] = new Perso(pRenderer, 100, true, 4810, 0, "bucherons canadiens");


	SDL_Event event;
	for (int i(0); i < tailletabCine; i++)
	{
		SDL_RenderCopy(pRenderer, TabCine[i], NULL, NULL);
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
						if ((event.button.x > 0) && (event.button.x < largeurFenetre) && (event.button.y > 0) && (event.button.y < hauteurFenetre))
						{
							merde = false;
							break;

						}
					}
				}
			}
		}
	}

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

	Mix_Music * muuuuuuuusiiiiiiiiique;
	muuuuuuuusiiiiiiiiique = Mix_LoadMUS("musique/musique.mp3");
	Mix_VolumeMusic(MIX_MAX_VOLUME);

	Mix_PlayMusic(muuuuuuuusiiiiiiiiique, -1);

	do // a chaque mort
	{
		Mix_RewindMusic();

		int Scrolling(0);
		bool Scrolle(false); // false : le perso se déplace, true : le fond défile
		timer fps;
		int imageParSecondes(60);
		bool quit(false);
		bool niveauFinit(false);
		bool case1estUtilisee(false);

		Fdest = { 0, 0, largeurFond, hauteurFenetre };
		destCase1 = { 1000, 555, 35, 42 };


		for (int i = 0; i < nbreEnnemisBase; i++)
			tabEnnemis[i]->setPv(140);

		tabEnnemis[0]->setDest(1440, 400);
		tabEnnemis[1]->setDest(2000, 0);
		tabEnnemis[2]->setDest(2560, 0);
		tabEnnemis[3]->setDest(3380, 0);
		tabEnnemis[4]->setDest(3700, 400);
		tabEnnemis[5]->setDest(4650, 400);
		tabEnnemis[6]->setDest(4810, 0);


		perso.ramasserArme(pRenderer, "rein");
		perso.setDest(largeurFenetre / 2 - 100 / 2, 0);
		perso.setPv(450);
		perso.reinitialMouvement();

		Mix_RewindMusic();

		tabPlatform[0].x = 1440;
		tabPlatform[0].y = 355;

		tabPlatform[1].x = 2000;
		tabPlatform[1].y = 215;

		tabPlatform[2].x = 2560;
		tabPlatform[2].y = 355;

		tabPlatform[3].x = 3380;
		tabPlatform[3].y = 355;

		tabPlatform[4].x = 3930;
		tabPlatform[4].y = 355;

		tabPlatform[5].x = 4810;
		tabPlatform[5].y = 215;

		tabPlatform[6].x = 5330;
		tabPlatform[6].y = 355;
		

		while (quit == false ) // a chaque image
		{
			fps.start();

			perso.recuperation_event(Scrolling, nbrePlatform, tabPlatform);

			for (int i = 0; i < nbreEnnemisBase; i++)
			{
				if (tabEnnemis[i]->getEstVivant() == true)
					tabEnnemis[i]->IAtiser(perso.getDest(), Scrolle, (perso.getStatus()), nbrePlatform, tabPlatform, tabEnnemis, nbreEnnemisBase, i, 250);
			}


			// ------------------------------------------------Scrolling-------------------------------------------------------------------------------------------------

			Fdest.x -= Scrolling;
			if (case1estUtilisee == false)
				destCase1.x -= Scrolling; // deplacement des boite d'arme

			for (int i(0); i < nbrePlatform; i++)
				tabPlatform[i].x -= Scrolling;


			if (Scrolling == 0)
				Scrolle = false;
			else
				Scrolle = true;



			if (Fdest.x < (-(Fdest.w) + largeurFenetre))
			{
				Fdest.x += Scrolling;
				if (case1estUtilisee == false)
					destCase1.x += Scrolling;

				for (int i(0); i < nbrePlatform; i++)
					tabPlatform[i].x += Scrolling;

				Scrolle = false;

				niveauFinit = true;
			}

			if (Fdest.x > 0)
			{
				Fdest.x += Scrolling;
				if (case1estUtilisee == false)
					destCase1.x += Scrolling;

				for (int i(0); i < nbrePlatform; i++)
					tabPlatform[i].x += Scrolling;

				Scrolle = false;
			}

			// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------
			if (case1estUtilisee == false)
			{
				if (checkCollision(destCase1, perso.getDest()) == true)	// detection collision perso/boite d'arme
				{
					srand(time(0)); // initialisation de la génération de nombre aléatoire
					int nombreAleatoire;
					nombreAleatoire = rand() % tailleTabArme;

					perso.ramasserArme(pRenderer, tabArmes[nombreAleatoire]);

					case1estUtilisee = true;
				}
			}

			if (perso.getAUneArme() == true)
			{
				for (int i(0); i < nbrePlatform; i++)  // detection collision proj perso/platform
				{
					unsigned int j(0);
					j = 0;

					for (j; j < (perso.getArme()->getDestProj().size()); j++)
					{
						if (checkCollision(tabPlatform[i], perso.getArme()->getDestProj()[j]) == true)
						{
							std::vector<SDL_Rect>::iterator iter = perso.getArme()->getDestProj().begin(); // effacage de la case contenant le rect du tir qui a touché

							for (unsigned int l(0); l < j; l++)
								iter++;

							perso.getArme()->getDestProj().erase(iter);
						}
					}
				}
			}


			for (int k(0); k < nbreEnnemisBase; k++)
			{
				if (tabEnnemis[k]->getAUneArme() == true)
				{
					for (int i(0); i < nbrePlatform; i++)  // detection collision proj ennemi/platform
					{
						unsigned int j(0);
						j = 0;

						for (j; j < (tabEnnemis[k]->getArme()->getDestProj().size()); j++)
						{
							if (checkCollision(tabPlatform[i], tabEnnemis[k]->getArme()->getDestProj()[j]) == true)
							{
								std::vector<SDL_Rect>::iterator iter = tabEnnemis[k]->getArme()->getDestProj().begin(); // effacage de la case contenant le rect du tir qui a touché

								for (unsigned int l(0); l < j; l++)
									iter++;

								tabEnnemis[k]->getArme()->getDestProj().erase(iter);
							}
						}
					}
				}
			}

			if (perso.getAUneArme() == true)
			{
				for (int i(0); i < nbreEnnemisBase; i++)  // detection collision entre proj perso/ennemi
				{
					unsigned int j(0);
					j = 0;

					for (j; j < (perso.getArme()->getDestProj().size()); j++)
					{
						if (tabEnnemis[i]->getEstVivant() == true)
						{
							if (checkCollision(tabEnnemis[i]->getDest(), perso.getArme()->getDestProj()[j]) == true)
								perso.infligerDegats(tabEnnemis[i], j);
						}
					}
				}
			}


			for (int i(0); i < nbreEnnemisBase; i++)  // detection collision entre proj ennemi/perso
			{
				if (tabEnnemis[i]->getAUneArme() == true)
				{
					unsigned int j(0);
					j = 0;

					for (j; j < (tabEnnemis[i]->getArme()->getDestProj().size()); j++)
					{
						if (checkCollision(perso.getDest(), (tabEnnemis[i]->getArme()->getDestProj())[j]) == true)
							tabEnnemis[i]->infligerDegats(&perso, j);

					}
				}
			}

			SDL_RenderCopy(pRenderer, pFTexture, NULL, &Fdest); // affichage fond
			for (int i(0); i < nbrePlatform; i++) // affichage plateformes
				SDL_RenderCopy(pRenderer, pTexturePlat, NULL, &tabPlatform[i]);
			if (case1estUtilisee == false) // affichage case arme
				SDL_RenderCopy(pRenderer, pTextureSprites, NULL, &destCase1);


			for (int i = 0; i < nbreEnnemisBase; i++) // Affichage ennemis
			{
				if (tabEnnemis[i]->getEstVivant() == true)
					tabEnnemis[i]->show(pRenderer, Scrolle, (perso.getStatus()), nbrePlatform, tabPlatform, Scrolling);
			}

			perso.show(pRenderer, Scrolle, (perso.getStatus()), nbrePlatform, tabPlatform, Scrolling); // affichage perso

			SDL_RenderPresent(pRenderer);

			const Uint8 *state = SDL_GetKeyboardState(NULL);
			if (state[SDL_SCANCODE_ESCAPE])
			{
				overQuit = true;
			}

			while (fps.get_ticks() < 1000 / imageParSecondes)
			{
				//...
			}

			if (perso.getEstVivant() == false)
			{
				for (int i(0); i < nbreEnnemisBase; i++)
					delete tabEnnemis[i]->getArme();
				for (int i(0); i < nbreEnnemisBase; i++)
					tabEnnemis[i]->ramasserArme(pRenderer, "hache");

				quit = true;
			}

			if (overQuit == true || niveauFinit == true)
			{
				for (int i = 0; i < nbreEnnemisBase; i++)
				{
					delete tabEnnemis[i];
					tabEnnemis[i] = nullptr;
				}

				quit = true;
			}

		}

	} while (perso.getEstVivant() == false);

	return;
}

void niveau2(SDL_Window *pWindow, SDL_Renderer *pRenderer, Perso &perso, string tabArmes[], int tailleTabArme, bool &overQuit)
{

	SDL_Surface *pFond;
	pFond = SDL_LoadBMP("images/niveaux/laboratoire secret/fond.bmp");
	SDL_Texture *pFTexture = SDL_CreateTextureFromSurface(pRenderer, pFond);
	SDL_Rect Fdest = { 0, 0, largeurFond, hauteurFenetre };

	SDL_Surface *pSprites = SDL_LoadBMP("images/sprites/boiteArme/boiteArme.bmp");
	Uint32 colorkey = SDL_MapRGB(pSprites->format, 255, 255, 255);
	SDL_SetColorKey(pSprites, SDL_RLEACCEL | SDL_TRUE, colorkey);
	SDL_Texture *pTextureSprites = SDL_CreateTextureFromSurface(pRenderer, pSprites);
	SDL_Rect destCase1 = { 1000, 555, 35, 42 };

	SDL_Surface *pPlat = SDL_LoadBMP("images/niveaux/laboratoire secret/platforme.bmp");
	SDL_Texture *pTexturePlat = SDL_CreateTextureFromSurface(pRenderer, pPlat);


	int const tailletabCine(14);
	SDL_Texture *TabCine[tailletabCine];
	SDL_Surface *Cine;
	Cine = SDL_LoadBMP("images/niveaux/laboratoire secret/cinematiques2/1.bmp");
	TabCine[0] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/laboratoire secret/cinematiques2/2.bmp");
	TabCine[1] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/laboratoire secret/cinematiques2/3.bmp");
	TabCine[2] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/laboratoire secret/cinematiques2/4.bmp");
	TabCine[3] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/laboratoire secret/cinematiques2/5.bmp");
	TabCine[4] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/laboratoire secret/cinematiques2/6.bmp");
	TabCine[5] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/laboratoire secret/cinematiques2/7.bmp");
	TabCine[6] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/laboratoire secret/cinematiques2/8.bmp");
	TabCine[7] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/laboratoire secret/cinematiques2/9.bmp");
	TabCine[8] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/laboratoire secret/cinematiques2/10.bmp");
	TabCine[9] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/laboratoire secret/cinematiques2/11.bmp");
	TabCine[10] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/laboratoire secret/cinematiques2/12.bmp");
	TabCine[11] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/laboratoire secret/cinematiques2/13.bmp");
	TabCine[12] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/laboratoire secret/cinematiques2/14.bmp");
	TabCine[13] = SDL_CreateTextureFromSurface(pRenderer, Cine);

	int const nbreEnnemisBase(9);
	Perso *tabEnnemis[nbreEnnemisBase];

	int const nbrePlatform(6);
	SDL_Rect tabPlatform[nbrePlatform];

	for (int i(0); i < nbrePlatform; i++)
	{
		tabPlatform[i].w = 347;
		tabPlatform[i].h = 44;
	}

	tabEnnemis[0] = new Perso(pRenderer, 100, true, 1725, 0, "scientifiques");
	tabEnnemis[1] = new Perso(pRenderer, 100, true, 1725, 400, "scientifiques");
	tabEnnemis[2] = new Perso(pRenderer, 100, true, 2930, 0, "scientifiques");
	tabEnnemis[3] = new Perso(pRenderer, 100, true, 3200, 400, "scientifiques");
	tabEnnemis[4] = new Perso(pRenderer, 100, true, 3400, 0, "scientifiques");
	tabEnnemis[5] = new Perso(pRenderer, 100, true, 3900, 400, "scientifiques");
	tabEnnemis[6] = new Perso(pRenderer, 100, true, 4970, 400, "scientifiques");
	tabEnnemis[7] = new Perso(pRenderer, 100, true, 4970, 0, "scientifiques");
	tabEnnemis[8] = new Perso(pRenderer, 100, true, 5440, 400, "scientifiques");

	SDL_Event event;
	for (int i(0); i < tailletabCine; i++)
	{
		SDL_RenderCopy(pRenderer, TabCine[i], NULL, NULL);
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
						if ((event.button.x > 0) && (event.button.x < largeurFenetre) && (event.button.y > 0) && (event.button.y < hauteurFenetre))
						{
							merde = false;
							break;

						}
					}
				}
			}
		}
	}

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

	Mix_Music * muuuuuuuusiiiiiiiiique;
	muuuuuuuusiiiiiiiiique = Mix_LoadMUS("musique/musique.mp3");
	Mix_VolumeMusic(MIX_MAX_VOLUME);

	Mix_PlayMusic(muuuuuuuusiiiiiiiiique, -1);

	do
	{
		Mix_RewindMusic();
		
		int Scrolling(0);
		bool Scrolle(false); // false : le perso se déplace, true : le fond défile
		timer fps;
		int imageParSecondes(60);
		bool quit(false);
		bool niveauFinit(false);
		bool case1estUtilisee(false);

		Fdest = { 0, 0, largeurFond, hauteurFenetre };
		destCase1 = { 1000, 555, 35, 42 };
		
		for (int i = 0; i < nbreEnnemisBase; i++)
			tabEnnemis[i]->setPv(140);

		tabEnnemis[0]->setDest(1725, 0);
		tabEnnemis[1]->setDest(1725, 400);
		tabEnnemis[2]->setDest(2930, 0);
		tabEnnemis[3]->setDest(3200, 400);
		tabEnnemis[4]->setDest(3400, 0);
		tabEnnemis[5]->setDest(3900, 400);
		tabEnnemis[6]->setDest(4970, 400);
		tabEnnemis[7]->setDest(4970, 0);
		tabEnnemis[8]->setDest(5440, 400);


		perso.ramasserArme(pRenderer, "rein");
		perso.setDest(largeurFenetre / 2 - 100 / 2, 0);
		perso.setPv(450);
		perso.reinitialMouvement();
	

		tabPlatform[0].x = 1725;
		tabPlatform[0].y = 215;

		tabPlatform[1].x = 2930;
		tabPlatform[1].y = 355;

		tabPlatform[2].x = 3400;
		tabPlatform[2].y = 215;

		tabPlatform[3].x = 3900;
		tabPlatform[3].y = 355;

		tabPlatform[4].x = 4970;
		tabPlatform[4].y = 355;

		tabPlatform[5].x = 5440;
		tabPlatform[5].y = 215;



		while (quit == false)
		{
			fps.start();

			perso.recuperation_event(Scrolling, nbrePlatform, tabPlatform);

			for (int i = 0; i < nbreEnnemisBase; i++)
			{
				if (tabEnnemis[i]->getEstVivant() == true)
					tabEnnemis[i]->IAtiser(perso.getDest(), Scrolle, (perso.getStatus()), nbrePlatform, tabPlatform, tabEnnemis, nbreEnnemisBase, i, 250);
			}


			// ------------------------------------------------Scrolling-------------------------------------------------------------------------------------------------

			Fdest.x -= Scrolling;
			if (case1estUtilisee == false)
				destCase1.x -= Scrolling; // deplacement des boite d'arme

			for (int i(0); i < nbrePlatform; i++)
				tabPlatform[i].x -= Scrolling;


			if (Scrolling == 0)
				Scrolle = false;
			else
				Scrolle = true;



			if (Fdest.x < (-(Fdest.w) + largeurFenetre))
			{
				Fdest.x += Scrolling;
				if (case1estUtilisee == false)
					destCase1.x += Scrolling;

				for (int i(0); i < nbrePlatform; i++)
					tabPlatform[i].x += Scrolling;

				Scrolle = false;

				niveauFinit = true;
			}

			if (Fdest.x > 0)
			{
				Fdest.x += Scrolling;
				if (case1estUtilisee == false)
					destCase1.x += Scrolling;

				for (int i(0); i < nbrePlatform; i++)
					tabPlatform[i].x += Scrolling;

				Scrolle = false;
			}

			// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------
			if (case1estUtilisee == false)
			{
				if (checkCollision(destCase1, perso.getDest()) == true)	// detection collision perso/boite d'arme
				{
					srand(time(0)); // initialisation de la génération de nombre aléatoire
					int nombreAleatoire;
					nombreAleatoire = rand() % tailleTabArme;

					perso.ramasserArme(pRenderer, tabArmes[nombreAleatoire]);

					case1estUtilisee = true;
				}
			}

			if (perso.getAUneArme() == true)
			{
				for (int i(0); i < nbrePlatform; i++)  // detection collision proj perso/platform
				{
					unsigned int j(0);
					j = 0;

					for (j; j < (perso.getArme()->getDestProj().size()); j++)
					{
						if (checkCollision(tabPlatform[i], perso.getArme()->getDestProj()[j]) == true)
						{
							std::vector<SDL_Rect>::iterator iter = perso.getArme()->getDestProj().begin(); // effacage de la case contenant le rect du tir qui a touché

							for (unsigned int l(0); l < j; l++)
								iter++;

							perso.getArme()->getDestProj().erase(iter);
						}
					}
				}
			}


			for (int k(0); k < nbreEnnemisBase; k++)
			{
				if (tabEnnemis[k]->getAUneArme() == true)
				{
					for (int i(0); i < nbrePlatform; i++)  // detection collision proj perso/platform
					{
						unsigned int j(0);
						j = 0;

						for (j; j < (tabEnnemis[k]->getArme()->getDestProj().size()); j++)
						{
							if (checkCollision(tabPlatform[i], tabEnnemis[k]->getArme()->getDestProj()[j]) == true)
							{
								std::vector<SDL_Rect>::iterator iter = tabEnnemis[k]->getArme()->getDestProj().begin(); // effacage de la case contenant le rect du tir qui a touché

								for (unsigned int l(0); l < j; l++)
									iter++;

								tabEnnemis[k]->getArme()->getDestProj().erase(iter);
							}
						}
					}
				}
			}

			if (perso.getAUneArme() == true)
			{
				for (int i(0); i < nbreEnnemisBase; i++)  // detection collision entre proj perso/ennemi
				{
					unsigned int j(0);
					j = 0;

					for (j; j < (perso.getArme()->getDestProj().size()); j++)
					{
						if (tabEnnemis[i]->getEstVivant() == true)
						{
							if (checkCollision(tabEnnemis[i]->getDest(), perso.getArme()->getDestProj()[j]) == true)
								perso.infligerDegats(tabEnnemis[i], j);
						}
					}
				}
			}


			for (int i(0); i < nbreEnnemisBase; i++)  // detection collision entre proj ennemi/perso
			{
				if (tabEnnemis[i]->getAUneArme() == true)
				{
					unsigned int j(0);
					j = 0;

					for (j; j < (tabEnnemis[i]->getArme()->getDestProj().size()); j++)
					{
						if (checkCollision(perso.getDest(), (tabEnnemis[i]->getArme()->getDestProj())[j]) == true)
							tabEnnemis[i]->infligerDegats(&perso, j);

					}
				}
			}

			SDL_RenderCopy(pRenderer, pFTexture, NULL, &Fdest); // affichage fond
			for (int i(0); i < nbrePlatform; i++) // affichage plateformes
				SDL_RenderCopy(pRenderer, pTexturePlat, NULL, &tabPlatform[i]);
			if (case1estUtilisee == false) // affichage case arme
				SDL_RenderCopy(pRenderer, pTextureSprites, NULL, &destCase1);


			for (int i = 0; i < nbreEnnemisBase; i++) // Affichage ennemis
			{
				if (tabEnnemis[i]->getEstVivant() == true)
					tabEnnemis[i]->show(pRenderer, Scrolle, (perso.getStatus()), nbrePlatform, tabPlatform, Scrolling);
			}

			perso.show(pRenderer, Scrolle, (perso.getStatus()), nbrePlatform, tabPlatform, Scrolling); // affichage perso

			SDL_RenderPresent(pRenderer);

			const Uint8 *state = SDL_GetKeyboardState(NULL);
			if (state[SDL_SCANCODE_ESCAPE])
			{
				overQuit = true;
			}

			while (fps.get_ticks() < 1000 / imageParSecondes)
			{
				//...
			}

			if (perso.getEstVivant() == false)
			{
				for (int i(0); i < nbreEnnemisBase; i++)
					delete tabEnnemis[i]->getArme();
				for (int i(0); i < nbreEnnemisBase; i++)
					tabEnnemis[i]->ramasserArme(pRenderer, "pistolet cool");

				quit = true;
			}

			if (overQuit == true || niveauFinit == true)
			{
				for (int i = 0; i < nbreEnnemisBase; i++)
				{
					delete tabEnnemis[i];
					tabEnnemis[i] = nullptr;
				}

				quit = true;
			}

		}

	} while (perso.getEstVivant() == false);

	return;
}

void niveau3(SDL_Window *pWindow, SDL_Renderer *pRenderer, Perso &perso, string tabArmes[], int tailleTabArme, bool &overQuit)
{

	SDL_Surface *pFond;
	pFond = SDL_LoadBMP("images/niveaux/prehistoire/fond.bmp");
	SDL_Texture *pFTexture = SDL_CreateTextureFromSurface(pRenderer, pFond);
	SDL_Rect Fdest = { 0, 0, largeurFond, hauteurFenetre };

	SDL_Surface *pSprites = SDL_LoadBMP("images/sprites/boiteArme/boiteArme.bmp");
	Uint32 colorkey = SDL_MapRGB(pSprites->format, 255, 255, 255);
	SDL_SetColorKey(pSprites, SDL_RLEACCEL | SDL_TRUE, colorkey);
	SDL_Texture *pTextureSprites = SDL_CreateTextureFromSurface(pRenderer, pSprites);
	SDL_Rect destCase1 = { 1000, 555, 35, 42 };

	SDL_Surface *pPlat = SDL_LoadBMP("images/niveaux/prehistoire/platforme.bmp");
	Uint32 colorkey2 = SDL_MapRGB(pPlat->format, 255, 255, 255);
	SDL_SetColorKey(pPlat, SDL_RLEACCEL | SDL_TRUE, colorkey2);
	SDL_Texture *pTexturePlat = SDL_CreateTextureFromSurface(pRenderer, pPlat);

	int const tailletabCine(14);
	SDL_Texture *TabCine[tailletabCine];
	SDL_Surface *Cine;
	Cine = SDL_LoadBMP("images/niveaux/prehistoire/cinematiques2/1.bmp");
	TabCine[0] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/prehistoire/cinematiques2/2.bmp");
	TabCine[1] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/prehistoire/cinematiques2/3.bmp");
	TabCine[2] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/prehistoire/cinematiques2/4.bmp");
	TabCine[3] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/prehistoire/cinematiques2/5.bmp");
	TabCine[4] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/prehistoire/cinematiques2/6.bmp");
	TabCine[5] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/prehistoire/cinematiques2/7.bmp");
	TabCine[6] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/prehistoire/cinematiques2/8.bmp");
	TabCine[7] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/prehistoire/cinematiques2/9.bmp");
	TabCine[8] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/prehistoire/cinematiques2/10.bmp");
	TabCine[9] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/prehistoire/cinematiques2/11.bmp");
	TabCine[10] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/prehistoire/cinematiques2/12.bmp");
	TabCine[11] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/prehistoire/cinematiques2/13.bmp");
	TabCine[12] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/prehistoire/cinematiques2/14.bmp");
	TabCine[13] = SDL_CreateTextureFromSurface(pRenderer, Cine);


	int const nbreEnnemisBase(11);
	Perso *tabEnnemis[nbreEnnemisBase];


	int const nbrePlatform(7);
	SDL_Rect tabPlatform[nbrePlatform];

	for (int i(0); i < nbrePlatform; i++)
	{
		tabPlatform[i].w = 347;
		tabPlatform[i].h = 44;
	}

	tabEnnemis[0] = new Perso(pRenderer, 100, true, 1840, 0, "hommes prehistoriques");
	tabEnnemis[1] = new Perso(pRenderer, 100, true, 2200, 400, "hommes prehistoriques");
	tabEnnemis[2] = new Perso(pRenderer, 100, true, 2460, 0, "hommes prehistoriques");
	tabEnnemis[3] = new Perso(pRenderer, 100, true, 3400, 400, "hommes prehistoriques");
	tabEnnemis[4] = new Perso(pRenderer, 100, true, 3520, 0, "hommes prehistoriques");
	tabEnnemis[5] = new Perso(pRenderer, 100, true, 4040, 0, "hommes prehistoriques");
	tabEnnemis[6] = new Perso(pRenderer, 100, true, 4350, 400, "hommes prehistoriques");
	tabEnnemis[7] = new Perso(pRenderer, 100, true, 4590, 0, "hommes prehistoriques");
	tabEnnemis[8] = new Perso(pRenderer, 100, true, 5470, 400, "hommes prehistoriques");
	tabEnnemis[9] = new Perso(pRenderer, 100, true, 5900, 400, "hommes prehistoriques");
	tabEnnemis[10] = new Perso(pRenderer, 100, true, 6010, 0, "hommes prehistoriques");

	SDL_Event event;
	for (int i(0); i < tailletabCine; i++)
	{
		SDL_RenderCopy(pRenderer, TabCine[i], NULL, NULL);
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
						if ((event.button.x > 0) && (event.button.x < largeurFenetre) && (event.button.y > 0) && (event.button.y < hauteurFenetre))
						{
							merde = false;
							break;

						}
					}
				}
			}
		}
	}

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

	Mix_Music * muuuuuuuusiiiiiiiiique;
	muuuuuuuusiiiiiiiiique = Mix_LoadMUS("musique/musique.mp3");
	Mix_VolumeMusic(MIX_MAX_VOLUME);

	Mix_PlayMusic(muuuuuuuusiiiiiiiiique, -1);

	do
	{
		Mix_RewindMusic();
	
		int Scrolling(0);
		bool Scrolle(false); // false : le perso se déplace, true : le fond défile
		timer fps;
		int imageParSecondes(60);
		bool quit(false);
		bool niveauFinit(false);
		bool case1estUtilisee(false);

		Fdest = { 0, 0, largeurFond, hauteurFenetre };
		destCase1 = { 1000, 555, 35, 42 };


		for (int i = 0; i < nbreEnnemisBase; i++)
			tabEnnemis[i]->setPv(100);

		tabEnnemis[0]->setDest(1840, 0);
		tabEnnemis[1]->setDest(2200, 400);
		tabEnnemis[2]->setDest(2460, 0);
		tabEnnemis[3]->setDest(3400, 400);
		tabEnnemis[4]->setDest(3520, 0);
		tabEnnemis[5]->setDest(4040, 0);
		tabEnnemis[6]->setDest(4350, 400);
		tabEnnemis[7]->setDest(4590, 0);
		tabEnnemis[8]->setDest(5470, 400);
		tabEnnemis[9]->setDest(5900, 400);
		tabEnnemis[10]->setDest(6010, 0);


		perso.ramasserArme(pRenderer, "rein");
		perso.setDest(largeurFenetre / 2 - 100 / 2, 0);
		perso.setPv(450);
		perso.reinitialMouvement();


		tabPlatform[0].x = 1840;
		tabPlatform[0].y = 215;

		tabPlatform[1].x = 2460;
		tabPlatform[1].y = 215;

		tabPlatform[2].x = 3520;
		tabPlatform[2].y = 355;

		tabPlatform[3].x = 4040;
		tabPlatform[3].y = 355;

		tabPlatform[4].x = 4590;
		tabPlatform[4].y = 215;

		tabPlatform[5].x = 5470;
		tabPlatform[5].y = 355;

		tabPlatform[6].x = 6010;
		tabPlatform[6].y = 215;
		

		while (quit == false)
		{
			fps.start();

			perso.recuperation_event(Scrolling, nbrePlatform, tabPlatform);

			for (int i = 0; i < nbreEnnemisBase; i++)
			{
				if (tabEnnemis[i]->getEstVivant() == true)
					tabEnnemis[i]->IAtiser(perso.getDest(), Scrolle, (perso.getStatus()), nbrePlatform, tabPlatform, tabEnnemis, nbreEnnemisBase, i, 250);
			}


			// ------------------------------------------------Scrolling-------------------------------------------------------------------------------------------------

			Fdest.x -= Scrolling;
			if (case1estUtilisee == false)
				destCase1.x -= Scrolling; // deplacement des boite d'arme

			for (int i(0); i < nbrePlatform; i++)
				tabPlatform[i].x -= Scrolling;


			if (Scrolling == 0)
				Scrolle = false;
			else
				Scrolle = true;



			if (Fdest.x < (-(Fdest.w) + largeurFenetre))
			{
				Fdest.x += Scrolling;
				if (case1estUtilisee == false)
					destCase1.x += Scrolling;

				for (int i(0); i < nbrePlatform; i++)
					tabPlatform[i].x += Scrolling;

				Scrolle = false;

				niveauFinit = true;
			}

			if (Fdest.x > 0)
			{
				Fdest.x += Scrolling;
				if (case1estUtilisee == false)
					destCase1.x += Scrolling;

				for (int i(0); i < nbrePlatform; i++)
					tabPlatform[i].x += Scrolling;

				Scrolle = false;
			}

			// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------
			if (case1estUtilisee == false)
			{
				if (checkCollision(destCase1, perso.getDest()) == true)	// detection collision perso/boite d'arme
				{
					srand(time(0)); // initialisation de la génération de nombre aléatoire
					int nombreAleatoire;
					nombreAleatoire = rand() % tailleTabArme;

					perso.ramasserArme(pRenderer, tabArmes[nombreAleatoire]);

					case1estUtilisee = true;
				}
			}

			if (perso.getAUneArme() == true)
			{
				for (int i(0); i < nbrePlatform; i++)  // detection collision proj perso/platform
				{
					unsigned int j(0);
					j = 0;

					for (j; j < (perso.getArme()->getDestProj().size()); j++)
					{
						if (checkCollision(tabPlatform[i], perso.getArme()->getDestProj()[j]) == true)
						{
							std::vector<SDL_Rect>::iterator iter = perso.getArme()->getDestProj().begin(); // effacage de la case contenant le rect du tir qui a touché

							for (unsigned int l(0); l < j; l++)
								iter++;

							perso.getArme()->getDestProj().erase(iter);
						}
					}
				}
			}


			for (int k(0); k < nbreEnnemisBase; k++)
			{
				if (tabEnnemis[k]->getAUneArme() == true)
				{
					for (int i(0); i < nbrePlatform; i++)  // detection collision proj perso/platform
					{
						unsigned int j(0);
						j = 0;

						for (j; j < (tabEnnemis[k]->getArme()->getDestProj().size()); j++)
						{
							if (checkCollision(tabPlatform[i], tabEnnemis[k]->getArme()->getDestProj()[j]) == true)
							{
								std::vector<SDL_Rect>::iterator iter = tabEnnemis[k]->getArme()->getDestProj().begin(); // effacage de la case contenant le rect du tir qui a touché

								for (unsigned int l(0); l < j; l++)
									iter++;

								tabEnnemis[k]->getArme()->getDestProj().erase(iter);
							}
						}
					}
				}
			}

			if (perso.getAUneArme() == true)
			{
				for (int i(0); i < nbreEnnemisBase; i++)  // detection collision entre proj perso/ennemi
				{
					unsigned int j(0);
					j = 0;

					for (j; j < (perso.getArme()->getDestProj().size()); j++)
					{
						if (tabEnnemis[i]->getEstVivant() == true)
						{
							if (checkCollision(tabEnnemis[i]->getDest(), perso.getArme()->getDestProj()[j]) == true)
								perso.infligerDegats(tabEnnemis[i], j);
						}
					}
				}
			}


			for (int i(0); i < nbreEnnemisBase; i++)  // detection collision entre proj ennemi/perso
			{
				if (tabEnnemis[i]->getAUneArme() == true)
				{
					unsigned int j(0);
					j = 0;

					for (j; j < (tabEnnemis[i]->getArme()->getDestProj().size()); j++)
					{
						if (checkCollision(perso.getDest(), (tabEnnemis[i]->getArme()->getDestProj())[j]) == true)
							tabEnnemis[i]->infligerDegats(&perso, j);

					}
				}
			}

			SDL_RenderCopy(pRenderer, pFTexture, NULL, &Fdest); // affichage fond
			for (int i(0); i < nbrePlatform; i++) // affichage plateformes
				SDL_RenderCopy(pRenderer, pTexturePlat, NULL, &tabPlatform[i]);
			if (case1estUtilisee == false) // affichage case arme
				SDL_RenderCopy(pRenderer, pTextureSprites, NULL, &destCase1);


			for (int i = 0; i < nbreEnnemisBase; i++) // Affichage ennemis
			{
				if (tabEnnemis[i]->getEstVivant() == true)
					tabEnnemis[i]->show(pRenderer, Scrolle, (perso.getStatus()), nbrePlatform, tabPlatform, Scrolling);
			}

			perso.show(pRenderer, Scrolle, (perso.getStatus()), nbrePlatform, tabPlatform, Scrolling); // affichage perso

			SDL_RenderPresent(pRenderer);

			const Uint8 *state = SDL_GetKeyboardState(NULL);
			if (state[SDL_SCANCODE_ESCAPE])
			{
				overQuit = true;
			}

			while (fps.get_ticks() < 1000 / imageParSecondes)
			{
				//...
			}

			if (perso.getEstVivant() == false)
			{
				for (int i(0); i < nbreEnnemisBase; i++)
					delete tabEnnemis[i]->getArme();
				for (int i(0); i < nbreEnnemisBase; i++)
					tabEnnemis[i]->ramasserArme(pRenderer, "gourdin");

				quit = true;
			}

			if (overQuit == true || niveauFinit == true)
			{
				for (int i = 0; i < nbreEnnemisBase; i++)
				{
					delete tabEnnemis[i];
					tabEnnemis[i] = nullptr;
				}

				quit = true;
			}

		}

	} while (perso.getEstVivant() == false);

	return;
}

void niveau4(SDL_Window *pWindow, SDL_Renderer *pRenderer, Perso &perso, string tabArmes[], int tailleTabArme, bool &overQuit)
{
	SDL_Surface *pFond;
	pFond = SDL_LoadBMP("images/niveaux/futur/fond.bmp");
	SDL_Texture *pFTexture = SDL_CreateTextureFromSurface(pRenderer, pFond);
	SDL_Rect Fdest = { 0, 0, largeurFond, hauteurFenetre };

	SDL_Surface *pSprites = SDL_LoadBMP("images/sprites/boiteArme/boiteArme.bmp");
	Uint32 colorkey = SDL_MapRGB(pSprites->format, 255, 255, 255);
	SDL_SetColorKey(pSprites, SDL_RLEACCEL | SDL_TRUE, colorkey);
	SDL_Texture *pTextureSprites = SDL_CreateTextureFromSurface(pRenderer, pSprites);
	SDL_Rect destCase1 = { 1000, 555, 35, 42 };

	SDL_Surface *pPlat = SDL_LoadBMP("images/niveaux/futur/platforme.bmp");
	Uint32 colorkey2 = SDL_MapRGB(pPlat->format, 255, 255, 255);
	SDL_SetColorKey(pPlat, SDL_RLEACCEL | SDL_TRUE, colorkey2);
	SDL_Texture *pTexturePlat = SDL_CreateTextureFromSurface(pRenderer, pPlat);


	int const tailletabCine(17);
	SDL_Texture *TabCine[tailletabCine];
	SDL_Surface *Cine;
	Cine = SDL_LoadBMP("images/niveaux/futur/cinematiques2/1.bmp");
	TabCine[0] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/futur/cinematiques2/2.bmp");
	TabCine[1] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/futur/cinematiques2/3.bmp");
	TabCine[2] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/futur/cinematiques2/4.bmp");
	TabCine[3] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/futur/cinematiques2/5.bmp");
	TabCine[4] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/futur/cinematiques2/6.bmp");
	TabCine[5] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/futur/cinematiques2/7.bmp");
	TabCine[6] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/futur/cinematiques2/8.bmp");
	TabCine[7] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/futur/cinematiques2/9.bmp");
	TabCine[8] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/futur/cinematiques2/10.bmp");
	TabCine[9] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/futur/cinematiques2/11.bmp");
	TabCine[10] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/futur/cinematiques2/12.bmp");
	TabCine[11] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/futur/cinematiques2/13.bmp");
	TabCine[12] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/futur/cinematiques2/14.bmp");
	TabCine[13] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/futur/cinematiques2/15.bmp");
	TabCine[14] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/futur/cinematiques2/16.bmp");
	TabCine[15] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/futur/cinematiques2/17.bmp");
	TabCine[16] = SDL_CreateTextureFromSurface(pRenderer, Cine);


	int const nbreEnnemisBase(11);
	Perso *tabEnnemis[nbreEnnemisBase];


	int const nbrePlatform(6);
	SDL_Rect tabPlatform[nbrePlatform];

	for (int i(0); i < nbrePlatform; i++)
	{
		tabPlatform[i].w = 347;
		tabPlatform[i].h = 44;
	}

	tabEnnemis[0] = new Perso(pRenderer, 100, true, 1600, 400, "robots du futur");
	tabEnnemis[1] = new Perso(pRenderer, 100, true, 1740, 0, "robots du futur");
	tabEnnemis[2] = new Perso(pRenderer, 100, true, 2400, 400, "robots du futur");
	tabEnnemis[3] = new Perso(pRenderer, 100, true, 2700, 0, "robots du futur");
	tabEnnemis[4] = new Perso(pRenderer, 100, true, 4100, 0, "robots du futur");
	tabEnnemis[5] = new Perso(pRenderer, 100, true, 4200, 400, "robots du futur");
	tabEnnemis[6] = new Perso(pRenderer, 100, true, 4660, 0, "robots du futur");
	tabEnnemis[7] = new Perso(pRenderer, 100, true, 5500, 400, "robots du futur");
	tabEnnemis[8] = new Perso(pRenderer, 100, true, 5620, 0, "robots du futur");
	tabEnnemis[9] = new Perso(pRenderer, 100, true, 6220, 0, "robots du futur");
	tabEnnemis[10] = new Perso(pRenderer, 100, true, 6300, 400, "robots du futur");

	SDL_Event event;
	for (int i(0); i < tailletabCine; i++)
	{
		SDL_RenderCopy(pRenderer, TabCine[i], NULL, NULL);
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
						if ((event.button.x > 0) && (event.button.x < largeurFenetre) && (event.button.y > 0) && (event.button.y < hauteurFenetre))
						{
							merde = false;
							break;

						}
					}
				}
			}
		}
	}

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

	Mix_Music * muuuuuuuusiiiiiiiiique;
	muuuuuuuusiiiiiiiiique = Mix_LoadMUS("musique/musique.mp3");
	Mix_VolumeMusic(MIX_MAX_VOLUME);

	Mix_PlayMusic(muuuuuuuusiiiiiiiiique, -1);

	do
	{
		Mix_RewindMusic();

		int Scrolling(0);
		bool Scrolle(false); // false : le perso se déplace, true : le fond défile
		timer fps;
		int imageParSecondes(60);
		bool quit(false);
		bool niveauFinit(false);
		bool case1estUtilisee(false);

		Fdest = { 0, 0, largeurFond, hauteurFenetre };
		destCase1 = { 1000, 555, 35, 42 };

		for (int i = 0; i < nbreEnnemisBase; i++)
			tabEnnemis[i]->setPv(140);

		tabEnnemis[0]->setDest(1600, 400);
		tabEnnemis[1]->setDest(1740, 0);
		tabEnnemis[2]->setDest(2400, 400);
		tabEnnemis[3]->setDest(2700, 0);
		tabEnnemis[4]->setDest(4100, 0);
		tabEnnemis[5]->setDest(4200, 400);
		tabEnnemis[6]->setDest(4660, 0);
		tabEnnemis[7]->setDest(5500, 400);
		tabEnnemis[8]->setDest(5620, 0);
		tabEnnemis[9]->setDest(6220, 0);
		tabEnnemis[10]->setDest(6300, 400);


		perso.ramasserArme(pRenderer, "rein");
		perso.setDest(largeurFenetre / 2 - 100 / 2, 0);
		perso.setPv(450);
		perso.reinitialMouvement();

		tabPlatform[0].x = 1740;
		tabPlatform[0].y = 215;

		tabPlatform[1].x = 2700;
		tabPlatform[1].y = 215;

		tabPlatform[2].x = 4100;
		tabPlatform[2].y = 215;

		tabPlatform[3].x = 4660;
		tabPlatform[3].y = 355;

		tabPlatform[4].x = 5620;
		tabPlatform[4].y = 355;

		tabPlatform[5].x = 6220;
		tabPlatform[5].y = 215;




		while (quit == false)
		{
			fps.start();

			perso.recuperation_event(Scrolling, nbrePlatform, tabPlatform);

			for (int i = 0; i < nbreEnnemisBase; i++)
			{
				if (tabEnnemis[i]->getEstVivant() == true)
					tabEnnemis[i]->IAtiser(perso.getDest(), Scrolle, (perso.getStatus()), nbrePlatform, tabPlatform, tabEnnemis, nbreEnnemisBase, i, 250);
			}


			// ------------------------------------------------Scrolling-------------------------------------------------------------------------------------------------

			Fdest.x -= Scrolling;
			if (case1estUtilisee == false)
				destCase1.x -= Scrolling; // deplacement des boite d'arme

			for (int i(0); i < nbrePlatform; i++)
				tabPlatform[i].x -= Scrolling;


			if (Scrolling == 0)
				Scrolle = false;
			else
				Scrolle = true;



			if (Fdest.x < (-(Fdest.w) + largeurFenetre))
			{
				Fdest.x += Scrolling;
				if (case1estUtilisee == false)
					destCase1.x += Scrolling;

				for (int i(0); i < nbrePlatform; i++)
					tabPlatform[i].x += Scrolling;

				Scrolle = false;

				niveauFinit = true;
			}

			if (Fdest.x > 0)
			{
				Fdest.x += Scrolling;
				if (case1estUtilisee == false)
					destCase1.x += Scrolling;

				for (int i(0); i < nbrePlatform; i++)
					tabPlatform[i].x += Scrolling;

				Scrolle = false;
			}

			// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------
			if (case1estUtilisee == false)
			{
				if (checkCollision(destCase1, perso.getDest()) == true)	// detection collision perso/boite d'arme
				{
					srand(time(0)); // initialisation de la génération de nombre aléatoire
					int nombreAleatoire;
					nombreAleatoire = rand() % tailleTabArme;

					perso.ramasserArme(pRenderer, tabArmes[nombreAleatoire]);

					case1estUtilisee = true;
				}
			}

			if (perso.getAUneArme() == true)
			{
				for (int i(0); i < nbrePlatform; i++)  // detection collision proj perso/platform
				{
					unsigned int j(0);
					j = 0;

					for (j; j < (perso.getArme()->getDestProj().size()); j++)
					{
						if (checkCollision(tabPlatform[i], perso.getArme()->getDestProj()[j]) == true)
						{
							std::vector<SDL_Rect>::iterator iter = perso.getArme()->getDestProj().begin(); // effacage de la case contenant le rect du tir qui a touché

							for (unsigned int l(0); l < j; l++)
								iter++;

							perso.getArme()->getDestProj().erase(iter);
						}
					}
				}
			}


			for (int k(0); k < nbreEnnemisBase; k++)
			{
				if (tabEnnemis[k]->getAUneArme() == true)
				{
					for (int i(0); i < nbrePlatform; i++)  // detection collision proj perso/platform
					{
						unsigned int j(0);
						j = 0;

						for (j; j < (tabEnnemis[k]->getArme()->getDestProj().size()); j++)
						{
							if (checkCollision(tabPlatform[i], tabEnnemis[k]->getArme()->getDestProj()[j]) == true)
							{
								std::vector<SDL_Rect>::iterator iter = tabEnnemis[k]->getArme()->getDestProj().begin(); // effacage de la case contenant le rect du tir qui a touché

								for (unsigned int l(0); l < j; l++)
									iter++;

								tabEnnemis[k]->getArme()->getDestProj().erase(iter);
							}
						}
					}
				}
			}

			if (perso.getAUneArme() == true)
			{
				for (int i(0); i < nbreEnnemisBase; i++)  // detection collision entre proj perso/ennemi
				{
					unsigned int j(0);
					j = 0;

					for (j; j < (perso.getArme()->getDestProj().size()); j++)
					{
						if (tabEnnemis[i]->getEstVivant() == true)
						{
							if (checkCollision(tabEnnemis[i]->getDest(), perso.getArme()->getDestProj()[j]) == true)
								perso.infligerDegats(tabEnnemis[i], j);
						}
					}
				}
			}


			for (int i(0); i < nbreEnnemisBase; i++)  // detection collision entre proj ennemi/perso
			{
				if (tabEnnemis[i]->getAUneArme() == true)
				{
					unsigned int j(0);
					j = 0;

					for (j; j < (tabEnnemis[i]->getArme()->getDestProj().size()); j++)
					{
						if (checkCollision(perso.getDest(), (tabEnnemis[i]->getArme()->getDestProj())[j]) == true)
							tabEnnemis[i]->infligerDegats(&perso, j);

					}
				}
			}

			SDL_RenderCopy(pRenderer, pFTexture, NULL, &Fdest); // affichage fond
			for (int i(0); i < nbrePlatform; i++) // affichage plateformes
				SDL_RenderCopy(pRenderer, pTexturePlat, NULL, &tabPlatform[i]);
			if (case1estUtilisee == false) // affichage case arme
				SDL_RenderCopy(pRenderer, pTextureSprites, NULL, &destCase1);


			for (int i = 0; i < nbreEnnemisBase; i++) // Affichage ennemis
			{
				if (tabEnnemis[i]->getEstVivant() == true)
					tabEnnemis[i]->show(pRenderer, Scrolle, (perso.getStatus()), nbrePlatform, tabPlatform, Scrolling);
			}

			perso.show(pRenderer, Scrolle, (perso.getStatus()), nbrePlatform, tabPlatform, Scrolling); // affichage perso

			SDL_RenderPresent(pRenderer);

			const Uint8 *state = SDL_GetKeyboardState(NULL);
			if (state[SDL_SCANCODE_ESCAPE])
			{
				overQuit = true;
			}

			while (fps.get_ticks() < 1000 / imageParSecondes)
			{
				//...
			}

			if (perso.getEstVivant() == false)
			{
				for (int i(0); i < nbreEnnemisBase; i++)
					delete tabEnnemis[i]->getArme();
				for (int i(0); i < nbreEnnemisBase; i++)
					tabEnnemis[i]->ramasserArme(pRenderer, "bras robot");

				quit = true;
			}

			if (overQuit == true || niveauFinit == true)
			{
				for (int i = 0; i < nbreEnnemisBase; i++)
				{
					delete tabEnnemis[i];
					tabEnnemis[i] = nullptr;
				}

				quit = true;
			}

		}

	} while (perso.getEstVivant() == false);

	return;
}

void niveau5(SDL_Window *pWindow, SDL_Renderer *pRenderer, Perso &perso, string tabArmes[], int tailleTabArme, bool &overQuit)
{
	SDL_Surface *pFond;
	pFond = SDL_LoadBMP("images/niveaux/espace/fond.bmp");
	SDL_Texture *pFTexture = SDL_CreateTextureFromSurface(pRenderer, pFond);
	SDL_Rect Fdest = { 0, 0, largeurFond, hauteurFenetre };

	SDL_Surface *pSprites = SDL_LoadBMP("images/sprites/boiteArme/boiteArme.bmp");
	Uint32 colorkey = SDL_MapRGB(pSprites->format, 255, 255, 255);
	SDL_SetColorKey(pSprites, SDL_RLEACCEL | SDL_TRUE, colorkey);
	SDL_Texture *pTextureSprites = SDL_CreateTextureFromSurface(pRenderer, pSprites);
	SDL_Rect destCase1 = { 1000, 555, 35, 42 };

	SDL_Surface *pPlat = SDL_LoadBMP("images/niveaux/espace/platforme.bmp");
	SDL_Texture *pTexturePlat = SDL_CreateTextureFromSurface(pRenderer, pPlat);


	int const tailletabCine(16);
	SDL_Texture *TabCine[tailletabCine];
	SDL_Surface *Cine;
	Cine = SDL_LoadBMP("images/niveaux/espace/cinematiques2/1.bmp");
	TabCine[0] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/espace/cinematiques2/2.bmp");
	TabCine[1] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/espace/cinematiques2/3.bmp");
	TabCine[2] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/espace/cinematiques2/4.bmp");
	TabCine[3] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/espace/cinematiques2/5.bmp");
	TabCine[4] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/espace/cinematiques2/6.bmp");
	TabCine[5] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/espace/cinematiques2/7.bmp");
	TabCine[6] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/espace/cinematiques2/8.bmp");
	TabCine[7] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/espace/cinematiques2/9.bmp");
	TabCine[8] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/espace/cinematiques2/10.bmp");
	TabCine[9] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/espace/cinematiques2/11.bmp");
	TabCine[10] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/espace/cinematiques2/12.bmp");
	TabCine[11] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/espace/cinematiques2/13.bmp");
	TabCine[12] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/espace/cinematiques2/14.bmp");
	TabCine[13] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/espace/cinematiques2/15.bmp");
	TabCine[14] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/espace/cinematiques2/16.bmp");
	TabCine[15] = SDL_CreateTextureFromSurface(pRenderer, Cine);

	int const nbreEnnemisBase(9);
	Perso *tabEnnemis[nbreEnnemisBase];


	int const nbrePlatform(6);
	SDL_Rect tabPlatform[nbrePlatform];

	for (int i(0); i < nbrePlatform; i++)
	{
		tabPlatform[i].w = 347;
		tabPlatform[i].h = 44;
	}


	tabEnnemis[0] = new Perso(pRenderer, 100, true, 1100, 400, "punks de l'espace");
	tabEnnemis[1] = new Perso(pRenderer, 100, true, 1655, 400, "punks de l'espace");
	tabEnnemis[2] = new Perso(pRenderer, 100, true, 2400, 400, "punks de l'espace");
	tabEnnemis[3] = new Perso(pRenderer, 100, true, 3120, 0, "punks de l'espace");
	tabEnnemis[4] = new Perso(pRenderer, 100, true, 3250, 400, "punks de l'espace");
	tabEnnemis[5] = new Perso(pRenderer, 100, true, 4400, 400, "punks de l'espace");
	tabEnnemis[6] = new Perso(pRenderer, 100, true, 5000, 0, "punks de l'espace");
	tabEnnemis[7] = new Perso(pRenderer, 100, true, 6030, 0, "punks de l'espace");
	tabEnnemis[8] = new Perso(pRenderer, 100, true, 6250, 400, "punks de l'espace");

	SDL_Event event;
	for (int i(0); i < tailletabCine; i++)
	{
		SDL_RenderCopy(pRenderer, TabCine[i], NULL, NULL);
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
						if ((event.button.x > 0) && (event.button.x < largeurFenetre) && (event.button.y > 0) && (event.button.y < hauteurFenetre))
						{
							merde = false;
							break;

						}
					}
				}
			}
		}
	}

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

	Mix_Music * muuuuuuuusiiiiiiiiique;
	muuuuuuuusiiiiiiiiique = Mix_LoadMUS("musique/musique.mp3");
	Mix_VolumeMusic(MIX_MAX_VOLUME);

	Mix_PlayMusic(muuuuuuuusiiiiiiiiique, -1);

	do
	{
		Mix_RewindMusic();
		int Scrolling(0);
		bool Scrolle(false); // false : le perso se déplace, true : le fond défile
		timer fps;
		int imageParSecondes(60);
		bool quit(false);
		bool niveauFinit(false);
		bool case1estUtilisee(false);

		Fdest = { 0, 0, largeurFond, hauteurFenetre };
		destCase1 = { 1000, 555, 35, 42 };

		for (int i = 0; i < nbreEnnemisBase; i++)
			tabEnnemis[i]->setPv(200);

		tabEnnemis[0]->setDest(1100, 400);
		tabEnnemis[1]->setDest(1655, 400);
		tabEnnemis[2]->setDest(2400, 400);
		tabEnnemis[3]->setDest(3120, 0);
		tabEnnemis[4]->setDest(3250, 400);
		tabEnnemis[5]->setDest(4400, 400);
		tabEnnemis[6]->setDest(5000, 0);
		tabEnnemis[7]->setDest(6030, 0);
		tabEnnemis[8]->setDest(6250, 400);

		perso.ramasserArme(pRenderer, "rein");
		perso.setDest(largeurFenetre / 2 - 100 / 2, 0);
		perso.setPv(450);
		perso.reinitialMouvement();

		
		tabPlatform[0].x = 1655;
		tabPlatform[0].y = 355;

		tabPlatform[1].x = 2565;
		tabPlatform[1].y = 355;

		tabPlatform[2].x = 3120;
		tabPlatform[2].y = 215;

		tabPlatform[3].x = 4390;
		tabPlatform[3].y = 355;

		tabPlatform[4].x = 4990;
		tabPlatform[4].y = 355;

		tabPlatform[5].x = 6035;
		tabPlatform[5].y = 355;



		while (quit == false)
		{
			fps.start();

			perso.recuperation_event(Scrolling, nbrePlatform, tabPlatform);

			for (int i = 0; i < nbreEnnemisBase; i++)
			{
				if (tabEnnemis[i]->getEstVivant() == true)
					tabEnnemis[i]->IAtiser(perso.getDest(), Scrolle, (perso.getStatus()), nbrePlatform, tabPlatform, tabEnnemis, nbreEnnemisBase, i, 250);
			}


			// ------------------------------------------------Scrolling-------------------------------------------------------------------------------------------------

			Fdest.x -= Scrolling;
			if (case1estUtilisee == false)
				destCase1.x -= Scrolling; // deplacement des boite d'arme

			for (int i(0); i < nbrePlatform; i++)
				tabPlatform[i].x -= Scrolling;


			if (Scrolling == 0)
				Scrolle = false;
			else
				Scrolle = true;



			if (Fdest.x < (-(Fdest.w) + largeurFenetre))
			{
				Fdest.x += Scrolling;
				if (case1estUtilisee == false)
					destCase1.x += Scrolling;

				for (int i(0); i < nbrePlatform; i++)
					tabPlatform[i].x += Scrolling;

				Scrolle = false;

				niveauFinit = true;
			}

			if (Fdest.x > 0)
			{
				Fdest.x += Scrolling;
				if (case1estUtilisee == false)
					destCase1.x += Scrolling;

				for (int i(0); i < nbrePlatform; i++)
					tabPlatform[i].x += Scrolling;

				Scrolle = false;
			}

			// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------
			if (case1estUtilisee == false)
			{
				if (checkCollision(destCase1, perso.getDest()) == true)	// detection collision perso/boite d'arme
				{
					srand(time(0)); // initialisation de la génération de nombre aléatoire
					int nombreAleatoire;
					nombreAleatoire = rand() % tailleTabArme;

					perso.ramasserArme(pRenderer, tabArmes[nombreAleatoire]);

					case1estUtilisee = true;
				}
			}

			if (perso.getAUneArme() == true)
			{
				for (int i(0); i < nbrePlatform; i++)  // detection collision proj perso/platform
				{
					unsigned int j(0);
					j = 0;

					for (j; j < (perso.getArme()->getDestProj().size()); j++)
					{
						if (checkCollision(tabPlatform[i], perso.getArme()->getDestProj()[j]) == true)
						{
							std::vector<SDL_Rect>::iterator iter = perso.getArme()->getDestProj().begin(); // effacage de la case contenant le rect du tir qui a touché

							for (unsigned int l(0); l < j; l++)
								iter++;

							perso.getArme()->getDestProj().erase(iter);
						}
					}
				}
			}


			for (int k(0); k < nbreEnnemisBase; k++)
			{
				if (tabEnnemis[k]->getAUneArme() == true)
				{
					for (int i(0); i < nbrePlatform; i++)  // detection collision proj perso/platform
					{
						unsigned int j(0);
						j = 0;

						for (j; j < (tabEnnemis[k]->getArme()->getDestProj().size()); j++)
						{
							if (checkCollision(tabPlatform[i], tabEnnemis[k]->getArme()->getDestProj()[j]) == true)
							{
								std::vector<SDL_Rect>::iterator iter = tabEnnemis[k]->getArme()->getDestProj().begin(); // effacage de la case contenant le rect du tir qui a touché

								for (unsigned int l(0); l < j; l++)
									iter++;

								tabEnnemis[k]->getArme()->getDestProj().erase(iter);
							}
						}
					}
				}
			}

			if (perso.getAUneArme() == true)
			{
				for (int i(0); i < nbreEnnemisBase; i++)  // detection collision entre proj perso/ennemi
				{
					unsigned int j(0);
					j = 0;

					for (j; j < (perso.getArme()->getDestProj().size()); j++)
					{
						if (tabEnnemis[i]->getEstVivant() == true)
						{
							if (checkCollision(tabEnnemis[i]->getDest(), perso.getArme()->getDestProj()[j]) == true)
								perso.infligerDegats(tabEnnemis[i], j);
						}
					}
				}
			}


			for (int i(0); i < nbreEnnemisBase; i++)  // detection collision entre proj ennemi/perso
			{
				if (tabEnnemis[i]->getAUneArme() == true)
				{
					unsigned int j(0);
					j = 0;

					for (j; j < (tabEnnemis[i]->getArme()->getDestProj().size()); j++)
					{
						if (checkCollision(perso.getDest(), (tabEnnemis[i]->getArme()->getDestProj())[j]) == true)
							tabEnnemis[i]->infligerDegats(&perso, j);

					}
				}
			}

			SDL_RenderCopy(pRenderer, pFTexture, NULL, &Fdest); // affichage fond
			for (int i(0); i < nbrePlatform; i++) // affichage plateformes
				SDL_RenderCopy(pRenderer, pTexturePlat, NULL, &tabPlatform[i]);
			if (case1estUtilisee == false) // affichage case arme
				SDL_RenderCopy(pRenderer, pTextureSprites, NULL, &destCase1);


			for (int i = 0; i < nbreEnnemisBase; i++) // Affichage ennemis
			{
				if (tabEnnemis[i]->getEstVivant() == true)
					tabEnnemis[i]->show(pRenderer, Scrolle, (perso.getStatus()), nbrePlatform, tabPlatform, Scrolling);
			}

			perso.show(pRenderer, Scrolle, (perso.getStatus()), nbrePlatform, tabPlatform, Scrolling); // affichage perso

			SDL_RenderPresent(pRenderer);

			const Uint8 *state = SDL_GetKeyboardState(NULL);
			if (state[SDL_SCANCODE_ESCAPE])
			{
				overQuit = true;
			}

			while (fps.get_ticks() < 1000 / imageParSecondes)
			{
				//...
			}

			if (perso.getEstVivant() == false)
			{
				for (int i(0); i < nbreEnnemisBase; i++)
					delete tabEnnemis[i]->getArme();
				for (int i(0); i < nbreEnnemisBase; i++)
					tabEnnemis[i]->ramasserArme(pRenderer, "bazookat");

				quit = true;
			}

			if (overQuit == true || niveauFinit == true)
			{
				for (int i = 0; i < nbreEnnemisBase; i++)
				{
					delete tabEnnemis[i];
					tabEnnemis[i] = nullptr;
				}

				quit = true;
			}

		}

	} while (perso.getEstVivant() == false);

	return;
}

void niveau6(SDL_Window *pWindow, SDL_Renderer *pRenderer, Perso &perso, string tabArmes[], int tailleTabArme, bool &overQuit)
{

	SDL_Surface *pFond;
	pFond = SDL_LoadBMP("images/niveaux/lune/fond.bmp");
	SDL_Texture *pFTexture = SDL_CreateTextureFromSurface(pRenderer, pFond);
	SDL_Rect Fdest = { 0, 0, largeurFond, hauteurFenetre };

	SDL_Surface *pSprites = SDL_LoadBMP("images/sprites/boiteArme/boiteArme.bmp");
	Uint32 colorkey = SDL_MapRGB(pSprites->format, 255, 255, 255);
	SDL_SetColorKey(pSprites, SDL_RLEACCEL | SDL_TRUE, colorkey);
	SDL_Texture *pTextureSprites = SDL_CreateTextureFromSurface(pRenderer, pSprites);
	SDL_Rect destCase1 = { 1000, 555, 35, 42 };

	SDL_Surface *pPlat = SDL_LoadBMP("images/niveaux/lune/platforme.bmp");
	SDL_Texture *pTexturePlat = SDL_CreateTextureFromSurface(pRenderer, pPlat);

	int const tailletabCine(9);
	SDL_Texture *TabCine[tailletabCine];
	SDL_Surface *Cine;
	Cine = SDL_LoadBMP("images/niveaux/lune/cinematiques2/1.bmp");
	TabCine[0] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/lune/cinematiques2/2.bmp");
	TabCine[1] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/lune/cinematiques2/3.bmp");
	TabCine[2] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/lune/cinematiques2/4.bmp");
	TabCine[3] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/lune/cinematiques2/5.bmp");
	TabCine[4] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/lune/cinematiques2/6.bmp");
	TabCine[5] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/lune/cinematiques2/7.bmp");
	TabCine[6] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/lune/cinematiques2/8.bmp");
	TabCine[7] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/lune/cinematiques2/9.bmp");
	TabCine[8] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/lune/cinematiques2/10.bmp");


	int const nbreEnnemisBase(8);
	Perso *tabEnnemis[nbreEnnemisBase];
	
	int const nbrePlatform(6);
	SDL_Rect tabPlatform[nbrePlatform];

	for (int i(0); i < nbrePlatform; i++)
	{
		tabPlatform[i].w = 347;
		tabPlatform[i].h = 44;
	}


	tabEnnemis[0] = new Perso(pRenderer, 100, true, 1720, 0, "petits gris");
	tabEnnemis[1] = new Perso(pRenderer, 100, true, 2100, 400, "petits gris");
	tabEnnemis[2] = new Perso(pRenderer, 100, true, 2480, 0, "petits gris");
	tabEnnemis[3] = new Perso(pRenderer, 100, true, 4130, 0, "petits gris");
	tabEnnemis[4] = new Perso(pRenderer, 100, true, 4500, 400, "petits gris");
	tabEnnemis[5] = new Perso(pRenderer, 100, true, 4770, 0, "petits gris");
	tabEnnemis[6] = new Perso(pRenderer, 100, true, 5620, 0, "petits gris");
	tabEnnemis[7] = new Perso(pRenderer, 100, true, 6200, 400, "petits gris");

	SDL_Event event;
	for (int i(0); i < tailletabCine; i++)
	{
		SDL_RenderCopy(pRenderer, TabCine[i], NULL, NULL);
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
						if ((event.button.x > 0) && (event.button.x < largeurFenetre) && (event.button.y > 0) && (event.button.y < hauteurFenetre))
						{
							merde = false;
							break;

						}
					}
				}
			}
		}
	}

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

	Mix_Music * muuuuuuuusiiiiiiiiique;
	muuuuuuuusiiiiiiiiique = Mix_LoadMUS("musique/musique.mp3");
	Mix_VolumeMusic(MIX_MAX_VOLUME);

	Mix_PlayMusic(muuuuuuuusiiiiiiiiique, -1);

	do
	{
		Mix_RewindMusic();
		int Scrolling(0);
		bool Scrolle(false); // false : le perso se déplace, true : le fond défile
		timer fps;
		int imageParSecondes(60);
		bool quit(false);
		bool niveauFinit(false);
		bool case1estUtilisee(false);

		Fdest = { 0, 0, largeurFond, hauteurFenetre };
		destCase1 = { 1000, 555, 35, 42 };

		for (int i = 0; i < nbreEnnemisBase; i++)
			tabEnnemis[i]->setPv(200);

		tabEnnemis[0]->setDest(1720, 0);
		tabEnnemis[1]->setDest(2100, 400);
		tabEnnemis[2]->setDest(2480, 0);
		tabEnnemis[3]->setDest(4130, 0);
		tabEnnemis[4]->setDest(4500, 400);
		tabEnnemis[5]->setDest(4770, 0);
		tabEnnemis[6]->setDest(5620, 0);
		tabEnnemis[7]->setDest(6200, 400);


		perso.ramasserArme(pRenderer, "rein");
		perso.setDest(largeurFenetre / 2 - 100 / 2, 0);
		perso.setPv(450);
		perso.reinitialMouvement();		


		tabPlatform[0].x = 1720;
		tabPlatform[0].y = 215;

		tabPlatform[1].x = 2480;
		tabPlatform[1].y = 215;

		tabPlatform[2].x = 4130;
		tabPlatform[2].y = 215;

		tabPlatform[3].x = 4770;
		tabPlatform[3].y = 355;

		tabPlatform[4].x = 5620;
		tabPlatform[4].y = 355;

		tabPlatform[5].x = 6060;
		tabPlatform[5].y = 215;

		

		

		while (quit == false)
		{
			fps.start();

			perso.recuperation_event(Scrolling, nbrePlatform, tabPlatform);

			for (int i = 0; i < nbreEnnemisBase; i++)
			{
				if (tabEnnemis[i]->getEstVivant() == true)
					tabEnnemis[i]->IAtiser(perso.getDest(), Scrolle, (perso.getStatus()), nbrePlatform, tabPlatform, tabEnnemis, nbreEnnemisBase, i, 250);
			}


			// ------------------------------------------------Scrolling-------------------------------------------------------------------------------------------------

			Fdest.x -= Scrolling;
			if (case1estUtilisee == false)
				destCase1.x -= Scrolling; // deplacement des boite d'arme

			for (int i(0); i < nbrePlatform; i++)
				tabPlatform[i].x -= Scrolling;


			if (Scrolling == 0)
				Scrolle = false;
			else
				Scrolle = true;



			if (Fdest.x < (-(Fdest.w) + largeurFenetre))
			{
				Fdest.x += Scrolling;
				if (case1estUtilisee == false)
					destCase1.x += Scrolling;

				for (int i(0); i < nbrePlatform; i++)
					tabPlatform[i].x += Scrolling;

				Scrolle = false;

				niveauFinit = true;
			}

			if (Fdest.x > 0)
			{
				Fdest.x += Scrolling;
				if (case1estUtilisee == false)
					destCase1.x += Scrolling;

				for (int i(0); i < nbrePlatform; i++)
					tabPlatform[i].x += Scrolling;

				Scrolle = false;
			}

			// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------
			if (case1estUtilisee == false)
			{
				if (checkCollision(destCase1, perso.getDest()) == true)	// detection collision perso/boite d'arme
				{
					srand(time(0)); // initialisation de la génération de nombre aléatoire
					int nombreAleatoire;
					nombreAleatoire = rand() % tailleTabArme;

					perso.ramasserArme(pRenderer, tabArmes[nombreAleatoire]);

					case1estUtilisee = true;
				}
			}

			if (perso.getAUneArme() == true)
			{
				for (int i(0); i < nbrePlatform; i++)  // detection collision proj perso/platform
				{
					unsigned int j(0);
					j = 0;

					for (j; j < (perso.getArme()->getDestProj().size()); j++)
					{
						if (checkCollision(tabPlatform[i], perso.getArme()->getDestProj()[j]) == true)
						{
							std::vector<SDL_Rect>::iterator iter = perso.getArme()->getDestProj().begin(); // effacage de la case contenant le rect du tir qui a touché

							for (unsigned int l(0); l < j; l++)
								iter++;

							perso.getArme()->getDestProj().erase(iter);
						}
					}
				}
			}


			for (int k(0); k < nbreEnnemisBase; k++)
			{
				if (tabEnnemis[k]->getAUneArme() == true)
				{
					for (int i(0); i < nbrePlatform; i++)  // detection collision proj perso/platform
					{
						unsigned int j(0);
						j = 0;

						for (j; j < (tabEnnemis[k]->getArme()->getDestProj().size()); j++)
						{
							if (checkCollision(tabPlatform[i], tabEnnemis[k]->getArme()->getDestProj()[j]) == true)
							{
								std::vector<SDL_Rect>::iterator iter = tabEnnemis[k]->getArme()->getDestProj().begin(); // effacage de la case contenant le rect du tir qui a touché

								for (unsigned int l(0); l < j; l++)
									iter++;

								tabEnnemis[k]->getArme()->getDestProj().erase(iter);
							}
						}
					}
				}
			}

			if (perso.getAUneArme() == true)
			{
				for (int i(0); i < nbreEnnemisBase; i++)  // detection collision entre proj perso/ennemi
				{
					unsigned int j(0);
					j = 0;

					for (j; j < (perso.getArme()->getDestProj().size()); j++)
					{
						if (tabEnnemis[i]->getEstVivant() == true)
						{
							if (checkCollision(tabEnnemis[i]->getDest(), perso.getArme()->getDestProj()[j]) == true)
								perso.infligerDegats(tabEnnemis[i], j);
						}
					}
				}
			}


			for (int i(0); i < nbreEnnemisBase; i++)  // detection collision entre proj ennemi/perso
			{
				if (tabEnnemis[i]->getAUneArme() == true)
				{
					unsigned int j(0);
					j = 0;

					for (j; j < (tabEnnemis[i]->getArme()->getDestProj().size()); j++)
					{
						if (checkCollision(perso.getDest(), (tabEnnemis[i]->getArme()->getDestProj())[j]) == true)
							tabEnnemis[i]->infligerDegats(&perso, j);

					}
				}
			}

			SDL_RenderCopy(pRenderer, pFTexture, NULL, &Fdest); // affichage fond
			for (int i(0); i < nbrePlatform; i++) // affichage plateformes
				SDL_RenderCopy(pRenderer, pTexturePlat, NULL, &tabPlatform[i]);
			if (case1estUtilisee == false) // affichage case arme
				SDL_RenderCopy(pRenderer, pTextureSprites, NULL, &destCase1);


			for (int i = 0; i < nbreEnnemisBase; i++) // Affichage ennemis
			{
				if (tabEnnemis[i]->getEstVivant() == true)
					tabEnnemis[i]->show(pRenderer, Scrolle, (perso.getStatus()), nbrePlatform, tabPlatform, Scrolling);
			}

			perso.show(pRenderer, Scrolle, (perso.getStatus()), nbrePlatform, tabPlatform, Scrolling); // affichage perso

			SDL_RenderPresent(pRenderer);

			const Uint8 *state = SDL_GetKeyboardState(NULL);
			if (state[SDL_SCANCODE_ESCAPE])
			{
				overQuit = true;
			}

			while (fps.get_ticks() < 1000 / imageParSecondes)
			{
				//...
			}

			if (perso.getEstVivant() == false)
			{
				for (int i(0); i < nbreEnnemisBase; i++)
					delete tabEnnemis[i]->getArme();
				for (int i(0); i < nbreEnnemisBase; i++)
					tabEnnemis[i]->ramasserArme(pRenderer, "yeux laser");

				quit = true;
			}

			if (overQuit == true || niveauFinit == true)
			{
				for (int i = 0; i < nbreEnnemisBase; i++)
				{
					delete tabEnnemis[i];
					tabEnnemis[i] = nullptr;
				}

				quit = true;
			}

		}

	} while (perso.getEstVivant() == false);

	return;
}

void niveau7(SDL_Window *pWindow, SDL_Renderer *pRenderer, Perso &perso, string tabArmes[], int tailleTabArme, bool &overQuit)
{

	SDL_Surface *pFond;
	pFond = SDL_LoadBMP("images/niveaux/dimension Z/fond.bmp");
	SDL_Texture *pFTexture = SDL_CreateTextureFromSurface(pRenderer, pFond);
	SDL_Rect Fdest = { 0, 0, largeurFond, hauteurFenetre };

	SDL_Surface *pSprites = SDL_LoadBMP("images/sprites/boiteArme/boiteArme.bmp");
	Uint32 colorkey = SDL_MapRGB(pSprites->format, 255, 255, 255);
	SDL_SetColorKey(pSprites, SDL_RLEACCEL | SDL_TRUE, colorkey);
	SDL_Texture *pTextureSprites = SDL_CreateTextureFromSurface(pRenderer, pSprites);
	SDL_Rect destCase1 = { 1000, 555, 35, 42 };

	SDL_Surface *pPlat = SDL_LoadBMP("images/niveaux/dimension Z/platforme.bmp");
	SDL_Texture *pTexturePlat = SDL_CreateTextureFromSurface(pRenderer, pPlat);

	int const tailletabCine(19);
	SDL_Texture *TabCine[tailletabCine];
	SDL_Surface *Cine;
	Cine = SDL_LoadBMP("images/niveaux/dimension Z/cinematiques2/1.bmp");
	TabCine[0] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/dimension Z/cinematiques2/2.bmp");
	TabCine[1] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/dimension Z/cinematiques2/3.bmp");
	TabCine[2] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/dimension Z/cinematiques2/4.bmp");
	TabCine[3] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/dimension Z/cinematiques2/5.bmp");
	TabCine[4] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/dimension Z/cinematiques2/6.bmp");
	TabCine[5] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/dimension Z/cinematiques2/7.bmp");
	TabCine[6] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/dimension Z/cinematiques2/8.bmp");
	TabCine[7] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/dimension Z/cinematiques2/9.bmp");
	TabCine[8] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/dimension Z/cinematiques2/10.bmp");
	TabCine[9] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/dimension Z/cinematiques2/11.bmp");
	TabCine[10] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/dimension Z/cinematiques2/12.bmp");
	TabCine[11] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/dimension Z/cinematiques2/13.bmp");
	TabCine[12] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/dimension Z/cinematiques2/14.bmp");
	TabCine[13] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/dimension Z/cinematiques2/15.bmp");
	TabCine[14] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/dimension Z/cinematiques2/16.bmp");
	TabCine[15] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/dimension Z/cinematiques2/17.bmp");
	TabCine[16] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/dimension Z/cinematiques2/18.bmp");
	TabCine[17] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/dimension Z/cinematiques2/19.bmp");
	TabCine[18] = SDL_CreateTextureFromSurface(pRenderer, Cine);

	int const nbreEnnemisBase(10);
	Perso *tabEnnemis[nbreEnnemisBase];




	int const nbrePlatform(6);
	SDL_Rect tabPlatform[nbrePlatform];

	for (int i(0); i < nbrePlatform; i++)
	{
		tabPlatform[i].w = 347;
		tabPlatform[i].h = 44;
	}


	tabEnnemis[0] = new Perso(pRenderer, 100, true, 1300, 400, "gens Z");
	tabEnnemis[1] = new Perso(pRenderer, 100, true, 1490, 0, "gens Z");
	tabEnnemis[2] = new Perso(pRenderer, 100, true, 1800, 400, "gens Z");
	tabEnnemis[3] = new Perso(pRenderer, 100, true, 3130, 0, "gens Z");
	tabEnnemis[4] = new Perso(pRenderer, 100, true, 3550, 400, "gens Z");
	tabEnnemis[5] = new Perso(pRenderer, 100, true, 3680, 0, "gens Z");
	tabEnnemis[6] = new Perso(pRenderer, 100, true, 4230, 400, "gens Z");
	tabEnnemis[7] = new Perso(pRenderer, 100, true, 5410, 0, "gens Z");
	tabEnnemis[8] = new Perso(pRenderer, 100, true, 6000, 400, "gens Z");
	tabEnnemis[9] = new Perso(pRenderer, 100, true, 6010, 0, "gens Z");

	SDL_Event event;
	for (int i(0); i < tailletabCine; i++)
	{
		SDL_RenderCopy(pRenderer, TabCine[i], NULL, NULL);
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
						if ((event.button.x > 0) && (event.button.x < largeurFenetre) && (event.button.y > 0) && (event.button.y < hauteurFenetre))
						{
							merde = false;
							break;

						}
					}
				}
			}
		}
	}

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

	Mix_Music * muuuuuuuusiiiiiiiiique;
	muuuuuuuusiiiiiiiiique = Mix_LoadMUS("musique/musique.mp3");
	Mix_VolumeMusic(MIX_MAX_VOLUME);

	Mix_PlayMusic(muuuuuuuusiiiiiiiiique, -1);

	do
	{
		Mix_RewindMusic();
		int Scrolling(0);
		bool Scrolle(false); // false : le perso se déplace, true : le fond défile
		timer fps;
		int imageParSecondes(60);
		bool quit(false);
		bool niveauFinit(false);
		bool case1estUtilisee(false);

		Fdest = { 0, 0, largeurFond, hauteurFenetre };
		destCase1 = { 1000, 555, 35, 42 };


		for (int i = 0; i < nbreEnnemisBase; i++)
			tabEnnemis[i]->setPv(200);

		tabEnnemis[0]->setDest(1300, 400);
		tabEnnemis[1]->setDest(1490, 0);
		tabEnnemis[2]->setDest(1800, 400);
		tabEnnemis[3]->setDest(3130, 0);
		tabEnnemis[4]->setDest(3550, 400);
		tabEnnemis[5]->setDest(3680, 0);
		tabEnnemis[6]->setDest(4230, 400);
		tabEnnemis[7]->setDest(5410, 0);
		tabEnnemis[8]->setDest(6000, 400);
		tabEnnemis[9]->setDest(6010, 0);

		perso.ramasserArme(pRenderer, "rein");
		perso.setDest(largeurFenetre / 2 - 100 / 2, 0);
		perso.setPv(450);
		perso.reinitialMouvement();
		


		tabPlatform[0].x = 1490;
		tabPlatform[0].y = 215;

		tabPlatform[1].x = 3130;
		tabPlatform[1].y = 355;

		tabPlatform[2].x = 3680;
		tabPlatform[2].y = 215;

		tabPlatform[3].x = 4230;
		tabPlatform[3].y = 355;

		tabPlatform[4].x = 5410;
		tabPlatform[4].y = 215;

		tabPlatform[5].x = 6010;
		tabPlatform[5].y = 215;


		while (quit == false)
		{
			fps.start();

			perso.recuperation_event(Scrolling, nbrePlatform, tabPlatform);

			for (int i = 0; i < nbreEnnemisBase; i++)
			{
				if (tabEnnemis[i]->getEstVivant() == true)
					tabEnnemis[i]->IAtiser(perso.getDest(), Scrolle, (perso.getStatus()), nbrePlatform, tabPlatform, tabEnnemis, nbreEnnemisBase, i, 250);
			}


			// ------------------------------------------------Scrolling-------------------------------------------------------------------------------------------------

			Fdest.x -= Scrolling;
			if (case1estUtilisee == false)
				destCase1.x -= Scrolling; // deplacement des boite d'arme

			for (int i(0); i < nbrePlatform; i++)
				tabPlatform[i].x -= Scrolling;


			if (Scrolling == 0)
				Scrolle = false;
			else
				Scrolle = true;



			if (Fdest.x < (-(Fdest.w) + largeurFenetre))
			{
				Fdest.x += Scrolling;
				if (case1estUtilisee == false)
					destCase1.x += Scrolling;

				for (int i(0); i < nbrePlatform; i++)
					tabPlatform[i].x += Scrolling;

				Scrolle = false;

				niveauFinit = true;
			}

			if (Fdest.x > 0)
			{
				Fdest.x += Scrolling;
				if (case1estUtilisee == false)
					destCase1.x += Scrolling;

				for (int i(0); i < nbrePlatform; i++)
					tabPlatform[i].x += Scrolling;

				Scrolle = false;
			}

			// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------
			if (case1estUtilisee == false)
			{
				if (checkCollision(destCase1, perso.getDest()) == true)	// detection collision perso/boite d'arme
				{
					srand(time(0)); // initialisation de la génération de nombre aléatoire
					int nombreAleatoire;
					nombreAleatoire = rand() % tailleTabArme;

					perso.ramasserArme(pRenderer, tabArmes[nombreAleatoire]);

					case1estUtilisee = true;
				}
			}

			if (perso.getAUneArme() == true)
			{
				for (int i(0); i < nbrePlatform; i++)  // detection collision proj perso/platform
				{
					unsigned int j(0);
					j = 0;

					for (j; j < (perso.getArme()->getDestProj().size()); j++)
					{
						if (checkCollision(tabPlatform[i], perso.getArme()->getDestProj()[j]) == true)
						{
							std::vector<SDL_Rect>::iterator iter = perso.getArme()->getDestProj().begin(); // effacage de la case contenant le rect du tir qui a touché

							for (unsigned int l(0); l < j; l++)
								iter++;

							perso.getArme()->getDestProj().erase(iter);
						}
					}
				}
			}


			for (int k(0); k < nbreEnnemisBase; k++)
			{
				if (tabEnnemis[k]->getAUneArme() == true)
				{
					for (int i(0); i < nbrePlatform; i++)  // detection collision proj perso/platform
					{
						unsigned int j(0);
						j = 0;

						for (j; j < (tabEnnemis[k]->getArme()->getDestProj().size()); j++)
						{
							if (checkCollision(tabPlatform[i], tabEnnemis[k]->getArme()->getDestProj()[j]) == true)
							{
								std::vector<SDL_Rect>::iterator iter = tabEnnemis[k]->getArme()->getDestProj().begin(); // effacage de la case contenant le rect du tir qui a touché

								for (unsigned int l(0); l < j; l++)
									iter++;

								tabEnnemis[k]->getArme()->getDestProj().erase(iter);
							}
						}
					}
				}
			}

			if (perso.getAUneArme() == true)
			{
				for (int i(0); i < nbreEnnemisBase; i++)  // detection collision entre proj perso/ennemi
				{
					unsigned int j(0);
					j = 0;

					for (j; j < (perso.getArme()->getDestProj().size()); j++)
					{
						if (tabEnnemis[i]->getEstVivant() == true)
						{
							if (checkCollision(tabEnnemis[i]->getDest(), perso.getArme()->getDestProj()[j]) == true)
								perso.infligerDegats(tabEnnemis[i], j);
						}
					}
				}
			}


			for (int i(0); i < nbreEnnemisBase; i++)  // detection collision entre proj ennemi/perso
			{
				if (tabEnnemis[i]->getAUneArme() == true)
				{
					unsigned int j(0);
					j = 0;

					for (j; j < (tabEnnemis[i]->getArme()->getDestProj().size()); j++)
					{
						if (checkCollision(perso.getDest(), (tabEnnemis[i]->getArme()->getDestProj())[j]) == true)
							tabEnnemis[i]->infligerDegats(&perso, j);

					}
				}
			}

			SDL_RenderCopy(pRenderer, pFTexture, NULL, &Fdest); // affichage fond
			for (int i(0); i < nbrePlatform; i++) // affichage plateformes
				SDL_RenderCopy(pRenderer, pTexturePlat, NULL, &tabPlatform[i]);
			if (case1estUtilisee == false) // affichage case arme
				SDL_RenderCopy(pRenderer, pTextureSprites, NULL, &destCase1);


			for (int i = 0; i < nbreEnnemisBase; i++) // Affichage ennemis
			{
				if (tabEnnemis[i]->getEstVivant() == true)
					tabEnnemis[i]->show(pRenderer, Scrolle, (perso.getStatus()), nbrePlatform, tabPlatform, Scrolling);
			}

			perso.show(pRenderer, Scrolle, (perso.getStatus()), nbrePlatform, tabPlatform, Scrolling); // affichage perso

			SDL_RenderPresent(pRenderer);

			const Uint8 *state = SDL_GetKeyboardState(NULL);
			if (state[SDL_SCANCODE_ESCAPE])
			{
				overQuit = true;
			}

			while (fps.get_ticks() < 1000 / imageParSecondes)
			{
				//...
			}

			if (perso.getEstVivant() == false)
			{
				for (int i(0); i < nbreEnnemisBase; i++)
					delete tabEnnemis[i]->getArme();
				for (int i(0); i < nbreEnnemisBase; i++)
					tabEnnemis[i]->ramasserArme(pRenderer, "pouvoir Z");

				quit = true;
			}

			if (overQuit == true || niveauFinit == true)
			{
				for (int i = 0; i < nbreEnnemisBase; i++)
				{
					delete tabEnnemis[i];
					tabEnnemis[i] = nullptr;
				}

				quit = true;
			}

		}

	} while (perso.getEstVivant() == false);

	return;
}

void niveau8(SDL_Window *pWindow, SDL_Renderer *pRenderer, Perso &perso, string tabArmes[], int tailleTabArme, bool &overQuit)
{

	SDL_Surface *pFond;
	pFond = SDL_LoadBMP("images/niveaux/route/fond.bmp");
	SDL_Texture *pFTexture = SDL_CreateTextureFromSurface(pRenderer, pFond);
	SDL_Rect Fdest = { 0, 0, largeurFond, hauteurFenetre };

	SDL_Surface *pSprites = SDL_LoadBMP("images/sprites/boiteArme/boiteArme.bmp");
	Uint32 colorkey = SDL_MapRGB(pSprites->format, 255, 255, 255);
	SDL_SetColorKey(pSprites, SDL_RLEACCEL | SDL_TRUE, colorkey);
	SDL_Texture *pTextureSprites = SDL_CreateTextureFromSurface(pRenderer, pSprites);
	SDL_Rect destCase1 = { 1000, 555, 35, 42 };

	SDL_Surface *pPlat = SDL_LoadBMP("images/niveaux/route/platforme.bmp");
	Uint32 colorkey2 = SDL_MapRGB(pPlat->format, 255, 255, 255);
	SDL_SetColorKey(pPlat, SDL_RLEACCEL | SDL_TRUE, colorkey2);
	SDL_Texture *pTexturePlat = SDL_CreateTextureFromSurface(pRenderer, pPlat);

	int const tailletabCine(13);
	SDL_Texture *TabCine[tailletabCine];
	SDL_Surface *Cine;
	Cine = SDL_LoadBMP("images/niveaux/route/cinematiques2/1.bmp");
	TabCine[0] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/route/cinematiques2/2.bmp");
	TabCine[1] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/route/cinematiques2/3.bmp");
	TabCine[2] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/route/cinematiques2/4.bmp");
	TabCine[3] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/route/cinematiques2/5.bmp");
	TabCine[4] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/route/cinematiques2/6.bmp");
	TabCine[5] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/route/cinematiques2/7.bmp");
	TabCine[6] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/route/cinematiques2/8.bmp");
	TabCine[7] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/route/cinematiques2/9.bmp");
	TabCine[8] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/route/cinematiques2/10.bmp");
	TabCine[9] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/route/cinematiques2/11.bmp");
	TabCine[10] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/route/cinematiques2/12.bmp");
	TabCine[11] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/route/cinematiques2/13.bmp");
	TabCine[12] = SDL_CreateTextureFromSurface(pRenderer, Cine);


	int const nbreEnnemisBase(11);
	Perso *tabEnnemis[nbreEnnemisBase];

	int const nbrePlatform(7);
	SDL_Rect tabPlatform[nbrePlatform];

	for (int i(0); i < nbrePlatform; i++)
	{
		tabPlatform[i].w = 347;
		tabPlatform[i].h = 44;
	}

	tabEnnemis[0] = new Perso(pRenderer, 100, true, 1420, 0, "neo nazis");
	tabEnnemis[1] = new Perso(pRenderer, 100, true, 1420, 400, "neo nazis");
	tabEnnemis[2] = new Perso(pRenderer, 100, true, 2210, 0, "neo nazis");
	tabEnnemis[3] = new Perso(pRenderer, 100, true, 2210, 400, "neo nazis");
	tabEnnemis[4] = new Perso(pRenderer, 100, true, 3390, 0, "neo nazis");
	tabEnnemis[5] = new Perso(pRenderer, 100, true, 3980, 0, "neo nazis");
	tabEnnemis[6] = new Perso(pRenderer, 100, true, 4510, 0, "neo nazis");
	tabEnnemis[7] = new Perso(pRenderer, 100, true, 5500, 0, "neo nazis");
	tabEnnemis[8] = new Perso(pRenderer, 100, true, 5800, 400, "neo nazis");
	tabEnnemis[9] = new Perso(pRenderer, 100, true, 6100, 0, "neo nazis");
	tabEnnemis[10] = new Perso(pRenderer, 100, true, 6250, 400, "neo nazis");

	SDL_Event event;
	for (int i(0); i < tailletabCine; i++)
	{
		SDL_RenderCopy(pRenderer, TabCine[i], NULL, NULL);
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
						if ((event.button.x > 0) && (event.button.x < largeurFenetre) && (event.button.y > 0) && (event.button.y < hauteurFenetre))
						{
							merde = false;
							break;

						}
					}
				}
			}
		}
	}

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

	Mix_Music * muuuuuuuusiiiiiiiiique;
	muuuuuuuusiiiiiiiiique = Mix_LoadMUS("musique/musique.mp3");
	Mix_VolumeMusic(MIX_MAX_VOLUME);

	Mix_PlayMusic(muuuuuuuusiiiiiiiiique, -1);

	do
	{
		Mix_RewindMusic();
		int Scrolling(0);
		bool Scrolle(false); // false : le perso se déplace, true : le fond défile
		timer fps;
		int imageParSecondes(60);
		bool quit(false);
		bool niveauFinit(false);
		bool case1estUtilisee(false);

		Fdest = { 0, 0, largeurFond, hauteurFenetre };
		destCase1 = { 1000, 555, 35, 42 };


		for (int i = 0; i < nbreEnnemisBase; i++)
			tabEnnemis[i]->setPv(310);

		tabEnnemis[0]->setDest(1420, 400);
		tabEnnemis[1]->setDest(1420, 0);
		tabEnnemis[2]->setDest(2210, 0);
		tabEnnemis[3]->setDest(2210, 0);
		tabEnnemis[4]->setDest(3390, 400);
		tabEnnemis[5]->setDest(3980, 400);
		tabEnnemis[6]->setDest(4510, 0);
		tabEnnemis[7]->setDest(5500, 0);
		tabEnnemis[8]->setDest(5800, 0);
		tabEnnemis[9]->setDest(6100, 0);
		tabEnnemis[10]->setDest(6250, 0);

		perso.ramasserArme(pRenderer, "rein");
		perso.setDest(largeurFenetre / 2 - 100 / 2, 0);
		perso.setPv(450);
		perso.reinitialMouvement();

		
		tabPlatform[0].x = 1420;
		tabPlatform[0].y = 355;

		tabPlatform[1].x = 2210;
		tabPlatform[1].y = 355;

		tabPlatform[2].x = 3390;
		tabPlatform[2].y = 215;

		tabPlatform[3].x = 3980;
		tabPlatform[3].y = 215;

		tabPlatform[4].x = 4510;
		tabPlatform[4].y = 215;

		tabPlatform[5].x = 5500;
		tabPlatform[5].y = 355;

		tabPlatform[6].x = 6100;
		tabPlatform[6].y = 215;

		

		

		while (quit == false)
		{
			fps.start();

			perso.recuperation_event(Scrolling, nbrePlatform, tabPlatform);

			for (int i = 0; i < nbreEnnemisBase; i++)
			{
				if (tabEnnemis[i]->getEstVivant() == true)
					tabEnnemis[i]->IAtiser(perso.getDest(), Scrolle, (perso.getStatus()), nbrePlatform, tabPlatform, tabEnnemis, nbreEnnemisBase, i, 250);
			}


			// ------------------------------------------------Scrolling-------------------------------------------------------------------------------------------------

			Fdest.x -= Scrolling;
			if (case1estUtilisee == false)
				destCase1.x -= Scrolling; // deplacement des boite d'arme

			for (int i(0); i < nbrePlatform; i++)
				tabPlatform[i].x -= Scrolling;


			if (Scrolling == 0)
				Scrolle = false;
			else
				Scrolle = true;



			if (Fdest.x < (-(Fdest.w) + largeurFenetre))
			{
				Fdest.x += Scrolling;
				if (case1estUtilisee == false)
					destCase1.x += Scrolling;

				for (int i(0); i < nbrePlatform; i++)
					tabPlatform[i].x += Scrolling;

				Scrolle = false;

				niveauFinit = true;
			}

			if (Fdest.x > 0)
			{
				Fdest.x += Scrolling;
				if (case1estUtilisee == false)
					destCase1.x += Scrolling;

				for (int i(0); i < nbrePlatform; i++)
					tabPlatform[i].x += Scrolling;

				Scrolle = false;
			}

			// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------
			if (case1estUtilisee == false)
			{
				if (checkCollision(destCase1, perso.getDest()) == true)	// detection collision perso/boite d'arme
				{
					srand(time(0)); // initialisation de la génération de nombre aléatoire
					int nombreAleatoire;
					nombreAleatoire = rand() % tailleTabArme;

					perso.ramasserArme(pRenderer, tabArmes[nombreAleatoire]);

					case1estUtilisee = true;
				}
			}

			if (perso.getAUneArme() == true)
			{
				for (int i(0); i < nbrePlatform; i++)  // detection collision proj perso/platform
				{
					unsigned int j(0);
					j = 0;

					for (j; j < (perso.getArme()->getDestProj().size()); j++)
					{
						if (checkCollision(tabPlatform[i], perso.getArme()->getDestProj()[j]) == true)
						{
							std::vector<SDL_Rect>::iterator iter = perso.getArme()->getDestProj().begin(); // effacage de la case contenant le rect du tir qui a touché

							for (unsigned int l(0); l < j; l++)
								iter++;

							perso.getArme()->getDestProj().erase(iter);
						}
					}
				}
			}


			for (int k(0); k < nbreEnnemisBase; k++)
			{
				if (tabEnnemis[k]->getAUneArme() == true)
				{
					for (int i(0); i < nbrePlatform; i++)  // detection collision proj perso/platform
					{
						unsigned int j(0);
						j = 0;

						for (j; j < (tabEnnemis[k]->getArme()->getDestProj().size()); j++)
						{
							if (checkCollision(tabPlatform[i], tabEnnemis[k]->getArme()->getDestProj()[j]) == true)
							{
								std::vector<SDL_Rect>::iterator iter = tabEnnemis[k]->getArme()->getDestProj().begin(); // effacage de la case contenant le rect du tir qui a touché

								for (unsigned int l(0); l < j; l++)
									iter++;

								tabEnnemis[k]->getArme()->getDestProj().erase(iter);
							}
						}
					}
				}
			}

			if (perso.getAUneArme() == true)
			{
				for (int i(0); i < nbreEnnemisBase; i++)  // detection collision entre proj perso/ennemi
				{
					unsigned int j(0);
					j = 0;

					for (j; j < (perso.getArme()->getDestProj().size()); j++)
					{
						if (tabEnnemis[i]->getEstVivant() == true)
						{
							if (checkCollision(tabEnnemis[i]->getDest(), perso.getArme()->getDestProj()[j]) == true)
								perso.infligerDegats(tabEnnemis[i], j);
						}
					}
				}
			}


			for (int i(0); i < nbreEnnemisBase; i++)  // detection collision entre proj ennemi/perso
			{
				if (tabEnnemis[i]->getAUneArme() == true)
				{
					unsigned int j(0);
					j = 0;

					for (j; j < (tabEnnemis[i]->getArme()->getDestProj().size()); j++)
					{
						if (checkCollision(perso.getDest(), (tabEnnemis[i]->getArme()->getDestProj())[j]) == true)
							tabEnnemis[i]->infligerDegats(&perso, j);

					}
				}
			}

			SDL_RenderCopy(pRenderer, pFTexture, NULL, &Fdest); // affichage fond
			for (int i(0); i < nbrePlatform; i++) // affichage plateformes
				SDL_RenderCopy(pRenderer, pTexturePlat, NULL, &tabPlatform[i]);
			if (case1estUtilisee == false) // affichage case arme
				SDL_RenderCopy(pRenderer, pTextureSprites, NULL, &destCase1);


			for (int i = 0; i < nbreEnnemisBase; i++) // Affichage ennemis
			{
				if (tabEnnemis[i]->getEstVivant() == true)
					tabEnnemis[i]->show(pRenderer, Scrolle, (perso.getStatus()), nbrePlatform, tabPlatform, Scrolling);
			}

			perso.show(pRenderer, Scrolle, (perso.getStatus()), nbrePlatform, tabPlatform, Scrolling); // affichage perso

			SDL_RenderPresent(pRenderer);

			const Uint8 *state = SDL_GetKeyboardState(NULL);
			if (state[SDL_SCANCODE_ESCAPE])
			{
				overQuit = true;
			}

			while (fps.get_ticks() < 1000 / imageParSecondes)
			{
				//...
			}

			if (perso.getEstVivant() == false)
			{
				for (int i(0); i < nbreEnnemisBase; i++)
					delete tabEnnemis[i]->getArme();
				for (int i(0); i < nbreEnnemisBase; i++)
					tabEnnemis[i]->ramasserArme(pRenderer, "motherphoqueur");

				quit = true;
			}

			if (overQuit == true || niveauFinit == true)
			{
				for (int i = 0; i < nbreEnnemisBase; i++)
				{
					delete tabEnnemis[i];
					tabEnnemis[i] = nullptr;
				}

				quit = true;
			}

		}

	} while (perso.getEstVivant() == false);

	return;
}

void niveau9(SDL_Window *pWindow, SDL_Renderer *pRenderer, Perso &perso, string tabArmes[], int tailleTabArme, bool &overQuit)
{

	SDL_Surface *pFond;
	pFond = SDL_LoadBMP("images/niveaux/chateau/fond.bmp");
	SDL_Texture *pFTexture = SDL_CreateTextureFromSurface(pRenderer, pFond);
	SDL_Rect Fdest = { 0, 0, largeurFond, hauteurFenetre };

	SDL_Surface *pSprites = SDL_LoadBMP("images/sprites/boiteArme/boiteArme.bmp");
	Uint32 colorkey = SDL_MapRGB(pSprites->format, 255, 255, 255);
	SDL_SetColorKey(pSprites, SDL_RLEACCEL | SDL_TRUE, colorkey);
	SDL_Texture *pTextureSprites = SDL_CreateTextureFromSurface(pRenderer, pSprites);
	SDL_Rect destCase1 = { 1000, 555, 35, 42 };

	SDL_Surface *pPlat = SDL_LoadBMP("images/niveaux/chateau/platforme.bmp");
	Uint32 colorkey2 = SDL_MapRGB(pPlat->format, 255, 255, 255);
	SDL_SetColorKey(pPlat, SDL_RLEACCEL | SDL_TRUE, colorkey2);
	SDL_Texture *pTexturePlat = SDL_CreateTextureFromSurface(pRenderer, pPlat);

	int const tailletabCine(15);
	SDL_Texture *TabCine[tailletabCine];
	SDL_Surface *Cine;
	Cine = SDL_LoadBMP("images/niveaux/chateau/cinematiques2/1.bmp");
	TabCine[0] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/chateau/cinematiques2/2.bmp");
	TabCine[1] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/chateau/cinematiques2/3.bmp");
	TabCine[2] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/chateau/cinematiques2/4.bmp");
	TabCine[3] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/chateau/cinematiques2/5.bmp");
	TabCine[4] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/chateau/cinematiques2/6.bmp");
	TabCine[5] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/chateau/cinematiques2/7.bmp");
	TabCine[6] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/chateau/cinematiques2/8.bmp");
	TabCine[7] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/chateau/cinematiques2/9.bmp");
	TabCine[8] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/chateau/cinematiques2/10.bmp");
	TabCine[9] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/chateau/cinematiques2/11.bmp");
	TabCine[10] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/chateau/cinematiques2/12.bmp");
	TabCine[11] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/chateau/cinematiques2/13.bmp");
	TabCine[12] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/chateau/cinematiques2/14.bmp");
	TabCine[13] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/chateau/cinematiques2/15.bmp");
	TabCine[14] = SDL_CreateTextureFromSurface(pRenderer, Cine);

	int const nbreEnnemisBase(13);
	Perso *tabEnnemis[nbreEnnemisBase];

	int const nbrePlatform(8);
	SDL_Rect tabPlatform[nbrePlatform];

	for (int i(0); i < nbrePlatform; i++)
	{
		tabPlatform[i].w = 347;
		tabPlatform[i].h = 44;
	}

	tabEnnemis[0] = new Perso(pRenderer, 100, true, 1250, 400, "nazis");
	tabEnnemis[1] = new Perso(pRenderer, 100, true, 1380, 0, "nazis");
	tabEnnemis[2] = new Perso(pRenderer, 100, true, 1800, 400, "nazis");
	tabEnnemis[3] = new Perso(pRenderer, 100, true, 2080, 0, "nazis");
	tabEnnemis[4] = new Perso(pRenderer, 100, true, 2400, 400, "nazis");
	tabEnnemis[5] = new Perso(pRenderer, 100, true, 3200, 400, "nazis");
	tabEnnemis[6] = new Perso(pRenderer, 100, true, 3520, 0, "nazis");
	tabEnnemis[7] = new Perso(pRenderer, 100, true, 3950, 400, "nazis");
	tabEnnemis[8] = new Perso(pRenderer, 100, true, 4780, 0, "nazis");
	tabEnnemis[9] = new Perso(pRenderer, 100, true, 4780, 400, "nazis");
	tabEnnemis[10] = new Perso(pRenderer, 100, true, 5700, 400, "nazis");
	tabEnnemis[11] = new Perso(pRenderer, 100, true, 6250, 0, "nazis");
	tabEnnemis[12] = new Perso(pRenderer, 100, true, 6250, 400, "nazis");

	SDL_Event event;
	for (int i(0); i < tailletabCine; i++)
	{
		SDL_RenderCopy(pRenderer, TabCine[i], NULL, NULL);
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
						if ((event.button.x > 0) && (event.button.x < largeurFenetre) && (event.button.y > 0) && (event.button.y < hauteurFenetre))
						{
							merde = false;
							break;

						}
					}
				}
			}
		}
	}

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

	Mix_Music * muuuuuuuusiiiiiiiiique;
	muuuuuuuusiiiiiiiiique = Mix_LoadMUS("musique/musique.mp3");
	Mix_VolumeMusic(MIX_MAX_VOLUME);

	Mix_PlayMusic(muuuuuuuusiiiiiiiiique, -1);

	do
	{
		Mix_RewindMusic();
		int Scrolling(0);
		bool Scrolle(false); // false : le perso se déplace, true : le fond défile
		timer fps;
		int imageParSecondes(60);
		bool quit(false);
		bool niveauFinit(false);
		bool case1estUtilisee(false);

		Fdest = { 0, 0, largeurFond, hauteurFenetre };
		destCase1 = { 1000, 555, 35, 42 };


		for (int i = 0; i < nbreEnnemisBase; i++)
			tabEnnemis[i]->setPv(310);

		tabEnnemis[0]->setDest(1250, 400);
		tabEnnemis[1]->setDest(1380, 0);
		tabEnnemis[2]->setDest(1800, 400);
		tabEnnemis[3]->setDest(2080, 0);
		tabEnnemis[4]->setDest(2400, 400);
		tabEnnemis[5]->setDest(3200, 400);
		tabEnnemis[6]->setDest(3520, 0);
		tabEnnemis[7]->setDest(3950, 400);
		tabEnnemis[8]->setDest(4780, 0);
		tabEnnemis[9]->setDest(4780, 400);
		tabEnnemis[10]->setDest(5700, 400);
		tabEnnemis[11]->setDest(6250, 0);
		tabEnnemis[12]->setDest(6250, 400);

		perso.ramasserArme(pRenderer, "rein");
		perso.setDest(largeurFenetre / 2 - 100 / 2, 0);
		perso.setPv(450);
		perso.reinitialMouvement();


		tabPlatform[0].x = 1380;
		tabPlatform[0].y = 215;

		tabPlatform[1].x = 2080;
		tabPlatform[1].y = 215;

		tabPlatform[2].x = 2980;
		tabPlatform[2].y = 355;

		tabPlatform[3].x = 3520;
		tabPlatform[3].y = 215;

		tabPlatform[4].x = 4060;
		tabPlatform[4].y = 215;

		tabPlatform[5].x = 4780;
		tabPlatform[5].y = 215;

		tabPlatform[6].x = 5440;
		tabPlatform[6].y = 355;

		tabPlatform[7].x = 6200;
		tabPlatform[7].y = 355;





		while (quit == false)
		{
			fps.start();

			perso.recuperation_event(Scrolling, nbrePlatform, tabPlatform);

			for (int i = 0; i < nbreEnnemisBase; i++)
			{
				if (tabEnnemis[i]->getEstVivant() == true)
					tabEnnemis[i]->IAtiser(perso.getDest(), Scrolle, (perso.getStatus()), nbrePlatform, tabPlatform, tabEnnemis, nbreEnnemisBase, i, 250);
			}


			// ------------------------------------------------Scrolling-------------------------------------------------------------------------------------------------

			Fdest.x -= Scrolling;
			if (case1estUtilisee == false)
				destCase1.x -= Scrolling; // deplacement des boite d'arme

			for (int i(0); i < nbrePlatform; i++)
				tabPlatform[i].x -= Scrolling;


			if (Scrolling == 0)
				Scrolle = false;
			else
				Scrolle = true;



			if (Fdest.x < (-(Fdest.w) + largeurFenetre))
			{
				Fdest.x += Scrolling;
				if (case1estUtilisee == false)
					destCase1.x += Scrolling;

				for (int i(0); i < nbrePlatform; i++)
					tabPlatform[i].x += Scrolling;

				Scrolle = false;

				niveauFinit = true;
			}

			if (Fdest.x > 0)
			{
				Fdest.x += Scrolling;
				if (case1estUtilisee == false)
					destCase1.x += Scrolling;

				for (int i(0); i < nbrePlatform; i++)
					tabPlatform[i].x += Scrolling;

				Scrolle = false;
			}

			// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------
			if (case1estUtilisee == false)
			{
				if (checkCollision(destCase1, perso.getDest()) == true)	// detection collision perso/boite d'arme
				{
					srand(time(0)); // initialisation de la génération de nombre aléatoire
					int nombreAleatoire;
					nombreAleatoire = rand() % tailleTabArme;

					perso.ramasserArme(pRenderer, tabArmes[nombreAleatoire]);

					case1estUtilisee = true;
				}
			}

			if (perso.getAUneArme() == true)
			{
				for (int i(0); i < nbrePlatform; i++)  // detection collision proj perso/platform
				{
					unsigned int j(0);
					j = 0;

					for (j; j < (perso.getArme()->getDestProj().size()); j++)
					{
						if (checkCollision(tabPlatform[i], perso.getArme()->getDestProj()[j]) == true)
						{
							std::vector<SDL_Rect>::iterator iter = perso.getArme()->getDestProj().begin(); // effacage de la case contenant le rect du tir qui a touché

							for (unsigned int l(0); l < j; l++)
								iter++;

							perso.getArme()->getDestProj().erase(iter);
						}
					}
				}
			}


			for (int k(0); k < nbreEnnemisBase; k++)
			{
				if (tabEnnemis[k]->getAUneArme() == true)
				{
					for (int i(0); i < nbrePlatform; i++)  // detection collision proj perso/platform
					{
						unsigned int j(0);
						j = 0;

						for (j; j < (tabEnnemis[k]->getArme()->getDestProj().size()); j++)
						{
							if (checkCollision(tabPlatform[i], tabEnnemis[k]->getArme()->getDestProj()[j]) == true)
							{
								std::vector<SDL_Rect>::iterator iter = tabEnnemis[k]->getArme()->getDestProj().begin(); // effacage de la case contenant le rect du tir qui a touché

								for (unsigned int l(0); l < j; l++)
									iter++;

								tabEnnemis[k]->getArme()->getDestProj().erase(iter);
							}
						}
					}
				}
			}

			if (perso.getAUneArme() == true)
			{
				for (int i(0); i < nbreEnnemisBase; i++)  // detection collision entre proj perso/ennemi
				{
					unsigned int j(0);
					j = 0;

					for (j; j < (perso.getArme()->getDestProj().size()); j++)
					{
						if (tabEnnemis[i]->getEstVivant() == true)
						{
							if (checkCollision(tabEnnemis[i]->getDest(), perso.getArme()->getDestProj()[j]) == true)
								perso.infligerDegats(tabEnnemis[i], j);
						}
					}
				}
			}


			for (int i(0); i < nbreEnnemisBase; i++)  // detection collision entre proj ennemi/perso
			{
				if (tabEnnemis[i]->getAUneArme() == true)
				{
					unsigned int j(0);
					j = 0;

					for (j; j < (tabEnnemis[i]->getArme()->getDestProj().size()); j++)
					{
						if (checkCollision(perso.getDest(), (tabEnnemis[i]->getArme()->getDestProj())[j]) == true)
							tabEnnemis[i]->infligerDegats(&perso, j);

					}
				}
			}

			SDL_RenderCopy(pRenderer, pFTexture, NULL, &Fdest); // affichage fond
			for (int i(0); i < nbrePlatform; i++) // affichage plateformes
				SDL_RenderCopy(pRenderer, pTexturePlat, NULL, &tabPlatform[i]);
			if (case1estUtilisee == false) // affichage case arme
				SDL_RenderCopy(pRenderer, pTextureSprites, NULL, &destCase1);


			for (int i = 0; i < nbreEnnemisBase; i++) // Affichage ennemis
			{
				if (tabEnnemis[i]->getEstVivant() == true)
					tabEnnemis[i]->show(pRenderer, Scrolle, (perso.getStatus()), nbrePlatform, tabPlatform, Scrolling);
			}

			perso.show(pRenderer, Scrolle, (perso.getStatus()), nbrePlatform, tabPlatform, Scrolling); // affichage perso

			SDL_RenderPresent(pRenderer);

			const Uint8 *state = SDL_GetKeyboardState(NULL);
			if (state[SDL_SCANCODE_ESCAPE])
			{
				overQuit = true;
			}

			while (fps.get_ticks() < 1000 / imageParSecondes)
			{
				//...
			}

			if (perso.getEstVivant() == false)
			{
				for (int i(0); i < nbreEnnemisBase; i++)
					delete tabEnnemis[i]->getArme();
				for (int i(0); i < nbreEnnemisBase; i++)
					tabEnnemis[i]->ramasserArme(pRenderer, "pistolet nazi");

				quit = true;
			}

			if (overQuit == true || niveauFinit == true)
			{
				for (int i = 0; i < nbreEnnemisBase; i++)
				{
					delete tabEnnemis[i];
					tabEnnemis[i] = nullptr;
				}

				quit = true;
			}

		}

	} while (perso.getEstVivant() == false);

	return;
}

void combatFinal(SDL_Window *pWindow, SDL_Renderer *pRenderer, Perso &perso, std::string tabArmes[], int tailleTabArme, bool &overQuit)
{

	SDL_Surface *pFond;
	pFond = SDL_LoadBMP("images/niveaux/boss/galaxie.bmp");
	SDL_Texture *pFTexture = SDL_CreateTextureFromSurface(pRenderer, pFond);
	SDL_Rect Fdest = { 0, 0, largeurFenetre, hauteurFenetre };

	SDL_Surface *pPlat = SDL_LoadBMP("images/niveaux/boss/platforme.bmp");
	Uint32 colorkey2 = SDL_MapRGB(pPlat->format, 255, 255, 255);
	SDL_SetColorKey(pPlat, SDL_RLEACCEL | SDL_TRUE, colorkey2);
	SDL_Texture *pTexturePlat = SDL_CreateTextureFromSurface(pRenderer, pPlat);

	int const tailletabCine(19);
	SDL_Texture *TabCine[tailletabCine];
	SDL_Surface *Cine;
	Cine = SDL_LoadBMP("images/niveaux/boss/cinematiques2/1.bmp");
	TabCine[0] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/boss/cinematiques2/2.bmp");
	TabCine[1] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/boss/cinematiques2/3.bmp");
	TabCine[2] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/boss/cinematiques2/4.bmp");
	TabCine[3] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/boss/cinematiques2/5.bmp");
	TabCine[4] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/boss/cinematiques2/6.bmp");
	TabCine[5] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/boss/cinematiques2/7.bmp");
	TabCine[6] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/boss/cinematiques2/8.bmp");
	TabCine[7] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/boss/cinematiques2/9.bmp");
	TabCine[8] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/boss/cinematiques2/10.bmp");
	TabCine[9] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/boss/cinematiques2/11.bmp");
	TabCine[10] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/boss/cinematiques2/12.bmp");
	TabCine[11] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/boss/cinematiques2/13.bmp");
	TabCine[12] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/boss/cinematiques2/14.bmp");
	TabCine[13] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/boss/cinematiques2/15.bmp");
	TabCine[14] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/boss/cinematiques2/16.bmp");
	TabCine[15] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/boss/cinematiques2/17.bmp");
	TabCine[16] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/boss/cinematiques2/18.bmp");
	TabCine[17] = SDL_CreateTextureFromSurface(pRenderer, Cine);
	Cine = SDL_LoadBMP("images/niveaux/boss/cinematiques2/19.bmp");
	TabCine[18] = SDL_CreateTextureFromSurface(pRenderer, Cine);

	int const nbreEnnemisBase(1);
	Perso *tabEnnemis[nbreEnnemisBase];

	int const nbrePlatform(1);
	SDL_Rect tabPlatform[nbrePlatform];

	for (int i(0); i < nbrePlatform; i++)
	{
		tabPlatform[i].w = 347;
		tabPlatform[i].h = 44;
	}

	tabEnnemis[0] = new Perso(pRenderer, 1000, true, 850, 286, "boss");

	int partiCombat(1);

	SDL_Event event;
	for (int i(0); i < tailletabCine; i++)
	{
		SDL_RenderCopy(pRenderer, TabCine[i], NULL, NULL);
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
						if ((event.button.x > 0) && (event.button.x < largeurFenetre) && (event.button.y > 0) && (event.button.y < hauteurFenetre))
						{
							merde = false;
							break;

						}
					}
				}
			}
		}
	}
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

	Mix_Music * muuuuuuuusiiiiiiiiique;
	muuuuuuuusiiiiiiiiique = Mix_LoadMUS("musique/musique.mp3");
	Mix_VolumeMusic(MIX_MAX_VOLUME);

	Mix_PlayMusic(muuuuuuuusiiiiiiiiique, -1);

	do
	{
		Mix_RewindMusic();
		int Scrolling(0);
		bool Scrolle(false); // false : le perso se déplace, true : le fond défile
		timer fps;
		int imageParSecondes(60);
		bool quit(false);
		bool niveauFinit(false);

		Fdest = { 0, 0, largeurFenetre, hauteurFenetre };
		
		if (partiCombat == 1)
			tabEnnemis[0]->setPv(1000);
		else if (partiCombat == 2)
			tabEnnemis[0]->setPv(1551);

		tabEnnemis[0]->setDest(850, 286);


		srand(time(0)); 
		int nombreAleatoire;
		nombreAleatoire = rand() % tailleTabArme;
		perso.ramasserArme(pRenderer, tabArmes[nombreAleatoire]);
		perso.setDest(260, 0);
		perso.setEstSurPlatform(false); // NUL - trouver un moyen de modifier 
		perso.setPv(450);
		perso.reinitialMouvement();

		tabPlatform[0].x = 260;
		tabPlatform[0].y = 355;

		


		while (quit == false)
		{
			fps.start();
				
			perso.recuperation_event(Scrolling, nbrePlatform, tabPlatform);

			tabEnnemis[0]->IAtiser(perso.getDest(), Scrolle, (perso.getStatus()), nbrePlatform, tabPlatform, tabEnnemis, nbreEnnemisBase, 0, 0, true, perso.getEstSurPlatforme(), perso.getEstAccroupi(), partiCombat);
			if (tabEnnemis[0]->getPv() <= 500 && tabEnnemis[0]->getPv() > (500 - perso.getArme()->getDegats()) && partiCombat == 1)
			{
				tabEnnemis[0]->ramasserArme(pRenderer, "rayon de la joie et de l'allegresse");
				partiCombat = 2; 
			}

			if (perso.getAUneArme() == true)
			{
				for (int i(0); i < nbrePlatform; i++)  // detection collision proj perso/platform
				{
					unsigned int j(0);
					j = 0;

					for (j; j < (perso.getArme()->getDestProj().size()); j++)
					{
						if (checkCollision(tabPlatform[i], perso.getArme()->getDestProj()[j]) == true)
						{
							std::vector<SDL_Rect>::iterator iter = perso.getArme()->getDestProj().begin(); // effacage de la case contenant le rect du tir qui a touché

							for (unsigned int l(0); l < j; l++)
								iter++;

							perso.getArme()->getDestProj().erase(iter);
						}
					}
				}
			}


			for (int k(0); k < nbreEnnemisBase; k++)
			{
				if (tabEnnemis[k]->getAUneArme() == true)
				{
					for (int i(0); i < nbrePlatform; i++)  // detection collision proj ennemi/platform
					{
						unsigned int j(0);
						j = 0;

						for (j; j < (tabEnnemis[k]->getArme()->getDestProj().size()); j++)
						{
							if (checkCollision(tabPlatform[i], tabEnnemis[k]->getArme()->getDestProj()[j]) == true)
							{
								std::vector<SDL_Rect>::iterator iter = tabEnnemis[k]->getArme()->getDestProj().begin(); // effacage de la case contenant le rect du tir qui a touché

								for (unsigned int l(0); l < j; l++)
									iter++;

								tabEnnemis[k]->getArme()->getDestProj().erase(iter);
							}
						}
					}
				}
			}

			if (perso.getAUneArme() == true)
			{
				for (int i(0); i < nbreEnnemisBase; i++)  // detection collision entre proj perso/ennemi
				{
					unsigned int j(0);
					j = 0;

					for (j; j < (perso.getArme()->getDestProj().size()); j++)
					{
						if (tabEnnemis[i]->getEstVivant() == true)
						{
							if (checkCollision(tabEnnemis[i]->getDest(), perso.getArme()->getDestProj()[j]) == true)
								perso.infligerDegats(tabEnnemis[i], j);
						}
					}
				}
			}


			for (int i(0); i < nbreEnnemisBase; i++)  // detection collision entre proj ennemi/perso
			{
				if (tabEnnemis[i]->getAUneArme() == true)
				{
					unsigned int j(0);
					j = 0;

					for (j; j < (tabEnnemis[i]->getArme()->getDestProj().size()); j++)
					{
						if (checkCollision(perso.getDest(), (tabEnnemis[i]->getArme()->getDestProj())[j]) == true)
							tabEnnemis[i]->infligerDegats(&perso, j);

					}
				}
			}

			SDL_RenderCopy(pRenderer, pFTexture, NULL, &Fdest); // affichage fond
			SDL_RenderCopy(pRenderer, pTexturePlat, NULL, &tabPlatform[0]);
			tabEnnemis[0]->show(pRenderer, Scrolle, (perso.getStatus()), nbrePlatform, tabPlatform, Scrolling);
			perso.show(pRenderer, Scrolle, (perso.getStatus()), nbrePlatform, tabPlatform, Scrolling, true); // affichage perso

			SDL_RenderPresent(pRenderer);

			const Uint8 *state = SDL_GetKeyboardState(NULL);
			if (state[SDL_SCANCODE_ESCAPE])
			{
				overQuit = true;
			}

			while (fps.get_ticks() < 1000 / imageParSecondes)
			{
				//...
			}

			if (perso.getEstVivant() == false)
			{
				delete tabEnnemis[0]->getArme();

				if (partiCombat == 1)
				{
					tabEnnemis[0]->ramasserArme(pRenderer, "croix");
					tabEnnemis[0]->setPalierHeros(0);
				}
				else if (partiCombat == 2)
				{
					tabEnnemis[0]->ramasserArme(pRenderer, "rayon de la joie et de l'allegresse");
					tabEnnemis[0]->resetCompteurs();
				}

				quit = true;
			}

			if (overQuit == true || niveauFinit == true)
			{
				
				delete tabEnnemis[0];
				tabEnnemis[0] = nullptr;
				

				quit = true;
			}

		}

	} while (perso.getEstVivant() == false);

	return;

}
