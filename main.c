#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

#include "vecteurs.c"
#include "camera.c"
#include "ecran.c"


int main(){

  //INITIALISATION
  camera camera;
  camera.position.x = 0;
  camera.position.y = 0;
  camera.position.z = 0;
  camera.direction.x = 1;
  camera.direction.y = 0;
  camera.direction.z = 0;
  actualiserUV(&camera);

  SDL_Window *ecran;
  SDL_Renderer *renderer;
  SDL_Color green = {0, 0, 255, 255};
  SDL_Color red = {255, 0, 0, 255};

  ecran = SDL_CreateWindow("Madfihr", 20, 20, 640, 480, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(ecran, -1, SDL_RENDERER_ACCELERATED);
  //Création du monde
  triangle3D T1;

  T1.A.x = 5;
  T1.A.y = 1;
  T1.A.z = 0;

  T1.B.x = 5;
  T1.B.y = 1;
  T1.B.z = 1;

  T1.C.x = 5;
  T1.C.y = 0;
  T1.C.z = 0;

  T1.color = red;

  triangle3D T2;

  T2.A.x = 5;
  T2.A.y = 1;
  T2.A.z = 0;

  T2.B.x = 6;
  T2.B.y = 1;
  T2.B.z = 0;

  T2.C.x = 5;
  T2.C.y = 0;
  T2.C.z = 0;

  T2.color = green;

  triangle3D monde[2];
  monde[0] = T1;
  monde[1] = T2;
  int tailleMonde = 2;

  //RUN
  int continuer = 1;
  vect delta; //utile pour les mvts
  SDL_Event event;
  while (continuer){
    clearEcran(renderer);
    renderMonde(renderer, &camera, monde, tailleMonde);

    SDL_WaitEvent(&event);
    switch(event.type)
    {
      case SDL_QUIT:
        continuer = 0;

      case SDL_KEYDOWN:
        switch (event.key.keysym.sym){
          case SDLK_LSHIFT:
            camera.position.y += 0.5;
            break;
          case SDLK_LCTRL:
            camera.position.y -= 0.5;
            break;
          case SDLK_z:
            delta = camera.direction;
            multiplicationScalaire(&delta, 0.3);
            add(&camera.position, &delta , &camera.position);
            break;
          case SDLK_s:
            delta = camera.direction;
            multiplicationScalaire(&delta, -0.3);
            add(&camera.position, &delta , &camera.position);
            break;
          case SDLK_q:
            delta = camera.u;
            multiplicationScalaire(&delta, -0.3);
            add(&camera.position, &delta , &camera.position);
            break;
          case SDLK_d:
            delta = camera.u;
            multiplicationScalaire(&delta, 0.3);
            add(&camera.position, &delta , &camera.position);
            break;
          case SDLK_a:
            //rotate left
            rotate(&camera.direction, &camera.v, 0.1);
            break;
          case SDLK_e:
            //rotate right
            rotate(&camera.direction, &camera.v, -0.1);
            break;
        }
        actualiserUV(&camera);
    }
  }

  quitEcran();
  return 0;
}
