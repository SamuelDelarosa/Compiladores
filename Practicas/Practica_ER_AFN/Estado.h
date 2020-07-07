#include "stdlib.h"

typedef struct Nodo{
	int id;
	char ts;
	char ti;
	int visitado;
	struct Nodo *s;
	struct Nodo *i;
}* Estado;

Estado vacio();
int esvacio(Estado);
Estado cons(int, char, Estado, char, Estado);
void imprimeTransiciones(Estado);
void reinicia(Estado);
void renumera(Estado, int);

Estado vacio(){
	return NULL;
}

int esvacio(Estado e){
	return e==NULL;
}

int getId(Estado e){
	return e->id;
}
Estado cons(int id, char s, Estado sup, char i, Estado inf){
	Estado temp = (Estado)malloc(sizeof(struct Nodo));
	temp->id = id;
	temp->ts = s;
	temp->ti = i;
	temp->s = sup;
	temp->i = inf;
	temp->visitado = 0;
	return temp;
}

void imprimeTransiciones(Estado e){
	if(!esvacio(e) && e->visitado == 0){
		if(!esvacio(e->s)){
			printf("%d-%c->%d\n", getId(e), e->ts, getId(e->s));

			
		}
		if(!esvacio(e->i)){
			printf("%d-%c->%d\n", getId(e), e->ti, getId(e->i));
		}
		e->visitado = 1;
		imprimeTransiciones(e->s);
		imprimeTransiciones(e->i);
	}
}

void reinicia(Estado e){
	if(!esvacio(e) && e->visitado != 0){
		e->visitado = 0;
		reinicia(e->s);
		reinicia(e->i);
	}
}
void renumera(Estado e, int i){
	if(!esvacio(e) && e->visitado == 0){
		e->id = getId(e) + i;
		e->visitado = 1;
		renumera(e->s, i);
		renumera(e->i, i);
	}
}

