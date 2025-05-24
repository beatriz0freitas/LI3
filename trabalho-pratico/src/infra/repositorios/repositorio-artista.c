#include "repositorio-artistas.h"

struct RepositorioArtistas
{
    GHashTable *hashTableArtistas;
    // estruturas auxiliares para query 2
    GArray *listaArtistasAuxiliar;
    gboolean listaArtistasAuxiliarOrdenada;

};

RepositorioArtistas *repositorio_artistas_novo()
{
    RepositorioArtistas *repo = g_new(RepositorioArtistas, 1);
    repo->hashTableArtistas = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, artista_destroi);
    repo->listaArtistasAuxiliar = g_array_new(FALSE, FALSE, sizeof(Artista *));
    repo->listaArtistasAuxiliarOrdenada = FALSE;
    return repo;
}

void repositorio_artistas_destroi(RepositorioArtistas *repo)
{
    g_hash_table_destroy(repo->hashTableArtistas);
    g_array_free(repo->listaArtistasAuxiliar, TRUE);
    g_free(repo);
}

void repositorio_artistas_adicionar(RepositorioArtistas *repo, Artista *artista)
{
    int id = artista_get_idArtista(artista);
    g_hash_table_insert(repo->hashTableArtistas, GINT_TO_POINTER(id), artista);
    g_array_append_val(repo->listaArtistasAuxiliar, artista);
    repo->listaArtistasAuxiliarOrdenada = FALSE;
}

Artista *repositorio_artistas_get_artista_por_id(RepositorioArtistas *repo, int id)
{
    return (Artista *)g_hash_table_lookup(repo->hashTableArtistas, GINT_TO_POINTER(id));
}

Artista *repositorio_artistas_get_artistaOrdenado_por_indice(RepositorioArtistas *repo, int indice)
{
    if (!repo->listaArtistasAuxiliarOrdenada)
    {
        g_array_sort(repo->listaArtistasAuxiliar, artista_compara_decrescente);
        repo->listaArtistasAuxiliarOrdenada = TRUE;
    }
    return g_array_index(repo->listaArtistasAuxiliar, Artista *, indice);
}

int repositorio_artistas_get_artistasOrdenados_tamanho (RepositorioArtistas *repo){
    return repo->listaArtistasAuxiliar->len;
}

void repositorio_artistas_lista_desordenada (RepositorioArtistas *repo){
    repo->listaArtistasAuxiliarOrdenada = FALSE;
}

