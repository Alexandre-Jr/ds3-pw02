#ifndef BTREE_H
#define BTREE_H




// Include as bibliotecas padroes
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include dados.h
#include "../../../include/src/utils.h"



// Define constantes

#define ORDEM_ARVOREB 5
#define TAMANHO_PAG_ARVOREB 93


// Define as estruturas da arvore B

typedef long int tipo_chave;

typedef struct arvorebElemento
{
    tipo_chave chave;
    long int pr;
} arvorebElemento;

typedef struct arvorebCabecalho
{
    char status;
    int noRaiz;
    int RRNproxNo;
} arvorebCabecalho;

typedef struct arvorebRegistro
{
    char folha;
    int nroChavesNo;
    int RRNdoNo;
    arvorebElemento * elementos;
    int * ponteiros;
} arvorebRegistro;

typedef struct arvoreb
{
    arqBin * _arq;

    // Funcoes
    
    // Abrir o arquivo da arvoreb
    int (*abrirArquivo)(arvoreb * _arvoreb, char * nomeArquivo);

    // Abrir o arquivo da arvoreb
    int (*fecharArquivo)(arvoreb * _arvoreb);

    // Destroi a estrutura arvoreb e desaloca o espaco necessario (retorna 1 - erro e retorna 0 - sucesso)
    int (*criaArquivoArvoreb)(arvoreb * _arvoreb, char * nomeArquivo);

    // Insere o cabecalho no arquivo arvoreb
    int (*insereCabecalho)(arvoreb * _arvoreb, arvorebCabecalho * _arvorebCabecalho);

    // Le o cabecalho no arquivo arvoreb
    int (*leCabecalho)(arvoreb * _arvoreb, arvorebCabecalho * _arvorebCabecalhoDestino);

    // Le o registro no arquivo arvoreb
    int (*leRegistro)(arvoreb * _arvoreb, arvorebRegistro * _arvorebRegistroDestino, int RRN);

    // Insere o elemento no arquivo arvoreb
    int (*insereElemento)(arvoreb * _arvoreb, arvorebElemento * _arvorebElemento);

    // Pesquisa um elemento por uma chave na arvoreb e insere uma copia em _arvorebElementoDestino
    int (*pesquisaChave)(arvoreb * _arvoreb, tipo_chave chaveBusca, arvorebElemento * _arvorebElementoDestino);


} arvoreb;



// Funcoes


// Funcoes da arvorebRegistro

// Cria a estrutura arvorebRegistro e aloca o espaco necessario (retorna 1 - erro e retorna 0 - sucesso)
int criaArvorebRegistro(arvorebRegistro ** __arvorebRegistro);

// Limpa a estrutura arvorebRegistro, mas nao desaloca o espaco necessario (retorna 1 - erro e retorna 0 - sucesso)
int limpaArvorebRegistro(arvorebRegistro * _arvorebRegistro);

// Destroi a estrutura arvorebRegistro e desaloca o espaco necessario (retorna 1 - erro e retorna 0 - sucesso)
int destroiArvorebRegistro(arvorebRegistro ** __arvorebRegistro);


// Funcoes da arvorebCabecalho

// Cria a estrutura arvorebCabecalho e aloca o espaco necessario (retorna 1 - erro e retorna 0 - sucesso)
int criaArvorebCabecalho(arvorebCabecalho ** __arvorebCabecalho);

// Destroi a estrutura arvorebCabecalho e desaloca o espaco necessario (retorna 1 - erro e retorna 0 - sucesso)
int destroiArvorebCabecalho(arvorebCabecalho ** __arvorebCabecalho);


// Funcoes da arvoreb

// Abrir o arquivo da arvoreb
int arvoreb_abrirArquivo(arvoreb * _arvoreb, char * nomeArquivo);

// Fecha o arquivo da arvoreb (retorna 1 - erro e retorna 0 - sucesso)
int arvoreb_fecharArquivo(arvoreb * _arvoreb);

// Destroi a estrutura arvoreb e desaloca o espaco necessario (retorna 1 - erro e retorna 0 - sucesso)
int arvoreb_criaArquivoArvoreb(arvoreb *__arvoreb, char * nomeArquivo);


// Insere o cabecalho no arquivo arvoreb (retorna 1 - erro e retorna 0 - sucesso)
int arvoreb_insereCabecalho(arvoreb * _arvoreb, arvorebCabecalho * _arvorebCabecalho);

// Le o cabecalho no arquivo arvoreb (retorna 1 - erro e retorna 0 - sucesso)
int arvoreb_leCabecalho(arvoreb * _arvoreb, arvorebCabecalho * _arvorebCabecalhoDestino);


// Insere o registro no arquivo arvoreb (retorna 1 - erro e retorna 0 - sucesso)
int escreveArvorebRegistro(arvoreb * _arvoreb, arvorebRegistro * _arvorebRegistro, int RRN);

// Le o registro no arquivo arvoreb (retorna 1 - erro e retorna 0 - sucesso)
int arvoreb_leRegistro(arvoreb * _arvoreb, arvorebRegistro * _arvorebRegistroDestino, int RRN);


// Pesquisa um elemento por uma chave na arvoreb e insere uma copia em _arvorebElementoDestino (retorna 1 - erro e retorna 0 - sucesso)
int arvoreb_pesquisaChave(arvoreb * _arvoreb, tipo_chave chaveBusca, arvorebElemento * _arvorebElementoDestino);


// Insere o elemento no arquivo arvoreb (retorna 1 - erro e retorna 0 - sucesso)
int arvoreb_insereElemento(arvoreb * _arvoreb, arvorebElemento * _arvorebElemento);

// Funcao debug print todos os elementos e cabecarios da arvore b
int printArvoreb(arvoreb * _arvoreb);

int fprintArvoreb(arvoreb * _arvoreb, char * _nome_file);

// Cria a estrutura arvorebCabecalho e aloca o espaco necessario (retorna 1 - erro e retorna 0 - sucesso)
int criaArvoreb(arvoreb ** __arvoreb);

// Destroi a estrutura arvoreb e desaloca o espaco necessario (retorna 1 - erro e retorna 0 - sucesso)
int destroiArvoreb(arvoreb ** __arvoreb);

#endif