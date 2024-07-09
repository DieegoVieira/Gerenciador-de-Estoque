#ifndef ESTOQUE_H_INCLUDED
#define ESTOQUE_H_INCLUDED

#include <stdio.h>

// Tipo que define o medicamento
typedef struct Medicamento {
    char nome[20];
    int codigo;
    float valor;
    int data[3]; // Representa a data no formato [dia, mes, ano]
} Medicamento;

// Tipo que define o nó da lista
typedef struct Lista {
    Medicamento *remedio;
    struct Lista *prox;
} Lista;

/* Cria um novo medicamento */
Medicamento * CriaMedicamento(char *nome, int codigo, float valor, int *data_de_validade);

/* Cria a lista */
Lista * CriaLista();

/* Insere um medicamento em uma lista */
Lista * InsereListaMedicamento(FILE *fp, Lista *l, Medicamento *m);

/* Retira um medicamento de uma determinada lista */
Lista * RetiraListaMedicamento(FILE *fp, Lista *l, int id_medicamento);

/* Verifica se um medicamento está presente em uma determinada lista */
void VerificaListaMedicamento(FILE *fp, Lista *l, int id_medicamento);

/* Verifica se existe um medicamento vencido em uma determinada lista */
void VerificaListaValidade(FILE *fp, Lista *l, int *data);

/* Imprime todos os medicamentos de uma lista */
void ImprimeListaMedicamentos(FILE *fp, Lista *l);

/* Ordena Lista pelo valor do medicamento */
Lista * OrdenaListaValor(Lista *l);

/* Ordena Lista pela data de vencimento do medicamento */
Lista * OrdenaListaVencimento(Lista *l);

//Atualiza o preço de um medicamento pelo seu código
Lista *AtualizaPrecoMedicamento(FILE *fp, Lista *list, int code, float novoPreco);

#endif // ESTOQUE_H_INCLUDED
