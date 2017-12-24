/******************************************************************************/
/**                                                    ,---------------.     **/
/**    VISUALIZACAO COMPUTACIONAL                      |        .-.    |     **/
/**    Mestrado em Matemática - FCTUC                  |        !o|    |     **/
/**                                                    |>-,   ,-' | ,-<|     **/
/**    AUTORES: - Catarina Quiterio                    |  `---'   `-'  |     **/
/**             - Israel Campiotti                     `---------------'     **/
/******************************************************************************/
/* DESCRICAO: Ficheiro de interface com declaracoes de funcoes que controlam  */
/*            a cena e interacao com usuario................................  */
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
//estrutura dos flocos de neve
typedef struct Neve {
	struct Neve *floco;
	double x;
	double y;
}Neve;
extern Objeto *obj, ball, box, cone;
extern double lambda, yDif_BALL;
extern int randomID, randomPos, BOX, CONE;
extern int tx, speed, largura, altura, gameover, verInstrucoes;
extern double corCasa1[3], corLuz1[3];
extern double corCasa2[3], corLuz2[3];
extern int ia;
//variaveis auxiliares para ficheiro
Neve *linha;
int n, m, i, j;
//
//	Funções ////////////////////////////////////////////////////////////////////
//
//inicia parametros de exibicao
void iniciar(void);
//move o boneco de neve
void timerMoveEsfera(int pos);
//decide qual a nova posicao do boneco em movimento para cima
void decideMovimentoEsfera_Cima();
//decide qual a nova posicao do boneco em movimento para baixo
void decideMovimentoEsfera_Baixo();
//decide em qual posicao em y o obstaculo sera gerado
void setPlace(int pos);
//checa se o boneco se chocou com algum objeto
void FuncaoDeChoque();
//controla o movimento do boneco automaticamente
void iaMovimento();
//desenha elementos da cena
void Desenhar(void);
//move a cena atualizando tx e a posicao do objeto
void moveCena(int s);
//controla input do teclado
void Teclado(unsigned char key, int x, int y);
//controla input do menu
void controlaMenu(GLint entry);
//inicia a estrutura dos flocos de neve
void iniciaNeve();
//desenha flocos de neve
void desenhaNeve();
//gera posicao aleatoria para floco de neve
void iniciaPosicaoFloco(int i, int j);
//desenha instrucoes 
void desenhaInstrucoes();
//exibe texto em roman 24
void displayText(const double x, const double y, const char *string, double r, double g, double b);
//imprime texto dados posicoes, texto e cor
void displayRoman24(const double x, const double y, const char *string, double r, double g, double b);
//
//	Fim do ficheiro de interface ///////////////////////////////////////////////
//
#endif

