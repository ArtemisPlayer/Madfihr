//##############################################################
//#                   M A D F I H R                            #
//#    A 3D engine written in c by ArtemisPlayer. v1.2         #
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
  int display;//Affiche t on le triangle ?
};

typedef struct camera camera;
struct camera
{ //structure camera
  vect position;
  vect direction;
  vect u;
  vect v;
};

typedef struct Point Point;
struct Point{//vecteur 2D
  double x;
  double y;
};

//FONCTIONS

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

void printVect(vect *vect){//Pour debug
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

void printTriangle(triangle3D *triangle){//pour debug
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

//--------------------------------------------CAMERA

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

int projeterPersp(vect* A, double p[], camera* camera){

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
    return -1;
  } else {
    p[1] = -y/(x*tan(fov));
    p[0] = z/(x*tan(fov));
    return 0;
  }

}

void projetterT3DPersp(triangle2D* t2D, triangle3D* t3D, camera* camera){
  //affiche en triangle 2D un triangle 3D vu par camera
  double multiplicateurX = 1000;
  double multiplicateurY = 1000;
  double p[2];

  int checksum = 0;

  checksum += projeterPersp(&t3D->A, p, camera);
  t2D->p1[0] = p[0]*multiplicateurX + 320;
  t2D->p1[1] = p[1]*multiplicateurY + 240;

  checksum += projeterPersp(&t3D->B, p, camera);
  t2D->p2[0] = p[0]*multiplicateurX + 320;
  t2D->p2[1] = p[1]*multiplicateurY + 240;

  checksum += projeterPersp(&t3D->C, p, camera);
  t2D->p3[0] = p[0]*multiplicateurX + 320;
  t2D->p3[1] = p[1]*multiplicateurY + 240;

  t2D->color = t3D->color;

  if (checksum<0){
    t2D->display = 0;
  } else {
    t2D->display = 1;
  }
}


//--------------------------------------------ECRAN

typedef struct Vertice Vertice;
struct Vertice
{ //structure vecteur 2D
  float x;
  float y;
};

void fillBottomFlatTriangle(Vertice v1, Vertice v2, Vertice v3, SDL_Renderer* renderer){
  float invslope1 = (v2.x - v1.x) / (v2.y - v1.y);
  float invslope2 = (v3.x - v1.x) / (v3.y - v1.y);

  float curx1 = v1.x;
  float curx2 = v1.x;

  for (int scanlineY = v1.y; scanlineY <= v2.y && scanlineY <= 480; scanlineY++){
    if (scanlineY > 0){
      SDL_RenderDrawLine(renderer, (int)curx1, scanlineY, (int)curx2, scanlineY);
    }
    curx1 += invslope1;
    curx2 += invslope2;
  }
}

void fillTopFlatTriangle(Vertice v1, Vertice v2, Vertice v3, SDL_Renderer* renderer){
  float invslope1 = (v3.x - v1.x) / (v3.y - v1.y);
  float invslope2 = (v3.x - v2.x) / (v3.y - v2.y);

  float curx1 = v3.x;
  float curx2 = v3.x;

  for (int scanlineY = v3.y; scanlineY > v1.y && scanlineY > 0; scanlineY--){
    if (scanlineY < 480){
      SDL_RenderDrawLine(renderer, (int)curx1, scanlineY, (int)curx2, scanlineY);
    }
    curx1 -= invslope1;
    curx2 -= invslope2;
  }
}

void drawTriangle(SDL_Renderer* renderer, triangle2D t2D){
  //On crée les vertices en triant au passage
  //Le code est fat mais c'est pour plus de vitesse
  if (t2D.display == 0){
    return;
  }
  Vertice v1;
  Vertice v2;
  Vertice v3;

  if (t2D.p1[1] < t2D.p2[1]){
    if (t2D.p1[1] < t2D.p3[1]){
      v1.x = t2D.p1[0];
      v1.y = t2D.p1[1];
      if (t2D.p2[1] < t2D.p3[1]){
        v2.x = t2D.p2[0];
        v2.y = t2D.p2[1];
        v3.x = t2D.p3[0];
        v3.y = t2D.p3[1];
      } else {
        v2.x = t2D.p3[0];
        v2.y = t2D.p3[1];
        v3.x = t2D.p2[0];
        v3.y = t2D.p2[1];
      }
    } else {
      v1.x = t2D.p3[0];
      v1.y = t2D.p3[1];
      v2.x = t2D.p1[0];
      v2.y = t2D.p1[1];
      v3.x = t2D.p2[0];
      v3.y = t2D.p2[1];
    }
      
  } else {
    if (t2D.p2[1] < t2D.p3[1]){
      v1.x = t2D.p2[0];
      v1.y = t2D.p2[1];
      if (t2D.p1[1] < t2D.p3[1]){
        v2.x = t2D.p1[0];
        v2.y = t2D.p1[1];
        v3.x = t2D.p3[0];
        v3.y = t2D.p3[1];
      } else {
        v2.x = t2D.p3[0];
        v2.y = t2D.p3[1];
        v3.x = t2D.p1[0];
        v3.y = t2D.p1[1];
      }
    } else {
      v1.x = t2D.p3[0];
      v1.y = t2D.p3[1];
      v2.x = t2D.p2[0];
      v2.y = t2D.p2[1];
      v3.x = t2D.p1[0];
      v3.y = t2D.p1[1];
    }

  }
  /* here we know that v1.y <= v2.y <= v3.y */
  SDL_SetRenderDrawColor(renderer, t2D.color.r, t2D.color.g, t2D.color.b, 255);
  if (v2.y == v3.y){
    fillBottomFlatTriangle(v1, v2, v3, renderer);
  } else if (v1.y == v2.y){
    fillTopFlatTriangle(v1, v2, v3, renderer);
  } else{
    Vertice v4;
    v4.x = (v1.x + ((v2.y - v1.y) / (v3.y - v1.y)) * (v3.x - v1.x));
    v4.y = v2.y;
    fillBottomFlatTriangle(v1, v2, v4, renderer);
    fillTopFlatTriangle(v2, v4, v3, renderer);
  }
}


void quitEcran(){
  SDL_Quit();
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

    if (scalaire(&camera->direction, &barycentre) < 0){
      index[i] = distanceMax;
    } else{
      index[i] = norme(&barycentre);
    }
  }

  for (int i = 0; i < tailleMonde; i++){//tri par insertion
    tempIM = indexMin(index, tailleMonde);
    sorted[i] = monde[tempIM];
    index[tempIM] = distanceMax; //pour ne pas le reprendre la fois suivante
  }

  triangle2D temp;

  for (int k = 0; k < tailleMonde; k++){
    projetterT3DPersp(&temp, &sorted[tailleMonde - k - 1], camera);//on affiche les plus loin en premier
    drawTriangle(renderer, temp);
  }
  SDL_RenderPresent(renderer);
}


