
#include <SDL2/SDL.h>
#include <SDL2/SDL_version.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <string.h>
#include <iostream>
#include <vector> 
#include <stdio.h>
#include "personnage.h"
#include "armes.h"



#define largeurFenetre 1300
#define hauteurFenetre 700
#define largeurFond 8000

#define vitScrollHeros 8


	
Perso::Perso(SDL_Renderer *pRendererSprites, int pv, bool estMob, int positionXdebut, int positionYDebut, std::string type) : largeur(100), hauteur(200), positionXDebut(positionXdebut), positionXMap(positionXdebut), frame(0), vitesseScrolling(vitScrollHeros), status(1), compteur(0), compteur2(-1), compteur3(0), compteur4(-1), seDeplace(false), estSurPlatform(false), saute(false), veutSauter(false), veutAllerD(false), veutAllerG(false), vitesseSaut(15), hauteurSaut(280), AUneArme(false), veutTirer(false), tire(false), pv(pv), estVivant(true), frame2(0), recoitDegats(false), compteur5(0), compteur6(0), estMob(estMob), ramasseArme(false), estAccroupi(false), veutSaccroupir(false), type(type), palierHeros(0), compteur35000(0), compteur666(0)
{

	if (estMob == false)
	{
		pSprites = SDL_LoadBMP("images/sprites/personnage/gentil/feuilleSprite.bmp");
		pBarreVie = SDL_LoadBMP("images/menu/vie.bmp");
		Uint32 colorkey = SDL_MapRGB(pBarreVie->format, 255, 255, 255);
		SDL_SetColorKey(pBarreVie, SDL_RLEACCEL | SDL_TRUE, colorkey);
		pTextureVie = SDL_CreateTextureFromSurface(pRendererSprites, pBarreVie);
	}
	else
	{
		if (type == "bucherons canadiens")
		{
			pSprites = SDL_LoadBMP("images/sprites/personnage/mechant/bucherons canadiens/feuilleSprite.bmp");
			ramasserArme(pRendererSprites, "hache");
		}
		else if (type == "punks de l'espace")
		{
			pSprites = SDL_LoadBMP("images/sprites/personnage/mechant/punks de l'espace/feuilleSprite.bmp");
			ramasserArme(pRendererSprites, "bazookat");
		}
		else if (type == "hommes prehistoriques")
		{
			pSprites = SDL_LoadBMP("images/sprites/personnage/mechant/hommes prehistoriques/feuilleSprite.bmp");
			ramasserArme(pRendererSprites, "gourdin");
		}
		else if (type == "scientifiques")
		{
			pSprites = SDL_LoadBMP("images/sprites/personnage/mechant/scientifiques/feuilleSprite.bmp");
			ramasserArme(pRendererSprites, "pistolet cool");
		}
		else if (type == "robots du futur")
		{
			pSprites = SDL_LoadBMP("images/sprites/personnage/mechant/robots du futur/feuilleSprite.bmp");
			ramasserArme(pRendererSprites, "bras robot");
		}
		else if (type == "petits gris")
		{
			pSprites = SDL_LoadBMP("images/sprites/personnage/mechant/petits gris/feuilleSprite.bmp");
			ramasserArme(pRendererSprites, "yeux laser");
		}
		else if (type == "gens Z")
		{
			pSprites = SDL_LoadBMP("images/sprites/personnage/mechant/gens Z/feuilleSprite.bmp");
			ramasserArme(pRendererSprites, "pouvoir Z");
		}
		else if(type == "nazis")
		{
			pSprites = SDL_LoadBMP("images/sprites/personnage/mechant/nazis/feuilleSprite.bmp");
			ramasserArme(pRendererSprites, "pistolet nazi");
		}
		else if (type == "neo nazis")
		{
			pSprites = SDL_LoadBMP("images/sprites/personnage/mechant/neo nazis/feuilleSprite.bmp");
			ramasserArme(pRendererSprites, "motherphoqueur");
		}
		else if (type == "boss")
		{
			pSprites = SDL_LoadBMP("images/sprites/personnage/mechant/boss/feuilleSprite.bmp");
			ramasserArme(pRendererSprites, "croix");
		}


	}

	if (estMob == true)
		vitesseScrolling -= 1;

	Uint32 colorkey = SDL_MapRGB(pSprites->format, 255, 255, 255);
	SDL_SetColorKey(pSprites, SDL_RLEACCEL | SDL_TRUE, colorkey);
	pTextureSprites = SDL_CreateTextureFromSurface(pRendererSprites, pSprites);

	destSprites.x = positionXDebut;
	destSprites.y = positionYDebut;
	destSprites.h = hauteur;
	destSprites.w = largeur;

	//---------------------------------------------------------------------------------------------------------------------------------------------------

	if (type != "boss")
	{
		for (int i(0); i < 13; i++)
		{
			AnimDroite[i].x = largeur * i;
			AnimDroite[i].y = 0;
			AnimDroite[i].w = largeur;
			AnimDroite[i].h = hauteur;
		}

		for (int i(0); i < 13; i++)
		{
			AnimGauche[i].x = largeur * (12 - i);
			AnimGauche[i].y = hauteur;
			AnimGauche[i].w = largeur;
			AnimGauche[i].h = hauteur;
		}

		Saut[0].x = 0;
		Saut[0].y = 400;
		Saut[0].w = largeur;
		Saut[0].h = hauteur;

		Saut[1].x = largeur;
		Saut[1].y = 400;
		Saut[1].w = largeur;
		Saut[1].h = hauteur;

		for (int i(0); i < 3; i++)
		{
			AccroupiD[i].x = 300 + (largeur * i);
			AccroupiD[i].y = 400;
			AccroupiD[i].w = largeur;
			AccroupiD[i].h = hauteur;
		}

		for (int i(0); i < 3; i++)
		{
			AccroupiG[i].x = 700 + (largeur * (2 - i));
			AccroupiG[i].y = 400;
			AccroupiG[i].w = largeur;
			AccroupiG[i].h = hauteur;
		}

		BarreVieSrc = { 0, 0, 450, 30 };
		BarreVieDest = { largeurFenetre / 2 - 450 / 2, 20, 450, 30 };

	}
	else
	{
		largeur = 420;
		hauteur = 400;

		destSprites.h = hauteur;
		destSprites.w = largeur;

		status = 0;

		vitesseScrolling = 10;

		estSurPlatform = true;

		for (int i(0); i < 6; i++)
		{
			AnimGauche[i].x = 0;
			AnimGauche[i].y = hauteur * 2;
			AnimGauche[i].w = largeur;
			AnimGauche[i].h = hauteur;
		}
	}
}

