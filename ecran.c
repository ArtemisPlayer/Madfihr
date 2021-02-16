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

void dessinerTriangle(SDL_Surface *ecran, triangle2D* t2D){
  //dessine un triangle 2d
  //va etre galere

  //on suppose que le triangle a deja été porté aux coordonnées de l
  // 'ecran , ex : p[0] = 200; 300
  int maxX;
  int maxY;
  int minX;
  int minY;
  maxX = t2D->p1[0];
  maxY = t2D->p1[1];
  minX = t2D->p1[0];
  minY = t2D->p1[1];

  if (t2D->p2[0] > maxX){
    maxX = t2D->p2[0];
  } else if (t2D->p2[0] < minX){
    minX = t2D->p2[0];
  }

  if (t2D->p2[1] > maxY){
    maxY = t2D->p2[1];
  } else if (t2D->p2[1] < minY){
    minY = t2D->p2[1];
  }

  if (t2D->p3[0] > maxX){
    maxX = t2D->p3[0];
  } else if (t2D->p3[0] < minX){
    minX = t2D->p3[0];
  }

  if (t2D->p3[1] > maxY){
    maxY = t2D->p3[1];
  } else if (t2D->p3[1] < minY){
    minY = t2D->p3[1];
  }

  //on sait que les pixels à examiner seront entre minX - maxX, id Y
  for (int x = minX; x <= maxX; x++){
    for (int y = minY; y <= maxY; y++){
      //
    }
  }


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





