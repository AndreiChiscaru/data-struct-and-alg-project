/* Chiscaru Andrei - 312CB */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

typedef struct drum
{
    int nr_tr; // numarul tronsoanelor
    float tronsoane[100]; // vector de tronsoane
} drum;

typedef struct Celula{
    char info[20]; // orasul
    float valmaxintare, valmaxiesire;
    int nr_drumuri;
    drum *drumuri; // vector de drumuri
    struct Celula *urm[100]; // vector de orase spre care exista drum
} TCelula, *TLista;

void printRoutes(TLista *orase, int numOrase);
// void modificaRoutes(TLista *orase, int numOrase, float *val_pr, float* val_ult);
void modificaRoutes(TLista *orase, int numOrase);
void adaug_drum(TLista x, TLista y, drum d);
TLista aloc_cel(const char* oras);
void afisare_rute_care_raman(TLista *orase, int numOrase, float L);