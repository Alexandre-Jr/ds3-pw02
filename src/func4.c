#include "../include/src/func4.h"

void func4() {
    int n; 
    char nomeArquivo[LIMITE_TAMANHO_NOME_ARQUIVO];
    // Entrada de dados
    scanf("%s", nomeArquivo);
    scanf("%d", &n);

    // Abertura do arquivo binário
    arqBin *_arqBin = criaArqBin();
    strcpy(_arqBin->nomeBin, nomeArquivo);  // Define o nome do arquivo binário
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
    if( cab.status == '0') {
        printf("Falha no processamento do arquivo.\n");
        destroiArqBin(&_arqBin);
        return;
    }

    // variavel para armazenar registro
    registro *reg = criaRegistro();

    // Captura o tamanho do arquivo e o numero de paginas
    int tamArqBin = 0;
    tamanhoArqBin(_arqBin, &tamArqBin);
    int numeroReg = (tamArqBin - TAMANHO_PAG) / TAMANHO_REGISTRO;

    char lixo = '$';
    int remover = 0;

    int flag_string;
    char campo[LIMITE_TAMANHO_NOME_CAMPO], valor[TAMANHO_CAMPO_VARIAVEL_MAXIMO];

    for(int i = 0; i < n; ++i) {
        // Leitura da entrada do usuário

        // Leitura do nome do campo
        scanf("%s", campo);
        // Verifica o tipo do campo
        if(strcmp(campo, "nome") == 0) flag_string = 1;
        else if(strcmp(campo, "especie") == 0) flag_string = 1;
        else if(strcmp(campo, "habitat") == 0) flag_string = 1;
        else if(strcmp(campo, "tipo") == 0) flag_string = 1;
        else if(strcmp(campo, "dieta") == 0) flag_string = 1;
        else if(strcmp(campo, "alimento") == 0) flag_string = 1;

        //Faz a leitura adequada ao tipo de campo
        if(flag_string) scan_quote_string(valor);  // Le com aspas
        else scanf("%s", valor); // Le sem aspas

        // Itera pelos registros
        for(int j = 0; j < numeroReg; ++j) {
            remover = 0;
            // Aponta para o registro j
            fseek(_arqBin->_file, TAMANHO_PAG + j * TAMANHO_REGISTRO, SEEK_SET);
            // Le o registro
            leRegistro(_arqBin, reg);
            if (reg->removido == '1') continue; // Se já estiver removido, ignora

            // Verifica se o registro atende ao critério de remoção
            if (strcmp(campo, "populacao") == 0 && atoi(valor) == reg->populacao) remover = 1;
            else if (strcmp(campo, "tamanho") == 0 && atof(valor) == reg->tamanho) remover = 1;
            else if (strcmp(campo, "unidadeMedida") == 0 && valor[0] == reg->unidadeMedida) remover = 1;
            else if (strcmp(campo, "velocidade") == 0 && atoi(valor) == reg->velocidade) remover = 1;
            else if (strcmp(campo, "nome") == 0 && strcmp(valor, reg->nome) == 0) remover = 1;
            else if (strcmp(campo, "especie") == 0 && strcmp(valor, reg->especie) == 0) remover = 1;
            else if (strcmp(campo, "habitat") == 0 && strcmp(valor, reg->habitat) == 0) remover = 1;
            else if (strcmp(campo, "tipo") == 0 && strcmp(valor, reg->tipo) == 0) remover = 1;
            else if (strcmp(campo, "dieta") == 0 && strcmp(valor, reg->dieta) == 0) remover = 1;
            else if (strcmp(campo, "alimento") == 0 && strcmp(valor, reg->alimento) == 0) remover = 1;
            
            if(remover) {
                reg->removido = '1'; // Marca como removido logicamente
                reg->encadeamento = cab.topo; // Atualiza o link
                cab.status = '0'; // Atualiza para escritas
                ++cab.nroRegRem; // Incrementa o numero de remocoes
                cab.topo = j; // Novo topo da lista
                escreveCabecalho(_arqBin, &cab); // Reescreve o cabecalho
                // Aponta para o inicio do registro
                fseek(_arqBin->_file, TAMANHO_PAG + j * TAMANHO_REGISTRO, SEEK_SET);

                // Atualiza o registro com os campos de controle
                fwrite(&reg->removido, sizeof(char), 1, _arqBin->_file);
                fwrite(&reg->encadeamento, sizeof(int), 1, _arqBin->_file);
                // Preenche o restante com lixo
                for(int k = 0; k < TAMANHO_REGISTRO  - sizeof(char) - sizeof(int); ++k) {
                    fwrite(&lixo, sizeof(char), 1, _arqBin->_file);
                }
                // Atualiza o cabecalho novamente, finalizando a escrita
                cab.status = '1';
                escreveCabecalho(_arqBin, &cab);
            }

        }
    }
    fecharArqBin(_arqBin);
    binarioNaTela(_arqBin->nomeBin);
    destroiArqBin(&_arqBin);
    free(reg);
    
}