Perso::~Perso()
{
	delete arme;
}

SDL_Rect Perso::getDest()
{

	return destSprites;

}

void Perso::setDest( int positionX, int positionY )
{
	destSprites.x = positionX;
	positionXMap = positionX;

	destSprites.y = positionY;
}

void Perso::setPv(int valeur)
{
	pv = valeur;

	if (pv > 0)
		estVivant = true;
	else
		estVivant = false;
}

void Perso::reinitialMouvement()
{
	veutAllerD = false;
	veutAllerG = false;
	veutSaccroupir = false;
	veutSauter = false; 
	saute = false;
	frame = 0;
}

void Perso::recuperation_event(int &Scrolling, int tailleTabPLat, SDL_Rect tabPlatform[])
{
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_UP: veutSauter = true; break;
			case SDLK_LEFT: veutAllerG = true; break;
			case SDLK_RIGHT: veutAllerD = true; break;
			case SDLK_DOWN: veutSaccroupir = true; break;
			case SDLK_SPACE: veutTirer = true; break;

			default: break;
			}
		}
	
		if (event.type == SDL_KEYUP)
		{

			switch (event.key.keysym.sym)
			{
			case SDLK_LEFT: veutAllerG = false; Scrolling = 0; frame = 0; frame2 = 0; seDeplace = false; break;
			case SDLK_RIGHT: veutAllerD = false;  Scrolling = 0; frame = 0; frame2 = 0; seDeplace = false; break;
			case SDLK_DOWN: veutSaccroupir = false; if (estAccroupi == true){ destSprites.y -= 50; } estAccroupi = false; frame2 = 0; break;
			case SDLK_SPACE: veutTirer = false; break;

			default: break;
			}
		}
	}

}

bool Perso::checkCollision(SDL_Rect A, SDL_Rect B)
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

