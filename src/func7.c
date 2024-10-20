// Link
#include "../include/src/func7.h"

void func7()
{

  // Cria a struct de arqBin
  arqBin *_arqBin = criaArqBin();

  // Faz a leitura do nome do arquivo
  scanf("%s", _arqBin->nomeBin);

  // Abrir arquivo
  if (abrirArqBin(_arqBin, 'r') == 1)
  {
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
  if (_cabecalho->status == '0')
  {
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

  if (NumeroReg == 0)
  { // Sem registros
    printf("Registro inexistente.\n");
    return;
  }

  // Cria a estrutura da arvoreb
  arvoreb *_arvoreb;
  criaArvoreb(&_arvoreb);

  // Faz a leitura do nome destino da arvoreb
  scanf("%s", _arvoreb->_arq->nomeBin);

  // Cria um arquivo da arvoreb
  _arvoreb->criaArquivoArvoreb(_arvoreb, _arvoreb->_arq->nomeBin);

  // Abre o arquivo
  _arvoreb->abrirArquivo(_arvoreb, _arvoreb->_arq->nomeBin);

  // Cria um cabecario
  arvorebCabecalho *_arvbCab;
  criaArvorebCabecalho(&_arvbCab);

  _arvbCab->status = '0';
  _arvbCab->RRNproxNo = 0;
  _arvbCab->noRaiz = 0;

  _arvoreb->insereCabecalho(_arvoreb, _arvbCab);

  // Faz a varredura no numero de registros
  for (int i = 0; i < NumeroReg; i++)
  {
    // Encontra a posicao do registro
    fseek(_arqBin->_file, i * TAMANHO_REGISTRO + TAMANHO_PAG, SEEK_SET);

    // Cria registro
    registro *_registro = criaRegistro();

    // Le registro
    leRegistro(_arqBin, _registro);

    if (_registro->removido == '0')
    {
      // Cria um elemento da arvoreb
      arvorebElemento arvbEle;
      arvbEle.chave = converteNome(_registro->nome);
      arvbEle.pr = i * 160 + 1600;

      int j = _arvoreb->insereElemento(_arvoreb, &arvbEle);
    }

    // Destroi registro da memoria
    destroiRegistro(&_registro);
  }

  // Finaliza a edicao na arvoreb
  _arvoreb->leCabecalho(_arvoreb, _arvbCab);

  _arvbCab->status = '1';

  _arvoreb->insereCabecalho(_arvoreb, _arvbCab);

  // Debug
  // printArvoreb(_arvoreb);

  // Fechar arquivo binario lido
  fecharArqBin(_arqBin);

  fecharArqBin(_arvoreb->_arq);

  binarioNaTela(_arvoreb->_arq->nomeBin);

  // Termina a funcao
  destroiCabecalho(&_cabecalho);
  destroiArqBin(&_arqBin);
}