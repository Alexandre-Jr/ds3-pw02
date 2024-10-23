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
    func5plus();
    break;
  case 10:
    
    // Caso para DEBUG facil
    arvoreb * _arvb;
    criaArvoreb(&_arvb);

    char v[] = "indiceDino8.bin";

    _arvb->abrirArquivo(_arvb, v);
    char arq[] = "Gabarito.txt";
    fprintArvoreb(_arvb, arq);
    /*
   char nome[] = "pterodactilus";
    printf("%ld", converteNome(nome));*/
    break;
  }

return 0;
}