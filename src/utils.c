// Link
#include "../include/src/utils.h"

// Escreve o cabecalho em arqBin
int escreveCabecalho(arqBin * _arqBin, cabecalho * _cabecalho) {
    // Verifica se o arqbin foi criado
    if (_arqBin == NULL) {
        return 1;
    }

    // Verifica se o arquivo esta aberto
    if (_arqBin->_file == NULL || (_arqBin->estado != 'w' && _arqBin->estado != 's')) {
        return 1;
    }

    // Verifica se o registro existe
    if (_cabecalho == NULL) {
        return 2;
    }

    // Inferir a posicao inicio do pointeiro do arquivo
    fseek(_arqBin->_file, 0, SEEK_SET);

    // Caracter nulo
    char nullChar = '$';

    // Preenche uma pagina com caracter nulo
    for (int i = 0; i < TAMANHO_PAG; i++) {
        fwrite(&nullChar, sizeof(char), 1, _arqBin->_file);
    }

    // Inferir a posicao inicio do pointeiro do arquivo
    fseek(_arqBin->_file, 0, SEEK_SET);

    // Insere os valores do cabecalho
    fwrite(&_cabecalho->status, sizeof(char), 1, _arqBin->_file);
    fwrite(&_cabecalho->topo, sizeof(int), 1, _arqBin->_file);
    fwrite(&_cabecalho->proxRRN, sizeof(int), 1, _arqBin->_file);
    fwrite(&_cabecalho->nroRegRem, sizeof(int), 1, _arqBin->_file);
    fwrite(&_cabecalho->nroPagDisco, sizeof(int), 1, _arqBin->_file);
    fwrite(&_cabecalho->qttCompacta, sizeof(int), 1, _arqBin->_file);

    return 0;
}

int escreveCampoVariavel(arqBin * _arqBin, char * campo) {

    if (campo == NULL) {
        return 1;
    }

    for (int i = 0; campo[i] != '\0'; i++) {
        fwrite(&campo[i], sizeof(char), 1, _arqBin->_file);
    }
    return 0;
}

//Separa string por delimitador

// Escreve um registro em arqBin
int inserirRegistro(arqBin * _arqBin, registro * _registro, int seekpoint) {
    // Verifica se o arqbin foi criado
    if (_arqBin == NULL) {
        return 1;
    }

    // Verifica se o arquivo esta aberto
    if (_arqBin->_file == NULL || (_arqBin->estado != 'w' && _arqBin->estado != 's')) {
        return 1;
    }

    // Verifica se o registro existe
    if (_registro == NULL) {
        return 2;
    }

    // Preenche o espaco de um registro com o nulo
    // Caracter nulo
    char nullChar = '$';
    fseek(_arqBin->_file, seekpoint, SEEK_SET);

    for (int i = 0; i < TAMANHO_REGISTRO; i++) {
        fwrite(&nullChar, sizeof(char), 1, _arqBin->_file);
    }

    fseek(_arqBin->_file, seekpoint, SEEK_SET);

    // Efetua escrita de parametros fixos
    fwrite(&_registro->removido, sizeof(char), 1, _arqBin->_file);
    fwrite(&_registro->encadeamento, sizeof(int), 1, _arqBin->_file);
    fwrite(&_registro->populacao, sizeof(int), 1, _arqBin->_file);
    fwrite(&_registro->tamanho, sizeof(float), 1, _arqBin->_file);
    fwrite(&_registro->unidadeMedida, sizeof(char), 1, _arqBin->_file);
    fwrite(&_registro->velocidade, sizeof(int), 1, _arqBin->_file);

    // Delimitador
    char delimitador = '#';

    // Efetua escrita de campos variados
    escreveCampoVariavel(_arqBin, _registro->nome);
    fwrite(&delimitador, sizeof(char), 1, _arqBin->_file);
    escreveCampoVariavel(_arqBin, _registro->especie);
    fwrite(&delimitador, sizeof(char), 1, _arqBin->_file);
    escreveCampoVariavel(_arqBin, _registro->habitat);
    fwrite(&delimitador, sizeof(char), 1, _arqBin->_file);
    escreveCampoVariavel(_arqBin, _registro->tipo);
    fwrite(&delimitador, sizeof(char), 1, _arqBin->_file);
    escreveCampoVariavel(_arqBin, _registro->dieta);
    fwrite(&delimitador, sizeof(char), 1, _arqBin->_file);
    escreveCampoVariavel(_arqBin, _registro->alimento);
    fwrite(&delimitador, sizeof(char), 1, _arqBin->_file);
    return 0;
}


