#include "../include/shop.h"
#include "../include/pessoa.h"
#include "../include/loja.h"
#include "../include/carro.h"

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
      switch(cel){
        //checa se é a posição de inicio de pessoas
        case 'p':
          inicio_pessoa[0] = i;
          inicio_pessoa[1] = j;
          cel = '.'; 
        break;
        //checa se é a posição de saida das pessoas
        case 's':
          saida_pessoa[0] = i;
          saida_pessoa[1] = j;
          cel = '.';
        break;
        //checa se é a posição de inicio de carros
        case 'c':
          inicio_carro[0] = i;
          inicio_carro[1] = j;
          cel = '*';
        break;
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

// RecebePega lock inicial e insere caractere no mapa
void inicia_pessoa(celula* cel){
  
  int linha = inicio_pessoa[0];
  int coluna = inicio_pessoa[1];

  pthread_mutex_lock(&mlock[linha][coluna]); // Pega lock da celula
  sleep(rand()%2);
  shop[linha][coluna] = 'P';
  
  cel->linha = linha;
  cel->coluna = coluna;
}

// Retorna uma celula que contem a posição inicial dos carros
celula* celula_entrada_carro(void){

  celula* cel = malloc(sizeof(celula));

  cel->linha = inicio_carro[0];
  cel->coluna = inicio_carro[1];

  return cel;
}

// Recebe uma struct das 4 celulas de posição de um carro e
// inicializa os carro no mapa em 4 posições a partir da posição 
// atribuindo essas celulas as recebidas
void inicia_carro(pos_carro* pos){
  celula* ini = celula_entrada_carro();
  int linha = ini->linha;
  int coluna = ini->coluna;
  
  // 4 locks inicias do carro
  pthread_mutex_lock(&mlock[linha][coluna]);
  pthread_mutex_lock(&mlock[linha+1][coluna]);
  pthread_mutex_lock(&mlock[linha][coluna+1]);
  pthread_mutex_lock(&mlock[linha+1][coluna+1]);
  
  pos->topo_d->linha  = linha;
  pos->topo_d->coluna = coluna + 1;
  shop[linha][coluna+1] = 'C';

  pos->baixo_d->linha  = linha + 1;
  pos->baixo_d->coluna = coluna + 1;
  shop[linha+1][coluna+1] = 'C';
  
  pos->topo_e->linha  = linha;
  pos->topo_e->coluna = coluna;
  shop[linha][coluna] = 'C';
  
  pos->baixo_e->linha  = linha +1;
  pos->baixo_e->coluna = coluna;
  shop[linha+1][coluna] = 'C';
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
  char cel;
  system("clear");
  for (i = 0; i < LINHAS; ++i)   {
    for (j = 0; j < COLUNAS; ++j){
      cel = shop[i][j];
      switch(cel){
        case '.':
          printf(ANSI_COLOR_GREEN "%c" ANSI_COLOR_RESET, cel );
        break;
        case '=':
          printf(ANSI_COLOR_BLUE "%c" ANSI_COLOR_RESET, cel );
        break;
        case '|':
          printf(ANSI_COLOR_BLUE "%c" ANSI_COLOR_RESET, cel );
        break;
        case '-':
          printf(ANSI_COLOR_BLUE "%c" ANSI_COLOR_RESET, cel );
        break;
        case '_':
          printf(ANSI_COLOR_BLUE "%c" ANSI_COLOR_RESET, cel );
        break;
        case 'P':
          printf(ANSI_COLOR_YELLOW "%c" ANSI_COLOR_RESET, cel );
        break;
        case '#':
          printf(ANSI_COLOR_CYAN "%c" ANSI_COLOR_RESET, cel );
        break;
        default:
          printf("%c", cel );
      }
    }
  }
  printf("\n");
  for(i=0;i < LOJAS; i++){
    aux = estoque_loja(i);
    printf("|id: %d estoque : %d|",i,aux);
    if(i%3 == 2)
      printf("\n");
  }
  printf("\n");
  fflush(stdout);
  usleep(50000);
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
