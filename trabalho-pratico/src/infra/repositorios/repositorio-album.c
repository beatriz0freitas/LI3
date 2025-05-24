#include "repositorio-album.h"

struct RepositorioAlbuns
{
    GHashTable *hashTableAlbuns;
};

RepositorioAlbuns *repositorio_albuns_novo()
{
    RepositorioAlbuns *repo = g_new(RepositorioAlbuns, 1);
    repo->hashTableAlbuns = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, album_destroi);
    return repo;
}

void repositorio_albuns_destroi(RepositorioAlbuns *repo)
{
    g_hash_table_destroy(repo->hashTableAlbuns);
    g_free(repo);
}

void repositorio_albuns_adicionar(RepositorioAlbuns *repo, Album *album)
{
    int id = album_get_idAlbum(album);
    g_hash_table_insert(repo->hashTableAlbuns, GINT_TO_POINTER(id), album);
}

Album *repositorio_albuns_get_album_por_id(RepositorioAlbuns *repo, int id)
{
    return (Album *)g_hash_table_lookup(repo->hashTableAlbuns, GINT_TO_POINTER(id));
}
