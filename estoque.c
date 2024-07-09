#include "estoque.h"
#include <string.h>
#include <stdlib.h>

/* Cria um novo medicamento */
Medicamento * CriaMedicamento ( char *nome ,int codigo , float valor ,int* data_de_validade ){
    Medicamento *droga = (Medicamento*) malloc(sizeof(Medicamento));
    if (droga == NULL){printf("\nErro de alocação de memoria na criação do medicamento!"); return 0;}
    strcpy(droga->nome, nome);
    droga->codigo= codigo;
    droga->valor= valor;
    for(int n = 0; n<3 ; n++){
        droga->data[n] = data_de_validade[n];
    }
    return droga;
}

// Cria a lista
Lista * CriaLista (){
    return NULL;
}

/* Insere um medicamento em uma lista */
Lista * InsereListaMedicamento ( FILE * fp , Lista * l , Medicamento * m ){
    FILE *out_fp = fopen("saida.txt", "a");
    if (out_fp == NULL) {
        printf("\nFalha em abrir o arquivo de saída!");
        return l;
    }

    Lista *novo = (Lista*) malloc(sizeof(Lista));
    novo->prox = l;
    novo->remedio= m;
    fprintf(out_fp, "MEDICAMENTO %s %i ADICIONADO\n", m->nome, m->codigo);
    fclose(out_fp);
    return novo;
}

/* Retira um medicamento de uma determinada lista */
Lista * RetiraListaMedicamento(FILE *fp, Lista *l, int id_medicamento) {
    FILE *out_fp = fopen("saida.txt", "a");
    if (out_fp == NULL) {
        printf("\nFalha em abrir o arquivo de saída!");
        return l;
    }

    Lista *aux, *anterior = NULL;
    aux = l;
    
    while (aux != NULL) {
        if (aux->remedio->codigo == id_medicamento) {
            if (anterior == NULL) {
                l = aux->prox;
            } else {
                anterior->prox = aux->prox;
            }
            fprintf(out_fp, "MEDICAMENTO %s %i RETIRADO\n", aux->remedio->nome, aux->remedio->codigo);
            free(aux->remedio);
            free(aux);
            fclose(out_fp);
            return l;
        }
        anterior = aux;
        aux = aux->prox;
    }
    
    fprintf(out_fp, "MEDICAMENTO %i NÃO ENCONTRADO NA LISTA\n", id_medicamento);
    fclose(out_fp);
    return l;
}

/* Verifica se um medicamento e s t presente em uma determinada lista */
void VerificaListaMedicamento ( FILE * fp , Lista * l , int id_medicamento ){
    FILE *out_fp = fopen("saida.txt", "a");
    if (out_fp == NULL) {
        printf("\nFalha em abrir o arquivo de saída!");
    }
    Lista *aux;
    for(aux=l; aux != NULL; aux = aux->prox){
        if(id_medicamento == aux->remedio->codigo){
            fprintf(out_fp, "MEDICAMENTO ENCONTRADO %s, %i, %.2f, %i/%i/%i\n", aux->remedio->nome, aux->remedio->codigo, aux->remedio->valor, aux->remedio->data[0], aux->remedio->data[1], aux->remedio->data[2]);
            fclose(out_fp);
            return;
        }
    }
    fprintf(out_fp, "MEDICAMENTO %i NAO ENCONTRADO\n", id_medicamento);
    fclose(out_fp);
}

