#include<stdio.h>
#include<stdlib.h>
#include "pocet.h"

typedef struct prvok_nonresize{//zakladny dizajn 1 prvku tabulky
    long long int kluc;//data, ktore chceme vlozit do tabulky
    struct prvok_nonresize *dalsi;//kolizie su riesene chainingom, teda kazdy rpvok je zaroven spajany zoznam
}PRVOK_NONRESIZE;

long long int velkost_nonresize = POCET; //globalna premenna na momentalnu velkost tabulky
long long int plna_nonresize = 0; //globalna premenna na momentalne zaplnenie tabulky


PRVOK_NONRESIZE **insert_table_nonresize(PRVOK_NONRESIZE **tabulka,long long int kluc); //vlozenie do tabulky
PRVOK_NONRESIZE* search_table_nonresize(PRVOK_NONRESIZE **tabulka,long long int kluc); //najdenie v tabulke


PRVOK_NONRESIZE** insert_table_nonresize(PRVOK_NONRESIZE **tabulka,long long int kluc){
    long long int h2 = kluc % velkost_nonresize; //hashovaci algoritmus, len jednoduche modulo. Pri vkladani cisiel nema velky zmysel pouzivat zlozitejsie funkcie, kolizie by sa nezmensili aj tak
    if (plna_nonresize == velkost_nonresize){ //ak sa tabulka zaplnila, skonci
        return NULL;
    }

    if (tabulka == NULL){//ak tabulka este nebola vytvorena, vytvorit
        tabulka = (PRVOK_NONRESIZE **)malloc(velkost_nonresize * sizeof(PRVOK_NONRESIZE)); //funguje ako calloc, ale calloc nefunguje na velke cisla
        for (long long int  x = 0; x< velkost_nonresize; x++){
            tabulka[x]= NULL;
        }
    }

    PRVOK_NONRESIZE *prvok = (PRVOK_NONRESIZE *)malloc(sizeof(PRVOK_NONRESIZE)); //vytvorenie noveho prvku a priradenie hodnot
    prvok->kluc = kluc;
    prvok->dalsi = tabulka[h2]; //prvok sa vlozi vzdy na zaciatok spajaneho zoznamu, preto sa do jeho parametru dalsi vklada 
                                //momentalny obsah spajenho zoznamu v danom mieste v tabulke


    tabulka[h2] = prvok; //vlozenie noveho prvku aj s povodnym spajanym zoznamom spat do tabulky
    plna_nonresize++; //pripocitanie zaplnenia


    return tabulka;
}

PRVOK_NONRESIZE* search_table_nonresize(PRVOK_NONRESIZE **tabulka,long long int kluc){
    PRVOK_NONRESIZE *prvok = (tabulka)[kluc % velkost_nonresize]; //hladanie podla hashovacieho algoritmu
    if (prvok != NULL){
        while (prvok != NULL){
            if (prvok->kluc == kluc){ //nasla sa dana hodnota?
                return prvok;
            }
            else{
                prvok = prvok->dalsi; //ak nie, moze byt hlbsie v zozname
            }
        }
    }

return NULL; //ak to prvok nenajde, vrati sa NULL
}
