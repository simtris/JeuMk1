#include <SDL2/SDL.h>
#include <SDL2/SDL_version.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include "arme.h"
#include "armes.h"

#define largeurFenetre 1300
#define hauteurFenetre 700


Pistolait::Pistolait(SDL_Renderer *pRendererSprites) : Arme()
{
	nomArme = "pistolait";
	degats = 20;
	cadenceTir = 2;
	largeurArme = 100;
	hauteurArme = 50;
	largeurProj = 30;
	hauteurProj = 50;
	vitesseProj = 30;

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	PAN = Mix_LoadWAV("musique/armes/pistolait.wav");

	pSpritesArme = SDL_LoadBMP("images/sprites/armes/gentil/pistolait/feuilleSprite.bmp");
	Uint32 colorkey = SDL_MapRGB(pSpritesArme->format, 255, 255, 255);
	SDL_SetColorKey(pSpritesArme, SDL_RLEACCEL | SDL_TRUE, colorkey);
	pTextureSpritesArme = SDL_CreateTextureFromSurface(pRendererSprites, pSpritesArme);

	SDL_RenderCopy(pRendererSprites, pTextureSpritesArme, NULL, NULL);

	//--------------------------------------------------------------------------------------------------------------

	for (int i(0); i < 6; i++)
	{
		AnimTirDroite[i].x = largeurArme * i;
		AnimTirDroite[i].y = 400;
		AnimTirDroite[i].w = largeurArme;
		AnimTirDroite[i].h = hauteurArme;
	}

	for (int i(0); i < 6; i++)
	{
		AnimTirGauche[i].x = largeurArme * (5 - i);
		AnimTirGauche[i].y = 400 + hauteurArme;
		AnimTirGauche[i].w = largeurArme;
		AnimTirGauche[i].h = hauteurArme;
	}

	SpriteProjectile[0].x = 970;
	SpriteProjectile[0].y = 400;
	SpriteProjectile[0].w = largeurProj;
	SpriteProjectile[0].h = hauteurProj;

	SpriteProjectile[1].x = 1000;
	SpriteProjectile[1].y = 400;
	SpriteProjectile[1].w = largeurProj;
	SpriteProjectile[1].h = hauteurProj;

	DestArme[0] = { 0, 0, largeurArme, hauteurArme };
	DestArme[1] = { 0, 0, largeurArme, hauteurArme };

}