// Efetivamente cria um arquivo abrindo-o com a flag w
void criarArquivo(arqBin * _arqBin) {
    abrirArqBin(_arqBin, 'w');
    fecharArqBin(_arqBin);
}

// Captura de inteiro
void leInt(int * _inteiro) {
    scanf("%d", _inteiro);
}

void leFloat(float * _float) {
    scanf("%f", _float);
}

// Captura valores de string
void leString(char * string) {
    // Variaveis de leitura e contagem
    int i = 0;
    char c;


    c = getchar();

    // Loop ate ler "\n" ou "\t" ou " "
    for(; c != '\n' & c != '\t' & c != ' '; i++) {
        string[i] = c;
        c = getchar();
    }

    // Insere o sinal de termino da string
    string[i] = '\0';
}

// Compara strings / se for igual return 0 e se nao for return 1
int compString(char * string1, char * string2) {
    for (int i = 0; string1[i] != '\0'; i++) {
        if (string1[i] != string2[i]) {
            return 1;
        }
    }
    return 0;
}

void binarioNaTela(char *nomeArquivoBinario) { /* Você não precisa entender o código dessa função. */

  /* Use essa função para comparação no run.codes. Lembre-se de ter fechado (fclose) o arquivo anteriormente.
  *  Ela vai abrir de novo para leitura e depois fechar (você não vai perder pontos por isso se usar ela). */

  unsigned long i, cs;
  unsigned char *mb;
  size_t fl;
  FILE *fs;
  if(nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
    fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela): não foi possível abrir o arquivo que me passou para leitura. Ele existe e você tá passando o nome certo? Você lembrou de fechar ele com fclose depois de usar?\n");
    return;
  }
  fseek(fs, 0, SEEK_END);
  fl = ftell(fs);
  fseek(fs, 0, SEEK_SET);
  mb = (unsigned char *) malloc(fl);
  fread(mb, 1, fl, fs);

  cs = 0;
  for(i = 0; i < fl; i++) {
    cs += (unsigned long) mb[i];
  }
  printf("%lf\n", (cs / (double) 100));
  free(mb);
  fclose(fs);
}

void scan_quote_string(char *str) {

	/*
	*	Use essa função para ler um campo string delimitado entre aspas (").
	*	Chame ela na hora que for ler tal campo. Por exemplo:
	*
	*	A entrada está da seguinte forma:
	*		nomeDoCampo "MARIA DA SILVA"
	*
	*	Para ler isso para as strings já alocadas str1 e str2 do seu programa, você faz:
	*		scanf("%s", str1); // Vai salvar nomeDoCampo em str1
	*		scan_quote_string(str2); // Vai salvar MARIA DA SILVA em str2 (sem as aspas)
	*
	*/

	char R;

	while((R = getchar()) != EOF && isspace(R)); // ignorar espaços, \r, \n...

	if(R == 'N' || R == 'n') { // campo NULO
		getchar(); getchar(); getchar(); // ignorar o "ULO" de NULO.
		strcpy(str, ""); // copia string vazia
	} else if(R == '\"') {
		if(scanf("%[^\"]", str) != 1) { // ler até o fechamento das aspas
			strcpy(str, "");
		}
		getchar(); // ignorar aspas fechando
	} else if(R != EOF){ // vc tá tentando ler uma string que não tá entre aspas! Fazer leitura normal %s então, pois deve ser algum inteiro ou algo assim...
		str[0] = R;
		scanf("%s", &str[1]);
	} else { // EOF
		strcpy(str, "");
	}
}

// Aloca os espacos para o arqBin e retorna o ponteiro para ele
arqBin * criaArqBin() {
    arqBin * _arqBin = (arqBin *) malloc(sizeof(arqBin));

    _arqBin->estado = '0';
    _arqBin->nomeBin = (char *) malloc(LIMITE_TAMANHO_NOME_ARQUIVO * sizeof(char));
    _arqBin->_file = NULL;

    return _arqBin;
}

