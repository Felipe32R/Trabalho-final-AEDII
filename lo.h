#include <string.h>
#include <conio.h>
#include <iostream>
#include <locale.h>



struct End{
    char rua[50], bairro[50];
    int numero;
};

struct NoLO {
	char nome[50];
	int idade, cpf,gravidade;
	End endereco;
	NoLO *prox;
};

void criarLO (NoLO *&LO) {
	LO = NULL;
}

int loVazia(NoLO *LO) {
	return (LO == NULL);
}

void inserirNaLO (NoLO *&LO, char nome[50], char rua[50], char bairro[50], int idade, int cpf,int gravidade, int numero) {
	NoLO *aux = new (NoLO);
    strcpy(aux->nome, nome);
    aux->idade = idade;
    aux->cpf = cpf;
    aux->gravidade = gravidade;
    strcpy(aux->endereco.rua, rua);
    aux->endereco.numero = numero;
    strcpy(aux->endereco.bairro, bairro);
	
	NoLO *vizE = NULL;
	NoLO *vizD = LO;
	
	while ((vizD != NULL) && (aux->gravidade > vizD->gravidade)) {
		vizE = vizD;
		vizD = vizD->prox;
	}
	
	if (vizE == NULL) {
		LO = aux;
	}
	else {
		vizE->prox = aux;
	}
	aux->prox = vizD;	
}

void removerDaLO(NoLO *&LO, char nome[50], char rua[50], char bairro[50], int idade, int cpf,int gravidade, int numero) {
	
	NoLO *vizE = NULL;
	NoLO *vizD = LO;
	
	
	while ((vizD != NULL) && (strcmp (nome, vizD->nome) > 0)) {
		vizE = vizD;
		vizD = vizD->prox;
	}
	
	if (vizD != NULL && vizE == NULL) {
		LO = LO->prox;
		delete(vizD);
		printf("Paciente removido da lista!");
		return;
	}
	
	else if (vizD != NULL) {	
		NoLO *aux = vizD;
		vizD = vizD->prox;
		delete(aux);
	
		if (vizD != NULL) 
			vizE->prox = vizD;
		
		else {
			if (vizE == NULL) 
				LO = vizD;				
			else
				vizE->prox = vizD;
		}
		printf("%s removido!", aux->nome);
		return;
	}
	
	printf("%s nao localizado na lista!", vizD->nome);
}

void imprimirLO (NoLO *LO) {
	system("cls");
	int i = 1;
	if (!loVazia(LO)) {	
		NoLO *aux = new (NoLO);
		aux = LO;		
		while (aux != NULL) {
            printf ("\n%i º da fila de urgencia/comum: \n", i);
            i++;
            printf ("\n Nome: %s", aux->nome);
            printf ("\n Idade: %i", aux->idade);
            printf ("\n CPF: %i",aux->cpf);
            printf ("\nGravidade: %i",aux->gravidade);
            printf ("\n Endereco");
            printf ("\n Rua: %s",aux->endereco.rua);
            printf ("\n Numero: %i",aux->endereco.numero);
            printf ("\n Bairro: %s",aux->endereco.bairro);
            printf ("\n --------------------------------------------");
			aux = aux->prox;
		}
	}
	else
		printf("Lista vazia!");
	printf("\n\n");
	system("pause");
}
