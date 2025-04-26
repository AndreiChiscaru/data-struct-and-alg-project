/* Chiscaru Andrei - 312CB */
#include "graf-L.h"


void printRoutes(TLista *orase, int numOrase) {
    int i, j, k;
    for (i = 0; i < numOrase; ++i) {
        TLista or_cu = orase[i];
        for (j = 0; j < or_cu->nr_drumuri; ++j) {
            TLista dest = or_cu->urm[j];
            printf("%s %s %d ", or_cu->info, dest->info, or_cu->drumuri[j].nr_tr);
            for (k = 0; k < or_cu->drumuri[j].nr_tr; ++k) {
                printf("%.2f ", or_cu->drumuri[j].tronsoane[k]);
            }
            printf("\n");
        }
    }
}

void afisare_rute_care_raman(TLista *orase, int numOrase, float L) {
    int i, j, k, s = 0, ind = 1;
    for (i = 0; i < numOrase; ++i) {
        TLista or_cu = orase[i];
        if (or_cu->nr_drumuri == 0) { // daca e zero scad din indexul pe care il afisez ca sa
            // ca sa le am pe cele corecte
            s++;
        }
        for (j = 0; j < or_cu->nr_drumuri; ++j) {
            TLista dest = or_cu->urm[j];
            // printf("%s %s %d ", or_cu->info, dest->info, or_cu->drumuri[j].nr_tr);
            float sum = 0.0;
            for (k = 0; k < or_cu->drumuri[j].nr_tr; ++k) {
                sum += or_cu->drumuri[j].tronsoane[k];
                // printf("%.2f ", or_cu->drumuri[j].tronsoane[k]);
            }
            sum = sum / or_cu->drumuri[j].nr_tr;
            // fac media si compar cu uzura media acceptabila
            if (sum <= L) {
                // printf("%d ", i + 1 - s);
                printf("%d ", ind);
            }
            ind++;
            // printf("\n");
        }
    }
    printf("\n");
}


