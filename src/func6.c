// Link
#include "../include/src/func6.h"

// Funcao principal da funcionalidade de busca
void func6() {

    // Cria a struct de arqBin
    arqBin * _arqBinFonte = criaArqBin();
    arqBin * _arqBinCompactado = criaArqBin();

    // Faz a leitura do nome do arquivo fonte
    scanf("%s", _arqBinFonte->nomeBin);

    // Cria o nome do arquivo compactado
    char nomeArquivoCompactado[] = "comp.bin\0";
    strcpy(_arqBinCompactado->nomeBin, nomeArquivoCompactado);

    // Abrir arquivo fonte
    if (abrirArqBin(_arqBinFonte, 'r') == 1) {
        printf("Falha no processamento do arquivo.\n");

        // Fechar arquivo
        fecharArqBin(_arqBinFonte);

        // Termina a funcao
        destroiArqBin(&_arqBinFonte);

        return;
    }

    // Cria o arquivo destino
    criarArquivo(_arqBinCompactado);

    // Abre arquivo destino de compactado
    abrirArqBin(_arqBinCompactado, 's');

    // Le o cabecalho fonte
    cabecalho * _cabecalhoFonte = criaCabecalho();
    leCabecalho(_arqBinFonte, _cabecalhoFonte);

    // Verifica se o arquivo não apresenta o aviso de inconsistente
    if (_cabecalhoFonte->status == '0') {
        printf("Falha no processamento do arquivo.");

        // Fechar arquivo
        fecharArqBin(_arqBinFonte);
        fecharArqBin(_arqBinCompactado);
        // Termina a funcao
        destroiCabecalho(&_cabecalhoFonte);
        destroiArqBin(&_arqBinFonte);
        destroiArqBin(&_arqBinCompactado);
        return;
    }

    // Captura o tamanho do arquivo e o numero de paginas
    int tamArqBin = 0;
    tamanhoArqBin(_arqBinFonte, &tamArqBin);

    int NumeroRegFonte = (tamArqBin - TAMANHO_PAG) / TAMANHO_REGISTRO;
    int NumeroPagFonte = ceil((float) tamArqBin / TAMANHO_PAG);

    // Cria o cabecalho do destino
    cabecalho * _cabecalhoCompactado = criaCabecalho();
    _cabecalhoCompactado->status = 0;
    _cabecalhoCompactado->topo = -1;
    _cabecalhoCompactado->proxRRN = 0;
    _cabecalhoCompactado->nroRegRem = 0;
    _cabecalhoCompactado->nroPagDisco = 0;
    _cabecalhoCompactado->qttCompacta = _cabecalhoFonte->qttCompacta + 1;
    // Escreve cabecalho no arquivo destino
    escreveCabecalho(_arqBinCompactado, _cabecalhoCompactado);

    // Variavel do numero de registros adicionados
    int nRegAdic = 0;

    fseek(_arqBinCompactado->_file, 0, SEEK_SET);
    // Faz a varredura no numero de registros do arquivo fonte
    for(int i = 0; i < NumeroRegFonte; i++) {
         // Encontra a posicao do registro
        fseek(_arqBinFonte->_file, i * TAMANHO_REGISTRO + TAMANHO_PAG, SEEK_SET);

        // Cria registro
        registro * _registro = criaRegistro();
        // Le registro
        leRegistro(_arqBinFonte, _registro);        

        if (_registro->removido == '0') {
            fseek(_arqBinCompactado->_file, nRegAdic * TAMANHO_REGISTRO + TAMANHO_PAG, SEEK_SET);
            inserirRegistro(_arqBinCompactado, _registro, nRegAdic * TAMANHO_REGISTRO + TAMANHO_PAG);
            nRegAdic++;
        }

        // Destroi registro da memoria
        destroiRegistro(&_registro);
    }

    // Captura o tamanho do arquivo e o numero de paginas
    int tamArqBinCompactado = 0;
    tamanhoArqBin(_arqBinCompactado, &tamArqBinCompactado);

    int NumeroRegCompactado = (tamArqBinCompactado - TAMANHO_PAG) / TAMANHO_REGISTRO;
    int NumeroPagCompactado = ceil((float) tamArqBinCompactado / TAMANHO_PAG);

    // Atualiza cabecalho
    _cabecalhoCompactado->status = '1';
    _cabecalhoCompactado->topo = -1;
    _cabecalhoCompactado->proxRRN = nRegAdic;
    _cabecalhoCompactado->nroRegRem = 0;
    _cabecalhoCompactado->nroPagDisco = NumeroPagCompactado;

    escreveCabecalho(_arqBinCompactado, _cabecalhoCompactado);


    // Fechar arqBin
    fecharArqBin(_arqBinCompactado);

    // Feedback
    binarioNaTela(_arqBinCompactado->nomeBin);

    // Libera memória do cabecalho
    destroiCabecalho(&_cabecalhoFonte);
    destroiCabecalho(&_cabecalhoCompactado);

    //Desalocar arqBin
    destroiArqBin(&_arqBinFonte);
    destroiArqBin(&_arqBinCompactado);
}