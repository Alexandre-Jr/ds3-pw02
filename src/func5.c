#include "../include/src/func5.h"

void func5() {
    int n;
    arqBin *_arqBin = criaArqBin();
    // Entrada de dados
    scanf("%s", _arqBin->nomeBin);
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
    if( cab.status == '0') {
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
    for(int i = 0; i < n; ++i) {
        // Realiza a leitura do registro a ser inserido
        for(int j = 0; j < 10; ++j) {
            scan_quote_string(campo[j]);
            tamanho_campo[j] = strlen(campo[j]) + 1; // Conta o '\0'
        }
        // Aloca espaço e copia os valores para a struct
        // Nome
        reg->nome = (char*) malloc(tamanho_campo[0]);
        strncpy(reg->nome, campo[0], tamanho_campo[0]);
        
        // Dieta
        reg->dieta = (char*) malloc(tamanho_campo[1]);
        strncpy(reg->dieta, campo[1], tamanho_campo[1]);

        // Habitat
        reg->habitat = (char*) malloc(tamanho_campo[2]);
        strncpy(reg->habitat, campo[2], tamanho_campo[2]);

        // População
        if(strcmp(campo[3], "") == 0) reg->populacao = -1;
        else reg->populacao = atoi(campo[3]);

        // Tipo
        reg->tipo = (char*) malloc(tamanho_campo[4]);
        strncpy(reg->tipo, campo[4], tamanho_campo[4]);

        // Velocidade
        if(strcmp(campo[5], "") == 0) reg->velocidade = -1;
        else reg->velocidade = atoi(campo[5]);

        // UnidadeMedida
        if(strcmp(campo[6], "") == 0) reg->unidadeMedida = '$';
        else reg->unidadeMedida = campo[6][0];

        // Tamanho
        if(strcmp(campo[7], "") == 0) reg->tamanho = -1;
        else reg->tamanho = atof(campo[7]);

        // Especie
        reg->especie = (char*) malloc(tamanho_campo[8]);
        strncpy(reg->especie, campo[8], tamanho_campo[8]);

        // Alimento
        reg->alimento = (char*) malloc(tamanho_campo[9]);
        strncpy(reg->alimento, campo[9], tamanho_campo[9]);
        // Realiza a leitura do cabecalho
        leCabecalho(_arqBin, &cab);

        cab.status = '0'; // Modifica para escrita
        escreveCabecalho(_arqBin, &cab);
        // Verifica se a lista está vazia(sem campos removidos)
        if(cab.nroRegRem == 0) {
            // Dados padrões
            reg->encadeamento = -1;
            reg->removido = '0';
            // Insere no último registro(proxRRN)
            inserirRegistro(_arqBin, reg, TAMANHO_PAG + cab.proxRRN * TAMANHO_REGISTRO);
            // Incrementa o proxRRN
            ++cab.proxRRN;

            // Atualiza o número de paginas no disco
            cab.nroPagDisco = (cab.proxRRN * TAMANHO_REGISTRO + TAMANHO_PAG - 1) / TAMANHO_PAG + 1;
        }
        else {
            // Cria um registro auxiliar
            registro *regLido = criaRegistro();
            // Le o registro removido logicamente
            fseek(_arqBin->_file, TAMANHO_PAG + cab.topo * TAMANHO_REGISTRO, SEEK_SET);
            leRegistro(_arqBin, regLido);

            // Marca como não removido
            reg->encadeamento = -1;
            reg->removido = '0';

            // Insere no espaço removido
            inserirRegistro(_arqBin, reg, TAMANHO_PAG + cab.topo * TAMANHO_REGISTRO);

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

    binarioNaTela(_arqBin->nomeBin);

    free(reg);
}