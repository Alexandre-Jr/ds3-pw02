#include <stdio.h>
#include "./include/src/func1.h"
#include "./include/src/func2.h"
#include "./include/src/func3.h"
#include "./include/src/func4.h"
#include "./include/src/func5.h"
#include "./include/src/func6.h"

#include "./include/src/structs/arvoreb.h"



long converteNome(char* str) {
    /* O registro que tem essa string como chave foi removido */
    if(str[0] == '*')
        return -1;

    /* Começamos com o primeiro digito na ordem de 6^0 = 1 */
    long power = 1;

    /* Faz a conversão char por char para chegar ao resultado */
    long result = 0;
    for(int i = 0; i < strlen(str); i++) {
        int cur_digit;
        /* Checa pelas letras minúsculas e as converte para números */
        if(str[i] >= 'a' && str[i] <= 'z')
            cur_digit = str[i] - 'a';
        /* Checa pelas letras maiúsculas e as converte para números */
        else if(str[i] >= 'A' && str[i] <= 'Z')
            cur_digit = str[i] - 'A';

        /*
            Multiplica o digito atual pelo ordem da posição atual
            e adiciona no resultado
            Primeira posição:   6^0 = 1
            Segunda posição:    6^1 = 6
            Terceira posição:   6^2 = 36
            Quarta posição:     6^3 = 216
            Quinta posição:     6^4 = 1.296
        */
        result += cur_digit * power;

        /* Aumenta a ordem atual */
        power *= 6;
    }

    return result;
}

void func7() {

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

  // Cria a estrutura da arvoreb
  arvoreb * _arvoreb;
  criaArvoreb(&_arvoreb);

  // Faz a leitura do nome destino da arvoreb
  scanf("%s", _arvoreb->_arq->nomeBin);

  // Cria um arquivo da arvoreb
  _arvoreb->criaArquivoArvoreb(_arvoreb, _arvoreb->_arq->nomeBin);

  // Abre o arquivo
  _arvoreb->abrirArquivo(_arvoreb, _arvoreb->_arq->nomeBin);

  
  // Cria um cabecario
  arvorebCabecalho * _arvbCab;
  criaArvorebCabecalho(&_arvbCab);

  _arvbCab->status = '0';
  _arvbCab->RRNproxNo = 0;
  _arvbCab->noRaiz = 0;

  _arvoreb->insereCabecalho(_arvoreb, _arvbCab);




  // Faz a varredura no numero de registros
  for (int i = 0; i < NumeroReg; i++) {
    // Encontra a posicao do registro
    fseek(_arqBin->_file, i * TAMANHO_REGISTRO + TAMANHO_PAG, SEEK_SET);

    // Cria registro
    registro *_registro = criaRegistro();

    // Le registro
    leRegistro(_arqBin, _registro);

    if(_registro->removido == '0') {
      // Cria um elemento da arvoreb
      arvorebElemento arvbEle;
      arvbEle.chave = converteNome(_registro->nome);
      arvbEle.pr = i * 160 + 1600; 

      int j = _arvoreb->insereElemento(_arvoreb, &arvbEle);

      printf("%d", j);
    }

    

    // Destroi registro da memoria
    destroiRegistro(&_registro);
  }

  // Finaliza a edicao na arvoreb
  _arvoreb->leCabecalho(_arvoreb, _arvbCab);
  
  _arvbCab->status = '1';

  _arvoreb->insereCabecalho(_arvoreb, _arvbCab);

  printArvoreb(_arvoreb);

  // Fechar arquivo binario lido
  fecharArqBin(_arqBin);

  fecharArqBin(_arvoreb->_arq);

  binarioNaTela(_arvoreb->_arq->nomeBin);

  // Termina a funcao
  destroiCabecalho(&_cabecalho);
  destroiArqBin(&_arqBin);


}

int main(void) {
  /*
  int opc;
  scanf("%d", &opc);
  switch (opc) {
  case 1:
    func1();
    break;
  case 2:
    func2();
    break;
  case 3:
    func3();
    break;
  case 4:
    func4();
    break;
  case 5:
    func5();
    break;
  case 6:
    func6();
    break;
  case 7:
    func7();
    break;
  }*/


  // Para Eler um arquivo indice arvore b
  /*
  arvoreb * _arvb;
  criaArvoreb(&_arvb);

  char v[] = "bin.bin";

  _arvb->abrirArquivo(_arvb, v);
  
  printArvoreb(_arvb);*/

  return 0;
}