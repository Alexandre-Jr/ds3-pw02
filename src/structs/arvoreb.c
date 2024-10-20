// Link com o header file
#include "../../include/src/structs/arvoreb.h"




// Funcoes da arvorebRegistro

// Cria a estrutura arvorebRegistro e aloca o espaco necessario (retorna 1 - erro e retorna 0 - sucesso)
int criaArvorebRegistro(arvorebRegistro ** __arvorebRegistro) {
    // Aloca memoria e verifica
    (*__arvorebRegistro)  = (arvorebRegistro *) malloc(sizeof(arvorebRegistro));

    if (*__arvorebRegistro == NULL) return 1;

    // Aloca a lista de elementos e verifica
    (*__arvorebRegistro)->elementos = (arvorebElemento *) malloc(sizeof(arvorebElemento) * (ORDEM_ARVOREB - 1));

    if ((*__arvorebRegistro)->elementos == NULL) {
        free(*__arvorebRegistro);
        *__arvorebRegistro = NULL;

        return 1;
    }

    // Aloca a lista de elementos e verifica
    (*__arvorebRegistro)->ponteiros = (int *) malloc(sizeof(long int) * (ORDEM_ARVOREB));

    if ((*__arvorebRegistro)->ponteiros == NULL) {
        free(*__arvorebRegistro);
        *__arvorebRegistro = NULL;

        free((*__arvorebRegistro)->elementos );
        (*__arvorebRegistro)->elementos  = NULL;

        return 1;
    }

    // Insere os valores padroes iniciais
    (*__arvorebRegistro)->folha = '0';
    (*__arvorebRegistro)->nroChavesNo = 0;
    (*__arvorebRegistro)->RRNdoNo = 0;

    // Limpa a lista de ponteiros e elementos
    for (int i = 0; i < ORDEM_ARVOREB; i++) {
        (*__arvorebRegistro)->ponteiros[i] = -1;
    }

    // Limpa a lista de elementos e elementos
    for (int i = 0; i < ORDEM_ARVOREB - 1; i++) {
        (*__arvorebRegistro)->elementos[i].chave = -1;
        (*__arvorebRegistro)->elementos[i].pr = -1;
    }

    return 0;
}

// Limpa a estrutura arvorebRegistro, mas nao desaloca o espaco necessario (retorna 1 - erro e retorna 0 - sucesso)
int limpaArvorebRegistro(arvorebRegistro * _arvorebRegistro) {
    
    // Verifica se o arvorebRegistro existe
    if (_arvorebRegistro == NULL) {
        return 1;
    }


    // Insere os valores padroes iniciais
    (_arvorebRegistro)->folha = '0';
    (_arvorebRegistro)->nroChavesNo = 0;
    (_arvorebRegistro)->RRNdoNo = 0;

    // Limpa a lista de ponteiros e elementos
    for (int i = 0; i < ORDEM_ARVOREB; i++) {
        (_arvorebRegistro)->ponteiros[i] = -1;
    }

    // Limpa a lista de elementos e elementos
    for (int i = 0; i < ORDEM_ARVOREB - 1; i++) {
        (_arvorebRegistro)->elementos[i].chave = -1;
        (_arvorebRegistro)->elementos[i].pr = -1;
    }

    return 0;
}

// Destroi a estrutura arvorebRegistro e desaloca o espaco necessario (retorna 1 - erro e retorna 0 - sucesso)
int destroiArvorebRegistro(arvorebRegistro ** __arvorebRegistro) {

    if (__arvorebRegistro == NULL || (*__arvorebRegistro)->elementos == NULL || (*__arvorebRegistro)->ponteiros == NULL) {
        return 1;
    }

    free((*__arvorebRegistro)->ponteiros);
    (*__arvorebRegistro)->ponteiros = NULL;

    free((*__arvorebRegistro)->elementos);
    (*__arvorebRegistro)->elementos = NULL;

    free((*__arvorebRegistro));
    (*__arvorebRegistro) = NULL;

    return 0;
}


// Funcoes da arvorebCabecalho

// Cria a estrutura arvorebCabecalho e aloca o espaco necessario (retorna 1 - erro e retorna 0 - sucesso)
int criaArvorebCabecalho(arvorebCabecalho ** __arvorebCabecalho) {
    // Aloca memoria e verifica
    (*__arvorebCabecalho) = (arvorebCabecalho*) malloc (sizeof(arvorebCabecalho));

    if (*__arvorebCabecalho == NULL) return 1;
    

    // Insere valores padroes iniciais;
    (*__arvorebCabecalho)->status = '0';
    (*__arvorebCabecalho)->noRaiz = 0;
    (*__arvorebCabecalho)->RRNproxNo = 0;

    return 0;
}

