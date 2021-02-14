#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vecteurs.c"

void projeter(vect* A, double p[], camera* camera){
  //on va récupérer l'angle selon x et y entre A et camera->direction
  double alpha;
  double normeB;
  double normeCam;
  double pScalaire;

  vect B;
  vect oppCam;
  oppCam = camera->position;
  oppose(&oppCam);

  add(&oppCam, A, &B);

  normeB = norme(&B);
  normeCam = norme(&camera->direction);

  pScalaire = scalaire(&B, &camera->direction);

  alpha = acos(pScalaire/normeB/normeCam);
  // c'est l'angle entre le vecteur camera-point et direction


  printf("%f", alpha);

}

void projeter(vect* A, double p[], camera* camera){
  vect u;
  vect v;
  //autre tentative

}


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
  point.z=0;

  projeter(&point, inutile, &camera);

  return 0;
}