// Destroi e desaloca o arqbin
void destroiArqBin(arqBin ** __arqBin) {

    if ((*__arqBin)->nomeBin != NULL) {
        free((*__arqBin)->nomeBin);
        (*__arqBin)->nomeBin = NULL;
    }

    if ((*__arqBin)->_file != NULL) {
        fclose((*__arqBin)->_file);
        (*__arqBin)->estado = '0';
        (*__arqBin)->_file = NULL;
    }

    if ((*__arqBin) != NULL) {
        free((*__arqBin));
        (*__arqBin) = NULL;
    }
}

// Captura o tamanho do arquivo (em bytes), é necessario que ele esteja aberto
// Output: 0 - sucesso | 1 - arquivo fechado
int tamanhoArqBin(arqBin * _arqBin, int * tamArqBin) {
    // Verifica se o arqbin foi criado
    if (_arqBin == NULL) {
        return 1;
    }

    // Verifica se o arquivo esta aberto
    if (_arqBin->_file == NULL || (_arqBin->estado != 'r' && _arqBin->estado != 's')) {
        return 1;
    }

    // Vai ate o fim do arquivo
    fseek(_arqBin->_file, 0, SEEK_END);

    // Captura o tamanho do arquivo
    (*tamArqBin) = (int) ftell(_arqBin->_file);

    // Retorna ao inicio do arquivo
    fseek(_arqBin->_file, 0, SEEK_SET);

    return 0;
}


// Limpa o buffer do terminal ate achar "\n" ou "\t" ou " "
void limpaBuffer() {
    char c;
    c = getchar();
    while (c != '\n' & c != '\t' & c != ' '){
        c = getchar();
    }
}

// Função para separação de string em substrings de acordo com um delimitador
void splitString(char* stringOrigem, int len, char delimitador, char substring[][TAMANHO_CAMPO_VARIAVEL_MAXIMO], int numSubStrings, int tamanhoSubStrings[]) {
    int it_campo = 0, it_string = 0;

    // Inicializa todas as substrings com strings vazias
    for (int i = 0; i < numSubStrings; ++i) {
        strcpy(substring[i], ""); 
    }

    // Percorre a string de origem para separar substrings
    for (int i = 0; i < len; ++i) {
        if (stringOrigem[i] == delimitador || stringOrigem[i] == '\0' || stringOrigem[i] == 13) { // Se achar o delimitador, finaliza a substring atual
            substring[it_campo][it_string] = '\0'; // Finaliza a string atual
            tamanhoSubStrings[it_campo] = it_string + 1; // Conta o '\0'
            it_string = 0; // Reseta o índice da próxima substring
            ++it_campo; // Vai para a próxima substring
            if (it_campo >= numSubStrings) break; // Limita ao número de substrings
        } else {
            substring[it_campo][it_string] = stringOrigem[i]; // Escreve na substring atual
            ++it_string;
        }
        if (i + 1 == len && stringOrigem[i] != delimitador && stringOrigem[i] != '\0' && stringOrigem[i] != 13) { // Ultima substring

            it_string++;
            tamanhoSubStrings[it_campo] = it_string;
        }
    }
    // Finaliza a última substring
    substring[it_campo][it_string] = '\0';
}

