#include "ordenacao.h"

//funcao para comparacao de dois registros, levando em conta sua marcacao e sua nota
int compare(const RegistroParaSubstituicao registro1, const RegistroParaSubstituicao registro2) {
    //retornos: 1 = registro1 > registro2, 0 = registro1 <= registro2
    
    if(registro1.marcado == registro2.marcado)
        if(registro1.registro.nota > registro2.registro.nota)
            return 1;
        else
            return 0;

    else if(registro1.marcado && !registro2.marcado)
        return 1;

    //caso em que o primeiro nao é marcado, e o segundo é marcado
    return 0;
}

//QuickSort Interno:

void trocarPosicao(TipoRegistro* registro, int * i, int * j){
    TipoRegistro auxiliar;

    auxiliar = registro[*i];
    registro[*i] = registro[*j];
    registro[*j] = auxiliar;
    *i += 1;
    *j -= 1;
}

//quickSort utilizado na geracao de blocos por ordenacao
void quicksort_interno(TipoRegistro * registro, int inicio, int fim){
    int i, j;
    TipoRegistro pivo; 

    i = inicio;
    j = fim;
    pivo = registro[(inicio + fim) / 2];

    while (i <= j){
        while (registro[i].nota < pivo.nota && i < fim)
            i++;
        
        while (registro[j].nota > pivo.nota && j > inicio)
            j--;

        if (i <= j)
            trocarPosicao(registro, &i, &j);
    }

    if (j > inicio)
        quicksort_interno(registro, inicio, j);

    if (i < fim)
        quicksort_interno(registro, i, fim);
}

void trocarPosicao2(RegistroParaSubstituicao* registros, int * i, int * j){
    RegistroParaSubstituicao auxiliar;

    auxiliar = registros[*i];
    registros[*i] = registros[*j];
    registros[*j] = auxiliar;
    *i += 1;
    *j -= 1;

}

//quickSort utilizado na geracao de blocos utilizando selecao por substituicao
void quicksort_interno_SelecaoSubs(RegistroParaSubstituicao * registros, int inicio, int fim){
    int i, j;
    RegistroParaSubstituicao pivo; 

    i = inicio;
    j = fim;
    pivo = registros[(inicio + fim) / 2];

    while (i <= j){
        //enquanto registros[i] < pivo
        while (compare(pivo, registros[i]) && i < fim)
            i++;
        
        //enquanto registros[j] > pivo
        while (compare(registros[j], pivo) && j > inicio)
            j--;

        if (i <= j)
            trocarPosicao2(registros, &i, &j);
    }

    if (j > inicio)
        quicksort_interno_SelecaoSubs(registros, inicio, j);

    if (i < fim)
        quicksort_interno_SelecaoSubs(registros, i, fim);
}