void modificaRoutes(TLista *orase, int numOrase) {
    int i, j, k; // poz_oras = 0;
    for (i = 0; i < numOrase; ++i) {
        TLista or_cu = orase[i];
        // char ult[20] = or_cu->urm[0]->info;
        
        for (j = 0; j < or_cu->nr_drumuri; ++j) {
            TLista dest = or_cu->urm[j];
            int primu_e_0 = 0;
            // printf("%s %s %d ", or_cu->info, dest->info, or_cu->drumuri[j].nr_tr);
            // Pentru primul tronson fac separat ca sa compar cu maximul ultimelor tronsoane care
            // intra in primul oras
            
            float penult_val_inainte = or_cu->drumuri[j].tronsoane[0] * 2;
            if (or_cu->drumuri[j].tronsoane[0] > 0.0 && or_cu->drumuri[j].tronsoane[0] < 100.0) {
                or_cu->drumuri[j].tronsoane[0] = 2 * or_cu->drumuri[j].tronsoane[0];
            }
            if (or_cu->drumuri[j].tronsoane[0] > 100.0) {
                or_cu->drumuri[j].tronsoane[0] = 100.0;
            } // daca e mai mare de 100 sa il faca 100 (ca ala e maximul)

            if (or_cu->drumuri[j].tronsoane[0] == 0.0) { // compar si aleg maximul
                primu_e_0 = 1;
                // printf("\n%.2f\n", val_ult[i]);
                // printf("\nCompar %.2f cu %.2f\n", val_ult[i + 1] / 2, or_cu->drumuri[j].tronsoane[1] / 2);
                if (or_cu->drumuri[j].nr_tr == 1) {
                    printf("\nCompar: %.2f cu %.2f", or_cu->valmaxiesire, or_cu->urm[j]->valmaxintare);
                    printf("\nCompar: %s cu %s", or_cu->info, or_cu->urm[j]->info);
                    float max = 0.0;
                    if ((or_cu->valmaxiesire / 2) > (or_cu->urm[j]->valmaxintare / 2)) { // in val_pr am maximul primului
                        max = or_cu->valmaxiesire / 2;
                    } else {
                        // printf("\nScriu: %.2f", or_cu->valmaxintare);
                        max = or_cu->urm[j]->valmaxintare / 2;
                    }
                    if (max < (or_cu->valmaxintare / 2)) {
                        max = or_cu->valmaxintare / 2;
                    }
                    if (max < (or_cu->urm[j]->valmaxiesire / 2)) {
                        max = or_cu->urm[j]->valmaxiesire / 2;
                    }
                    or_cu->drumuri[j].tronsoane[0] = max;
                } else {
                    float max = or_cu->valmaxiesire;
                    if (max < or_cu->valmaxintare) {
                        max = or_cu->valmaxintare;
                    }
                    if ((max / 2) > (or_cu->drumuri[j].tronsoane[1] / 2)) { // in val_pr am maximul primului
                        or_cu->drumuri[j].tronsoane[0] = max / 2;
                    } else {
                        or_cu->drumuri[j].tronsoane[0] = or_cu->drumuri[j].tronsoane[1] / 2;
                    }
                }
            }
            // printf("%.2f ", or_cu->drumuri[j].tronsoane[0]);
            for (k = 1; k < (or_cu->drumuri[j].nr_tr - 1); ++k) { // fara cazurile in care tronsonul e in extremitati
                if (or_cu->drumuri[j].tronsoane[k] > 0.0 && or_cu->drumuri[j].tronsoane[k] < 100.0) {
                    or_cu->drumuri[j].tronsoane[k] = 2 * or_cu->drumuri[j].tronsoane[k];
                    penult_val_inainte = or_cu->drumuri[j].tronsoane[k];
                } // dublez dc e mai mare ca 0
                if (or_cu->drumuri[j].tronsoane[k] > 100.0) {
                    or_cu->drumuri[j].tronsoane[k] = 100.0;
                    penult_val_inainte = 100.0;
                } // daca e mai mare ca 100 il face 100
                if (or_cu->drumuri[j].tronsoane[k] == 0.0) { // aleg maximul dintre stanga si dreapta
                    penult_val_inainte = 0.0;
                    if (k == 1 && primu_e_0 == 1) {
                        or_cu->drumuri[j].tronsoane[k] = or_cu->drumuri[j].tronsoane[k + 1] / 2;
                    } else {
                        if (or_cu->drumuri[j].tronsoane[k - 1] / 2 > or_cu->drumuri[j].tronsoane[k + 1]) {
                            or_cu->drumuri[j].tronsoane[k] = or_cu->drumuri[j].tronsoane[k - 1] / 4;
                        } else {
                            or_cu->drumuri[j].tronsoane[k] = or_cu->drumuri[j].tronsoane[k + 1] / 2;
                        }
                    }
                }
                // printf("%.2f ", or_cu->drumuri[j].tronsoane[k]);
            }
            // Aici fac pt k
            if (or_cu->drumuri[j].tronsoane[k] > 0.0 && or_cu->drumuri[j].tronsoane[k] < 100.0) {
                or_cu->drumuri[j].tronsoane[k] = 2 * or_cu->drumuri[j].tronsoane[k];
            } 
            if (or_cu->drumuri[j].tronsoane[k] > 100.0) {
                or_cu->drumuri[j].tronsoane[k] = 100.0;
            } // daca e mai mare ca 100 il fac 100
            if (or_cu->drumuri[j].tronsoane[k] == 0.0) {
                // printf("\nCompar %.2f cu %.2f\n", penult_val_inainte / 2, val_pr[i + 2]);
                float max = or_cu->urm[j]->valmaxintare;
                if (max < or_cu->urm[j]->valmaxiesire) {
                    max = or_cu->urm[j]->valmaxiesire;
                }
                if ((penult_val_inainte / 2) > max) {
                    // impart la 4 pt ca pe cel din stanga l am inmultit deja cu 2 si eu vreau val initiala adc / 2
                    or_cu->drumuri[j].tronsoane[k] = penult_val_inainte / 4;
                } else {
                    or_cu->drumuri[j].tronsoane[k] = max / 2;
                }
            }
            // printf("%.2f ", or_cu->drumuri[j].tronsoane[k]);
            // printf("\n");
        }
    }
    for (i = 0; i < numOrase; ++i) {
        // float maxp = 0, maxf = 0;
        for (j = 0; j < orase[i]->nr_drumuri; j++) {
            if (orase[i]->drumuri[j].tronsoane[0] > orase[i]->valmaxintare) {
                orase[i]->valmaxintare = orase[i]->drumuri[j].tronsoane[0];
            }
            // printf("\n\n%f\n\n", orase[i]->drumuri[j].tronsoane[orase[i]->drumuri[j].nr_tr - 1]);
            if (orase[i]->drumuri[j].tronsoane[orase[i]->drumuri[j].nr_tr - 1] > orase[i]->urm[j]->valmaxiesire) {
                orase[i]->urm[j]->valmaxiesire = orase[i]->drumuri[j].tronsoane[orase[i]->drumuri[j].nr_tr - 1];
                // maxf = orase[i]->drumuri[j].tronsoane[orase[i]->drumuri[j].nr_tr - 1];
            }
        }
        // orase[i]->valmaxintare = maxp;
        // orase[i]. = maxf;
    }
}


void adaug_drum(TLista x, TLista y, drum d) {
    if (x->nr_drumuri < 100) {
        x->drumuri = (drum*)realloc(x->drumuri, (x->nr_drumuri + 1) * sizeof(drum));
        x->drumuri[x->nr_drumuri] = d;
        x->urm[x->nr_drumuri] = y;
        x->nr_drumuri++;
    }
}

TLista aloc_cel(const char* oras) {
    TLista new = (TLista)malloc(sizeof(TCelula));
    strcpy(new->info, oras);
    new->nr_drumuri = 0;
    new->drumuri = NULL;
    new->valmaxiesire = 0.0;
    new->valmaxintare = 0.0;
    for (int i = 0; i < 100; i++) {
        new->urm[i] = NULL;
    }
    return new;
}
