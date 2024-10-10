#include "../include/src/func1.h"

#define MAX_LINHA 2048 // Ajuste conforme necessário

// Criação de cabeçalhos e registros padrões
cabecalho cabecalho_padrao = {'0', -1, 0, 0, 1, 0};
registro registro_padrao = {'0', -1, 0, 0.0, '$', 0};

// Função para ler CSV e gravar o arquivo binário
void func1() {
    // Criação dos arquivos
    arqBin *bin = criaArqBin();
    FILE *csv;
    char csv_nome[LIMITE_TAMANHO_NOME_ARQUIVO];

    // Recebe os nomes dos arquivos
    scanf("%s", csv_nome);
    scanf("%s", bin->nomeBin);


    // Abre os arquivos de entrada e saída
    csv = fopen(csv_nome, "r");
    if (!csv) {
        printf("Falha no procesamento do arquivo.\n");
        return;
    }

    fseek(csv, 0, SEEK_SET);
    

    if (abrirArqBin(bin, 'w') != 0) {
        printf("Falha no procesamento do arquivo.\n");
        fclose(csv);
        return;
    }

    // Escrevendo o cabeçalho inicial no arquivo binário
    cabecalho cab = cabecalho_padrao;
    escreveCabecalho(bin, &cab);

    char linha[MAX_LINHA];
    
    // Descarta a linha de cabeçalho do arquivo CSV
    if (fgets(linha, sizeof(linha), csv) == NULL) {
        printf("Falha no procesamento do arquivo.\n");
        fclose(csv);
        fecharArqBin(bin);
        return;
    }

    registro *reg = criaRegistro();

    // Ler o CSV linha por linha e armazenar no arquivo binário
    while (fgets(linha, sizeof(linha), csv)) {
        //*reg = registro_padrao; // Inicializa o registro com valores padrão
        reg->removido = '0';
        reg->encadeamento = -1;
        
        // Remove o caractere de nova linha no final da linha, se existir
        size_t len = strlen(linha);
        if (len > 0 && (linha[len - 1] == '\n' || linha[len - 1] == '\r')) {
            linha[len - 1] = '\0';
        }
        
        // Separação dos campos
        int tamanhosCampos[10];
        char campos[10][TAMANHO_CAMPO_VARIAVEL_MAXIMO];
        splitString(linha, len, ',', campos, 10, tamanhosCampos);
        
        //Alocação da memória necessária para cada campo de tamanho variável
        reg->nome = (char*)malloc(tamanhosCampos[0]);
        reg->dieta = (char*)malloc(tamanhosCampos[1]);
        reg->habitat = (char*)malloc(tamanhosCampos[2]);
        reg->tipo = (char*)malloc(tamanhosCampos[4]);
        reg->especie = (char*)malloc(tamanhosCampos[8]);
        reg->alimento = (char*)malloc(tamanhosCampos[9]);
        
        //Copia dos valores do array de strings para a struct de registro
        strncpy(reg->nome, campos[0],tamanhosCampos[0]);
        strncpy(reg->dieta, campos[1],tamanhosCampos[1]);
        strncpy(reg->habitat, campos[2],tamanhosCampos[2]);
        if(strcmp(campos[3],"") == 0) reg->populacao = -1;
        else reg->populacao = atoi(campos[3]);
        strncpy(reg->tipo, campos[4],tamanhosCampos[4]);
        if(strcmp(campos[5],"") == 0) reg->velocidade = -1;
        else reg->velocidade = atoi(campos[5]);
        if(strcmp(campos[6],"") == 0) reg->unidadeMedida = '$';
        else reg->unidadeMedida = campos[6][0];
        if(strcmp(campos[7],"") == 0) reg->tamanho = -1;
        else reg->tamanho = (float)atof(campos[7]);
        strncpy(reg->especie, campos[8],tamanhosCampos[8]);
        strncpy(reg->alimento, campos[9],tamanhosCampos[9]);

        // Escreve o registro no arquivo binário, garantindo que o tamanho seja exato
        inserirRegistro(bin, reg, cab.proxRRN * TAMANHO_REGISTRO + TAMANHO_PAG);

        // Incrementa o número de registradores
        ++cab.proxRRN;
        
        // Libera memória
        free(reg->nome);
        free(reg->dieta);
        free(reg->habitat);
        free(reg->tipo);
        free(reg->especie);
        free(reg->alimento);
    }

    // Atualiza os dados do cabeçalho
    cab.status = '1'; // Arquivo consistente
    cab.nroPagDisco = (cab.proxRRN * TAMANHO_REGISTRO + TAMANHO_PAG - 1) / TAMANHO_PAG + 1;
    
    escreveCabecalho(bin, &cab);

    // Fecha ambos os arquivos
    fclose(csv);
    fecharArqBin(bin);

    // Mostra o conteúdo do arquivo binário
    binarioNaTela(bin->nomeBin);

    // Libera memória
    destroiArqBin(&bin);
    free(reg);
}
