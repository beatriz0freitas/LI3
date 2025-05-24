#include "gestor-query4.h"

#define IDADE_MAXIMA 120

Linha *gestor_query4_artista_output(Artista *artista, int frequencia)
{
    Linha *linha = resultado_query_linha_novo();  

    char *idArtistaStr = artista_id_para_string(artista_get_idArtista(artista));
    TipoArtista tipo = artista_get_tipoArtista(artista);
    char *tipoStr = artista_tipo_para_string(tipo);
    char *frequenciaStr = g_strdup_printf("%d", frequencia);

    resultado_query_linha_adiciona_celula(linha, idArtistaStr);
    resultado_query_linha_adiciona_celula(linha, tipoStr);
    resultado_query_linha_adiciona_celula(linha, frequenciaStr);
    g_free(idArtistaStr);
    g_free(frequenciaStr);

    return linha;
}

ResultadoQuery *gestor_query4_executa(Comando *comando, Dados *dados)
{
    GHashTable *frequenciaArtistas = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, utils_g_slice_free_int);

    GDate *dataAtual = g_date_new();
    g_date_set_dmy(dataAtual, 9, 9, 2024);

    GDate *dataInicio = g_date_new();
    GDate *dataFim = g_date_new();

    int semanaInicio = 0;
    int semanaFim = 0;

    char *dataInicioStr = comando_get_argumento_por_indice(comando, 0);
    char *dataFimStr = comando_get_argumento_por_indice(comando, 1);

    if (dataInicioStr && dataFimStr)
    {
        int diaInicio, mesInicio, anoInicio;
        int diaFim, mesFim, anoFim;

        sscanf(dataInicioStr, "%d/%d/%d", &anoInicio, &mesInicio, &diaInicio);
        sscanf(dataFimStr, "%d/%d/%d", &anoFim, &mesFim, &diaFim);

        if (g_date_valid_dmy(diaInicio,mesInicio,anoInicio) && g_date_valid_dmy(diaFim,mesFim,anoFim) )
        {
            g_date_set_dmy(dataInicio, diaInicio, mesInicio, anoInicio);
            g_date_set_dmy(dataFim, diaFim, mesFim, anoFim);
            semanaInicio = utils_calcular_numero_semana_juliana(dataInicio);
            semanaFim = utils_calcular_numero_semana_juliana(dataFim);
        }
    }
    else
    {
        semanaFim = utils_calcular_numero_semana_juliana(dataAtual);
        semanaInicio = semanaFim - dados_get_numero_semanas(dados) - 1;
    }

    // Conta o número de vezes que cada artista aparece no top 10
    int idArtistaMaisFrequente = -1;
    int maiorFrequencia = 0;

    for (int semana = semanaInicio; semana <= semanaFim; semana++)
    {
        const MinHeap *heap = dados_get_top10_da_semana(dados, semana);

        if (heap){
        int tamanhoHeap = min_heap_get_tamanho(heap);
        
        for (int i = 0; i < tamanhoHeap; i++)
        {
            ArtistaReproducao *artistaReproducao = (ArtistaReproducao *)min_heap_get_dados_por_indice(heap, i);
            int idArtistaEmAvaliacao = artista_reproducao_get_idArtista(artistaReproducao);
            int *frequencia = g_hash_table_lookup(frequenciaArtistas, GINT_TO_POINTER(idArtistaEmAvaliacao));

            if (!frequencia)
            {
                frequencia = g_slice_new(int);
                *frequencia = 1;
                g_hash_table_insert(frequenciaArtistas, GINT_TO_POINTER(idArtistaEmAvaliacao), frequencia);
            }
            else
            {
                (*frequencia)++;
            }

            // mantem o id do artista que esteve mais vezes no top10
            if((*frequencia) > maiorFrequencia || ((*frequencia) == maiorFrequencia && idArtistaEmAvaliacao < idArtistaMaisFrequente)) {
                idArtistaMaisFrequente = idArtistaEmAvaliacao;
                maiorFrequencia = (*frequencia);
            }
        }
    }
}
    // Prepara o resultado com o artista mais frequente
    ResultadoQuery *resultado = resultado_query_novo();
    if (idArtistaMaisFrequente != -1)
    {
        RepositorioArtistas *repositorioArtistas = dados_get_repositorioArtistas(dados);
        Artista *artista = repositorio_artistas_get_artista_por_id(repositorioArtistas, idArtistaMaisFrequente);

        Linha *linha = gestor_query4_artista_output(artista, maiorFrequencia);

        resultado_query_adiciona_linha(resultado, linha);
    }
    g_hash_table_destroy(frequenciaArtistas);

    g_free(dataInicioStr);
    g_free(dataFimStr);
    g_date_free(dataAtual);
    g_date_free(dataInicio);
    g_date_free(dataFim);

    return resultado;
}

