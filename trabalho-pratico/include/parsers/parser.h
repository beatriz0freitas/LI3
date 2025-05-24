/**
 * @file parser.h
 * @brief Definição de funções para carregar dados a partir de ficheiros.
*/
#ifndef PARSER_H
#define PARSER_H

#include "utils.h"

/**
 * @brief Função que converte uma linha de um ficheiro num objeto.
 * 
 * O tipo `LinhaParaObjeto` representa uma função que recebe uma linha de texto e a converte
 * em um objeto específico, que é retornado como `gpointer`.
*/
typedef gpointer (*LinhaParaObjeto)(char **coluna);


/**
 * @brief Função que adiciona um objeto a uma estrutura de dados.
 * 
 * O tipo `AdicionaObjeto` representa uma função que recebe um contexto e um objeto, e adiciona
 * esse objeto ao contexto. Retorna `TRUE` se o objeto foi adicionado com sucesso, `FALSE` caso contrário.
*/
typedef gboolean (*AdicionaObjeto)(void *contexto, gpointer objeto);


/**
 * @brief Função que liberta a memoória alocada para um objeto.
*/
typedef void (*DestroiObjeto)(gpointer objeto);


/**
 * @brief Carrega dados a partir de um ficheiro e adiciona-os a uma estrutura de dados.
 * 
 * Esta função lê um ficheiro de texto linha a linha, e para cada linha chama a função `linha_para_objeto`
 * para converter a linha num objeto. Se a conversão for bem sucedida, o objeto é adicionado ao contexto
 * através da função `adiciona_objeto`. Caso contrário, a linha é escrita num ficheiro de erros.
 * 
 * @param contexto Apontador para a estrutura de dados onde os objetos serão armazenados.
 * @param caminhoFicheiro Caminho para o ficheiro de onde os dados serão lidos.
 * @param adiciona_objeto Função que adiciona um objeto ao contexto.
 * @param linha_para_objeto Função que converte uma linha de texto num objeto.
 * @param destroi_objeto Função que liberta a memória alocada para um objeto.
*/
void parser_carrega(void *contexto, char *caminhoFicheiro, AdicionaObjeto adiciona_objeto, LinhaParaObjeto linha_para_objeto, DestroiObjeto destroi_objeto);

#endif