// Destroi a estrutura arvorebCabecalho e desaloca o espaco necessario (retorna 1 - erro e retorna 0 - sucesso)
int destroiArvorebCabecalho(arvorebCabecalho ** __arvorebCabecalho) {
    if (*__arvorebCabecalho == NULL) {
        return 1;
    }

    free(*__arvorebCabecalho);
    *__arvorebCabecalho = NULL;

    return 0;
}


// Funcoes da arvoreb

// Abrir o arquivo da arvoreb (retorna 1 - erro e retorna 0 - sucesso)
int arvoreb_abrirArquivo(arvoreb * _arvoreb, char * nomeArquivo) {
    // Copia nome para a estrutura
    strcpy(_arvoreb->_arq->nomeBin, nomeArquivo);

    return abrirArqBin(_arvoreb->_arq, 's');
}

// Fecha o arquivo da arvoreb (retorna 1 - erro e retorna 0 - sucesso)
int arvoreb_fecharArquivo(arvoreb * _arvoreb) {
    return fecharArqBin(_arvoreb->_arq);
}

// Destroi a estrutura arvoreb e desaloca o espaco necessario (retorna 1 - erro e retorna 0 - sucesso)
int arvoreb_criaArquivoArvoreb(arvoreb * _arvoreb, char * nomeArquivo) {
    // Copia nome para a estrutura
    strcpy(_arvoreb->_arq->nomeBin, nomeArquivo);


    // Cria arquivo
    if (abrirArqBin(_arvoreb->_arq, 'w') == 1) {
        return 1;
    }


    // Fecha o arquivo aberto
    return fecharArqBin(_arvoreb->_arq);
}


// Insere o cabecalho no arquivo arvoreb (retorna 1 - erro e retorna 0 - sucesso)
int arvoreb_insereCabecalho(arvoreb * _arvoreb, arvorebCabecalho * _arvorebCabecalho) {
    // Teste de erro, verifica se o arquivo foi aberto e se o cabecalho existe
    if (_arvoreb->_arq->estado == '0' || _arvorebCabecalho == NULL) {
        return 1;
    }

    // Vai ate o inicio do arquivo
    fseek(_arvoreb->_arq->_file, 0, SEEK_SET);


    // Escreve o lixo
    char charLixo = '$';
    for (int i = 0; i < TAMANHO_PAG_ARVOREB; i++) {
        fwrite(&charLixo, sizeof(char), 1, _arvoreb->_arq->_file);
    }

    // Vai ate o inicio do arquivo
    fseek(_arvoreb->_arq->_file, 0, SEEK_SET);
    
    // Escreve os campos do cabecalho
    fwrite(&_arvorebCabecalho->status, sizeof(char), 1, _arvoreb->_arq->_file);
    fwrite(&_arvorebCabecalho->noRaiz, sizeof(int), 1, _arvoreb->_arq->_file);
    fwrite(&_arvorebCabecalho->RRNproxNo, sizeof(int), 1, _arvoreb->_arq->_file);
    
    return 0;
}

// Le o cabecalho no arquivo arvoreb (retorna 1 - erro e retorna 0 - sucesso)
int arvoreb_leCabecalho(arvoreb * _arvoreb, arvorebCabecalho * _arvorebCabecalhoDestino) {
    // Teste de erro, verifica se o arquivo foi aberto e se o cabecalho existe
    if (_arvoreb->_arq->estado == '0' || _arvorebCabecalhoDestino == NULL) {
        return 1;
    }

    // Vai ate o inicio do arquivo
    fseek(_arvoreb->_arq->_file, 0, SEEK_SET);
    
    // Escreve os campos do cabecalho
    fread(&_arvorebCabecalhoDestino->status, sizeof(char), 1, _arvoreb->_arq->_file);
    fread(&_arvorebCabecalhoDestino->noRaiz, sizeof(int), 1, _arvoreb->_arq->_file);
    fread(&_arvorebCabecalhoDestino->RRNproxNo, sizeof(int), 1, _arvoreb->_arq->_file);
    
    return 0;
}


