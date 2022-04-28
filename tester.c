#include "AVL.h"
#include "hash.h"
#include "hash_nonresize.h"
#include "pocet.h"
#include "tabulka_net.h"
#include <limits.h>
#include "rbt_net.h"

long long int  main(void){
    FILE *subor;
    UZOL* koren2 = NULL;
    PRVOK **tabulka = NULL;
    PRVOK_NONRESIZE **tabulka2 = NULL;
    PRVOK *hladaj;
    PRVOK_NONRESIZE *hladaj3;
    UZOL *hladaj2;
    struct node *hladaj4;
    clock_t start2,aktual,aktual2,aktual3,aktual5,aktual6,aktual4,aktual7,aktual8,aktual9,aktual10;
    long long int  *ary = (long long int  *)malloc(POCET * sizeof(long long int ));
    srand(time(0));

    NILL = malloc(sizeof(struct node));
	NILL->color = BLACK;
    ROOT = NILL;

    subor = fopen("hodnoty.csv","a");

    long long int  * pole = (long long int   *)malloc(POCET * sizeof(long long int  )); //vytvorenie vzorky prvkov, ktora sa bude vkladat do vsetkych datovych struktur
    for(long long int   i = 0; i < POCET; i++){
        long long int   n = 0; //algoritmus na vytvorenie nahodnych cisel z intervalu
        for (long long int  y = 0; y < 1000; y++){
            n += rand();
        }
        //long long int n = (rand() % (POCET - 1 +1) + 1);
        pole[i] = n;
    }
    

    for(long long int  i=0;i<POCET;i++) //prevzata tabulka
        ary[i]=INT_MIN; 

    printf("Test pre %d prvkov\n",POCET);
    fprintf(subor,"%d ,",POCET);
    start2 = clock(); //zaciatok merania casu


    for(long long int   i = 0; i < POCET; i++){
        koren2 = insert_avl(koren2,pole[i]); //vlozenie vsetkych prvkov do mojho AVL stromu
    }
    aktual = clock(); //zistenie casu
    double done = aktual - start2;
    printf("Cas po vlozeni (AVL strom): %g s\n",done/CLOCKS_PER_SEC);
    fprintf(subor,"%g ,",done/CLOCKS_PER_SEC);

    for (long long int   i = 0; i < POCET; i++){
        hladaj2 = search_avl(koren2, pole[i]); //hladanie prvkov v AVL strome
    }
    aktual3 = clock();
    done = aktual3 - aktual;
    printf("Cas po hladani (AVL strom): %g s\n",(done)/CLOCKS_PER_SEC);
    fprintf(subor,"%g ,",done/CLOCKS_PER_SEC);



    for(long long int   i = 0; i < POCET; i++){
        red_black_insert(pole[i]); //vlozenie vsetkych prvkov do prevzateho RBT
    }
    aktual9 = clock(); //zistenie casu
    done = aktual9 - aktual3;
    printf("Cas po vlozeni (RB strom): %g s\n",done/CLOCKS_PER_SEC);
    fprintf(subor,"%g ,",done/CLOCKS_PER_SEC);
    for(long long int   i = 0; i < POCET; i++){
        hladaj4 = tree_search(pole[i]); //hladanie vsetkych prvkov v prevzatom RBT
    }
    aktual10 = clock(); //zistenie casu
    done = aktual10 - aktual9;
    printf("Cas po hladani (RB strom): %g s\n",done/CLOCKS_PER_SEC);
    fprintf(subor,"%g ,",done/CLOCKS_PER_SEC);


    for(long long int   i = 0; i < POCET; i++){
        tabulka = insert_table(tabulka,pole[i]); //vlozenie vsetkych prvkov do tabulky
    }
    aktual2 = clock(); //zistenie casu
    done = aktual2 - aktual10;
    printf("Cas po vlozeni (tabulka): %g s\n",(done)/CLOCKS_PER_SEC);
    fprintf(subor,"%g ,",done/CLOCKS_PER_SEC);
    for (long long int   i = 0; i < POCET; i++){
        hladaj = search_table(tabulka, pole[i]); //hladanie prvkov v tabulke
    }
    aktual4 = clock();
    done = aktual4 - aktual2;
    printf("Cas po hladani (tabulka): %g s\n",(done)/CLOCKS_PER_SEC);
    fprintf(subor,"%g ,",done/CLOCKS_PER_SEC);



    for(long long int   i = 0; i < POCET; i++){
        tabulka2 = insert_table_nonresize(tabulka2,pole[i]); //vlozenie vsetkych prvkov do tabulky bez resizuingu
    }
    aktual5 = clock();
    done = aktual5 - aktual4;
    printf("Cas po vlozeni (tabulka bez resizing): %g s\n",(done)/CLOCKS_PER_SEC);
    fprintf(subor,"%g ,",done/CLOCKS_PER_SEC);
    for (long long int   i = 0; i < POCET; i++){
        hladaj3 = search_table_nonresize(tabulka2, pole[i]); //hladanie prvkov v tabulke
    }
    aktual6 = clock();
    done = aktual6 - aktual5;
    printf("Cas po hladani (tabulka bez resizing): %g s\n",(done)/CLOCKS_PER_SEC);
    fprintf(subor,"%g ,",done/CLOCKS_PER_SEC);



    for(long long int   i = 0; i < POCET; i++){
        insert_tabulka_net(ary,pole[i]); //vlozenie vsetkych prvkov do tabulky z netu
    }
    aktual7 = clock();
    done = aktual7 - aktual6;
    printf("Cas po vlozeni (tabulka z netu): %g s\n",(done)/CLOCKS_PER_SEC);
    fprintf(subor,"%g ,",done/CLOCKS_PER_SEC);

    for (long long int   i = 0; i < POCET; i++){
        search_tabulka_net(ary, pole[i]); //hladanie prvkov v tabulke
    }
    aktual8 = clock();
    done = aktual8 - aktual7;
    printf("Cas po hladani (tabulka z netu): %g s\n",(done)/CLOCKS_PER_SEC);
    fprintf(subor,"%g \n",done/CLOCKS_PER_SEC);

    fclose(subor);
    return 0;
}
