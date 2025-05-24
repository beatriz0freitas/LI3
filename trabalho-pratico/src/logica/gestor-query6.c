#include "gestor-query6.h"

#define IDADE_MAXIMA 120

typedef struct {
    int idArtista;
    int tempoTotalAudicao;
    GHashTable *musicasOuvidas;
} DadosArtista;

DadosArtista *dadosArtista_novo(int idArtista)
{
    DadosArtista *dadosArtista = g_new(DadosArtista, 1);
    dadosArtista->idArtista = idArtista;
    dadosArtista->tempoTotalAudicao = 0;
    dadosArtista->musicasOuvidas = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, utils_g_slice_free_int);

    return dadosArtista;
}

//comecamos por tentar resolver como qualuqer outra query
//ir ao parser e carregar o resumos anuais de cada utilizador(estrutura auxiliar criada) para evitar calvulos repetidos
//percebemos que aumentava imenso a memoria (hashtable que ocupava 200MB para dados auxiliares - a meio estava a 1000MB - memoria atingia o limite - nao passava nos testes)

//decidimos entao fazer uma abordagem diferente
//guardar o historico por indice de utilizador por ano -
//indice com 2 hashtables, utilizador e hashtable de anos e depois essa e HashTable ano tem uma lista com o historico daquele utilizador naquele ano

//mais eficiente fazer os calculos na propria querie porque tinhamos de calcular um numero reduzido de historicos em vez de todos e guardá-los.

//query vai ao rep historicos e passa-os a uma serie de funcoes auxiliares que calculam os dados necessarios para os resumos anuais

char *gestor_query6_hora_mais_ouvida(GArray *historicos)
{

    int audicaoPorHoras[24];
    memset(audicaoPorHoras, 0, sizeof(audicaoPorHoras));

    for (int i = 0; i < historicos->len; i++)
    {

        Historico *historico = g_array_index(historicos, Historico *, i);

        short horaOuvida = historico_get_horaMusicaOuvida(historico);
        short tempoAudicao = historico_get_duracaoAudicaoMusicaSegundos(historico);

        audicaoPorHoras[horaOuvida] += tempoAudicao;
    }

    // TODO: ver se nao seria mais eficiente manter o track de hora mais ouvida enquanto se adiciona no array
    int horaMaisOuvida = -1;
    int maiorAudicao = 0;
    for (int i = 0; i < 24; i++)
    {
        int tempoAudicao = audicaoPorHoras[i];
        // nao precissa do desempate de hora mais cedo porque isto vai da menor para a maior
        if (tempoAudicao > maiorAudicao)
        {
            maiorAudicao = tempoAudicao;
            horaMaisOuvida = i;
        }
    }

    char *horaMaisOuvidaStr = g_strdup_printf("%02d", horaMaisOuvida);

    return horaMaisOuvidaStr;
}

char *gestor_query6_album_mais_ouvido(GArray *historicos, Dados *dados)
{

    GHashTable *tempoPorAlbum = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, utils_g_slice_free_int);

    for (int i = 0; i < historicos->len; i++)
    {
        Historico *historico = g_array_index(historicos, Historico *, i);
        short tempoAudicao = historico_get_duracaoAudicaoMusicaSegundos(historico);
        int idMusica = historico_get_idMusica(historico);

        RepositorioMusicas *repositorioMusicas = dados_get_repositorioMusicas(dados);
        Musica *musica = repositorio_musicas_get_musica_por_id(repositorioMusicas, &idMusica);
        int idAlbum = musica_get_idAlbum(musica);

        int *tempoAtual = g_hash_table_lookup(tempoPorAlbum, GINT_TO_POINTER(idAlbum));
        if (!tempoAtual)
        {
            int *novoTempo = g_slice_new(int);
            *novoTempo = tempoAudicao;
            g_hash_table_insert(tempoPorAlbum, GINT_TO_POINTER(idAlbum), novoTempo);
        }
        else
        {
            *tempoAtual += tempoAudicao;
        }
    }

    // talvez ir guardando o mais ouvido enquanto se adiciona

    GHashTableIter iter;
    gpointer key, value;
    int idAlbumMaisOuvido = -1;
    int maiorTempoAudicao = 0;

    g_hash_table_iter_init(&iter, tempoPorAlbum);
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        int idAlbum = GPOINTER_TO_INT(key);
        int tempoAudicao = *(int *)value;
        if (tempoAudicao > maiorTempoAudicao)
        {
            maiorTempoAudicao = tempoAudicao;
            idAlbumMaisOuvido = idAlbum;
        }
    }

    g_hash_table_destroy(tempoPorAlbum);

    return album_id_para_string(idAlbumMaisOuvido);
}