/* Verifica se existe um medicamento vencido em uma determinada lista */
void VerificaListaValidade ( FILE * fp , Lista * l , int * data ){
    FILE *out_fp = fopen("saida.txt", "a");
    if (out_fp == NULL) {
        printf("\nFalha em abrir o arquivo de saída!");
    }
    Lista *aux;
    for(aux=l; aux != NULL; aux = aux->prox){
        if(aux->remedio->data[2]  < data[2]){
            fprintf(out_fp, "MEDICAMENTO %s %i VENCIDO\n", aux->remedio->nome, aux->remedio->codigo);
        }
        else if(aux->remedio->data[2] == data[2]){
            if(aux->remedio->data[1] < data[1]){
                fprintf(out_fp, "MEDICAMENTO %s %i VENCIDO\n", aux->remedio->nome, aux->remedio->codigo);
            }
            else if(aux->remedio->data[1] == data[1]){
                if(aux->remedio->data[0] < data[0]){
                    fprintf(out_fp, "MEDICAMENTO %s %i VENCIDO\n", aux->remedio->nome, aux->remedio->codigo);
                }
            }
        }
    }
    fclose(out_fp);
}

/* Imprime todos os medicamentos de uma lista */
void ImprimeListaMedicamentos ( FILE * fp , Lista * l ){
    FILE *out_fp = fopen("saida.txt", "a");
    if (out_fp == NULL) {
        printf("\nFalha em abrir o arquivo de saída!");
        return;
    }

    Lista *aux;
    for(aux=l; aux != NULL; aux = aux->prox){
        fprintf(out_fp, "%s %i %.2f %i/%i/%i\n", aux->remedio->nome, aux->remedio->codigo, aux->remedio->valor, aux->remedio->data[0], aux->remedio->data[1], aux->remedio->data[2]);
    }
    fclose(out_fp);
}

void trocaListas(Lista *A, Lista *B){
    Medicamento *c;
    c= A->remedio;
    A->remedio=B->remedio;
    B->remedio=c;
}

/* Ordena Lista pelo valor do medicamento */
Lista * OrdenaListaValor ( Lista * list ){
    if(list == NULL){
        printf("Nao e possivel ordenar a lista pois ela encontra-se vazia"); return NULL;
    }
    Lista *c1, *c2, *guarda = NULL;
    for(c1= list; c1 != NULL ; c1= c1->prox){
        guarda = c1;
        for(c2=c1->prox; c2 != NULL; c2=c2->prox){
            if(c2->remedio->valor < guarda->remedio->valor){
                guarda = c2;
            }
        }
        trocaListas(c1, guarda);
    }
    return list;
}

/* Ordena Lista pela data de vencimento do medicamento */
Lista * OrdenaListaVencimento ( Lista * list ){
    if(list == NULL){
        printf("Nao e possivel ordenar a lista pois ela encontra-se vazia"); return NULL;
    }
    Lista *i, *j, *guard = NULL;
    for(i=list; i != NULL; i= i->prox){
        guard = i;
        for(j=i->prox; j != NULL; j=j->prox){
            if(j->remedio->data[2] < guard->remedio->data[2] || 
               (j->remedio->data[2] == guard->remedio->data[2] && j->remedio->data[1] < guard->remedio->data[1]) || 
               (j->remedio->data[2] == guard->remedio->data[2] && j->remedio->data[1] == guard->remedio->data[1] && j->remedio->data[0] < guard->remedio->data[0])){
                guard= j;
            }
        }
        trocaListas(i, guard);
    }
    return list;
}

//Atualiza o preço de um medicamento pelo seu código
Lista *AtualizaPrecoMedicamento(FILE *fp, Lista *list, int code, float novoPreco){
    FILE *out_fp = fopen("saida.txt", "a");
    if (out_fp == NULL) {
        printf("\nFalha em abrir o arquivo de saída!");
        return list;
    }
    Lista *aux;
    for(aux=list; aux != NULL; aux = aux->prox){
        if(aux->remedio->codigo == code){
            aux->remedio->valor = novoPreco;
            fprintf(out_fp, "PRECO ATUALIZADO %s %.2f\n", aux->remedio->nome, aux->remedio->valor);
            fclose(out_fp);
            return list;
        }
    }
    fprintf(out_fp, "MEDICAMENTO %i NAO ENCONTRADO PARA ATUALIZAR\n", code);
    fclose(out_fp);
    return list;
}
