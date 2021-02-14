//Fichier contenant les fonctions sur les vecteurs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> //pour sqrt

//STRUCTURES
typedef struct vect vect;
struct vect
{ //strcuture vecteur 3D
  double x;
  double y;
  double z;
};

typedef struct triangle3D triangle3D;
struct triangle3D
{ //structure triangle 3D base des formes
  vect A;
  vect B;
  vect C;
  char color;
};

typedef struct triangle2D triangle2D;
struct triangle2D
{ //structure triangle 2D pour la camera
  double p1[2];
  double p2[2];
  double p3[2];
  char color;
};

typedef struct camera camera;
struct camera
{ //structure camera
  vect position;
  vect direction;
  double tailleX;
  double tailleY;
};

//PROTOTYPES
void add(vect* A, vect* B, vect* C);
void oppose(vect* A);
double norme(vect* vecteur);
void multiplicationScalaire(vect* A, double scalaire);
double scalaire(vect* A, vect* B);

double scalaire(vect* A, vect* B){
  //produit scalaire de deux vecteurs
  return A->x*B->x + A->y*B->y + A->z*B->z;
}

void multiplicationScalaire(vect* A, double scalaire){
  //multiplication d'un vecteur par un scalaire
  A->x = A->x*scalaire;
  A->y = A->y*scalaire;
  A->z = A->z*scalaire;
}

double norme(vect* vecteur){
  //norme d'un vecteur
  return sqrt(vecteur->x*vecteur->x + vecteur->y*vecteur->y + vecteur->z*vecteur->z);
}

void oppose(vect* A){
  // -A
  A->x = -A->x;
  A->y = -A->y;
  A->z = -A->z;
}


void add(vect* A, vect* B, vect* C){
  //C = A + B
  C->x = A->x + B->x;
  C->y = A->y + B->y;
  C->z = A->z + B->z;
}
