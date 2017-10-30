/*
Autora: Camille de L. Jesus

Componente Curricular: EXA854 - MI Algoritmos

Data: 11/12/2014

Declaro que este c�digo foi elaborado por mim de forma individual e n�o cont�m nenhum
trecho de c�digo de outro colega ou de outro autor, tais como provindos de livros e
apostilas, e p�ginas ou documentos eletr�nicos da Internet. Qualquer trecho de c�digo
de outra autoria que n�o a minha est� destacado com uma cita��o para o autor e a fonte
do c�digo, e estou ciente que estes trechos n�o ser�o considerados para fins de avalia��o.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 50

// C�digo do Sistema de Gerenciamento de Processos (JuriSoft) //

typedef struct dados {   //Estrutura para armazenar os dados processuais
						int numero;
						char foro[TAM], advogado[TAM], cliente[TAM];
						struct dados *anterior;
   						struct dados *proximo;
} Dados;

//Prot�tipo das fun��es (elas ser�o explicadas individualmente em seu escopo):
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


int main (void)   //Fun��o principal
{
	system("color 0F");	
	int escolha;	
	Dados *processo = (Dados *) malloc (sizeof (Dados));   //Aloca��o din�mica da primeira c�lula da lista	
	
	if (!processo) {   //Caso d� erro de aloca��o:
		printf ("\n\nErro ao alocar!\n");
		exit (1);   //Finaliza o programa
	} else {   //Caso a aloca��o seja feita com sucesso:
		inicia (processo);   //Chama a fun��o das linhas 74-77
	
		do {
			system ("cls");
			escolha = menu ();   //Chama a fun��o das linhas 80-89
			opcao (processo, escolha);   //Chama a fun��o das linhas 92-124
		} while (escolha);
	free (processo);   //Desaloca o ponteiro
	
	return 0;
	}	
}


void inicia (Dados *processo)   //Faz a primeira posi��o da lista apontar pra nulo:
{
	processo = NULL;
}


int menu (void)   //Fun��o que exibe o menu de op��es do sistema e l� a op��o escolhida:
{
	int escolha;	
	printf ("\n\t\t%c%c Sistema de Gerenciamento de Processos (JuriSoft) %c%c\n\n", 254, 254, 254, 254);
    printf ("\nDigite:\n\n [1] - Cadastro\n [2] - Consulta Espec%cfica\n [3] - Edi%c%co\n [4] - Remo%c%co\n [5] - Exibi%c%co Especial\n [6] - Sair\n\n  ", 161, 135, 198, 135, 198, 135, 198);
    scanf ("%i", &escolha);	
	return escolha;   //Retorna a op��o digitada
}


void opcao (Dados *processo, int escolha)
{
	
	switch (escolha) {   //De acordo com a op��o escolhida, a fun��o correspondente � chamada:
		case 1:
			insere (processo);   //Chama a fun��o das linhas 126-206
			printa_arquivo (processo);
			break;
			
		case 2:
			busca (processo);   //Chama a fun��o das linhas 127-209
			break;
		
		case 3:
			edita (processo);   //Chama a fun��o das linhas 333-379
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


void insere (Dados *processo)   //Fun��o que insere elementos na lista:
{
	int escolha1, caractere, quant_linhas = 1, i;
	static int x = 0;
	Dados *aux, *p, *novo;
	FILE *file;	
	
	do {   //Modo de leitura dos dados doprocesso:
    	printf ("\nDigite:\n\n [1] - Leitura de arquivo\n [2] - Via teclado\n\n  ");
    	scanf ("%i", &escolha1);
    	
    	if (escolha1 == 1) {   //Caso seja escolhida a op��o de leitura de arquivo:
    		file = fopen ("Processos.txt", "r");   //O processo � aberto para leitura
    		
    		while ((caractere = fgetc (file)) != EOF) {   //Caractere por caractere � lido at� chegar ao final do arquivo
    	
				if (caractere == '\n') {   //Ao haver quebra de linha:
    				quant_linhas++;   //Adiciona-se 1 � uma vari�vel contadora
    			}
			}
			quant_linhas /= 4;	//H� informa��es de apenas 1 processo a cada 4 linhas no arquivo		
			fclose (file);   //O arquivo � fechado							
			aux = (Dados*) calloc (quant_linhas, sizeof (Dados));   //� alocado dinamicamente espa�o para a quantidade de processos (calculada anteriormente)
								
			if (!aux) {   //Caso d� erro de aloca��o:
      			printf("\n\nErro! Mem%cria insuficiente!\n", 162);
      		} else {
      			file = fopen ("Processos.txt", "r");   //O processo � aberto para leitura
				  										
				for (i = 0; i < quant_linhas; i++) {   //A informa��es lidas s�o salvas num vetor de struct:
					fscanf (file, "%i\n", &aux[i].numero);
					fgets (aux[i].foro, sizeof (aux->foro), file);
					fgets (aux[i].advogado, sizeof (aux->advogado), file);
					fgets (aux[i].cliente, sizeof (aux->cliente), file);							
				}
				
				for (i = 0; i < quant_linhas; i++) {   //As informa��es salvas no vetor de struct s�o passadas pra lista encadeada:
					novo = (Dados*) malloc (sizeof (Dados));   //Aloca��o das c�lulas da lista
					x += 1;   //Incrementa��o do n�mero do arquivo:
					novo->numero = x;
					//C�pia de strings do vetor pra lista:
					strcpy (novo->foro, aux[i].foro);
					strcpy (novo->advogado, aux[i].advogado);
					strcpy (novo->cliente, aux[i].cliente);
					
					novo->proximo = NULL;   //A c�lula passa a apontar pra nulo
					
					if (vazia (processo)) {   //Chama a fun��o das linhas 234-242
						processo = novo;   //A primeira posi��o da lista recebe uma c�lula
					} else {
						p = processo;   //O ponteiro p aponta para o in�cio da lista
						
						while (p->proximo != NULL) {   //E vai percorrendo-a at� encontrar a �ltima c�lula
							p = p->proximo;
						}
						p->proximo = novo;   //Adiciona-se outra c�lula ao fim da lista
					}					
				}
				printf ("\n\nProcesso(s) carregado(s).\n");
				getch ();
				
			}
    	} else if (escolha1 == 2) {   //Caso seja escolhida a op��o de leitura pelo teclado:
    		Dados *novo = aloca (&x);   //Chama a fun��o das linhas 212-231 e passa o endere�o da vari�vel de incrementa��o do n�mero do processo
			novo->proximo = NULL;   //Faz a c�lula retornada apontar pra nulo
			
			if (vazia (processo)) {   //Chama a fun��o das linhas 234-242
				processo = novo;   //A primeira posi��o da lista recebe uma c�lula
			} else {
				Dados *p = processo;   //O ponteiro p aponta para o in�cio da lista
				
				while (p->proximo != NULL) {   //E vai percorrendo-a at� encontrar a �ltima c�lula
					p = p->proximo;
				}
				p->proximo = novo;   //Adiciona-se outra c�lula ao fim da lista
			}	
			printf ("\n\nProcesso armazenado.\n");
			getch ();								    		
		} 
					
	} while ((escolha1 != 1) && (escolha1 != 2));		
}


Dados *aloca (int *x)   //Nessa fun��o � feita uma aloca��o por vez:
{
	Dados *novo = (Dados *) malloc (sizeof (Dados));   //Aloca uma c�lula
	
	if (!novo) {   //Caso d� erro de aloca��o:
		printf ("\n\nErro ao alocar!\n");   
		exit (1);   //Finaliza o programa
	} else {
		*x += 1;   //Incrementa��o do n�mero do arquivo:
		novo->numero = *x;	
		fflush(stdin);	//Limpa o buffer do teclado
		printf ("\n\nNome do foro: ");
		gets (novo->foro);   //L� e salva a string do nome do foro
		printf ("\nNome do advogado: ");
		gets (novo->advogado);   //L� e salva a string do nome do advogado
		printf ("\nNome do cliente: ");
		gets (novo->cliente);    //L� e salva a string do nome do cliente
		
		return novo;   //Retorna a c�lula
	}
}


int vazia (Dados *processo)   //Verifica se a lista (a primeira posi��o dela) est� vazia:
{
	
	if (processo == NULL) {   //Caso sim:
		return 1;   //Retorna 1 (verdade)
	} else {   //Caso n�o:
		return 0;   //Retorn 0 (falso)
	}		
}


int busca (Dados *processo)   //Fun��o que busca elementos na lista
{
	int num, escolha2;
	char adv[TAM], cli[TAM];
	Dados *p;
	
	p = processo;	//O ponteiro p aponta para o in�cio da lista
	
	
	do {   //Modo de busca dos dados do processo:
		printf ("\nConsultar por:\n\n [1] - N%cmero\n [2] - Advogado\n [3] - Cliente\n\n  ", 163);
		scanf ("%i", &escolha2);   //Leitura da op��o de busca
	
		if (escolha2 == 1) {   //Caso seja escolhida a op��o de busca pelo n�mero do processo:
			printf ("\n\nN%cmero do processo: ", 163);
			scanf ("%i", &num);   //Leitura do n�mero do processo desejado
			
			while ((p != NULL) && (p->numero != num)) {   //A lista � percorrida at� encontrar a �ltima c�lula ou o processo do n�mero informado:
				p = p->proximo;
			}
			
			if (p == NULL) {   //Caso o ponteiro aponte pra nulo, ou seja, est� vazio pois chegou ao fim da lista ou nenhum processo foi ainda cadastrado:
		 		printf("\n\nProcesso n%co encontrado.\n", 198);
				getch ();
			} else {   //Caso n�o; quer dizer que a informa��o procurada foi encontrada e a lista parou de ser percorridd na sua exata posi��o
				//Os �tens dessa c�lula s�o exibidos:
				printf("\n\n%c Processo %i:\n", 26, p->numero);
				printf ("\n%s", p->foro);	
				printf ("\n%s", p->advogado);
				printf ("\n%s\n", p->cliente);
				getch ();
			}
		} else if (escolha2 == 2) {   //Caso seja escolhida a op��o de busca pelo nome do advogado:
			printf ("\n\nNome do advogado: ");
			fflush (stdin);
			gets (adv);   //Leitura do nome do advogado do processo desejado
			
			while (p != NULL) {   //A lista � percorrida v�rias vezes at� a �ltima posi��o, pra verificar se h� mais processos que correspondem a busca
				
				while ((p != NULL) && (strcmp (p->advogado, adv) != 0)) {   //A lista � percorrida at� encontrar a �ltima c�lula ou o processo do advogado informado:
					p = p->proximo;
				}
			
				if (p == NULL) {   //Caso o ponteiro aponte pra nulo, ou seja, est� vazio pois chegou ao fim da lista ou nenhum processo foi ainda cadastrado:
			 		printf("\n\nProcesso n%co encontrado.\n", 198);
					getch ();
					return 0;
				} else {   //Caso n�o; quer dizer que a informa��o procurada foi encontrada e a lista parou de ser percorridd na sua exata posi��o
					//Os �tens dessa c�lula s�o exibidos:
					printf("\n\n%c Processo %i:\n", 26, p->numero);
					printf ("\n%s", p->foro);	
					printf ("\n%s", p->advogado);
					printf ("\n%s\n", p->cliente);
				}
				p = p->proximo;
			}
			getch ();
			
		} else if (escolha2 == 3) {   //Caso seja escolhida a op��o de busca pelo nome do cliente:
			printf ("\n\nNome do cliente: ");
			fflush (stdin);
			gets (cli);   //Leitura do nome do cliente do processo desejado
		
			while (p != NULL) {   //A lista � percorrida v�rias vezes at� a �ltima posi��o, pra verificar se h� mais processos que correspondem a busca
				
				while ((p != NULL) && (strcmp (p->cliente, cli) != 0)) {   //A lista � percorrida at� encontrar a �ltima c�lula ou o processo do cliente informado:
					p = p->proximo;
				}
			
				if (p == NULL) {   //Caso o ponteiro aponte pra nulo, ou seja, est� vazio pois chegou ao fim da lista ou nenhum processo foi ainda cadastrado:
			 		printf("\n\nProcesso n%co encontrado.\n", 198);
					getch ();
					return 0;
				} else {   //Caso n�o; quer dizer que a informa��o procurada foi encontrada e a lista parou de ser percorrida na sua exata posi��o
					//Os �tens dessa c�lula s�o exibidos:
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


void edita (Dados *processo)   //Fun��o que edita elementos da lista
{
	int num, escolha3;
	char fo[TAM], adv[TAM], cli[TAM];
	Dados *p = processo;   //O ponteiro p aponta para o in�cio da lista
	
	printf ("\n\nN%cmero do processo: ", 163);
	scanf ("%i", &num);   //L� o n�mero de processo para pesquisa
			
	while ((p != NULL) && (p->numero != num)) {   //A lista � percorrida at� encontrar a �ltima c�lula ou o processo do n�mero informado:
		p = p->proximo;
	}
		
	if (p == NULL) {   //Caso o ponteiro aponte pra nulo, ou seja, est� vazio pois chegou ao fim da lista ou nenhum processo foi ainda cadastrado:
		printf("\n\nProcesso n%co encontrado.\n", 198);
		getch ();
	} else {   //Caso n�o; quer dizer que a informa��o procurada foi encontrada e a lista parou de ser percorrida na sua exata posi��o
		//Os �tens dessa c�lula s�o exibidos:
		printf("\n\n%c Processo %i:\n", 26, p->numero);
		printf ("\n%s", p->foro);	
		printf ("\n%s", p->advogado);
		printf ("\n%s\n", p->cliente);
		
		do {   //Modo de edi��o dos dados do processo:
			printf ("\nEditar:\n\n [1] - Foro\n [2] - Advogado\n [3] - Cliente\n\n  ", 163);
			scanf ("%i", &escolha3);   //Leitura da op��o de edi��o
	
			if (escolha3 == 1) {   //Caso seja escolhida a op��o de edi��o do nome do foro:
				printf ("\n\nNome do foro: ");
				fflush(stdin);
				gets (fo);   //A string nova � lida
				strcpy (p->foro, fo);   //E copiada pro campo em que a antiga estava
			} else if (escolha3 == 2) {   //Caso seja escolhida a op��o de edi��o do nome do advogado:
				printf ("\n\nNome do advogado: ");
				fflush(stdin);
				gets (adv);   //A string nova � lida
		    	strcpy (p->advogado, adv);   //E copiada pro campo em que a antiga estava
			} else if (escolha3 == 3) {   //Caso seja escolhida a op��o de edi��o do nome do advogado:
				printf ("\n\nNome do cliente: ");
				fflush(stdin);
				gets (adv);   //A string nova � lida
				strcpy (p->cliente, adv);   //E copiada pro campo em que a antiga estava
			}
		} while ((escolha3 < 1) || (escolha3 > 3));
	}
}


void retira (Dados **processo)   //Fun��o que remove elementos da lista
{
	int num, cont = 0;
   	Dados *anterior, *atual, *aux;
	
   
	if (!(vazia (*processo))) {   //Chama a fun��o das linhas 234-242
   		printf ("\n\nN%cmero do processo: ", 163);
   		scanf ("%i", &num);   //L� o n�mero de processo para pesquisa
   		//S�o necess�rios 2 ponteiros auxiliares para exclus�o de um elemento:
		anterior = *processo;   //O ponteiro aponta para a primeira posi��o
   		atual = (*processo)->proximo;   //O ponteiro aponta para o pr�ximo da primeira posi��o
	   
		while ((atual != NULL) && (atual->numero != num)) {   //A lista � percorrida at� encontrar a �ltima c�lula ou o processo do n�mero informado:
	    	//Atualiza��o dos ponteiros:
			anterior = atual;
	      	atual = atual->proximo;
	   	}
	   
		if (atual != NULL) {   //Caso n�o aponte para nulo; quer dizer que a informa��o procurada foi encontrada e a lista parou de ser percorrida na exata posi��o para exclus�o
	    	anterior->proximo = atual->proximo;   //O ponteiro anterior � posi��o desejada aponta para o pr�ximo da c�lula em quest�o
	      	free (atual);   //A c�lula desejada da lista � desalocada
	      	printf ("\n\nProcesso removido.\n");
	      		      	
			for (aux = (*processo)->proximo; aux != NULL; aux = aux->proximo) {   //A lista � percorrida at� encontrar a �ltima c�lula
	  			cont = cont + 1;   //E os processos s�o ordenados pelo n�mero
				aux->numero = cont;
			}
	    } else {   //Caso o ponteiro aponte pra nulo, ou seja, est� vazio pois chegou ao fim da lista ou nenhum processo foi ainda cadastrado:
	    	printf("\n\nProcesso n%co encontrado.\n", 198);
			getch ();
	    }			 	
	}  else {   //Caso o ponteiro aponte pra nulo desde o in�cio:
	    	printf("\n\nLista vazia.\n", 198);
			getch ();
	}	
}


void exibicao_especial (Dados *processo)   //Fun��o que exibe elementos espec�ficos da lista
{
    int escolha5;
    char adv[TAM];
    Dados *primeiro = NULL, *ultimo = NULL, *novo, *p = processo->proximo, *aux = processo->proximo;
        
	if (aux != NULL) {   //Caso a lista n�o esteja vazia:
		printf ("\n\nNome do advogado: ");
    	fflush(stdin);
    	gets(adv);  //Leitura do nome do advogado para pesquisa
    
    
	    while (aux != NULL) {   //Repeti��o para percorrer a lista em busca de mais de 1 processo desse mesmo advogado:
	    	
    		if (strcmp (aux->advogado, adv) == 0) {   //Compara a string lida com a(s) string(s) salva
	            novo = (Dados*) malloc (sizeof (Dados));
	   	        //Copia os dados da lista para outra a estrutura que foi alocada:
				novo->numero = aux->numero;
				strcpy (novo->foro, aux->foro);
				strcpy (novo->advogado, aux->advogado);
				strcpy (novo->cliente, aux->cliente);
				
				novo->proximo = NULL;   //A c�lula passa a apontar pra nulo
						
				if (vazia (processo)) {   //Chama a fun��o das linhas 234-242
					primeiro = novo;   //Um ponteiro aponta pra estrutura alocada, sendo o primeiro da lista
					ultimo = primeiro;   //Outro ponteiro aponta pro anterior, sendo o �ltimo da lista
				} else {
					p = primeiro;   //O ponteiro p aponta para o in�cio da lista
					
					while (p->proximo != NULL) {   //A lista � percorrida at� a �ltima c�lula:
						p = p->proximo;
					}
					p->proximo = novo;   //O ponteiro pr�ximo da �ltima c�lula passa a apontar pra estrutura alocada
					ultimo = novo;   //Outro ponteiro aponta pra mesma estrutura
	        	}
	   		}
			aux = aux->proximo;	   		
	   	}
	    
	    do {   //Modo de exibi��o dos dados do processo do advogado:
	    	printf ("\nExibir em ordem:\n\n [1] - Crescente\n [2] - Decrescente\n\n");
	    	scanf("%i", &escolha5);   //Leitura da op��o
	    	
			if (escolha5 == 1) {   //Caso seja em ordem crescente:
	        	Dados *a = primeiro;   //Um ponteiro aponta pra primeira posi��o da lista crescentemente ordenada
	        	
				while (a != NULL) {   //Caso n�o aponte pra nulo; os �tens dessa lista s�o printados:
	        		printf("\n %c Processo %i:\n", 26, a->numero);
					printf ("\n%s", a->foro);	
					printf ("\n%s", a->advogado);
					printf ("\n%s\n", a->cliente);	
					a = a->proximo;   //A lista � percorrida
	        	}
	        	getch ();
	    	} else if (escolha5 == 2) {   //Caso seja em ordem crescente:
	    	    Dados *b = ultimo;   //Um ponteiro aponta pra primeira posi��o da lista decrescentemente ordenada
	    	    
	        	while (b != NULL){   //Caso n�o aponte pra nulo; os �tens dessa lista s�o printados:
	        		printf("\n %c Processo %i:\n", 26, b->numero);
					printf ("\n%s", b->foro);	
					printf ("\n%s", b->advogado);
					printf ("\n%s\n", b->cliente);	
					b = b->anterior;   //A lista � percorrida ao contr�rio
	    		}
	    		getch ();	    	}
	    	
		} while ((escolha5 != 1) || (escolha5 != 2));
	} else {   //Caso o ponteiro aponte pra nulo desde o in�cio:
		printf ("\n\nLista vazia.\n");
		getch ();
	}	
}


/*
Fun��o para exibir os processos (ela percorre a lista e printa os dados):
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
Fun��o que printa num arquivo os processos cadastrados:
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