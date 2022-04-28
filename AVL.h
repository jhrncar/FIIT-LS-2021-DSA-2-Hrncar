#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct uzol{  //zakladny dizajn jedneho uzlu v strome
    long long int  vyska; //vyska uzlu, s ktorou budeme pocitat balancovanie
    long long int  hodnota; //hodnota = kluc, data co do stromu vkladame
    struct uzol *vlavo; //lavy podstrom
    struct uzol *vpravo; //pravy podstrom
}UZOL;

UZOL* novy(long long int  cislo); //vytvorenie noveho uzlu
long long int  max(long long int   a, long long int   b); //maximum z 2 cisel
long long int  vyska(UZOL *uzol); //zistenie vysky, ak vrati -1 ak uzol nieje vytvoreny
UZOL *rot_vpravo(UZOL *uzol); //pravy - rotacny algoritmus 
UZOL *rot_vlavo(UZOL *uzol); //lavy - rotacny algoritmus
UZOL* insert_avl(UZOL* uzol, long long int   cislo); //insert do AVL stromu
UZOL *search_avl(UZOL *uzol,long long int   cislo); //search v AVL strome

UZOL* novy(long long int   cislo){
    UZOL *novy = (UZOL*) malloc(sizeof(UZOL));//alokacia pamate pre novy uzol

    novy->vyska = 0; //nastavenie zaciatocnych hodnot
    novy->hodnota = cislo;
    novy->vlavo = NULL;
    novy->vpravo = NULL;
    
    return novy;
}

long long int  max(long long int   a, long long int   b){
    if (a > b){ //jednoduche porovnanie
        return a;
    }
    else {
        return b;
    }

}

long long int  vyska(UZOL *uzol){
	if (uzol == NULL) //jednoduche vratenie hodnoty
		return -1;
    else{
	    return uzol->vyska;
    }
}


UZOL *rot_vpravo(UZOL *uzol){//obrazok v dokumentacii
    UZOL *lavy = uzol->vlavo; //lavy podstrom vybraneho uzlu
    UZOL *lpravy = lavy->vpravo; //pravy podstrom z laveho podstromu vybraneho uzlu

    lavy->vpravo = uzol; //vymena miest
    uzol->vlavo = lpravy;

    uzol->vyska = 1 + max(vyska(uzol->vlavo),vyska(uzol->vpravo)); //aktualizovanie vysok vysky, pre prehladnost su vytvorene funkcie
    lavy->vyska = 1 + max(vyska(lavy->vlavo),vyska(lavy->vpravo));
    return lavy;    
}


UZOL *rot_vlavo(UZOL *uzol){//obrazok v dokumentacii
    UZOL *pravy = uzol->vpravo;//pravy podstrom vybraneho uzlu
    UZOL *plavy = pravy->vlavo;//lavy podstrom z praveho podstromu vybraneho uzlu

    pravy->vlavo = uzol; //vymena miest
    uzol->vpravo = plavy;

    uzol->vyska = 1 + max(vyska(uzol->vlavo),vyska(uzol->vpravo));//aktualizovanie vysok vysky, pre prehladnost su vytvorene funkcie
    pravy->vyska = 1 + max(vyska(pravy->vlavo),vyska(pravy->vpravo));
    return pravy;
}


UZOL* insert_avl(UZOL* uzol, long long int   cislo){
    
    if (uzol == NULL){//nemame vytvoreny este strom?
        return (novy(cislo));
    }
    
    long long int  pred = uzol->hodnota;//v konecom dosledku do bude hodnota na uzle, ktory bude nad uzolm ktory vlozime

    if (pred > cislo){//v AVL strome su mensie hodnoty umiestnene vlavo
        if (uzol->vlavo != NULL){//rekurzivne najde najhlbsie miesto, kam sa da vlozit uzol
            uzol->vlavo = insert_avl(uzol->vlavo,cislo);
        }
        else{
            uzol->vlavo = novy(cislo); //ak najde take miesto, vlozi ho tam
        }
    }

    else if (pred < cislo){//v AVL strome su vacsie hodnoty umiestnene vpravo
        if (uzol->vpravo != NULL){//rekurzivne najde najhlbsie miesto, kam sa da vlozit uzol
            uzol->vpravo = insert_avl(uzol->vpravo,cislo);
        }
        else{
            uzol->vpravo = novy(cislo);//ak najde take miesto, vlozi ho tam

        }
    }

    else {
        return uzol;//ak take miesto nenajde, t. j. tato hodnota uz v strome je, nespravi nic
    }

    uzol->vyska = 1 + max(vyska(uzol->vlavo), vyska(uzol->vpravo)); //aktualizacia vysky

    long long int  vyvazenost = vyska(uzol->vlavo) - vyska(uzol->vpravo);//v AVL strome moze byt tato hodnota len -1,0,1. Ak je to nieco ine, rotuje sa

    if (vyvazenost > 1 && cislo < ((uzol->vlavo)->hodnota)){ //ak je vyvazenost moc velka, moc prvokv je vlavo a treba ich rotovat doprava
        return rot_vpravo(uzol);
    }

    else if (vyvazenost < -1 && cislo > ((uzol->vpravo)->hodnota)){ //ak je vyvazenost moc mala, moc prvkov je vpravo a treba ich rotovat dolava
        return rot_vlavo(uzol);
    }

    else if (vyvazenost > 1 && cislo > ((uzol->vlavo)->hodnota)){ //ak je moc velka, ale cislo bolo vlozene na prave miesto, treba spravit najprv lavu a potom pravu rotaciu
        uzol->vlavo = rot_vlavo(uzol->vlavo);
        return rot_vpravo(uzol);
    }

    else if (vyvazenost < -1 && cislo < ((uzol->vpravo)->hodnota)){ //ak je moc mala, ale cislo bolo vlozene na lave miesto, treba spravit najprv pravu a potom lavu rotaciu
        uzol->vpravo = rot_vpravo(uzol->vpravo);
        return rot_vlavo(uzol);
    }
    else{
        return uzol;//ak netreba rotovat, vrat len strom
    }
    
}

UZOL *search_avl(UZOL *uzol,long long int   cislo){
    UZOL *najdi = NULL;//postupne rekurzivne prechadzanie po strome
    if (cislo > uzol->hodnota){//ak cislo je mensie ako momentalna hodnota, chod do praveho podstromu
        if (uzol->vpravo != NULL){
            najdi = search_avl(uzol->vpravo,cislo);
        }
        else{
            return NULL;
        }
    }

    else if (cislo < uzol->hodnota){//ak cislo je vacsie ako momentalna hodnota, chod do laveho podstromu
        if (uzol->vlavo != NULL){
            najdi = search_avl(uzol->vlavo,cislo);
        }
        else{
            return NULL;
        }
    }

    else {
        najdi = uzol;//ak cislo je rovne, naslo sa a vrati sa 
    }
    return najdi;
}