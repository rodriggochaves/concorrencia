#include "../include/loja.h"
#include "../include/shop.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

pthread_t lojas[LOJAS];
pthread_cond_t estoque_cond[LOJAS];
pthread_mutex_t lj_lock[LOJAS];
sem_t filas[LOJAS];
sem_t atendimento[LOJAS];
loja* dados_lojas[LOJAS];

void vender(int* estoque,int id){
  pthread_mutex_lock(&lj_lock[id]);
  if(*estoque == 0){
    // sinaliza caminhão

    // Espera abastecimento do caminhão
    pthread_cond_wait(&estoque_cond[id],&lj_lock[id]);
  }
  *estoque -= 1;
  sem_post(&atendimento[id]);
  pthread_mutex_unlock(&lj_lock[id]);
}

void* loja_thread(void* arg){
  loja* lj = ((loja *) arg);

  while(sem_wait(&filas[lj->id])){
    // code
    vender(&lj->estoque,lj->id);
  }
  pthread_exit(0);
}

void criar_loja(int id){
  
  // Alocação dinâmica da struct
  loja* lj = malloc(sizeof(loja));
  lj->pos = malloc(sizeof(celula));
  
  // Inicialização da struct
  lj->id = id;
  lj->estoque = ESTOQUE_MAX;
  lj->pos = celula_char(LOJA_INIT_CHAR,id+1);

  // Inicialização de vetores relacionados
  dados_lojas[id] = lj;   // Torna acessivel os dados das lojas por id
  sem_init(&filas[id],0,FILA_MAX);
  sem_init(&atendimento[id],0,FILA_MAX);
  pthread_mutex_init(&lj_lock[id],NULL);
  pthread_cond_init(&estoque_cond[id],NULL);

  pthread_create(&lojas[id],NULL,loja_thread,(void*) (lj));
}

void comprar(int id){
  sem_post(&filas[id]);
  sem_wait(&atendimento[id]);
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