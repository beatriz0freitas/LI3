#include "repositorio-dados.h"

#define IDADE_MAXIMA 120

struct Dados {
    // Repositorios
    RepositorioArtistas *repositorioArtistas;
    RepositorioMusicas *repositorioMusicas;
    RepositorioUtilizadores *repositorioUtilizadores;
    RepositorioHistoricos *repositorioHistoricos;
    RepositorioAlbuns *repositorioAlbuns;

    // TODO ver se as auxiliares podem ficar melhor noutros locais, como repositorios

    // estrutura auxiliar para query 3
    GHashTable *generosDeMusicaGostadosPorIdade;

    // estruturas auxiliares para query 4
    GHashTable *reproducoesPorArtistaPorSemana;
    GHashTable *top10PorSemana;

    // estruturas auxiliares para query5
    GHashTable *indiceColunasGenero;


    char **ordemColunaUtilizadores;
    int **audicoesUtilizadoresPorGenero;
    int proximoIndiceColuna;

    // estrutura auxiliar para query6
    GHashTable *historicosNecessarios;
    GHashTable *utilizadoresNecessarios;
};

Dados *dados_novo(GHashTable *hashTable_Query6_Utilizadores, GHashTable *utilizadoresNecessarios)
{
    Dados *dados = g_new(Dados, 1);
    // Repositorios
    dados->repositorioArtistas = repositorio_artistas_novo();
    dados->repositorioMusicas = repositorio_musicas_novo();
    dados->repositorioUtilizadores = repositorio_utilizadores_novo();
    dados->repositorioAlbuns = repositorio_albuns_novo();
    dados->repositorioHistoricos = repositorio_historicos_novo();

    // query 3
    // TODO : Encapsulamento, estamos a fazer get directo para iterar, na query 3
    dados->generosDeMusicaGostadosPorIdade = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, (GDestroyNotify)g_array_unref);

    // query 4
    dados->reproducoesPorArtistaPorSemana = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, (GDestroyNotify)g_hash_table_destroy);
    dados->top10PorSemana = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, (GDestroyNotify)repositorio_dados_heap_artista_reproducao_destroi);

    // query 5
    dados->indiceColunasGenero = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, (GDestroyNotify)utils_g_slice_free_int);

    dados->ordemColunaUtilizadores = NULL;
    dados->audicoesUtilizadoresPorGenero = NULL;
    dados->proximoIndiceColuna = 0;


    // query6
    dados->historicosNecessarios = hashTable_Query6_Utilizadores;
    dados->utilizadoresNecessarios = utilizadoresNecessarios;

    return dados;
}

void dados_destroi(Dados *dados)
{
    // repositorios
    repositorio_artistas_destroi(dados->repositorioArtistas);
    repositorio_musicas_destroi(dados->repositorioMusicas);
    repositorio_utilizadores_destroi(dados->repositorioUtilizadores);
    repositorio_historicos_destroi(dados->repositorioHistoricos);
    repositorio_albuns_destroi(dados->repositorioAlbuns);

    // query 3
    g_hash_table_destroy(dados->generosDeMusicaGostadosPorIdade);

    // query 4
    // dados->reproducoesPorArtistaPorSemana ja foi dado free em repositorio_dados_criar_top10_por_semana
    g_hash_table_destroy(dados->top10PorSemana);

    // query 5
    // indice coluna e genero ja foram destruidas



    if (dados->ordemColunaUtilizadores)
    {
        for (int i = 0; i < dados->proximoIndiceColuna; i++)
        {
            g_free(dados->ordemColunaUtilizadores[i]);
        }
        free(dados->ordemColunaUtilizadores);
    }
    if (dados->audicoesUtilizadoresPorGenero)
    {
        for (int i = 0; i < repositorio_utilizadores_get_proximoIndiceLinha (dados->repositorioUtilizadores); i++)
        {
            free(dados->audicoesUtilizadoresPorGenero[i]);
        }
        free(dados->audicoesUtilizadoresPorGenero);
    }

    // query6

    if (dados->historicosNecessarios)
    {
        g_hash_table_destroy(dados->historicosNecessarios);
    }

    if (dados->utilizadoresNecessarios)
    {
        g_hash_table_destroy(dados->utilizadoresNecessarios);
    }

    g_free(dados);
}

