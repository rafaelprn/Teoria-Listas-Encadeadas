#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//LISTA SIMPLES
//TRABALHO DE ESTRUTURA DE DADOS

typedef struct No{
    int chave;
    struct No *prox;
}No;

No *alocaNo(int k);
void imprime(No *p);
void insereBusca(No **p, int buscak, int chave);
void insereOrdenada(No **p, int k);
void removeBusca(No **p, int buscak);
void liberaLista(No **p);
No *divideLista(No **p, int k);

int main(){

No *prim = NULL, *prim2 = NULL;
	int op=1, n, n1;
	while(op!=7){
		printf("\n\nOPCOES:");
        printf("\n1 - InsereBusca");
        printf("\n2 - InsereOrdenado");
        printf("\n3 - RemoveBusca");
        printf("\n4 - RemoveLista");
		printf("\n5 - Imprimir");
		printf("\n6 - Dividir");
		printf("\n7 - Sair");
		printf("\nInforme opcao: ");
		scanf("%d", &op);

		switch(op)
		{
			case 1:
				{
                    printf("\nInforme o numero que deseja inserir: ");
                    scanf("%d", &n);
                    printf("Agora informe onde deseja inseri-lo: ");
                    scanf("%d", &n1);
                    insereBusca(&prim, n1, n);
					
				}break;

			case 2:
				{
                    printf("\nInforme o numero que deseja inserir: ");
                    scanf("%d", &n);
                    insereOrdenada(&prim, n);
					
				}break;

			case 3:
				{
					printf("\nInforme o numero que deseja remover: ");
                    scanf("%d", &n);
                    removeBusca(&prim, n);

				}break;

            case 4:
                {
                    printf("Qual lista deseja remover? ");
                    scanf("%d", &n);
                    if(n == 1){
                        printf("\nRemovendo a Lista 1...");
                        liberaLista(&prim);
                        imprime(prim);
                    }
                    else{
                        printf("\nRemovendo a Lista 2...");
                        liberaLista(&prim2);
                        imprime(prim2);
                    }

                }break;

            case 5:
                {
                    printf("\nLista 1: ");
					imprime(prim);
					printf("\n############\nLista 2: ");
					imprime(prim2);
                }break;

            case 6:
                {
                    int n;
					if(prim2 != NULL){
						printf("\nNAO PODE DIVIDIR");
					}
					else{
						printf("\nInforme Numero: ");
						scanf("%d", &n);
						prim2 = divideLista(&prim, n);
					}
                }break;
             case 7:
                {
                    printf("\nFIM\n");
                }break;

		default: printf("\nOpcao Invalida");
		}
	}

	return 0;
}


//FUNCTIONS
void insereBusca(No **p, int buscak, int chave){ //prim: a lista, 
    No *novo = *p, *paux = NULL; // vamos usar novo p navegar, paux vai ser o novo no

    if (*p == NULL){
        printf("Lista vazia!\n");
        return;
    }

    while(novo != NULL){ //percorrer a lista
        if (novo->chave == buscak){//faz a inserção, mexe com os pont prox
            paux = alocaNo(chave);
            paux->prox = novo->prox;
            novo->prox = paux;
            return;
        }
        novo = novo->prox;
    }
    printf("Elemento nao encontrado.");
}

void insereOrdenada(No **p, int k){
	assert(p);
    No *novo = alocaNo(k); //vai alocar o novo no
    No *paux = *p; //paux vai percorrer a lista
    //if (novo == NULL) return; //caso tenha dado errado
    if (*p == NULL){//caso a lista esteja vazia ate entao
        novo->prox = NULL;
        *p = novo;
        return;
    } 
    else if(novo->chave< (*p)->chave){ //é o menor?
        novo->prox = *p;
        *p = novo; //se for insere no inicio
        return;
    }
    else{ //se nao for o menor nó
        while(paux->prox && novo->chave > paux->prox->chave){//enquanto tiver prox e a chave do novo for maior q o prox
            paux = paux->prox; //vai caminhar na lista
        }
        novo->prox = paux->prox; //caso ele seja o maior
        paux->prox = novo; //vai inserir no final
        return;
    }
}

void removeBusca(No **p, int buscak){
    assert(p);
    No *aux = *p, *ant = *p, *remove; //vamos usar prim p remover, ant fica o anterior
    if(*p == NULL){
        printf("Lista vazia!\n");
        return;
    }
    if(aux->chave == buscak){
        aux = (*p)->prox;
        remove = *p;
        (*p) = aux;
        free(remove);
        return;
    }
    while(aux != NULL){
        //if(aux == NULL) return;
        if (aux->chave == buscak){
            ant->prox = aux->prox;
            free(aux);
            aux = NULL;
            return;
        }
        ant = aux;
        aux = aux->prox;
    }
}

void liberaLista(No **p){ //recursividade
    if (*p == NULL){
        return;
    }
    liberaLista(&(*p)->prox);
    (*p)->prox = NULL;
    free(*p);
    *p = NULL;
}

No *divideLista(No **p, int k){ //pega uma chave e divide a lista em 2 a partir dele
	No *aux = NULL, *ant = NULL;
	if( *p == NULL) return NULL; //a lista esta vazia
	aux = *p;
	if( (*p)->chave == k){ //caso o item passado seja ao primeiro elemento da lista
		*p = NULL;
		return aux;
	}
	else{//se nao for o primeiro (n precisa do else pq tem return)
		ant = aux;
		aux = aux->prox;
		while(aux != NULL){
			if(aux->chave == k){//se eu encontrei o campo de divisao
				ant->prox = NULL; //ant ta no ultimo no da 2 lista (dividida antes do campo escolhido)
				return aux;
			}
			ant = aux; //ant tem q ficar no anterior de aux
			aux = aux->prox; //aux vai pro proximo ja q ant ta atras dele
		}
		printf("\nCHAVE NAO ENCONTRADA"); //saiu do while sem encontrar nada
		return NULL;
	}
	
}

No *alocaNo(int k) //alocar 1 nó na memória
{
 No *no; 
 no = (No *) malloc(sizeof(No)); 
 if (no == NULL) return NULL;
 no->chave = k;
 no->prox = NULL;
 return no;
}

void imprime(No *p)
{
	if(p == NULL){
        printf("\nLista vazia!");
        return;
    }
	while(p != NULL){
		printf("\n%d", p->chave);
		p = p->prox;
	}
}