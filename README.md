Organização Hospitalar Grupo 3

 

 

# Éricles, Felipe e Sara

 

 

 

O programa visa a melhoria do processo de atendimento hospitalar, efetuando a organização das fichas dos pacientes desde a entrada até o atendimento final. Também é utilizado para o cadastro de médicos disponíveis, onde poderá exibir qual médico está de plantão no momento, caso o paciente queira saber quem irá atende- lo, incluindo a possibilidade de realizar a troca de turno entre os médicos cadastrados. Todos os pacientes serão incluídos em um arquivo binário diário, que poderá ser consultado posteriormente selecionando o dia desejado de acordo com o nome do arquivo. Este arquivo exibirá todas as fichas dos pacientes em ordem de cadastro no dia selecionado.

# Funcionamento

 

Assim que o programa for aberto, deve-se digitar o caminho onde será criado o arquivo diário( um arquivo .dat por exemplo). Em seguida o usuário entra em um menu com 10 opções. São elas:

 

 

Opção 1 - *Cadastrar ficha de paciente*

 

Permite o cadastro das informações de pacientes quantas vezes o usuário desejar.

 

# Informações solicitadas:

 

*Nome, Idade, CPF*

 

*Gravidade (1,2 ou 3, em que 3 são casos de emergência, 2 de urgência e 1 casos* *comuns)*

*Rua, Bairro e Número.*



Após o cadastro cada paciente é separado em uma fila. Casos emergentes possuem uma fila própria.

Os casos urgentes e comuns compartilham da mesma fila, sendo assim devidamente ordenados de acordo com o grau de cada paciente, dando prioridade aos casos urgentes. Para essa ordenação foram utilizadas Lista Ordenada e Pilha.

 

 

Opção 2 - *Exibir fila de emergência*

 

Exibe a fila de pacientes de grau 3.

 

Caso não haja pacientes cadastrados será exibido “fila vazia”.

 

 

 

Opção 3 - *Exibir fila de urgência/comum ordenada*

 

Exibe a fila de pacientes de grau 2 e 1 devidamente ordenada nesta ordem.

 

Caso seja inserido um novo paciente em urgência, ele será direcionado à frente dos de grau 1.

Caso não haja pacientes cadastrados será exibido “fila vazia”.

 

 

 

Opção 4 - *Atendimento de paciente em emergência*

 

Retira o primeiro paciente da fila de emergência, encaminhando-o para o atendimento.

Caso não haja mais pacientes na fila, será exibido “fila vazia”.

 

 

 

Opção 5 - *Atendimento de paciente em urgência e não urgência*

 

Retira o primeiro paciente da fila de urgência/comum, encaminhando-o para o atendimento.

Caso não haja mais pacientes na fila, será exibido “fila vazia”.



Opção 6 - *Cadastrar médicos*

 

Permite ao usuário cadastrar um médico.

 

# Informações solicitadas:

 

*Nome e CRM.*

 

Os médicos são inseridos em uma Lista Circular.

 

 

 

Opção 7 - *Mostrar médico de plantão*

 

Exibe o médico que está disponível no momento.

 

 

 

Opção 8 - *Passar plantão para o próximo médico*

 

Realiza uma troca de turno entre os médicos, passando o plantão para o próximo médico cadastrado sucessivamente, percorrendo a Lista Circular.

 

 

Opção 9 - *Exibir relatório do dia selecionado*

 

Solicita ao usuário o nome de um arquivo para exibir todos os pacientes que nele foram cadastrados naquele dia.

Caso o usuário digite um arquivo não existente, será exibido “Arquivo não encontrado.”.

 

 

Opção 10 – *Sair*

 

Encerra o programa e salva os dados de todos os pacientes que foram cadastrados no dia em um arquivo.