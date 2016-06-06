#include "../include/main.h"
#include "../include/pessoa.h"
#include "../include/shop.h"
#include "../include/loja.h"
#include "../include/carro.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(void){
  int i;
  srand(time(NULL)); // Inicializando seed randomica
  
  cria_shop(); // Inicializa matriz do mapa

  for (i = 0; i < LOJAS; ++i){
    criar_loja(i);
  }
  print_init(); // inicializa impressão do mapa
  for (i=0;i< PESSOAS; ++i){
    criar_pessoa(i);
  }
  for (i = 0; i < CARROS; ++i){
    criar_carro(i);
  }

  // Somente a finalização das pessoas é aguardada
  for(i=0;i<PESSOAS;i++){
    destruir_pessoa(i);
  }
  return 0;  
}