#include "../include/main.h"
#include "../include/pessoa.h"
#include "../include/shop.h"


int main(void){
  int i;
  cria_shop();
  for( i= 0; i<PESSOAS;i++){
    criar_pessoa(i);
  }

  for(i=0;i<PESSOAS;i++){
    destruir_pessoa(i);
  }
  return 0;  
}