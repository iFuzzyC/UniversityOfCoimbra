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
#ifndef RESOLVELIXO_H
#define RESOLVELIXO_H
//
// Declaracao de variaveis  ///////////////////////////////////////////////////
//
extern int quadEcopontos[3][2];				//matriz 3x2 em se se guardam as coordenadas usadas para desenhar os 3 ecopontos
extern double quadW;					//largura dos ecopontos

extern Objeto *obj, gaf, paper, gafV, tin, box, bottle;			//objectos a colocar no ecoponto

extern int largura, altura, viewUmLargura, viewUmAltura, newAltura;
extern int viewRetCimaAltura, viewRetCimaLargura;
extern int startx, starty;				//coordenadas da posicao original do rato quando se inicia um movimento

extern int moving, nvX1, desqX1, nivel;		//moving indica se se esta a mover um objecto ou nao
extern double lambda, xf, yf, elapsed, elapsedInstrucoes;			/*lambda indica se o objecto ja chegou ao local correcto quando se esta a mover automaticamente*/

extern int lixoAmarelo, lixoAzul, lixoVerde;			//numero correspondente ao tipo de ecoponto
extern int gafPlast, lata, gafVidro, frasco, papel, caixa;			//numero atribuido a cada objecto

extern int mostraInstrucoes;		//numero que indica quando se deve mostrar as instrucoes
extern int xBotaoInstrucoes, yBotaoInstrucoes, wBotaoInstrucoes, hBotaoInstrucoes;			//coordenadas, largura e altura do botao das instrucoes

extern char *nome;
//
//	Funções ////////////////////////////////////////////////////////////////////
//
/*verifica se esta no ecoponto certo - 1 sim, 0 nao*/
int ecopontoCerto(double x, double y, const int lixo);

/*verifica se o lixo foi largado no ecoponto certo. Quando noi foi largado nem na posicao original
nem no ecoponto certo, atribui-se o valor das coordenadas originais as coordenadas usadas para desenhar o objecto*/
void testaLocal();

/*verifica se algum objecto foi seleccionado - retorna 1 se sim, 0 se nao*/
int objetoClique(Objeto *objEsc, GLint x, GLint y);

/*controla o rato - dentro do viewPortUm*/
void controlaMouse(GLint button, GLint state, GLint x, GLint y);

/*controla o arrastamento do objecto*/
void controlaArrasto(int x, int y);

/*controla o movimento automatico do objecto selecionado*/
void timerLixo(int op);

/*resolve automaticamente objectos de plastico*/
void resolveLixoAmarelo(int nObj);

/*resolve automaticamente objectos de papel*/
void resolveLixoAzul(int nObj);

/*resolve automaticamente objectos de vidro*/
void resolveLixoverde(int nObj);

/*indica o objecto a colocar automaticamente no ecoponto certo para cada tipo de lixo, em cada nivel*/
void controlaAutomatico(GLint entry);

//
//	Fim do ficheiro de interface ///////////////////////////////////////////////
//
#endif