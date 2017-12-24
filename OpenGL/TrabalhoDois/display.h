/******************************************************************************/
/**                                                    ,---------------.     **/
/**    VISUALIZACAO COMPUTACIONAL                      |        .-.    |     **/
/**    Mestrado em Matemática - FCTUC                  |        !o|    |     **/
/**                                                    |>-,   ,-' | ,-<|     **/
/**    AUTORES: - Catarina Quiterio                    |  `---'   `-'  |     **/
/**             - Israel Campiotti                     `---------------'     **/
/******************************************************************************/
/* DESCRICAO: Texto que devera descrever o âmbito deste ficheiro de ........  */
/*            interface ....................................................  */
/*		      ..............................................................  */
/******************************************************************************/
//
//	Proteção do ficheiro de interface /////////////////////////////////////////
//
#ifndef DISPLAY_H
#define DISPLAY_H
//
//  Declaracao de variaveis ////////////////////////////////////////////////////
//
extern int altura, largura;
extern int viewUmAltura, viewUmLargura;
extern int viewRetCimaLargura, viewRetCimaAltura, viewRetCimaX, viewRetCimaY;
extern int viewRetDirLargura, viewRetDirAltura, viewRetDirX, viewRetDirY;
extern int newAltura;
extern int lixoAmarelo, lixoAzul, lixoVerde;
extern int gafPlast, papel, gafVidro, lata, caixa, frasco;
extern double lambda, tempo, elapsed, elapsedInstrucoes;
extern char time[200];
extern int lixoW, lixoH, lixoXi, lixoYi;
extern int nvX1, nvY1, desqX1, desqY1;
extern int nivel;
extern char nivelStr[8];
extern Objeto *obj, lixo0, lixo1, lixo2, gaf, paper, gafV, tin, box, bottle;
extern int mostraInstrucoes;
extern int xBotaoInstrucoes, yBotaoInstrucoes, wBotaoInstrucoes, yBotaoInstrucoes;
extern char *nome;
//
//	Funções ////////////////////////////////////////////////////////////////////
//
/*inicia variaveis globais*/
void iniciaGlobais();

/*inicia a janela - limpa, define cor e ortho2D*/
void init();

/*reinicia variaveis que mudam de acordo com o que o utilizador faz*/
void iniciaVariaveis();

/*controla a mudança de viewPort devido a mudanca de tamanho de janela*/
void controlaViewPort(int largura, int altura);

/*controla a mudanca de tamanho da janela*/
void reshape(int w, int h);

/*muda o nivel do jogo*/
void mudancaNivel();

/*termina o jogo*/
void fimDeJogo();

/*cronometra o tempo dentro do nivel*/
void cronometro(int s);

/*controla seleccao do menu*/
void controlaMenu(GLint entry);

//controla o teclado, reconhecendo a tecla ESC
void controlaKeyboard(unsigned char key, int x, int y);

/*controla o movimento das nuvens*/
void moveNuvemG1(int suc);

/*desenha na janela*/
void display(void);

//
//	Fim do ficheiro de interface ///////////////////////////////////////////////
//
#endif