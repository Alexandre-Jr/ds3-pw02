// Link
#include "../include/src/func9.h"
/*
 * Função que realiza a inserção de registros na árvore B.
 */
void func9() {

  // Cria a struct de arqBin
  arqBin *_arqBin = criaArqBin();

  // Faz a leitura do nome do arquivo
  scanf("%s", _arqBin->nomeBin);

  // Abrir arquivo
  if (abrirArqBin(_arqBin, 'r') == 1) {
    printf("Falha no processamento do arquivo.\n");

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

  // Verifica se o arquivo binario não apresenta o aviso de inconsistente
  if (_cabecalho->status == '0') {
    printf("Falha no processamento do arquivo.\n");

    // Fechar arquivo
    fecharArqBin(_arqBin);

    // Termina a funcao
    destroiCabecalho(&_cabecalho);
    destroiArqBin(&_arqBin);

    return;
  }

  if (_cabecalho->proxRRN == 0) { // Sem registros
    printf("Registro inexistente.\n");
    return;
  }

  // Cria a estrutura da arvoreb
  arvoreb *_arvoreb;
  criaArvoreb(&_arvoreb);

  // Faz a leitura do nome destino da arvoreb
  scanf("%s", _arvoreb->_arq->nomeBin);

  // Abre o arquivo
  _arvoreb->abrirArquivo(_arvoreb, _arvoreb->_arq->nomeBin);

  // Cria um cabecalho
  arvorebCabecalho *_arvbCab;
  criaArvorebCabecalho(&_arvbCab);

  _arvoreb->leCabecalho(_arvoreb, _arvbCab);

  // Verifica se a arvoreb esta inconsistente
  if (_arvbCab->status == '0') {
    printf("Falha no processamento do arquivo.\n");

    // Fechar arquivo
    fecharArqBin(_arqBin);

    // Termina a funcao
    destroiCabecalho(&_cabecalho);
    destroiArqBin(&_arqBin);

    return;
  }

  // Numero de registros a serem inseridos
  int n;
  scanf("%d", &n);

  // Altera o status do arquivo arvoreb para inconsistente
  _arvbCab->status = '0';

  _arvoreb->insereCabecalho(_arvoreb, _arvbCab);

  // Altera o status do arquivo binario para inconsistente
  _cabecalho->status = '0';

  escreveCabecalho(_arqBin, _cabecalho);

  // Variavel auxiliar para leitura
  char aux[100];

  // Leitura dos n registros a serem inseridos
  for (int i = 0; i < n; ++i) {
    // Cria um registro
    registro *_novo_registro = criaRegistro();
    // Leitura dos campos
    // Nome
    scan_quote_string(aux);
    _novo_registro->nome = (char *)malloc(strlen(aux) + 1);
    strncpy(_novo_registro->nome, aux, strlen(aux) + 1);

    // Dieta
    scan_quote_string(aux);
    if (strcmp(aux, "") == 0) {
      _novo_registro->dieta = NULL;
    } else {
      _novo_registro->dieta = (char *)malloc(strlen(aux) + 1);
      strncpy(_novo_registro->dieta, aux, strlen(aux) + 1);
    }

    // Habitat
    scan_quote_string(aux);
    if (strcmp(aux, "") == 0) {
      _novo_registro->habitat = NULL;
    } else {
      _novo_registro->habitat = (char *)malloc(strlen(aux) + 1);
      strncpy(_novo_registro->habitat, aux, strlen(aux) + 1);
    }

    // Populacao
    scan_quote_string(aux);
    if (strcmp(aux, "") == 0) {
      _novo_registro->populacao = -1;
    } else {
      _novo_registro->populacao = atoi(aux);
    }

    // Tipo
    scan_quote_string(aux);
    if (strcmp(aux, "") == 0) {
      _novo_registro->tipo = NULL;
    } else {
      _novo_registro->tipo = (char *)malloc(strlen(aux) + 1);
      strncpy(_novo_registro->tipo, aux, strlen(aux) + 1);
    }

    // Velocidade
    scan_quote_string(aux);
    if (strcmp(aux, "") == 0) {
      _novo_registro->velocidade = -1;
    } else {
      _novo_registro->velocidade = atoi(aux);
    }

    // Unidade de medida
    scan_quote_string(aux);
    if (strcmp(aux, "") == 0) {
      _novo_registro->unidadeMedida = '$';
    } else {
      _novo_registro->unidadeMedida = aux[0];
    }

    // Tamanho
    scan_quote_string(aux);
    if (strcmp(aux, "") == 0) {
      _novo_registro->tamanho = -1;
    } else {
      _novo_registro->tamanho = atof(aux);
    }

    // Especie
    scan_quote_string(aux);
    if (strcmp(aux, "") == 0) {
      _novo_registro->especie = NULL;
    } else {
      _novo_registro->especie = (char *)malloc(strlen(aux) + 1);
      strncpy(_novo_registro->especie, aux, strlen(aux) + 1);
    }

    // Alimento
    scan_quote_string(aux);
    if (strcmp(aux, "") == 0) {
      _novo_registro->alimento = NULL;
    } else {
      _novo_registro->alimento = (char *)malloc(strlen(aux) + 1);
      strncpy(_novo_registro->alimento, aux, strlen(aux) + 1);
    }

    // Insere o registro no arquivo
    inserirRegistro(_arqBin, _novo_registro,
                    (_cabecalho->proxRRN + i) * 160 + 1600);

    // Cria um elemento da arvoreb
    arvorebElemento arvbEle;

    arvbEle.chave = converteNome(_novo_registro->nome);
    arvbEle.pr = (_cabecalho->topo + i) * 160 + 1600;

    // Insere o elemento na arvoreb
    int j = _arvoreb->insereElemento(_arvoreb, &arvbEle);
    if (j == 1) {
      printf("Falha no processamento do arquivo.\n");
      return;
    }

    // Destroi registro da memoria
    destroiRegistro(&_novo_registro);
  }

  // Atualiza o cabecalho do arquivo binario
  _cabecalho->status = '1';
  _cabecalho->proxRRN += n;
  escreveCabecalho(_arqBin, _cabecalho);

  // Finaliza a edicao na arvoreb
  _arvbCab->status = '1';
  _arvoreb->insereCabecalho(_arvoreb, _arvbCab);

  // char arq[100] = "arvoreb_";
  // fprintArvoreb(_arvoreb, arq);

  // Fechar arquivo binario lido
  fecharArqBin(_arqBin);

  // Fechar arquivo arvoreb
  fecharArqBin(_arvoreb->_arq);

  // Imprime a arvoreb na tela
  binarioNaTela(_arvoreb->_arq->nomeBin);

  // Termina a funcao
  destroiCabecalho(&_cabecalho);
  destroiArqBin(&_arqBin);
}

void func5plus() {
  int n;
  arqBin *_arqBin = criaArqBin();
  char *nomeArvoreb = (char *)malloc(sizeof(char) * 100);

  // Cria a estrutura da arvoreb
  arvoreb *_arvoreb;
  criaArvoreb(&_arvoreb);

  // Cria um cabecario
  arvorebCabecalho *_arvbCab;
  criaArvorebCabecalho(&_arvbCab);
  _arvoreb->leCabecalho(_arvoreb, _arvbCab);

  // Entrada de dados
  scanf("%s", _arqBin->nomeBin);

  // Faz a leitura do nome destino da arvoreb e abre
  scanf("%s", _arvoreb->_arq->nomeBin);
  int i = _arvoreb->abrirArquivo(_arvoreb, _arvoreb->_arq->nomeBin);
  
  scanf("%d ", &n);
  // Abre o arquivo
  if (abrirArqBin(_arqBin, 's') != 0) {
    printf("Falha no processamento do arquivo.\n");
    return;
  }

  // Leitura do cabeçalho
  cabecalho cab;
  if (leCabecalho(_arqBin, &cab) != 0) {
    printf("Falha no processamento do arquivo.\n");
    return;
  }
  // Verifica se o arquivo não apresenta o aviso de inconsistente
  if (cab.status == '0') {
    printf("Falha no processamento do arquivo.\n");
    destroiArqBin(&_arqBin);
    return;
  }
  // variavel para armazenar registro
  registro *reg = criaRegistro();

  char lixo = '$';
  char campo[10][TAMANHO_CAMPO_VARIAVEL_MAXIMO];
  int tamanho_campo[10];

  // Itera n vezes
  for (int i = 0; i < n; ++i) {
    // Realiza a leitura do registro a ser inserido
    for (int j = 0; j < 10; ++j) {
      scan_quote_string(campo[j]);
      tamanho_campo[j] = strlen(campo[j]) + 1; // Conta o '\0'
    }
    // Aloca espaço e copia os valores para a struct
    // Nome
    reg->nome = (char *)malloc(tamanho_campo[0]);
    strncpy(reg->nome, campo[0], tamanho_campo[0]);

    // Dieta
    reg->dieta = (char *)malloc(tamanho_campo[1]);
    strncpy(reg->dieta, campo[1], tamanho_campo[1]);

    // Habitat
    reg->habitat = (char *)malloc(tamanho_campo[2]);
    strncpy(reg->habitat, campo[2], tamanho_campo[2]);

    // População
    if (strcmp(campo[3], "") == 0)
      reg->populacao = -1;
    else
      reg->populacao = atoi(campo[3]);

    // Tipo
    reg->tipo = (char *)malloc(tamanho_campo[4]);
    strncpy(reg->tipo, campo[4], tamanho_campo[4]);

    // Velocidade
    if (strcmp(campo[5], "") == 0)
      reg->velocidade = -1;
    else
      reg->velocidade = atoi(campo[5]);

    // UnidadeMedida
    if (strcmp(campo[6], "") == 0)
      reg->unidadeMedida = '$';
    else
      reg->unidadeMedida = campo[6][0];

    // Tamanho
    if (strcmp(campo[7], "") == 0)
      reg->tamanho = -1;
    else
      reg->tamanho = atof(campo[7]);

    // Especie
    reg->especie = (char *)malloc(tamanho_campo[8]);
    strncpy(reg->especie, campo[8], tamanho_campo[8]);

    // Alimento
    reg->alimento = (char *)malloc(tamanho_campo[9]);
    strncpy(reg->alimento, campo[9], tamanho_campo[9]);
    // Realiza a leitura do cabecalho
    leCabecalho(_arqBin, &cab);

    cab.status = '0'; // Modifica para escrita
    escreveCabecalho(_arqBin, &cab);
    // Verifica se a lista está vazia(sem campos removidos)
    if (cab.nroRegRem == 0) {
      // Dados padrões
      reg->encadeamento = -1;
      reg->removido = '0';
      // Insere no último registro(proxRRN)
      inserirRegistro(_arqBin, reg,
                      TAMANHO_PAG + cab.proxRRN * TAMANHO_REGISTRO);

      // Cria um elemento da arvoreb
      arvorebElemento arvbEle;
      arvbEle.chave = converteNome(reg->nome);
      arvbEle.pr = cab.proxRRN * 160 + 1600;

      int j = _arvoreb->insereElemento(_arvoreb, &arvbEle);

      // Incrementa o proxRRN
      ++cab.proxRRN;

      // Atualiza o número de paginas no disco
      cab.nroPagDisco =
          (cab.proxRRN * TAMANHO_REGISTRO + TAMANHO_PAG - 1) / TAMANHO_PAG + 1;
    } else {
      // Cria um registro auxiliar
      registro *regLido = criaRegistro();
      // Le o registro removido logicamente
      fseek(_arqBin->_file, TAMANHO_PAG + cab.topo * TAMANHO_REGISTRO,
            SEEK_SET);
      leRegistro(_arqBin, regLido);

      // Marca como não removido
      reg->encadeamento = -1;
      reg->removido = '0';

      // Insere no espaço removido
      inserirRegistro(_arqBin, reg, TAMANHO_PAG + cab.topo * TAMANHO_REGISTRO);


      // Cria um elemento da arvoreb
      arvorebElemento arvbEle;
      arvbEle.chave = converteNome(reg->nome);
      arvbEle.pr = (long int)cab.topo * 160 + 1600;

      int j = _arvoreb->insereElemento(_arvoreb, &arvbEle);

      // Atualiza o topo da lista
      cab.topo = regLido->encadeamento;

      // Diminui o número de registros removidos
      --cab.nroRegRem;

      // Destroi o registro auxiliar
      destroiRegistro(&regLido);
    }
    // Atualiza o cabecalho e finaliza a escrita
    cab.status = '1';
    escreveCabecalho(_arqBin, &cab);

    // Libera memória

    free(reg->nome);
    free(reg->especie);
    free(reg->habitat);
    free(reg->tipo);
    free(reg->dieta);
    free(reg->alimento);
  }
  // Fecha o binario
  fecharArqBin(_arqBin);

  // Fechar arquivo arvoreb
  fecharArqBin(_arvoreb->_arq);

  // Imprime a arvoreb na tela
  binarioNaTela(_arvoreb->_arq->nomeBin);

  free(reg);
}
