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
  SDL_Color white = {255, 255, 255, 255};

  ecran = SDL_CreateWindow("Madfihr", 20, 20, 640, 480, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(ecran, -1, SDL_RENDERER_ACCELERATED);

  //Création du monde
  triangle3D T1;

  T1.A.x = 2;
  T1.A.y = 1;
  T1.A.z = 0;

  T1.B.x = 2;
  T1.B.y = 1;
  T1.B.z = 1;

  T1.C.x = 2;
  T1.C.y = 0;
  T1.C.z = 0;

  triangle3D monde[1];
  int tailleMonde = 1;

  //RUN
  renderMonde(renderer, &camera, monde, tailleMonde);
  wait();

  quitEcran();
  return 0;
}
