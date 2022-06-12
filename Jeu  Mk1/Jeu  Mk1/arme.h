#ifndef ARME_H_INCLUDED
#define ARME_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_version.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#include <string.h>

class Arme
{
public:

	Arme();

	bool checkCollision(SDL_Rect A, SDL_Rect B);

	SDL_Texture* getText() { return pTextureSpritesArme; }
	SDL_Rect getDestArmeG() { return DestArme[0]; }
	SDL_Rect getSautArmeG() { return SautArme[0]; }
	SDL_Rect getDestArmeD() { return DestArme[1]; }

	virtual void setDestArme(int positionYPerso, int positionXPerso, int frame, int frame2, bool estSurPlat, bool estAccroupi) = 0;

	SDL_Rect getSautArmeD() { return SautArme[1]; }
	SDL_Rect getSpriteProjG() { return SpriteProjectile[0]; }
	SDL_Rect getSpriteProjD() { return SpriteProjectile[1]; }
	SDL_Rect getAnimTirDroit(int frame) { return AnimTirDroite[frame]; }
	SDL_Rect getAnimTirGauche(int frame) { return AnimTirGauche[frame]; } 
	SDL_Rect getAccroupiD(int frame) { return AccroupiD[frame]; }
	SDL_Rect getAccroupiG(int frame) { return AccroupiG[frame]; }
	
	SDL_Rect getRectNom() { return Nom; }
	SDL_Rect getDestNom() { return DestNom; }

	std::vector<SDL_Rect>& getDestProj() { return DestProjectile; }
	
	int getVitesseProj() { return vitesseProj; }
	void setVitesseProj(int valeur) { vitesseProj = valeur; }
	
    void deplacerProj(int i, char sens);
	void remplirTabProj(SDL_Rect positionPerso, char direction, std::string nomArme, bool herosAccroupi = NULL);
	
	int getLargeurArme() { return largeurArme; }
	int getHauteurArme() { return hauteurArme; }
	int getLargeurProj() { return largeurProj; }
	int getHauteurProj() { return hauteurProj; }
	std::string getNom() { return nomArme; }
	int getDegats() { return degats; }
	int getCadTir() { return cadenceTir; }

	bool getPeutTirer() { return peutTirer; }
	void setPeutTirer(bool valeur) { peutTirer = valeur; }

	Mix_Chunk *getPAN(){ return PAN; }


protected:

	std::string nomArme;
	int degats;
	int cadenceTir;
	int largeurArme;
	int hauteurArme;
	int largeurProj;
	int hauteurProj;
	int vitesseProj;

	bool peutTirer; // Gère cadence de tir ( se remet en true quand l'anim du tire précédent se termine )
	bool estRamassee;

	Mix_Chunk *PAN;

	std::vector<SDL_Rect>DestProjectile;
	std::vector<SDL_Rect>::iterator iter;
	SDL_Rect SpriteProjectile[2];

	SDL_Surface* pSpritesArme;
	SDL_Texture *pTextureSpritesArme;

	SDL_Rect AnimTirDroite[6];
	SDL_Rect AnimTirGauche[6];
	SDL_Rect AccroupiD[3];
	SDL_Rect AccroupiG[3];
	SDL_Rect DestArme[2];  // 0 pour gauche, 1 pour droite
	SDL_Rect SautArme[2];
	SDL_Rect Nom;
	SDL_Rect DestNom;


};

#endif 