// Output: 0 - Sucesso e 1 - Fracasso por registro inesistente
int abrirArqBin(arqBin * _arqBin, char tipeDeAbertura) {

    // Confere se o arquivo nao foi aberto
    if (_arqBin->_file == NULL) {

        // Abre o arquivo da maneira selecionada
        if (tipeDeAbertura == 'w') {

            _arqBin->_file = fopen(_arqBin->nomeBin, "wb");
            _arqBin->estado = 'w';

        } else if (tipeDeAbertura == 'r') {

            _arqBin->_file = fopen(_arqBin->nomeBin, "rb");
            _arqBin->estado = 'r';

        } else if (tipeDeAbertura == 's') {

            _arqBin->_file = fopen(_arqBin->nomeBin, "rb+");
            _arqBin->estado = 's';

        } else {

            return 1;

        }

        // Se o arquvo nao foi possivel de abrir
        if (_arqBin->_file == NULL) {
            _arqBin->estado = '0';
            return 1;
        }

        return 0;

    }

    if (tipeDeAbertura == 'w' && _arqBin->estado != 'w') {

        fclose(_arqBin->_file);
        _arqBin->_file = fopen(_arqBin->nomeBin, "wb");
        _arqBin->estado = 'w';

        // Se o arquivo nao foi possivel de abrir
        if (_arqBin->_file == NULL) {
            _arqBin->estado = '0';
            return 1;
        }

        return 0;
    }

    if (tipeDeAbertura == 's' && _arqBin->estado != 's') {

        fclose(_arqBin->_file);
        _arqBin->_file = fopen(_arqBin->nomeBin, "rb+");
        _arqBin->estado = 's';

        // Se o arquivo nao foi possivel de abrir
        if (_arqBin->_file == NULL) {
            _arqBin->estado = '0';
            return 1;
        }

        return 0;

    }

    if (tipeDeAbertura == 'r' && _arqBin->estado != 'r') {

        fclose(_arqBin->_file);
        _arqBin->_file = fopen(_arqBin->nomeBin, "rb");
        _arqBin->estado = 'r';

        // Se o arquivo nao foi possivel de abrir
        if (_arqBin->_file == NULL) {
            _arqBin->estado = '0';
            return 1;
        }

        return 0;

    }

    if (_arqBin->_file == NULL) {
        _arqBin->estado = '0';
        return 1;
    }

    return 0;
}

// Output: 0 - Sucesso e 1 - Arquivo ja fechado ou nao aberto
int fecharArqBin(arqBin * _arqBin) {
    if ((_arqBin)->_file != NULL) {
        fclose((_arqBin)->_file);
        (_arqBin)->estado = '0';
        (_arqBin)->_file = NULL;
        return 0;
    }
    return 1;
}


// Aloca os espacos para o cabecalho e retorna o ponteiro para ele
cabecalho * criaCabecalho() {
    cabecalho * _cabecalho = (cabecalho *) malloc(sizeof(cabecalho));
    return _cabecalho;
}

// Destroi e desaloca o cabecalho
void destroiCabecalho(cabecalho ** __cabecalho) {
    if (*__cabecalho != NULL) {
        free(*__cabecalho);
        *__cabecalho == NULL;
    }
}

// Output: 0 - Sucesso | 1 - Arquivo nao aberto ou criado | 2 - Cabecalho nao criado
int leCabecalho(arqBin * _arqBin, cabecalho * _cabecalho) {
    // Verifica se o arqbin foi criado
    if (_arqBin == NULL) {
        return 1;
    }

    // Verifica se o arquivo esta aberto
    if (_arqBin->_file == NULL || (_arqBin->estado != 'r' && _arqBin->estado != 's')) {
        return 1;
    }

    // Verifica se o cabecalho existe
    if (_cabecalho == NULL) {
        return 2;
    }

    // Coloca o ponteiro do arquivo no inicio do arquivo
    fseek(_arqBin->_file, 0, SEEK_SET);

    // Efetua a leitura
    fread(&_cabecalho->status, sizeof(char), 1, _arqBin->_file);
    fread(&_cabecalho->topo, sizeof(int), 1, _arqBin->_file);
    fread(&_cabecalho->proxRRN, sizeof(int), 1, _arqBin->_file);
    fread(&_cabecalho->nroRegRem, sizeof(int), 1, _arqBin->_file);
    fread(&_cabecalho->nroPagDisco, sizeof(int), 1, _arqBin->_file);
    fread(&_cabecalho->qttCompacta, sizeof(int), 1, _arqBin->_file);

    return 0;
}



// Aloca os espacos para o registro e retorna o ponteiro para ele
registro * criaRegistro() {
    registro * _registro = (registro *) malloc(sizeof(registro));

    _registro->nome = NULL;
    _registro->especie = NULL;
    _registro->habitat = NULL;
    _registro->tipo = NULL;
    _registro->dieta = NULL;
    _registro->alimento = NULL;

    return _registro;
}

