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

  vect point;
  point.x=1;
  point.y=1;
  point.z=1;

  actualiserUV(&camera);

  //AFFICHAGE
  runEcran();

  return 0;
}
