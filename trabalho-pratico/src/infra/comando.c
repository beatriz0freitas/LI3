#include "comando.h"

struct Comando {
    int numeroDaQuery;
    int numeroComando;
    char *separador;
    GPtrArray *argumentos; 
};

Comando *comando_novo() {
    Comando *comando = g_new0(Comando, 1);
    comando->argumentos = g_ptr_array_new_with_free_func(g_free);
    comando->separador = g_strdup(";");
    return comando;
}

void comando_destroi(Comando *comando) {
    if (comando) {
        g_ptr_array_free(comando->argumentos, TRUE); 
        g_free(comando->separador);
        g_free(comando);
    }
}

Comando *comando_constroi_de_linha(char *linha) {
    if (!linha || linha[0] == '\0') return NULL; 

    Comando *comando = comando_novo();
    comando->numeroDaQuery = linha[0] - '0'; 

    if (linha[1] == 'S') {
        g_free(comando->separador);
        comando->separador = g_strdup("=");
        linha = linha + 3;
    }else {
        linha = linha + 2;
    }

    char *token = strtok(linha, " ");
    while (token != NULL) {
        if (token[0] == '"') {
            char *inicioArgumento = g_strdup(token + 1);
            token = strtok(NULL, "\"");
            char *argumento = NULL;

            if (token == NULL) {
                argumento = utils_remove_caracteres_inicio_e_fim(inicioArgumento, 0, 1);
            } else {
                char *fimArgumento = g_strdup(token);
                argumento = g_strconcat(inicioArgumento, " ", fimArgumento, NULL);
                g_free(fimArgumento);
            }

            g_ptr_array_add(comando->argumentos, argumento);
            g_free(inicioArgumento);
        } else {
            g_ptr_array_add(comando->argumentos, g_strdup(token));
        }

        token = strtok(NULL, " ");
    }

    return comando;
}

void comando_adiciona_argumento(Comando *comando, const char *novoArgumento) {
    if (comando && novoArgumento) {
        g_ptr_array_add(comando->argumentos, g_strdup(novoArgumento));
    }
}

void comando_set_numero_query(Comando *comando, int numeroComando) {
     comando->numeroDaQuery = numeroComando;
}

int comando_get_numero_query(Comando *comando) {
    return comando->numeroDaQuery;
}

const char *comando_get_separador(Comando *comando) {
    return comando->separador;
}

char *comando_get_argumento_por_indice(Comando *comando, int indice) {
    if (!comando || indice < 0 || indice >= (int)comando->argumentos->len) {
        return NULL;
    }
    return g_strdup(g_ptr_array_index(comando->argumentos, indice));
}

int comando_get_numero_comando(Comando *comando) {
    return  comando->numeroComando ;
}

void comando_set_numero_comando(Comando *comando, int numeroComando) {
    if (comando) {
        comando->numeroComando = numeroComando;
    }
}
