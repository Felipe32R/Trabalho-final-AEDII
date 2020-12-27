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
	printf("\t\n\n Digite o caminho onde deseja criar o arquivo diário: \n");			//Solicita ao usuário o caminho do arquivo onde serão salvas as informações dos pacientes
	scanf ("%s", &caminho);
	
	arquivo = fopen(caminho, "a+b");
	
	if (arquivo == NULL) {																				//Verifica se o caminho informado para o arquivo é válido
		printf("Não foi possível abrir o arquivo! Tente novamente: \n\n");
	}
	
	else {
		do{
			system ("cls");
		    printf ("\n\t\t\t MENU DE OPÇÕES \n");
		    printf ("\t (1) - Cadastrar ficha de paciente \n");
		    printf ("\t (2) - Exibir fila de emergência \n");
			printf ("\t (3) - Exibir fila de urgência/não urgência ordenada \n");
			printf ("\t (4) - Atendimento de paciente em emergência \n");
			printf ("\t (5) - Atendimento de paciente em urgência e não urgência \n");
			printf ("\t (6) - Cadastrar médicos \n"); 
			printf ("\t (7) - Mostrar médico de plantão \n");
			printf ("\t (8) - Passar plantão para o próximo médico \n");
			printf ("\t (9) - Exibir relatório do dia selecionado \n");
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
				        printf("\nEndereço:\n");
				        printf("\nRua: ");
				        cin.sync();
				        gets(rua);
				        printf("\nNúmero: ");
				        scanf("%i", &numero);
				        printf("\nBairro: ");
				        cin.sync();
				        gets(bairro);
				        
				       	NoFila paciente;																//Declara uma estrutura utilizada para manipulação de arquivo binário
				       	
					   	strcpy(paciente.nome, nome);													//Atribui valores recebidos a estrutura
						paciente.idade = idade;
					    paciente.cpf = cpf;
					    paciente.gravidade = gravidade;
					    strcpy(paciente.endereco.rua, rua);
					    paciente.endereco.numero = numero;
					    strcpy(paciente.endereco.bairro, bairro);
					    
					    fwrite(&paciente, sizeof(paciente), 1, arquivo);								//Escreve no arquivo binário a estrutura com os dados do paciente
				        
				        if (gravidade == 3){															//Se a gravidade do caso do paciente for 3 (Emergente) será utilizada uma fila exclusiva
				        	enfileirar(filaEmergencia, nome, rua, bairro, idade, cpf, gravidade, numero);
						}
						else{																			//Caso a gravidade seja 1 (Não urgente) ou 2 (Urgente) será utilizada uma única fila, que será ordenada
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
					
					
					while (aux2 != NULL){																//Inverte a ordenação para que pacientes em caso urgente sejam atendidos antes dos não urgente
						empilhar(Ordenacao,aux2->nome,aux2->endereco.rua,aux2->endereco.bairro,aux2->idade,aux2->cpf,aux2->gravidade,aux2->endereco.numero);
						aux2 = aux2->prox;
					}
					
					criarFila(filaComum);
					NoPilha *aux3 = NULL;
					aux3 = Ordenacao;
		
					while (aux3 != NULL){																//Retorna os pacientes da pilha para a fila principal, já ordenados de acordo com a gravidade
						enfileirar(filaComum,aux3->nome,aux3->end.rua,aux3->end.bairro,aux3->idade,aux3->cpf,aux3->gravidade,aux3->end.numero);
						aux3 = aux3->prox;	
					}
					system("cls");
				
				break;
				}
				
		        case 2:
		        {
					printf("------- FILA DE EMERGÊNCIA -------\n");
					imprimirFila(filaEmergencia);
		        break;
				}		
				
				case 3:
		        {
					printf("------- FILA DE URGÊNCIA/NÃO URGÊNCIA -------\n");
					imprimirFila(filaComum);
		        break;
				}
				
				case 4:
				{
					system ("cls");
					if (filaVazia(filaEmergencia)){
						printf ("\nNão há ninguém na fila!\n");
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
						printf ("\nNão há ninguém na fila!\n");
						system("pause");
					}
					else{
						char confirmarUrgente;
						printf("\nConfirmar atendimento de %s? (S/N)\n", filaComum.prim);
						cin >> confirmarUrgente;
						
						if (toupper(confirmarUrgente) == 'S'){
						
						system ("cls");
						printf("------- ATENDIMENTO URGENTE E ATENDIMENTO NÃO URGENTE -------\n");
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
							
				        printf("------- CADASTRO DE MÉDICOS -------");
				        printf("\n\nNome: ");
				        cin.sync();
				        gets(nome);
				        printf("\nCRM: ");
				        scanf("%i", &CRM);
					        
				       	inserirNaLC(medicos, nome , CRM, 0);										//Insere em uma Lista Circular os médicos, para que possam revezar turno
						printf ("\nDeseja cadastrar mais um médico?	(S/N)\n\n");
					    cin >> opc;
					}while(toupper(opc) != 'N');
				}
				break;	
				
				case 7:
				{
					system("cls");
					if (medicos == NULL){
						printf ("\nNão há médicos cadastrados!\n");
					}
					
					else{
					printf ("\n Médico(a) de plantão: %s", medicos->nome);
					printf ("\n CRM: %i\n\n", medicos->CRM);    
					}                                           										//Exibe o médico que está no plantão
					system("pause");
				break;
				}
				
				case 8:
				{	
					system("cls");
					if (medicos == NULL){
						printf ("\nNão há médicos cadastrados!\n");
					}
					else{
						char opTurno;
						
						printf("\nDeseja mesmo trocar o turno? (S/N)\n");
						cin >> opTurno;
						
						if (toupper(opTurno) == 'S'){
							medicos = medicos->prox;                                                        //Passa o plantão para o próximo médico cadastrado
							system ("cls");
							printf ("\nTurno trocado para médico(a) %s\n\n", medicos->nome);
						}
					}
					system("pause");
				break;
				}
				case 9:
					{
						system ("cls");
						printf ("\n Digite o nome do arquivo que deseja visualizar o relatório diário:\n");
						scanf ("%s", &caminho);															//Recebe o caminho do arquivo que será lido
						
						arquivo = fopen(caminho, "rb");													//Abre o arquivo em modo de leitura
						if (fread (&caminho, sizeof(caminho), 1, arquivo) == NULL){
							printf ("\nArquivo não encontrado.\n");
							system("pause");
						}
						else{
						system ("cls");
						printf ("\n------------------- PACIENTES CADASTRADOS NO DIA SELECIONADO -------------------\n\n");
						
						int i = 1;
						NoFila paciente;
						
						while (!feof(arquivo)){															//Percorre o arquivo até o final do mesmo
							if (fread (&paciente, sizeof(paciente), 1, arquivo) != NULL){				//Lê as informações contidas no arquivo
								printf ("\n %iº paciente cadastrado:", i);
								i++;
					            printf ("\n Nome: %s", paciente.nome);
					            printf ("\n Idade: %i", paciente.idade);
					            printf ("\n CPF: %i", paciente.cpf);
					            printf ("\n Gravidade: %i", paciente.gravidade);
					            printf ("\n Endereço");
					            printf ("\n Rua: %s", paciente.endereco.rua);
					            printf ("\n Número: %i", paciente.endereco.numero);
					            printf ("\n Bairro: %s", paciente.endereco.bairro);
					            printf ("\n --------------------------------------------\n");
							}
						}
						system("pause");
						fclose (arquivo);																//Finaliza o arquivo que foi utilizado para o relatório
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
					printf("\nOpção inválida!\n");   													//Exibe a mensagem caso o usuário selecione uma opção que não existe no menu 
					system ("pause");
			}
			
		} while (op != 10);
		
		fclose (arquivo);																				//Finaliza o arquivo diário
		 
		}
	}
