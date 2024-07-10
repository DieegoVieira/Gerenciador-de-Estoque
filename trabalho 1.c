#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estoque.h"

int main() {
    FILE *fp;
    fp = fopen("entrada.txt", "r");
    if (fp == NULL) {
        printf("\nFalha em abrir o arquivo!");
        return 0;
    }
    Lista *estoque = CriaLista();

    char linha[100];
    char medicamento[50];
    int cod, validade[3];
    float preco;

    while (fscanf(fp, "%s", linha) != EOF) {
        if (strcmp(linha, "FIM") == 0) {
            printf("O arquivo foi lido e a saida encontra-se no arquivo \"saida.txt\"");
            break;
        } 
        else if (strcmp(linha, "MEDICAMENTO") == 0) {
            fscanf(fp, "%s %i %f %i %i %i", medicamento, &cod, &preco, &validade[0], &validade[1], &validade[2]);
            Medicamento *remedio = CriaMedicamento(medicamento, cod, preco, validade);
            estoque = InsereListaMedicamento(fp, estoque, remedio);
        }
        else if (strcmp(linha, "RETIRA") == 0) {
            fscanf(fp, "%i", &cod);
            estoque = RetiraListaMedicamento(fp, estoque, cod);
        }
        else if (strcmp(linha, "IMPRIME_LISTA") == 0) {
            ImprimeListaMedicamentos(fp, estoque);
        }
        else if (strcmp(linha, "ATUALIZA_PRECO") == 0) {
            fscanf(fp, "%i %f", &cod, &preco);
            estoque = AtualizaPrecoMedicamento(fp, estoque, cod, preco);
        }
        else if (strcmp(linha, "VERIFICA_VALIDADE") == 0) {
            fscanf(fp, "%i %i %i", &validade[0], &validade[1], &validade[2]);
            VerificaListaValidade(fp, estoque, validade);
        }
        else if (strcmp(linha, "VERIFICA_LISTA") == 0) {
            fscanf(fp, "%i", &cod);
            VerificaListaMedicamento(fp, estoque, cod);
        }
        else if (strcmp(linha, "ORDENA_LISTA_VALIDADE") == 0) {
            estoque = OrdenaListaVencimento(estoque);
        }
        else if (strcmp(linha, "ORDENA_LISTA_VALOR") == 0) {
            estoque = OrdenaListaValor(estoque);
        }
        else{
            fprintf(fp, "FALHA NA LEITURA DA LINHA");
        }
    }

    fclose(fp);
    return 0;
}
