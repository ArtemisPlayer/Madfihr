#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vecteurs.c"

void projeter(vect* A, double p[2], camera* camera);

void projeter(vect* A, double p[], camera* camera){
  vect u;
  vect v;

  //autre tentative: on normalise le vecteur direction:
  multiplicationScalaire(&camera->direction, 1/norme(&camera->direction));

  vect haut;
  haut.x = 0;
  haut.y = 1;
  haut.z = 0;

  //on crée un vecteur v qui sera grosso modo vers le haut et completera
  //la base camera->direction
  v = camera->direction;
  multiplicationScalaire(&v, -scalaire(&haut, &camera->direction));
  add(&haut, &v, &v);
  multiplicationScalaire(&v, 1/norme(&v));


  //on termine la base avec u
  pVectoriel(&camera->direction, &v, &u);

  //on enregistre les modifs
  p[0] = scalaire(A, &u);
  p[1] = scalaire(A, &v);

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
  point.z=1;

  projeter(&point, inutile, &camera);
  printf("%f\n", inutile[0]);
  printf("%f\n", inutile[1]);

  return 0;
}