//hashtable que guarda os dados de todos os artistas: id, tempo total de audicao e hashTable musicas ouvidas
//para cada historico, adiciona o tempo de audicao a cada artista e incrementa o contador de musicas ouvidas
GHashTable *gestor_query6_artistas_musicas_tempo(GArray *historicos, Dados *dados)
{

    GHashTable *artistasDados = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, (GDestroyNotify)g_free);

    for (int i = 0; i < historicos->len; i++)
    {
        Historico *historico = g_array_index(historicos, Historico *, i);
        int idMusica = historico_get_idMusica(historico);
        short tempoAudicao = historico_get_duracaoAudicaoMusicaSegundos(historico);

        RepositorioMusicas *repositorioMusicas = dados_get_repositorioMusicas(dados);
        Musica *musica = repositorio_musicas_get_musica_por_id(repositorioMusicas, &idMusica);
        int numeroArtistas = musica_get_quantidadeDeArtistas(musica);

        for (int j = 0; j < numeroArtistas; j++)
        {
            int idArtista = musica_get_idArtistaPorIndice(musica, j);

            DadosArtista *dadosArtista = g_hash_table_lookup(artistasDados, GINT_TO_POINTER(idArtista));
            if (!dadosArtista)
            {
                dadosArtista = dadosArtista_novo(idArtista);
                g_hash_table_insert(artistasDados, GINT_TO_POINTER(idArtista), dadosArtista);
            }

            dadosArtista->tempoTotalAudicao += tempoAudicao;

            int *contagemMusica = g_hash_table_lookup(dadosArtista->musicasOuvidas, GINT_TO_POINTER(idMusica));
            if (!contagemMusica)
            {
                int *novaContagem = g_slice_new(int);
                *novaContagem = 1;
                g_hash_table_insert(dadosArtista->musicasOuvidas, GINT_TO_POINTER(idMusica), novaContagem);
            }
            else
            {
                (*contagemMusica)++;
            }
        }
    }

    return artistasDados;
}

//usa a subtracao para ordenar no sort
int comparar_dados_artista(const void *a, const void *b)
{
    const DadosArtista *artistaA = *(const DadosArtista **)a;
    const DadosArtista *artistaB = *(const DadosArtista **)b;

    if (artistaB->tempoTotalAudicao != artistaA->tempoTotalAudicao)
    {
        return artistaB->tempoTotalAudicao - artistaA->tempoTotalAudicao;
    }

    return artistaA->idArtista - artistaB->idArtista;
}

GArray *gestor_query6_artistas_ordenados(GHashTable *ArtistasDados)
{

    GArray *artistasArray = g_array_new(FALSE, FALSE, sizeof(DadosArtista *));

    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, ArtistasDados);
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        DadosArtista *dadosArtista = (DadosArtista *)value;
        g_array_append_val(artistasArray, dadosArtista);
    }

    g_array_sort(artistasArray, comparar_dados_artista);

    return artistasArray;
}

//como ordenando com sort é so ir buscar o id do primeiro
char *gestor_query6_artista_mais_ouvido(GArray *artistasOrdenados)
{
    DadosArtista *artistaMaisOuvido = g_array_index(artistasOrdenados, DadosArtista *, 0);
    int idArtista = artistaMaisOuvido->idArtista;

    char *idArtistaStr = artista_id_para_string(idArtista);

    return idArtistaStr;
}

char *gestor_query6_tempoTotalAudicao(GArray *historicos)
{
    int tempoTotal = 0;

    for (int i = 0; i < historicos->len; i++)
    {
        Historico *historico = g_array_index(historicos, Historico *, i);
        tempoTotal += historico_get_duracaoAudicaoMusicaSegundos(historico);
    }

    char *tempoTotalStr = utils_segundos_para_string(tempoTotal);
    return tempoTotalStr;
}

