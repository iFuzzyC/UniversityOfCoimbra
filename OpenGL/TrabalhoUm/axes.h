/******************************************************************************/
/**                                                    ,---------------.     **/
/**    VISUALIZACAO COMPUTACIONAL                      |        .-.    |     **/
/**    Mestrado em Matematica - FCTUC                  |        !o|    |     **/
/**                                                    |>-,   ,-' | ,-<|     **/
/**    AUTORES: - Israel Campiotti...                  |  `---'   `-'  |     **/
/**             - Catarina Quiterio..                  `---------------'     **/
/******************************************************************************/
/* DESCRICAO: O objetivo deste arquivo e proporcionar uma maneira de se dese- */
/*            nhar eixos coordenados. ......................................  */
/*		      ..............................................................  */
/******************************************************************************/
//
//	Proteção do ficheiro de interface /////////////////////////////////////////
//
#pragma once

//
//	Variaveis Globais //////////////////////////////////////////////////////////
//
double mult = 0.35;

//
//	Funcoes ////////////////////////////////////////////////////////////////////
//

//imprime os eixos coordenados, com n marcacoes e tamanho 2*mult*normalizer
void displayAxes(const double normalizer, const int n) {
	//define cor dos eixos
	glColor3f(1.0, 1.0, 1.0);
	double x = 0.0, y = 0.0;
	int i = 0;
	//eixo y
	for (i = 0; i < n; i++) {
		glBegin(GL_LINE_STRIP);
		glVertex3f(x - 3, y, 0);
		glVertex3f(x + 3, y, 0);
		glEnd();
		glFlush();
		glBegin(GL_LINE_STRIP);
		glVertex3f(x - 3, -y, 0);
		glVertex3f(x + 3, -y, 0);
		glEnd();
		glFlush();
		y += (mult*normalizer/(double)n);
	}
	//eixo x
	x = 0.0; y = 0;
	for (i = 0; i < n; i++) {
		glBegin(GL_LINE_STRIP);
		glVertex3f(x, y - 3, 0);
		glVertex3f(x, y + 3, 0);
		glEnd();
		glFlush();
		glBegin(GL_LINE_STRIP);
		glVertex3f(-x, y - 3, 0);
		glVertex3f(-x, y + 3, 0);
		glEnd();
		glFlush();
		x += (mult*normalizer / (double)n);
	}
	//fazendo setas
	x = mult*normalizer; y = x;
	//eixo x
	glBegin(GL_LINE_STRIP);
	glVertex3f(x - 5, 5.0, 0.0);
	glVertex3f(x, 0.0, 0.0);
	glEnd();
	glFlush();
	glBegin(GL_LINE_STRIP);
	glVertex3f(x - 5, -5.0, 0.0);
	glVertex3f(x, 0.0, 0.0);
	glEnd();
	glFlush();
	//eixo y
	glBegin(GL_LINE_STRIP);
	glVertex3f(0.0, y, 0.0);
	glVertex3f(5.0, y- 5.0, 0.0);
	glEnd();
	glFlush();
	glBegin(GL_LINE_STRIP);
	glVertex3f(-5.0, y -5.0, 0.0);
	glVertex3f(0.0, y, 0.0);
	glEnd();
	glFlush();

	//desenha linhas
	//eixo x
	glBegin(GL_LINE_STRIP);
	glVertex3f(-mult*normalizer, 0, 0);
	glVertex3f(mult*normalizer, 0, 0);
	glEnd();
	glFlush();
	//eixo y
	glBegin(GL_LINE_STRIP);
	glVertex3f(0, -mult*normalizer, 0);
	glVertex3f(0, mult*normalizer, 0);
	glEnd();
	glFinish();

}
