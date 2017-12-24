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
#ifndef OBJETOS_H
#define OBJETOS_H
//
//	Definições /////////////////////////////////////////////////////////////////
//
#define PI 3.1415927
//
//  Declaracao de variaveis  ///////////////////////////////////////////////////
//
extern int quadEcopontos[3][2];				//matriz 3x2 em se se guardam as coordenadas usadas para desenhar os 3 ecopontos
extern double quadW;					//largura dos ecopontos
//
//	Funções ////////////////////////////////////////////////////////////////////
//
//usando a cor, coordenadas, largura e altura indicadas como argumentos, desenha um ecoponto
void desenhaEcoponto(double r, double g, double b, double Ox, double Oy, double sW, double sH, const int lixo);

//desenha uma garrafa de plastico usando os coordenadas, largura e altura indicadas como argumentos da funcao
void desenhaGafPlast(double Ox, double Oy, double sW, double sH);

//desenha uma folha de papel usando os coordenadas, largura e altura indicadas como argumentos da funcao
void desenhaFolha(double Ox, double Oy, double sW, double sH);

//desenha uma garrafa de vidro usando os coordenadas, largura e altura indicadas como argumentos da funcao
void desenhaGafVidro(double Ox, double Oy, double sW, double sH);

//desenha uma lata usando os coordenadas, largura e altura indicadas como argumentos da funcao
void desenhaLata(double Ox, double Oy, double sW, double sH);

//desenha uma caixa de cartao usando os coordenadas, largura e altura indicadas como argumentos da funcao
void desenhaCaixa(double Ox, double Oy, double sW, double sH);

//desenha um frasco de vidro usando os coordenadas, largura e altura indicadas como argumentos da funcao
void desenhaFrasco(double Ox, double Oy, double sW, double sH);

//desenha sol no canto superior esquerdo da janela
void desenhaSol(const int largura, const int altura);

//desenha nuvem usando as coordenadas, a largura e o k indicados como argumentos da funcao
void desenhaNuvens(double nuvemX, double nuvemY, double nuvemRaio, double k);

//desenha a estrada
void desenhaChao(double Oy, double sH, const int largura);

//desenha o contorno
void desenhaBorda(int largura, int altura);

//desenha os rectangulos onde se encontra a informacao sobre o jogo
void desenhaRetangulo(int largura, int altura);

//imprime texto dadas as coordenadas, texto e cor
void displayText(const double x, const double y, const char *string, double r, double g, double b);

void displayRoman24(const double x, const double y, const char *string, double r, double g, double b);

//desenha o botao INSTRUCOES
void botaoInstrucoes(int xBotaoInstrucoes, int yBotaoInstrucoes, int wBotaoInstrucoes, int hBotaoInstrucoes);

//
//	Fim do ficheiro de interface ///////////////////////////////////////////////
//
#endif