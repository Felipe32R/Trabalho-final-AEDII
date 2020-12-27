#include <conio.h>
#include <iostream>
#include <math.h>
#include <locale.h>
#include "filas.h"
#include "lo.h"
#include "pilhas.h"
#include "lc.h"



using namespace std;

int main (){
	
    setlocale (LC_ALL, "portuguese");
    
    int op, contador,sair;
	char opcao, caminho[40];
	
	Fila filaEmergencia, filaComum;
	NoLO *filaOrdenada;
	
	criarFila(filaEmergencia);
	criarFila(filaComum);
	criarLO(filaOrdenada);
	
	NoLC *medicos;
	criarLC(medicos);
	
	FILE *arquivo;

	
	printf("\t\t------- BEM VINDO -------");
	printf("\t\n\n Digite o caminho onde deseja criar o arquivo di�rio: \n");			//Solicita ao usu�rio o caminho do arquivo onde ser�o salvas as informa��es dos pacientes
	scanf ("%s", &caminho);
	
	arquivo = fopen(caminho, "a+b");
	
	if (arquivo == NULL) {																				//Verifica se o caminho informado para o arquivo � v�lido
		printf("N�o foi poss�vel abrir o arquivo! Tente novamente: \n\n");
	}
	
	else {
		do{
			system ("cls");
		    printf ("\n\t\t\t MENU DE OP��ES \n");
		    printf ("\t (1) - Cadastrar ficha de paciente \n");
		    printf ("\t (2) - Exibir fila de emerg�ncia \n");
			printf ("\t (3) - Exibir fila de urg�ncia/n�o urg�ncia ordenada \n");
			printf ("\t (4) - Atendimento de paciente em emerg�ncia \n");
			printf ("\t (5) - Atendimento de paciente em urg�ncia e n�o urg�ncia \n");
			printf ("\t (6) - Cadastrar m�dicos \n"); 
			printf ("\t (7) - Mostrar m�dico de plant�o \n");
			printf ("\t (8) - Passar plant�o para o pr�ximo m�dico \n");
			printf ("\t (9) - Exibir relat�rio do dia selecionado \n");
			printf ("\t (10) - Sair \n");
		    scanf(" %i",&op);
		    
		    switch (op){
		        case 1: 
		        {	
		        	do{
					
				        system("cls");
	
				        char nome[50], rua[50], bairro[50];
						int idade, cpf, gravidade, numero;
						
				        printf("------- CADASTRO DE PACIENTES -------");
				        printf("\n\nNome: ");
				        cin.sync();																		//Comando usado para limpar o Buffer
				        gets(nome);
				        printf("\nIdade: ");
				        scanf("%i", &idade);
				        printf("\nCPF: ");
				        scanf("%ld", &cpf);
				        printf ("\nGravidade(1,2 ou 3): ");
				        scanf ("%i",&gravidade);
				        printf("\nEndere�o:\n");
				        printf("\nRua: ");
				        cin.sync();
				        gets(rua);
				        printf("\nN�mero: ");
				        scanf("%i", &numero);
				        printf("\nBairro: ");
				        cin.sync();
				        gets(bairro);
				        
				       	NoFila paciente;																//Declara uma estrutura utilizada para manipula��o de arquivo bin�rio
				       	
					   	strcpy(paciente.nome, nome);													//Atribui valores recebidos a estrutura
						paciente.idade = idade;
					    paciente.cpf = cpf;
					    paciente.gravidade = gravidade;
					    strcpy(paciente.endereco.rua, rua);
					    paciente.endereco.numero = numero;
					    strcpy(paciente.endereco.bairro, bairro);
					    
					    fwrite(&paciente, sizeof(paciente), 1, arquivo);								//Escreve no arquivo bin�rio a estrutura com os dados do paciente
				        
				        if (gravidade == 3){															//Se a gravidade do caso do paciente for 3 (Emergente) ser� utilizada uma fila exclusiva
				        	enfileirar(filaEmergencia, nome, rua, bairro, idade, cpf, gravidade, numero);
						}
						else{																			//Caso a gravidade seja 1 (N�o urgente) ou 2 (Urgente) ser� utilizada uma �nica fila, que ser� ordenada
							enfileirar(filaComum, nome, rua, bairro, idade, cpf, gravidade, numero);
						}
				        
					    printf ("\nDeseja cadastrar mais um paciente? (S/N)\n");
					    cin >> opcao;
					    
					} while (toupper(opcao) != 'N');
				   	
		
				   	system("cls");
		
		        	criarLO(filaOrdenada);
		        	NoFila *auxiliar = NULL ;
		        	filaOrdenada = NULL;
		        	auxiliar = filaComum.prim;
		        	
		        	while (auxiliar != NULL){															//Ordena a fila dos pacientes da menor gravidade para a maior
						inserirNaLO(filaOrdenada,auxiliar->nome,auxiliar->endereco.rua,auxiliar->endereco.bairro,auxiliar->idade,auxiliar->cpf,auxiliar->gravidade,auxiliar->endereco.numero);
						auxiliar = auxiliar->prox;
					}
					
					NoPilha *Ordenacao;
					criarPilha(Ordenacao);
					NoLO *aux2 = NULL;
					aux2 = filaOrdenada;
					
					
					while (aux2 != NULL){																//Inverte a ordena��o para que pacientes em caso urgente sejam atendidos antes dos n�o urgente
						empilhar(Ordenacao,aux2->nome,aux2->endereco.rua,aux2->endereco.bairro,aux2->idade,aux2->cpf,aux2->gravidade,aux2->endereco.numero);
						aux2 = aux2->prox;
					}
					
					criarFila(filaComum);
					NoPilha *aux3 = NULL;
					aux3 = Ordenacao;
		
					while (aux3 != NULL){																//Retorna os pacientes da pilha para a fila principal, j� ordenados de acordo com a gravidade
						enfileirar(filaComum,aux3->nome,aux3->end.rua,aux3->end.bairro,aux3->idade,aux3->cpf,aux3->gravidade,aux3->end.numero);
						aux3 = aux3->prox;	
					}
					system("cls");
				
				break;
				}
				
		        case 2:
		        {
					printf("------- FILA DE EMERG�NCIA -------\n");
					imprimirFila(filaEmergencia);
		        break;
				}		
				
				case 3:
		        {
					printf("------- FILA DE URG�NCIA/N�O URG�NCIA -------\n");
					imprimirFila(filaComum);
		        break;
				}
				
				case 4:
				{
					system ("cls");
					if (filaVazia(filaEmergencia)){
						printf ("\nN�o h� ningu�m na fila!\n");
						system("pause");
					}
					else{
						char confirmarEmergente;
						printf("\nConfirmar atendimento de %s? (S/N)\n", filaEmergencia.prim);
						cin>> confirmarEmergente;
						
						if (toupper(confirmarEmergente) == 'S'){
							system ("cls");
							printf("------- ATENDIMENTO EMERGENTE -------\n");
							printf("\nPaciente %s encaminhado(a) para o atendimento.\n\n", filaEmergencia.prim);
							desenfileirar(filaEmergencia);														//Retira da fila o paciente que foi atendido
							}
						system("pause");
					}
				}
				break;
				
				case 5:
				{
					system ("cls");
					if (filaVazia(filaComum)){
						printf ("\nN�o h� ningu�m na fila!\n");
						system("pause");
					}
					else{
						char confirmarUrgente;
						printf("\nConfirmar atendimento de %s? (S/N)\n", filaComum.prim);
						cin >> confirmarUrgente;
						
						if (toupper(confirmarUrgente) == 'S'){
						
						system ("cls");
						printf("------- ATENDIMENTO URGENTE E ATENDIMENTO N�O URGENTE -------\n");
						printf("\nPaciente %s encaminhado(a) para o atendimento.\n\n", filaComum.prim);
						desenfileirar(filaComum);															//Retira da fila o paciente que foi atendido
						system("pause");
						}
					}
				}
				break;
				
				case 6:
				{	
					char opc;
					do{
						system("cls");
				        char nome[50];
						int CRM;
							
				        printf("------- CADASTRO DE M�DICOS -------");
				        printf("\n\nNome: ");
				        cin.sync();
				        gets(nome);
				        printf("\nCRM: ");
				        scanf("%i", &CRM);
					        
				       	inserirNaLC(medicos, nome , CRM, 0);										//Insere em uma Lista Circular os m�dicos, para que possam revezar turno
						printf ("\nDeseja cadastrar mais um m�dico?	(S/N)\n\n");
					    cin >> opc;
					}while(toupper(opc) != 'N');
				}
				break;	
				
				case 7:
				{
					system("cls");
					if (medicos == NULL){
						printf ("\nN�o h� m�dicos cadastrados!\n");
					}
					
					else{
					printf ("\n M�dico(a) de plant�o: %s", medicos->nome);
					printf ("\n CRM: %i\n\n", medicos->CRM);    
					}                                           										//Exibe o m�dico que est� no plant�o
					system("pause");
				break;
				}
				
				case 8:
				{	
					system("cls");
					if (medicos == NULL){
						printf ("\nN�o h� m�dicos cadastrados!\n");
					}
					else{
						char opTurno;
						
						printf("\nDeseja mesmo trocar o turno? (S/N)\n");
						cin >> opTurno;
						
						if (toupper(opTurno) == 'S'){
							medicos = medicos->prox;                                                        //Passa o plant�o para o pr�ximo m�dico cadastrado
							system ("cls");
							printf ("\nTurno trocado para m�dico(a) %s\n\n", medicos->nome);
						}
					}
					system("pause");
				break;
				}
				case 9:
					{
						system ("cls");
						printf ("\n Digite o nome do arquivo que deseja visualizar o relat�rio di�rio:\n");
						scanf ("%s", &caminho);															//Recebe o caminho do arquivo que ser� lido
						
						arquivo = fopen(caminho, "rb");													//Abre o arquivo em modo de leitura
						if (fread (&caminho, sizeof(caminho), 1, arquivo) == NULL){
							printf ("\nArquivo n�o encontrado.\n");
							system("pause");
						}
						else{
						system ("cls");
						printf ("\n------------------- PACIENTES CADASTRADOS NO DIA SELECIONADO -------------------\n\n");
						
						int i = 1;
						NoFila paciente;
						
						while (!feof(arquivo)){															//Percorre o arquivo at� o final do mesmo
							if (fread (&paciente, sizeof(paciente), 1, arquivo) != NULL){				//L� as informa��es contidas no arquivo
								printf ("\n %i� paciente cadastrado:", i);
								i++;
					            printf ("\n Nome: %s", paciente.nome);
					            printf ("\n Idade: %i", paciente.idade);
					            printf ("\n CPF: %i", paciente.cpf);
					            printf ("\n Gravidade: %i", paciente.gravidade);
					            printf ("\n Endere�o");
					            printf ("\n Rua: %s", paciente.endereco.rua);
					            printf ("\n N�mero: %i", paciente.endereco.numero);
					            printf ("\n Bairro: %s", paciente.endereco.bairro);
					            printf ("\n --------------------------------------------\n");
							}
						}
						system("pause");
						fclose (arquivo);																//Finaliza o arquivo que foi utilizado para o relat�rio
						}
					break;
					}
					
				case 10:
				{
					system("cls");
					char opSaida;
					printf("\nDeseja mesmo sair? (S/N)\n");													
					cin >> opSaida;
				
					if (toupper(opSaida) == 'S'){
					fclose (arquivo);
					exit(0);                                                                         	//Finaliza o programa
				}
				break;	
				}
				
				default: 
					printf("\nOp��o inv�lida!\n");   													//Exibe a mensagem caso o usu�rio selecione uma op��o que n�o existe no menu 
					system ("pause");
			}
			
		} while (op != 10);
		
		fclose (arquivo);																				//Finaliza o arquivo di�rio
		 
		}
	}
