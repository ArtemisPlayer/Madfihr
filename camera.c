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

  double fov; //demi-angle de vision
  fov = 0.80;

  vect Aprime; //A dans le repere de la camera
  vect minusPos;

  minusPos = camera->position;
  oppose(&minusPos);
  add(A, &minusPos, &Aprime);

  //coordonnées de A prime dans le rep direction v u
  double x;
  double y;
  double z;

  x = scalaire(&Aprime, &camera->direction);
  y = scalaire(&Aprime, &camera->v);
  z = scalaire(&Aprime, &camera->u);
  
  if (x <= (double) 0){
    p[0] = 10;
    p[1] = 10;//hors écran (écran va de -1 à 1 selon y )
  } else {
    p[1] = -y/(x*tan(fov));
    p[0] = z/(x*tan(fov));
  }

}

void projetterT3DOrtho(triangle2D* t2D, triangle3D* t3D, camera* camera){
  //affiche en triangle 2D un triangle 3D vu par camera
  double multiplicateurX = 100;
  double multiplicateurY = -100;
  double p[2];

  projeterOrtho(&t3D->A, p, camera);
  t2D->p1[0] = p[0]*multiplicateurX + 320;
  t2D->p1[1] = p[1]*multiplicateurY + 240;

  projeterOrtho(&t3D->B, p, camera);
  t2D->p2[0] = p[0]*multiplicateurX + 320;
  t2D->p2[1] = p[1]*multiplicateurY + 240;

  projeterOrtho(&t3D->C, p, camera);
  t2D->p3[0] = p[0]*multiplicateurX + 320;
  t2D->p3[1] = p[1]*multiplicateurY + 240;

  t2D->color = t3D->color;
}

void projetterT3DPersp(triangle2D* t2D, triangle3D* t3D, camera* camera){
  //affiche en triangle 2D un triangle 3D vu par camera
  double multiplicateurX = 1000;
  double multiplicateurY = 1000;
  double p[2];

  projeterPersp(&t3D->A, p, camera);
  t2D->p1[0] = p[0]*multiplicateurX + 320;
  t2D->p1[1] = p[1]*multiplicateurY + 240;

  projeterPersp(&t3D->B, p, camera);
  t2D->p2[0] = p[0]*multiplicateurX + 320;
  t2D->p2[1] = p[1]*multiplicateurY + 240;

  projeterPersp(&t3D->C, p, camera);
  t2D->p3[0] = p[0]*multiplicateurX + 320;
  t2D->p3[1] = p[1]*multiplicateurY + 240;

  t2D->color = t3D->color;
}