#include "input.h"

struct Input
{
    FILE *ficheiroInput;
};

Input *input_novo(char *caminhoFicheiro)
{
    Input *input = g_new(Input, 1);
    input->ficheiroInput = fopen(caminhoFicheiro, "r");

    if (input->ficheiroInput == NULL)
    {
        perror("Erro ao abrir o ficheiro de input");
        return NULL;
    }

    return input;
}

void input_destroi(Input *input)
{
    fclose(input->ficheiroInput);
    g_free(input);
}

gboolean input_proxima_linha(Input *input, char **linha)
{
    ssize_t caracteresLidos = 0;
    size_t tamanhoBuffer=0;
    caracteresLidos = getline(linha, &tamanhoBuffer, input->ficheiroInput);
    if (caracteresLidos == -1){
        return FALSE;
    }
    return TRUE;
}
