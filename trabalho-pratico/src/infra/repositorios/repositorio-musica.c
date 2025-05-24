#include "repositorio-musicas.h"

struct RepositorioMusicas
{
    GHashTable *hashTableMusicas;
};

RepositorioMusicas *repositorio_musicas_novo()
{
    RepositorioMusicas *repo = g_new(RepositorioMusicas, 1);
    repo->hashTableMusicas = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, musica_destroi);
    return repo;
}

void repositorio_musicas_destroi(RepositorioMusicas *repo)
{
    g_hash_table_destroy(repo->hashTableMusicas);
    g_free(repo);
}

void repositorio_musicas_adicionar(RepositorioMusicas *repo, Musica *musica)
{
    int id = musica_get_idMusica(musica);
    g_hash_table_insert(repo->hashTableMusicas, GINT_TO_POINTER(id), musica);
}

Musica *repositorio_musicas_get_musica_por_id(RepositorioMusicas *repo, int *id)
{
    return (Musica *)g_hash_table_lookup(repo->hashTableMusicas, GINT_TO_POINTER(*id));
}
