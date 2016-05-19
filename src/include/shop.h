#ifndef SHOP_H
#define SHOP_H

#ifdef __linux__
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define ANSI_BGCOLOR_GREEN   "\e[42m"
#define ANSI_BGCOLOR_BLUE   "\e[44m"
#define ANSI_BGCOLOR_RESET   "\e[49m"

#else

#define ANSI_COLOR_RED     ""
#define ANSI_COLOR_GREEN   ""
#define ANSI_COLOR_YELLOW  ""
#define ANSI_COLOR_BLUE    ""
#define ANSI_COLOR_MAGENTA ""
#define ANSI_COLOR_CYAN    ""
#define ANSI_COLOR_RESET   ""

#define ANSI_BGCOLOR_GREEN   ""
#define ANSI_BGCOLOR_BLUE    ""
#define ANSI_BGCOLOR_RESET   ""


#endif

typedef struct Celula{
  int linha;
  int coluna;
}celula;

struct pos_carro;
typedef struct Pos_carro pos_carro;

int mover(celula*,celula*);

void cria_shop(void);

void imprime_shop(void);

void inicia_pessoa(celula*);

void inicia_carro(pos_carro*);

void print_init(void);

void atribui_celula(celula*,celula*);

void debug(int);

int mover_direita(celula*);

int mover_baixo(celula*);

void trocar_celula(celula*,celula*);

celula* celula_char(char,int);

celula* celula_saida_pessoa(void);

void remover(celula*,char);

#endif