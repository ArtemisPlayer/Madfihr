#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//PROTOTYPES
void projeter(vect* A, double p[2], camera* camera);

//FONCTIONS
void actualiserUV(camera* camera){
  //on normalise le vecteur direction:
  multiplicationScalaire(&camera->direction, 1/norme(&camera->direction));

  vect haut;
  haut.x = 0;
  haut.y = 1;
  haut.z = 0;

  //on crée un vecteur v qui sera grosso modo vers le haut et completera
  //la base camera->direction
  camera->v = camera->direction;
  multiplicationScalaire(&camera->v, -scalaire(&haut, &camera->direction));
  add(&haut, &camera->v, &camera->v);
  multiplicationScalaire(&camera->v, 1/norme(&camera->v));


  //on termine la base avec u
  pVectoriel(&camera->direction, &camera->v, &camera->u);

}

void projeter(vect* A, double p[], camera* camera){
  //projette tout vecteur sur l'écran
  p[0] = scalaire(A, &camera->u);
  p[1] = scalaire(A, &camera->v);

}
