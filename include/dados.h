#ifndef DADOS_H
#define DADOS_H

#include <stdio.h>

#define TAMANHO_REGISTRO 160
#define TAMANHO_CAMPO_VARIAVEL_MAXIMO 142
#define LIMITE_TAMANHO_NOME_ARQUIVO 25
#define LIMITE_TAMANHO_NOME_CAMPO 25
#define TAMANHO_PAG 1600

typedef struct {
  char status;
  int topo;
  int proxRRN;
  int nroRegRem;
  int nroPagDisco;
  int qttCompacta;
} cabecalho;

typedef struct {
  char removido;
  int encadeamento;
  int populacao;
  float tamanho;
  char unidadeMedida;
  int velocidade;
  char *nome;
  char *especie;
  char *habitat;
  char *tipo;
  char *dieta;
  char *alimento;
} registro;

#endif // DADOS_H