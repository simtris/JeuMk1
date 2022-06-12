#ifndef PERSONNAGE_H_INCLUDED
#define PERSONNAGE_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_version.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include "armes.h"



class Perso
{

public:

	Perso(SDL_Renderer *pRendererSprites, int pv, bool estMob, int positionXdebut, int positionYdebut, std::string type = "rein");
	~Perso();

	void recuperation_event(int &Scrolling, int tailleTabPLat, SDL_Rect tabPlatform[]);
	bool checkCollision(SDL_Rect A, SDL_Rect B);
	bool checkCollision(SDL_Rect A, SDL_Rect B, std::string cote);
	
	SDL_Rect getDest();
	void setDest(int positionX, int positionY);
	int getPv() { return pv; }
	void setPv(int valeur);
	int getStatus() { return status; }
	bool getEstVivant() { return estVivant; }
	Arme *getArme() { return arme; }
	bool getAUneArme() { return AUneArme; }
	bool getEstSurPlatforme() { return estSurPlatform; } // NUL
	void setEstSurPlatform(bool truc) { estSurPlatform = truc; } // NUL
	bool getEstAccroupi() { return estAccroupi; }
	void reinitialMouvement();
	
	void allerADroite(int &Scrolling, int tailleTabPLat, SDL_Rect tabPlatform[], bool boss = false);
	void allerAGauche(int &Scrolling, int tailleTabPLat, SDL_Rect tabPlatform[], bool boss = false);
	void allerADroite(bool Scrolle, int status2, int tailleTabPLat, SDL_Rect tabPlatform[]); // utilisées par 
	void allerAGauche(bool Scrolle, int status2, int tailleTabPLat, SDL_Rect tabPlatform[]);  // les mobs
	void sauter(int tailleTabPLat, SDL_Rect tabPlatform[]);
	void accroupir();

	void ramasserArme(SDL_Renderer *pRendererSprites, std::string typeArme);
	void tirer();
	void infligerDegats(Perso* cible, unsigned int positionSpriteDansTab);
	void recevoirDegats(int degatsRecus);

	void IAtiser(SDL_Rect destPerso, bool Scrolle, int status2, int tailleTabPLat, SDL_Rect tabPlatform[], Perso *tabEnnemis[], int nbreEnnemisBase, int placeDsTab, int longPatern, bool boss = false, bool herosSautePas = NULL, bool herosAccroupi = NULL, int partiCombat = NULL);
	void show(SDL_Renderer *pRendererSprites, bool Scrolle, int status2, int tailleTabPLat, SDL_Rect tabPlatform[], int &Scrolling, bool boss = false);

	void setPalierHeros(int valeur) { palierHeros = valeur; } // NUL TROUVER AUTRE MOYEN
	void resetCompteurs() { compteur35000 = 0; compteur666 = 0; } // NUL

private:

	Arme *arme;

	int pv;
	bool estVivant;
	bool const estMob;
	std::string type;

	int largeur;
	int hauteur;
	int positionXDebut;
	int positionXMap;
	bool veutAllerD;
	bool veutAllerG;

	bool estAccroupi;
	bool veutSaccroupir;

	bool seDeplace;
	bool estSurPlatform;

	bool veutSauter;
	bool saute;
	int hauteurSaut;
	int vitesseSaut;
	int positionYDebutSaut;

	bool recoitDegats;

	int status; // 0 pour gauche, 1 pour droite
	int frame;
	int frame2;
	int vitesseScrolling;

	int compteur;
	int compteur2;
	int compteur3;
	int compteur4;
	int compteur5;
	int compteur6;

	bool AUneArme; // dit si on affiche l'animation avec ou sans arme 
	bool veutTirer;
	bool tire;
	bool ramasseArme;

	SDL_Event event;
	SDL_Event event2;

	SDL_Surface* pSprites;
	SDL_Surface *pBarreVie;
	SDL_Texture *pTextureSprites;
	SDL_Texture *pTextureSprites2;
	SDL_Texture *pTextureVie;
	SDL_Rect destSprites;

	SDL_Rect AnimGauche[13];
	SDL_Rect AnimDroite[13];
	SDL_Rect Saut[2];
	SDL_Rect AccroupiD[3];
	SDL_Rect AccroupiG[3];
	
	SDL_Rect BarreVieSrc;
	SDL_Rect BarreVieDest;

	int palierHeros; // 0 sol, 1 plateforme - NUL TROUVER AUTRE CHOSE
	int compteur35000; // NUL
	int compteur666; // NUL

};

#endif 