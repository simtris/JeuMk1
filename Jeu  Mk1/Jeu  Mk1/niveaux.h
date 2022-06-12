#ifndef NIVEAUX_H_INCLUDED
#define NIVEAUX_H_INCLUDED

#include <SDL2/SDL.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <ctime> 
#include <cstdlib> 
#include "personnage.h"
#include "timer.h"
#include "armes.h"


bool checkCollision(SDL_Rect A, SDL_Rect B);

void niveau1(SDL_Window *pWindow, SDL_Renderer *pRenderer, Perso &perso, std::string tabArmes[], int tailleTabArme, bool &overQuit);
void niveau2(SDL_Window *pWindow, SDL_Renderer *pRenderer, Perso &perso, std::string tabArmes[], int tailleTabArme, bool &overQuit);
void niveau3(SDL_Window *pWindow, SDL_Renderer *pRenderer, Perso &perso, std::string tabArmes[], int tailleTabArme, bool &overQuit);
void niveau4(SDL_Window *pWindow, SDL_Renderer *pRenderer, Perso &perso, std::string tabArmes[], int tailleTabArme, bool &overQuit);
void niveau5(SDL_Window *pWindow, SDL_Renderer *pRenderer, Perso &perso, std::string tabArmes[], int tailleTabArme, bool &overQuit);
void niveau6(SDL_Window *pWindow, SDL_Renderer *pRenderer, Perso &perso, std::string tabArmes[], int tailleTabArme, bool &overQuit);
void niveau7(SDL_Window *pWindow, SDL_Renderer *pRenderer, Perso &perso, std::string tabArmes[], int tailleTabArme, bool &overQuit);
void niveau8(SDL_Window *pWindow, SDL_Renderer *pRenderer, Perso &perso, std::string tabArmes[], int tailleTabArme, bool &overQuit);
void niveau9(SDL_Window *pWindow, SDL_Renderer *pRenderer, Perso &perso, std::string tabArmes[], int tailleTabArme, bool &overQuit);
void combatFinal(SDL_Window *pWindow, SDL_Renderer *pRenderer, Perso &perso, std::string tabArmes[], int tailleTabArme, bool &overQuit);

#endif