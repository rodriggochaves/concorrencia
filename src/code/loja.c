#include "../include/loja.h"
#include "../include/shop.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

pthread_t lojas[LOJAS];
loja* dados_lojas[LOJAS];

char sim = 'A';

void* loja_thread(void* arg){

  pthread_exit(0);
}

void criar_loja(int id){
  printf("%d\n", id);
  loja* lj = malloc(sizeof(loja));
  lj->pos = malloc(sizeof(celula));
  lj->id = id;
  lj->sim = sim + id;
  lj->pos = celula_char(LOJA_INIT_CHAR,id+1);
  dados_lojas[id] = lj;   // Torna acessivel os dados das lojas por id
  pthread_create(&lojas[id],NULL,loja_thread,(void*) (lj));
}

int total_lojas(){
  return LOJAS;
}

celula* pos_loja(int id){
  return dados_lojas[id]->pos;
}

void destruir_loja(int id){
  pthread_join(lojas[id],NULL);
}