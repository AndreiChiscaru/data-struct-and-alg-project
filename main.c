/* Chiscaru Andrei - 312CB */
#include "graf-L.h"


int main() {
    TLista orase[100] = {NULL};
    // float ultim_tr_care_intra_in_or[100] = {0.0}; // vector in care tin val ultimului tronson care intra in oras(ma ajuta in cazul in
    // care am 0 in primul tronson pentru a compara)
    // float primul_tr_care_intra_in_or[100] = {0.0}; // vector in care tin val tronson care intra in oras(ma ajuta in cazul in
    // care am 0 in ultimul tronson pentru a compara)
    // drum d;
    char **ordine_orase = (char **)malloc(100 * sizeof(char *));
    int numOrase = 0, K, R;
    float L, ult, primul; // ult e ultimul tronson al fiecarui drum
    FILE* file = fopen("tema3.in", "r");
    FILE* out = fopen("tema3.out", "w");
    fscanf(file, "%d", &R); // nr rute
    fscanf(file, "%d", &K); // nr ani
    fscanf(file, "%f", &L); // uzura acceptabila
    int i, j;
    for (i = 0; i < 100; i++) {
        ordine_orase[i] = NULL;
    }
    int nr_ordine_orase = 0;
    for (i = 0; i < R; i++) {
        char oras1[20], oras2[20];
        int nr_tronsoane;
        fscanf(file, "%s %s %d", oras1, oras2, &nr_tronsoane);
        ordine_orase[nr_ordine_orase] = (char *)malloc((strlen(oras1) + 1) * sizeof(char));
        ordine_orase[nr_ordine_orase + 1] = (char *)malloc((strlen(oras2) + 1) * sizeof(char));
        strcpy(ordine_orase[nr_ordine_orase], oras1);
        strcpy(ordine_orase[nr_ordine_orase + 1], oras2);
        nr_ordine_orase += 2;
        drum d;
        d.nr_tr = nr_tronsoane;
        for (j = 0; j < 100; j++) {
            d.tronsoane[j] = -1.0;
        }
        for (j = 0; j < nr_tronsoane; j++) {
            fscanf(file, "%f", &d.tronsoane[j]);
        }
        ult = d.tronsoane[nr_tronsoane - 1];
        primul = d.tronsoane[0];
        TLista oras_1 = NULL, oras_2 = NULL;
        int  poz = -1, poz2 = -1;
        for (j = 0; j < numOrase; j++) {
            if (strcmp(orase[j]->info, oras1) == 0) {
                oras_1 = orase[j];
                poz2 = j;
            }
            if (strcmp(orase[j]->info, oras2) == 0) {
                oras_2 = orase[j];
                poz = j;
            }
        }
        // poz++;
        // poz2++;
        if (oras_1 == NULL) {
            oras_1 = aloc_cel(oras1);
            orase[numOrase] = oras_1;
            orase[numOrase]->valmaxintare = primul;
            numOrase++;
            // daca nu am mai trecut prin oras pun primul tronson in vector
            // primul_tr_care_intra_in_or[numOrase] = primul;
        } else {
            if (orase[poz2]->valmaxintare < primul) {
                orase[poz2]->valmaxintare = primul;
                // primul_tr_care_intra_in_or[poz2] = primul;
            }
        }
        if (oras_2 == NULL) {
            oras_2 = aloc_cel(oras2);
            orase[numOrase] = oras_2;
            orase[numOrase]->valmaxiesire = ult;
            numOrase++;
            // daca nu am mai trecut prin oras pun ultimul tronson in vector
            // ultim_tr_care_intra_in_or[numOrase] = ult;
        } else {
            if (orase[poz]->valmaxiesire < ult) {
                orase[poz]->valmaxiesire = ult;
            }
        }

        adaug_drum(oras_1, oras_2, d);
    }
    fclose(file);
    printRoutes(orase, numOrase);
    // simulate(orase, numOrase, K);

    for (j = 0; j < K; j++) {
        // aici vectorii primul.. si ultim.. sunt corecti
        /*
        printf("Primele:\n");
        for (i = 0; i < numOrase; i++) {
            printf("Val orasului: %d este %.2f\n", i, primul_tr_care_intra_in_or[i]);
        }
        printf("Ultimele:\n");
        for (i = 0; i < numOrase; i++) {
            printf("Val orasului: %d este %.2f\n", i, ultim_tr_care_intra_in_or[i]);
        }
        */
        // modificaRoutes(orase, numOrase, primul_tr_care_intra_in_or, ultim_tr_care_intra_in_or);
        modificaRoutes(orase, numOrase);
        printf("\n");
        // aici trebuie sa ii modific pt noile val ale tronsoanelor
        /*
        for (j = 0; j < numOrase; j++) {
            primul_tr_care_intra_in_or[j] = orase[j]->drumuri->tronsoane[0];
        }
        */
        
        printRoutes(orase, numOrase);
        printf("\n");
        
        /* 
        printf("Primele:\n");
        for (i = 0; i < numOrase; i++) {
            printf("Val orasului: %d este %.2f\n", i, primul_tr_care_intra_in_or[i]);
        }
        printf("Ultimele:\n");
        for (i = 0; i < numOrase; i++) {
            printf("Val orasului: %d este %.2f\n", i, ultim_tr_care_intra_in_or[i]);
        }
        */
    }
    printRoutes(orase, numOrase);
    afisare_rute_care_raman(orase, numOrase, L);
    int k, q;
    // Afisare in fisier a oraselor si tronsoanelor
    for (q = 0; q < nr_ordine_orase; q = q + 2) {
        for (i = 0; i < numOrase; ++i) {
        TLista or_cu = orase[i];
        for (j = 0; j < or_cu->nr_drumuri; ++j) {
            TLista dest = or_cu->urm[j];
            if (strcmp(ordine_orase[q], or_cu->info) == 0 && strcmp(ordine_orase[q + 1], dest->info) == 0) {
                fprintf(out, "%s %s %d ", or_cu->info, dest->info, or_cu->drumuri[j].nr_tr);
                for (k = 0; k < or_cu->drumuri[j].nr_tr; ++k) {
                    fprintf(out, "%.2f ", or_cu->drumuri[j].tronsoane[k]);
                }
                fprintf(out ,"\n");
            }
        }
    }
    }
    // Afisarea indexuri drumuri care raman
    int s = 0, ind = 1, ok = 0;
    for (i = 0; i < numOrase; ++i) {
        TLista or_cu = orase[i];
        if (or_cu->nr_drumuri == 0) { // daca e zego scad din indexul pe care il afisez ca sa
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
                // fprintf(out, "%d ", i + 1 - s);
                fprintf(out, "%d ", ind);
                ok = 1;
            }
            ind++;
            // printf("\n");
        }
    }
    if (ok == 1) {
        fprintf(out, "\n");
    }
    fclose(out);
    
    for (i = 0; i < nr_ordine_orase; ++i) {
        free(ordine_orase[i]);
    }
    free(ordine_orase);
    for (int i = 0; i < numOrase; i++) {
        free(orase[i]->drumuri);
        free(orase[i]);
    }
    
    return 0;
}