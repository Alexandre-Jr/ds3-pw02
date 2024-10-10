// Link
#include "../include/src/func2.h"

// Faz a varredura dos registros do arquivo
void func2() {
  // Cria a struct de arqBin
  arqBin *_arqBin = criaArqBin();

  // Faz a leitura do nome do arquivo
  scanf("%s", _arqBin->nomeBin);

  // Abrir arquivo
  if (abrirArqBin(_arqBin, 'r') == 1) {
    printf("Falha no procesamento do arquivo.\n");

    // Fechar arquivo
    fecharArqBin(_arqBin);

    // Termina a funcao
    destroiArqBin(&_arqBin);

    return;
  }

  // Cria cabecalho
  cabecalho *_cabecalho = criaCabecalho();

  // Le cabecalho
  leCabecalho(_arqBin, _cabecalho);

  // Verifica se o arquivo não apresenta o aviso de inconsistente
  if (_cabecalho->status == '0') {
    printf("Falha no processamento do arquivo.\n");

    // Fechar arquivo
    fecharArqBin(_arqBin);

    // Termina a funcao
    destroiCabecalho(&_cabecalho);
    destroiArqBin(&_arqBin);

    return;
  }

  // Captura o tamanho do arquivo e o numero de paginas
  int tamArqBin = 0;
  tamanhoArqBin(_arqBin, &tamArqBin);

  int NumeroReg = (tamArqBin - TAMANHO_PAG) / TAMANHO_REGISTRO;
  int NumeroPag = ceil((float)tamArqBin / TAMANHO_PAG);

  if(NumeroReg == 0) { // Sem registros
    printf("Registro inexistente.\n");
    return;
  }

  // Faz a varredura no numero de registros
  for (int i = 0; i < NumeroReg; i++) {
    // Encontra a posicao do registro
    fseek(_arqBin->_file, i * TAMANHO_REGISTRO + TAMANHO_PAG, SEEK_SET);

    // Cria registro
    registro *_registro = criaRegistro();

    // Le registro
    leRegistro(_arqBin, _registro);

    // Printa registro
    printRegistro(_registro);

    // Destroi registro da memoria
    destroiRegistro(&_registro);
  }

  // Printa o numero de paginas
  printf("Numero de paginas de disco: %d", NumeroPag);
  printf("\n\n");

  // Fechar arquivo
  fecharArqBin(_arqBin);

  // Termina a funcao
  destroiCabecalho(&_cabecalho);
  destroiArqBin(&_arqBin);
}