// Insere o registro no arquivo arvoreb (retorna 1 - erro e retorna 0 - sucesso)
int escreveArvorebRegistro(arvoreb * _arvoreb, arvorebRegistro * _arvorebRegistro, int RRN) {
    // Teste de erro, verifica se o arquivo foi aberto, se o registro foi aberto, e se o RRN é valido
    if (_arvoreb->_arq->estado == '0' || _arvorebRegistro == NULL || RRN < 0) {
        return 1;
    }

    // Vai ate a posicao do registro
    fseek(_arvoreb->_arq->_file, (RRN + 1) * TAMANHO_PAG_ARVOREB, SEEK_SET);

    // Escreve os campos do registro
    fwrite(&_arvorebRegistro->folha, sizeof(char), 1, _arvoreb->_arq->_file);
    fwrite(&_arvorebRegistro->nroChavesNo, sizeof(int), 1, _arvoreb->_arq->_file);
    fwrite(&_arvorebRegistro->RRNdoNo, sizeof(int), 1, _arvoreb->_arq->_file);
    
    for (int i = 0; i < ORDEM_ARVOREB; i++) {
        fwrite(&_arvorebRegistro->ponteiros[i], sizeof(int), 1, _arvoreb->_arq->_file);
        if (i < ORDEM_ARVOREB - 1) {
            fwrite(&_arvorebRegistro->elementos[i].chave, sizeof(tipo_chave), 1, _arvoreb->_arq->_file);
            fwrite(&_arvorebRegistro->elementos[i].pr, sizeof(long int), 1, _arvoreb->_arq->_file);
        }
    }

    return 0;
}

// Le o registro no arquivo arvoreb (retorna 1 - erro e retorna 0 - sucesso)
int arvoreb_leRegistro(arvoreb * _arvoreb, arvorebRegistro * _arvorebRegistroDestino, int RRN) {
    // Teste de erro, verifica se o arquivo foi aberto, se o registro foi aberto, e se o RRN é valido
    if (_arvoreb->_arq->estado == '0' || _arvorebRegistroDestino == NULL || RRN < 0) {
        return 1;
    }

    // Vai ate a posicao do registro
    fseek(_arvoreb->_arq->_file, (RRN + 1) * TAMANHO_PAG_ARVOREB, SEEK_SET);

    // Escreve os campos do registro
    fread(&_arvorebRegistroDestino->folha, sizeof(char), 1, _arvoreb->_arq->_file);
    fread(&_arvorebRegistroDestino->nroChavesNo, sizeof(int), 1, _arvoreb->_arq->_file);
    fread(&_arvorebRegistroDestino->RRNdoNo, sizeof(int), 1, _arvoreb->_arq->_file);

    for (int i = 0; i < ORDEM_ARVOREB; i++) {
        fread(&_arvorebRegistroDestino->ponteiros[i], sizeof(int), 1, _arvoreb->_arq->_file);
        if (i < ORDEM_ARVOREB - 1) {
            fread(&_arvorebRegistroDestino->elementos[i].chave, sizeof(tipo_chave), 1, _arvoreb->_arq->_file);
            fread(&_arvorebRegistroDestino->elementos[i].pr, sizeof(long int), 1, _arvoreb->_arq->_file);
        }
    }

    return 0;
}


