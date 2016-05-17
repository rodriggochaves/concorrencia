#include "../include/loja.h"
#include "../include/shop.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

pthread_t lojas[LOJAS];
pthread_cond_t estoque_cond[LOJAS];
pthread_mutex_t estoque_lock[LOJAS];
sem_t filas[LOJAS];
sem_t atendimento[LOJAS];
loja* dados_lojas[LOJAS];

void vender(int* estoque,int quant){
  int i;
  for(i=0;i<quant;i++){
    if(*estoque == 0){
      // sinaliza caminhão
      pthread_cond_wait(&)
    }
  }
}

void* loja_thread(void* arg){
  while(sem_wait(&filas[id])){
    // code
    vender(lj->estoque,1);
    sem_post(&atendimento[id]);
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