RepositorioArtistas *dados_get_repositorioArtistas(Dados *dados)
{
    return dados->repositorioArtistas;
}

RepositorioMusicas *dados_get_repositorioMusicas(Dados *dados)
{
    return dados->repositorioMusicas;
}

RepositorioUtilizadores *dados_get_repositorioUtilizadores(Dados *dados)
{
    return dados->repositorioUtilizadores;
}

RepositorioHistoricos *dados_get_repositorioHistoricos(Dados *dados)
{
    return dados->repositorioHistoricos;
}

RepositorioAlbuns *dados_get_repositorioAlbuns(Dados *dados)
{
    return dados->repositorioAlbuns;
}

//TODO: melhoria topN
const MinHeap *dados_get_top10_da_semana(Dados *dados, int semana)
{
    return g_hash_table_lookup(dados->top10PorSemana, GINT_TO_POINTER(semana));
}

int dados_get_numero_semanas (Dados *dados){
    return g_hash_table_size(dados->top10PorSemana);
}

int **dados_get_audicoesUtilizadoresPorGenero(Dados *dados)
{
    return dados->audicoesUtilizadoresPorGenero;
}

int dados_get_proximoIndiceColuna(Dados *dados)
{
    return dados->proximoIndiceColuna;
}

char **dados_get_ordemColunasGeneros(Dados *dados)
{
    return dados->ordemColunaUtilizadores;
}

gboolean repositorio_dados_valida_logica_musica(Musica *musica, RepositorioArtistas *repositorioArtistas)
{
    Artista *artista = NULL;
    short quantidadeArtistas = musica_get_quantidadeDeArtistas(musica);
    for (short i = 0; i < quantidadeArtistas; i++)
    {

        int idArtista = musica_get_idArtistaPorIndice(musica, i);
        artista = repositorio_artistas_get_artista_por_id(repositorioArtistas, idArtista);
        if (artista == NULL)
        {
            return FALSE;
        }
    }
    return TRUE;
}

gboolean repositorio_dados_valida_logica_musica_album(Musica *musica, RepositorioAlbuns *repositorioalbuns)
{
    Album *album = NULL;

    int idAlbum = musica_get_idAlbum(musica);
    album = repositorio_albuns_get_album_por_id(repositorioalbuns, idAlbum);
    if (album == NULL)
    {
        return FALSE;
    }

    return TRUE;
}

gboolean repositorio_dados_valida_musicas_gostadas(Utilizador *utilizador, Dados *dados)
{
    RepositorioMusicas *repositorioMusicas = dados->repositorioMusicas;

    short quantidadeDeMusicas = utilizador_get_quantidadeDeMusicasGostadas(utilizador);
    if (quantidadeDeMusicas == 0)
        return TRUE;

    for (short i = 0; i < quantidadeDeMusicas; i++)
    {
        int musicaId = utilizador_get_musicasGostadasPorIndice(utilizador, i);
        Musica *musica = repositorio_musicas_get_musica_por_id(repositorioMusicas, &musicaId);
        if (musica == NULL)
        {
            return FALSE; // Música inválida encontrada
        }
    }
    return TRUE; // Todas as músicas são válidas
}

gboolean repositorio_dados_valida_musica(Musica *musica, RepositorioArtistas *repositorioArtistas, RepositorioAlbuns *repositorioAlbuns)
{
    if (!repositorio_dados_valida_logica_musica_album(musica, repositorioAlbuns))
    {
        return FALSE;
    }
    if (!repositorio_dados_valida_logica_musica(musica, repositorioArtistas))
    {
        return FALSE;
    }
    return TRUE;
}

