
#include "repositorio-utilizadores.h"

struct RepositorioUtilizadores
{
    GHashTable *hashTableUtilizadores;
    //estruturas auxiliares para query5
    GHashTable *indiceLinhasUtilizador;
    char **ordemLinhasUtilizadores;
    int proximoIndiceLinha;
};

RepositorioUtilizadores *repositorio_utilizadores_novo()
{
    RepositorioUtilizadores *repo = g_new(RepositorioUtilizadores, 1);
    repo->hashTableUtilizadores = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, utilizador_destroi);
    repo->indiceLinhasUtilizador = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, (GDestroyNotify)utils_g_slice_free_int);
    repo->ordemLinhasUtilizadores = NULL;
    repo->proximoIndiceLinha = 0;
    return repo;
}

void repositorio_utilizadores_destroi(RepositorioUtilizadores *repo)
{
    g_hash_table_destroy(repo->hashTableUtilizadores);
    if (repo->ordemLinhasUtilizadores)
    {
        for (int i = 0; i < repo->proximoIndiceLinha; i++)
        {
            free(repo->ordemLinhasUtilizadores[i]);
        }
        free(repo->ordemLinhasUtilizadores);
    }
    g_hash_table_destroy(repo->indiceLinhasUtilizador);
    g_free(repo);
}

void repositorio_utilizadores_adicionar(RepositorioUtilizadores *repo, Utilizador *utilizador, GHashTable *utilizadoresNecessarios)
{
    int id = utilizador_get_idDoUtilizador(utilizador);
    int *indiceLinhaUtilizador = g_slice_new(int);
    *indiceLinhaUtilizador = repo->proximoIndiceLinha;
    g_hash_table_insert(repo->indiceLinhasUtilizador, GINT_TO_POINTER(id), indiceLinhaUtilizador);
    repo->proximoIndiceLinha++;

    if (utilizadoresNecessarios == NULL || g_hash_table_contains(utilizadoresNecessarios, GINT_TO_POINTER(id)))
    {
        g_hash_table_insert(repo->hashTableUtilizadores, GINT_TO_POINTER(id), utilizador);
    }else {
        utilizador_destroi(utilizador);
    }
}

Utilizador *repositorio_utilizadores_get(RepositorioUtilizadores *repo, int id) //encapsulamento
{
    return (Utilizador *)g_hash_table_lookup(repo->hashTableUtilizadores, GINT_TO_POINTER(id));
}

int repositorio_utilizadores_get_tamanho(RepositorioUtilizadores *repo)
{
    GHashTable *hashtableutilizadores = repo->hashTableUtilizadores;
    return g_hash_table_size(hashtableutilizadores);
}

gpointer repositorio_utilizadores_get_indice_linha(RepositorioUtilizadores *repo, int idUtilizador){
    return g_hash_table_lookup(repo->indiceLinhasUtilizador, GINT_TO_POINTER(idUtilizador));
}

void repositorio_utilizadores_adiciona_utilizador_indice_linha(RepositorioUtilizadores *repo, int idUtilizador){
        int *indiceLinhaUtilizador = g_slice_new(int);
        *indiceLinhaUtilizador = repo->proximoIndiceLinha;
        g_hash_table_insert(repo->indiceLinhasUtilizador, GINT_TO_POINTER(idUtilizador), indiceLinhaUtilizador);
        repo->proximoIndiceLinha++;
}

int repositorio_utilizadores_get_proximoIndiceLinha(RepositorioUtilizadores *repo)
{
    return repo->proximoIndiceLinha;
}

void repositorio_utilizadores_cria_ordemLinhasUtilizadores(RepositorioUtilizadores *repo)
{
    int numeroUtilizadores = g_hash_table_size(repo->indiceLinhasUtilizador);
    repo->ordemLinhasUtilizadores = (char **)malloc(numeroUtilizadores * sizeof(char *));

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, repo->indiceLinhasUtilizador);

    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        int idUtilizador = GPOINTER_TO_INT(key);
        int *indicePtr = (int *)value;
        int indice = *indicePtr;
        char *idString = utilizador_id_para_string(idUtilizador);
        repo->ordemLinhasUtilizadores[indice] = idString;
    }

}

char **repositorio_utilizadores_get_ordemLinhasUtilizadores(RepositorioUtilizadores *repo)
{
    return repo->ordemLinhasUtilizadores;
}

int repositorio_utilizadores_get_tamanho_indice (RepositorioUtilizadores *repo){
    return repo->proximoIndiceLinha;
}

gboolean repositorio_utilizadores_existe (RepositorioUtilizadores *repo, int id){
    return g_hash_table_contains(repo->indiceLinhasUtilizador, GINT_TO_POINTER(id));
}