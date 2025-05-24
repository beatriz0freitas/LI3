#ifndef REPOSITORIO_ALBUM_H
#define REPOSITORIO_ALBUM_H

#include "album.h"

/**
 * @file repositorio-album.h
 * @brief Interface para o repositório de álbuns.
 * 
 * Este módulo define a estrutura e as funções para gerir um repositório de álbuns, 
 * permitindo a criação, destruição, adição e recuperação de álbuns.
 */

/**
 * @brief Estrutura que representa o repositório de álbuns.
 * 
 * A implementação completa está no arquivo de origem, sendo que esta estrutura
 * encapsula os detalhes internos.
 */
typedef struct RepositorioAlbuns RepositorioAlbuns;

/**
 * @brief Cria um novo repositório de álbuns.
 * 
 * Aloca e inicializa uma instância de `RepositorioAlbuns`, que contém
 * uma tabela hash para armazenar os álbuns.
 * 
 * @return Apontador para a nova instância de `RepositorioAlbuns`.
 */
RepositorioAlbuns *repositorio_albuns_novo();

/**
 * @brief Destroi um repositório de álbuns.
 * 
 * Liberta todos os recursos associados a um repositório.
 * 
 * @param repo Apontador para o repositório a ser destruído.
 */
void repositorio_albuns_destroi(RepositorioAlbuns *repo);

/**
 * @brief Adiciona um álbum ao repositório.
 * 
 * Insere um álbum no repositório usando o ID do álbum como chave.
 * Se um álbum com o mesmo ID já existir, ele será substituído.
 * 
 * @param repo Apontador para o repositório onde o álbum será adicionado.
 * @param album Apontador para o álbum a ser adicionado.
 */
void repositorio_albuns_adicionar(RepositorioAlbuns *repo, Album *album);

/**
 * @brief Recupera um álbum pelo ID.
 * 
 * 
 * @param repo Apontador para o repositório onde a busca será realizada.
 * @param id ID do álbum a ser procurado.
 * 
 * @return Apontador para o álbum encontrado, ou NULL se o álbum não existir no repositório.
 */
Album *repositorio_albuns_get_album_por_id(RepositorioAlbuns *repo, int id);

#endif // REPOSITORIO_ALBUM_H