// Pesquisa um elemento por uma chave na arvoreb e insere uma copia em _arvorebElementoDestino (retorna 1 - erro e retorna 0 - sucesso)
int arvoreb_pesquisaChave(arvoreb * _arvoreb, tipo_chave chaveBusca, arvorebElemento * _arvorebElementoDestino) {
    // Teste de erro
    if (_arvorebElementoDestino == NULL) {
        return 1;
    }

    // Cria o cabecalho
    arvorebCabecalho * _arvbCab;
    criaArvorebCabecalho(&_arvbCab);

    // Le o cabecalho
    _arvoreb->leCabecalho(_arvoreb, _arvbCab);


    // Cria registro
    arvorebRegistro * _arvbReg;
    criaArvorebRegistro(&_arvbReg);

    // Le o registro raiz
    _arvoreb->leRegistro(_arvoreb, _arvbReg, _arvbCab->noRaiz);


    // Loop de busca
    int existeChave = 0; // 0 - falso e 1 verdadeiro

    int inicioLista, fimLista, pivo;

    
    while(1) {
        // Captura o inicio e o fim da busca binaria
        inicioLista = 0;
        fimLista = _arvbReg->nroChavesNo - 1;

        // Executa a busca binaria
        while (inicioLista <= fimLista) {
            
            // Captura o pivo
            pivo = (fimLista - inicioLista) / 2 + inicioLista;


            // Verifica se é igual a chave busca
            if (_arvbReg->elementos[pivo].chave == chaveBusca) {
                
                existeChave = 1;
                break;

            } 
            
            // Se nao, recalcula os limites de busca
            if (_arvbReg->elementos[pivo].chave > chaveBusca) {

                fimLista = pivo - 1;

            } else {

                inicioLista = pivo + 1;

            }

        }

        // Se o no for folha ou se já foi encontrado a chave, quebra o loop
        if (_arvbReg->folha == '1' || existeChave == 1) {
            break;
        }

        // Se nao encontrou no no, busca no no prox a partir de onde parou o pivo e o valor da chave na posicao do pivo
        if (_arvbReg->elementos[pivo].chave > chaveBusca ) {
            if (_arvbReg->ponteiros[pivo] == -1) break;
            
            _arvoreb->leRegistro(_arvoreb, _arvbReg, _arvbReg->ponteiros[pivo]);

        } else {
            if (_arvbReg->ponteiros[pivo + 1] == 1) break;
            
            _arvoreb->leRegistro(_arvoreb, _arvbReg, _arvbReg->ponteiros[pivo + 1]);

        }

    }
    
    // Verifica se a chave foi encontrada
    if (existeChave == 0) {

        _arvorebElementoDestino->chave = -1;
        _arvorebElementoDestino->pr = -1;
        return 1;

    } else {

        _arvorebElementoDestino->chave = _arvbReg->elementos[pivo].chave;
        _arvorebElementoDestino->pr = _arvbReg->elementos[pivo].pr;

    }

    // Desaloca memoria alocada
    destroiArvorebRegistro(&_arvbReg);
    destroiArvorebCabecalho(&_arvbCab);

    return 0;
}


