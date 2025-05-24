/**
 * @file repositorio-utilizadores.h
 * @brief Declarações de funções e estruturas referentes ao repositório de utilizadores.
 * 
 * Este arquivo contém as definições da estrutura `RepositorioUtilizadores` e as funções associadas
 * para criar, manipular, buscar e destruir um repositório de utilizadores. 
 */
#ifndef REPOSITORIO_UTILIZADORES_H
#define REPOSITORIO_UTILIZADORES_H

#include "utilizador.h"

/**
 * @brief Estrutura para representar um repositório de utilizadores.
 * 
 * A estrutura `RepositorioUtilizadores` armazena os utilizadores, por ID,
 * permitindo acesso rápido e eficiente aos dados dos utilizadores.
 */
typedef struct RepositorioUtilizadores RepositorioUtilizadores;


/**
 * @brief Cria e inicializa um novo `RepositorioUtilizadores`.
 * 
 * @return Um apontador para o novo `RepositorioUtilizadores`.
 */
RepositorioUtilizadores *repositorio_utilizadores_novo();


/**
 * @brief Liberta a memória associada a um `RepositorioUtilizadores`.
 * 
 * @param repo Apontador para o `RepositorioUtilizadores` a ser libertado.
 */
void repositorio_utilizadores_destroi(RepositorioUtilizadores *repo);


/**
 * @brief Adiciona um `Utilizador` ao `RepositorioUtilizadores`.
 * 
 * @param repo Apontador para o `RepositorioUtilizadores` a ser modificado.
 * @param utilizador Apontador para o `Utilizador` a ser adicionado.
 */
void repositorio_utilizadores_adicionar(RepositorioUtilizadores *repo, Utilizador *utilizador, GHashTable *UtilizadoresNecessarios);


/**
 * @brief Retorna um `Utilizador` a partir do seu ID.
 * 
 * @param repo Apontador para o `RepositorioUtilizadores` a ser consultado.
 * @param id Apontador para o ID do `Utilizador` a ser recuperado.
 * @return Apontador para o `Utilizador` correspondente ao ID fornecido, ou `NULL` se não existir.
 */
Utilizador *repositorio_utilizadores_get(RepositorioUtilizadores *repo, int id);

/**
 * @brief Retorna o número total de utilizadores no repositório.
 * 
 * @param repo Apontador para o `RepositorioUtilizadores`.
 * @return O número total de utilizadores.
 */
int repositorio_utilizadores_get_tamanho(RepositorioUtilizadores *repo);

/**
 * @brief Adiciona um novo indice ao respetivo id do Utilizador
 * 
 * @param repo Apontador para o `RepositorioUtilizadores`.
 * @param idUtilizador Id do utilizador a associar o indice.
 * 
 */
void repositorio_utilizadores_adiciona_utilizador_indice_linha (RepositorioUtilizadores *repo, int idUtilizador);


/**
 * @brief Retora o indice de um utilizador na linha ordenada
 * 
 * @param repo Apontador para o `RepositorioUtilizadores`.
 * @param idUtilizador Id do utilizador a associar o indice.
 * 
 * @return Indice do utilizador na linha ordenada.
 */

gpointer repositorio_utilizadores_get_indice_linha (RepositorioUtilizadores *repo, int idUtilizador);

/**
 * @brief Retora o proximo indice de um utilizador novo
 * 
 * @param repo Apontador para o `RepositorioUtilizadores`.
 * 
 * @return Indice para um novo utilizador na linha ordenada.
 */

int repositorio_utilizadores_get_proximoIndiceLinha(RepositorioUtilizadores *repo);

/**
 * @brief Cria uma lista com a ordem dos Utilizadores na matriz.
 * 
 * @param repo Apontador para o `RepositorioUtilizadores`.
 * 
 */

void repositorio_utilizadores_cria_ordemLinhasUtilizadores(RepositorioUtilizadores *repo);

/**
 * @brief Retorna a lista criada com a ordem dos Utilizadores na matriz.
 * 
 * @param repo Apontador para o `RepositorioUtilizadores`.
 * 
 * @return lista dos Ids dos utilizadores pela ordem da matriz.
 */

char **repositorio_utilizadores_get_ordemLinhasUtilizadores(RepositorioUtilizadores *repo);

/**
 * @brief Retorna o tamanho do indice.
 * 
 * @param repo Apontador para o `RepositorioUtilizadores`.
 * 
 * @return Numero de utilizadores presentes no incide (tamanho).
 */

int repositorio_utilizadores_get_tamanho_indice (RepositorioUtilizadores *repo);

/**
 * @brief Verfica se um utilizador existe no indice.
 * 
 * @param repo Apontador para o `RepositorioUtilizadores`.
 * @param id Id do utilizador a verificar.
 * 
 * @return TRUE se o utilizador existe e FALSE caso contrário.
 */

gboolean repositorio_utilizadores_existe(RepositorioUtilizadores *repo, int id);

#endif 
