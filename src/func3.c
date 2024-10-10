// Link
#include "../include/src/func2.h"

// Funcao principal da funcionalidade de busca
void func3() {
    // Limpa o buffer
    limpaBuffer();

    // Cria a struct de arqBin
    arqBin * _arqBin = criaArqBin();

    // Faz a leitura do nome do arquivo
    leString(_arqBin->nomeBin);

    // Captura o numero de buscas
    int nBusca;
    leInt(&nBusca);
    limpaBuffer();

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
    cabecalho * _cabecalho = criaCabecalho();

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
    int NumeroPag = ceil((float) tamArqBin / TAMANHO_PAG);

    // Inicia as buscas possíveis
    char stringHabitat[] = "habitat\0";
    char stringTamanho[] = "tamanho\0";
    char stringVelocidade[] = "velocidade\0";
    char stringNome[] = "nome\0";
    char stringPopulacao[] = "populacao\0";
    char stringEspecie[] = "especie\0";
    char stringTipo[] = "tipo\0";
    char stringDieta[] = "dieta\0";
    char stringAlimento[] = "alimento\0";

    // Faz a varredura no numero de registros pesquisando
    for (int j = 0; j < nBusca; j++) {

        // Print o numero da busca
        printf("Busca %d\n", j + 1);

        // Declara string de busca (string que indicará o tipo de busca)
        char * stringBusca = (char *) malloc (LIMITE_TAMANHO_NOME_CAMPO * sizeof(char));
        leString(stringBusca);


        // Armazena o tipo de busca
        int tipoBusca; // 6 - habitat & 2 - tamanho & 3 - Velocidade & 4 - nome

        // Cria variáveis para guardar o valor a ser buscado
        char * stringValorBusca = (char *) malloc (LIMITE_TAMANHO_NOME_CAMPO * sizeof(char));
        int intValorBusca;
        float floatValorBusca;

        // Verifica o tipo de busca
        if (compString(stringBusca, stringPopulacao) == 0) {
            tipoBusca = 1;
            leInt(&intValorBusca);
        }  else if (compString(stringBusca, stringTamanho) == 0) {
            tipoBusca = 2;
            leFloat(&floatValorBusca);
        } else if (compString(stringBusca, stringVelocidade) == 0) {
            tipoBusca = 3;
            leInt(&intValorBusca);
        } else if (compString(stringBusca, stringNome) == 0) {
            tipoBusca = 4;
            scan_quote_string(stringValorBusca);
        } else if (compString(stringBusca, stringEspecie) == 0) {
            tipoBusca = 5;
            scan_quote_string(stringValorBusca);
        } else if (compString(stringBusca, stringHabitat) == 0) {
            tipoBusca = 6;
            scan_quote_string(stringValorBusca);
        } else if (compString(stringBusca, stringTipo) == 0) {
            tipoBusca = 7;
            scan_quote_string(stringValorBusca);
        } else if (compString(stringBusca, stringDieta) == 0) {
            tipoBusca = 8;
            scan_quote_string(stringValorBusca);
        } else if (compString(stringBusca, stringAlimento) == 0) {
            tipoBusca = 9;
            scan_quote_string(stringValorBusca);
        } 

        if (j != nBusca -1) {
            limpaBuffer();
        }

        // Armazena o numero de registros encontrados
        int nRegistrosEncontrados = 0;

        for(int i = 0; i < NumeroReg; i++) {
            // Encontra a posicao do registro
            fseek(_arqBin->_file, i * TAMANHO_REGISTRO + TAMANHO_PAG, SEEK_SET);

            // Cria registro
            registro * _registro = criaRegistro();

            // Le registro
            leRegistro(_arqBin, _registro);

            if (_registro->removido == '0') {
                // Se o tipo de busca for populacao
                if (tipoBusca == 1) {
                    if (intValorBusca == _registro->populacao) {
                        printRegistro(_registro);
                        nRegistrosEncontrados++;
                    }
                } else if (tipoBusca == 2) {
                   if (_registro->tamanho == floatValorBusca) {
                        printRegistro(_registro);
                         nRegistrosEncontrados++;
                    }
                // Se o tipo de busca for velocidade
                } else if (tipoBusca == 3) {
                    if (_registro->velocidade == intValorBusca) {
                        printRegistro(_registro);
                        nRegistrosEncontrados++;
                    }
                // Se o tipo de busca for nome
                } else if (tipoBusca == 4) {
                    if (compString(stringValorBusca, _registro->nome) == 0) {
                        printRegistro(_registro);
                        nRegistrosEncontrados++;
                    }
                // Se o tipo de busca for especie
                } else if (tipoBusca == 5) {
                    if (compString(stringValorBusca, _registro->especie) == 0) {
                        printRegistro(_registro);
                        nRegistrosEncontrados++;
                    }
                // Se o tipo de busca for habitat
                } else if (tipoBusca == 6) {
                    if (compString(stringValorBusca, _registro->habitat) == 0) {
                        printRegistro(_registro);
                        nRegistrosEncontrados++;
                        }
                // Se o tipo de busca for tipo
                } else if (tipoBusca == 7) {
                    if (compString(stringValorBusca, _registro->tipo) == 0) {
                        printRegistro(_registro);
                        nRegistrosEncontrados++;
                    }
                // Se o tipo de busca for dieta
                } else if (tipoBusca == 8) {
                    if (compString(stringValorBusca, _registro->dieta) == 0) {
                        printRegistro(_registro);
                        nRegistrosEncontrados++;
                    }
                // Se o tipo de busca for alimento
                } else if (tipoBusca == 9) {
                    if (compString(stringValorBusca, _registro->alimento) == 0) {
                        printRegistro(_registro);
                        nRegistrosEncontrados++;
                    }
                }
            }

            // Destroi registro da memoria
            destroiRegistro(&_registro);
        }

        // Se nenhum registro for encontrado
        if (nRegistrosEncontrados == 0) {
            printf("Registro inexistente.\n\n");
        }

        // Printa o numero de paginas
        printf("Numero de paginas de disco: %d", NumeroPag);
        printf("\n\n");

        // Libera a memoria alocada
        free(stringBusca);
        free(stringValorBusca);
    };

    //Fechar arquivo
    fecharArqBin(_arqBin);

    // Termina a funcao
    destroiCabecalho(&_cabecalho);
    destroiArqBin(&_arqBin);
}