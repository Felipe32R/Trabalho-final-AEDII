#include <string.h>
#include <conio.h>
#include <iostream>

struct Endereco{
    char rua[50], bairro[50];
    int numero;
};

struct NoFila {
	char nome[50];
	int idade, cpf,gravidade;
	Endereco endereco;
	NoFila *prox;
};

struct Fila {
	NoFila *prim; //ponteiro para a primeira posi��o da fila
	NoFila *ult; //ponteiro para a �ltima posi��o da fila
};

void criarFila (Fila &F) {
	F.prim = F.ult = NULL;
}

int filaVazia (Fila F) {
	return ((F.prim == NULL) && (F.ult == NULL));
}

void imprimirFila(Fila F) {
	system("cls");
	int i = 1;
	if (!filaVazia(F)) {
		NoFila *aux = F.prim;
		while (aux != NULL) {
			
			if (aux->gravidade == 3){
			
			printf ("\n%i � da fila de emerg�ncia:",i);
			i++;
            printf ("\n Nome: %s", aux->nome);
            printf ("\n Idade: %i", aux->idade);
            printf ("\n CPF: %i",aux->cpf);
            printf ("\n Gravidade: %i",aux->gravidade);
            printf ("\n Endere�o");
            printf ("\n Rua: %s",aux->endereco.rua);
            printf ("\n N�mero: %i",aux->endereco.numero);
            printf ("\n Bairro: %s",aux->endereco.bairro);
            printf ("\n --------------------------------------------");
        }
        else{
        	printf ("\n%i � da fila urgente/n�o urgente:",i);
			i++;
            printf ("\n Nome: %s", aux->nome);
            printf ("\n Idade: %i", aux->idade);
            printf ("\n CPF: %i",aux->cpf);
            printf ("\n Gravidade: %i",aux->gravidade);
            printf ("\n Endere�o");
            printf ("\n Rua: %s",aux->endereco.rua);
            printf ("\n N�mero: %i",aux->endereco.numero);
            printf ("\n Bairro: %s",aux->endereco.bairro);
            printf ("\n --------------------------------------------");
        	
		}
			aux = aux->prox;
		}
	}
	else
		printf("Fila vazia!");
	
	printf("\n\n");
	system("pause");
}

void enfileirar(Fila &F, char nome[50], char rua[50], char bairro[50], int idade, int cpf,int gravidade, int numero) {
	NoFila *aux = new (NoFila);
    strcpy(aux->nome, nome);
    aux->idade = idade;
    aux->cpf = cpf;
    aux->gravidade = gravidade;
    strcpy(aux->endereco.rua, rua);
    aux->endereco.numero = numero;
    strcpy(aux->endereco.bairro, bairro);
    aux->prox = NULL;
	if (filaVazia(F)) F.prim = aux;
	else F.ult->prox = aux;
	F.ult = aux;
}

NoFila desenfileirar(Fila &F) {
	NoFila *aux = F.prim;
	NoFila paciente = *F.prim;
	char nome[50];
	strcpy(nome, aux->nome);
	if (F.prim == F.ult) F.ult = NULL;
	F.prim = aux->prox;
	delete(aux);
	return paciente;
}
