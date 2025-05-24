#include "artista.h"

// "id";"name";"description";"recipe_per_stream";"id_constituent";"country";"type"
#define COLUNA_ID 0
#define COLUNA_NOME_ARTISTAS 1
#define COLUNA_PROFIT_POR_REPRODUCAO 3
#define COLUNA_ID_CONSTITUINTES 4
#define COLUNA_PAIS 5
#define COLUNA_TIPO_ARTISTA 6

struct Artista {
    char *nomeArtista;
    char *nacionalidadeArtista;
    int *idConstituintesArtistas; // Array de IDs dos constituintes
    float profitPorReproducao;
    float profitTotal;
    TipoArtista tipoArtista;
    int idArtista;
    int duracaoDiscorgrafiaEmSegundos;
    short numeroDeAlbuns;
    short quantidadeConstituintes;

};

Artista *artista_novo() {
    Artista *artista = g_slice_new0(Artista);
    artista->idConstituintesArtistas = NULL;
    artista->quantidadeConstituintes = 0;
    return artista;
}

void artista_destroi(gpointer gp) {
    Artista *artista = (Artista *)gp;
    if (artista == NULL) {
        return;
    }
    free(artista->idConstituintesArtistas);
    g_free(artista->nomeArtista);
    g_free(artista->nacionalidadeArtista);
    g_slice_free(Artista, artista);

}

int artista_get_idArtista(Artista *artista) {
    return artista->idArtista;
}

const char *artista_get_nomeArtista(Artista *artista) {
    return artista->nomeArtista;
}

int artista_get_idConstituintesArtistasPorIndice(Artista *artista, int indice) {
    if (indice < 0 || indice >= artista->quantidadeConstituintes) {
        return -1; // Índice inválido
    }
    return artista->idConstituintesArtistas[indice];
}

short artista_get_numeroConstituintesArtistas(Artista *artista) {
    return artista->quantidadeConstituintes;
}

const char *artista_get_nacionalidadeArtista(Artista *artista) {
    return artista->nacionalidadeArtista;
}

TipoArtista artista_get_tipoArtista(Artista *artista) {
    return artista->tipoArtista;
}

int artista_get_duracaoDiscorgrafiaEmSegundos(Artista *artista) {
    return artista->duracaoDiscorgrafiaEmSegundos;
}

void artista_acrescenta_duracaoDiscografiaEmSegundos(Artista *artista, int duracaoDiscorgrafiaEmSegundos) {
    artista->duracaoDiscorgrafiaEmSegundos += duracaoDiscorgrafiaEmSegundos;
}

short artista_get_numeroDeAlbuns(Artista *artista) {
    return artista->numeroDeAlbuns;
}

void artista_incrementa_numeroDeAlbuns(Artista *artista) {
    artista->numeroDeAlbuns++;
}

float artista_get_profitPorReproducao(Artista *artista) {
    return artista->profitPorReproducao;
}

float artista_get_profitTotal(Artista *artista) {
    return artista->profitTotal;
}

void artista_incrementa_profitTotal(Artista *artista) {
    artista->profitTotal += artista->profitPorReproducao;
}

void artista_constituintes_incrementa_profitTotal(Artista *artista, float profit) {
    artista->profitTotal += profit;
}

TipoArtista artista_tipo(char *tipo) {
    char *tipoSemAspas = utils_remove_caracteres_inicio_e_fim(tipo, 1, 2);
    if (strcasecmp(tipoSemAspas, "group") == 0) {
        g_free(tipoSemAspas);
        return GROUP;
    } else if (strcasecmp(tipoSemAspas, "individual") == 0) {
        g_free(tipoSemAspas);
        return INDIVIDUAL;
    } else {
        g_free(tipoSemAspas);
        return ARTISTA_INVALIDO;
    }
}

char *artista_tipo_para_string(TipoArtista tipoArtista) {
    switch (tipoArtista) {
        case INDIVIDUAL:
            return "individual";
        case GROUP:
            return "group";
        default:
            return "invalido";
    }
}

gboolean artista_valida(Artista *artista) {
    short numConstituintes = artista_get_numeroConstituintesArtistas(artista);
    return !(artista_get_tipoArtista(artista) == INDIVIDUAL && numConstituintes != 0);
}

void artista_processa_id_artistas_constituintes(Artista *artista, const char *coluna) {
    if (strlen(coluna) <= 4) {
        return;
    }

    gchar *coluna_sem_brackets = g_strndup(coluna + 1, strlen(coluna) - 2);
    gchar **ids_constituintes = g_strsplit(coluna_sem_brackets, ", ", -1);

    // Contar número de constituintes
    short num_constituintes = 0;
    while (ids_constituintes[num_constituintes] != NULL) {
        num_constituintes++;
    }

    // Alocar memória para os constituintes
    artista->idConstituintesArtistas = malloc(num_constituintes * sizeof(int));
    artista->quantidadeConstituintes = num_constituintes;

    for (short i = 0; i < num_constituintes; i++) {
        artista->idConstituintesArtistas[i] = atoi(ids_constituintes[i] + 2);
    }

    g_strfreev(ids_constituintes);
    g_free(coluna_sem_brackets);
}

Artista *artista_constroi_de_linha(char **coluna) {
    TipoArtista tipoartista = artista_tipo(coluna[COLUNA_TIPO_ARTISTA]);
    if (tipoartista == ARTISTA_INVALIDO) {
        return NULL;
    }

    Artista *artista = artista_novo();

    artista->idArtista = atoi(coluna[COLUNA_ID] + 1);
    artista->nomeArtista = strdup(coluna[COLUNA_NOME_ARTISTAS]);
    artista_processa_id_artistas_constituintes(artista, coluna[COLUNA_ID_CONSTITUINTES]);
    artista->nacionalidadeArtista = strdup(coluna[COLUNA_PAIS]);
    artista->tipoArtista = tipoartista;

    float profit = atof(coluna[COLUNA_PROFIT_POR_REPRODUCAO]);
    artista->profitPorReproducao = (int)(profit * 100) / 100.0;

    return artista;
}

gint artista_compara_decrescente(gconstpointer a, gconstpointer b) {
    Artista *artistaA = *(Artista **)a;
    Artista *artistaB = *(Artista **)b;

    int duracaoA = artista_get_duracaoDiscorgrafiaEmSegundos(artistaA);
    int duracaoB = artista_get_duracaoDiscorgrafiaEmSegundos(artistaB);

    const char *nomeA = artista_get_nomeArtista(artistaA);
    const char *nomeB = artista_get_nomeArtista(artistaB);

    if (duracaoA == duracaoB) {
        return strcmp(nomeA, nomeB);
    } else {
        return duracaoB - duracaoA;
    }
}

char *artista_id_para_string (int id) {
    char *resultado = g_strdup_printf("A%07d", id);
    return resultado;
}