gboolean repositorio_dados_tenta_adicionar_artista(void *apontador, Artista *artista)
{
    Dados *dados = (Dados *)apontador;

    if (artista_valida(artista))
    {
        RepositorioArtistas *repositorioArtistas = dados->repositorioArtistas;
        repositorio_artistas_adicionar(repositorioArtistas, artista);
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void repositorio_adiciona_discografia_artista_segundos(Musica *musica, RepositorioArtistas *repositorioArtistas)
{
    short duracaoMusicaEmSegundos = musica_get_duracaoMusicaEmSegundos(musica);
    short quantidadeArtistas = musica_get_quantidadeDeArtistas(musica);

    for (short i = 0; i < quantidadeArtistas; i++)
    {
        int idArtista = musica_get_idArtistaPorIndice(musica, i);
        Artista *artista = repositorio_artistas_get_artista_por_id(repositorioArtistas, idArtista);
        artista_acrescenta_duracaoDiscografiaEmSegundos(artista, duracaoMusicaEmSegundos);
    }
}

gboolean repositorio_dados_tenta_adicionar_musica(void *apontador, Musica *musica)
{
    Dados *dados = (Dados *)apontador;

    RepositorioArtistas *repositorioArtistas = dados->repositorioArtistas;
    RepositorioAlbuns *repositorioAlbuns = dados->repositorioAlbuns;

    if (repositorio_dados_valida_musica(musica, repositorioArtistas, repositorioAlbuns))
    {
        RepositorioMusicas *repositorioMusicas = dados->repositorioMusicas;
        repositorio_musicas_adicionar(repositorioMusicas, musica);
        repositorio_adiciona_discografia_artista_segundos(musica, repositorioArtistas);
        repositorio_artistas_lista_desordenada(repositorioArtistas);
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
void repositorio_dados_adiciona_likes_de_utilizador(Dados *dados, Utilizador *utilizador)
{
    GHashTable *generosDeMusicaGostadosPorIdade = dados->generosDeMusicaGostadosPorIdade;
    RepositorioMusicas *repositorioMusicas = dados->repositorioMusicas;

    short idade = utilizador_get_idadeDoUtilizador(utilizador);
    if (idade < 0 || idade >= IDADE_MAXIMA)
        return;

    short numMusicas = utilizador_get_quantidadeDeMusicasGostadas(utilizador);
    for (short i = 0; i < numMusicas; i++)
    {
        int idMusica = utilizador_get_musicasGostadasPorIndice(utilizador, i);
        Musica *musica = repositorio_musicas_get_musica_por_id(repositorioMusicas, &idMusica);

        if (musica)
        {
            Quark generoQuark = musica_get_generoMusicaQuark(musica);

            GArray *array = g_hash_table_lookup(generosDeMusicaGostadosPorIdade, GINT_TO_POINTER(generoQuark));
            if (!array)
            {
                array = g_array_sized_new(FALSE, TRUE, sizeof(int), IDADE_MAXIMA);
                g_array_set_size(array, IDADE_MAXIMA);
                g_hash_table_insert(generosDeMusicaGostadosPorIdade, GINT_TO_POINTER(generoQuark), array);
            }
            g_array_index(array, int, idade)++;
        }
    }
}

gboolean repositorio_dados_tenta_adicionar_utilizador(void *apontador, Utilizador *utilizador)
{
    Dados *dados = (Dados *)apontador;

    if (repositorio_dados_valida_musicas_gostadas(utilizador, dados))
    {
        RepositorioUtilizadores *repositorioUtilizadores = dados->repositorioUtilizadores;
        repositorio_dados_adiciona_likes_de_utilizador(dados, utilizador);
        repositorio_utilizadores_adicionar(repositorioUtilizadores, utilizador, dados->utilizadoresNecessarios);
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void repositorio_dados_adiciona_albuns_artista(Album *album, Dados *dados)
{
    RepositorioArtistas *repositorioArtistas = dados->repositorioArtistas;

    short quantidadeArtistas = album_get_quantidadeDeArtistas(album);
    for (short i = 0; i < quantidadeArtistas; i++)
    {
        int idArtista = album_get_idArtistaPorIndice(album, i);
        Artista *artista = repositorio_artistas_get_artista_por_id(repositorioArtistas, idArtista);
        if (artista != NULL)
        {
            artista_incrementa_numeroDeAlbuns(artista);
        }
        else
        {
            g_print("Artista não encontrado\n");
        }
    }
}

gboolean repositorio_dados_tenta_adicionar_albuns(void *apontador, Album *album)
{
    Dados *dados = (Dados *)apontador;

    RepositorioAlbuns *repositorioAlbuns = dados->repositorioAlbuns;
    repositorio_albuns_adicionar(repositorioAlbuns, album);
    repositorio_dados_adiciona_albuns_artista(album, dados);

    return TRUE;
}

void repositorio_dados_adiciona_reproducoesPorArtistaPorSemana(Dados *dados, Historico *historico)
{

    GHashTable *reproducoesPorArtistaPorSemana = dados->reproducoesPorArtistaPorSemana;
    RepositorioMusicas *repositorioMusicas = dados->repositorioMusicas;

    int semana = utils_calcular_numero_semana_juliana(historico_get_dataMusicaOuvida(historico));

    int idMusica = historico_get_idMusica(historico);

    Musica *musica = repositorio_musicas_get_musica_por_id(repositorioMusicas, &idMusica);

    GHashTable *hashTableArtistas = g_hash_table_lookup(reproducoesPorArtistaPorSemana, GINT_TO_POINTER(semana));
    if (!hashTableArtistas)
    {
        hashTableArtistas = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, utils_g_slice_free_int);
        g_hash_table_insert(reproducoesPorArtistaPorSemana, GINT_TO_POINTER(semana), hashTableArtistas);
    }
    short reproducaoEmSegundos = historico_get_duracaoAudicaoMusicaSegundos(historico);
    short quantidadeArtistas = musica_get_quantidadeDeArtistas(musica);

    for (short i = 0; i < quantidadeArtistas; i++)
    {
        int idArtista = musica_get_idArtistaPorIndice(musica, i);

        int *valorAtual = g_hash_table_lookup(hashTableArtistas, GINT_TO_POINTER(idArtista));
        if (!valorAtual)
        {

            valorAtual = g_slice_new(int);
            *valorAtual = reproducaoEmSegundos;
            g_hash_table_insert(hashTableArtistas, GINT_TO_POINTER(idArtista), valorAtual);
        }
        else
        {

            *valorAtual += reproducaoEmSegundos;
        }
    }
}

void repositorio_dados_adiciona_profit_artista(Dados *dados, Historico *historico)
{
    RepositorioMusicas *repositorioMusicas = dados->repositorioMusicas;
    RepositorioArtistas *repositorioArtistas = dados->repositorioArtistas;

    int idMusica = historico_get_idMusica(historico);
    Musica *musica = repositorio_musicas_get_musica_por_id(repositorioMusicas, &idMusica);

    short quantidadeDeArtistas = musica_get_quantidadeDeArtistas(musica);
    for (short i = 0; i < quantidadeDeArtistas; i++)
    {
        int idArtista = musica_get_idArtistaPorIndice(musica, i);
        Artista *artista = repositorio_artistas_get_artista_por_id(repositorioArtistas, idArtista);

        TipoArtista tipoArtista = artista_get_tipoArtista(artista);

        artista_incrementa_profitTotal(artista);
        if (tipoArtista == GROUP)
        {
            float profitPorReproducao = artista_get_profitPorReproducao(artista);
            short numeroConstituintes = artista_get_numeroConstituintesArtistas(artista);
            float lucroPorArtista = profitPorReproducao / numeroConstituintes;
            for (short j = 0; j < numeroConstituintes; j++)
            {
                int idConstituinte = artista_get_idConstituintesArtistasPorIndice(artista, j);
                Artista *constituinte = repositorio_artistas_get_artista_por_id(repositorioArtistas, idConstituinte);
                artista_constituintes_incrementa_profitTotal(constituinte, lucroPorArtista);
            }
        }
    }
}

void repositorio_dados_inicia_audicoesUtilizadoresPorGenero(Dados *dados)
{
    int numeroLinhas = repositorio_utilizadores_get_tamanho_indice(dados->repositorioUtilizadores); // numero total de utilizadores
    int numeroColunas = g_hash_table_size(dados->generosDeMusicaGostadosPorIdade);           // numero total de generos

    dados->audicoesUtilizadoresPorGenero = (int **)malloc(numeroLinhas * sizeof(int *));

    for (int i = 0; i < numeroLinhas; i++)
    {
        dados->audicoesUtilizadoresPorGenero[i] = (int *)calloc(numeroColunas, sizeof(int));
    }
}

void repositorio_dados_adiciona_audicoesUtilizadoresPorGenero(Dados *dados, Historico *historico)
{

    int idUtilizador = historico_get_idUtilizador(historico);
    int idMusica = historico_get_idMusica(historico);

    RepositorioMusicas *repositorioMusicas = dados->repositorioMusicas;
    Musica *musica = repositorio_musicas_get_musica_por_id(repositorioMusicas, &idMusica);
    Quark generoMusicaQuark = musica_get_generoMusicaQuark(musica);

    int *indiceLinhaUtilizador = repositorio_utilizadores_get_indice_linha(dados->repositorioUtilizadores, idUtilizador);
    if (!indiceLinhaUtilizador)
    {
    repositorio_utilizadores_adiciona_utilizador_indice_linha (dados->repositorioUtilizadores, idUtilizador);
    }

    int *indiceColunaGenero = g_hash_table_lookup(dados->indiceColunasGenero, GINT_TO_POINTER(generoMusicaQuark));
    if (!indiceColunaGenero)
    {
        indiceColunaGenero = g_slice_new(int);
        *indiceColunaGenero = dados->proximoIndiceColuna;
        g_hash_table_insert(dados->indiceColunasGenero, GINT_TO_POINTER(generoMusicaQuark), indiceColunaGenero);
        dados->proximoIndiceColuna++;
    }

    int **matriz = dados->audicoesUtilizadoresPorGenero;

    matriz[*indiceLinhaUtilizador][*indiceColunaGenero]++;
}


void repositorio_dados_cria_ordemColunasGeneros(Dados *dados)
{

    dados->ordemColunaUtilizadores = (char **)malloc(dados->proximoIndiceColuna * sizeof(char *));

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, dados->indiceColunasGenero);

    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        Quark generoQuark = (Quark) GPOINTER_TO_INT(key);
        int *indicePtr = (int *)value;
        int indice = *indicePtr;

        dados->ordemColunaUtilizadores[indice] = g_strdup( string_de_quark( generoQuark));
    }

    g_hash_table_destroy(dados->indiceColunasGenero);
}

gboolean repositorio_dados_tenta_adicionar_historico(void *apontador, Historico *historico)
{
    Dados *dados = (Dados *)apontador;

    repositorio_dados_adiciona_reproducoesPorArtistaPorSemana(dados, historico);
    repositorio_dados_adiciona_profit_artista(dados, historico);
    repositorio_dados_adiciona_audicoesUtilizadoresPorGenero(dados, historico);

    GHashTable *comandosQuery6 = dados->historicosNecessarios;
    int idUtilizador = historico_get_idUtilizador(historico);
    if (comandosQuery6 == NULL)
    {
        repositorio_historicos_adicionar(dados->repositorioHistoricos, historico);
    }
    else if (g_hash_table_contains(comandosQuery6, GINT_TO_POINTER(idUtilizador)))
    {
        repositorio_historicos_adicionar(dados->repositorioHistoricos, historico);
    } else {
        historico_destroi(historico);
    }
    return TRUE;
}

struct ArtistaReproducao
{
    int idArtista;
    int reproducoes;
};

// Função de comparação para ArtistaReproducao (ordena por número de reproduções)
int artista_reproducao_compara(const void *a, const void *b)
{
    const ArtistaReproducao *artistaA = (const ArtistaReproducao *)a;
    const ArtistaReproducao *artistaB = (const ArtistaReproducao *)b;

    // Comparação pelo número de reproduções
    if (artistaA->reproducoes != artistaB->reproducoes)
    {
        return artistaA->reproducoes - artistaB->reproducoes;
    }

    // Desempate pelo ID do artista (menor ID vem primeiro)
    return artistaB->idArtista - artistaA->idArtista;
}

ArtistaReproducao *artista_reproducao_novo()
{
    ArtistaReproducao *artista = g_slice_new0(ArtistaReproducao);
    return artista;
}

void artista_reproducao_destroi(void *artistareproducao)
{
    ArtistaReproducao *artistaReproducao = (ArtistaReproducao *)artistareproducao;
    g_slice_free(ArtistaReproducao, artistaReproducao);
}

void repositorio_dados_heap_artista_reproducao_destroi(MinHeap *heap)
{
    heap_destroi(heap, artista_reproducao_destroi);
}

int artista_reproducao_get_idArtista(struct ArtistaReproducao *artista)
{
    return artista->idArtista;
}

int artista_reproducao_get_reproducoes(struct ArtistaReproducao *artista)
{
    return artista->reproducoes;
}

void repositorio_dados_criar_top10_por_semana(Dados *dados)
{
    GHashTable *reproducoesPorArtistaPorSemana = dados->reproducoesPorArtistaPorSemana;
    GHashTable *top10PorSemanas = dados->top10PorSemana;

    // Itera sobre as semanas na hashtable
    GHashTableIter iterSemanas;
    gpointer keySemana, valueArtistas;

    g_hash_table_iter_init(&iterSemanas, reproducoesPorArtistaPorSemana);
    while (g_hash_table_iter_next(&iterSemanas, &keySemana, &valueArtistas))
    {
        GHashTable *artistas = (GHashTable *)valueArtistas;

        // Cria uma min-heap de tamanho 10 para armazenar os artistas com maior tempo de reprodução
        MinHeap *heap = heap_nova(10, artista_reproducao_compara);

        GHashTableIter iterArtistas;
        gpointer keyArtista, valueReproducoes;
        g_hash_table_iter_init(&iterArtistas, artistas);

        while (g_hash_table_iter_next(&iterArtistas, &keyArtista, &valueReproducoes))
        {
            int idArtista = GPOINTER_TO_INT(keyArtista);
            int reproducoes = *(int *)valueReproducoes;

            ArtistaReproducao *artistaReproducao = artista_reproducao_novo();
            artistaReproducao->idArtista = idArtista;
            artistaReproducao->reproducoes = reproducoes;

            heap_insere(heap, artistaReproducao, artista_reproducao_destroi);
        }

        g_hash_table_insert(top10PorSemanas, keySemana, heap);
    }

    g_hash_table_destroy(dados->reproducoesPorArtistaPorSemana); // apenas era preciso para criar o top10
}

Dados *dados_carregar(void *estatisticasCarregamento, char *pastaDados, Dados *dados)
{

    if (!pastaDados || strlen(pastaDados) == 0)
    {
        fprintf(stderr, "Erro: Caminho dos dados não fornecido ou inválido.\n");
        return NULL;
    }

    // Concatena os caminhos dos ficheiros de dados
    char *caminhoFicheiroUsers = g_strconcat(pastaDados, "/users.csv", NULL);
    char *caminhoFicheiroArtists = g_strconcat(pastaDados, "/artists.csv", NULL);
    char *caminhoFicheiroMusics = g_strconcat(pastaDados, "/musics.csv", NULL);
    char *caminhoFicheiroAlbums = g_strconcat(pastaDados, "/albums.csv", NULL);
    char *caminhoFicheirohistorico = g_strconcat(pastaDados, "/history.csv", NULL);

    Estatisticas *estatisticas = (Estatisticas *)estatisticasCarregamento;

    // Carrega artistas
    estatisticas_inicia_contagem(estatisticas, "CarregamentoArtistas");
    parser_carrega(dados, caminhoFicheiroArtists,
                   (AdicionaObjeto)repositorio_dados_tenta_adicionar_artista,
                   (LinhaParaObjeto)artista_constroi_de_linha,
                   (DestroiObjeto)artista_destroi);
    estatisticas_termina_contagem(estatisticas, "CarregamentoArtistas");

    // Carrega Albuns
    estatisticas_inicia_contagem(estatisticas, "CarregamentoAlbuns");
    parser_carrega(dados, caminhoFicheiroAlbums,
                   (AdicionaObjeto)repositorio_dados_tenta_adicionar_albuns,
                   (LinhaParaObjeto)album_constroi_de_linha,
                   (DestroiObjeto)album_destroi);
    estatisticas_termina_contagem(estatisticas, "CarregamentoAlbuns");

    // Carrega músicas
    estatisticas_inicia_contagem(estatisticas, "CarregamentoMusicas");
    parser_carrega(dados, caminhoFicheiroMusics,
                   (AdicionaObjeto)repositorio_dados_tenta_adicionar_musica,
                   (LinhaParaObjeto)musica_constroi_de_linha,
                   (DestroiObjeto)musica_destroi);
    estatisticas_termina_contagem(estatisticas, "CarregamentoMusicas");

    // Carrega utilizadores
    estatisticas_inicia_contagem(estatisticas, "CarregamentoUtilizadores");
    parser_carrega(dados, caminhoFicheiroUsers,
                   (AdicionaObjeto)repositorio_dados_tenta_adicionar_utilizador,
                   (LinhaParaObjeto)utilizador_constroi_de_linha,
                   (DestroiObjeto)utilizador_destroi);
    estatisticas_termina_contagem(estatisticas, "CarregamentoUtilizadores");

    // Carrega Histórico
    repositorio_dados_inicia_audicoesUtilizadoresPorGenero(dados);
    estatisticas_inicia_contagem(estatisticas, "CarregamentoHistorico");
    parser_carrega(dados, caminhoFicheirohistorico,
                   (AdicionaObjeto)repositorio_dados_tenta_adicionar_historico,
                   (LinhaParaObjeto)historico_constroi_de_linha,
                   (DestroiObjeto)historico_destroi);
    estatisticas_termina_contagem(estatisticas, "CarregamentoHistorico");

    // Carrega estruturas auxiliares para queries

    repositorio_dados_criar_top10_por_semana(dados);
    repositorio_dados_cria_ordemColunasGeneros(dados);
    repositorio_utilizadores_cria_ordemLinhasUtilizadores(dados->repositorioUtilizadores);

    g_free(caminhoFicheiroUsers);
    g_free(caminhoFicheiroArtists);
    g_free(caminhoFicheiroMusics);
    g_free(caminhoFicheiroAlbums);
    g_free(caminhoFicheirohistorico);

    return dados;
}



// iterador para generos 

 struct GenerosIterador {
    GHashTableIter iter;
    gpointer key;
    gpointer value;
};

// Função para inicializar o iterador
GenerosIterador *generos_iterador_novo(Dados *dados) {
    GHashTable *generosDeMusicaGostadosPorIdade = dados->generosDeMusicaGostadosPorIdade;

    GenerosIterador *iterador = malloc(sizeof(GenerosIterador));
    if (!iterador) {
        return NULL;
    }

    g_hash_table_iter_init(&iterador->iter, generosDeMusicaGostadosPorIdade);
    iterador->key = NULL;
    iterador->value = NULL;

    return iterador;
}

gboolean generos_iterador_proximo(GenerosIterador *iterador, Quark *genero, GArray **array) {
    if (!iterador || !genero || !array) {
        return FALSE;
    }

    if (g_hash_table_iter_next(&iterador->iter, &iterador->key, &iterador->value)) {
        *genero = (Quark)GPOINTER_TO_INT(iterador->key);
        *array = (GArray *)iterador->value;
        return TRUE;
    }

    return FALSE;
}

void generos_iterador_destroi(GenerosIterador *iterador) {
    if (iterador) {
        free(iterador);
    }
}
