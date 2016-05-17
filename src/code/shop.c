#include "../include/shop.h"
#include "../include/pessoa.h"
#include "../include/loja.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>


#define LINHAS 17
#define COLUNAS 57

char shop[LINHAS][COLUNAS];
int inicio_pessoa[2];
int saida_pessoa[2];
int inicio_carro[2];

pthread_mutex_t mlock[LINHAS][COLUNAS];
pthread_t printer;

// Extrai mapa e dados do arquivo.
// As outras funcionalidades do modulo se tornam disponiveis
// somente após a execução dessa função.

void* print_thread(void*);

void cria_shop(){
  int i,j;
  char cel;
  FILE* fp;
  
  fp=fopen("./src/files/shop.txt", "r");
  
	for (i = 0; i < LINHAS; ++i){
   
		for (j = 0; j < COLUNAS; ++j){
      cel = fgetc(fp);   
      //checa se é a posição de inicio de pessoas   
      if(cel == 'p'){
        inicio_pessoa[0] = i;
        inicio_pessoa[1] = j;
        cel = '.'; 
      }
      //checa se é a posição de saida das pessoas
      if(cel == 's'){
        saida_pessoa[0] = i;
        saida_pessoa[1] = j;
        cel = '.';
      }  
      //checa se é a posição de inicio de carros
      if(cel == 'c'){
        inicio_carro[0] = i;
        inicio_carro[1] = j;
        cel = '*';
      }       
      shop[i][j] = cel;                 // atribui char a matriz
      pthread_mutex_init(&mlock[i][j],NULL); //inicializa lock da celula
    }
  }
  fclose(fp);
  
}

void print_init(){
  pthread_create(&printer,NULL,print_thread,NULL);
}

void* print_thread(void* arg){
  while(1){
    imprime_shop();
  }
}
//retorna 1 se a celula pode ser ocupada e 0 caso contrário
int valido(int linha, int coluna){
  char c = shop[linha][coluna];
  if (c != '-' && c != '|' && c != '=' && c != '_' && c != 'V'){
    return 1;
  } else {
    return 0;
  }
}

// Pega lock inicial e insere caractere no mapa
void inicia_pessoa(celula* cel){
  
  int linha = inicio_pessoa[0];
  int coluna = inicio_pessoa[1];

  pthread_mutex_lock(&mlock[linha][coluna]); // Pega lock da celula
  shop[linha][coluna] = 'P';
  
  cel->linha = linha;
  cel->coluna = coluna;
}

// Recebe um caractere e o número de sua ocorrência e retorna ponteiro pra celula
// ou NULL caso essa ocorrência não exista
celula* celula_char(char alvo,int ocor){
  celula* cel = malloc(sizeof(celula));
  int i,j,cont_sim = 0;

  for (i = 0; i < LINHAS; ++i){
    for(j=0;j < COLUNAS;j++){
      if(shop[i][j] == alvo){
        cont_sim += 1;
        if (cont_sim == ocor){
          cel->linha = i;
          cel->coluna = j;
          return cel;
        }
      }
    }
  }
  return NULL;
}

// Libera a celula passada e substitui pelo caractere passado
void remover(celula* cel,char c){
  shop[cel->linha][cel->coluna] = c;
  pthread_mutex_unlock(&mlock[cel->linha][cel->coluna]);
}

// Move caractere da celula ini para celula prox, caso a movimentação seja valida
int mover(celula* ini,celula* prox){
  
  int linha,coluna;
  int nlinha,ncoluna;
  char charini,charprox;

  linha = ini->linha;
  coluna = ini->coluna;

  nlinha = prox->linha;
  ncoluna = prox->coluna;

  if (valido(nlinha,ncoluna)){
    pthread_mutex_lock(&mlock[nlinha][ncoluna]);
    
    charini = shop[linha][coluna];
    charprox = shop[nlinha][ncoluna];
    
    // Lembrar de apagar isso aqui
    if(charini == '.'){
      charini = '*';
    }
    // Faz troca dos char das duas celulas
    shop[linha][coluna] = charprox;
    shop[nlinha][ncoluna] = charini;

    // printf("movido para %d %d\n",nlinha,ncoluna );
    pthread_mutex_unlock(&mlock[linha][coluna]);
  
    return 0;
  
  } else {
  
    return 1;
  }
}

// retorna celula de saida das pessoas
celula* celula_saida_pessoa(){

  celula* cel = malloc(sizeof(celula));
  
  cel->linha = saida_pessoa[0];
  cel->coluna = saida_pessoa[1];
  
  return cel;
}

//printa o shop
void imprime_shop(){
  int i,j,aux;
  for (i = 0; i < LINHAS; ++i)   {
    for (j = 0; j < COLUNAS; ++j){
      printf("%c",shop[i][j]);        
    }
  }
  printf("\n");
  for (i = 0; i < LOJAS; ++i){
    estoque_loja(i);
    printf("id :%d | ", i);
    if(i%4 == 0){
      printf("\n");    
    }
  } 
  printf("\n");
  fflush(stdout);
  sleep(2);
}

/*
========================================================
c******************************************************|
*******************************************************|
========#==========#===========#=========#=======******|
|....|..V.......|..V.........|.V......|..V......|******|
|....|..........|............|........|.........|******|
|....|___....___|____....____|__....__|___...___|******|
p...............................................|******|
................................................|******|
................................................|******|
|---...---|---...---|---...---|---...---|--...--|******|
|.........|.........|.........|.........|.......|******|
|....V....|....V....|....V....|....V....|...V...|******|
=====#=========#=========#=========#========#====******|
*******************************************************|
*******************************************************|
========================================================
*/
