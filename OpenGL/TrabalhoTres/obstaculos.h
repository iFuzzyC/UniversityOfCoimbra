/******************************************************************************/
/**                                                    ,---------------.     **/
/**    VISUALIZACAO COMPUTACIONAL                      |        .-.    |     **/
/**    Mestrado em Matemática - FCTUC                  |        !o|    |     **/
/**                                                    |>-,   ,-' | ,-<|     **/
/**    AUTORES: - Catarina Quiterio                    |  `---'   `-'  |     **/
/**             - Israel Campiotti                     `---------------'     **/
/******************************************************************************/
/* DESCRICAO: Ficheiro de interface para o desenho da cena .................  */
/*            ..............................................................  */
/*		      ..............................................................  */
/******************************************************************************/
//
//	Proteção do ficheiro de interface /////////////////////////////////////////
//
#ifndef OBSTACULOS_H
#define OBSTACULOS_H
//
//  Declaracao de variaveis ////////////////////////////////////////////////////
//
//estrutura dos obstaculos
typedef struct {
	int id;
	double Ox;
	double x;
	double y;
	double yCima;
	double yMeio;
	double yBaixo;
	double radius;
}Objeto;
//caixa
extern int x_BOX, yCima_BOX, yMeio_BOX, yBaixo_BOX;
//cone
extern int x_CONE, yCima_CONE, yMeio_CONE, yBaixo_CONE;
//ball
extern int x_BALL, yCima_BALL, yMeio_BALL, yBaixo_BALL;
//auxiliares
extern Objeto *obj, box, ball, cone;
extern int tx, largura, altura;
extern double corCasa1[3], corLuz1[3];
extern double corCasa2[3], corLuz2[3];
//
//	Funções ////////////////////////////////////////////////////////////////////
//
/*inicia variaveis globais*/
void iniciaGlobais();
//inicia variavel do tipo Objeto
Objeto iniciaObj(int n, double ox, double oy, double r, double cimaY, double meioY, double baixoY);
//desenha asfalto
void dChao();
//desenha obstaculos caixa
void desenhaObj();
//desenha esferas
void desenhaEsfera(double radius, double *corEsfera);
//desenha cones
void desenhaCone();
//desenha boneco de neve
void desenhaBoneco();
//desenha casa
void desenhaCasa(double *corCasa, double *corLuz);
//desenha 6 casas
void desenhaVariasCasas();
//
//	Fim do ficheiro de interface ///////////////////////////////////////////////
//
#endif


