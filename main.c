#include "arvore.h"
#include <stdlib.h>
#include <stdio.h>


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
/*
    NUMERO DE FOLHAS
    NUMERO DE NOHS COM UM FILHO
    NUMERO DE NOHS COM DOIS FILHOS
*/
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

int *arv_histograma(Arv * a, int * occur){
    if(!arv_vazia(a)){
        occur[(int)a->info] = occur[(int)a->info]+1;    
        occur = arv_histograma(a->esq, occur);
        occur = arv_histograma(a->dir, occur);
    }
    return occur;
}

int main(){

    Arv *tree; 
    int *occur = (int *) calloc (254, sizeof(int));
    int *dados = (int *) calloc (3, sizeof(int));
    int altura; 

    tree = arv_criavazia();
    tree = arv_insere(tree, 'c');
    tree = arv_insere(tree, 'a');
    tree = arv_insere(tree, 'a');
    tree = arv_insere(tree, 'a');
    tree = arv_insere(tree, 'a');
    tree = arv_insere(tree, 'a');
    tree = arv_insere(tree, 'a');
    tree = arv_insere(tree, 'd');
    tree = arv_insere(tree, 'd');
    tree = arv_insere(tree, 'd');
    tree = arv_insere(tree, 'd');
    tree = arv_insere(tree, 'b');
    dados = arv_conta(tree, dados);
    occur = arv_histograma(tree, occur);
    //printf("%d%d%d%d\n", occur[97], occur[98], occur[99], occur[100]);
    //printf("%d%d%d\n", dados[0], dados[1], dados[2]);
    //arv_imprime_simetrica(tree);
    altura = 0; 
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


    return 0;
}