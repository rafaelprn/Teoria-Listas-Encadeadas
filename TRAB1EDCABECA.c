#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//LISTA COM CABEÇA
//TRABALHO DE ESTRUTURA DE DADOS

typedef struct No{
    int chave;
    struct No *prox;
}No;

No *alocaNo(int k);
No *criaLista();
void imprimeCab(No *p);
void insereBusca(No *lista, int buscak, int chave);
void insereOrdenada(No *p, int k);
void removeBusca(No *p, int buscak);
void liberaLista(No *p);
No *divideLista(No *p, int k);

int main(){

    No *prim1 = criaLista();
    No *prim2 = criaLista();
	int op=0, n, n1;
	while(op!=7){
		printf("\n\nOPCOES:");
        printf("\n1 - InsereBusca");
        printf("\n2 - InsereOrdenado");
        printf("\n3 - RemoveBusca");
        printf("\n4 - LiberaLista");
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
                    insereBusca(prim1, n1, n);
					
				}break;

			case 2:
				{
                    printf("\nInforme o numero que deseja inserir: ");
                    scanf("%d", &n);
                    insereOrdenada(prim1, n);
	
				}break;

			case 3:
				{
					printf("\nInforme o numero que deseja remover: ");
                    scanf("%d", &n);
                    removeBusca(prim1, n);

				}break;

            case 4:
                {
                    printf("Qual lista deseja remover? ");
                    scanf("%d", &n);
                    if(n == 1){
                        printf("\nRemovendo a Lista 1...");
                        liberaLista(prim1);
                        imprimeCab(prim1->prox);
                    }
                    else{
                        printf("\nRemovendo a Lista 2...");
                        liberaLista(prim2);
                        imprimeCab(prim2->prox);
                    }
            
                }break;

            case 5:
                {
                    printf("\nLista 1: ");
					imprimeCab(prim1->prox);
					printf("\n##############\nLista 2: ");
					imprimeCab(prim2->prox);

                }break;

            case 6:
                {
                    int n;
					if(prim2->prox != NULL){
						printf("\nNAO PODE DIVIDIR");
					}
					else{
						printf("\nInforme Numero: ");
						scanf("%d", &n);
						prim2->prox = divideLista(prim1, n);
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
No *criaLista(){
  No *cabeca = (No *)malloc(sizeof(No)); //alocando
  if (cabeca == NULL) return NULL; //caso de errado
  cabeca->chave = -1; //valor reservado, ja que esse é o nó cabeça
  cabeca->prox = NULL; //como até o momento é o primeiro nó
  return cabeca; //retorna o endereço pro ponteiro usado na main
}

void insereBusca(No *lista, int buscak, int chave){ //prim: a lista, 
    No *paux = lista->prox, *novo = NULL; // vamoS usar novo p navegar, novo vai ser o paux no
    if (paux == NULL){
        printf("Lista vazia!\n");
        return;
    }
    while(paux != NULL){ //percorrer a lista
        if (paux->chave == buscak){//faz a inserção, mexe com os pont prox
            novo = alocaNo(chave);
            novo->prox = paux->prox;
            paux->prox = novo;
            return;
        }
        paux = paux->prox;
    }
    printf("\nElemento nao encontrado.");
}

void insereOrdenada(No *p, int k){
	assert(p);
    No *novo = alocaNo(k); //vai alocar o novo no
    No *paux = p; //paux vai percorrer a lista
    if (p->prox == NULL){//caso a lista esteja vazia ate entao
        novo->prox = NULL;
        p->prox = novo;
        return;
    } 
    else if(novo->chave< p->prox->chave){ //é o menor?
        novo->prox = p->prox;
        p->prox = novo; //se for insere no inicio
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

void removeBusca(No *p, int buscak){
    assert(p);
    if(p->prox == NULL){
        printf("Lista vazia!\n");
        return;
    }
    No *aux = p->prox, *ant = p; //vamos usar prim p remover, ant fica o anterior
    while(aux != NULL){
        //if(aux == NULL) return;
        if (aux->chave == buscak){
            ant->prox = aux->prox;
            free(aux);
            return;
        }
        ant = aux;
        aux = aux->prox;
    }
}

void liberaLista(No *p){
    if (p->prox == NULL){
        return;
    }
    liberaLista(p->prox);
    p->prox = NULL;
    free(p->prox);
    p->prox = NULL;
}

No *divideLista(No *p, int k){ //pega uma chave e divide a lista em 2 a partir dele
	No *aux = NULL, *ant = NULL;
	if(p->prox == NULL) return NULL; //a lista esta vazia
	aux = p->prox;
	if(p->prox->chave == k){ //caso o item passado seja o primeiro elemento da lista
		p->prox = NULL;
		return aux;
	}
	else{//se nao for o primeiro (n precisa do else pq tem return)
		ant = aux;
		aux = aux->prox;
		while(aux != NULL){
			if(aux->chave == k){//se eu encontrei o campo de divisao
				ant->prox = NULL; //ant ta no ultimo no da 2 lista (dividida antes do campo escolhido)
                // No *prim3 = criaLista();
                // prim3->prox = aux;
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

void imprimeCab(No *p)
{
	if(p == NULL){
        printf("\nLista vazia!");
        //return;
    }
	while(p != NULL){
		printf("\n%d", p->chave);
		p = p->prox;
	}
}