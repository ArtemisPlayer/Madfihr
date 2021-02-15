#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ecran ecran;
struct ecran
{
  int COLS;
  int LINES;
  char chaine[7000];
};

void initEcran(ecran* ecran);
void setPoint(int col, int ligne, ecran* ecran, char couleur);
void afficher(ecran* ecran);

void initEcran(ecran* ecran){
  ecran->COLS = 100;
  ecran->LINES = 70;
  for (int i = 0; i<7000; i++){
    ecran->chaine[i] = ' ';
  }
}

void setPoint(int col, int ligne, ecran* ecran, char couleur){
  ecran->chaine[ligne*100 + col] = couleur;
}

void afficher(ecran* ecran){
  printf("\e[1;1H\e[2J");//clear screen (linux only)
  for (int i = 0; i < 7000; i++){
    printf("%c", ecran->chaine[i]);
    if ((i+1)%100 == 0){//si en fin de ligne alors
      printf("%c", '\n');
    }
  }
}