bool Perso::checkCollision(SDL_Rect A, SDL_Rect B, std::string cote)
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

	if (cote == "bas")
	{
		if (estAccroupi == false && basA >= hautB && basA < hautB + vitesseSaut )
		{
			if (droiteA >= gaucheB && gaucheA <= droiteB)
				return true;
		}
		else if (estAccroupi == true && basA >= hautB + 50 && basA < hautB + vitesseSaut + 50)
		{
			if (droiteA >= gaucheB && gaucheA <= droiteB)
				return true;
		}

		return false;
	}
	else if (cote == "gauche")
	{
		if (gaucheA <= droiteB && gaucheA > droiteB - vitesseScrolling*2 ) // le *2 par pur sécurité
		{
			if (hautA <= basB && basA >= hautB)
				return true;
		}

		return false;
	}
	else if (cote == "droite")
	{
		if (droiteA >= gaucheB && droiteA < gaucheB + vitesseScrolling*2)
		{
			if (hautA <= basB && basA >= hautB)
				return true;
		}

		return false;
	}
	else if (cote == "haut")
	{
		if (hautA <= basB && hautA > basB - vitesseSaut)
		{
			if (droiteA >= gaucheB && gaucheA <= droiteB)
				return true;
		}

		return false;
	}
	else
		return false;
}

void Perso::allerADroite(int &Scrolling, int tailleTabPLat, SDL_Rect tabPlatform[], bool boss)
{
	if (estMob == true)
		return;

	destSprites.x += vitesseScrolling;
	positionXMap += vitesseScrolling;

	for (int i(0); i < tailleTabPLat; i++)
	{
		if (checkCollision(destSprites, tabPlatform[i], "droite") == true)
		{
			destSprites.x -= vitesseScrolling;
			positionXMap -= vitesseScrolling;
			Scrolling = 0;
			seDeplace = false;
			break;
		}
		else
		{
			if (i == (tailleTabPLat - 1))
			{
				if (destSprites.x < (largeurFenetre / 8) * 4.5 - largeur / 2)
					Scrolling = 0;
				else
				{
					if (boss == false )
					{
						Scrolling = 0;
						Scrolling += vitesseScrolling;
						destSprites.x -= vitesseScrolling;
					}
					else if (destSprites.x + largeur > 850)
						destSprites.x -= vitesseScrolling;


				}

				seDeplace = true;

			}
		}
	}

	status = 1;

	//----------------------------------------GESTION ANIMATION----------------------------------------------------------------------------------------

	if (frame == 0)
		frame = 1;

	compteur++;
	if (compteur == 3)
	{
		frame++;
		compteur = 0;
	}


	if (frame == 13)
		frame = 1;
}

void Perso::allerAGauche(int &Scrolling, int tailleTabPLat, SDL_Rect tabPlatform[], bool boss)
{
	if (estMob == true)
		return;

	destSprites.x -= vitesseScrolling;
	positionXMap -= vitesseScrolling;


	for (int i(0); i < tailleTabPLat; i++)
	{
		if (checkCollision(destSprites, tabPlatform[i], "gauche") == true)
		{
			destSprites.x += vitesseScrolling;
			positionXMap += vitesseScrolling;
			Scrolling = 0;
			seDeplace = false;
			break;		
		}
		else
		{
			if (i == (tailleTabPLat - 1))
			{
				if (destSprites.x > largeurFenetre / 8 * 3.5 - largeur / 2) // Si le perso est entre le 1er 1/4 et le 3e 1/4, c'est le perso qui se deplace, sinon, c'est le fond qui défile
					Scrolling = 0;
				else
				{
					if (boss == false)
					{
					Scrolling = 0;
					Scrolling -= vitesseScrolling;
					destSprites.x += vitesseScrolling;
					}
					else if (destSprites.x < 0)
						destSprites.x += vitesseScrolling;

				}
	
				seDeplace = true;

			}
		}
	}

	status = 0;


	//----------------------------------------GESTION ANIMATION----------------------------------------------------------------------------------------

	if (frame == 0)
		frame = 1;

	compteur++;
	if (compteur == 3)
	{
		frame++;
		compteur = 0;
	}

	if (frame == 13)
		frame = 1;

}

void Perso::allerADroite(bool Scrolle, int status2, int tailleTabPLat, SDL_Rect tabPlatform[])
{

	if (estMob == false)
		return;


	status = 1;

	if (Scrolle == true && status != status2)
		destSprites.x += vitesseScrolling + vitScrollHeros;
	else if (Scrolle == true && status == status2)
		destSprites.x -= (vitScrollHeros - vitesseScrolling);
	else if (Scrolle == false)
		destSprites.x += vitesseScrolling;

	positionXMap += vitesseScrolling;

	for (int i(0); i < tailleTabPLat; i++)
	{
		if (checkCollision(destSprites, tabPlatform[i], "droite") == true)
		{
				destSprites.x -= vitesseScrolling;
				positionXMap -= vitesseScrolling;
				seDeplace = false;
				break;
		}
		else
		{
			if (i == (tailleTabPLat - 1))
				seDeplace = true;
		}
	}


	//----------------------------------------GESTION ANIMATION----------------------------------------------------------------------------------------

	if (frame == 0)
		frame = 1;

	compteur++;
	if (compteur == 3)
	{
		frame++;
		compteur = 0;
	}


	if (frame == 13)
		frame = 1;
}

