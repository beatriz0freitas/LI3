#include "gestor-de-programa.h"

struct GestorDePrograma
{
    GestorDeQueries *gestorQueries;
    Estatisticas *estatisticas;
    gboolean modoEconomiaMemoria;
};

GestorDePrograma *gestor_programa_novo(Estatisticas *estatisticas, gboolean modoEconomiaMemoria)
{
    GestorDePrograma *gestor = g_new(GestorDePrograma, 1);
    gestor->gestorQueries = gestor_queries_novo(estatisticas);
    gestor->estatisticas = estatisticas;
    gestor->modoEconomiaMemoria = modoEconomiaMemoria;
    return gestor;
}

void inspecionaInPutParaEconomiaDeMemoria(gboolean modoEconomiaMemoria, char *caminhoFicheiroInput, GHashTable **historicosNecessarios, GHashTable **utilizadoresNecessarios)
{
    if (!modoEconomiaMemoria)
        return;

    Input *inputPreCarregamento = input_novo(caminhoFicheiroInput);
    *historicosNecessarios = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, NULL);
    *utilizadoresNecessarios = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, NULL);
    // carrega todos os comandos
    char *linha = NULL;
    while (input_proxima_linha(inputPreCarregamento, &linha))
    {
        Comando *comando = comando_constroi_de_linha(linha);
        if (comando_get_numero_query(comando) == 6)
        {
            char *userrIdStr = comando_get_argumento_por_indice(comando, 0);
            int idUtilizador = atoi(userrIdStr + 1);
            g_hash_table_insert(*historicosNecessarios, GINT_TO_POINTER(idUtilizador), NULL);
            g_free(userrIdStr);
        }
        if (comando_get_numero_query(comando) == 1)
        {
            char *IdStr = comando_get_argumento_por_indice(comando, 0);
            if (IdStr[0] == 'U')
            {
                int idUtilizador = atoi(IdStr + 1);
                g_hash_table_insert(*utilizadoresNecessarios, GINT_TO_POINTER(idUtilizador), NULL);
            }
            g_free(IdStr);
        }
        comando_destroi(comando);
        g_free(linha);
    }
    
    g_free(linha);
    input_destroi(inputPreCarregamento);
}

void gestor_programa_executa(GestorDePrograma *gestorPrograma, char *pastaDados, char *caminhoFicheiroInput)
{

    GHashTable *historicosNecessarios = NULL;
    GHashTable *utilizadoresNecessarios = NULL;

    inspecionaInPutParaEconomiaDeMemoria(gestorPrograma->modoEconomiaMemoria, caminhoFicheiroInput, &historicosNecessarios, &utilizadoresNecessarios);

    Estatisticas *estatisticas = gestorPrograma->estatisticas;

    // Cria e carrega a estrutura de dados
    Dados *dados = dados_novo(historicosNecessarios, utilizadoresNecessarios);
    dados = dados_carregar(estatisticas, pastaDados, dados);
    if (dados == NULL)
    {
        perror("Erro ao carregar os dados");
        dados_destroi(dados);
        return;
    }

    // Abre o ficheiro de input
    Input *input = input_novo(caminhoFicheiroInput);

    // Processa os comandos do ficheiro de input linha a linha
    char *linha = NULL;
    int numeroComando = 0;
    while (input_proxima_linha(input, &linha))
    {
        numeroComando++;
        Comando *comando = comando_constroi_de_linha(linha);
        comando_set_numero_comando(comando, numeroComando);
        const char * separador = comando_get_separador(comando);
        ResultadoQuery *resultado = gestor_queries_executa(gestorPrograma->gestorQueries, comando, dados);
        output_print(resultado, separador, resultado_query_toString, numeroComando);

        if (resultado != NULL) {
        resultado_query_destroi(resultado);
        }

        comando_destroi(comando);
        g_free(linha);
    }
    if (linha)
    {
        g_free(linha);
    }

    dados_destroi(dados);
    input_destroi(input);
    gestor_de_quarks_destroi();
}

void gestor_programa_destroi(GestorDePrograma *gestorPrograma)
{
    gestor_queries_destroi(gestorPrograma->gestorQueries);
    g_free(gestorPrograma);
}

GestorDeQueries *gestor_programa_get_gestor_queries(GestorDePrograma *gestorDePrograma)
{
    return gestorDePrograma->gestorQueries;
}