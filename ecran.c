#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initEcran(SDL_Surface* ecran){
    
  SDL_Init(SDL_INIT_VIDEO);

  ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);
  SDL_WM_SetCaption("Madfihr", NULL);
}

void quitEcran(){
  SDL_Quit();
}

void dessinerTriangle(SDL_Surface* ecran, triangle2D* t2D){
  //dessine un triangle 2d
  //va etre galere
}

void runEcran()
{
  int continuer = 1;
  SDL_Surface *ecran;

  initEcran(ecran);

  SDL_Event event;
 
  while (continuer){
    SDL_WaitEvent(&event);
    switch(event.type)
    {
      case SDL_QUIT:
        continuer = 0;
    }
  }
  quitEcran();
}