void clearEcran(SDL_Renderer *renderer){
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}


//--------------------------------------------MAIN

void processEvent(SDL_Event event, camera *camera, int *continuer){
  //Gère les évènements clavier
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
            multiplicationScalaire(&delta, 1);
            add(&camera->position, &delta , &camera->position);
            break;
          case SDLK_s:
            delta = camera->direction;
            multiplicationScalaire(&delta, -1);
            add(&camera->position, &delta , &camera->position);
            break;
          case SDLK_q:
            delta = camera->u;
            multiplicationScalaire(&delta, -1);
            add(&camera->position, &delta , &camera->position);
            break;
          case SDLK_d:
            delta = camera->u;
            multiplicationScalaire(&delta, 1);
            add(&camera->position, &delta , &camera->position);
            break;
          case SDLK_a:
            //rotate left
            rotate(&camera->direction, &camera->v, 0.05);
            break;
          case SDLK_e:
            //rotate right
            rotate(&camera->direction, &camera->v, -0.05);
            break;
        }
        actualiserUV(camera);
    }
}

int main(){

  //INITIALISATION --------------------------
  camera camera;
  camera.position.x = -10;
  camera.position.y = 7;
  camera.position.z = 10;
  camera.direction.x = 1;
  camera.direction.y = 0;
  camera.direction.z = 0;
  actualiserUV(&camera);

  SDL_Window *ecran;
  SDL_Renderer *renderer;

  ecran = SDL_CreateWindow("Madfihr", 20, 20, 640, 480, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(ecran, -1, SDL_RENDERER_ACCELERATED);

  //CREATION DU MONDE -----------------------

  FILE* in_file = fopen("WORLD", "r"); 

  char line[100];
  fgets(line, 100, in_file);

  int tailleMonde;//première ligne donne le nombre de triangles
  sscanf(line, "%i", &tailleMonde);

  triangle3D *monde;
  monde = malloc(tailleMonde*sizeof(triangle3D));

  int i = 0; 
  int color = 0;

  SDL_Color green = {0, 255, 0, 255};
  SDL_Color red = {255, 0, 0, 255};
  SDL_Color blue = {0, 0, 255, 255};
  SDL_Color grey = {70, 70, 70, 255};

  while (fgets(line, 100, in_file) != NULL) { 
    if (line[0] == '\'' || line[0] == '\n'){
      continue;
    }
    sscanf(line, "%lf %lf %lf - %lf %lf %lf - %lf %lf %lf - C%i", &monde[i].A.x, &monde[i].A.y, &monde[i].A.z,
        &monde[i].B.x, &monde[i].B.y, &monde[i].B.z,
        &monde[i].C.x, &monde[i].C.y, &monde[i].C.z, &color);
    if (color == 0){ // 0 red 1 green 2 blue 3 grey
      monde[i].color = red;
    } else if (color == 1) {
      monde[i].color = green;
    } else if (color == 2) {
      monde[i].color = blue;
    } else if (color == 3) {
      monde[i].color = grey;
    }
    i++;
  } 


  //RUN -------------------------------------
  struct timeval tv1;
  struct timeval tv2;
  long deltaTime = 0;
  double fps;

  int continuer = 1;
  SDL_Event event;
  int counter = 0;

  while (continuer){

    if (counter == 100){
      gettimeofday(&tv1, NULL);
      deltaTime = tv1.tv_usec - tv2.tv_usec;
      if (deltaTime > 0){
        fps = 100 * 1000000/deltaTime;
        printf("%f\n", fps);
      }
      gettimeofday(&tv2, NULL);
      counter = 0;
    } else {
      counter++;
    }
    

    clearEcran(renderer);
    renderMonde(renderer, &camera, monde, tailleMonde);
    SDL_PollEvent(&event);
    processEvent(event, &camera, &continuer);
  }

  quitEcran();
  return 0;
}
