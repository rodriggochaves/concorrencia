#include "../include/main.h"
#include "../include/pessoa.h"
#include "../include/shop.h"
#include "../include/loja.h"
#include <stdio.h>

int main(void){
  int i;
  cria_shop();

  for( i= 0; i<PESSOAS;i++){
    criar_pessoa(i);
  }
  for(i=0;i<PESSOAS;i++){
    destruir_pessoa(i);
  }
  imprime_shop();
  return 0;  
}