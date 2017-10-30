/*
Autora: Camille de L. Jesus

Componente Curricular: EXA854 - MI Algoritmos

Data: 11/12/2014

Declaro que este código foi elaborado por mim de forma individual e não contém nenhum
trecho de código de outro colega ou de outro autor, tais como provindos de livros e
apostilas, e páginas ou documentos eletrônicos da Internet. Qualquer trecho de código
de outra autoria que não a minha está destacado com uma citação para o autor e a fonte
do código, e estou ciente que estes trechos não serão considerados para fins de avaliação.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 50

// Código do Sistema de Gerenciamento de Processos (JuriSoft) //

typedef struct dados {   //Estrutura para armazenar os dados processuais
						int numero;
						char foro[TAM], advogado[TAM], cliente[TAM];
						struct dados *anterior;
   						struct dados *proximo;
} Dados;

//Protótipo das funções (elas serão explicadas individualmente em seu escopo):
void inicia (Dados *);
int menu (void);
void opcao (Dados *, int op);
void insere (Dados *);
Dados *aloca ();
int vazia (Dados *);
int busca (Dados *);
void edita (Dados *);
void retira (Dados **);
void exibicao_especial (Dados *);

void exibe (Dados *);
void printa_arquivo (Dados *);


int main (void)   //Função principal
{
	system("color 0F");	
	int escolha;	
	Dados *processo = (Dados *) malloc (sizeof (Dados));   //Alocação dinâmica da primeira célula da lista	
	
	if (!processo) {   //Caso dê erro de alocação:
		printf ("\n\nErro ao alocar!\n");
		exit (1);   //Finaliza o programa
	} else {   //Caso a alocação seja feita com sucesso:
		inicia (processo);   //Chama a função das linhas 74-77
	
		do {
			system ("cls");
			escolha = menu ();   //Chama a função das linhas 80-89
			opcao (processo, escolha);   //Chama a função das linhas 92-124
		} while (escolha);
	free (processo);   //Desaloca o ponteiro
	
	return 0;
	}	
}


void inicia (Dados *processo)   //Faz a primeira posição da lista apontar pra nulo:
{
	processo = NULL;
}


int menu (void)   //Função que exibe o menu de opções do sistema e lê a opção escolhida:
{
	int escolha;	
	printf ("\n\t\t%c%c Sistema de Gerenciamento de Processos (JuriSoft) %c%c\n\n", 254, 254, 254, 254);
    printf ("\nDigite:\n\n [1] - Cadastro\n [2] - Consulta Espec%cfica\n [3] - Edi%c%co\n [4] - Remo%c%co\n [5] - Exibi%c%co Especial\n [6] - Sair\n\n  ", 161, 135, 198, 135, 198, 135, 198);
    scanf ("%i", &escolha);	
	return escolha;   //Retorna a opção digitada
}


void opcao (Dados *processo, int escolha)
{
	
	switch (escolha) {   //De acordo com a opção escolhida, a função correspondente é chamada:
		case 1:
			insere (processo);   //Chama a função das linhas 126-206
			printa_arquivo (processo);
			break;
			
		case 2:
			busca (processo);   //Chama a função das linhas 127-209
			break;
		
		case 3:
			edita (processo);   //Chama a função das linhas 333-379
			break;
		
		case 4:
			retira (&processo);
			break;
		
		case 5:
			exibicao_especial (processo);
			break;
		
		case 6:
			exit (0);
			break;
			
		default:
			printf ("\n\nOp%c%co inv%clida!", 135, 198, 160);
			getch ();
	}
}


void insere (Dados *processo)   //Função que insere elementos na lista:
{
	int escolha1, caractere, quant_linhas = 1, i;
	static int x = 0;
	Dados *aux, *p, *novo;
	FILE *file;	
	
	do {   //Modo de leitura dos dados doprocesso:
    	printf ("\nDigite:\n\n [1] - Leitura de arquivo\n [2] - Via teclado\n\n  ");
    	scanf ("%i", &escolha1);
    	
    	if (escolha1 == 1) {   //Caso seja escolhida a opção de leitura de arquivo:
    		file = fopen ("Processos.txt", "r");   //O processo é aberto para leitura
    		
    		while ((caractere = fgetc (file)) != EOF) {   //Caractere por caractere é lido até chegar ao final do arquivo
    	
				if (caractere == '\n') {   //Ao haver quebra de linha:
    				quant_linhas++;   //Adiciona-se 1 à uma variável contadora
    			}
			}
			quant_linhas /= 4;	//Há informações de apenas 1 processo a cada 4 linhas no arquivo		
			fclose (file);   //O arquivo é fechado							
			aux = (Dados*) calloc (quant_linhas, sizeof (Dados));   //É alocado dinamicamente espaço para a quantidade de processos (calculada anteriormente)
								
			if (!aux) {   //Caso dê erro de alocação:
      			printf("\n\nErro! Mem%cria insuficiente!\n", 162);
      		} else {
      			file = fopen ("Processos.txt", "r");   //O processo é aberto para leitura
				  										
				for (i = 0; i < quant_linhas; i++) {   //A informações lidas são salvas num vetor de struct:
					fscanf (file, "%i\n", &aux[i].numero);
					fgets (aux[i].foro, sizeof (aux->foro), file);
					fgets (aux[i].advogado, sizeof (aux->advogado), file);
					fgets (aux[i].cliente, sizeof (aux->cliente), file);							
				}
				
				for (i = 0; i < quant_linhas; i++) {   //As informações salvas no vetor de struct são passadas pra lista encadeada:
					novo = (Dados*) malloc (sizeof (Dados));   //Alocação das células da lista
					x += 1;   //Incrementação do número do arquivo:
					novo->numero = x;
					//Cópia de strings do vetor pra lista:
					strcpy (novo->foro, aux[i].foro);
					strcpy (novo->advogado, aux[i].advogado);
					strcpy (novo->cliente, aux[i].cliente);
					
					novo->proximo = NULL;   //A célula passa a apontar pra nulo
					
					if (vazia (processo)) {   //Chama a função das linhas 234-242
						processo = novo;   //A primeira posição da lista recebe uma célula
					} else {
						p = processo;   //O ponteiro p aponta para o início da lista
						
						while (p->proximo != NULL) {   //E vai percorrendo-a até encontrar a última célula
							p = p->proximo;
						}
						p->proximo = novo;   //Adiciona-se outra célula ao fim da lista
					}					
				}
				printf ("\n\nProcesso(s) carregado(s).\n");
				getch ();
				
			}
    	} else if (escolha1 == 2) {   //Caso seja escolhida a opção de leitura pelo teclado:
    		Dados *novo = aloca (&x);   //Chama a função das linhas 212-231 e passa o endereço da variável de incrementação do número do processo
			novo->proximo = NULL;   //Faz a célula retornada apontar pra nulo
			
			if (vazia (processo)) {   //Chama a função das linhas 234-242
				processo = novo;   //A primeira posição da lista recebe uma célula
			} else {
				Dados *p = processo;   //O ponteiro p aponta para o início da lista
				
				while (p->proximo != NULL) {   //E vai percorrendo-a até encontrar a última célula
					p = p->proximo;
				}
				p->proximo = novo;   //Adiciona-se outra célula ao fim da lista
			}	
			printf ("\n\nProcesso armazenado.\n");
			getch ();								    		
		} 
					
	} while ((escolha1 != 1) && (escolha1 != 2));		
}


Dados *aloca (int *x)   //Nessa função é feita uma alocação por vez:
{
	Dados *novo = (Dados *) malloc (sizeof (Dados));   //Aloca uma célula
	
	if (!novo) {   //Caso dê erro de alocação:
		printf ("\n\nErro ao alocar!\n");   
		exit (1);   //Finaliza o programa
	} else {
		*x += 1;   //Incrementação do número do arquivo:
		novo->numero = *x;	
		fflush(stdin);	//Limpa o buffer do teclado
		printf ("\n\nNome do foro: ");
		gets (novo->foro);   //Lê e salva a string do nome do foro
		printf ("\nNome do advogado: ");
		gets (novo->advogado);   //Lê e salva a string do nome do advogado
		printf ("\nNome do cliente: ");
		gets (novo->cliente);    //Lê e salva a string do nome do cliente
		
		return novo;   //Retorna a célula
	}
}


int vazia (Dados *processo)   //Verifica se a lista (a primeira posição dela) está vazia:
{
	
	if (processo == NULL) {   //Caso sim:
		return 1;   //Retorna 1 (verdade)
	} else {   //Caso não:
		return 0;   //Retorn 0 (falso)
	}		
}


int busca (Dados *processo)   //Função que busca elementos na lista
{
	int num, escolha2;
	char adv[TAM], cli[TAM];
	Dados *p;
	
	p = processo;	//O ponteiro p aponta para o início da lista
	
	
	do {   //Modo de busca dos dados do processo:
		printf ("\nConsultar por:\n\n [1] - N%cmero\n [2] - Advogado\n [3] - Cliente\n\n  ", 163);
		scanf ("%i", &escolha2);   //Leitura da opção de busca
	
		if (escolha2 == 1) {   //Caso seja escolhida a opção de busca pelo número do processo:
			printf ("\n\nN%cmero do processo: ", 163);
			scanf ("%i", &num);   //Leitura do número do processo desejado
			
			while ((p != NULL) && (p->numero != num)) {   //A lista é percorrida até encontrar a última célula ou o processo do número informado:
				p = p->proximo;
			}
			
			if (p == NULL) {   //Caso o ponteiro aponte pra nulo, ou seja, está vazio pois chegou ao fim da lista ou nenhum processo foi ainda cadastrado:
		 		printf("\n\nProcesso n%co encontrado.\n", 198);
				getch ();
			} else {   //Caso não; quer dizer que a informação procurada foi encontrada e a lista parou de ser percorridd na sua exata posição
				//Os ítens dessa célula são exibidos:
				printf("\n\n%c Processo %i:\n", 26, p->numero);
				printf ("\n%s", p->foro);	
				printf ("\n%s", p->advogado);
				printf ("\n%s\n", p->cliente);
				getch ();
			}
		} else if (escolha2 == 2) {   //Caso seja escolhida a opção de busca pelo nome do advogado:
			printf ("\n\nNome do advogado: ");
			fflush (stdin);
			gets (adv);   //Leitura do nome do advogado do processo desejado
			
			while (p != NULL) {   //A lista é percorrida várias vezes até a última posição, pra verificar se há mais processos que correspondem a busca
				
				while ((p != NULL) && (strcmp (p->advogado, adv) != 0)) {   //A lista é percorrida até encontrar a última célula ou o processo do advogado informado:
					p = p->proximo;
				}
			
				if (p == NULL) {   //Caso o ponteiro aponte pra nulo, ou seja, está vazio pois chegou ao fim da lista ou nenhum processo foi ainda cadastrado:
			 		printf("\n\nProcesso n%co encontrado.\n", 198);
					getch ();
					return 0;
				} else {   //Caso não; quer dizer que a informação procurada foi encontrada e a lista parou de ser percorridd na sua exata posição
					//Os ítens dessa célula são exibidos:
					printf("\n\n%c Processo %i:\n", 26, p->numero);
					printf ("\n%s", p->foro);	
					printf ("\n%s", p->advogado);
					printf ("\n%s\n", p->cliente);
				}
				p = p->proximo;
			}
			getch ();
			
		} else if (escolha2 == 3) {   //Caso seja escolhida a opção de busca pelo nome do cliente:
			printf ("\n\nNome do cliente: ");
			fflush (stdin);
			gets (cli);   //Leitura do nome do cliente do processo desejado
		
			while (p != NULL) {   //A lista é percorrida várias vezes até a última posição, pra verificar se há mais processos que correspondem a busca
				
				while ((p != NULL) && (strcmp (p->cliente, cli) != 0)) {   //A lista é percorrida até encontrar a última célula ou o processo do cliente informado:
					p = p->proximo;
				}
			
				if (p == NULL) {   //Caso o ponteiro aponte pra nulo, ou seja, está vazio pois chegou ao fim da lista ou nenhum processo foi ainda cadastrado:
			 		printf("\n\nProcesso n%co encontrado.\n", 198);
					getch ();
					return 0;
				} else {   //Caso não; quer dizer que a informação procurada foi encontrada e a lista parou de ser percorrida na sua exata posição
					//Os ítens dessa célula são exibidos:
					printf("\n\n%c Processo %i:\n", 26, p->numero);
					printf ("\n%s", p->foro);	
					printf ("\n%s", p->advogado);
					printf ("\n%s\n", p->cliente);
				}
				p = p->proximo;
			}
			getch ();
		}
	} while ((escolha2 < 1) || (escolha2 > 3));
}


void edita (Dados *processo)   //Função que edita elementos da lista
{
	int num, escolha3;
	char fo[TAM], adv[TAM], cli[TAM];
	Dados *p = processo;   //O ponteiro p aponta para o início da lista
	
	printf ("\n\nN%cmero do processo: ", 163);
	scanf ("%i", &num);   //Lê o número de processo para pesquisa
			
	while ((p != NULL) && (p->numero != num)) {   //A lista é percorrida até encontrar a última célula ou o processo do número informado:
		p = p->proximo;
	}
		
	if (p == NULL) {   //Caso o ponteiro aponte pra nulo, ou seja, está vazio pois chegou ao fim da lista ou nenhum processo foi ainda cadastrado:
		printf("\n\nProcesso n%co encontrado.\n", 198);
		getch ();
	} else {   //Caso não; quer dizer que a informação procurada foi encontrada e a lista parou de ser percorrida na sua exata posição
		//Os ítens dessa célula são exibidos:
		printf("\n\n%c Processo %i:\n", 26, p->numero);
		printf ("\n%s", p->foro);	
		printf ("\n%s", p->advogado);
		printf ("\n%s\n", p->cliente);
		
		do {   //Modo de edição dos dados do processo:
			printf ("\nEditar:\n\n [1] - Foro\n [2] - Advogado\n [3] - Cliente\n\n  ", 163);
			scanf ("%i", &escolha3);   //Leitura da opção de edição
	
			if (escolha3 == 1) {   //Caso seja escolhida a opção de edição do nome do foro:
				printf ("\n\nNome do foro: ");
				fflush(stdin);
				gets (fo);   //A string nova é lida
				strcpy (p->foro, fo);   //E copiada pro campo em que a antiga estava
			} else if (escolha3 == 2) {   //Caso seja escolhida a opção de edição do nome do advogado:
				printf ("\n\nNome do advogado: ");
				fflush(stdin);
				gets (adv);   //A string nova é lida
		    	strcpy (p->advogado, adv);   //E copiada pro campo em que a antiga estava
			} else if (escolha3 == 3) {   //Caso seja escolhida a opção de edição do nome do advogado:
				printf ("\n\nNome do cliente: ");
				fflush(stdin);
				gets (adv);   //A string nova é lida
				strcpy (p->cliente, adv);   //E copiada pro campo em que a antiga estava
			}
		} while ((escolha3 < 1) || (escolha3 > 3));
	}
}


void retira (Dados **processo)   //Função que remove elementos da lista
{
	int num, cont = 0;
   	Dados *anterior, *atual, *aux;
	
   
	if (!(vazia (*processo))) {   //Chama a função das linhas 234-242
   		printf ("\n\nN%cmero do processo: ", 163);
   		scanf ("%i", &num);   //Lê o número de processo para pesquisa
   		//São necessários 2 ponteiros auxiliares para exclusão de um elemento:
		anterior = *processo;   //O ponteiro aponta para a primeira posição
   		atual = (*processo)->proximo;   //O ponteiro aponta para o próximo da primeira posição
	   
		while ((atual != NULL) && (atual->numero != num)) {   //A lista é percorrida até encontrar a última célula ou o processo do número informado:
	    	//Atualização dos ponteiros:
			anterior = atual;
	      	atual = atual->proximo;
	   	}
	   
		if (atual != NULL) {   //Caso não aponte para nulo; quer dizer que a informação procurada foi encontrada e a lista parou de ser percorrida na exata posição para exclusão
	    	anterior->proximo = atual->proximo;   //O ponteiro anterior à posição desejada aponta para o próximo da célula em questão
	      	free (atual);   //A célula desejada da lista é desalocada
	      	printf ("\n\nProcesso removido.\n");
	      		      	
			for (aux = (*processo)->proximo; aux != NULL; aux = aux->proximo) {   //A lista é percorrida até encontrar a última célula
	  			cont = cont + 1;   //E os processos são ordenados pelo número
				aux->numero = cont;
			}
	    } else {   //Caso o ponteiro aponte pra nulo, ou seja, está vazio pois chegou ao fim da lista ou nenhum processo foi ainda cadastrado:
	    	printf("\n\nProcesso n%co encontrado.\n", 198);
			getch ();
	    }			 	
	}  else {   //Caso o ponteiro aponte pra nulo desde o início:
	    	printf("\n\nLista vazia.\n", 198);
			getch ();
	}	
}


void exibicao_especial (Dados *processo)   //Função que exibe elementos específicos da lista
{
    int escolha5;
    char adv[TAM];
    Dados *primeiro = NULL, *ultimo = NULL, *novo, *p = processo->proximo, *aux = processo->proximo;
        
	if (aux != NULL) {   //Caso a lista não esteja vazia:
		printf ("\n\nNome do advogado: ");
    	fflush(stdin);
    	gets(adv);  //Leitura do nome do advogado para pesquisa
    
    
	    while (aux != NULL) {   //Repetição para percorrer a lista em busca de mais de 1 processo desse mesmo advogado:
	    	
    		if (strcmp (aux->advogado, adv) == 0) {   //Compara a string lida com a(s) string(s) salva
	            novo = (Dados*) malloc (sizeof (Dados));
	   	        //Copia os dados da lista para outra a estrutura que foi alocada:
				novo->numero = aux->numero;
				strcpy (novo->foro, aux->foro);
				strcpy (novo->advogado, aux->advogado);
				strcpy (novo->cliente, aux->cliente);
				
				novo->proximo = NULL;   //A célula passa a apontar pra nulo
						
				if (vazia (processo)) {   //Chama a função das linhas 234-242
					primeiro = novo;   //Um ponteiro aponta pra estrutura alocada, sendo o primeiro da lista
					ultimo = primeiro;   //Outro ponteiro aponta pro anterior, sendo o último da lista
				} else {
					p = primeiro;   //O ponteiro p aponta para o início da lista
					
					while (p->proximo != NULL) {   //A lista é percorrida até a última célula:
						p = p->proximo;
					}
					p->proximo = novo;   //O ponteiro próximo da última célula passa a apontar pra estrutura alocada
					ultimo = novo;   //Outro ponteiro aponta pra mesma estrutura
	        	}
	   		}
			aux = aux->proximo;	   		
	   	}
	    
	    do {   //Modo de exibição dos dados do processo do advogado:
	    	printf ("\nExibir em ordem:\n\n [1] - Crescente\n [2] - Decrescente\n\n");
	    	scanf("%i", &escolha5);   //Leitura da opção
	    	
			if (escolha5 == 1) {   //Caso seja em ordem crescente:
	        	Dados *a = primeiro;   //Um ponteiro aponta pra primeira posição da lista crescentemente ordenada
	        	
				while (a != NULL) {   //Caso não aponte pra nulo; os ítens dessa lista são printados:
	        		printf("\n %c Processo %i:\n", 26, a->numero);
					printf ("\n%s", a->foro);	
					printf ("\n%s", a->advogado);
					printf ("\n%s\n", a->cliente);	
					a = a->proximo;   //A lista é percorrida
	        	}
	        	getch ();
	    	} else if (escolha5 == 2) {   //Caso seja em ordem crescente:
	    	    Dados *b = ultimo;   //Um ponteiro aponta pra primeira posição da lista decrescentemente ordenada
	    	    
	        	while (b != NULL){   //Caso não aponte pra nulo; os ítens dessa lista são printados:
	        		printf("\n %c Processo %i:\n", 26, b->numero);
					printf ("\n%s", b->foro);	
					printf ("\n%s", b->advogado);
					printf ("\n%s\n", b->cliente);	
					b = b->anterior;   //A lista é percorrida ao contrário
	    		}
	    		getch ();	    	}
	    	
		} while ((escolha5 != 1) || (escolha5 != 2));
	} else {   //Caso o ponteiro aponte pra nulo desde o início:
		printf ("\n\nLista vazia.\n");
		getch ();
	}	
}


/*
Função para exibir os processos (ela percorre a lista e printa os dados):
*/
void exibe (Dados *processo)
{
	system("cls");
	printf ("\n\t\t\t   %c Processos existentes: \n", 254);
	
	
	if (vazia (processo)) {
		printf ("\n\nLista vazia!\n");
		getch ();
	}
	
	Dados *p = processo->proximo;
	
	
	while (p != NULL) {
		printf("\n %c Processo %i:\n", 26, p->numero);
		printf ("\n%s", p->foro);	
		printf ("\n%s", p->advogado);
		printf ("\n%s\n", p->cliente);	
		p = p->proximo;
		getch ();
	}
}


/*
Função que printa num arquivo os processos cadastrados:
*/
void printa_arquivo (Dados *processo) 
{
	FILE *file = fopen ("Processos (2).txt", "w+"); 
    Dados *aux = processo;
    
    for (aux = processo->proximo; aux != NULL; aux = aux->proximo) {
        fprintf(file, "%d\n%s\n%s\n%s\n", aux->numero, aux->foro, aux->advogado, aux->cliente);      
    }    
    fclose(file);
}