// Insere o elemento no arquivo arvoreb (retorna 1 - erro e retorna 0 - sucesso)
int arvoreb_insereElemento(arvoreb * _arvoreb, arvorebElemento * _arvorebElemento) {

    // Teste de erro
    if (_arvorebElemento == NULL) {
        return 1;
    }
    
    // Cria o cabecalho
    arvorebCabecalho * _arvbCab;
    criaArvorebCabecalho(&_arvbCab);

    // Le o cabecalho
    _arvoreb->leCabecalho(_arvoreb, _arvbCab);

    // Cria registro
    arvorebRegistro * _arvbReg;
    criaArvorebRegistro(&_arvbReg);


    // Verifica se ha algum elemento ou registro na arvoreb

    if (_arvbCab->RRNproxNo == 0) {
        _arvbReg->folha = '1';
        _arvbReg->nroChavesNo = 1;
        _arvbReg->elementos[0] = *_arvorebElemento;
        escreveArvorebRegistro(_arvoreb, _arvbReg, 0);

        _arvbCab->RRNproxNo++;
        _arvoreb->insereCabecalho(_arvoreb, _arvbCab);
        
        destroiArvorebRegistro(&_arvbReg);
        destroiArvorebCabecalho(&_arvbCab);

        return 0;
    }

    // Cria a lista que armazenara RRN do caminho de registros ate o local da insercao
    int espacoEtapasCaminho = 1000;
    int * caminho = (int *) malloc (sizeof(int) * espacoEtapasCaminho);
    int numeroEtapasCaminho = 0;

    // Le o registro raiz
    _arvoreb->leRegistro(_arvoreb, _arvbReg, _arvbCab->noRaiz);

    // Loop de busca
    int existeChave = 0; // 0 - falso e 1 verdadeiro
    int posChave = -1;


    int inicioLista, fimLista, pivo;

    

    while(1) {
        
        // Verfica se ha espaco na lista caminho
        if (espacoEtapasCaminho <= numeroEtapasCaminho) {
            caminho = (int *) realloc(caminho, espacoEtapasCaminho + 100);
            espacoEtapasCaminho += 100;
        }

        // Adiciona o registro atual ao caminho
        caminho[numeroEtapasCaminho] = _arvbReg->RRNdoNo;
        numeroEtapasCaminho++;

        // Captura o inicio e o fim da busca binaria
        inicioLista = 0;
        fimLista = _arvbReg->nroChavesNo - 1;

        // Executa a busca binaria
        while (inicioLista <= fimLista) {

            // Captura o pivo
            pivo = (fimLista - inicioLista) / 2 + inicioLista;


            // Verifica se é igual a chave busca
            if (_arvbReg->elementos[pivo].chave == _arvorebElemento->chave) {
                
                existeChave = 1;
                break;

            } 
            
            // Se nao, recalcula os limites de busca
            if (_arvbReg->elementos[pivo].chave > _arvorebElemento->chave) {

                fimLista = pivo - 1;

            } else {

                inicioLista = pivo + 1;

            }

        }


        // Se o no for folha ou se já foi encontrado a chave, quebra o loop
        if (_arvbReg->folha == '1' || existeChave == 1) {
            break;
        }

        
        

        // Se nao encontrou no no, busca no no prox a partir de onde parou o pivo e o valor da chave na posicao do pivo
        if (_arvbReg->elementos[pivo].chave > _arvorebElemento->chave ) {
            if (_arvbReg->ponteiros[pivo] == -1) break;
            
            _arvoreb->leRegistro(_arvoreb, _arvbReg, _arvbReg->ponteiros[pivo]);

        } else {
            if (_arvbReg->ponteiros[pivo + 1] == -1) break;
            
            _arvoreb->leRegistro(_arvoreb, _arvbReg, _arvbReg->ponteiros[pivo + 1]);

        }

    }
    
    

    // Verifica se a chave foi encontrada
    if (existeChave == 1) {

        printf("[sys]: Registro ja existe na arvoreb\n");
        
        // Desaloca memoria alocada
        free(caminho);
        destroiArvorebRegistro(&_arvbReg);
        destroiArvorebCabecalho(&_arvbCab);

        return 0;


    }

    // Inseri o registro

    // Calcula a posicao de insercao
    if (_arvbReg->elementos[pivo].chave > _arvorebElemento->chave ) {
        pivo;
    } else {
        pivo++;
    }

    

    // Se ja ha espaco no no
    if ( _arvbReg->nroChavesNo < ORDEM_ARVOREB - 1 ) {
        


        

        // Da um shift para a direita ate a posicao da insercao
        for (int i = _arvbReg->nroChavesNo - 1; i >= pivo; i--) {
            _arvbReg->elementos[i + 1].chave = _arvbReg->elementos[i].chave ;
            _arvbReg->elementos[i + 1].pr = _arvbReg->elementos[i].pr;
        }

        // Adiciona o elemento
        _arvbReg->elementos[pivo].chave = _arvorebElemento->chave;
        _arvbReg->elementos[pivo].pr = _arvorebElemento->pr;

        // Aumenta o contador
        _arvbReg->nroChavesNo++;

        // Atualiza no arquivo
        if (escreveArvorebRegistro(_arvoreb, _arvbReg, _arvbReg->RRNdoNo) == 1) {
            
            // Desaloca memoria alocada
            free(caminho);
            destroiArvorebRegistro(&_arvbReg);
            destroiArvorebCabecalho(&_arvbCab);
            
            return 1;
        }
        
        return 0;

    }

    // Se nao ha espaco no no

    // Split na primeira insercao

    arvorebElemento splitArvbEle[ORDEM_ARVOREB];
    int splitArvbPtr[ORDEM_ARVOREB + 1];

    // Insere os valores originais junto com o valor correspondente no pivo

    // Como se trata de um no folha, todos os ponteiros devem ser -1
    for(int i = 0; i < ORDEM_ARVOREB + 1; i++) {
        splitArvbPtr[i] = -1;
    }

    // Copia do registro original com a chave a ser inserida

    for(int i = 0; i < ORDEM_ARVOREB - 1; i++) {

        splitArvbEle[i] = _arvbReg->elementos[i];
    }
    
    // Shift para regiao depois do pivo
    for(int i = ORDEM_ARVOREB - 2; i >= pivo; i--) {

        splitArvbEle[i + 1] = _arvbReg->elementos[i];

    }


    // Adiciona a chave a ser inserida

    splitArvbEle[pivo] = *_arvorebElemento;

    
    // Limpa chaves do registro original

    for (int i = 0; i < ORDEM_ARVOREB - 1; i++) {

        _arvbReg->elementos[i].chave = -1;
        _arvbReg->elementos[i].pr = -1;

    }

    // Cria um novo registro
    arvorebRegistro * _arvbRegNovo;
    criaArvorebRegistro(&_arvbRegNovo);

    
    // Faz a divisao das chaves

    for(int i = 0; i < ORDEM_ARVOREB / 2; i++) {
        
        _arvbReg->elementos[i] = splitArvbEle[i];
    }

    // Atualiza reg origem
    _arvbReg->nroChavesNo = ORDEM_ARVOREB / 2;

    for(int i = ORDEM_ARVOREB / 2 + 1; i < ORDEM_ARVOREB; i++) {

        _arvbRegNovo->elementos[i - ORDEM_ARVOREB / 2 - 1] = splitArvbEle[i];

        
    }

    // Atualiza novo reg e o cabecario
    _arvbRegNovo->nroChavesNo = ORDEM_ARVOREB - ORDEM_ARVOREB / 2 - 1;
    _arvbRegNovo->RRNdoNo = _arvbCab->RRNproxNo;
    _arvbRegNovo->folha = '1';
    _arvbCab->RRNproxNo++;

    
    // Atualiza o cabecario e registro no arquivo
    escreveArvorebRegistro(_arvoreb, _arvbReg, _arvbReg->RRNdoNo);
    escreveArvorebRegistro(_arvoreb, _arvbRegNovo, _arvbRegNovo->RRNdoNo);

    _arvoreb->insereCabecalho(_arvoreb, _arvbCab);

    // Elemento a ser promovido
    arvorebElemento elePromovido = splitArvbEle[ORDEM_ARVOREB / 2];

    // Loop para promover chaves
    arvorebRegistro * _arvbRegPai;
    criaArvorebRegistro(&_arvbRegPai);

    while(numeroEtapasCaminho > 1) {

        // Carrega no superior
        numeroEtapasCaminho--;
        
        criaArvorebRegistro(&_arvbRegPai);

        //if (_arvorebElemento->chave == 456) printf("\n%d %d |", _arvbReg->RRNdoNo, _arvbRegPai->RRNdoNo);
        _arvoreb->leRegistro(_arvoreb, _arvbRegPai, caminho[numeroEtapasCaminho - 1]);
        //if (_arvorebElemento->chave == 456) printf("\n%d %d |\n\n", _arvbReg->RRNdoNo, _arvbRegPai->RRNdoNo);

        // Captura o inicio e o fim da busca binaria
        inicioLista = 0;
        fimLista = _arvbRegPai->nroChavesNo - 1;

        // Executa a busca binaria
        while (inicioLista <= fimLista) {

            // Captura o pivo
            pivo = (fimLista - inicioLista) / 2 + inicioLista;


            // Verifica se é igual a chave busca
            if (_arvbRegPai->elementos[pivo].chave == elePromovido.chave) {
                
                existeChave = 1;
                break;

            } 
            
            // Se nao, recalcula os limites de busca
            if (_arvbRegPai->elementos[pivo].chave > elePromovido.chave) {

                fimLista = pivo - 1;

            } else {

                inicioLista = pivo + 1;

            }

        }

        // Calcula a posicao de insercao
        if (_arvbRegPai->elementos[pivo].chave > elePromovido.chave ) {
            pivo;
        } else {
            pivo++;
        }

        // Se o no pai nao estiver totalmente preenchido
        if (_arvbRegPai->nroChavesNo < ORDEM_ARVOREB - 1) {
            
            

            // Da um shift para a direita ate a posicao da insercao dos ponteiros e elementos
            for (int i = _arvbRegPai->nroChavesNo - 1; i >= pivo; i--) {
                _arvbRegPai->elementos[i + 1].chave = _arvbRegPai->elementos[i].chave ;
                _arvbRegPai->elementos[i + 1].pr = _arvbRegPai->elementos[i].pr;
                _arvbRegPai->ponteiros[i + 2] = _arvbRegPai->ponteiros[i + 1];
            }
            _arvbRegPai->ponteiros[pivo] = _arvbRegPai->ponteiros[pivo];



            // Adiciona o elemento
            _arvbRegPai->elementos[pivo].chave = elePromovido.chave;
            _arvbRegPai->elementos[pivo].pr = elePromovido.pr;

            // Aumenta o contador
            _arvbRegPai->nroChavesNo++;

            
            // Atualiza os ponteiros
            _arvbRegPai->ponteiros[pivo] = _arvbReg->RRNdoNo;
            _arvbRegPai->ponteiros[pivo + 1] = _arvbRegNovo->RRNdoNo;


            


            // Atualiza no arquivo
            escreveArvorebRegistro(_arvoreb, _arvbRegPai, _arvbRegPai->RRNdoNo);

            numeroEtapasCaminho = -1;

            break;

        }
        
        // Se o no pai estiver totalmente preenchido
        arvorebElemento splitArvbElePai[ORDEM_ARVOREB];
        int splitArvbPtrPai[ORDEM_ARVOREB + 1];

        // Copia os elementos e ponteiros do nó pai
        for (int i = 0; i < ORDEM_ARVOREB - 1; i++) {
            splitArvbElePai[i] = _arvbRegPai->elementos[i];
            splitArvbPtrPai[i] = _arvbRegPai->ponteiros[i];
        }
        splitArvbPtrPai[ORDEM_ARVOREB - 1] = _arvbRegPai->ponteiros[ORDEM_ARVOREB - 1];

        // Insere a chave promovida e os ponteiros
        for (int i = ORDEM_ARVOREB - 2; i >= pivo; i--) {
            splitArvbElePai[i + 1] = _arvbRegPai->elementos[i];
            splitArvbPtrPai[i + 2] = _arvbRegPai->ponteiros[i + 1];
        }
        splitArvbElePai[pivo] = elePromovido;
        splitArvbPtrPai[pivo] = _arvbReg->RRNdoNo;
        splitArvbPtrPai[pivo + 1] = _arvbRegNovo->RRNdoNo;

        // Cria um novo no para o pai apos o split
        arvorebRegistro * _arvbRegPaiNovo;
        criaArvorebRegistro(&_arvbRegPaiNovo);

        for(int i = 0; i < ORDEM_ARVOREB - 1; i++) {
            _arvbRegPai->elementos[i].chave = -1;
            _arvbRegPai->elementos[i].pr = -1;
            _arvbRegPai->ponteiros[i] = -1;
        }

        _arvbRegPai->ponteiros[ORDEM_ARVOREB - 1] = -1;

        for (int i = 0; i < ORDEM_ARVOREB / 2; i++) {
            _arvbRegPai->elementos[i] = splitArvbElePai[i];
            _arvbRegPai->ponteiros[i] = splitArvbPtrPai[i];
        }
        _arvbRegPai->ponteiros[ORDEM_ARVOREB / 2] = splitArvbPtrPai[ORDEM_ARVOREB / 2];
        _arvbRegPai->nroChavesNo = ORDEM_ARVOREB / 2;

        for (int i = ORDEM_ARVOREB / 2 + 1; i < ORDEM_ARVOREB; i++) {
            _arvbRegPaiNovo->elementos[i - ORDEM_ARVOREB / 2 - 1] = splitArvbElePai[i];
            _arvbRegPaiNovo->ponteiros[i - ORDEM_ARVOREB / 2 - 1] = splitArvbPtrPai[i];
        }
        _arvbRegPaiNovo->ponteiros[ORDEM_ARVOREB - ORDEM_ARVOREB / 2 - 1] = splitArvbPtrPai[ORDEM_ARVOREB];
        _arvbRegPaiNovo->nroChavesNo = ORDEM_ARVOREB - ORDEM_ARVOREB / 2 - 1;
        _arvbRegPaiNovo->RRNdoNo = _arvbCab->RRNproxNo;

        

        _arvbCab->RRNproxNo++;

        // Atualiza o cabecalho e escreve os nós
        escreveArvorebRegistro(_arvoreb, _arvbRegPai, _arvbRegPai->RRNdoNo);
        escreveArvorebRegistro(_arvoreb, _arvbRegPaiNovo, _arvbRegPaiNovo->RRNdoNo);
        _arvoreb->insereCabecalho(_arvoreb, _arvbCab);

        // Atualiza o elemento promovido para o próximo loop
        elePromovido = splitArvbElePai[ORDEM_ARVOREB / 2];


        destroiArvorebRegistro(&_arvbReg);
        destroiArvorebRegistro(&_arvbRegNovo);
        
        _arvbReg = _arvbRegPai;
        _arvbRegPai = NULL;
        _arvbRegNovo = _arvbRegPaiNovo;

    }


    
    
    // Se o loop chegou ate a raiz => que e necessario fazer outro split na raiz
    if (numeroEtapasCaminho == 1) {

        arvorebRegistro * novaRaiz;
        criaArvorebRegistro(&novaRaiz);

        novaRaiz->elementos[0] = elePromovido;
        novaRaiz->ponteiros[0] = _arvbReg->RRNdoNo;
        novaRaiz->ponteiros[1] = _arvbRegNovo->RRNdoNo;
        novaRaiz->nroChavesNo = 1;
        novaRaiz->RRNdoNo = _arvbCab->RRNproxNo;
        _arvbCab->RRNproxNo++;

        escreveArvorebRegistro(_arvoreb, novaRaiz, novaRaiz->RRNdoNo);

        // Atualiza o cabeçalho para apontar para a nova raiz
        _arvbCab->noRaiz = novaRaiz->RRNdoNo;
        _arvoreb->insereCabecalho(_arvoreb, _arvbCab);

        destroiArvorebRegistro(&novaRaiz);
    }



    // Desaloca memoria alocada
    //destroiArvorebRegistro(&_arvbRegPai);
    destroiArvorebRegistro(&_arvbReg);
    destroiArvorebRegistro(&_arvbRegNovo);
    destroiArvorebCabecalho(&_arvbCab);

    return 0; 

}