void Perso::allerAGauche(bool Scrolle, int status2, int tailleTabPLat, SDL_Rect tabPlatform[])
{
	if (estMob == false)
		return;

	status = 0;

	if (Scrolle == true && status != status2)
		destSprites.x -= vitesseScrolling + vitScrollHeros;
	else if (Scrolle == true && status == status2)
		destSprites.x += (vitScrollHeros - vitesseScrolling);
	else if (Scrolle == false)
		destSprites.x -= vitesseScrolling;

	positionXMap -= vitesseScrolling;

	for (int i(0); i < tailleTabPLat; i++)
	{
		if (checkCollision(destSprites, tabPlatform[i], "gauche") == true)
		{
			destSprites.x += vitesseScrolling;
			positionXMap += vitesseScrolling;
			seDeplace = false;
			break;
		}
		else
		{
			if (i == (tailleTabPLat - 1))
				seDeplace = true;
		}
	}
	

	//----------------------------------------GESTION ANIMATION----------------------------------------------------------------------------------------

	if (frame == 0)
		frame = 1;

	compteur++;
	if (compteur == 3)
	{
		frame++;
		compteur = 0;
	}

	if (frame == 13)
		frame = 1;

}

void Perso::sauter(int tailleTabPLat, SDL_Rect tabPlatform[])
{

	if ((estSurPlatform == true) || (saute == true))
	{
		if (saute == false)
			positionYDebutSaut = destSprites.y;

		destSprites.y -= vitesseSaut;
		for (int i(0); i < tailleTabPLat; i++)
		{
			if (checkCollision(destSprites, tabPlatform[i], "haut") == true)
			{
				destSprites.y += vitesseSaut;
				saute = false;
				veutSauter = false;
				break;
			}
			else
			{
				if (i == (tailleTabPLat - 1))
				{
					saute = true;
					estSurPlatform = false;
				}
			}
		}

		if (destSprites.y <= (positionYDebutSaut - hauteurSaut))
		{
			saute = false;
			veutSauter = false;
		}
	}
	else
	{
		veutSauter = false;
		return;
	}


}

void Perso::accroupir()
{
	if (saute == false)
	{
		if (estAccroupi == false)
			destSprites.y += 50;
		

		estAccroupi = true;

		if (seDeplace == false)
		{
			frame2 = 0;
			return;
		}

		if (frame2 == 0)
			frame = 1;

		compteur6++;
		if (compteur6 == 10)
		{
			frame2++;
			compteur6 = 0;
		}

		if (frame2 == 3)
			frame2 = 1;
	}
	else
	{
		if (estAccroupi == true)
			destSprites.y -= 50;

		estAccroupi = false;
		compteur6 = 0;
		frame2 = 0;

		return;
	}
}

void Perso::ramasserArme(SDL_Renderer *pRendererSprites, std::string nomArme)
{
	if (nomArme == "lance-roquette")
		arme = new LanceRoquette(pRendererSprites);
	else if (nomArme == "pistolait")
		arme = new Pistolait(pRendererSprites);
	else if (nomArme == "magnum")
		arme = new Magnum(pRendererSprites);
	else if (nomArme == "bazookat")
		arme = new Bazookat(pRendererSprites);
	else if (nomArme == "fusil a pompe")
		arme = new FusilAPompe(pRendererSprites);
	else if (nomArme == "chat-crame")
		arme = new ChatCrame(pRendererSprites);
	else if (nomArme == "a-caca-rantesept")
		arme = new ACaca(pRendererSprites);
	else if (nomArme == "hache")
		arme = new Hache(pRendererSprites);
	else if (nomArme == "gourdin")
		arme = new Gourdin(pRendererSprites);
	else if (nomArme == "pistolet cool")
		arme = new PistoletCool(pRendererSprites);
	else if (nomArme == "bras robot")
		arme = new BrasRobot(pRendererSprites);
	else if (nomArme == "yeux laser")
		arme = new YeuxLaser(pRendererSprites);
	else if (nomArme == "pouvoir Z")
		arme = new PouvoirZ(pRendererSprites);
	else if (nomArme == "pistolet nazi")
		arme = new PistoletNazi(pRendererSprites);
	else if (nomArme == "motherphoqueur")
		arme = new Motherphoqueur(pRendererSprites);
	else if (nomArme == "croix")
		arme = new Croix(pRendererSprites);
	else if (nomArme == "rayon de la joie et de l'allegresse")
		arme = new RayonDeLaJoieEtDeLallegresse(pRendererSprites);
	else if (nomArme == "rein")
	{
		delete arme;
		arme = nullptr;

		AUneArme = false;
		return;
	}
	else
		return;

	AUneArme = true;

	if (estMob == false)
		ramasseArme = true;
}