// Destroi e desaloca o registro
void destroiRegistro(registro ** __registro) {

    if ((*__registro)->nome != NULL) {
        free((*__registro)->nome);
        (*__registro)->nome = NULL;
    }

    if ((*__registro)->especie != NULL) {
        free((*__registro)->especie);
        (*__registro)->especie = NULL;
    }

    if ((*__registro)->habitat != NULL) {
        free((*__registro)->habitat);
        (*__registro)->habitat = NULL;
    }

    if ((*__registro)->tipo != NULL) {
        free((*__registro)->tipo);
        (*__registro)->tipo = NULL;
    }

    if ((*__registro)->dieta != NULL) {
        free((*__registro)->dieta);
        (*__registro)->dieta = NULL;
    }

    if ((*__registro)->alimento != NULL) {
        free((*__registro)->alimento);
        (*__registro)->alimento = NULL;
    }

    if (*__registro != NULL) {
        free(*__registro);
        *__registro = NULL;
    }

}

// Le byte por byte ate encontrar o #
void leCampoVariavel(arqBin * _arqBin, char ** __campo) {
    char c;
    char * buffer = (char *) malloc(sizeof(char) * TAMANHO_CAMPO_VARIAVEL_MAXIMO);
    int tamanhoBuffer = 1;

    // Primeira leitura
    fread(&c, sizeof(char), 1, _arqBin->_file);

    // Verifica se o campo é nulo
    if (c == '#') {
        *__campo = NULL;
        return;
    }

    // Loop de leitura até encontrar #
    while(c != '#') {
        buffer[tamanhoBuffer - 1] = c;
        fread(&c, sizeof(char), 1, _arqBin->_file);
        tamanhoBuffer++;
    }

    // Adiciona o \0
    buffer[tamanhoBuffer - 1] = '\0';

    // Aloca o espaço necessário em __campo
    *__campo = (char *) malloc(sizeof(char) * tamanhoBuffer);

    // Copia o valor de buffer em *__campo
    strncpy(*__campo, buffer, tamanhoBuffer);

    // Libera espaço
    free(buffer);
}


// Output: 0 - Sucesso | 1 - Arquivo nao aberto ou criado | 2 - Cabecalho nao criado
int leRegistro(arqBin * _arqBin, registro * _registro) {
    // Verifica se o arqbin foi criado
    if (_arqBin == NULL) {
        return 1;
    }

    // Verifica se o arquivo está aberto
    if (_arqBin->_file == NULL || (_arqBin->estado != 'r' && _arqBin->estado != 's')) {
        return 1;
    }

    // Verifica se o registro existe
    if (_registro == NULL) {
        return 2;
    }

    // Efetua leitura de parâmetros fixos
    fread(&_registro->removido, sizeof(char), 1, _arqBin->_file);
    fread(&_registro->encadeamento, sizeof(int), 1, _arqBin->_file);

    if (_registro->removido == '1') {
        return 0;
    }

    fread(&_registro->populacao, sizeof(int), 1, _arqBin->_file);
    fread(&_registro->tamanho, sizeof(float), 1, _arqBin->_file);
    fread(&_registro->unidadeMedida, sizeof(char), 1, _arqBin->_file);
    fread(&_registro->velocidade, sizeof(int), 1, _arqBin->_file);

    // Efetua leitura de campos variados
    leCampoVariavel(_arqBin, &_registro->nome);
    leCampoVariavel(_arqBin, &_registro->especie);
    leCampoVariavel(_arqBin, &_registro->habitat);
    leCampoVariavel(_arqBin, &_registro->tipo);
    leCampoVariavel(_arqBin, &_registro->dieta);
    leCampoVariavel(_arqBin, &_registro->alimento);

    return 0;
}


// Printa o registro
void printRegistro(registro * _registro) {
    if(_registro->removido == '1') {
        return;
    }

    if (_registro->nome != NULL) {
        printf("Nome: %s\n", _registro->nome);
    }

    if (_registro->especie != NULL) {
        printf("Especie: %s\n", _registro->especie);
    }

    if (_registro->tipo != NULL) {
        printf("Tipo: %s\n", _registro->tipo);
    }

    if (_registro->dieta != NULL) {
        printf("Dieta: %s\n", _registro->dieta);
    }

    if (_registro->habitat != NULL) {
        printf("Lugar que habitava: %s\n", _registro->habitat);
    }

    if (_registro->tamanho != -1) {
        printf("Tamanho: %.1f m\n", _registro->tamanho);
    }

    if (_registro->velocidade != -1) {

        printf("Velocidade: %d %cm/h\n", _registro->velocidade, _registro->unidadeMedida);

    }


    printf("\n");
}


