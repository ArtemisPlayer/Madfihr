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

  SDL_SetRenderDrawColor(renderer, t2D->color.r, t2D->color.g, t2D->color.b, 255);
  
  for (int x = minX; x <= maxX; x++){
    for (int y = minY; y <= maxY; y++){
      p.x = (double) x;
      p.y = (double) y;
      
      
      if (IsPointInTri(&p, &v1, &v2, &v3)){
        SDL_RenderDrawPoint(renderer, x, y);
      }
    }
  }
  SDL_RenderPresent(renderer);
}


void renderMonde(SDL_Renderer *renderer, camera* camera, triangle3D monde[], int tailleMonde){
  //il va d'abord falloir trier pour afficher le plus proche en dernier...  

  triangle3D sorted[tailleMonde];

  vect barycentre;
  vect gamma; //vecteur intermédiaire de calcul
  int tempIM; //variable pous stocker l'index min temporairemet
  double distanceMax;

  double index[tailleMonde];
  for (int i = 0; i < tailleMonde; i++){
    //calcul du barycentre du triangle:
    barycentre.x = (monde[i].A.x + monde[i].B.x + monde[i].C.x)/3;
    barycentre.y = (monde[i].A.y + monde[i].B.y + monde[i].C.y)/3;
    barycentre.z = (monde[i].A.z + monde[i].B.z + monde[i].C.z)/3;
    gamma = camera->position;
    multiplicationScalaire(&gamma, -1);
    add(&barycentre, &gamma, &barycentre);//barycentre dans le repere camera
    index[i] = norme(&barycentre);
  }
  printf("index 0 : %f\n", index[0]);

  distanceMax = max(index, tailleMonde);

  for (int i = 0; i < tailleMonde; i++){//tri par insertion
    tempIM = indexMin(index, tailleMonde);
    sorted[i] = monde[tempIM];
    index[tempIM] = distanceMax*2; //pour ne pas le reprendre la fois suivante
  }

  triangle2D temp;

  for (int k = 0; k < tailleMonde; k++){
    
    projetterT3DPersp(&temp, &sorted[tailleMonde - k - 1], camera);//on affiche les plus loin en premier
    dessinerTriangle(renderer, &temp);

  }
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

void clearEcran(SDL_Renderer *renderer){
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}
