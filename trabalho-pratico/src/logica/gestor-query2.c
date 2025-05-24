#include "gestor-query2.h"

void gestor_query2_adiciona_artistas(ResultadoQuery* resultado, GArray * artistasOrdenadosFiltrada) {
    for (guint i = 0; i < artistasOrdenadosFiltrada->len; i++) {
        Artista* artista = g_array_index(artistasOrdenadosFiltrada, Artista*, i);

        const char *nome = artista_get_nomeArtista(artista);
        char *tipo = artista_tipo_para_string(artista_get_tipoArtista(artista));
        int duracaoDiscografiaEmSegundos = artista_get_duracaoDiscorgrafiaEmSegundos(artista);
        char *duracaoStr = utils_segundos_para_string(duracaoDiscografiaEmSegundos);
        const char *nacionalidade = artista_get_nacionalidadeArtista(artista);

        Linha *linha = resultado_query_linha_novo();
        resultado_query_linha_adiciona_celula(linha, nome);
        resultado_query_linha_adiciona_celula(linha, tipo);
        resultado_query_linha_adiciona_celula(linha, duracaoStr);
        resultado_query_linha_adiciona_celula(linha, nacionalidade);

        resultado_query_adiciona_linha(resultado, linha);

        g_free(duracaoStr);

    }
}

ResultadoQuery* gestor_query2_executa(Comando *comando, Dados *dados) {

    char *NStr = comando_get_argumento_por_indice(comando, 0);
    if (NStr == NULL) { 
        return NULL;
    }
    int N = atoi(NStr);
    g_free(NStr);
    char *filtroPais = comando_get_argumento_por_indice(comando, 1);

    if (N < 0) {
        if (filtroPais != NULL) g_free(filtroPais);
        return NULL;
    }

    GArray *artistasOrdenadosFiltrada = g_array_new(FALSE, FALSE, sizeof(Artista*));
    RepositorioArtistas *repositorioArtistas = dados_get_repositorioArtistas(dados);

    if (filtroPais == NULL) {
        for (int i = 0; i < N && i < repositorio_artistas_get_artistasOrdenados_tamanho (repositorioArtistas); i++) {
            Artista *artista = repositorio_artistas_get_artistaOrdenado_por_indice(repositorioArtistas, i);
            g_array_append_val(artistasOrdenadosFiltrada, artista);
        }
    } else {
        int nArtistas = 0;
        for (int i = 0; i < repositorio_artistas_get_artistasOrdenados_tamanho (repositorioArtistas) && nArtistas < N; i++) {
            Artista *artista = repositorio_artistas_get_artistaOrdenado_por_indice(repositorioArtistas, i);
            const char *nacionalidadeArtista = artista_get_nacionalidadeArtista(artista);
            if (strcmp(nacionalidadeArtista, filtroPais) == 0) {
                g_array_append_val(artistasOrdenadosFiltrada, artista);
                nArtistas++;
            }
        }
    }

    ResultadoQuery *resultado = resultado_query_novo();
    gestor_query2_adiciona_artistas(resultado, artistasOrdenadosFiltrada);

    g_free(filtroPais);
    g_array_free(artistasOrdenadosFiltrada, TRUE);

    return resultado;
}
