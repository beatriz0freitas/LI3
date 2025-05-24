#include "gestor-de-quarks.h"

struct GestorDeQuarks {
    GHashTable *string_para_quark;
    GHashTable *quark_para_string;
    Quark proximo_quark;
};

// Gestor de quarks estático
static GestorDeQuarks *gestor = NULL;

static void gestor_de_quarks_inicializa() {
    if (gestor == NULL) {
        gestor = g_new(GestorDeQuarks, 1);
        gestor->string_para_quark = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);
        gestor->quark_para_string = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, g_free);
        gestor->proximo_quark = 1; 
    }
}

Quark quark_de_string(const char *string) {

    gestor_de_quarks_inicializa(); // chama sempre inicializa, mas gestor_de_quarks_inicializa so inicializa na primeira vez que é chamado

    gpointer quark_existente = g_hash_table_lookup(gestor->string_para_quark, string);

    if (quark_existente != NULL) {
        return GPOINTER_TO_UINT(quark_existente);
    }

    Quark quark = gestor->proximo_quark++;

    g_hash_table_insert(gestor->string_para_quark, g_strdup(string), GUINT_TO_POINTER(quark));
    g_hash_table_insert(gestor->quark_para_string, GUINT_TO_POINTER(quark), g_strdup(string));

    return quark;
}

const char *string_de_quark(Quark id) {
    gestor_de_quarks_inicializa();
    return g_hash_table_lookup(gestor->quark_para_string, GUINT_TO_POINTER(id));
}


void gestor_de_quarks_destroi() {
    if (gestor) {
        g_hash_table_destroy(gestor->string_para_quark);
        g_hash_table_destroy(gestor->quark_para_string);
        g_free(gestor);
        gestor = NULL;
    }
}

