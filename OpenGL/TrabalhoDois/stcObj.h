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
#ifndef STCOBJ_H
#define STCOBJ_H
//
//	Definições /////////////////////////////////////////////////////////////////
//
typedef struct
{
	double Ox;		//coordenadas originais do objecto
	double Oy;
	double sW;		//largura do objecto
	double sH;		//altura do objecto
	double dX;		//coordenadas usadas para desenhar o objecto
	double dY;
	int nobj;		//numero correspondente ao numero do objecto
	int lixo;		//numero correspondente ao ecoponto correcto
	int noEcoponto;			//numero que indica se o local em que o lixo se encontra corresponde ao lixo certo ou nao
} Objeto;
//
//	Funções ////////////////////////////////////////////////////////////////////
//
// atribui os valores indicados como argumentos da funcao as variaveis certas
Objeto initObj(double Ox, double Oy, double sW, double sH, int nobj, int lixo);

//
//	Fim do ficheiro de interface ///////////////////////////////////////////////
//
#endif