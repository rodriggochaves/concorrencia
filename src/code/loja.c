#include "../include/loja.h"
#include "../include/shop.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

pthread_t lojas[LOJAS];
char sim = 'A';

void* loja_thread(void* arg){

  pthread_exit(0);
}

void criar_loja(int id){
  loja* lj = malloc(sizeof(loja));
  lj->pos = malloc(sizeof(celula));
  lj->id = id;
  lj->sim = sim + 1;
  lj->pos = celula_char(LOJA_INIT_CHAR,id+1);
  pthread_create(&lojas[id],NULL,loja_thread,(void*) (lj));
}

int total_lojas(){
  return LOJAS
}
void destruir_loja(int id){
  pthread_join(lojas[id],NULL);
}