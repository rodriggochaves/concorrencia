#include "../include/loja.h"
#include "../include/shop.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

pthread_t lojas[LOJAS]

void* loja_thread(void* arg){

  pthread_exit(0);
}

void criar_loja(int id){
  loja* lj = malloc(sizeof(loja));
  lj->pos = malloc(sizeof(celula));
  lj->id = id;
  pthread_create(&lojas[id],NULL,loja_thread,(void*) (lj));
}

void destruir_loja(int id){
  pthread_join(lojas[id],NULL);
}