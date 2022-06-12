
#include <SDL2/SDL.h>
#include <SDL2/SDL_version.h>
#include <string>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include "arme.h"

#define largeurFenetre 1300
#define hauteurFenetre 700

Arme::Arme() : peutTirer(true), estRamassee(false)
{

	// 0 pour gauche, 1 pour droite

	SautArme[0].x = 1100;
	SautArme[0].y = 400;
	SautArme[0].w = 100;
	SautArme[0].h = 200;

	SautArme[1].x = 1200;
	SautArme[1].y = 400;
	SautArme[1].w = 100;
	SautArme[1].h = 200;

	Nom = { 0, 500, 200, 60 };
	DestNom = { (largeurFenetre - 1000) / 2, 70, 1000, 300 };

	for (int i(0); i < 3; i++)
	{
		AccroupiD[i].x = 200 + (100 * i);
		AccroupiD[i].y = 500;
		AccroupiD[i].w = 100;
		AccroupiD[i].h = 200;
	}

	for (int i(0); i < 3; i++)
	{
		AccroupiG[i].x = 600 + (100 * (2 - i));
		AccroupiG[i].y = 500;
		AccroupiG[i].w = 100;
		AccroupiG[i].h = 200;
	}

}

bool Arme::checkCollision(SDL_Rect A, SDL_Rect B)
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

void Arme::remplirTabProj(SDL_Rect positionPerso, char direction, std::string nomArme, bool herosAccroupi)
{
	if (direction == 'd')
	{
		if (nomArme == "pistolait")
			positionPerso.x += 110;
		else if (nomArme == "lance-roquette")
			positionPerso.x += 100;
		else if (nomArme == "fusil a pompe")
			positionPerso.x += 100;
		else if (nomArme == "a-caca-rantesept")
			positionPerso.x += 121;
		else if (nomArme == "chat-crame" && herosAccroupi == false)
			positionPerso.x += 100;
		else if (nomArme == "chat-crame" && herosAccroupi == true)
			positionPerso.x += 110;
		else if (nomArme == "bras robot")
			positionPerso.x += 70;
		else if (nomArme == "magnum")
			positionPerso.x += 100;
		else if (nomArme == "hache")
			positionPerso.x += 100;
		else if (nomArme == "pistolet cool")
			positionPerso.x += 110;
		else if (nomArme == "gourdin")
			positionPerso.x += 100;
		else if (nomArme == "bazookat")
			positionPerso.x += 100;
		else if (nomArme == "yeux laser")
			positionPerso.x += 60;
		else if (nomArme == "pouvoir Z")
			positionPerso.x += 95;
		else if (nomArme == "pistolet nazi")
			positionPerso.x += 70;
		else if (nomArme == "motherphoqueur")
			positionPerso.x += 80;



		positionPerso.h = hauteurProj;
		positionPerso.w = largeurProj;

	
	}
	else if (direction == 'g')
	{
		if (nomArme == "pistolait")
			positionPerso.x -= 40;
		else if (nomArme == "lance-roquette")
			positionPerso.x -= 40;
		else if (nomArme == "bras robot")
			positionPerso.x -= 1;
		else if (nomArme == "magnum")
			positionPerso.x -= 25;
		else if (nomArme == "a-caca-rantesept")
			positionPerso.x -= 55;
		else if (nomArme == "chat-crame" && herosAccroupi == false)
			positionPerso.x -= 80;
		else if (nomArme == "chat-crame" && herosAccroupi == true)
			positionPerso.x -= 95;
		else if (nomArme == "hache")
			positionPerso.x -= 40;
		else if (nomArme == "pistolet cool")
			positionPerso.x -= 10;
		else if (nomArme == "fusil a pompe")
			positionPerso.x -= 65;
		else if (nomArme == "gourdin")
			positionPerso.x -= 40;
		else if (nomArme == "bazookat")
			positionPerso.x -= 40;
		else if (nomArme == "yeux laser")
			positionPerso.x -= 1;
		else if (nomArme == "pouvoir Z")
			positionPerso.x -= 16;
		else if (nomArme == "pistolet nazi")
			positionPerso.x -= 10;
		else if (nomArme == "motherphoqueur")
			positionPerso.x -= 20;
		else if (nomArme == "croix")
			positionPerso.x -= 1;
		else if (nomArme == "rayon de la joie et de l'allegresse")
			positionPerso.x -= 500;

		positionPerso.h = hauteurProj;
		positionPerso.w = largeurProj;
	}
	else
		return;

	if (nomArme == "lance-roquette")
		positionPerso.y += 59;
	else if (nomArme == "bazookat")
		positionPerso.y += 55;
	else if (nomArme == "pistolait")
		positionPerso.y += 50;
	else if (nomArme == "magnum")
		positionPerso.y += 70;
	else if (nomArme == "a-caca-rantesept")
		positionPerso.y += 84;
	else if (nomArme == "chat-crame" && herosAccroupi == false)
		positionPerso.y += 80;
	else if (nomArme == "chat-crame" && herosAccroupi == true)
		positionPerso.y += 10;
	else if (nomArme == "fusil a pompe")
		positionPerso.y += 72;
	else if (nomArme == "hache")
		positionPerso.y += 60;
	else if (nomArme == "gourdin")
		positionPerso.y += 80;
	else if (nomArme == "pistolet cool")
		positionPerso.y += 84;
	else if (nomArme == "bras robot")
		positionPerso.y += 102;
	else if (nomArme == "yeux laser")
		positionPerso.y += 42;
	else if (nomArme == "pouvoir Z")
		positionPerso.y += 78;
	else if (nomArme == "pistolet nazi")
		positionPerso.y += 94;
	else if (nomArme == "motherphoqueur")
		positionPerso.y += 60;
	else if (nomArme == "croix")
		positionPerso.y += 180;
	else if (nomArme == "rayon de la joie et de l'allegresse")
		positionPerso.y += 150;
	
	else
		return;

	DestProjectile.push_back(positionPerso);
}

void Arme::deplacerProj(int i, char sens)
{
	if (sens == 'd')
		DestProjectile[i].x += vitesseProj;
	else if (sens == 'g')
		DestProjectile[i].x -= vitesseProj;
	else
		return;

}











