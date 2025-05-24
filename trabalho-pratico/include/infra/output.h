/**
 * @file output.h
 * @brief Declarações de funções e tipos para impressão de estruturas genéricas.
 *
 * Este arquivo define o tipo de função `FuncaoToString` e a função `output_print` que permitem imprimir
 * informações de estruturas genéricas, através da conversão da estrutura em uma string representativa.
 */
#ifndef OUTPUT_PRINT_H
#define OUTPUT_PRINT_H

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <glib.h>

/**
 * @brief Tipo de função que converte uma estrutura genérica numa string,
 * que pode ser usada para impressão ou registo.
 *
 * @param estrutura Apontador para a estrutura que será convertida em string.
 * @return Apontador para a string representando a estrutura.
 */
typedef char *(*FuncaoToString)(void *estrutura, const char *delimitador);


/**
 * @brief Imprime uma estrutura genérica num arquivo de saída.
 *
 * Esta função chama a função de conversão fornecida (`FuncaoToString`) para obter uma
 * string representando a estrutura fornecida e imprime essa string. O número do comando é
 * utilizado para indicar qual comando foi invocado para chamar a função de impressão e dar nome ao ficheiro.
 * 
 * @param structure Apontador para a estrutura que será convertida e impressa.
 * @param funcao_ToString Função que converte a estrutura numa string.
 * @param numeroDoCommando Número do comando que gerou a impressão.
 */
void output_print(void *structure, const char *delimitador, FuncaoToString funcao_ToString, int numeroDoCommando);

/**
 * @brief Imprime uma estrutura genérica no terminal.
 *
 * Esta função chama a função de conversão fornecida (`FuncaoToString`) para obter uma
 * string representando a estrutura fornecida e imprime essa string. O número da query é
 * utilizado para indicar qual query foi respondida.
 * 
 * @param structure Apontador para a estrutura que será convertida e impressa.
 * @param funcao_ToString Função que converte a estrutura numa string.
 * @param numeroDoCommando Número da query executada.
 */

void output_terminal(void *structure, const char *delimitador, FuncaoToString funcao_ToString, int numeroDaQuery);
#endif 
