    // Link
    #include "../include/src/func8.h"
    /*
    * Função que realiza a busca de um registro na árvore B que contém o valor de um campo específico.
    */
    void func8() {
        // Cria a struct de arqBin
    arqBin *_arqBin = criaArqBin();

    // Faz a leitura do nome do arquivo
    scanf("%s", _arqBin->nomeBin);

    // Abrir arquivo
    if (abrirArqBin(_arqBin, 'r') == 1)
    {
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
    
    // Abre o arquivo
    _arvoreb->abrirArquivo(_arvoreb, _arvoreb->_arq->nomeBin);

    // Cria um cabecario
    arvorebCabecalho *_arvbCab;
    criaArvorebCabecalho(&_arvbCab);

    _arvoreb->leCabecalho(_arvoreb, _arvbCab);

    // Verifica se a arvoreb esta inconsistente
    if (_arvbCab->status == '0')
    {
        printf("Falha no processamento do arquivo.\n");

        // Fechar arquivo
        fecharArqBin(_arqBin);

        // Termina a funcao
        destroiCabecalho(&_cabecalho);
        destroiArqBin(&_arqBin);

        return;
    }

    // Leitura do nome do campo
    char campo[100];
    scanf("%s", campo);

    // Leitura do valor do campo
    char valor[100];
    scan_quote_string(valor);

    // Converte o valor para long
    long int valorLong = converteNome(valor);
    
    // Pesquisa o valor na arvoreb
    arvorebElemento _arvbEle;
    int j = _arvoreb->pesquisaChave(_arvoreb, valorLong, &_arvbEle);

    // Verifica se o valor foi encontrado

    if (j == 1)
    {
        printf("Registro inexistente.\n");
        return;

    }

    // Cria um registro
    registro *_registro = criaRegistro();

    // Encontra a posicao do registro e o le
    fseek(_arqBin->_file, _arvbEle.pr, SEEK_SET);
    leRegistro(_arqBin, _registro);

    // Imprime o registro
    printRegistro(_registro);
    // Destroi registro da memoria
    destroiRegistro(&_registro);

    // Fechar arquivo binario lido
    fecharArqBin(_arqBin);

    fecharArqBin(_arvoreb->_arq);

    // Destroi cabecalho da arvoreb
    destroiArvorebCabecalho(&_arvbCab);

    // Destroi arvoreb
    destroiArvoreb(&_arvoreb);

    }
