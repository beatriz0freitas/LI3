#include "album.h"

// "id";"title";"artist_id";"year";"producers"
#define COLUNA_ID 0
#define COLUNA_TITULO 1
#define COLUNA_IDARTISTA 2

struct Album {
    int *idArtista;
    char *tituloAlbum;
    int idAlbum;
    short quantidadeArtistas;
};

Album *album_novo() {
    Album *album = g_slice_new0(Album);
    album->idArtista = NULL;
    album->quantidadeArtistas = 0;
    return album;
}

void album_destroi(gpointer gp) {
    Album *album = (Album *)gp;
    if (album == NULL) {
        return;
    }
    g_free(album->tituloAlbum);
    free(album->idArtista);
    g_slice_free(Album, album);

}

int album_get_idAlbum(Album *album) {
    return album->idAlbum;
}


int album_get_idArtistaPorIndice(Album *album, int indice) {
    if (indice < 0 || indice >= album->quantidadeArtistas) {
        return -1; // Indica um erro
    }
    return album->idArtista[indice];
}

short album_get_quantidadeDeArtistas(Album *album) {
    return album->quantidadeArtistas;
}

void album_processa_id_artistas_constituintes(Album *album, const char *coluna) {
    if (strlen(coluna) <= 4) {
        return;
    }

    const gchar *coluna_sem_brackets = coluna + 1; // Avançar para remover o primeiro '['
    gchar **id_artista_constituinte = g_strsplit(coluna_sem_brackets, ", ", -1);

    // Contar o número de constituintes para alocar memoria no array.
    short num_artistas = 0;
    while (id_artista_constituinte[num_artistas] != NULL) {
        num_artistas++;
    }

    // Alocar memória apenas uma vez
    album->idArtista = malloc(num_artistas * sizeof(int));
    album->quantidadeArtistas = num_artistas;

    for (short i = 0; i < num_artistas; i++) {
        album->idArtista[i] = atoi(id_artista_constituinte[i] + 2);
    }

    g_strfreev(id_artista_constituinte);
}

Album *album_constroi_de_linha(char **coluna) {
    Album *album = album_novo();

    album->idAlbum = atoi(coluna[COLUNA_ID] + 2);
    album->tituloAlbum = strdup(coluna[COLUNA_TITULO]);
    album_processa_id_artistas_constituintes(album, coluna[COLUNA_IDARTISTA]);

    return album;
}

char *album_id_para_string(int id) {
    char *resultado = (char *)malloc(8 * sizeof(char));
    sprintf(resultado, "%c%c%06d", 'A', 'L', id);
    return resultado;
}
