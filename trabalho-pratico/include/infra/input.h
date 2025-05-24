/**
 * @file input.h
 * @brief Declarações de funções e estrutura para leitura de arquivos linha por linha.
 *
 * Este módulo facilita a leitura de arquivos texto, permitindo processar linha por linha
 * de forma eficiente.
 */

#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <glib.h>

/**
 * @brief Estrutura para gerir a leitura de um arquivo.
 */
typedef struct Input Input;

/**
 * @brief Cria e inicializa uma instância de `Input` para leitura de um arquivo.
 *
 * @param caminhoFicheiro Caminho para o arquivo que será aberto para leitura.
 * @return Um apontador para uma nova instância de `Input`, ou `NULL` em caso de erro.
 */
Input *input_novo(char *caminhoFicheiro);

/**
 * @brief Liberta os recursos associados a uma instância de `Input`.
 *
 * @param input Apontador para a instância de `Input` a ser destruída.
 */
void input_destroi(Input *input);

/**
 * @brief Lê a próxima linha do arquivo gerido pela instância de `Input`.
 *
 * @param input Apontador para a instância de `Input`.
 * @param linha Apontador para onde a linha lida será armazenada (deve ser `NULL` inicialmente).
 * @return `TRUE` se uma linha foi lida com sucesso, ou `FALSE` se o final do arquivo foi alcançado.
 */
gboolean input_proxima_linha(Input *input, char **linha);

#endif