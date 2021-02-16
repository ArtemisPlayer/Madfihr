#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void quitEcran(){
  SDL_Quit();
}

void dessinerTriangle(SDL_Renderer *renderer, triangle2D* t2D){
  //dessine un triangle 2d
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
  Point p;
  Point v1;
  Point v2;
  Point v3;

  v1.x = t2D->p1[0];
  v1.y = t2D->p1[1];

  v2.x = t2D->p2[0];
  v2.y = t2D->p2[1];

  v3.x = t2D->p3[0];
  v3.y = t2D->p3[1];

  for (int x = minX; x <= maxX; x++){
    for (int y = minY; y <= maxY; y++){
      p.x = (double) x;
      p.y = (double) y;
      if (IsPointInTri(&p, &v1, &v2, &v3)){
        printf("x = %f ", p.x);
        printf("y = %f\n", p.y);
        SDL_RenderDrawPoint(renderer, x, y);
      }
    }
  }
  SDL_RenderPresent(renderer);
}

void runEcran()
{
  int continuer = 1;
  SDL_Window *ecran;
  SDL_Renderer *renderer;
  SDL_Color white = {255, 255, 255, 255};
  SDL_Event event;

  ecran = SDL_CreateWindow("Madfihr", 20, 20, 640, 480, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(ecran, -1, SDL_RENDERER_ACCELERATED);
  
  SDL_SetRenderDrawColor(renderer, white.r, white.g, white.b, white.a);
 
 
//----------------
  triangle2D demo;

  demo.p1[0] = 20;
  demo.p1[1] = 20;

  demo.p2[0] = 20;
  demo.p2[1] = 70;

  demo.p3[0] = 70;
  demo.p3[1] = 20;

  dessinerTriangle(renderer, &demo);

//----------------

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

