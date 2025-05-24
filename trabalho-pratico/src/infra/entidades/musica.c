#include "musica.h"

// "id";"title";"artist_id";"album_id";"duration";"genre";"year";"lyrics"
#define COLUNA_ID 0
#define COLUNA_ID_ARTISTA 2
#define COLUNA_ID_ABUM 3
#define COLUNA_DURACAO_MUSICA 4
#define COLUNA_GENERO 5

struct Musica {
    Quark generoMusica;;
    int *idArtista; // Array de IDs dos artistas
    int idMusica;
    int idAlbum;
    short quantidadeArtistas;
    short duracaoMusicaEmSegundos;
};

Musica *musica_nova() {
    Musica *musica = g_slice_new0(Musica);
    musica->idArtista = NULL;
    musica->quantidadeArtistas = 0;
    return musica;
}

void musica_destroi(gpointer gp) {
    Musica *musica = (Musica *)gp;
    if (musica == NULL) {
        return;
    }
    free(musica->idArtista);
    g_slice_free(Musica, musica);
}

int musica_get_idMusica(Musica *musica) {
    return musica->idMusica;
}

int musica_get_idAlbum(Musica *musica) {
    return musica->idAlbum;
}

int musica_get_idArtistaPorIndice(Musica *musica, int indice) {
    if (indice < 0 || indice >= musica->quantidadeArtistas) {
        return -1; // Índice inválido
    }
    return musica->idArtista[indice];
}

short musica_get_quantidadeDeArtistas(Musica *musica) {
    return musica->quantidadeArtistas;
}

short musica_get_duracaoMusicaEmSegundos(Musica *musica) {
    return musica->duracaoMusicaEmSegundos;
}

const char *musica_get_generoMusica(Musica *musica) {
    return  string_de_quark(musica->generoMusica);
}

Quark musica_get_generoMusicaQuark(Musica *musica){
    return  musica->generoMusica;
}

gboolean musica_valida(char **coluna) {
    if (!utils_valida_parentises(coluna[COLUNA_ID_ARTISTA])) {
        return FALSE;
    }
    if (!utils_valida_duracao(coluna[COLUNA_DURACAO_MUSICA])) {
        return FALSE;
    }
    return TRUE;
}

void musica_adiciona_id_artistas_constituintes(Musica *musica, const char *coluna) {
    gchar *coluna_sem_brackets = g_strndup(coluna + 2, strlen(coluna) - 3);
    gchar **ids_artistas_constituintes = g_strsplit(coluna_sem_brackets, ", ", -1);

    // Contar o número de IDs de artistas
    short num_artistas = 0;
    while (ids_artistas_constituintes[num_artistas] != NULL) {
        num_artistas++;
    }

    // Alocar memória apenas uma vez para todos os IDs
    musica->idArtista = malloc(num_artistas * sizeof(int));
    musica->quantidadeArtistas = num_artistas;

    for (short i = 0; i < num_artistas; i++) {
        gchar *idArtistaConstituinte = g_strndup(ids_artistas_constituintes[i] + 2, strlen(ids_artistas_constituintes[i]) - 2);
        musica->idArtista[i] = atoi(idArtistaConstituinte);
        g_free(idArtistaConstituinte);
    }

    g_strfreev(ids_artistas_constituintes);
    g_free(coluna_sem_brackets);
}

Musica *musica_constroi_de_linha(char **coluna) {
    if (!musica_valida(coluna)) {
        return NULL;
    }

    Musica *musica = musica_nova();

    musica->idMusica = atoi(coluna[COLUNA_ID] + 1);
    musica_adiciona_id_artistas_constituintes(musica, coluna[COLUNA_ID_ARTISTA]);
    musica->idAlbum = atoi(coluna[COLUNA_ID_ABUM] + 2);
    musica->duracaoMusicaEmSegundos = utils_converte_duracao_para_segundos(coluna[COLUNA_DURACAO_MUSICA]);
    musica->generoMusica = quark_de_string(coluna[COLUNA_GENERO]);

    return musica;
}
