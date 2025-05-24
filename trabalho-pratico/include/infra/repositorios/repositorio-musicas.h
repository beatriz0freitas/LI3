/**
 * @file repositorio-musicas.h
 * @brief Declarações de funções e estruturas referentes ao repositório de músicas.
 * 
 * Este arquivo contém as definições da estrutura `RepositorioMusicas` e as funções associadas
 * para criar, manipular, buscar e destruir um repositório de músicas.
 */
#ifndef REPOSITORIO_MUSICAS_H
#define REPOSITORIO_MUSICAS_H

#include "musica.h"

/**
 * @brief Estrutura para representar um repositório de músicas.
 * 
 * A estrutura `RepositorioMusicas` armazena as músicas.
 * Cada música é identificada de forma única e armazenada com base no seu ID.
 */
typedef struct RepositorioMusicas RepositorioMusicas;


/**
 * @brief Cria e inicializa um novo repositório de músicas.
 * 
 * @return Um apontador para o repositório de músicas criado.
 */
RepositorioMusicas *repositorio_musicas_novo();


/**
 * @brief Liberta a memória associada a um repositório de músicas.
 * 
 * @param repo Apontador para o repositório de músicas a ser libertado.
 */
void repositorio_musicas_destroi(RepositorioMusicas *repo);


/**
 * @brief Adiciona uma música ao repositório de músicas.
 * 
 * @param repo Apontador para o repositório de músicas a ser modificado.
 * @param musica Apontador para a música a ser adicionada.
 */
void repositorio_musicas_adicionar(RepositorioMusicas *repo, Musica *musica);


/**
 * @brief Retorna uma música a partir do seu ID.
 * 
 * @param repo Apontador para o repositório de músicas a ser consultado.
 * @param id Apontador para o ID da música a ser recuperada.
 * @return Apontador para a música correspondente ao ID, ou `NULL` se não existir.
 */
Musica *repositorio_musicas_get_musica_por_id(RepositorioMusicas *repo, int *id);

#endif 
