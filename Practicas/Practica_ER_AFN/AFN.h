
#include<string.h>

#include "Estado.h"



#define BUFFER_SIZE 1000




typedef struct datos{
	Estado inicial;
	Estado final;
}* AFN;

Estado inicial(AFN);
Estado final(AFN);
AFN unSimbolo(char);
AFN concatenacionAFN(AFN, AFN);
AFN unionAFN(AFN, AFN);
AFN cerraduraP(AFN);
AFN cerraduraE(AFN);
void imprimeAFN(AFN);

Estado inicial(AFN a){
	return a->inicial;
}

Estado final(AFN a){
	return a->final;
}
AFN unSimbolo(char c){
	Estado f = cons(2,' ',NULL, ' ',NULL);
	Estado i = cons(1,c,f, ' ', NULL);
	AFN temp = (AFN)malloc(sizeof(struct datos));
	temp->inicial = i;
	temp->final = f;
	return temp;
}





void replaceAll(char *str, const char *oldWord, const char *newWord)
{
    char *pos, temp[BUFFER_SIZE];
    int index = 0;
    int owlen;

    owlen = strlen(oldWord);


    /*
     * Repeat till all occurrences are replaced. 
     */
    while ((pos = strstr(str, oldWord)) != NULL)
    {
        // Bakup current line
        strcpy(temp, str);

        // Index of current found word
        index = pos - str;

        // Terminate str after word found index
        str[index] = '\0';

        // Concatenate str with new word 
        strcat(str, newWord);
        
        // Concatenate str with remaining words after 
        // oldword found index.2
        strcat(str, temp + index + owlen);
    }
}


AFN concatenacionAFN(AFN a, AFN b){
	int desplazamiento = getId(a->final) - 1;
	renumera(inicial(b), desplazamiento);
	
	reinicia(a->inicial);
	reinicia(b->inicial);

	a->final->ts = b->inicial->ts;
	a->final->ti = b->final->ti;
	a->final->s = b->inicial->s;
	a->final->i = b->final->i;

	AFN temp = (AFN)malloc(sizeof(struct datos));
	temp->inicial = a->inicial;
	temp->final = b->final;
	return temp;
}

AFN unionAFN(AFN a, AFN b){
	renumera(a->inicial,1);
	renumera(b->inicial, getId(a->final));

	reinicia(a->inicial);
	reinicia(b->inicial);

	Estado inicial = cons(1, 'E', a->inicial, 'E', b->inicial);
	Estado final = cons(getId(b->final) + 1, ' ', NULL, ' ', NULL);
	
	a->final->ts = 'E';
	b->final->ti = 'E';
	a->final->s = final;
	b->final->i = final;

	AFN temp = (AFN)malloc(sizeof(struct datos));
	temp->inicial = inicial;
	temp->final = final;
	return temp;
}

AFN cerraduraP(AFN a){
	renumera(a->inicial, 1);

	reinicia(a->inicial);

	a->final->ts = 'E';
	a->final->ti = 'E';
	a->final->s = a->inicial;
	Estado final = cons(getId(a->final) + 1, ' ', NULL, ' ', NULL);
	a->final->i = final;
	Estado inicial = cons(1, 'E', a->inicial, ' ', NULL);

	AFN temp = (AFN)malloc(sizeof(struct datos));
	temp->inicial = inicial;
	temp->final = final;

	return temp;
}

AFN cerraduraE(AFN a){
	renumera(a->inicial, 1);
	reinicia(a->inicial);

	a->final->ts = 'E';
	a->final->ti = 'E';
	a->final->s = a->inicial;
	Estado final = cons(getId(a->final) + 1, ' ', NULL, ' ', NULL);
	a->final->i = final;
	Estado inicial = cons(1, 'E', a->inicial, 'E', final);

	AFN temp = (AFN)malloc(sizeof(struct datos));
	temp->inicial = inicial;
	temp->final = final;

	return temp;
}
void imprimeAFN(AFN afn){





FILE *f = fopen("temporal.gv", "w");
if (f == NULL)
{
    printf("Error al abrir archivo!\n");
    exit(1);
}

/* print some text */
const char *preambulo = "digraph automata { 					\n\                                                       
   rankdir=LR;                         					\n\
 {     													\n\
     node [fontsize=20 width=0.5 shape=circle]  		\n\
 1 [fixedsize=shape fixedsize=true] 					\n\
 2 [fixedsize=shape fixedsize=true] 					\n\
 3 [fixedsize=shape fixedsize=true] 					\n\
 4 [fixedsize=shape fixedsize=true] 					\n\
 5 [fixedsize=shape fixedsize=true] 					\n\
 6 [fixedsize=shape fixedsize=true  shape=doublecircle] \n\
     inicio [shape=point width=0.1] 					\n\
   } 													\n\
 inicio -> 1 [label=\"inicio\"];                        \n\
";

const char *final = "} ";

fprintf(f, "%s\n", preambulo);


imprimeTransiciones2(f,afn->inicial);


fprintf(f, "%s\n", final);


 fclose(f);


FILE *fPtr = fopen("temporal.gv", "r");
FILE * fTemp = fopen("output.gv", "w"); ;
    
    char buffer[BUFFER_SIZE];
    char oldWord[100]="E", newWord[100]="&#949;";
    


    if (fPtr == NULL || fTemp == NULL)
    {
        printf("Error al abrir archivo!\n");
        exit(EXIT_SUCCESS);
    }


    while ((fgets(buffer, BUFFER_SIZE, fPtr)) != NULL)
    {
        replaceAll(buffer, oldWord, newWord);
        fputs(buffer, fTemp);
    }


    fclose(fPtr);
    fclose(fTemp);
 





char cmdbuf[64];
   memset(cmdbuf, 0, sizeof(cmdbuf));
   if (snprintf(cmdbuf, sizeof(cmdbuf),
               "dot -Tpng output.gv -o grafico.png\n") 
         >= sizeof(cmdbuf)) {
       fprintf(stderr, "comando muy largo \n");
       exit(EXIT_FAILURE);
   };
   fflush(NULL); // always useful before system(3)
   int nok = system(cmdbuf);
   if (nok) {
      fprintf(stderr, "fallo %s compilacion %d\n", cmdbuf, nok);
      exit(EXIT_FAILURE);
   }




	int i;
	printf("Estados: ");
	for(i = 1; i<=getId(afn->final); i++)
		printf("%d,",i);
	printf("\n");
	printf("Estado inicial: %d\n", getId(afn->inicial));
	printf("Estado final: %d\n", getId(afn->final));
	printf("Transiciones: \n");
	imprimeTransiciones(afn->inicial);
	reinicia(afn->inicial);





}



void imprimeTransiciones2(FILE *f,Estado e){
	if(!esvacio(e) && e->visitado == 0){
		if(!esvacio(e->s)){

fprintf(f, "%d -> %d [label=\"%c\"];\n", getId(e), getId(e->s), e->ts);

			
		}
		if(!esvacio(e->i)){


fprintf(f, "%d -> %d [label=\"%c\"];\n", getId(e), getId(e->i), e->ti);

	
			
		}
		e->visitado = 1;
		imprimeTransiciones2(f, e->s);
		imprimeTransiciones2(f, e->i);
	}
}