// Funcao debug print todos os elementos e cabecarios da arvore b
int printArvoreb(arvoreb * _arvoreb) {

    arvorebCabecalho * _arvorebCabecalho;
    criaArvorebCabecalho(&_arvorebCabecalho);

    _arvoreb->leCabecalho(_arvoreb, _arvorebCabecalho);

    printf(" \n\nCabecalho:\n\nStatus: %c \nnoRaiz: %d \nRRNproxNo: %d\n\n", _arvorebCabecalho->status, _arvorebCabecalho->noRaiz, _arvorebCabecalho->RRNproxNo);


    arvorebRegistro * _arvorebRegistro;
    criaArvorebRegistro(&_arvorebRegistro);

    for(int i = 0; i < _arvorebCabecalho->RRNproxNo; i++) {
        _arvoreb->leRegistro(_arvoreb, _arvorebRegistro, i);

        printf("\n\nRegistro: %d\n\n Folha: %c \n nroChavesNo: %d\n RRNdoNo: %d\n P1: %d\n C1: %li    Pr1: %li\n P2: %d\n C2: %li    Pr2: %li\n P3: %d\n C3: %li    Pr3: %li\n P4: %d\n C4: %li    Pr4: %li \n P5: %d\n", 
        _arvorebRegistro->RRNdoNo, _arvorebRegistro->folha, _arvorebRegistro->nroChavesNo, _arvorebRegistro->RRNdoNo, _arvorebRegistro->ponteiros[0], _arvorebRegistro->elementos[0].chave, _arvorebRegistro->elementos[0].pr, 
        _arvorebRegistro->ponteiros[1], _arvorebRegistro->elementos[1].chave, _arvorebRegistro->elementos[1].pr,
        _arvorebRegistro->ponteiros[2], _arvorebRegistro->elementos[2].chave, _arvorebRegistro->elementos[2].pr,
        _arvorebRegistro->ponteiros[3], _arvorebRegistro->elementos[3].chave, _arvorebRegistro->elementos[3].pr, _arvorebRegistro->ponteiros[4]);


    }


    destroiArvorebCabecalho(&_arvorebCabecalho);

    return 0;

}

