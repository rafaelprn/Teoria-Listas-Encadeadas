#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//LISTA DUPLAMENTE ENCADEADA
//TRABALHO DE ESTRUTURA DE DADOS

typedef struct No{
    int chave;
    struct No *prox, *ant;
}No;

No *alocaNo(int k);
void imprimeDuplaEnc(No *p);
void insereBuscaDupla(No **p, int buscak, int chave);
void insereOrdenadaDupla(No **p, int k);
void removeBuscaDupla(No **p, int buscak);
void liberaListaDupla(No **p);
No *divideListaDupla(No **p, int k);

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
                    printf("Agora informe aonde deseja inseri-lo: ");
                    scanf("%d", &n1);
                    insereBuscaDupla(&prim, n1, n);
					
				}break;

			case 2:
				{
                    printf("\nInforme o numero que deseja inserir: ");
                    scanf("%d", &n);
                    insereOrdenadaDupla(&prim, n);					
				}break;

			case 3:
				{
					printf("\nInforme o numero que deseja remover: ");
                    scanf("%d", &n);
                    removeBuscaDupla(&prim, n);

				}break;

            case 4:
                {
                    printf("Qual lista deseja remover? ");
                    scanf("%d", &n);
                    if(n == 1){
                        printf("\nRemovendo a Lista 1...");
                        liberaListaDupla(&prim);
                    }
                    else{
                        printf("\nRemovendo a Lista 2...");
                        liberaListaDupla(&prim2);
                    }

                }break;

            case 5:
                {
                    printf("\nLista 1: ");
					imprimeDuplaEnc(prim);
					printf("\n############\nLista 2: ");
					imprimeDuplaEnc(prim2);
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
						prim2 = divideListaDupla(&prim, n);
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

void insereBuscaDupla(No **p, int buscak, int chave){
    No *novo = NULL, *paux = *p; // vamos usar paux p navegar, novo vai ser o novo no
    novo = alocaNo(chave);

    while(paux != NULL){//vai percorrer a lista
        if(paux->chave == buscak){ //se achou a chave
            if(paux->prox == NULL){//o nó procurado é o ultimo
                novo->prox = NULL;
                novo->ant = paux;
                paux->prox = novo;
                return;
            }
            else{//não é o ultimo nó
                paux->prox->ant = novo;
                novo->prox = paux->prox;
                paux->prox = novo;
                novo->ant = paux;
                return;
            }
        }
        paux = paux->prox;
    }
    printf("\nA chave nao foi encontrada.");
}

void insereOrdenadaDupla(No **p, int k){
    assert(p);
    No *paux = *p; //paux vai auxiliar a verificar
	No* novo = (No *)malloc(sizeof(No)); //alocando
	novo->chave = k; 

    if(*p == NULL){//a lista esta vazia?
        novo->prox = NULL;
        novo->ant = NULL;
        *p = novo;
        return;
    }
	else if(novo->chave < (*p)->chave){//é o menor item?
        novo->ant = NULL;
        novo->prox = paux;
        paux->ant = novo;
        *p = novo;
        return;
    }
    else{//não é o menor item, tem que andar ate achar um maior que ele pra inserir antes
        while((paux->prox != NULL) && (novo->chave > paux->prox->chave)){
            paux = paux->prox; //vai andar na lista
        }//quando sair do while é pq o proximo nó é maior que o novo, agora basta fazer a inserção
        if(paux->prox == NULL){ //é o maior no da lista?
            paux->prox = novo;
            novo->ant = paux;
            novo->prox = NULL;
            return;
        }
        else{ //não é o maior da lista
            novo->prox = paux->prox;
            paux->prox->ant = novo;
            novo->ant = paux;
            paux->prox = novo;
            return;
        }
    }
}

void removeBuscaDupla(No **p, int buscak){
    No *paux = *p;
	if (*p == NULL){
		printf("\nLista vazia\n");
		return;
	}
        while(paux != NULL){//vai percorrer a lista
        if(paux->chave == buscak){ //se achou a chave

            if(paux->prox == NULL && paux->ant == NULL){ //é o unico no da lista
                free(*p);
                *p = NULL;
                return;
            }
            else if(paux->prox == NULL){//o nó procurado é o ultimo?
                paux->ant->prox = NULL;//penultimo no olha pra nulo
                paux->ant = NULL;
                paux->prox = NULL;
                free(paux);
                return;
            }
            else{//não é o ultimo nó, (é o primeiro ou esta no meio)
                paux->prox->ant = paux->ant;
                *p = paux->prox;
                paux->prox = NULL;
                paux->ant = NULL;
                free(paux);
                paux = NULL;
                return;
            }
        }
        paux = paux->prox;
    }
    printf("\nA chave nao foi encontrada.");
}

void liberaListaDupla(No **p){
    No *aux = *p;
    while(aux != NULL){
        aux = aux->prox;
        free(*p);
        *p = aux;
    }
}

No *divideListaDupla(No **p, int k){ //pega uma chave e divide a lista em 2 a partir dele
	No *aux = NULL, *ant = NULL;
	if(*p == NULL) return NULL; //a lista esta vazia
	aux = *p;
	if( (*p)->chave == k){ //caso o item passado seja o primeir elemento da lista
		*p = NULL;
		return aux;
	}
	else{//se nao for o primeiro (n precisa do else pq tem return)
		ant = aux;
		while(aux != NULL){
			if(aux->chave == k){//se eu encontrei o campo de divisao
				ant->prox = NULL; //ant->prox ta no ultimo no da 1 lista 
                aux->ant = NULL; //aux->ant ta no primeiro no da 2 lista 
				return aux;
			}
			ant = aux; //ant tem q ficar no anterior de aux
			aux = aux->prox; //aux vai pro proximo ja q ant ta atras dele
		}
		printf("\nCHAVE NAO ENCONTRADA"); //saiu do while sem encontrar nada
		return NULL;
	}	
}

No *alocaNo(int k){
	No *no; 
	no = (No *) malloc(sizeof(No)); 
	if (no == NULL) return NULL;
	no->chave = k;
	no->prox = NULL;
	no->ant = NULL;
	return no;
}

void imprimeDuplaEnc(No *p){
    No *aux = p;
    if(p == NULL){
        printf("\nLista vazia!");
        return;
    }
    while(aux->prox != NULL){
        printf("\n%d ", aux->chave);
        aux = aux->prox;
    }
    printf("\n%d ", aux->chave);
}
