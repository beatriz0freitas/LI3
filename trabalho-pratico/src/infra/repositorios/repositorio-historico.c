#include "repositorio-historico.h"

struct RepositorioHistoricos
{
    GHashTable *historicoPorUtilizadorAno; // Índice por userID e ano
};

RepositorioHistoricos *repositorio_historicos_novo()
{
    RepositorioHistoricos *repo = g_new(RepositorioHistoricos, 1);
    repo->historicoPorUtilizadorAno = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, (GDestroyNotify)g_hash_table_destroy);
    return repo;
}

void repositorio_historicos_destroi(RepositorioHistoricos *repo)
{
    g_hash_table_destroy(repo->historicoPorUtilizadorAno);
    g_free(repo);
}

void destruir_garray_historicos(gpointer value)
{
    GArray *historicosAno = (GArray *)value;
    for (guint i = 0; i < historicosAno->len; i++)
    {
        Historico *historico = g_array_index(historicosAno, Historico *, i);
        historico_destroi(historico); 
    }
    g_array_unref(historicosAno); 
}

void repositorio_historicos_adicionar(RepositorioHistoricos *repo, Historico *historico)
{

    int userID = historico_get_idUtilizador(historico);
    GDate *dataMusica = historico_get_dataMusicaOuvida(historico);
    int ano = g_date_get_year(dataMusica);

    GHashTable *anosHashTable = g_hash_table_lookup(repo->historicoPorUtilizadorAno, GINT_TO_POINTER(userID));
    if (!anosHashTable)
    {
        anosHashTable = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, (GDestroyNotify)destruir_garray_historicos);
        g_hash_table_insert(repo->historicoPorUtilizadorAno, GINT_TO_POINTER(userID), anosHashTable);
    }

    GArray *historicosAno = g_hash_table_lookup(anosHashTable, GINT_TO_POINTER(ano));
    if (!historicosAno)
    {
        historicosAno = g_array_new(FALSE, FALSE, sizeof(Historico *));
        g_hash_table_insert(anosHashTable, GINT_TO_POINTER(ano), historicosAno);
    }

    g_array_append_val(historicosAno, historico);
}

GArray *repositorio_historicos_get_por_utilizador_e_ano(RepositorioHistoricos *repo, int userID, int ano)
{
    GHashTable *anosHashTable = g_hash_table_lookup(repo->historicoPorUtilizadorAno, GINT_TO_POINTER(userID));
    if (!anosHashTable)
    {
        return NULL;
    }

    return g_hash_table_lookup(anosHashTable, GINT_TO_POINTER(ano));
}
