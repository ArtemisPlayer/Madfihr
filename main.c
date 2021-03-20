//##############################################################
//#                   M A D F I H R                            #
//#    A 3D engine written in c by ArtemisPlayer. v1.1         #
//##############################################################


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <math.h>  

#include <sys/time.h>

//--------------------------------------------VECTEURS

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
  SDL_Color color;
};

typedef struct triangle2D triangle2D;
struct triangle2D
{ //structure triangle 2D pour la camera
  double p1[2];
  double p2[2];
  double p3[2];
  SDL_Color color;
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
int indexMin(double tableau[], int tailleTableau);
double max(double tableau[], int tailleTableau);
void printTriangle(triangle3D *triangle);

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

void printTriangle(triangle3D *triangle){
  printf("------------\n");
  printVect(&triangle->A);
  printVect(&triangle->B);
  printVect(&triangle->C);
}

//AUTRES FONCTIONS MATH

int indexMin(double tableau[], int tailleTableau){
  //tableau a valeurs positives
  double min;
  int minIndex;
  min = (double)10000;
  minIndex = 0;

  for (int j = 0; j<tailleTableau; j++){
    if (tableau[j] < min){
      min = tableau[j];
      minIndex = j;
    }
  }
  return minIndex;
}

double max(double tableau[], int tailleTableau){
  double max;
  max = (double) 0;
  for (int k; k<tailleTableau; k++){
    if (tableau[k] > max){
      max = tableau[k];
    }
  }
  return max;
}
//--------------------------------------------


//--------------------------------------------CAMERA
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
//--------------------------------------------


//--------------------------------------------ECRAN

void quitEcran(){
  SDL_Quit();
}

void dessinerTriangle(SDL_Renderer *renderer, triangle2D* t2D){
  //dessine un triangle 2d
  //on suppose que le triangle a deja été porté aux coordonnées de l
  // 'ecran , ex : p[0] = 200; 300
  int maxX;
  int maxY;
  int minX;
  int minY;

  maxX = t2D->p1[0];
  maxY = t2D->p1[1];
  minX = t2D->p1[0];
  minY = t2D->p1[1];

  if (t2D->p2[0] > maxX){
    maxX = t2D->p2[0];
  } else if (t2D->p2[0] < minX){
    minX = t2D->p2[0];
  }

  if (t2D->p2[1] > maxY){
    maxY = t2D->p2[1];
  } else if (t2D->p2[1] < minY){
    minY = t2D->p2[1];
  }

  if (t2D->p3[0] > maxX){
    maxX = t2D->p3[0];
  } else if (t2D->p3[0] < minX){
    minX = t2D->p3[0];
  }

  if (t2D->p3[1] > maxY){
    maxY = t2D->p3[1];
  } else if (t2D->p3[1] < minY){
    minY = t2D->p3[1];
  }

  //on check pas en dehors de l'écran:
  if (maxX > 640){
    maxX = 640;
  } 
  if (minX < 0){
    minX = 0;
  }
  if (maxY > 480){
    maxY = 480;
  } 
  if (minY < 0){
    minY = 0;
  }

  //on sait que les pixels à examiner seront entre minX - maxX, id Y
  Point p;
  Point v1;
  Point v2;
  Point v3;

  v1.x = t2D->p1[0];
  v1.y = t2D->p1[1];

  v2.x = t2D->p2[0];
  v2.y = t2D->p2[1];

  v3.x = t2D->p3[0];
  v3.y = t2D->p3[1];

  SDL_SetRenderDrawColor(renderer, t2D->color.r, t2D->color.g, t2D->color.b, 255);
  
  for (int x = minX; x <= maxX; x++){
    for (int y = minY; y <= maxY; y++){
      p.x = (double) x;
      p.y = (double) y;
      
      if (IsPointInTri(&p, &v1, &v2, &v3)){
        SDL_RenderDrawPoint(renderer, x, y);
      }
    }
  }
}


void renderMonde(SDL_Renderer *renderer, camera* camera, triangle3D monde[], int tailleMonde){
  //il va d'abord falloir trier pour afficher le plus proche en dernier...  

  triangle3D sorted[tailleMonde];

  vect barycentre;
  vect gamma; //vecteur intermédiaire de calcul
  int tempIM; //variable pous stocker l'index min temporairemet
  double distanceMax;
  distanceMax = (double) 10000;

  double index[tailleMonde];
  for (int i = 0; i < tailleMonde; i++){
    //calcul du barycentre du triangle:
    barycentre.x = (monde[i].A.x + monde[i].B.x + monde[i].C.x)/3;
    barycentre.y = (monde[i].A.y + monde[i].B.y + monde[i].C.y)/3;
    barycentre.z = (monde[i].A.z + monde[i].B.z + monde[i].C.z)/3;
    gamma = camera->position;
    multiplicationScalaire(&gamma, -1);
    add(&barycentre, &gamma, &barycentre);//barycentre dans le repere camera
    index[i] = norme(&barycentre);
  }

  for (int i = 0; i < tailleMonde; i++){//tri par insertion
    tempIM = indexMin(index, tailleMonde);
    sorted[i] = monde[tempIM];
    index[tempIM] = distanceMax; //pour ne pas le reprendre la fois suivante
  }

  triangle2D temp;
  //struct timeval tv1;
  //struct timeval tv2;

  for (int k = 0; k < tailleMonde; k++){

    projetterT3DPersp(&temp, &sorted[tailleMonde - k - 1], camera);//on affiche les plus loin en premier
    dessinerTriangle(renderer, &temp);// LONG quand grand triangle
  }
  SDL_RenderPresent(renderer);
}

void wait(){
  int continuer = 1;
  SDL_Event event;
  while (continuer){
    SDL_WaitEvent(&event);
    switch(event.type)
    {
      case SDL_QUIT:
        continuer = 0;
    }
  }
}

void clearEcran(SDL_Renderer *renderer){
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

//--------------------------------------------


//--------------------------------------------MAIN


void processEvent(SDL_Event event, camera *camera, int *continuer, int *isDemo){
  vect delta; //utile pour les mvts
  switch(event.type)
    {
      case SDL_QUIT:
        *continuer = 0;

      case SDL_KEYDOWN:
        switch (event.key.keysym.sym){
          case SDLK_LSHIFT:
            camera->position.y += 0.5;
            break;
          case SDLK_LCTRL:
            camera->position.y -= 0.5;
            break;
          case SDLK_z:
            delta = camera->direction;
            multiplicationScalaire(&delta, 0.3);
            add(&camera->position, &delta , &camera->position);
            break;
          case SDLK_s:
            delta = camera->direction;
            multiplicationScalaire(&delta, -0.3);
            add(&camera->position, &delta , &camera->position);
            break;
          case SDLK_q:
            delta = camera->u;
            multiplicationScalaire(&delta, -0.3);
            add(&camera->position, &delta , &camera->position);
            break;
          case SDLK_d:
            delta = camera->u;
            multiplicationScalaire(&delta, 0.3);
            add(&camera->position, &delta , &camera->position);
            break;
          case SDLK_a:
            //rotate left
            rotate(&camera->direction, &camera->v, 0.1);
            break;
          case SDLK_e:
            //rotate right
            rotate(&camera->direction, &camera->v, -0.1);
            break;
          case SDLK_SPACE:
            if (*isDemo == 0){
              *isDemo = 1;
              camera->position.x = -5;
              camera->position.y = 0.5;
              camera->position.z = 0;
            } else {
              *isDemo = 0;
            }
            break;
        }
        actualiserUV(camera);
    }
}


int main(){

  //INITIALISATION
  camera camera;
  camera.position.x = -5;
  camera.position.y = 0.5;
  camera.position.z = 0;
  camera.direction.x = 1;
  camera.direction.y = 0;
  camera.direction.z = 0;
  actualiserUV(&camera);

  SDL_Window *ecran;
  SDL_Renderer *renderer;
  SDL_Color green = {0, 255, 0, 255};
  SDL_Color red = {255, 0, 0, 255};
  SDL_Color blue = {0, 0, 255, 255};

  ecran = SDL_CreateWindow("Madfihr", 20, 20, 640, 480, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(ecran, -1, SDL_RENDERER_ACCELERATED);
  //Création du monde
  triangle3D T1;

  T1.A.x = 0;
  T1.A.y = 1;
  T1.A.z = 0;

  T1.B.x = 0;
  T1.B.y = 1;
  T1.B.z = 1;

  T1.C.x = 0;
  T1.C.y = 0;
  T1.C.z = 0;

  T1.color = red;

  triangle3D T2;

  T2.A.x = 0;
  T2.A.y = 1;
  T2.A.z = 0;

  T2.B.x = 1;
  T2.B.y = 1;
  T2.B.z = 0;

  T2.C.x = 0;
  T2.C.y = 0;
  T2.C.z = 0;

  T2.color = green;

  triangle3D T3;

  T3.A.x = 1;
  T3.A.y = 1;
  T3.A.z = 0;

  T3.B.x = 0;
  T3.B.y = 0;
  T3.B.z = 0;

  T3.C.x = 0;
  T3.C.y = 1;
  T3.C.z = 1;

  T3.color = blue;

  triangle3D monde[3];
  monde[0] = T1;
  monde[1] = T2;
  monde[2] = T3;
  int tailleMonde = 3;

  //RUN
  int continuer = 1;
  int isDemo = 0;
  vect alpha; //pour la demo
  SDL_Event event;
  while (continuer){
    clearEcran(renderer);
    renderMonde(renderer, &camera, monde, tailleMonde);
    if (isDemo == 1){
      SDL_PollEvent(&event);
    } else {
      SDL_WaitEvent(&event);
    }
    processEvent(event, &camera, &continuer, &isDemo);

    if (isDemo == 1){
      alpha = camera.u;
      multiplicationScalaire(&alpha, -0.1);
      add(&camera.position, &alpha , &camera.position);
      rotate(&camera.direction, &camera.v, -0.0199973);
      SDL_Delay(5);
      actualiserUV(&camera);
    }
  }

  quitEcran();
  return 0;
}
