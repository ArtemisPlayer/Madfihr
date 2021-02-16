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
        SDL_RenderDrawPoint(renderer, x, y);
      }
    }
  }
}

void renderMonde(SDL_Renderer *renderer, camera* camera, triangle3D monde[], int tailleMonde){
  
  triangle2D temp;

  for (int k = 0; k < tailleMonde; k++){
    projetterT3D(&temp, &monde[k], camera);
    printf("%f", temp.p1[0]);
    printf(" %f\n", temp.p1[1]);

    dessinerTriangle(renderer, &temp);
  }
  SDL_RenderPresent(renderer);
}

void update()
{
  //SDL_SetRenderDrawColor(renderer, white.r, white.g, white.b, white.a);
}

void wait(){
  int continuer = 1;
  SDL_Event event;
  while (continuer){
    SDL_WaitEvent(&event);
    switch(event.type)
    {
      case SDL_QUIT:
        continuer = 0;
    }
  }
}
