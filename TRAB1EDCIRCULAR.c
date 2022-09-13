#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//LISTA CIRCULAR
//TRABALHO DE ESTRUTURA DE DADOS

typedef struct No{
    int chave;
    struct No *prox;
}No;

No *alocaNo(int k);
void imprimeCirc(No *p);
void insereBuscaCirc(No **p, int buscak, int chave);
void insereOrdenadaCirc(No **p, int k);
void removeBuscaCirc(No **p, int buscak);
void liberaListaCirc(No **p);
No *divideLista(No **p, int k);
No *achaUltimo(No **p);

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
                    insereBuscaCirc(&prim, n1, n);
					
				}break;

			case 2:
				{
                    printf("\nInforme o numero que deseja inserir: ");
                    scanf("%d", &n);
                    insereOrdenadaCirc(&prim, n);
					
				}break;

			case 3:
				{
					printf("\nInforme o numero que deseja remover: ");
                    scanf("%d", &n);
                    removeBuscaCirc(&prim, n);

				}break;

            case 4:
                {
                    printf("Qual lista deseja remover? ");
                    scanf("%d", &n);
                    if(n == 1){
                        printf("\nRemovendo a Lista 1...");
                        liberaListaCirc(&prim);
                        imprimeCirc(prim);
                    }
                    else{
                        printf("\nRemovendo a Lista 2...");
                        liberaListaCirc(&prim2);
                        imprimeCirc(prim2);
                    }

                }break;

            case 5:
                {
                    printf("\nLista 1: ");
					imprimeCirc(prim);
					printf("\n############\nLista 2: ");
					imprimeCirc(prim2);
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

void insereCircular(No **p, int k){
    assert(p);
    if(*p == NULL){ //caso nao tenha ninguem nessa lista ainda
        *p = (No*) malloc(sizeof(No)); //cria a lista (primeiro item)
        if(*p != NULL){ //agora que criou a lista (primeiro item)
            (*p)->chave = k;
            (*p)->prox = *p; //o p->prox olha para si mesmo, ja que a lista é circular e ele é o unico item
        }
    }
    else{ //caso ja tenha algum item na lista
        No *pAux = (No*) malloc(sizeof(No)); //cria o segundo nó
        if (pAux == NULL) return; //caso de errado
        pAux->chave = k; //recebe a chave digitada
        pAux->prox = (*p)->prox;//o novo nó olha para o primeiro
        (*p)->prox = pAux; //o primeiro nó olha para o ultimo (que vc acabou de inserir)
    }
}

void insereBuscaCirc(No **p, int buscak, int chave){ //prim: a lista, 
    No *novo = *p, *paux = NULL; // vamos usar novo p navegar, paux vai ser o novo no

    if (*p == NULL){
        printf("Lista vazia!\n");
        return;
    }

    do{ //percorrer a lista
        if (novo->chave == buscak){//faz a inserção, mexe com os pont prox
            paux = alocaNo(chave);
            paux->prox = novo->prox;
            novo->prox = paux;
            return;
        }
        novo = novo->prox;
    }while(paux != *p);

    printf("Elemento nao encontrado.");
    return;
}

void insereOrdenadaCirc(No **p, int k){
	assert(p);
    No *novo = alocaNo(k); //vai alocar o novo no
    No *paux = *p; //paux vai percorrer a lista
    if (*p == NULL){//caso a lista esteja vazia ate entao
        *p = (No *)malloc(sizeof(No));
        if(*p != NULL){
            (*p)->chave = k;
            (*p)->prox = *p;
        }
    } 
    else if(k < paux->chave){ //é o menor?
        while(paux->prox != *p){
            paux = paux->prox; //percorre a lista
        }
        paux->prox = novo;//ultimo olha pro novo 
        novo->prox = *p;
        *p = novo;
    }
    else{ //se nao for o menor nó
        while(paux->prox != *p && novo->chave > paux->prox->chave){//enquanto tiver prox e a chave do novo for maior q o prox
            paux = paux->prox; //vai caminhar na lista
        }
        novo->prox = paux->prox; //caso ele seja o maior
        paux->prox = novo; //vai inserir no final
        return;
    }
}

No *achaUltimo(No **p){
    No *aux = *p;
    do{
        if(aux->prox == *p){
            return aux;
        }
        aux = aux->prox;
    }while(aux != NULL);
}

void removeBuscaCirc(No **p, int buscak){
    assert(p);
    if(*p == NULL) {
        printf("A Lista está vazia!\n");
        return;
    }
    if((*p)->chave == buscak){ //se for o primeiro
        if(((*p)->prox)->chave == (*p)->chave){ //se ele for o unico da lista
            free(*p);
            *p = NULL;
            return;
        }
        else{ //se for o primeiro mas nao for o unico
            No *aux = achaUltimo(p);
            aux->prox = (*p)->prox;
            free(*p);
            *p = aux->prox;
            return;
        }
    }
    No *aux = *p;
    do{
        if(aux->prox->chave = buscak){
            No *remove = aux->prox;
            aux->prox = remove->prox;
            free(remove);
            remove = NULL;
            return;
        }
        aux = aux->prox;
    }while(aux!=NULL);
}

//funcao que apaga todos os nós da lista circular
void liberaListaCirc(No **p){
    assert(p);
    No *aux = *p;
    No *aux2 = NULL;
    do{
        aux2 = aux->prox;
        free(aux);
        aux = aux2;
    }while(aux != *p);
    *p = NULL;
}

No *divideLista(No **p, int k){ //pega uma chave e divide a lista em 2 a partir dele
	No *aux = NULL, *ant = NULL, *ult = achaUltimo(p);
	if(*p == NULL) return NULL; //a lista esta vazia
	aux = *p;
	if( (*p)->chave == k){ //caso o item passado sej ao primeiro e unico elemtno da lista
		*p = NULL;
		return aux;
	}
	//se nao for  primeiro (n precisa do else pq tem return)
	ant = aux;
	do{
		if(aux->chave == k){//se eu encontrei o campo de divisao
			if(ant == *p){//o primeiro item
                ant->prox = ant;
                ult->prox = aux;
                return aux;
            }
            else if(aux->prox == *p){//o ultimo
                ant->prox = *p;
                aux->prox = aux;
                return aux;
            }
            else{//no meio
                ant->prox = *p;
                ult->prox = aux;
                return aux;
            }
		}
		ant = aux; //ant tem q ficar no anterior de aux
		aux = aux->prox; //aux vai pro proximo ja q ant ta atras dele
	}while(aux != *p);
	printf("\nCHAVE NAO ENCONTRADA"); //saiu do while sem encontrar nada
	return NULL;

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

void imprimeCirc(No *p)
{
    No *aux = p;
	if(p == NULL){
        printf("\nLista vazia!");
        return;
    }
	do{
        printf("\n%d", aux->chave);
        aux = aux->prox;
    }while(aux != p);
    return;
}