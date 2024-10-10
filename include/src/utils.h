#ifndef UTILS_H
#define UTILS_H

// Include bibliotecas padroes do c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Include bibliotecas do projeto
#include "../dados.h"

// Captura de inteiro
// Input: _inteiro - ponteiro para a variável onde o valor inteiro lido será armazenado
void leInt(int * _inteiro);

// Captura de float
// Input: _float - ponteiro para a variável onde o valor float lido será armazenado
void leFloat(float * _float);

// Captura valores de string
// Input: string - ponteiro para a variável onde a string lida será armazenada
void leString(char * string);


// Compara strings / se for igual return 0 e se nao for return 1
// Input: string1 - primeira string a ser comparada
//        string2 - segunda string a ser comparada
// Output: 0 se as strings forem iguais, 1 se forem diferentes
int compString(char * string1, char * string2);


// Função fornecida pelo professor
// Exibe o conteúdo de um arquivo binário na tela
// Input: nomeArquivoBinario - nome do arquivo binário a ser exibido
void binarioNaTela(char *nomeArquivoBinario);

// Função fornecida pelo professor
// Lê uma string entre aspas da entrada padrão
// Input: str - ponteiro para a string onde o texto lido será armazenado
void scan_quote_string(char *str);

// Estrutura que armazena os dados de um arquivo binário
typedef struct arqBin {
  char *nomeBin; // Nome do arquivo binário
  char estado;   // Estado do arquivo (por exemplo, se está aberto ou fechado)
  FILE *_file;   // Ponteiro para o arquivo
} arqBin;

// Aloca os espaços para o arqBin e retorna o ponteiro para ele
// Output: ponteiro para a estrutura arqBin alocada
arqBin *criaArqBin();

// Destroi e desaloca o arqBin
// Input: __arqBin - ponteiro duplo para a estrutura arqBin a ser destruída
void destroiArqBin(arqBin **__arqBin);

// Captura o tamanho do arquivo (em bytes), é necessário que ele esteja aberto
// Input: _arqBin - ponteiro para a estrutura arqBin que representa o arquivo
//        tamArqBin - ponteiro para um inteiro onde o tamanho do arquivo será armazenado
// Output: 0 - sucesso | 1 - arquivo fechado
int tamanhoArqBin(arqBin *_arqBin, int *tamArqBin);


// Limpa o buffer do terminal ate achar "\n" ou "\t" ou " "
void limpaBuffer();

// Função que divide uma string em substrings
// Input: stringOrigem - string a ser dividida
//        len - tamanho da string a ser dividida
//        delimitador - caractere que delimita as substrings
//        substring - matriz onde as substrings serão armazenadas
//        numSubStrings - número de substrings a serem armazenadas
//        tamanhoSubStrings - vetor onde os tamanhos das substrings serão armazenados
void splitString(char* stringOrigem, int len, char delimitador, char substring[][TAMANHO_CAMPO_VARIAVEL_MAXIMO], int numSubStrings, int tamanhoSubStrings[]);

// Abre o arquivo binário
// Input: _arqBin - ponteiro para a estrutura arqBin que representa o arquivo
//        modo - modo de abertura do arquivo ('r' para leitura, 'w' para escrita, etc.)
// Output: 0 - sucesso | 1 - falha ao abrir o arquivo
int abrirArqBin(arqBin *_arqBin, char modo);

// Fecha o arquivo binário
// Input: _arqBin - ponteiro para a estrutura arqBin que representa o arquivo
// Output: 0 - sucesso | 1 - falha ao fechar o arquivo
int fecharArqBin(arqBin *_arqBin);

// Aloca os espacos para o cabecalho e retorna o ponteiro para ele
// Output: ponteiro para a estrutura cabecalho alocada
cabecalho *criaCabecalho();

// Destroi e desaloca o cabecalho
// Input: __cabecalho - ponteiro duplo para a estrutura cabecalho a ser destruída
void destroiCabecalho(cabecalho **__cabecalho);

// Lê o cabeçalho do arquivo binário
// Input: _arqBin - ponteiro para a estrutura arqBin que representa o arquivo
//        cab - ponteiro para a estrutura de cabeçalho onde os dados lidos serão armazenados
// Output: 0 - sucesso | 1 - falha ao ler o cabeçalho
int leCabecalho(arqBin *_arqBin, cabecalho *cab);

// Aloca os espacos para o registro e retorna o ponteiro para ele
// Output: ponteiro para a estrutura registro alocada
registro *criaRegistro();

// Destroi e desaloca o registro
// Input: __registro - ponteiro duplo para a estrutura registro a ser destruída
void destroiRegistro(registro **__registro);

// Le byte por byte ate encontrar o #
// Input: _arqBin - ponteiro para a estrutura arqBin que representa o arquivo
//        __campo - ponteiro para a string onde o campo lido será armazenado
void leCampoVariavel(arqBin *_arqBin, char **__campo);

// Escreve o registro em arqBin
// Input: _arqBin - ponteiro para a estrutura arqBin que representa o arquivo
//        _registro - ponteiro para a estrutura registro que será escrita
// Output: 0 - sucesso | 1 - falha ao escrever o registro

int leRegistro(arqBin *_arqBin, registro *_registro);

// Printa o registro
// Input: _registro - ponteiro para a estrutura registro que será impressa
void printRegistro(registro *_registro);

// Escreve o cabeçalho em arqBin
// Input: _arqBin - ponteiro para a estrutura arqBin que representa o arquivo
//        _cabecalho - ponteiro para a estrutura cabecalho que será escrita
// Output: 0 - sucesso | 1 - falha ao escrever o cabeçalho
int escreveCabecalho(arqBin * _arqBin, cabecalho * _cabecalho);

// Escreve um campo variável em arqBin
// Input: _arqBin - ponteiro para a estrutura arqBin que representa o arquivo
//        campo - string que será escrita
// Output: 0 - sucesso | 1 - falha ao escrever o campo
int escreveCampoVariavel(arqBin * _arqBin, char * campo);

// Insere um registro em um arquivo binário
// Input: _arqBin - ponteiro para a estrutura arqBin que representa o arquivo
//        _registro - ponteiro para a estrutura registro que será inserida
//        seekpoint - posição onde o registro será inserido
// Output: 0 - sucesso | 1 - falha ao inserir o registro
int inserirRegistro(arqBin * _arqBin, registro * _registro, int seekpoint);

// Cria um arquivo binário
// Input: _arqBin - ponteiro para a estrutura arqBin que representa o arquivo
void criarArquivo(arqBin * _arqBin);

#endif // UTILS_H