//meter na hsah table e ver tamanho
char *gestor_query6_numeroMusicasTotal(GArray *historicos)
{
    GHashTable *musicasOuvidas = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, NULL);

    for (int i = 0; i < historicos->len; i++)
    {
        Historico *historico = g_array_index(historicos, Historico *, i);
        int idMusica = historico_get_idMusica(historico);

        if (!g_hash_table_contains(musicasOuvidas, GINT_TO_POINTER(idMusica)))
        {
            g_hash_table_insert(musicasOuvidas, GINT_TO_POINTER(idMusica), GINT_TO_POINTER(1));
        }
    }

    int numeroTotalMusicas = g_hash_table_size(musicasOuvidas);
    g_hash_table_destroy(musicasOuvidas);

    char *numeroTotalMusicasStr = g_strdup_printf("%d", numeroTotalMusicas);
    return numeroTotalMusicasStr;
}

//hash table com os generos e o tempo total de audicao
char *gestor_query6_generoMaisOuvido(GArray *historicos, Dados *dados)
{

    GHashTable *tempoPorGenero = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (GDestroyNotify)utils_g_slice_free_int);

    RepositorioMusicas *repositorioMusicas = dados_get_repositorioMusicas(dados);

    for (int i = 0; i < historicos->len; i++)
    {

        Historico *historico = g_array_index(historicos, Historico *, i);
        short tempoAudicao = historico_get_duracaoAudicaoMusicaSegundos(historico);
        int idMusica = historico_get_idMusica(historico);

        Musica *musica = repositorio_musicas_get_musica_por_id(repositorioMusicas, &idMusica);
        const char *genero = musica_get_generoMusica(musica);

        int *tempoAtual = g_hash_table_lookup(tempoPorGenero, genero);
        if (!tempoAtual)
        {
            int *novoTempo = g_slice_new(int);
            *novoTempo = tempoAudicao;
            g_hash_table_insert(tempoPorGenero, g_strdup(genero), novoTempo);
        }
        else
        {
            *tempoAtual += tempoAudicao;
        }
    }

    GHashTableIter iter;
    gpointer key, value;
    char *generoMaisOuvido = NULL;
    int maiorTempoAudicao = 0;

    g_hash_table_iter_init(&iter, tempoPorGenero);
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        char *genero = (char *)key;
        int tempoAudicao = *(int *)value;

        if (tempoAudicao > maiorTempoAudicao)
        {
            maiorTempoAudicao = tempoAudicao;
            generoMaisOuvido = genero;
        }
        else if (tempoAudicao == maiorTempoAudicao)
        {
            if (g_strcmp0(genero, generoMaisOuvido) < 0)
            {
                generoMaisOuvido = genero;
            }
        }
    }
    char *generoMaisOuvidoStr = g_strdup(generoMaisOuvido);
    g_hash_table_destroy(tempoPorGenero);

    return generoMaisOuvidoStr;
}


//hash table com os dias e o numero de musicas ouvidas
//descartamos o ano (todos os historicos sao do mesmo ano) e criamos uma chave difenrente para cada dia
char *gestor_query6_diaMaisOuvido(GArray *historicos)
{

    GHashTable *diasAudicao = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, utils_g_slice_free_int);

    Historico *primeiroHistorico = g_array_index(historicos, Historico *, 0);
    GDate *dataPrimeiroHistorico = historico_get_dataMusicaOuvida(primeiroHistorico);
    int ano = g_date_get_year(dataPrimeiroHistorico);

    for (int i = 0; i < historicos->len; i++)
    {
        Historico *historico = g_array_index(historicos, Historico *, i);
        GDate *dataMusica = historico_get_dataMusicaOuvida(historico);

        int mes = g_date_get_month(dataMusica);
        int dia = g_date_get_day(dataMusica);

        int mesDiaInt = mes * 100 + dia; // Cria chave no formato MMDD

        int *contagem = g_hash_table_lookup(diasAudicao, GINT_TO_POINTER(mesDiaInt));
        if (!contagem)
        {
            int *novaContagem = g_slice_new(int);
            *novaContagem = 1;
            g_hash_table_insert(diasAudicao, GINT_TO_POINTER(mesDiaInt), novaContagem);
        }
        else
        {
            (*contagem)++;
        }
    }

    GHashTableIter iter;
    gpointer chave, valor;
    int diaMaisOuvidoChave = 0;
    int maxMusicas = 0;

    g_hash_table_iter_init(&iter, diasAudicao);
    while (g_hash_table_iter_next(&iter, &chave, &valor))
    {
        int mesDiaInt = GPOINTER_TO_INT(chave);
        int numeroMusicas = *(int *)valor;

        if (numeroMusicas > maxMusicas)
        {
            maxMusicas = numeroMusicas;
            diaMaisOuvidoChave = mesDiaInt;
        }
        else if (numeroMusicas == maxMusicas)
        {
            if (mesDiaInt > diaMaisOuvidoChave)
            {
                diaMaisOuvidoChave = mesDiaInt;
            }
        }
    }

    int mesMaisOuvido = diaMaisOuvidoChave / 100;
    int diaMaisOuvido = diaMaisOuvidoChave % 100;

    char *diaMaisOuvidoStr = g_strdup_printf("%04d/%02d/%02d", ano, mesMaisOuvido, diaMaisOuvido);

    g_hash_table_destroy(diasAudicao);

    return diaMaisOuvidoStr;
}

