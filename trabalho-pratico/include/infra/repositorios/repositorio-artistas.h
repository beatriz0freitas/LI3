/**
 * @file repositorio-artistas.h
 * @brief Declarações de funções e estruturas referentes ao repositório de artistas.
 * 
 * Este arquivo contém as definições da estrutura `RepositorioArtistas` e as funções associadas
 * para criar, manipular, buscar e destruir um repositório de artistas.
 */
#ifndef REPOSITORIO_ARTISTAS_H
#define REPOSITORIO_ARTISTAS_H

#include "artista.h"

/**
 * @brief Estrutura para representar um repositório de artistas.
 * 
 */
typedef struct RepositorioArtistas RepositorioArtistas;


/**
 * @brief Cria e inicializa um novo `RepositorioArtistas`.
 * 
 * Esta função aloca memória para um novo `RepositorioArtistas` e inicializa os seus campos.
 * 
 * @return Um apontador para o novo `RepositorioArtistas`.
 */
RepositorioArtistas *repositorio_artistas_novo();


/**
 * @brief Liberta a memória associada a um `RepositorioArtistas`.
 * 
 * Esta função liberta todos os recursos associados ao `RepositorioArtistas`, incluindo
 * os artistas armazenados dentro dele.
 * 
 * @param repo Apontador para o `RepositorioArtistas` a ser libertado.
 */
void repositorio_artistas_destroi(RepositorioArtistas *repo);


/**
 * @brief Adiciona um `Artista` ao `RepositorioArtistas`.
 * 
 * Esta função insere um novo `Artista` no repositório, permitindo a sua gestão e recuperação
 * posterior.
 * 
 * @param repo Apontador para o `RepositorioArtistas` a ser modificado.
 * @param artista Apontador para o `Artista` a ser adicionado.
 */
void repositorio_artistas_adicionar(RepositorioArtistas *repo, Artista *artista);


/**
 * @brief Retorna um `Artista` a partir do seu ID.
 * 
 * Esta função retorna um `Artista` armazenado no repositório a partir do seu ID.
 * 
 * @param repo Apontador para o `RepositorioArtistas` a ser consultado.
 * @param id O ID do `Artista` a ser recuperado.
 * @return Um apontador para o `Artista` encontrado ou `NULL` se o ID não existir.
 */
Artista *repositorio_artistas_get_artista_por_id(RepositorioArtistas *repo, int id);

/**
 * @brief Retorna um artista da lista ordenada de artistas.
 * 
 * @param repo Apontador para o `RepositorioArtistas`.
 * @return Um apontador para o artista da lista de artistas ordenada de `RepositorioArtistas` pedido.
 */
Artista *repositorio_artistas_get_artistaOrdenado_por_indice(RepositorioArtistas *repo, int indice);


/**
 * @brief Retorna o tamanho da lista ordenada de artistas.
 * 
 * @param repo Apontador para o `RepositorioArtistas`.
 * @return O tamanho da lista de artistas ordenada de `RepositorioArtistas` .
 */
int repositorio_artistas_get_artistasOrdenados_tamanho (RepositorioArtistas *repo);

/**
 * @brief Põe o parâmetro de lista ordenada a false.
 * 
 * @param repo Apontador para o `RepositorioArtistas`.
 * @return O tamanho da lista de artistas ordenada de `RepositorioArtistas` .
 */
void repositorio_artistas_lista_desordenada (RepositorioArtistas *repo);

#endif
