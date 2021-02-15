#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vecteurs.c"
#include "camera.c"


int main(){
  const int COLS = 100;
  const int LINES = 70;

  camera camera;
  camera.position.x = 0;
  camera.position.y = 0;
  camera.position.z = 0;
  camera.direction.x = 1;
  camera.direction.y = 0;
  camera.direction.z = 0;

  double inutile[2];

  vect point;
  point.x=1;
  point.y=1;
  point.z=1;

  actualiserUV(&camera);
  projeterPersp(&point, inutile, &camera);
  printf("%f\n", inutile[0]);
  printf("%f\n", inutile[1]);

  return 0;
}
