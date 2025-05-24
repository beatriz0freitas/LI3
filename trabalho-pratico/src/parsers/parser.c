#include "parser.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COLUNAS 100

void parser_carrega(void *contexto, char *caminhoFicheiro, AdicionaObjeto adiciona_objeto, LinhaParaObjeto linha_para_objeto, DestroiObjeto destroi_objeto)
{
    FILE *ficheiro = fopen(caminhoFicheiro, "r");

    char *nomeFicheiro = utils_obtem_nome_ficheiro(caminhoFicheiro);

    char *caminhoFicheiroErros = g_strconcat("resultados/", nomeFicheiro, "_errors.csv", NULL);
    g_free(nomeFicheiro);

    FILE *ficheiroDeErros = fopen(caminhoFicheiroErros, "a");
    g_free(caminhoFicheiroErros);

    if (ficheiroDeErros == NULL)
    {
        perror("Erro ao abrir o ficheiro de erros");
        fclose(ficheiro);
        return;
    }

    char *linha = NULL;
    size_t tamanho = 0;

    // Lê a primeira linha e escreve no ficheiro de erros 
    if (getline(&linha, &tamanho, ficheiro) != -1)
    {
        fprintf(ficheiroDeErros, "%s", linha);
    }
    else
    {
        printf("Erro ao ler a primeira linha do ficheiro.\n");
        fclose(ficheiro);
        fclose(ficheiroDeErros);
        if (linha)
        {
            free(linha);
        }
        return;
    }

    // Processa o restante do ficheiro linha a linha
    while (getline(&linha, &tamanho, ficheiro) != -1)
    {
        char *colunas[MAX_COLUNAS + 1];
        int numColunas = 0;

        char *linhaErro = g_strdup(linha);

        colunas[numColunas] = strtok(linha, ";");
        while (colunas[numColunas] != NULL && numColunas < MAX_COLUNAS)
        {
            numColunas++;
            colunas[numColunas] = strtok(NULL, ";");
        }
        for (int i = 0; i < numColunas; i++)
        {
            utils_remove_aspas(colunas[i]);
        }
        colunas[numColunas] = NULL;

        gpointer objeto = linha_para_objeto(colunas);

        if (objeto == NULL || !adiciona_objeto(contexto, objeto))
        {
            fprintf(ficheiroDeErros, "%s", linhaErro); 
            if (objeto)
            {
                destroi_objeto(objeto);
            }
        }
        g_free(linhaErro);
    }
    if (linha)
    {
        free(linha);
    }

    fclose(ficheiro);
    fclose(ficheiroDeErros);
}
