#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define PESSOAS 1

pthread_t pessoas[PESSOAS];

struct{
  int id;
  int linha,coluna;
  float  dinheiro;
} typedef pessoa;

void* cliente(void *arg){
  pessoa* ps = ((pessoa *) arg);
  int id = ps->id;
  free(ps);
  pthread_exit(0);
}
void chegar_pessoa(int id){
  pessoa* ps = (pessoa *) malloc(sizeof(pessoa));
  int* inicio;
  inicio = (int *) (intptr_t) inicio_pessoas();
  ps->id = id;
  pthread_create(&pessoas[id],NULL,cliente,(void *) (ps));
}
void embora_pessoa(int id){
  pthread_join(pessoas[id],NULL);
}
int main(){
  int i;
  pessoa* ps;
  cria_shop();
  for( i= 0; i<PESSOAS;i++){
    chegar_pessoa(i);
  }

  imprime_shop();
  for(i=0;i<PESSOAS;i++){
    embora_pessoa(i);
  }  
}

