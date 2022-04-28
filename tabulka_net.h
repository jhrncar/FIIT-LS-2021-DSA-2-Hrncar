#include<stdio.h>
#include<limits.h>
#include "pocet.h"
#include<stdlib.h>

long long int   size = POCET;

void insert_tabulka_net(long long int  ary[],long long int  element){
	long long int   pos,n=0;
 
 
	pos = element%size;
 
	while(ary[pos]!= INT_MIN) {  
		if(ary[pos]== INT_MAX)
            break;
		pos = (pos+1)%size;
		n++;
		if(n==size)
		break;      
	}
 
	if(n==size);
        //printf("Hash table was full of elements\nNo Place to insert this element\n\n");
	else
        ary[pos] = element;    //Inserting element
}
 
 
void search_tabulka_net(long long int   ary[],long long int   element){
	long long int   pos,n=0;
 	
	pos = element%size;
 
	while(n++ != size){
		if(ary[pos]==element){
			//printf("Element found at index %d\n",pos);
			break;
		}
		else
            if(ary[pos]==INT_MAX ||ary[pos]!=INT_MIN)
                pos = (pos+1) %size;
	}
	if(--n==size); //printf("Element not found in hash table\n");
}
 

 
