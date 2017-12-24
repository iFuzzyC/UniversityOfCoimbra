/******************************************************************************/
/**                                                    ,---------------.     **/
/**    VISUALIZACAO COMPUTACIONAL                      |        .-.    |     **/
/**    Mestrado em Matemática - FCTUC                  |        !o|    |     **/
/**                                                    |>-,   ,-' | ,-<|     **/
/**    AUTORES: - Catarina Quiterio                    |  `---'   `-'  |     **/
/**             - Israel Campiotti                     `---------------'     **/
/******************************************************************************/
/* DESCRICAO: Texto que devera descrever, resumidamente, os objetivos e os .  */
/*            resultados do programa. ......................................  */
/*		      ..............................................................  */
/******************************************************************************/
// 
//	Bibliotecas a incluir //////////////////////////////////////////////////////
//
#include "stcObj.h"
//
//	Funções ////////////////////////////////////////////////////////////////////
//
Objeto initObj(double Ox, double Oy, double sW, double sH, int nobj, int lixo) {
	Objeto obj;
	obj.Ox = Ox;		
	obj.Oy = Oy;
	obj.sW = sW;
	obj.sH = sH;
	obj.dX = Ox;
	obj.dY = Oy;
	obj.lixo = lixo;
	obj.nobj = nobj;
	obj.noEcoponto = 0;			//inicialmente o ogjecto nao se encontra no ecoponto certo
	return obj;
}