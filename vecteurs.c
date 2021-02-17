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
};

typedef struct triangle2D triangle2D;
struct triangle2D
{ //structure triangle 2D pour la camera
  double p1[2];
  double p2[2];
  double p3[2];
};

typedef struct camera camera;
struct camera
{ //structure camera
  vect position;
  vect direction;
  vect u;
  vect v;
  double tailleX;
  double tailleY;
};

typedef struct Point Point;
struct Point{//vecteur 2D
  double x;
  double y;
};

//PROTOTYPES
void add(vect* A, vect* B, vect* C);
void oppose(vect* A);
double norme(vect* vecteur);
void multiplicationScalaire(vect* A, double scalaire);
double scalaire(vect* A, vect* B);
void pVectoriel(vect* A, vect* B, vect* C);
int isAngle2DObtu(double A[2], double B[2], double C[2]);
void printVect(vect *vect);
double Sign(Point* v1, Point* v2, Point* v3);
int IsPointInTri(Point* p, Point* v1, Point* v2, Point* v3);

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

void pVectoriel(vect* A, vect* B, vect* C){
  //C = A ^ B
  C->x = A->y * B->z - A->z * B->y;
  C->y = A->z * B->x - A->x * B->z;
  C->z = A->x * B->y - A->y * B->x;
}

int isAngle2DObtu(double A[2], double B[2], double C[2]){
  //angle ABC sens trigo
  double pScalaire;
  pScalaire = (C[0] - B[0])*(A[0] - B[0]) + (A[1] - B[1])*(C[1] - B[1]);
  if (pScalaire >= 0){
    return 1;//true
  } else {
    return 0;//false
  }

}

void printVect(vect *vect){
  printf("x=%f  ", vect->x);
  printf("y=%f  ", vect->y);
  printf("z=%f\n", vect->z);
}

void rotate(vect* A, vect* axe, double angle){
  //tourne le vecteur 3D A autour de axe
  //axe est de norme 1
  vect C; //vect pour cos
  vect B; //vect pour sin
  vect new;

  C = *axe;
  multiplicationScalaire(&C, -scalaire(A, axe));
  add(A, &C, &C);
  multiplicationScalaire(&C, 1/norme(&C));

  pVectoriel(axe, A, &B);
  multiplicationScalaire(&B, 1/norme(&B));
  //on a une bonne base (lol)
  new = *axe;

  multiplicationScalaire(&new, scalaire(axe, A));
  multiplicationScalaire(&B, sin(angle)*scalaire(A, &C));
  multiplicationScalaire(&C, cos(angle)*scalaire(A, &C));

  add(&new, &C, &new);
  add(&new, &B, &new);

  *A = new;
}

//VECTEURS 2D

double Sign(Point* v1, Point* v2, Point* v3){  
  return (v1->x - v3->x) * (v2->y - v3->y) - (v2->x - v3->x) * (v1->y - v3->y);
}

int IsPointInTri(Point* p, Point* v1, Point* v2, Point* v3){
  int b1, b2, b3;
  b1 = 0;
  b2 = 0;
  b3 = 0;
  if (Sign(p, v1, v2) < 0.0) b1 = 1;    
  if (Sign(p, v2, v3) < 0.0) b2 = 1;    
  if (Sign(p, v3, v1) < 0.0) b3 = 1;
  int sum;
  sum = b1+b2+b3;
  if (sum == 0 || sum == 3){
    return 1;
  } else {
    return 0;
  }
}    