void Perso::tirer()
{
	if (arme->getPeutTirer() == true || tire == true || compteur4 >= 6)
	{
		if (compteur4 == -1)
		{
			tire = true;
			arme->setPeutTirer(false);

			if (status == 0)
			{
				if (arme->getNom() == "chat-crame")
					arme->remplirTabProj(destSprites, 'g', arme->getNom(), estAccroupi);
				else
					arme->remplirTabProj(destSprites, 'g', arme->getNom());

				compteur4++;
			}
			else if (status == 1)
			{
				if (arme->getNom() == "chat-crame")
					arme->remplirTabProj(destSprites, 'd', arme->getNom(), estAccroupi);
				else
					arme->remplirTabProj(destSprites, 'd', arme->getNom());

				compteur4++;
			}

			Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
			Mix_Volume(2, 50);

			if (type == "rein")
				Mix_PlayChannel(2, arme->getPAN(), 0);
			else
				Mix_PlayChannel(3, arme->getPAN(), 0);
		}

		compteur3++;

		if (compteur3 == 4)
		{
			compteur3 = 0;
			compteur4++;
		}

		if (compteur4 == arme->getCadTir() || compteur4 == 6 && arme->getCadTir() < 6)
		{
			if (compteur4 == arme->getCadTir())
				arme->setPeutTirer(true);

			if (compteur4 == 6)
			{
				tire = false;
				compteur4 = -1;
			}

		}
		else if (compteur4 == arme->getCadTir() || compteur4 == 6 && arme->getCadTir() >= 6)
		{
			if (compteur4 == 6)
				tire = false;

			if (compteur4 == arme->getCadTir())
			{
				arme->setPeutTirer(true);
				compteur4 = -1;
			}

		}

		if (veutTirer == true && arme->getPeutTirer() == true)
		{
			tire = false; // si cadTir < 6
			compteur4 = -1;

			if (type == "boss")
				veutTirer = false;



		}
	}
	else
		return;
}

void Perso::infligerDegats(Perso* cible, unsigned int positionSpriteDansTab)
{
	cible->recevoirDegats(arme->getDegats());

	std::vector<SDL_Rect>::iterator iter = arme->getDestProj().begin();

	for (unsigned int i(0); i < positionSpriteDansTab; i++)
		iter++;

	arme->getDestProj().erase(iter);

}

void Perso::recevoirDegats(int degatsRecus)
{
	
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

	Mix_Chunk * muuuuuuuusiiiiiiiiique;
	if (type == "rein")
	{
		//muuuuuuuusiiiiiiiiique = Mix_LoadWAV("musique/personnages/perso.wav");
		muuuuuuuusiiiiiiiiique = Mix_LoadWAV("musique/personnages/mechants.wav");

		Mix_Volume(0, 125);
		Mix_PlayChannel(0, muuuuuuuusiiiiiiiiique, 0);
	}
	else if (type != "boss")
	{
			muuuuuuuusiiiiiiiiique = Mix_LoadWAV("musique/personnages/mechants.wav");
			Mix_Volume(1, 100);
			Mix_PlayChannel(1, muuuuuuuusiiiiiiiiique, 0);
		
	}
	else
	{
		muuuuuuuusiiiiiiiiique = Mix_LoadWAV("musique/personnages/boss.wav");
		Mix_PlayChannel(1, muuuuuuuusiiiiiiiiique, 0);
	}

	pv -= degatsRecus;
	
	if (pv <= 0)
	{
		estVivant = false;
		if (estMob == true)
			destSprites.y = 8000;
	}

	recoitDegats = true;

	

}

