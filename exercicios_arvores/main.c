#include "arvore.h"
#include <stdlib.h>
#include <stdio.h>

/*EXERCICIO 2*/

Arv *arv_insere(Arv *a, char c){
    if (a==NULL){
        a = (Arv *) malloc (sizeof(Arv));
        a->info = c; 
        a->esq = a->dir = NULL;
    }
    else if(c < a->info)
        a->esq = arv_insere(a->esq, c);
    else
        a->dir = arv_insere(a->dir, c);
  return a; 
}

/*EXERCICIO 3*/

int *arv_conta(Arv *a, int * dados){

    if (!arv_vazia(a)){
        if(a->esq==NULL && a->dir==NULL){
            dados[0] = dados[0] + 1;
        }
        else if(a->esq==NULL || a->dir==NULL){
            dados[1] = dados[1] + 1;
            
            
            if(!(arv_vazia(a->esq))){
                dados = arv_conta(a->esq, dados);
            }
            else if(!(arv_vazia(a->dir))){
                dados = arv_conta(a->dir, dados);
            }

        }
        else if((!(arv_vazia(a->esq))) && (!arv_vazia(a->dir))){
            dados[2] = dados[2] + 1;
            
            dados = arv_conta(a->esq, dados);
            dados = arv_conta(a->dir, dados);
        }
        return dados;
    }
    else{
        return dados; 
    }
}

/*EXERCICIO 4*/
int *arv_histograma(Arv * a, int * occur){
    if(!arv_vazia(a)){
        occur[(int)a->info] = occur[(int)a->info]+1;    
        occur = arv_histograma(a->esq, occur);
        occur = arv_histograma(a->dir, occur);
    }
    return occur;
}
void imprime_histograma(int * occur){
    int altura = 0; 
    for(int i = 0; i < 254; i++){
        if(altura < occur[i]){
            altura = occur[i];
        }
    }
    for(int j = 0; j < altura; altura--){
        for(int i  = 0; i < 254; i++){
            if(occur[i] != 0){
             if(occur[i] < altura){
                printf("    ");
             }
             else{
                printf("*   ");
             }
            }
        }
        printf("\n");
    }
    for(int i  = 0; i < 254; i++){
          if(occur[i] != 0){
            printf("%c   ", (char)i);
          }
    }
    printf("\n");
}

int main(){

    Arv *tree; 
    int *occur = (int *) calloc (254, sizeof(int));
    int *dados = (int *) calloc (3, sizeof(int));
    int altura; 

    /*EXERCICIO 2 - INSERÇÃO DE ELEMENTOS NUMA ÁRVORE*/
    tree = arv_criavazia();
    tree = arv_insere(tree, 'c');
    tree = arv_insere(tree, 'a');
    tree = arv_insere(tree, 'a');
    tree = arv_insere(tree, 'd');
    tree = arv_insere(tree, 'b');

    /*EXERCICIO 1 - IMPLEMENTAÇÃO DOS TIPOS DE PERCUSO*/
    printf("\nPREORDEM:  ");
    arv_imprime_preordem(tree);
    printf("\nSIMETRICA: ");
    arv_imprime_simetrica(tree);
    printf("\nPOSORDEM:  ");
    arv_imprime_posordem(tree);
    printf("\n");


    /*EXERCICIO 3 - IMPLEMENTAÇÃO E IMPRESSÃO DOS DADOS DE UMA ARVORE, FOLHAS
      NOS DE UM FILHO, E NOHS DE DOIS FILHOS*/
    dados = arv_conta(tree, dados);
    printf("\nDADOS ARVORES: ");
    printf("%d", dados[0]);
    printf("%d", dados[1]);
    printf("%d", dados[2]);
    printf("\n\nHISTOGRAMA: \n\n");

    /*EXERCICIO 4 - IMPLEMENTAÇÃO E IMPRESSAO DE UM H ISTOGRAMA DE OCORRENCIA
      DE UMA ARVORE*/
    occur = arv_histograma(tree, occur);
    imprime_histograma(occur);
    
    


    return 0;
}