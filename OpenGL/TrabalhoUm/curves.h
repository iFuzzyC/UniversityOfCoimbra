/******************************************************************************/
/**                                                    ,---------------.     **/
/**    VISUALIZACAO COMPUTACIONAL                      |        .-.    |     **/
/**    Mestrado em Matematica - FCTUC                  |        !o|    |     **/
/**                                                    |>-,   ,-' | ,-<|     **/
/**    AUTORES: - Israel Campiotti...                  |  `---'   `-'  |     **/
/**             - Catarina Quiterio..                  `---------------'     **/
/******************************************************************************/
/* DESCRICAO: Objetivo deste header e possibilitar as funcoes e variavies que */
/*            sao necessarias para gerar as curvas..........................  */
/*		      ..............................................................  */
/******************************************************************************/
//
//	Protecao do ficheiro de interface /////////////////////////////////////////
//
#pragma once
// 
//	Bibliotecas a incluir //////////////////////////////////////////////////////
//
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "axes.h"
//
//	Definicoes /////////////////////////////////////////////////////////////////
//define pi e raiz quadrada de dois
#define PI	 3.14159265359
#define sqr2 1.41421356237
//
//	Variaveis Globais //////////////////////////////////////////////////////////
//variaveis globais para auxilio no codigo
double radius = 100.0, k = 4.0, nWidht = 1.2, nHeight = 0.7;
int normalizer, lineSize = 1;
char dCurv;
double cColors[4][3];

//
//	Funcoes ////////////////////////////////////////////////////////////////////
//

//dado raio e origens imprime astroide - region mantem informacao sobre se e na regiao preta(=1) ou nao(=0)
void astroide(const double radius, int Ox, int Oy, const int region) {
	double x = 0.0, y = 0.0;
	double t = 0.0;
	//normalizador para o raio - mantem escala
	double a = (radius*mult*normalizer) / 500;
	int i = 0, n = 1000;
	/*iniciando*/
	//define cor
	glColor3f(cColors[0][0], cColors[0][1], cColors[0][2]);
	//desenha curva
	glBegin(GL_LINE_STRIP);
	for (i = 0; i < n; i++) {
		t = 2.0 * PI *((double)i / (double)n);
		x = (a / 4.0)*(3 * cos(t) + cos(3 * t));
		y = (a / 4.0)*(3 * sin(t) - sin(3 * t));
		//checa a regiao em que deve ser desenhada
		if (region == 1) {
			if (Ox + x < mult*(double)normalizer && Oy - y < mult*(double)normalizer) glVertex3f(Ox + x, Oy - y, 0.0);
		}
		else {
			glVertex3f(Ox + x, Oy - y, 0.0);
		}
	}
	//desenha
	glEnd();
	glFlush();
}
//dado raio e origens imprime cardioide - region mantem informacao sobre se e na regiao preta(=1) ou nao(=0)
void cardioide(const double radius, int Ox, int Oy, const int region) {
	double x = 0.0, y = 0.0, t = 0.0;
	//normalizador para o raio- mantem escala
	double a = (radius*mult*normalizer) / 500;
	int i = 0, n = 1000;
	/*iniciando*/
	//define cor
	glColor3f(cColors[1][0], cColors[1][1], cColors[1][2]);
	//desenha a curva
	glBegin(GL_LINE_STRIP);
	for (i = 0; i < n; i++) {
		t = 2.0 * PI *((double)i / (double)n);
		x = a * (2 * cos(t) - cos(2 * t));
		y = a * (2 * sin(t) - sin(2 * t));
		//checa a regiao em que a curva deve ser desehada
		if (region == 1) {
			if (Ox + x < mult*(double)normalizer && Oy - y < mult*(double)normalizer) glVertex3f(Ox + x, Oy - y, 0.0);
		}
		else {
			glVertex3f(Ox + x, Oy - y, 0.0);
		}
	}
	//desenha
	glEnd();
	glFlush();

}
//dado raio e origens imprime epicicloide - region mantem informacao sobre se e na regiao preta(=1) ou nao(=0)
void epicloide(const double radius, const double k, int Ox, int Oy, const int region) {
	double x = 0.0, y = 0.0, t = 0.0;
	//normalizador para o raio - mantem a escala
	double a = (radius*mult*normalizer) / 500;
	int i = 0, n = 1000;
	/*iniciando*/
	//define cor
	glColor3f(cColors[2][0], cColors[2][1], cColors[2][2]);
	//desebga a cyrva
	glBegin(GL_LINE_STRIP);
	for (i = 0; i < (int)(10 * k)*n; i++) {
		t = 2.0 * PI *((double)i / (double)n);
		x = (a*(k + 1)*cos(t) - a*cos((k + 1)*t));
		y = (a*(k + 1)*sin(t) - a*sin((k + 1)*t));
		//checa a regiao em que deve ser desenhada
		if (region == 1) {
			if (Ox + x <= mult*(double)normalizer && Oy - y <= mult*(double)normalizer) glVertex3f(Ox + x, Oy - y, 0.0);
			else if (Ox + x > mult*(double)normalizer) glVertex3f(mult*(double)normalizer, Oy - y, 0.0);
			else if (Oy - y > mult*(double)normalizer || Oy - y < -mult*(double)normalizer) glVertex3f(Ox + x, mult*(double)normalizer, 0.0);
		}
		else {
			glVertex3f(Ox + x, Oy - y, 0.0);
		}
	}
	//desenha
	glEnd();
	glFlush();

}
//dado raio e origens imprime lemniscata de bernoulli - region mantem informacao sobre se e na regiao preta(=1) ou nao(=0)
void bernoulli(const double radius, int Ox, int Oy, const int region) {
	double x = 0.0, y = 0.0, t = 0.0, aux = 0.0;
	//normalizador para o raio - mantem a escala
	double a = (radius*mult*normalizer) / 500;
	int i = 0, n = 1000;
	/*iniciando*/
	//define a cor
	glColor3f(cColors[3][0], cColors[3][1], cColors[3][2]);
	//desenha a curva
	glBegin(GL_LINE_STRIP);
	for (i = 0; i < n; i++) {
		t = 2.0 * PI *((double)i / (double)n);
		aux = pow(sin(t), 2) + 1;
		x = (a * sqr2 * cos(t)) / aux;
		y = x * sin(t);
		//checa em qual regiao deve ser desenhada
		if (region == 1) {
			if (Ox + x < mult*(double)normalizer && Oy - y < mult*(double)normalizer) glVertex3f(Ox + x, Oy - y, 0.0);
		}
		else {
			glVertex3f(Ox + x, Oy - y, 0.0);
		}
	}
	//desenha
	glEnd();
	glFlush();

}
