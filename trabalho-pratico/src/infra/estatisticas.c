#include "estatisticas.h"


struct Estatisticas {
    GHashTable *estatisticas;
};

struct EstatisticasItem {
    int numeroDeExecucoes;
    clock_t ultimoInicio;
    double tempoDeExecucao;
};

Estatisticas *estatisticas_novo()
{
    Estatisticas *stats = g_new0(Estatisticas, 1);
    stats->estatisticas = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);
    return stats;
}

void estatisticas_destroi(Estatisticas *estatisticas)
{
    if (!estatisticas) return;
    g_hash_table_destroy(estatisticas->estatisticas);
    g_free(estatisticas);
}

void estatisticas_inicia_contagem(Estatisticas *estatisticas, const char *item)
{
    if (!estatisticas) return;
    EstatisticasItem *estatisticasItem = g_hash_table_lookup(estatisticas->estatisticas, item);
    if (!estatisticasItem)
    {
        estatisticasItem = g_new0(EstatisticasItem, 1);
        g_hash_table_insert(estatisticas->estatisticas, g_strdup(item), estatisticasItem);
    }
    estatisticasItem->numeroDeExecucoes++;
    estatisticasItem->ultimoInicio = clock();
}

void estatisticas_termina_contagem(Estatisticas *estatisticas, const char *item)
{
    if (!estatisticas) return;
    EstatisticasItem *estatisticasItem = g_hash_table_lookup(estatisticas->estatisticas, item);
    if (!estatisticasItem) return;
    double elapsed = (double)(clock() - estatisticasItem->ultimoInicio) / CLOCKS_PER_SEC;
    estatisticasItem->tempoDeExecucao += elapsed;
}

EstatisticasItem *estatisticas_get_item(Estatisticas *estatisticas, const char *item)
{
    EstatisticasItem *estatisticasItem = g_hash_table_lookup(estatisticas->estatisticas, item);
    return estatisticasItem;
}

int estatisticas_item_get_numero_de_execucoes(EstatisticasItem *estatisticasItem)
{
    return estatisticasItem->numeroDeExecucoes;
}

double estatisticas_item_get_tempo_de_execucao(EstatisticasItem *estatisticasItem)
{
    return estatisticasItem->tempoDeExecucao;
}

char *estatisticas_to_string(Estatisticas *estatisticas)
{

    GString *str = g_string_new(NULL);


    g_string_append_printf(
        str,
        "%-25s | %-20s | %s\n",  // define larguras de colunas ajustáveis
        "Item", 
        "Numero de execuções", 
        "Tempo de execução"
    );

    GList *keys = g_hash_table_get_keys(estatisticas->estatisticas);

    for (GList *l = keys; l != NULL; l = l->next) {
        const char *itemName = (const char *)l->data;
        EstatisticasItem *estatisticasItem = g_hash_table_lookup(
            estatisticas->estatisticas, 
            itemName
        );

        if (estatisticasItem) {
            g_string_append_printf(
                str,
                "%-25s | %20d | %20.6f\n", 
                itemName,
                estatisticasItem->numeroDeExecucoes,
                estatisticasItem->tempoDeExecucao
            );
        }
    }
    g_list_free(keys);
    return g_string_free(str, FALSE);
}