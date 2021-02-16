#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//PROTOTYPES
void projeter(vect* A, double p[2], camera* camera);
void actualiserUV(camera* camera);
void projeterPersp(vect* A, double p[], camera* camera);
void afficherTriangle2D(triangle2D* t2D, int COLS, int LINES, double MAXX, double MAXY);

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

void projeterOrtho(vect* A, double p[], camera* camera){
  //projette tout vecteur sur l'écran de façon orthographique

  vect Aprime; //A dans le repere de la camera
  vect minusPos;

  minusPos = camera->position;
  oppose(&minusPos);
  add(A, &minusPos, &Aprime);

  p[0] = scalaire(&Aprime, &camera->u);
  p[1] = scalaire(&Aprime, &camera->v);
}

void projeterPersp(vect* A, double p[], camera* camera){
  //calcul de teta et phi

  vect Aprime; //A dans le repere de la camera
  vect minusPos;

  minusPos = camera->position;
  oppose(&minusPos);
  add(A, &minusPos, &Aprime);

  //coordonnées de A prime dans le rep direction v u
  double x;
  double y;
  double z;
  double module;

  module = norme(&Aprime);
  x = scalaire(&Aprime, &camera->direction);
  y = scalaire(&Aprime, &camera->v);
  z = scalaire(&Aprime, &camera->u);

  //theta:
  p[0] = acos(z/module);
  //phi:
  if (x == (double) 0){
    p[1] = 1.57;
  } else {
    printf("x = %f  ", x);
    printf("atan de %f ", y/x);
    printf("= %f\n", atan(y/x));
    p[1] = atan(y/x);
  }
}

void projetterT3D(triangle2D* t2D, triangle3D* t3D, camera* camera){
  //affiche en triangle 2D un triangle 3D vu par camera
  double multiplicateurX = 20;
  double multiplicateurY = 20;
  double p[2];

  projeterPersp(&t3D->A, p, camera);
  printf("%f ", p[0]);
  printf("%f\n", p[1]);
  t2D->p1[0] = p[0]*multiplicateurX;
  t2D->p1[1] = p[1]*multiplicateurY;

  projeterPersp(&t3D->B, p, camera);
  t2D->p2[0] = p[0]*multiplicateurX;
  t2D->p2[1] = p[1]*multiplicateurY;

  projeterPersp(&t3D->C, p, camera);
  t2D->p3[0] = p[0]*multiplicateurX;
  t2D->p3[1] = p[1]*multiplicateurY;

}