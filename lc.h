#include <string.h>
#include <conio.h>
#include <iostream>

using namespace std;

struct NoLC {
	char nome[50];
	int CRM;
	NoLC *prox;
};

void criarLC (NoLC *&LC) {
	LC = NULL;
}

int lcVazia (NoLC *LC) {
	return (LC == NULL);
}

void inserirNaLC (NoLC *&LC, char nome[50],int CRM, int inserirNoInicio) {
	NoLC *novoItem = new (NoLC);
	strcpy(novoItem->nome, nome);
	novoItem->CRM = CRM;
	
	if (lcVazia(LC)) {
		LC = novoItem;		
		novoItem->prox = novoItem;
	}
	else {
		NoLC *aux = LC;
		while(aux->prox != LC) {
			aux = aux->prox;
		}			
		aux->prox = novoItem;
		novoItem->prox = LC;
		
		if (inserirNoInicio) { //Indica que deseja inserir o novo elemento no início da lista (inserirNoInicio = 1)
			LC = novoItem;
		}	
	}
}

void imprimirLC (NoLC *LC) {
	if (lcVazia(LC)) 	
		printf("Lista vazia!");
	else {	
		system("cls");
		
		NoLC *aux = LC;
		
		do {
			printf ("%s %i-> ", aux->nome,aux->CRM);		
			aux = aux->prox;			
		} while (aux != LC);
	}
	printf("\n\n");
	system("pause");	
}
