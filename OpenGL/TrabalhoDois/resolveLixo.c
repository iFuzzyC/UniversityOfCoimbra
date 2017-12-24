/******************************************************************************/
/**                                                    ,---------------.     **/
/**    VISUALIZACAO COMPUTACIONAL                      |        .-.    |     **/
/**    Mestrado em Matem�tica - FCTUC                  |        !o|    |     **/
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
#include <GL/glut.h>
#include <time.h>
#include <unistd.h>
#include "stcObj.h"
#include "resolveLixo.h"
//
//	Fun��es ////////////////////////////////////////////////////////////////////
//
/*verifica se esta no ecoponto certo - 1 sim, 0 nao*/
int ecopontoCerto(double x, double y, const int lixo) {

	if (x >= quadEcopontos[lixo][0] && x <= quadEcopontos[lixo][0] + quadW && y >= quadEcopontos[lixo][1] && y <= quadEcopontos[lixo][1] + quadW) {
		return 1;
	}
	else return 0;
}

/*verifica se o lixo foi largado no ecoponto certo. Quando noi foi largado nem na posicao original
nem no ecoponto certo, atribui-se o valor das coordenadas originais as coordenadas usadas para desenhar o objecto*/
void testaLocal() {
	if (obj->noEcoponto != 1) obj->noEcoponto = ecopontoCerto(obj->dX, obj->dY, obj->lixo);
	if (obj->dX != obj->Ox || obj->dY != obj->Oy) {			//quando nao esta nas coordenadas originais
		if (obj->noEcoponto != 1) {			//quando nao esta no ecoponto certo
			*obj = initObj(obj->Ox, obj->Oy, obj->sW, obj->sH, obj->nobj, obj->lixo);
		}
	}
}

/*verifica se algum objeto foi selecionado - retorna 1 se sim, 0 se nao*/
int objetoClique(Objeto *objEsc, GLint x, GLint y) {
    //variaveis que controlam a proporcao entre viewport e janela
    double nL = (double)largura / (double)viewUmLargura, nH = (double)altura/ (double)viewUmAltura;
    //verifica se algum objeto foi selecionado
    if (x >= objEsc->Ox / nL && x <= (objEsc->Ox + objEsc->sW) / nL && (newAltura - y) >= objEsc->Oy/nH && (newAltura - y) <= (objEsc->Oy + objEsc->sH)/nH) {
        startx = x; starty = y;
        obj = objEsc;
        return 1;
    }
    else return 0;
}

/*controla o rato - dentro do viewPortUm*/
void controlaMouse(GLint button, GLint state, GLint x, GLint y) {
	double nL = (double)largura / (double)viewRetCimaLargura, nH = (double)altura / (double)viewRetCimaAltura;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {			//enquanto se pressiona o botao esquerdo do rato
		if (x >= xBotaoInstrucoes / nL && x <= (xBotaoInstrucoes + wBotaoInstrucoes) / nL && y <= (yBotaoInstrucoes + hBotaoInstrucoes) / nH && y >= (yBotaoInstrucoes) / nH) {
			mostraInstrucoes = 1;
			elapsedInstrucoes -= glutGet(GLUT_ELAPSED_TIME) / 1000.0;
		}
																	
		/*verifica qual objeto esta a ser movido e nao move os outros*/
		//garrafa de plastico
		moving = objetoClique(&gaf, x, y);
		//folha de papel
		if (moving == 0) {
			moving = objetoClique(&paper, x, y);
		}
		//garrafa de vidro
		if (moving == 0) {
			moving = objetoClique(&gafV, x, y);
		}
		//lata
		if (moving == 0) {
			moving = objetoClique(&tin, x, y);
		}
		//caixa de cartao
		if (moving == 0) {
			moving = objetoClique(&box, x, y);
		}
		//frasco de vidro
		if (moving == 0) {
			moving = objetoClique(&bottle, x, y);
		}
	}
	else {			//quando se larga o botao 
		/*verifica se o objecto previamente seleccionado foi largado no ecoponto certo*/
		testaLocal();
		/*termina movimento do objecto seleccionado*/
		moving = 0;
		nome = " ";
	}
	glutPostRedisplay();
}

/*controla o arrastamento do objeto*/
void controlaArrasto(int x, int y) {
	//quando se esta a arrastar um objecto com o rato desenha-se o objecto usando as coordenadas do rato
	if (moving == 1) {
		obj->dX = (double)largura / (double)viewUmLargura *(x - startx) + obj->Ox;
		obj->dY = (double)altura / (double)viewUmAltura * (-y + starty) + obj->Oy;
		switch (obj->nobj){
		case 3: 
			nome = "Garrafa de plastico";
			break;
		case 4:
			nome = "Folha de papel";
			break;
		case 5:
			nome = "Garrafa de vidro";
			break;
		case 6:
			nome = "Lata";
			break;
		case 7:
			nome = "Caixa de cartao";
			break;
		case 8:
			nome = "Frasco de vidro";
			break;
		default:
			break;
		}
		glutPostRedisplay();
	}
}

/*controla o movimento automatico do objecto selecionado*/
void timerLixo(int op) {
	//verifica se o lixo ja chegou ao ecoponto correto
	if (lambda >= 1.0) {
		obj->noEcoponto = 1;
		lambda = 0.0;
		sleep(5);
		return;
	}
	//comanda o movimento
	lambda += 0.05;
	obj->dX = lambda*xf + (1.0 - lambda)*obj->Ox;
	obj->dY = lambda*yf + (1.0 - lambda)*obj->Oy;
	glutPostRedisplay();
	glutTimerFunc(40, timerLixo, op);
}

/*resolve objectos de plastico*/
void resolveLixoAmarelo(int nObj) {
	if (nObj == gafPlast) obj = &gaf;
	else if (nObj == lata) obj = &tin;
	xf = quadEcopontos[lixoAmarelo][0] + 0.5*quadW;
	yf = quadEcopontos[lixoAmarelo][1];
	glutTimerFunc(40, timerLixo, 1);
}

/*resolve objectos de papel*/
void resolveLixoAzul(int nObj) {
	if (nObj == papel) obj = &paper;
	else if (nObj == caixa) obj = &box;
	xf = quadEcopontos[lixoAzul][0] + 0.5*quadW;
	yf = quadEcopontos[lixoAzul][1];
	glutTimerFunc(40, timerLixo, 1);
}

/*resolve objectos de vidro*/
void resolveLixoverde(int nObj) {
	if (nObj == gafVidro) obj = &gafV;
	else if (nObj == frasco) obj = &bottle;
	xf = quadEcopontos[lixoVerde][0] + 0.5*quadW;
	yf = quadEcopontos[lixoVerde][1];
	glutTimerFunc(40, timerLixo, 1);
}

/*indica o objecto a colocar automaticamente no ecoponto certo para cada tipo de lixo, em cada nivel*/
void controlaAutomatico(GLint entry) {
	switch (entry) {
		case 0:
			if (nivel == 1) resolveLixoAmarelo(gafPlast);
			else resolveLixoAmarelo(lata);
			break;
		case 1:
			if (nivel == 1) resolveLixoAzul(papel);
			else resolveLixoAzul(caixa);
			break;
		case 2:
			if (nivel == 1) resolveLixoverde(gafVidro);
			else resolveLixoverde(frasco);
			break;
		default:
			break;
	}
}

