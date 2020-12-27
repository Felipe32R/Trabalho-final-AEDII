#include <string.h>
#include <conio.h>
#include <iostream>
using namespace std;

struct NoLDE {
	char nome[50];
	int CRM;
	NoLDE *ant;
	NoLDE *prox;
};


void criarLista (NoLDE *&LDE) {
	LDE = NULL;	
}

int listaVazia (NoLDE *LDE) {	
	return (LDE == NULL);
}

void inserirNaLDE(NoLDE *&LDE, char x[50], int CRM, int inicio) {
	NoLDE *aux = new (NoLDE);
	strcpy (aux->nome, x);
	aux->CRM = CRM;
	
	if (inicio == 1) {	
		aux->ant = NULL;
		aux->prox = LDE;
		
		//caso a lista não seja vazia o campo "ant" do primeiro elemento recebe o novo elemento.
		if (!listaVazia(LDE)) LDE->ant = aux;
		
		//a nova lista inicia pelo elemento inserido.
		LDE = aux;	
	}
	else {	
		NoLDE *aux = new (NoLDE);
		strcpy (aux->nome, x);
		aux->CRM = CRM;
		aux->prox = NULL;
		
		if (listaVazia(LDE)) {
			aux->ant = NULL;
			LDE = aux;
		}
		else {		
			NoLDE *ult = LDE;
			while (ult->prox != NULL)
				ult = ult->prox;
			
			ult->prox = aux;
			aux->ant = ult;
		}
	}
}

void removerdaLDE(NoLDE *&LDE, char x[50]) {
	system("cls");
	
	//O elemento a ser eliminado é o primeiro
	if (strstr (LDE->nome, x)) {
		//Não existem mais itens na lista
		if (LDE->prox == NULL) {
			delete(LDE);
			LDE = NULL;
		}
		//Existindo outros elementos, o segundo passa a ser o primeiro
		else  {
			LDE = LDE->prox;
			delete(LDE->ant);
			LDE->ant = NULL;			
		}		
	}
	else {
		NoLDE *aux = LDE;
		//Percorre a lista para localizar o elemento
		while (aux != NULL && aux->nome != x) {
			aux = aux->prox;
		}
		//Se chegar no fim da lista, não encontrou o item na lista
		if (aux == NULL) {
			printf("%c nao encontrado na lista!\n\n", x);
			system("pause");
			return;			
		}
		
		//Último elemento da lista
		if (aux->prox == NULL) {
			aux->ant->prox = NULL;//atribui "NULL" ao campo "ant" do penultimo elemento.
			delete(aux);
		}
		//Elemento no meio da lista
		else {
			//o campo "prox" do anterior ao elemento recebe o proximo do elemento.
            aux->ant->prox = aux->prox;
            //o campo "ant" do proximo elemento recebe o elemento anterior.
            aux->prox->ant = aux->ant;
            delete(aux);//libera o elemento.
		}
	}
	
	printf("%c removido da lista!\n\n", x);
	system("pause");	
}

void imprimirLDE (NoLDE *LDE) {
	NoLDE *aux = LDE;
	system("cls");
	if (!listaVazia(LDE)) {			
		printf ("\n ---------------");
		while (aux != NULL) {
			printf("\nMédico: %s ", aux->nome);
			printf("\nCRM: %i", aux->CRM);
			aux = aux->prox;
		}
	}
	else {
		printf("Lista vazia!");
	}
	printf("\n\n");	
}