void Pistolait::setDestArme(int positionYPerso, int positionXPerso, int frame, int frame2, bool estSurPlat, bool estAccroupi)
{

	if (frame == 0 || estSurPlat == false || estAccroupi == true)
	{
		DestArme[0].x = positionXPerso - 60;
		DestArme[0].y = positionYPerso + 62;

		DestArme[1].x = positionXPerso + 60;
		DestArme[1].y = positionYPerso + 60;

		return;

	}
	DestArme[0].x = positionXPerso - 70;
	DestArme[0].y = positionYPerso + 62;

	DestArme[1].x = positionXPerso + 70;
	DestArme[1].y = positionYPerso + 60;

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Magnum::Magnum(SDL_Renderer *pRendererSprites) : Arme()
{
	nomArme = "magnum";
	degats = 50;
	cadenceTir = 5;
	largeurArme = 150;
	hauteurArme = 40;
	largeurProj = 30;
	hauteurProj = 30;
	vitesseProj = 25;

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	PAN = Mix_LoadWAV("musique/armes/magnum.wav");

	pSpritesArme = SDL_LoadBMP("images/sprites/armes/gentil/magnum/feuilleSprite.bmp");
	Uint32 colorkey = SDL_MapRGB(pSpritesArme->format, 255, 255, 255);
	SDL_SetColorKey(pSpritesArme, SDL_RLEACCEL | SDL_TRUE, colorkey);
	pTextureSpritesArme = SDL_CreateTextureFromSurface(pRendererSprites, pSpritesArme);

	SDL_RenderCopy(pRendererSprites, pTextureSpritesArme, NULL, NULL);

	//--------------------------------------------------------------------------------------------------------------

	for (int i(0); i < 6; i++)
	{
		AnimTirDroite[i].x = largeurArme * i;
		AnimTirDroite[i].y = 400;
		AnimTirDroite[i].w = largeurArme;
		AnimTirDroite[i].h = hauteurArme;
	}

	for (int i(0); i < 6; i++)
	{
		AnimTirGauche[i].x = largeurArme * (5 - i);
		AnimTirGauche[i].y = 400 + hauteurArme;
		AnimTirGauche[i].w = largeurArme;
		AnimTirGauche[i].h = hauteurArme;
	}

	SpriteProjectile[0].x = 960;
	SpriteProjectile[0].y = 400;
	SpriteProjectile[0].w = largeurProj;
	SpriteProjectile[0].h = hauteurProj;

	SpriteProjectile[1].x = 1000;
	SpriteProjectile[1].y = 400;
	SpriteProjectile[1].w = largeurProj;
	SpriteProjectile[1].h = hauteurProj;

	DestArme[0] = { 0, 0, largeurArme, hauteurArme };
	DestArme[1] = { 0, 0, largeurArme, hauteurArme };

}

void Magnum::setDestArme(int positionYPerso, int positionXPerso, int frame, int frame2, bool estSurPlat, bool estAccroupi)
{

	if (frame == 0 || estSurPlat == false || estAccroupi == true)
	{
		DestArme[0].x = positionXPerso - 45;
		DestArme[0].y = positionYPerso + 68;

		DestArme[1].x = positionXPerso + 15;
		DestArme[1].y = positionYPerso + 70;

		return;

	}

	DestArme[0].x = positionXPerso - 55;
	DestArme[0].y = positionYPerso + 68;

	DestArme[1].x = positionXPerso + 20;
	DestArme[1].y = positionYPerso + 70;

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

LanceRoquette::LanceRoquette(SDL_Renderer *pRendererSprites) : Arme()
{
	nomArme = "lance-roquette";
	degats = 140;
	cadenceTir = 10;
	largeurArme = 150;
	hauteurArme = 50;
	largeurProj = 70;
	hauteurProj = 40;
	vitesseProj = 20;

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	PAN = Mix_LoadWAV("musique/armes/lance-roquette.wav");

	pSpritesArme = SDL_LoadBMP("images/sprites/armes/gentil/lance-roquette/feuilleSprite.bmp");
	Uint32 colorkey = SDL_MapRGB(pSpritesArme->format, 255, 255, 255);
	SDL_SetColorKey(pSpritesArme, SDL_RLEACCEL | SDL_TRUE, colorkey);
	pTextureSpritesArme = SDL_CreateTextureFromSurface(pRendererSprites, pSpritesArme);

	SDL_RenderCopy(pRendererSprites, pTextureSpritesArme, NULL, NULL);

	//--------------------------------------------------------------------------------------------------------------

	for (int i(0); i < 6; i++)
	{
		AnimTirDroite[i].x = largeurArme * i;
		AnimTirDroite[i].y = 400;
		AnimTirDroite[i].w = largeurArme;
		AnimTirDroite[i].h = hauteurArme;
	}

	for (int i(0); i < 6; i++)
	{
		AnimTirGauche[i].x = largeurArme * (5 - i);
		AnimTirGauche[i].y = 400 + hauteurArme;
		AnimTirGauche[i].w = largeurArme;
		AnimTirGauche[i].h = hauteurArme;
	}

	SpriteProjectile[0].x = 930;
	SpriteProjectile[0].y = 400;
	SpriteProjectile[0].w = largeurProj;
	SpriteProjectile[0].h = hauteurProj;

	SpriteProjectile[1].x = 1000;
	SpriteProjectile[1].y = 400;
	SpriteProjectile[1].w = largeurProj;
	SpriteProjectile[1].h = hauteurProj;

	DestArme[0] = { 0, 0, largeurArme, hauteurArme };
	DestArme[1] = { 0, 0, largeurArme, hauteurArme };

}

void LanceRoquette::setDestArme(int positionYPerso, int positionXPerso, int frame, int frame2, bool estSurPlat, bool estAccroupi)
{


	if (frame == 0 || estSurPlat == false || estAccroupi == true)
	{
		DestArme[0].x = positionXPerso - 52;
		DestArme[0].y = positionYPerso + 62;

		DestArme[1].x = positionXPerso + 2;
		DestArme[1].y = positionYPerso + 60;

		return;

	}

	DestArme[0].x = positionXPerso - 61;
	DestArme[0].y = positionYPerso + 62;

	DestArme[1].x = positionXPerso + 11;
	DestArme[1].y = positionYPerso + 60;

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

FusilAPompe::FusilAPompe(SDL_Renderer *pRendererSprites) : Arme()
{
	nomArme = "fusil a pompe";
	degats = 90;
	cadenceTir = 7;
	largeurArme = 150;
	hauteurArme = 40;
	largeurProj = 65;
	hauteurProj = 18;
	vitesseProj = 30;

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	PAN = Mix_LoadWAV("musique/armes/fusil a pompe.wav");

	pSpritesArme = SDL_LoadBMP("images/sprites/armes/gentil/fusil a pompe/feuilleSprite.bmp");
	Uint32 colorkey = SDL_MapRGB(pSpritesArme->format, 255, 255, 255);
	SDL_SetColorKey(pSpritesArme, SDL_RLEACCEL | SDL_TRUE, colorkey);
	pTextureSpritesArme = SDL_CreateTextureFromSurface(pRendererSprites, pSpritesArme);

	SDL_RenderCopy(pRendererSprites, pTextureSpritesArme, NULL, NULL);

	//--------------------------------------------------------------------------------------------------------------

	for (int i(0); i < 6; i++)
	{
		AnimTirDroite[i].x = largeurArme * i;
		AnimTirDroite[i].y = 400;
		AnimTirDroite[i].w = largeurArme;
		AnimTirDroite[i].h = hauteurArme;
	}

	for (int i(0); i < 6; i++)
	{
		AnimTirGauche[i].x = largeurArme * (5 - i);
		AnimTirGauche[i].y = 400 + hauteurArme;
		AnimTirGauche[i].w = largeurArme;
		AnimTirGauche[i].h = hauteurArme;
	}

	SpriteProjectile[0].x = 935;
	SpriteProjectile[0].y = 408;
	SpriteProjectile[0].w = largeurProj;
	SpriteProjectile[0].h = hauteurProj;

	SpriteProjectile[1].x = 1001;
	SpriteProjectile[1].y = 408;
	SpriteProjectile[1].w = largeurProj;
	SpriteProjectile[1].h = hauteurProj;

	DestArme[0] = { 0, 0, largeurArme, hauteurArme };
	DestArme[1] = { 0, 0, largeurArme, hauteurArme };

}

void FusilAPompe::setDestArme(int positionYPerso, int positionXPerso, int frame, int frame2, bool estSurPlat, bool estAccroupi)
{

	if (frame == 0 || estSurPlat == false || estAccroupi == true)
	{
		DestArme[0].x = positionXPerso - 66;
		DestArme[0].y = positionYPerso + 73;

		DestArme[1].x = positionXPerso + 13;
		DestArme[1].y = positionYPerso + 73;

		return;

	}

	DestArme[0].x = positionXPerso - 75;
	DestArme[0].y = positionYPerso + 73;

	DestArme[1].x = positionXPerso + 22;
	DestArme[1].y = positionYPerso + 73;

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ACaca::ACaca(SDL_Renderer *pRendererSprites) : Arme()
{
	nomArme = "a-caca-rantesept";
	degats = 55;
	cadenceTir = 4;
	largeurArme = 180;
	hauteurArme = 30;
	largeurProj = 24;
	hauteurProj = 6;
	vitesseProj = 30;

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	PAN = Mix_LoadWAV("musique/armes/a-caca-ranteSept.wav");


	pSpritesArme = SDL_LoadBMP("images/sprites/armes/gentil/a-caca-ranteSept/feuilleSprite.bmp");
	Uint32 colorkey = SDL_MapRGB(pSpritesArme->format, 255, 255, 255);
	SDL_SetColorKey(pSpritesArme, SDL_RLEACCEL | SDL_TRUE, colorkey);
	pTextureSpritesArme = SDL_CreateTextureFromSurface(pRendererSprites, pSpritesArme);

	SDL_RenderCopy(pRendererSprites, pTextureSpritesArme, NULL, NULL);

	//--------------------------------------------------------------------------------------------------------------

	for (int i(0); i < 6; i++)
	{
		AnimTirDroite[i].x = largeurArme * i;
		AnimTirDroite[i].y = 400;
		AnimTirDroite[i].w = largeurArme;
		AnimTirDroite[i].h = hauteurArme;
	}

	for (int i(0); i < 6; i++)
	{
		AnimTirGauche[i].x = largeurArme * (5 - i);
		AnimTirGauche[i].y = 400 + hauteurArme;
		AnimTirGauche[i].w = largeurArme;
		AnimTirGauche[i].h = hauteurArme;
	}

	SpriteProjectile[0].x = 996;
	SpriteProjectile[0].y = 530;
	SpriteProjectile[0].w = largeurProj;
	SpriteProjectile[0].h = hauteurProj;

	SpriteProjectile[1].x = 970;
	SpriteProjectile[1].y = 530;
	SpriteProjectile[1].w = largeurProj;
	SpriteProjectile[1].h = hauteurProj;

	DestArme[0] = { 0, 0, largeurArme, hauteurArme };
	DestArme[1] = { 0, 0, largeurArme, hauteurArme };

}

void ACaca::setDestArme(int positionYPerso, int positionXPerso, int frame, int frame2, bool estSurPlat, bool estAccroupi)
{

	if (frame == 0 || estSurPlat == false || estAccroupi == true)
	{
		DestArme[0].x = positionXPerso - 101;
		DestArme[0].y = positionYPerso + 81;

		DestArme[1].x = positionXPerso + 18;
		DestArme[1].y = positionYPerso + 81;

		return;

	}

	DestArme[0].x = positionXPerso - 110;
	DestArme[0].y = positionYPerso + 81;

	DestArme[1].x = positionXPerso + 27; 
	DestArme[1].y = positionYPerso + 81;

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ChatCrame::ChatCrame(SDL_Renderer *pRendererSprites) : Arme()
{
	nomArme = "chat-crame";
	degats = 310;
	cadenceTir = 8;
	largeurArme = 45;
	hauteurArme = 45;
	largeurProj = 82;
	hauteurProj = 72;
	vitesseProj = 20;

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	PAN = Mix_LoadWAV("musique/armes/chat-crame.wav");

	pSpritesArme = SDL_LoadBMP("images/sprites/armes/gentil/chat-crame/feuilleSprite.bmp");
	Uint32 colorkey = SDL_MapRGB(pSpritesArme->format, 255, 255, 255);
	SDL_SetColorKey(pSpritesArme, SDL_RLEACCEL | SDL_TRUE, colorkey);
	pTextureSpritesArme = SDL_CreateTextureFromSurface(pRendererSprites, pSpritesArme);

	SDL_RenderCopy(pRendererSprites, pTextureSpritesArme, NULL, NULL);

	//--------------------------------------------------------------------------------------------------------------

	for (int i(0); i < 6; i++)
	{
		AnimTirDroite[i].x = 0;
		AnimTirDroite[i].y = 404;
		AnimTirDroite[i].w = largeurArme;
		AnimTirDroite[i].h = hauteurArme;
	}

	for (int i(0); i < 6; i++)
	{
		AnimTirGauche[i].x = 0;
		AnimTirGauche[i].y = 451;
		AnimTirGauche[i].w = largeurArme;
		AnimTirGauche[i].h = hauteurArme;
	}

	SpriteProjectile[0].x = 871;
	SpriteProjectile[0].y = 410;
	SpriteProjectile[0].w = largeurProj;
	SpriteProjectile[0].h = hauteurProj;

	SpriteProjectile[1].x = 955;
	SpriteProjectile[1].y = 410;
	SpriteProjectile[1].w = largeurProj;
	SpriteProjectile[1].h = hauteurProj;

	DestArme[0] = { 0, 0, largeurArme, hauteurArme };
	DestArme[1] = { 0, 0, largeurArme, hauteurArme };

}

void ChatCrame::setDestArme(int positionYPerso, int positionXPerso, int frame, int frame2, bool estSurPlat, bool estAccroupi)
{


	if (estAccroupi == true)
	{
		DestArme[0].x = positionXPerso - 25;
		DestArme[0].y = positionYPerso + 40;
	
		DestArme[1].x = positionXPerso + 75;
		DestArme[1].y = positionYPerso + 40;

		return;

	}

	if (frame == 0 || estSurPlat == false)
	{
		DestArme[0].x = positionXPerso - 10;
		DestArme[0].y = positionYPerso + 110;

		DestArme[1].x = positionXPerso + 60;
		DestArme[1].y = positionYPerso + 110;

		return;

	}


	DestArme[0].x = positionXPerso - 16;
	DestArme[0].y = positionYPerso + 110; 

	DestArme[1].x = positionXPerso + 63;
	DestArme[1].y = positionYPerso + 110;

}


//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Bazookat::Bazookat(SDL_Renderer *pRendererSprites) : Arme()
{
	nomArme = "bazookat";
	degats = 150;
	cadenceTir = 40;
	largeurArme = 150;
	hauteurArme = 50;
	largeurProj = 40;
	hauteurProj = 50;
	vitesseProj = 15;

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	PAN = Mix_LoadWAV("musique/armes/bazookat.wav");

	pSpritesArme = SDL_LoadBMP("images/sprites/personnage/mechant/punks de l'espace/feuilleSprite.bmp");
	Uint32 colorkey = SDL_MapRGB(pSpritesArme->format, 255, 255, 255);
	SDL_SetColorKey(pSpritesArme, SDL_RLEACCEL | SDL_TRUE, colorkey);
	pTextureSpritesArme = SDL_CreateTextureFromSurface(pRendererSprites, pSpritesArme);

	SDL_RenderCopy(pRendererSprites, pTextureSpritesArme, NULL, NULL);

	//--------------------------------------------------------------------------------------------------------------

	for (int i(0); i < 6; i++)
	{
		AnimTirDroite[i].x = largeurArme * i;
		AnimTirDroite[i].y = 400;
		AnimTirDroite[i].w = largeurArme;
		AnimTirDroite[i].h = hauteurArme;
	}

	for (int i(0); i < 6; i++)
	{
		AnimTirGauche[i].x = largeurArme * (5 - i);
		AnimTirGauche[i].y = 400 + hauteurArme;
		AnimTirGauche[i].w = largeurArme;
		AnimTirGauche[i].h = hauteurArme;
	}

	SpriteProjectile[0].x = 960;
	SpriteProjectile[0].y = 400;
	SpriteProjectile[0].w = largeurProj;
	SpriteProjectile[0].h = hauteurProj;

	SpriteProjectile[1].x = 1000;
	SpriteProjectile[1].y = 400;
	SpriteProjectile[1].w = largeurProj;
	SpriteProjectile[1].h = hauteurProj;

	DestArme[0] = { 0, 0, largeurArme, hauteurArme };
	DestArme[1] = { 0, 0, largeurArme, hauteurArme };

}

void Bazookat::setDestArme(int positionYPerso, int positionXPerso, int frame, int frame2, bool estSurPlat, bool estAccroupi)
{

	if (frame == 0 || estSurPlat == false || estAccroupi == true)
	{
		DestArme[0].x = positionXPerso - 55;
		DestArme[0].y = positionYPerso + 62;

		DestArme[1].x = positionXPerso;
		DestArme[1].y = positionYPerso + 64;

		return;

	}

	DestArme[0].x = positionXPerso - 60;
	DestArme[0].y = positionYPerso + 62;

	DestArme[1].x = positionXPerso + 5;
	DestArme[1].y = positionYPerso + 64;

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Gourdin::Gourdin(SDL_Renderer *pRendererSprites) : Arme()
{
	nomArme = "gourdin";
	degats = 90;
	cadenceTir = 35;
	largeurArme = 35;
	hauteurArme = 70;
	largeurProj = 35;
	hauteurProj = 70;
	vitesseProj = 15;

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	PAN = Mix_LoadWAV("musique/armes/gourdin.wav");

	pSpritesArme = SDL_LoadBMP("images/sprites/personnage/mechant/hommes prehistoriques/feuilleSprite.bmp");
	Uint32 colorkey = SDL_MapRGB(pSpritesArme->format, 255, 255, 255);
	SDL_SetColorKey(pSpritesArme, SDL_RLEACCEL | SDL_TRUE, colorkey);
	pTextureSpritesArme = SDL_CreateTextureFromSurface(pRendererSprites, pSpritesArme);

	SDL_RenderCopy(pRendererSprites, pTextureSpritesArme, NULL, NULL);

	//--------------------------------------------------------------------------------------------------------------

	for (int i(0); i < 6; i++)
	{
		AnimTirDroite[i].x = 0;
		AnimTirDroite[i].y = 400;
		AnimTirDroite[i].w = largeurArme;
		AnimTirDroite[i].h = hauteurArme;
	}

	for (int i(0); i < 6; i++)
	{
		AnimTirGauche[i].x = 0;
		AnimTirGauche[i].y = 480;
		AnimTirGauche[i].w = largeurArme;
		AnimTirGauche[i].h = hauteurArme;
	}

	SpriteProjectile[0].x = 965;
	SpriteProjectile[0].y = 400;
	SpriteProjectile[0].w = largeurProj;
	SpriteProjectile[0].h = hauteurProj;

	SpriteProjectile[1].x = 1000;
	SpriteProjectile[1].y = 400;
	SpriteProjectile[1].w = largeurProj;
	SpriteProjectile[1].h = hauteurProj;

	DestArme[0] = { 0, 0, largeurArme, hauteurArme };
	DestArme[1] = { 0, 0, largeurArme, hauteurArme };

}

void Gourdin::setDestArme(int positionYPerso, int positionXPerso, int frame, int frame2, bool estSurPlat, bool estAccroupi)
{

	if (frame == 0 || estSurPlat == false || estAccroupi == true)
	{
		DestArme[0].x = positionXPerso + 1;
		DestArme[0].y = positionYPerso + 80;

		DestArme[1].x = positionXPerso + 68;
		DestArme[1].y = positionYPerso + 80;

		return;

	}

	DestArme[0].x = positionXPerso + 1;
	DestArme[0].y = positionYPerso + 82;

	DestArme[1].x = positionXPerso + 67;
	DestArme[1].y = positionYPerso + 80;

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Hache::Hache(SDL_Renderer *pRendererSprites) : Arme()
{
	nomArme = "hache";
	degats = 90;
	cadenceTir = 30;
	largeurArme = 40;
	hauteurArme = 70;
	largeurProj = 40;
	hauteurProj = 70;
	vitesseProj = 20;
	
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	PAN = Mix_LoadWAV("musique/armes/hache.wav");

	pSpritesArme = SDL_LoadBMP("images/sprites/personnage/mechant/bucherons canadiens/feuilleSprite.bmp");
	Uint32 colorkey = SDL_MapRGB(pSpritesArme->format, 255, 255, 255);
	SDL_SetColorKey(pSpritesArme, SDL_RLEACCEL | SDL_TRUE, colorkey);
	pTextureSpritesArme = SDL_CreateTextureFromSurface(pRendererSprites, pSpritesArme);

	SDL_RenderCopy(pRendererSprites, pTextureSpritesArme, NULL, NULL);

	//--------------------------------------------------------------------------------------------------------------

	for (int i(0); i < 6; i++)
	{
		AnimTirDroite[i].x = 0;
		AnimTirDroite[i].y = 400;
		AnimTirDroite[i].w = largeurArme;
		AnimTirDroite[i].h = hauteurArme;
	}

	for (int i(0); i < 6; i++)
	{
		AnimTirGauche[i].x = 0;
		AnimTirGauche[i].y = 480;
		AnimTirGauche[i].w = largeurArme;
		AnimTirGauche[i].h = hauteurArme;
	}

	SpriteProjectile[0].x = 960;
	SpriteProjectile[0].y = 400;
	SpriteProjectile[0].w = largeurProj;
	SpriteProjectile[0].h = hauteurProj;

	SpriteProjectile[1].x = 1000;
	SpriteProjectile[1].y = 400;
	SpriteProjectile[1].w = largeurProj;
	SpriteProjectile[1].h = hauteurProj;

	DestArme[0] = { 0, 0, largeurArme, hauteurArme };
	DestArme[1] = { 0, 0, largeurArme, hauteurArme };

}

void Hache::setDestArme(int positionYPerso, int positionXPerso, int frame, int frame2, bool estSurPlat, bool estAccroupi)
{

	if (frame == 0 || estSurPlat == false || estAccroupi == true)
	{
		DestArme[0].x = positionXPerso;
		DestArme[0].y = positionYPerso + 62;

		DestArme[1].x = positionXPerso + 60;
		DestArme[1].y = positionYPerso + 60;

		return;

	}

	DestArme[0].x = positionXPerso - 10;
	DestArme[0].y = positionYPerso + 62;

	DestArme[1].x = positionXPerso + 70;
	DestArme[1].y = positionYPerso + 60;

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

PistoletCool::PistoletCool(SDL_Renderer *pRendererSprites) : Arme()
{
	nomArme = "pistolet cool";
	degats = 90;
	cadenceTir = 20;
	largeurArme = 60;
	hauteurArme = 20;
	largeurProj = 5;
	hauteurProj = 6;
	vitesseProj = 20;

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	PAN = Mix_LoadWAV("musique/armes/pistolet cool.wav");

	pSpritesArme = SDL_LoadBMP("images/sprites/personnage/mechant/scientifiques/feuilleSprite.bmp");
	Uint32 colorkey = SDL_MapRGB(pSpritesArme->format, 255, 255, 255);
	SDL_SetColorKey(pSpritesArme, SDL_RLEACCEL | SDL_TRUE, colorkey);
	pTextureSpritesArme = SDL_CreateTextureFromSurface(pRendererSprites, pSpritesArme);

	SDL_RenderCopy(pRendererSprites, pTextureSpritesArme, NULL, NULL);

	//--------------------------------------------------------------------------------------------------------------

	for (int i(0); i < 6; i++)
	{
		AnimTirDroite[i].x = largeurArme * i;
		AnimTirDroite[i].y = 400;
		AnimTirDroite[i].w = largeurArme;
		AnimTirDroite[i].h = hauteurArme;
	}

	for (int i(0); i < 6; i++)
	{
		AnimTirGauche[i].x = largeurArme * (5 - i);
		AnimTirGauche[i].y = 400 + hauteurArme;
		AnimTirGauche[i].w = largeurArme;
		AnimTirGauche[i].h = hauteurArme;
	}

	SpriteProjectile[0].x = 994;
	SpriteProjectile[0].y = 411;
	SpriteProjectile[0].w = largeurProj;
	SpriteProjectile[0].h = hauteurProj;

	SpriteProjectile[1].x = 1001;
	SpriteProjectile[1].y = 411;
	SpriteProjectile[1].w = largeurProj;
	SpriteProjectile[1].h = hauteurProj;

	DestArme[0] = { 0, 0, largeurArme, hauteurArme };
	DestArme[1] = { 0, 0, largeurArme, hauteurArme };

}

void PistoletCool::setDestArme(int positionYPerso, int positionXPerso, int frame, int frame2, bool estSurPlat, bool estAccroupi)
{

	if (frame == 0 || estSurPlat == false || estAccroupi == true)
	{
		DestArme[0].x = positionXPerso - 34;
		DestArme[0].y = positionYPerso + 79;

		DestArme[1].x = positionXPerso + 74;
		DestArme[1].y = positionYPerso + 79;

		return;

	}
	DestArme[0].x = positionXPerso - 43;
	DestArme[0].y = positionYPerso + 81;

	DestArme[1].x = positionXPerso + 84;
	DestArme[1].y = positionYPerso + 80;

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BrasRobot::BrasRobot(SDL_Renderer *pRendererSprites) : Arme()
{
	nomArme = "bras robot";
	degats = 120;
	cadenceTir = 25;
	largeurArme = 50;
	hauteurArme = 20;
	largeurProj = 11;
	hauteurProj = 2;
	vitesseProj = 20;
	
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	PAN = Mix_LoadWAV("musique/armes/bras robot.wav");

	pSpritesArme = SDL_LoadBMP("images/sprites/personnage/mechant/robots du futur/feuilleSprite.bmp");
	Uint32 colorkey = SDL_MapRGB(pSpritesArme->format, 255, 255, 255);
	SDL_SetColorKey(pSpritesArme, SDL_RLEACCEL | SDL_TRUE, colorkey);
	pTextureSpritesArme = SDL_CreateTextureFromSurface(pRendererSprites, pSpritesArme);

	SDL_RenderCopy(pRendererSprites, pTextureSpritesArme, NULL, NULL);

	//--------------------------------------------------------------------------------------------------------------

	for (int i(0); i < 6; i++)
	{
		AnimTirDroite[i].x = 0;
		AnimTirDroite[i].y = 400;
		AnimTirDroite[i].w = largeurArme;
		AnimTirDroite[i].h = hauteurArme;
	}

	for (int i(0); i < 6; i++)
	{
		AnimTirGauche[i].x = 0;
		AnimTirGauche[i].y = 480;
		AnimTirGauche[i].w = largeurArme;
		AnimTirGauche[i].h = hauteurArme;
	}

	SpriteProjectile[0].x = 988;
	SpriteProjectile[0].y = 409;
	SpriteProjectile[0].w = largeurProj;
	SpriteProjectile[0].h = hauteurProj;

	SpriteProjectile[1].x = 1001;
	SpriteProjectile[1].y = 409;
	SpriteProjectile[1].w = largeurProj;
	SpriteProjectile[1].h = hauteurProj;

	DestArme[0] = { 0, 0, largeurArme, hauteurArme };
	DestArme[1] = { 0, 0, largeurArme, hauteurArme };

}

void BrasRobot::setDestArme(int positionYPerso, int positionXPerso, int frame, int frame2, bool estSurPlat, bool estAccroupi)
{

	if (frame == 0 || estSurPlat == false || estAccroupi == true)
	{
		DestArme[0].x = positionXPerso - 34;
		DestArme[0].y = positionYPerso + 79;

		DestArme[1].x = positionXPerso + 74;
		DestArme[1].y = positionYPerso + 79;

		return;

	}
	DestArme[0].x = positionXPerso - 63;
	DestArme[0].y = positionYPerso + 81;

	DestArme[1].x = positionXPerso + 84;
	DestArme[1].y = positionYPerso + 80;

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

YeuxLaser::YeuxLaser(SDL_Renderer *pRendererSprites) : Arme()
{
	nomArme = "yeux laser";
	degats = 120;
	cadenceTir = 20;
	largeurArme = 25;
	hauteurArme = 15;
	largeurProj = 65;
	hauteurProj = 5;
	vitesseProj = 25;

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	PAN = Mix_LoadWAV("musique/armes/yeux laser.wav");

	pSpritesArme = SDL_LoadBMP("images/sprites/personnage/mechant/petits gris/feuilleSprite.bmp");
	Uint32 colorkey = SDL_MapRGB(pSpritesArme->format, 255, 255, 255);
	SDL_SetColorKey(pSpritesArme, SDL_RLEACCEL | SDL_TRUE, colorkey);
	pTextureSpritesArme = SDL_CreateTextureFromSurface(pRendererSprites, pSpritesArme);

	SDL_RenderCopy(pRendererSprites, pTextureSpritesArme, NULL, NULL);

	//--------------------------------------------------------------------------------------------------------------

	for (int i(0); i < 6; i++)
	{
		AnimTirDroite[i].x = 0;
		AnimTirDroite[i].y = 400;
		AnimTirDroite[i].w = largeurArme;
		AnimTirDroite[i].h = hauteurArme;
	}

	for (int i(0); i < 6; i++)
	{
		AnimTirGauche[i].x = 0;
		AnimTirGauche[i].y = 480;
		AnimTirGauche[i].w = largeurArme;
		AnimTirGauche[i].h = hauteurArme;
	}

	SpriteProjectile[0].x = 935;
	SpriteProjectile[0].y = 412;
	SpriteProjectile[0].w = largeurProj;
	SpriteProjectile[0].h = hauteurProj;

	SpriteProjectile[1].x = 1001;
	SpriteProjectile[1].y = 412;
	SpriteProjectile[1].w = largeurProj;
	SpriteProjectile[1].h = hauteurProj;

	DestArme[0] = { 0, 0, largeurArme, hauteurArme };
	DestArme[1] = { 0, 0, largeurArme, hauteurArme };

}

void YeuxLaser::setDestArme(int positionYPerso, int positionXPerso, int frame, int frame2, bool estSurPlat, bool estAccroupi)
{

	if (frame == 0 || estSurPlat == false || estAccroupi == true)
	{
		DestArme[0].x = positionXPerso - 34;
		DestArme[0].y = positionYPerso + 40;

		DestArme[1].x = positionXPerso + 74;
		DestArme[1].y = positionYPerso + 40;

		return;

	}
	DestArme[0].x = positionXPerso - 63;
	DestArme[0].y = positionYPerso + 40;

	DestArme[1].x = positionXPerso + 84;
	DestArme[1].y = positionYPerso + 40;

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

PouvoirZ::PouvoirZ(SDL_Renderer *pRendererSprites) : Arme()
{
	nomArme = "pouvoir Z";
	degats = 120;
	cadenceTir = 20;
	largeurArme = 36;
	hauteurArme = 18;
	largeurProj = 20;
	hauteurProj = 18;
	vitesseProj = 20;

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	PAN = Mix_LoadWAV("musique/armes/pouvoirZ.wav");

	pSpritesArme = SDL_LoadBMP("images/sprites/personnage/mechant/gens Z/feuilleSprite.bmp");
	Uint32 colorkey = SDL_MapRGB(pSpritesArme->format, 255, 255, 255);
	SDL_SetColorKey(pSpritesArme, SDL_RLEACCEL | SDL_TRUE, colorkey);
	pTextureSpritesArme = SDL_CreateTextureFromSurface(pRendererSprites, pSpritesArme);

	SDL_RenderCopy(pRendererSprites, pTextureSpritesArme, NULL, NULL);

	//--------------------------------------------------------------------------------------------------------------

	for (int i(0); i < 6; i++)
	{
		AnimTirDroite[i].x = 0;
		AnimTirDroite[i].y = 400;
		AnimTirDroite[i].w = largeurArme;
		AnimTirDroite[i].h = hauteurArme;
	}

	for (int i(0); i < 6; i++)
	{
		AnimTirGauche[i].x = 0;
		AnimTirGauche[i].y = 480;
		AnimTirGauche[i].w = largeurArme;
		AnimTirGauche[i].h = hauteurArme;
	}

	SpriteProjectile[0].x = 980;
	SpriteProjectile[0].y = 406;
	SpriteProjectile[0].w = largeurProj;
	SpriteProjectile[0].h = hauteurProj;

	SpriteProjectile[1].x = 1001;
	SpriteProjectile[1].y = 406;
	SpriteProjectile[1].w = largeurProj;
	SpriteProjectile[1].h = hauteurProj;

	DestArme[0] = { 0, 0, largeurArme, hauteurArme };
	DestArme[1] = { 0, 0, largeurArme, hauteurArme };

}

void PouvoirZ::setDestArme(int positionYPerso, int positionXPerso, int frame, int frame2, bool estSurPlat, bool estAccroupi)
{

	if (frame == 0 || estSurPlat == false || estAccroupi == true)
	{
		DestArme[0].x = positionXPerso - 34;
		DestArme[0].y = positionYPerso + 2;

		DestArme[1].x = positionXPerso + 74;
		DestArme[1].y = positionYPerso + 2;

		return;

	}
	DestArme[0].x = positionXPerso - 63;
	DestArme[0].y = positionYPerso + 4;

	DestArme[1].x = positionXPerso + 84;
	DestArme[1].y = positionYPerso + 3;

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

PistoletNazi::PistoletNazi(SDL_Renderer *pRendererSprites) : Arme()
{
	nomArme = "pistolet nazi";
	degats = 150;
	cadenceTir = 20;
	largeurArme = 50;
	hauteurArme = 20;
	largeurProj = 6;
	hauteurProj = 2;
	vitesseProj = 25;
	
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	PAN = Mix_LoadWAV("musique/armes/pistolet nazi.wav");

	pSpritesArme = SDL_LoadBMP("images/sprites/personnage/mechant/nazis/feuilleSprite.bmp");
	Uint32 colorkey = SDL_MapRGB(pSpritesArme->format, 255, 255, 255);
	SDL_SetColorKey(pSpritesArme, SDL_RLEACCEL | SDL_TRUE, colorkey);
	pTextureSpritesArme = SDL_CreateTextureFromSurface(pRendererSprites, pSpritesArme);

	SDL_RenderCopy(pRendererSprites, pTextureSpritesArme, NULL, NULL);

	//--------------------------------------------------------------------------------------------------------------

	for (int i(0); i < 6; i++)
	{
		AnimTirDroite[i].x = largeurArme * i;
		AnimTirDroite[i].y = 410;
		AnimTirDroite[i].w = largeurArme;
		AnimTirDroite[i].h = hauteurArme;
	}

	for (int i(0); i < 6; i++)
	{
		AnimTirGauche[i].x = largeurArme * (5 - i);
		AnimTirGauche[i].y = 410 + hauteurArme;
		AnimTirGauche[i].w = largeurArme;
		AnimTirGauche[i].h = hauteurArme;
	}

	SpriteProjectile[0].x = 995;
	SpriteProjectile[0].y = 404;
	SpriteProjectile[0].w = largeurProj;
	SpriteProjectile[0].h = hauteurProj;

	SpriteProjectile[1].x = 1001;
	SpriteProjectile[1].y = 404;
	SpriteProjectile[1].w = largeurProj;
	SpriteProjectile[1].h = hauteurProj;

	DestArme[0] = { 0, 0, largeurArme, hauteurArme };
	DestArme[1] = { 0, 0, largeurArme, hauteurArme };

}

void PistoletNazi::setDestArme(int positionYPerso, int positionXPerso, int frame, int frame2, bool estSurPlat, bool estAccroupi)
{

	if (frame == 0 || estSurPlat == false || estAccroupi == true)
	{
		DestArme[0].x = positionXPerso - 12;
		DestArme[0].y = positionYPerso + 89;

		DestArme[1].x = positionXPerso + 74;
		DestArme[1].y = positionYPerso + 89;

		return;

	}
	DestArme[0].x = positionXPerso - 20;
	DestArme[0].y = positionYPerso + 89;

	DestArme[1].x = positionXPerso + 81;
	DestArme[1].y = positionYPerso + 89;

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Motherphoqueur::Motherphoqueur(SDL_Renderer *pRendererSprites) : Arme()
{
	nomArme = "motherphoqueur";
	degats = 150;
	cadenceTir = 27;
	largeurArme = 31;
	hauteurArme = 100;
	largeurProj = 31;
	hauteurProj = 100;
	vitesseProj = 20;

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	PAN = Mix_LoadWAV("musique/armes/motherphoqueur.wav");

	pSpritesArme = SDL_LoadBMP("images/sprites/personnage/mechant/neo nazis/feuilleSprite.bmp");
	Uint32 colorkey = SDL_MapRGB(pSpritesArme->format, 255, 255, 255);
	SDL_SetColorKey(pSpritesArme, SDL_RLEACCEL | SDL_TRUE, colorkey);
	pTextureSpritesArme = SDL_CreateTextureFromSurface(pRendererSprites, pSpritesArme);

	SDL_RenderCopy(pRendererSprites, pTextureSpritesArme, NULL, NULL);

	//--------------------------------------------------------------------------------------------------------------

	for (int i(0); i < 6; i++)
	{
		AnimTirDroite[i].x = 0;
		AnimTirDroite[i].y = 400;
		AnimTirDroite[i].w = largeurArme;
		AnimTirDroite[i].h = hauteurArme;
	}

	for (int i(0); i < 6; i++)
	{
		AnimTirGauche[i].x = 0;
		AnimTirGauche[i].y = 500;
		AnimTirGauche[i].w = largeurArme;
		AnimTirGauche[i].h = hauteurArme;
	}

	SpriteProjectile[0].x = 995;
	SpriteProjectile[0].y = 409;
	SpriteProjectile[0].w = largeurProj;
	SpriteProjectile[0].h = hauteurProj;

	SpriteProjectile[1].x = 1026;
	SpriteProjectile[1].y = 409;
	SpriteProjectile[1].w = largeurProj;
	SpriteProjectile[1].h = hauteurProj;

	DestArme[0] = { 0, 0, largeurArme, hauteurArme };
	DestArme[1] = { 0, 0, largeurArme, hauteurArme };

}

void Motherphoqueur::setDestArme(int positionYPerso, int positionXPerso, int frame, int frame2, bool estSurPlat, bool estAccroupi)
{

	if (frame == 0 || estSurPlat == false || estAccroupi == true)
	{
		DestArme[0].x = positionXPerso + 10;
		DestArme[0].y = positionYPerso + 59;

		DestArme[1].x = positionXPerso + 60;
		DestArme[1].y = positionYPerso + 60;

		return;

	}
	
	DestArme[0].x = positionXPerso + 3;
	DestArme[0].y = positionYPerso + 60;

	DestArme[1].x = positionXPerso + 67;
	DestArme[1].y = positionYPerso + 60;

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Croix::Croix(SDL_Renderer *pRendererSprites) : Arme()
{
	nomArme = "croix";
	degats = 225;
	cadenceTir = 6;
	largeurArme = 420;
	hauteurArme = 400;
	largeurProj = 58;
	hauteurProj = 48;
	vitesseProj = 28;

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	PAN = Mix_LoadWAV("musique/armes/croix.wav");

	pSpritesArme = SDL_LoadBMP("images/sprites/personnage/mechant/boss/feuilleSprite.bmp");
	Uint32 colorkey = SDL_MapRGB(pSpritesArme->format, 255, 255, 255);
	SDL_SetColorKey(pSpritesArme, SDL_RLEACCEL | SDL_TRUE, colorkey);
	pTextureSpritesArme = SDL_CreateTextureFromSurface(pRendererSprites, pSpritesArme);

	SDL_RenderCopy(pRendererSprites, pTextureSpritesArme, NULL, NULL);

	//--------------------------------------------------------------------------------------------------------------

	for (int i(0); i < 6; i++)
	{
		AnimTirGauche[i].x = largeurArme * i;
		AnimTirGauche[i].y = hauteurArme;
		AnimTirGauche[i].w = largeurArme;
		AnimTirGauche[i].h = hauteurArme;
	}

	SpriteProjectile[0].x = 2590;
	SpriteProjectile[0].y = 550;
	SpriteProjectile[0].w = largeurProj;
	SpriteProjectile[0].h = hauteurProj;

	DestArme[0] = { 0, 0, largeurArme, hauteurArme };
	DestArme[1] = { 0, 0, largeurArme, hauteurArme };

}

void Croix::setDestArme(int positionYPerso, int positionXPerso, int frame, int frame2, bool estSurPlat, bool estAccroupi)
{

	DestArme[0].x = positionXPerso;
	DestArme[0].y = positionYPerso;

	DestArme[1].x = positionXPerso;
	DestArme[1].y = positionYPerso;

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

RayonDeLaJoieEtDeLallegresse::RayonDeLaJoieEtDeLallegresse(SDL_Renderer *pRendererSprites) : Arme()
{
	nomArme = "rayon de la joie et de l'allegresse";
	degats = 10000;
	cadenceTir = 6;
	largeurArme = 420;
	hauteurArme = 400;
	largeurProj = 550;
	hauteurProj = 35;
	vitesseProj = 50;

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	PAN = Mix_LoadWAV("musique/armes/rayon de la joie et de l'allegresse.wav");
	
	pSpritesArme = SDL_LoadBMP("images/sprites/personnage/mechant/boss/feuilleSprite.bmp");
	Uint32 colorkey = SDL_MapRGB(pSpritesArme->format, 255, 255, 255);
	SDL_SetColorKey(pSpritesArme, SDL_RLEACCEL | SDL_TRUE, colorkey);
	pTextureSpritesArme = SDL_CreateTextureFromSurface(pRendererSprites, pSpritesArme);

	SDL_RenderCopy(pRendererSprites, pTextureSpritesArme, NULL, NULL);

	//--------------------------------------------------------------------------------------------------------------

	for (int i(0); i < 6; i++)
	{
		AnimTirGauche[i].x = largeurArme * i;
		AnimTirGauche[i].y = 0;
		AnimTirGauche[i].w = largeurArme;
		AnimTirGauche[i].h = hauteurArme;
	}

	SpriteProjectile[0].x = 2600;
	SpriteProjectile[0].y = 200;
	SpriteProjectile[0].w = 129;
	SpriteProjectile[0].h = 23;

	DestArme[0] = { 0, 0, largeurArme, hauteurArme };
	DestArme[1] = { 0, 0, largeurArme, hauteurArme };

}

void RayonDeLaJoieEtDeLallegresse::setDestArme(int positionYPerso, int positionXPerso, int frame, int frame2, bool estSurPlat, bool estAccroupi)
{

	DestArme[0].x = positionXPerso;
	DestArme[0].y = positionYPerso;

	DestArme[1].x = positionXPerso;
	DestArme[1].y = positionYPerso;

}










