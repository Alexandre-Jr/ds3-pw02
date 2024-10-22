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

    printArvoreb(_arvoreb);

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

    // Leitura dos registros a serem inseridos
    for(int i = 0; i < n; ++i) {
        // Cria um registro
        registro *_novo_registro = criaRegistro();
        // Leitura dos campos
        // Nome
        scan_quote_string(aux);
        _novo_registro->nome = (char *) malloc(strlen(aux) + 1);
        strncpy(_novo_registro->nome, aux, strlen(aux) + 1);

        // Dieta
        scan_quote_string(aux);
        if(strcmp(aux, "NULO") == 0) {
            _novo_registro->dieta = NULL;
        } else {
            _novo_registro->dieta = (char *) malloc(strlen(aux) + 1);
            strncpy(_novo_registro->dieta, aux, strlen(aux) + 1);
        }

        // Habitat
        scan_quote_string(aux);
        if(strcmp(aux, "NULO") == 0) {
            _novo_registro->habitat = NULL;
        } else {
            _novo_registro->habitat = (char *) malloc(strlen(aux) + 1);
            strncpy(_novo_registro->habitat, aux, strlen(aux) + 1);
        }

        // Populacao
        scan_quote_string(aux);
        if(strcmp(aux, "NULO") == 0) {
            _novo_registro->populacao = -1;
        } else {
            _novo_registro->populacao = atoi(aux);
        }

        // Tipo
        scan_quote_string(aux);
        if(strcmp(aux, "NULO") == 0) {
            _novo_registro->tipo = NULL;
        } else {
            _novo_registro->tipo = (char *) malloc(strlen(aux) + 1);
            strncpy(_novo_registro->tipo, aux, strlen(aux) + 1);
        }

        // Velocidade
        scan_quote_string(aux);
        if(strcmp(aux, "NULO") == 0) {
            _novo_registro->velocidade = -1;
        } else {
            _novo_registro->velocidade = atof(aux);
        }

        // Unidade de medida
        scan_quote_string(aux);
        if(strcmp(aux, "NULO") == 0) {
            _novo_registro->unidadeMedida = '$';
        } else {
            _novo_registro->unidadeMedida = aux[0];
        }

        // Tamanho
        scan_quote_string(aux);
        if(strcmp(aux, "NULO") == 0) {
            _novo_registro->tamanho = -1;
        } else {
            _novo_registro->tamanho = atof(aux);
        }

        // Especie
        scan_quote_string(aux);
        if(strcmp(aux, "NULO") == 0) {
            _novo_registro->especie = NULL;
        } else {
            _novo_registro->especie = (char *) malloc(strlen(aux) + 1);
            strncpy(_novo_registro->especie, aux, strlen(aux) + 1);
        }

        // Alimento
        scan_quote_string(aux);
        if(strcmp(aux, "NULO") == 0) {
            _novo_registro->alimento = NULL;
        } else {
            _novo_registro->alimento = (char *) malloc(strlen(aux) + 1);
            strncpy(_novo_registro->alimento, aux, strlen(aux) + 1);
        }
        printRegistro(_novo_registro);
        //Insere o registro no arquivo
        inserirRegistro(_arqBin, _novo_registro, (i + NumeroReg) * 160 + 1600);
        printf("Registro inserido com sucesso.\n");
        // Cria um elemento da arvoreb
        arvorebElemento arvbEle;
        
        arvbEle.chave = converteNome(_novo_registro->nome);
        arvbEle.pr = (i + NumeroReg) * 160 + 1600;
        printf("%ld %ld\n", arvbEle.chave, arvbEle.pr);
        int j = _arvoreb->insereElemento(_arvoreb, &arvbEle);
        if(j == 1) {
            printf("Falha no processamento do arquivo.\n");
            return;
        }
        printf("Elemento inserido com sucesso.\n");
        // Destroi registro da memoria
        destroiRegistro(&_novo_registro);
    }
    // Atualiza o cabecalho do arquivo binario
    _cabecalho->status = '1';
    _cabecalho->proxRRN = NumeroReg + n;
    escreveCabecalho(_arqBin, _cabecalho);

    // Finaliza a edicao na arvoreb
    _arvoreb->leCabecalho(_arvoreb, _arvbCab);
    _arvbCab->status = '1';
    _arvoreb->insereCabecalho(_arvoreb, _arvbCab);
    //printArvoreb(_arvoreb);
    // Fechar arquivo binario lido
    fecharArqBin(_arqBin);

    fecharArqBin(_arvoreb->_arq);

    binarioNaTela(_arvoreb->_arq->nomeBin);

    // Termina a funcao
    destroiCabecalho(&_cabecalho);
    destroiArqBin(&_arqBin);
}