void Perso::IAtiser(SDL_Rect destPerso, bool Scrolle, int status2, int tailleTabPLat, SDL_Rect tabPlatform[], Perso *tabEnnemis[], int nbreEnnemisBase, int placeDsTab, int longPatern, bool boss, bool herosSautePas, bool herosAccroupi, int partiCombat)
{

	if (boss == false)
	{
		if (destSprites.x >= (largeurFenetre / 10) * 8 || destSprites.x + 100 <= (largeurFenetre / 10) * 2) // "ronde"
		{
			if (positionXMap < positionXDebut)
				allerADroite(Scrolle, status2, tailleTabPLat, tabPlatform);
			else if (positionXMap > positionXDebut + longPatern)
				allerAGauche(Scrolle, status2, tailleTabPLat, tabPlatform);
			else if (positionXMap >= positionXDebut && positionXMap < positionXDebut + longPatern && status == 1)
				allerADroite(Scrolle, status2, tailleTabPLat, tabPlatform);
			else if (positionXMap > positionXDebut && positionXMap <= positionXDebut + longPatern && status == 0)
				allerAGauche(Scrolle, status2, tailleTabPLat, tabPlatform);
			else if (positionXMap == positionXDebut && status == 0)
				allerADroite(Scrolle, status2, tailleTabPLat, tabPlatform);
			else if (positionXMap == positionXDebut + longPatern && status == 1)
				allerAGauche(Scrolle, status2, tailleTabPLat, tabPlatform);

			veutTirer = false;

		}
		else
		{
			if (destSprites.x > destPerso.x && destSprites.x >= destPerso.x + ((largeurFenetre / 10) * 2))
			{
				for (int i(0); i < nbreEnnemisBase; i++)
				{
					if (i == placeDsTab && placeDsTab != nbreEnnemisBase - 1)
						continue;

					if (destSprites.x > tabEnnemis[i]->getDest().x && (destSprites.x - tabEnnemis[i]->getDest().x) <= 50 && (tabEnnemis[i]->getDest().y + 100) >= destSprites.y && tabEnnemis[i]->getDest().y <= (destSprites.y + 100))
					{
						seDeplace = false;
						frame = 0;
						break;
					}

					if (i == nbreEnnemisBase - 1)
						allerAGauche(Scrolle, status2, tailleTabPLat, tabPlatform);
				}
			}

			else if (destSprites.x > destPerso.x && status == 1)
			{
				status = 0;
				frame = 0;
			}
			else if (destSprites.x < destPerso.x && destSprites.x <= destPerso.x - ((largeurFenetre / 10) * 2))
			{
				for (int i(0); i < nbreEnnemisBase; i++)
				{
					if (i == placeDsTab && placeDsTab != nbreEnnemisBase - 1)
						continue;

					if (destSprites.x < tabEnnemis[i]->getDest().x && (tabEnnemis[i]->getDest().x - destSprites.x) <= 50 && (tabEnnemis[i]->getDest().y + 100) >= destSprites.y && tabEnnemis[i]->getDest().y <= (destSprites.y + 100))
					{
						seDeplace = false;
						frame = 0;
						break;
					}

					if (i == nbreEnnemisBase - 1)
						allerADroite(Scrolle, status2, tailleTabPLat, tabPlatform);
				}
			}
			else if (destSprites.x < destPerso.x && status == 0)
			{
				status = 1;
				frame = 0;
			}
			else
			{
				seDeplace = false;
				frame = 0;
			}

			if (destSprites.x > 0 && destSprites.x < largeurFenetre && arme->getDestArmeD().y < destPerso.y + destPerso.h / 2 && (arme->getDestArmeD().y + arme->getHauteurArme()) > destPerso.y)
				veutTirer = true;
		}
	}

	else

	{
		if (partiCombat == 1)
		{
			int palierUn(286);
			int palierDeux(15);

			int objectifY;


			if (herosSautePas == true && destPerso.y > 355)
			{
				objectifY = palierUn;
				palierHeros = 0;
			}
			else if (herosSautePas == true && destPerso.y <= 355)
			{
				objectifY = palierDeux;
				palierHeros = 1;
			}
			else if (herosSautePas == false && palierHeros == 0)
				objectifY = palierUn;
			else if (herosSautePas == false && palierHeros == 1)
				objectifY = palierDeux;




			if (destSprites.y != objectifY)
			{
				if (objectifY < destSprites.y)
				{
					destSprites.y -= vitesseScrolling;

					if (destSprites.y < objectifY)
						destSprites.y = objectifY;
				}
				else if (objectifY > destSprites.y)
				{

					destSprites.y += vitesseScrolling;

					if (destSprites.y > objectifY)
						destSprites.y = objectifY;
				}
			}

			if (destSprites.y + destSprites.h / 2 < destPerso.y + destPerso.h  && destSprites.y + destSprites.h / 2 > destPerso.y && (destSprites.y < 120 || destSprites.y > 225))
				veutTirer = true;



		}

		else if (partiCombat == 2)

		{

			vitesseScrolling = 22;
			int palierUn(286);
			int palierDeux(41);
			int objectifY;
			int const tailleTab(20);
			int const tabNickeurDeRace[tailleTab] { 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1 };

			if (compteur35000 == 0 && compteur666 < 60) // pas mitraille dès le début
			{
				if (compteur666 == 0)
					veutTirer = false;

				compteur666 += 1;
			}


			if (tabNickeurDeRace[compteur35000] == 0)
				objectifY = palierUn;
			else if (tabNickeurDeRace[compteur35000] == 1)
				objectifY = palierDeux;


			if (veutTirer == false && compteur666 == 60)
			{
				if (objectifY < destSprites.y)
				{
					destSprites.y -= vitesseScrolling;

					if (destSprites.y < objectifY)
						destSprites.y = objectifY;
				}
				else if (objectifY > destSprites.y)
				{

					destSprites.y += vitesseScrolling;

					if (destSprites.y > objectifY)
						destSprites.y = objectifY;
				}

				if (destSprites.y == objectifY)
				{
					veutTirer = true;
					compteur35000 += 1;

					if (compteur35000 == tailleTab)
					{
						compteur35000  = 0;
						veutTirer = false;
					}
				}
			}
		}
	}
	
}

