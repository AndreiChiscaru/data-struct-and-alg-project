TASK 1:
    Am scris toate functiile in fisierul graf-L.c.

    Funcția printRoutes afiseaza toate drumurile dintre orase. 
    Pentru fiecare oras ( or_cu) din vect orase, parcurge toate drumurile sale
    si pentru fiecare drum afiseaza destinatia nr de tronsoane si lungimile.
    
    Funcția afisare_rute_care_raman afiseaza rutele care raman utilizabile dupa
    numarul dat de ani. Este comparant cu media uzurii tronsoanelor.
    
    Funcția modificaRoutes modifica valorile tronsoanleor dupa fiecare an. Intai verific daca 
    pe ruta este un singur element si compar cu maximele extremitatiolor ce intra sau ies din orasele 
    intre care e drumul. Pt k intre 1 si lungime - 1 compar cu vecinii doar. Pt ultimul element compar cu vecinul
    din stanga impartit la 2 pt ca l am inmultit cu 2 anterior si cu extremitatile destinatiei.
    Modific maximele extremitatilordin stuct la fiecare an.

    Funcția adaug_drum adauga drum de la oras1 la oras2 in vectorul de drumuri din struct.

    Funcția aloc_cel initializeaza si declara o celula( fac si mallocurile aici, la care le dau free in main, la final).

    Functia principala main:
    Descid fisierele de intrare si iesire fac citirea si alocarile cu functiile de mai sus(citirea e in main).
    Am un vector de stringuri alocat dinamic( la care am dat free la final) in care tin minte pe pozitia i si i+1 sursa
    si destinatia drumurilor in ordinea in care le citesc(am nevoie de el ca sa vad in ce ordine sa afisez ca daca se schimba
    putin ordinea drumurilor nu iau punctaj chiar daca tronsoanele au val corecta). Am un for pt numarul de ani in care apelez functia de modificare 
    si mai fac niste printuri(m au ajutat la debug). La final, pt afisare ma iau dupa ordinea din vectorul de stringuri pe care l am creat sa afiseaz 
    valorile modificate in ordinea corecta. Si dupa tot asa afisez si indexul drumurilor care trebuiesc pastrate(apelez afisare_rute_care_raman).
    Dupa dau free la vectorul de stinguri si la orase.