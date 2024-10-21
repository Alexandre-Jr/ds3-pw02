#include <stdio.h>
#include "./include/src/func1.h"
#include "./include/src/func2.h"
#include "./include/src/func3.h"
#include "./include/src/func4.h"
#include "./include/src/func5.h"
#include "./include/src/func6.h"
#include "./include/src/func7.h"
#include "./include/src/func8.h"
#include "./include/src/func9.h"
#include "./include/src/structs/arvoreb.h"


int main(void) {
  
  int opc;
  scanf("%d", &opc);
  switch (opc) {
  case 1:
    func1();
    break;
  case 2:
    func2();
    break;
  case 3:
    func3();
    break;
  case 4:
    func4();
    break;
  case 5:
    func5();
    break;
  case 6:
    func6();
    break;
  case 7:
    func7();
    break;
  case 8:
    func8();
    break; 
  case 9:
    func9();
    break;
  }


  // Para Eler um arquivo indice arvore b
  /*
  arvoreb * _arvb;
  criaArvoreb(&_arvb);

  char v[] = "bin.bin";

  _arvb->abrirArquivo(_arvb, v);
  
  printArvoreb(_arvb);*/

  return 0;
}