void Perso::show(SDL_Renderer *pRendererPoint, bool Scrolle, int status2, int tailleTabPLat, SDL_Rect tabPlatform[], int &Scrolling, bool boss )
{

	if (type != "boss")
	{
		if (estAccroupi == false && destSprites.y >= (600 - hauteur) && destSprites.y <= (600 - hauteur) + vitesseSaut) // test estSurPlatform
			estSurPlatform = true;
		else if (estAccroupi == true && destSprites.y >= (600 - hauteur) + 50 && destSprites.y <= (600 - hauteur) + vitesseSaut + 50)
			estSurPlatform = true;
		else
		{
			for (int i(0); i < tailleTabPLat; i++)
			{
				if (checkCollision(destSprites, tabPlatform[i], "bas") == true)
				{
					estSurPlatform = true;
					break;
				}
				estSurPlatform = false;
			}
		}
	}

	//------------------------------------------------------------------------------------------------------------------


	if (veutAllerD == true)
		allerADroite(Scrolling, tailleTabPLat, tabPlatform, boss);

	if (veutAllerG == true)
		allerAGauche(Scrolling, tailleTabPLat, tabPlatform, boss);

	if (AUneArme == true && (veutTirer == true || tire == true || compteur4 >= 6 && AUneArme == true))
		tirer();

	if (veutSauter == true)
		sauter(tailleTabPLat, tabPlatform);

	if (veutSaccroupir == true)
		accroupir();

	
	

	if ((saute == false) && (estSurPlatform == false) && type != "boss") // gravité
		destSprites.y += vitesseSaut;


	if (seDeplace == false && estMob == true && Scrolle == true && status2 == 0)
		destSprites.x += vitScrollHeros;
	else if (seDeplace == false && estMob == true && Scrolle == true && status2 == 1)
		destSprites.x -= vitScrollHeros;


	if (AUneArme == true)
		arme->setDestArme(destSprites.y, destSprites.x, frame, frame2, estSurPlatform, estAccroupi); // deplacement arme

	if (ramasseArme == true) //affichage nomArme
	{
		compteur2++;

		SDL_RenderCopy(pRendererPoint, arme->getText(), &(arme->getRectNom()), &(arme->getDestNom()));

		if (compteur2 == 80)
		{
			compteur2 = -1;
			ramasseArme = false;
		}
	}

	if (AUneArme == true)
	{
		for (unsigned int i(0); i < (arme->getDestProj().size()); i++) // deplacement + affichage proj

		{

			if ((arme->getDestProj())[i].x > destSprites.x)
			{
				if (Scrolle == true && status2 == 0)
				{
					arme->setVitesseProj((arme->getVitesseProj()) + vitesseScrolling);
					arme->deplacerProj(i, 'd');
					arme->setVitesseProj((arme->getVitesseProj()) - vitesseScrolling);
				}
				else if (Scrolle == true && status2 == 1)
				{
					arme->setVitesseProj((arme->getVitesseProj()) - vitesseScrolling);
					arme->deplacerProj(i, 'd');
					arme->setVitesseProj((arme->getVitesseProj()) + vitesseScrolling);
				}
				else
					arme->deplacerProj(i, 'd');

				if (arme->getDestProj()[i].x > largeurFenetre) // Suprression proj si sort de l'écran
				{
					std::vector<SDL_Rect>::iterator iter = arme->getDestProj().begin(); // effacage de la case contenant le rect du tir qui a touché

					iter += i;

					arme->getDestProj().erase(iter);

				}
				else
					SDL_RenderCopy(pRendererPoint, arme->getText(), &(arme->getSpriteProjD()), &(arme->getDestProj())[i]);
			}
			else if ((arme->getDestProj())[i].x < destSprites.x)
			{
				if (Scrolle == true && status2 == 0)
				{
					arme->setVitesseProj((arme->getVitesseProj()) - vitesseScrolling);
					arme->deplacerProj(i, 'g');
					arme->setVitesseProj((arme->getVitesseProj()) + vitesseScrolling);
				}
				else if (Scrolle == true && status2 == 1)
				{
					arme->setVitesseProj((arme->getVitesseProj()) + vitesseScrolling);
					arme->deplacerProj(i, 'g');
					arme->setVitesseProj((arme->getVitesseProj()) - vitesseScrolling);
				}
				else
					arme->deplacerProj(i, 'g');

				if (arme->getDestProj()[i].x + arme->getDestProj()[i].w < 0) // Suprression proj si sort de l'écran
				{
					std::vector<SDL_Rect>::iterator iter = arme->getDestProj().begin(); // effacage de la case contenant le rect du tir qui a touché

					iter += i;

					arme->getDestProj().erase(iter);

				}
				else
					SDL_RenderCopy(pRendererPoint, arme->getText(), &(arme->getSpriteProjG()), &(arme->getDestProj())[i]);
			}
		}
	}

	if (recoitDegats == false)
	{
		if (status == 1) // affichage perso + arme
		{
			if (AUneArme == false)
			{
				if (estSurPlatform == true && estAccroupi == false)
					SDL_RenderCopy(pRendererPoint, pTextureSprites, &AnimDroite[frame], &destSprites);
				else if (estAccroupi == true)
					SDL_RenderCopy(pRendererPoint, pTextureSprites, &AccroupiD[frame2], &destSprites);
				else
					SDL_RenderCopy(pRendererPoint, pTextureSprites, &Saut[status], &destSprites);
			}
			else
			{

				if (tire == false)
					SDL_RenderCopy(pRendererPoint, arme->getText(), &(arme->getAnimTirDroit(0)), &(arme->getDestArmeD()));
				else
					SDL_RenderCopy(pRendererPoint, arme->getText(), &(arme->getAnimTirDroit(compteur4)), &(arme->getDestArmeD()));

				if (estSurPlatform == true && estAccroupi == false)
					SDL_RenderCopy(pRendererPoint, arme->getText(), &AnimDroite[frame], &destSprites);
				else if (estAccroupi == true)
					SDL_RenderCopy(pRendererPoint, arme->getText(), &arme->getAccroupiD(frame2), &destSprites);
				else
					SDL_RenderCopy(pRendererPoint, arme->getText(), &(arme->getSautArmeD()), &destSprites);

			}

		}
		else if (status == 0)
		{
			if (AUneArme == false)
			{
				if (estSurPlatform == true && estAccroupi == false)
					SDL_RenderCopy(pRendererPoint, pTextureSprites, &AnimGauche[frame], &destSprites);
				else if (estAccroupi == true)
					SDL_RenderCopy(pRendererPoint, pTextureSprites, &AccroupiG[frame2], &destSprites);
				else
					SDL_RenderCopy(pRendererPoint, pTextureSprites, &Saut[status], &destSprites);
			}
			else
			{

				if (estSurPlatform == true && estAccroupi == false)
					SDL_RenderCopy(pRendererPoint, arme->getText(), &AnimGauche[frame], &destSprites);
				else if (estAccroupi == true)
					SDL_RenderCopy(pRendererPoint, arme->getText(), &arme->getAccroupiG(frame2), &destSprites);
				else
					SDL_RenderCopy(pRendererPoint, arme->getText(), &(arme->getSautArmeG()), &destSprites);

				if (tire == false)
					SDL_RenderCopy(pRendererPoint, arme->getText(), &(arme->getAnimTirGauche(0)), &(arme->getDestArmeG()));
				else
					SDL_RenderCopy(pRendererPoint, arme->getText(), &(arme->getAnimTirGauche(compteur4)), &(arme->getDestArmeG()));
			}

		}
	}
	else
	{
		compteur5++;
		if (compteur5 == 3)
		{
			recoitDegats = false;
			compteur5 = 0;
		}
	}
	
	BarreVieSrc.w = pv;
	BarreVieDest.w = pv;
	SDL_RenderCopy(pRendererPoint, pTextureVie, &BarreVieSrc, &BarreVieDest);

}
