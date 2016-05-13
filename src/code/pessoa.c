#include "../include/pessoa.h"
#include "../include/shop.h"



#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>


#define PESSOAS 5

pthread_t pessoas[PESSOAS];
pthread_mutex_t print = PTHREAD_MUTEX_INITIALIZER;

void* cliente(void *arg){
  int i;
  pessoa* ps = ((pessoa *) arg);
  celula* prox = malloc(sizeof(celula));

  // int id = ps->id;
  inicia_pessoa(ps->cel);

  prox->linha = ps->cel->linha;
  prox->coluna = ps->cel->coluna + 1;

  for (i = 0; i < 10; ++i){
    if(!mover(ps->cel,prox)){
      ps->cel->linha = prox->linha;
      ps->cel->coluna = prox->coluna;
    }
    pthread_mutex_lock(&print);
    imprime_shop();
    printf("linha:%dcoluna:%d\n", ps->cel->linha,ps->cel->coluna );
    pthread_mutex_unlock(&print);
    prox->coluna += 1;
  }
  // prox->linha = ps->cel->linha ;
  // prox->coluna = ps->cel->coluna ;
  
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

  for(i=0;i<PESSOAS;i++){
    destruir_pessoa(i);
  }
  return 0;  
}

