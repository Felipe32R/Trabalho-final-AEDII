#include <string.h>
#include <conio.h>
#include <iostream>

struct End2 {
    char rua[50], bairro[50];
    int numero;
};

struct NoPilha {
	char nome[50];
	int idade, cpf,gravidade;
	End2 end;
    NoPilha *prox;
};

void criarPilha(NoPilha *&topo) { //Cria uma pilha vazia, apontando o topo da pilha para nulo
	topo = NULL;
}

int pilhaVazia(NoPilha *topo) { //Verifica se a pilha está vazia ou não através da variável topo
	return (topo == NULL); //retorna o valor da comparação (0 ou 1)
}

void imprimirPilha(NoPilha *topo) {
	system("cls");
	if (!pilhaVazia(topo)) {
        NoPilha *aux = topo;
		while (aux != NULL) {
			printf ("\n Nome: %s", aux->nome);
            printf ("\n Idade: %i", aux->idade);
            printf ("\n CPF: %i",aux->cpf);
            printf ("\n Gravidade: %i",aux->gravidade);
            printf ("\n Endereço");
            printf ("\n Rua: %s",aux->end.rua);
            printf ("\n Número: %i",aux->end.numero);
            printf ("\n Bairro: %s\n|\n",aux->end.bairro);
			aux = aux->prox;
		}
		printf("\n\n");
	}
	else printf("Pilha vazia!\n\n");
	system("pause");
}

void empilhar(NoPilha *&topo, char nome[50], char rua[50], char bairro[50], int idade, int cpf,int gravidade, int numero) {
    NoPilha *novo = new NoPilha(); //aloca uma Nova area
	strcpy(novo->nome, nome); //atribui nome à  Nova area
	novo->idade = idade;
	novo->cpf = cpf;
	novo->gravidade = gravidade;
	strcpy(novo->end.rua, rua);
	novo->end.numero = numero;
	strcpy(novo->end.bairro, bairro);
	novo->prox = topo; //faz o próximo do novo nó apontar para onde era o topo
	topo = novo; //faz o topo apontar para o novo nó, que agora aponta para o Novo topo
}

 NoPilha desempilhar(NoPilha *&topo) {
    NoPilha *remover = topo;
	NoPilha paciente = *topo;
	topo = topo->prox;
	delete(remover);
	return paciente; //retorna o nome do paciente que está sendo desempilhado
}


