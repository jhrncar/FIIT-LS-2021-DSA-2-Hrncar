#include<stdio.h>
#include<stdlib.h>


typedef struct prvok{//zakladny dizajn 1 prvku tabulky
    long long int kluc;//data, ktore chceme vlozit do tabulky
    struct prvok *dalsi;//kolizie su riesene chainingom, teda kazdy rpvok je zaroven spajany zoznam
}PRVOK;

long long int velkost = 50; //globalna premenna na momentalnu velkost tabulky
long long int plna = 0; //globalna premenna na momentalne zaplnenie tabulky


PRVOK **insert_table(PRVOK **tabulka,long long int kluc); //vlozenie do tabulky
PRVOK* search_table(PRVOK **tabulka,long long int kluc); //najdenie v tabulke
PRVOK **rozsir(PRVOK **tabulka); //rozsirenie tabulky


PRVOK** insert_table(PRVOK **tabulka,long long int kluc){
    long long int h2 = kluc % velkost; //hashovaci algoritmus, len jednoduche modulo. Pri vkladani cisiel nema velky zmysel pouzivat zlozitejsie funkcie, kolizie by sa nezmensili aj tak
    double pomer = (double)plna / (double)velkost;
    if (pomer > 0.5){ //ak je tabulka zaplnena na viac ako 50%, treba ju rozsirit. Dolezite, aby sa spajane zoznamy udrzovali male
        tabulka = rozsir(tabulka); 
    }

    if (tabulka == NULL){//ak tabulka este nebola vytvorena, vytvorit
        tabulka = (PRVOK **)malloc(velkost * sizeof(PRVOK)); //funguje ako calloc, ale calloc nefunguje na velke cisla
        for (long long int  x = 0; x< velkost; x++){
            tabulka[x]= NULL;
        }
    }

    PRVOK *prvok = (PRVOK *)malloc(sizeof(PRVOK)); //vytvorenie noveho prvku a priradenie hodnot
    prvok->kluc = kluc;
    prvok->dalsi = tabulka[h2]; //prvok sa vlozi vzdy na zaciatok spajaneho zoznamu, preto sa do jeho parametru dalsi vklada 
                                //momentalny obsah spajenho zoznamu v danom mieste v tabulke


    tabulka[h2] = prvok; //vlozenie noveho prvku aj s povodnym spajanym zoznamom spat do tabulky
    plna++; //pripocitanie zaplnenia


    return tabulka;
}

PRVOK* search_table(PRVOK **tabulka,long long int kluc){
    PRVOK *prvok = (tabulka)[kluc % velkost]; //hladanie podla hashovacieho algoritmu
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

PRVOK **rozsir(PRVOK **tabulka){ //ak bolo zavolanie rozsirenie, je nutne vytvorit novu, vacsiu tabulku a kazdy prvok zo starej prehashovat do novej
    long long int velkost2 = velkost * 2;  //velkost bude vzdy 2x stara
    PRVOK **tabulka_new = (PRVOK **)malloc(velkost2 * sizeof(PRVOK)); //funguje ako calloc, ale calloc nezvlada velke cisla
    for (long long int  x = 0; x< velkost2; x++){
        tabulka_new[x]= NULL;
    }

    for (long long int i = 0; i < velkost; i++){ //linearne prejde kazdy prvok starej
        if(tabulka[i] != NULL){ //ak sa na tomto policku nic nenachadza, preskoc ho
            long long int kluc = tabulka[i]->kluc; //zober hodnotu zo starej
            long long int h2 = kluc % velkost2; //prehashuj ju funckiou z novej

            PRVOK *prvok = (PRVOK *)malloc(sizeof(PRVOK)); //vytvor novy prvok a prirad mu hodnoty 
            prvok->kluc = kluc; 
            prvok->dalsi = tabulka_new[h2]; //zarad ho na zaciatok spajaneho zoznamu v danom policku tabulky
            
            tabulka_new[h2] = prvok; //zarad prvok do tabulky
                        
        }
    }
    free(tabulka); //uvolni staru tabulku
    velkost = velkost2; //aktualizuj velkost
    return tabulka_new;
}
