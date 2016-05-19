#include "../include/loja.h"
#include "../include/shop.h"
#include "../include/carro.h"

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

pthread_t lojas[LOJAS];
pthread_cond_t estoque_cond[LOJAS];
pthread_mutex_t estoque_lock[LOJAS];
sem_t filas[LOJAS], checar_filas[LOJAS];
sem_t atendimento[LOJAS];
loja* dados_lojas[LOJAS];

void vender(int id){
  pthread_mutex_lock(&estoque_lock[id]);
  dados_lojas[id]->estoque -= 1;

  // Finaliza atendimento
  sem_post(&atendimento[id]);
  if(dados_lojas[id]->estoque == 0){
    // sinaliza caminhão
    chamar_carro(id);
    // Espera abastecimento do caminhão
    pthread_cond_wait(&estoque_cond[id],&estoque_lock[id]);
  }
  pthread_mutex_unlock(&estoque_lock[id]);
  
}

void* loja_thread(void* arg){

  loja* lj = ((loja *) arg);
  while(1){
    sem_wait(&filas[lj->id]);
    vender(lj->id);
    
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
  sem_init(&filas[id],0,0);
  sem_init(&checar_filas[id],0,FILA_MAX);
  sem_init(&atendimento[id],0,0);
  pthread_mutex_init(&estoque_lock[id],NULL);
  pthread_cond_init(&estoque_cond[id],NULL);

  pthread_create(&lojas[id],NULL,loja_thread,(void*) (lj));
}

void abastecer_loja(int loja_id){
  pthread_mutex_lock(&estoque_lock[loja_id]);
  dados_lojas[loja_id]->estoque = ESTOQUE_MAX;
  pthread_mutex_unlock(&estoque_lock[loja_id]);
  pthread_cond_signal(&estoque_cond[loja_id]);
}

int checar_fila(int id){
  if(!sem_trywait(&checar_filas[id])){
    return 1;
  } else {
    return 0;
  }
}

void comprar(int id){
  sem_post(&filas[id]);
  sem_wait(&atendimento[id]);
  sem_post(&checar_filas[id]);
}

int total_lojas(){
  return LOJAS;
}

int estoque_loja(int id){
  int estoque;
  pthread_mutex_lock(&estoque_lock[id]);
  estoque = dados_lojas[id]->estoque;
  pthread_mutex_unlock(&estoque_lock[id]);
  return estoque;
}

celula* pos_loja(int id){
  return dados_lojas[id]->pos;
}

void destruir_loja(int id){
  pthread_join(lojas[id],NULL);
}