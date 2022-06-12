#ifndef ARMES_H_INCLUDED
#define ARMES_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_version.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include "arme.h"

class Bazookat : public Arme
{
public:

	Bazookat(SDL_Renderer *pRendererSprites);

	virtual void setDestArme(int positionYPerso, int positionXPerso, int frame, int frame2, bool estSurPlat, bool estAccroupi);

private:

};

class Pistolait : public Arme
{
public:

	Pistolait(SDL_Renderer *pRendererSprites);

	virtual void setDestArme(int positionYPerso, int positionXPerso, int frame, int frame2, bool estSurPlat, bool estAccroupi);

private:

};

class Magnum : public Arme
{
public:

	Magnum(SDL_Renderer *pRendererSprites);

	virtual void setDestArme(int positionYPerso, int positionXPerso, int frame, int frame2, bool estSurPlat, bool estAccroupi);

private:

};

class FusilAPompe : public Arme
{
public:

	FusilAPompe(SDL_Renderer *pRendererSprites);

	virtual void setDestArme(int positionYPerso, int positionXPerso, int frame, int frame2, bool estSurPlat, bool estAccroupi);

private:

};

class LanceRoquette : public Arme
{
public:

	LanceRoquette(SDL_Renderer *pRendererSprites);

	virtual void setDestArme(int positionYPerso, int positionXPerso, int frame, int frame2, bool estSurPlat, bool estAccroupi);

private:

};

class ChatCrame : public Arme
{
public:

	ChatCrame(SDL_Renderer *pRendererSprites);

	virtual void setDestArme(int positionYPerso, int positionXPerso, int frame, int frame2, bool estSurPlat, bool estAccroupi);

private:

};

class ACaca : public Arme
{
public:

	ACaca(SDL_Renderer *pRendererSprites);

	virtual void setDestArme(int positionYPerso, int positionXPerso, int frame, int frame2, bool estSurPlat, bool estAccroupi);

private:

};

class Gourdin : public Arme
{
public:

	Gourdin(SDL_Renderer *pRendererSprites);

	virtual void setDestArme(int positionYPerso, int positionXPerso, int frame, int frame2, bool estSurPlat, bool estAccroupi);

private:

};

class Hache : public Arme
{
public:

	Hache(SDL_Renderer *pRendererSprites);

	virtual void setDestArme(int positionYPerso, int positionXPerso, int frame, int frame2, bool estSurPlat, bool estAccroupi);

private:

};

class PistoletCool : public Arme
{
	public:

		PistoletCool(SDL_Renderer *pRendererSprites);

		virtual void setDestArme(int positionYPerso, int positionXPerso, int frame, int frame2, bool estSurPlat, bool estAccroupi);

private:

};

class BrasRobot : public Arme
{
public:

	BrasRobot(SDL_Renderer *pRendererSprites);

	virtual void setDestArme(int positionYPerso, int positionXPerso, int frame, int frame2, bool estSurPlat, bool estAccroupi);

private:

};

class YeuxLaser : public Arme
{
public:

	YeuxLaser(SDL_Renderer *pRendererSprites);

	virtual void setDestArme(int positionYPerso, int positionXPerso, int frame, int frame2, bool estSurPlat, bool estAccroupi);

private:

};

class PouvoirZ : public Arme
{
public:

	PouvoirZ(SDL_Renderer *pRendererSprites);

	virtual void setDestArme(int positionYPerso, int positionXPerso, int frame, int frame2, bool estSurPlat, bool estAccroupi);

private:

};

class PistoletNazi : public Arme
{
	public:

		PistoletNazi(SDL_Renderer *pRendererSprites);

		virtual void setDestArme(int positionYPerso, int positionXPerso, int frame, int frame2, bool estSurPlat, bool estAccroupi);

private:

};

class Motherphoqueur : public Arme
{
public:

	Motherphoqueur(SDL_Renderer *pRendererSprites);

	virtual void setDestArme(int positionYPerso, int positionXPerso, int frame, int frame2, bool estSurPlat, bool estAccroupi);

private:

};

class Croix : public Arme
{
public:

	Croix(SDL_Renderer *pRendererSprites);

	virtual void setDestArme(int positionYPerso, int positionXPerso, int frame, int frame2, bool estSurPlat, bool estAccroupi);

private:

};

class RayonDeLaJoieEtDeLallegresse : public Arme
{
public:

	RayonDeLaJoieEtDeLallegresse(SDL_Renderer *pRendererSprites);

	virtual void setDestArme(int positionYPerso, int positionXPerso, int frame, int frame2, bool estSurPlat, bool estAccroupi);

private:

};












#endif