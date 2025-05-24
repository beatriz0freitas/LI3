#include <assert.h>
#include "utils.h"
#include "utilizador.h"



//  testar a função utils_calcula_idade
void test_idadeDoUtilizador() {
    printf("Teste unitário da função utils_calcula_idade\n");

    // input the teste
    GDate *dataNascimentoDoUtilizador;
    g_date_set_dmy(dataNascimentoDoUtilizador, 10, 10, 1990);

    // valores esperados
    int resultadoEsperado = 33;

    // chamada da função
    int resultado = utils_calcula_idade(dataNascimentoDoUtilizador);

    // fazer assert
    assert(resultado == resultadoEsperado);
}

// função de testes utils_remove_caracteres_inicio_e_fim
void test_removeCaracteresNoInicioEFim() {
    printf("Teste unitário da função utils_remove_caracteres_inicio_e_fim\n");

    // input the teste
    char *stringTeste = "12345";

    // valores esperados
    char *resultadoEsperado = "23";

    // chamada da função
    char *resultado = utils_remove_caracteres_inicio_e_fim(stringTeste, 1, 2);

    // fazer assert
    assert(strcmp(resultado, resultadoEsperado) == 0);
}


void test_numeroSemanaJuliana() {
    printf("Teste unitário da função utils_calcular_numero_semana_juliana\n");

    GDate *dataDomingo = g_date_new_dmy(22, 12, 2024);
    GDate *dataSegunda = g_date_new_dmy(23, 12, 2024);
    GDate *dataTerca = g_date_new_dmy(24, 12, 2024);
    GDate *dataQuarta = g_date_new_dmy(25, 12, 2024);
    GDate *dataQuinta = g_date_new_dmy(26, 12, 2024);
    GDate *dataSexta = g_date_new_dmy(27, 12, 2024);
    GDate *dataSabado = g_date_new_dmy(28, 12, 2024);


    int resultadoEsperado = utils_calcular_numero_semana_juliana(dataDomingo);

    int resultadoDomingo = utils_calcular_numero_semana_juliana(dataDomingo);
    assert(resultadoDomingo == resultadoEsperado);

    int resultadoSegunda = utils_calcular_numero_semana_juliana(dataSegunda);
    assert(resultadoSegunda == resultadoEsperado);

    int resultadoTerca = utils_calcular_numero_semana_juliana(dataTerca);
    assert(resultadoTerca == resultadoEsperado);

    int resultadoQuarta = utils_calcular_numero_semana_juliana(dataQuarta);
    assert(resultadoQuarta == resultadoEsperado);

    int resultadoQuinta = utils_calcular_numero_semana_juliana(dataQuinta);
    assert(resultadoQuinta == resultadoEsperado);

    int resultadoSexta = utils_calcular_numero_semana_juliana(dataSexta);
    assert(resultadoSexta == resultadoEsperado);

    int resultadoSabado = utils_calcular_numero_semana_juliana(dataSabado);
    assert(resultadoSabado == resultadoEsperado);

    g_date_free(dataSabado);
    g_date_free(dataDomingo);
    g_date_free(dataSegunda);
    g_date_free(dataTerca);
    g_date_free(dataQuarta);
    g_date_free(dataQuinta);
    g_date_free(dataSexta);

    printf("test_numeroSemanaJuliana OK!\n");
}


// função de testes utils_calcular_numero_semana_juliana
void test_mudancaSemanaJuliana() {
    
    printf("Teste de mudança de semana na função utils_calcular_numero_semana_juliana\n");

    GDate *sabado = g_date_new_dmy(21, 12, 2024); // Sábado, 21 de dezembro de 2024
    GDate *domingo = g_date_new_dmy(22, 12, 2024); // Domingo, 22 de dezembro de 2024

    int semanaSabado = utils_calcular_numero_semana_juliana(sabado);
    int semanaDomingo = utils_calcular_numero_semana_juliana(domingo);

    printf("Sábado (21/12/2024): Semana %d\n", semanaSabado);
    printf("Domingo (22/12/2024): Semana %d\n", semanaDomingo);

    assert(semanaDomingo == semanaSabado + 1); // O domingo deve estar na próxima semana

    g_date_free(sabado);
    g_date_free(domingo);

    printf("test_mudancaSemanaJuliana OK!\n");
}



int main(int argc, char *argv[]) {

    // Testes unitarios
    test_removeCaracteresNoInicioEFim();
    test_idadeDoUtilizador();
    test_numeroSemanaJuliana();
    test_mudancaSemanaJuliana();

    return 0;
}