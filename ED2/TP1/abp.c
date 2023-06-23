#include "abp.h"

void constroiArvore(FILE * arq, FILE *arqAbp){

    TipoRegistro itemLeitura;

    //Lê os dados do arquivo original e passa para o arquivo da arvore binaria de pesquisa
    while ((fread(&itemLeitura, sizeof(TipoRegistro), 1, arq)) != 0){
        TipoItem itemInserir;
        itemInserir.item = itemLeitura;
        itemInserir.dir = -1;
        itemInserir.esq = -1;

        fseek(arqAbp, 0, SEEK_END);
        fwrite(&itemInserir, sizeof(TipoItem), 1, arqAbp);
        atualizaPonteiros(arqAbp, &itemInserir);
    }
}


void atualizaPonteiros(FILE *arq, TipoItem *itemInserir)
{
    // Verificando a quantidade de itens no arquivo
    fseek(arq, 0, SEEK_END);
    long qtdItensArquivo = ftell(arq) / sizeof(TipoItem);
    fseek(arq, 0, SEEK_SET);

    //Nao e necessario atualizar ponteiros quando tem-se apenas um item
    if(qtdItensArquivo == 1) return;
    
    TipoItem aux;
    
    //Caminhando o ponteiro do arquivo ate o local onde devera alterar o ponteiro da arvore
    long ponteiro = 1;
    long desloc;
    
    //procura o ponteiro que precisa ser atualizado com o numero da linha do item que foi inserido
    do{
        //Calcula o deslocamento necessario, a partir do horario_inicio do arquivo, para chegar ao nó filho do pai
        desloc = (ponteiro - 1) * sizeof(TipoItem);
        fseek(arq, desloc, SEEK_SET);
        fread(&aux, sizeof(TipoItem), 1, arq);
        //Caminhando o ponteiro pelo arquivo ate encontrar uma "folha" = (-1)
        ponteiro = (itemInserir->item.Chave > aux.item.Chave) ? aux.dir : aux.esq;

    }while(ponteiro != -1);

    //Voltando uma posicao para tratar o "no" correto
    fseek(arq, -(sizeof(TipoItem)), SEEK_CUR);
    
    //Compara novamente as chaves para a insercao da linha
    if(itemInserir->item.Chave > aux.item.Chave) 
        aux.dir = qtdItensArquivo;
    else
        aux.esq = qtdItensArquivo;   
    fwrite(&aux, sizeof(TipoItem), 1, arq); //insere a linha
    return;
}

bool pequisarAbp(FILE *arq, TipoRegistro *pesquisado){
    TipoItem aux;

    long ponteiro = 1;
    long desloc;
    
    do{
        //Calcula o deslocamento necessario, a partir do horario_inicio do arquivo, para chegar ao no filho do pai
        desloc = (ponteiro - 1) * sizeof(TipoItem);
        fseek(arq, desloc, SEEK_SET);
        fread(&aux, sizeof(TipoItem), 1, arq);
        //Caminhando o ponteiro pelo arquivo ate encontrar uma "folha" = (-1)
        if(pesquisado->Chave == aux.item.Chave){
            *pesquisado = aux.item;
            return true;
        }
        ponteiro = (pesquisado->Chave > aux.item.Chave) ? aux.dir : aux.esq;

    }while(ponteiro != -1);
    
    return false;
}

bool arvore_binaria_de_pesquisa(char * nomeArquivo, Resultados * resultados){

    FILE *arq = fopen(nomeArquivo, "rb");
    if (arq == NULL){
        printErr("Erro na abertura do arquivo para construção da árovre\n");
        return false;
    }

    FILE *arqAbp = fopen("abp.bin", "wb+"); 
    if (arqAbp == NULL){
        printErr("Erro na abertura do arquivo\n");
        fclose(arq);
        return false;
    }

    constroiArvore(arq, arqAbp);

    resultados->horario_inicio = clock();

    fseek(arq, 0, SEEK_SET);
    fseek(arqAbp, 0, SEEK_SET);

    //Pesquisando    
    bool resultado = pequisarAbp(arqAbp, &(resultados->pesquisar));

    fclose(arq);
    fclose(arqAbp);

    resultados->horario_fim = clock();

    return resultado;
}