ResultadoQuery *gestor_query6_executa(Comando *comando, Dados *dados)
{
    char *idUtilizadorStr = comando_get_argumento_por_indice(comando, 0);
    if (idUtilizadorStr == NULL) { 
        return NULL;
    }
    int idUtilizador = atoi(idUtilizadorStr+1);
    g_free(idUtilizadorStr);
    char *anoStr =comando_get_argumento_por_indice(comando,1);
    if (anoStr == NULL) { 
        return NULL;
    }
    int ano = atoi(anoStr);
    g_free(anoStr);

    char *numeroArtistasMaisOuvidosStr = comando_get_argumento_por_indice(comando, 2);
    int numeroArtistasMaisOuvidos = 0;
    

    if (numeroArtistasMaisOuvidosStr != NULL){
    numeroArtistasMaisOuvidos = atoi(numeroArtistasMaisOuvidosStr);
    }
    g_free(numeroArtistasMaisOuvidosStr);

    ResultadoQuery *resultado = resultado_query_novo();

    GArray *historicos = repositorio_historicos_get_por_utilizador_e_ano(dados_get_repositorioHistoricos(dados), idUtilizador, ano);

    if (historicos)
    {
        Linha *linha = resultado_query_linha_novo();
        GHashTable *artistasDados = gestor_query6_artistas_musicas_tempo(historicos, dados);
        GArray *artistasOrdenados = gestor_query6_artistas_ordenados(artistasDados);

        char *tempoTotalAudicaoStr = gestor_query6_tempoTotalAudicao(historicos);
        char *numeroMusicasTotalStr = gestor_query6_numeroMusicasTotal(historicos);
        char *artistaMaisOuvidoStr = gestor_query6_artista_mais_ouvido(artistasOrdenados);
        char *idAlbumMaisOuvidoStr = gestor_query6_album_mais_ouvido(historicos, dados);
        char *horaMaisOuvidaStr = gestor_query6_hora_mais_ouvida(historicos);
        char *generoMaisOuvidoStr = gestor_query6_generoMaisOuvido(historicos, dados);
        char *diaMaisOuvidoStr = gestor_query6_diaMaisOuvido(historicos);

        resultado_query_linha_adiciona_celula(linha, tempoTotalAudicaoStr);
        resultado_query_linha_adiciona_celula(linha, numeroMusicasTotalStr);
        resultado_query_linha_adiciona_celula(linha, artistaMaisOuvidoStr);
        resultado_query_linha_adiciona_celula(linha, diaMaisOuvidoStr);
        resultado_query_linha_adiciona_celula(linha, generoMaisOuvidoStr);
        resultado_query_linha_adiciona_celula(linha, idAlbumMaisOuvidoStr);
        resultado_query_linha_adiciona_celula(linha, horaMaisOuvidaStr);

        resultado_query_adiciona_linha(resultado, linha);

        if (numeroArtistasMaisOuvidos > 0)
        {

            for (int i = 0; i < numeroArtistasMaisOuvidos && i < artistasOrdenados->len; i++)
            {
                DadosArtista *artista = g_array_index(artistasOrdenados, DadosArtista *, i);
                char *idArtistaStr = artista_id_para_string(artista->idArtista);
                char *numeroMusicasStr = g_strdup_printf("%d", g_hash_table_size(artista->musicasOuvidas));
                char *tempoAudicaoStr = utils_segundos_para_string(artista->tempoTotalAudicao);

                Linha *linha = resultado_query_linha_novo();
                resultado_query_linha_adiciona_celula(linha, idArtistaStr);
                resultado_query_linha_adiciona_celula(linha, numeroMusicasStr);
                resultado_query_linha_adiciona_celula(linha, tempoAudicaoStr);

                resultado_query_adiciona_linha(resultado, linha);
            }
        }
    }
    return resultado;
}
