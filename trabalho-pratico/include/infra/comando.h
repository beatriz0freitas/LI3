/**
 * @file comando.h
 * @brief Declarações de funções e estruturas referentes ao processamento de comandos.
 * 
 * Este arquivo define a estrutura `Comando` e as funções associadas para criar, manipular e destruir
 * comandos, bem como aceder seus atributos.
 */

#ifndef COMANDO_H
#define COMANDO_H

#include <glib.h>
#include "utils.h"


/**
 * @brief Estrutura que representa um comando.
 * 
 * A estrutura `Comando` contém informações sobre o número da query, número do comando,
 * separador e lista de argumentos associados ao comando.
 */
typedef struct Comando Comando;

/**
 * @brief Cria e inicializa um novo comando vazio.
 * 
 * @return Um apontador para o novo comando.
 */
Comando *comando_novo();

/**
 * @brief Liberta a memória associada a um comando.
 * 
 * @param comando Apontador para o comando a ser destruído.
 */
void comando_destroi(Comando *comando);

/**
 * @brief Constrói um comando a partir de uma linha de texto.
 * 
 * @param linha String contendo a linha de texto que representa o comando.
 * @return Um apontador para o comando construído, ou `NULL` se a linha for inválida.
 */
Comando *comando_constroi_de_linha(char *linha);

/**
 * @brief Adiciona um argumento ao comando.
 * 
 * @param comando Apontador para o comando.
 * @param novoArgumento String contendo o argumento a adicona
 * 
 */
void comando_adiciona_argumento(Comando *comando, const char *novoArgumento);

/**
 * @brief Obtém o número da query associada ao comando.
 * 
 * @param comando Apontador para o comando.
 * @return O número da query.
 */
int comando_get_numero_query(Comando *comando);

/**
 * @brief Obtém o separador utilizado no comando.
 * 
 * @param comando Apontador para o comando.
 * @return O separador do comando como uma string constante.
 */
const char *comando_get_separador(Comando *comando);

/**
 * @brief Obtém o argumento do comando por índice.
 * 
 * @param comando Apontador para o comando.
 * @param indice Índice do argumento a ser obtido.
 * @return Uma cópia do argumento no índice especificado, ou `NULL` se o índice for inválido.
 */
char *comando_get_argumento_por_indice(Comando *comando, int indice);

/**
 * @brief Obtém o número do comando.
 * 
 * @param comando Apontador para o comando.
 * @return O número do comando.
 */
int comando_get_numero_comando(Comando *comando);

/**
 * @brief Define o número do comando.
 * 
 * @param comando Apontador para o comando.
 * @param numeroComando O número do comando a ser definido.
 */
void comando_set_numero_comando(Comando *comando, int numeroComando);

/**
 * @brief Define o número da query do comando.
 * 
 * @param comando Apontador para o comando.
 * @param numeroComando O número da query do comando a ser definida.
 */
void comando_set_numero_query(Comando *comando, int numeroComando);

#endif