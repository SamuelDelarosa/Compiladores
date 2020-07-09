
#include<stdio.h>
#include<stdlib.h>
#include "AFN.h"


int main(){

	AFN a = unSimbolo('a');
	AFN b = unSimbolo('b');
    	AFN c = unSimbolo('c');

	AFN afn_resultado;
	
	afn_resultado = concatenacionAFN(a,b);
	afn_resultado = cerraduraE(afn_resultado);
	afn_resultado = unionAFN(afn_resultado,c);
	imprimeAFN(afn_resultado); //top es (ab)*|c

	return 0;
}


