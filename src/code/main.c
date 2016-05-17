#include "../include/main.h"
#include "../include/pessoa.h"
#include "../include/shop.h"
#include "../include/loja.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(void){
  int i;
  srand(time(NULL)); // Inicializando seed randomica
  
  cria_shop();

  for (i = 0; i < LOJAS; ++i){
    criar_loja(i);
  }
  for(i = 0; i<PESSOAS;i++){
    criar_pessoa(i);
  }

  // É relevante somente a finalização das pessoas
  for(i=0;i<PESSOAS;i++){
    destruir_pessoa(i);
  }
  imprime_shop();
  return 0;  
}