// Cria a estrutura arvorebCabecalho e aloca o espaco necessario (retorna 1 - erro e retorna 0 - sucesso)
int criaArvoreb(arvoreb ** __arvoreb) {
    // Aloca memoria e verifica
    *__arvoreb = (arvoreb*) malloc(sizeof(arvoreb));

    if (*__arvoreb == NULL) return 1;

    // Cria a estrutura de arquivo para arvoreb
    (*__arvoreb)->_arq = criaArqBin();


    // Insere os valores padroes
    (*__arvoreb)->abrirArquivo = &arvoreb_abrirArquivo;
    (*__arvoreb)->fecharArquivo = &arvoreb_fecharArquivo;
    (*__arvoreb)->criaArquivoArvoreb = &arvoreb_criaArquivoArvoreb;
    (*__arvoreb)->insereCabecalho = &arvoreb_insereCabecalho;
    (*__arvoreb)->leCabecalho = &arvoreb_leCabecalho;
    (*__arvoreb)->leRegistro = &arvoreb_leRegistro;
    (*__arvoreb)->insereElemento = &arvoreb_insereElemento;
    (*__arvoreb)->pesquisaChave = &arvoreb_pesquisaChave;

    return 0;
}

// Destroi a estrutura arvoreb e desaloca o espaco necessario (retorna 1 - erro e retorna 0 - sucesso)
int destroiArvoreb(arvoreb ** __arvoreb) {
    if (*__arvoreb == NULL) {
        return 1;
    }

    destroiArqBin(&(*__arvoreb)->_arq);

    free(*__arvoreb);
    *__arvoreb = NULL;
    return 0; 
}

