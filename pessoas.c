#include "pessoa.h"
#include "shop.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>


#define PESSOAS 5

pthread_t pessoas[PESSOAS];

void* cliente(void *arg){
  pessoa* ps = ((pessoa *) arg);
  // int id = ps->id;
  inicia_pessoa(ps->cel);


  celula* prox = malloc(sizeof(celula));
  printf("%d\n",ps->cel->linha );
  // prox->linha = ps->cel->linha ;
  // prox->coluna = ps->cel->coluna ;
  mover(ps->cel,prox);
  
  free(ps);
  pthread_exit(0);
}
void criar_pessoa(int id){
  pessoa* ps = malloc(sizeof(*ps));
  ps->cel = malloc(sizeof(*ps->cel));
  ps->id = id;
  pthread_create(&pessoas[id],NULL,cliente,(void *) (ps));
}
void destruir_pessoa(int id){
  pthread_join(pessoas[id],NULL);
}
int main(void){
  int i;
  cria_shop();
  for( i= 0; i<PESSOAS;i++){
    criar_pessoa(i);
  }

  imprime_shop();
  for(i=0;i<PESSOAS;i++){
    destruir_pessoa(i);
  }
  return 0;  
}

