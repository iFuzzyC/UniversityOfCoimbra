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
#include <math.h>
#include <string.h>
#include "objetos.h"
//
//	Fun��es ////////////////////////////////////////////////////////////////////
//
void desenhaEcoponto(double r, double g, double b, double Ox, double Oy, double sW, double sH, const int lixo) {
	int i;
	double rad, x, y, radius;

	glColor3f(0.0, 0.0, 0.400);
	glBegin(GL_POLYGON);
		glVertex2f(Ox, Oy);
		glVertex2f(Ox + sW, Oy);
		glVertex2f(Ox + sW, Oy + sH / 10);
		glVertex2f(Ox, Oy + sH / 10);
	glEnd();

	glColor3f(0.0, 0.0, 0.545);
	glBegin(GL_POLYGON);
		glVertex2f(Ox + 0.95*sW, Oy + sH / 10);
		glVertex2f(Ox + 0.95*sW, Oy + sH);
		glVertex2f(Ox + 0.05*sW, Oy + sH);
		glVertex2f(Ox + 0.05*sW, Oy + sH / 10);
	glEnd();


	glColor3f(0.0, 0.0, 0.470);
	glLineWidth(0.05*sW);
	rad = 0.9*sW / 21.0;
	for (i = 2; i < 21; i += 2) {
		x = Ox + 0.05*sW + i*rad;
		glBegin(GL_LINE_STRIP);
			glVertex2f(x, Oy + sH / 10);
			glVertex2f(x, Oy + sH);
		glEnd();
	}
	glLineWidth(1);

	//desenha quadrado com a cor do ecoponto
	glColor3f(r, g, b);
	glBegin(GL_POLYGON);
		glVertex2f(Ox + 0.3*sW, Oy + 0.95*sH - 0.4*sW);
		glVertex2f(Ox + 0.7*sW, Oy + 0.95*sH - 0.4*sW);
		glVertex2f(Ox + 0.7*sW, Oy + 0.95*sH);
		glVertex2f(Ox + 0.3*sW, Oy + 0.95*sH);
	glEnd();
	//guarda coordenadas do quadrado na matriz
	quadEcopontos[lixo][0] = Ox + 0.3*sW; quadEcopontos[lixo][1] = Oy + 0.95*sH - 0.4*sW;
	//guarda largura do quadrado
	quadW = 0.4*sW;

	radius = 0.15*sW;
	glColor3f(0.753, 0.753, 0.753);
	glBegin(GL_POLYGON);
	for (i = 0; i <= 300; i++) {
		rad = 2.0 * PI* ((double)i) / 300.0;
		x = radius*cos(rad);
		y = radius*sin(rad);
		glVertex3f(Ox + 0.5*sW + x, Oy + 0.95*sH - 0.2*sW + y, 0.0);
	}
	glEnd();
}

void desenhaGafPlast(double Ox, double Oy, double sW, double sH) {
	glColor3f(0.941, 1.0, 1.0);
	//corpo garrafa
	glBegin(GL_POLYGON);
		glVertex2f(Ox, Oy);
		glVertex2f(Ox + sW, Oy);
		glVertex2f(Ox + sW, Oy + 0.7*sH);
		glVertex2f(Ox + 0.7*sW, Oy + 0.9*sH);
		glVertex2f(Ox + 0.3*sW, Oy + 0.9*sH);
		glVertex2f(Ox, Oy + 0.7*sH);
	glEnd();
	//tampa
	glColor3f(0.0, 0.749, 1.0);
	glBegin(GL_POLYGON);
		glVertex2f(Ox + 0.28*sW, Oy + 0.9*sH);
		glVertex2f(Ox + 0.72*sW, Oy + 0.9*sH);
		glVertex2f(Ox + 0.72*sW, Oy + sH);
		glVertex2f(Ox + 0.28*sW, Oy + sH);
	glEnd();
}

void desenhaFolha(double Ox, double Oy, double sW, double sH) {
	int i, j;
	double x, y, dy;

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
		glVertex2f(Ox, Oy);
		glVertex2f(Ox + sW, Oy);
		glVertex2f(Ox + sW, Oy + sH);
		glVertex2f(Ox, Oy + sH);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	for (i = 1; i <= 3; i++) {
		y = Oy + ((double)i + 1.0) / 5.0*sH;
		glBegin(GL_LINE_STRIP);
		for (j = 0; j <= 300; j++) {
			x = (Ox + 1.0) + ((double)j*(sW - 2.0) / 300.0);
			dy = y + cos(8.0*PI*(double)j / 300.0);
			glVertex2f(x, dy);
		}
		glEnd();
	}
}

void desenhaGafVidro(double Ox, double Oy, double sW, double sH) {
	int i;
	double x, y, raio, tetha;
	glColor3f(0.0, 1.0, 0.0);
	//desenha corpo
	glBegin(GL_POLYGON);
		glVertex2f(Ox, Oy);
		glVertex2f(Ox + sW, Oy);
		glVertex2f(Ox + sW, Oy + 0.55*sH);
		glVertex2f(Ox, Oy + 0.55*sH);
	glEnd();
	//desenha bico
	glBegin(GL_POLYGON);
		glVertex2f(Ox + 0.35*sW, Oy + 0.55*sH);
		glVertex2f(Ox + 0.65*sW, Oy + 0.55*sH);
		glVertex2f(Ox + 0.65*sW, Oy + sH);
		glVertex2f(Ox + 0.35*sW, Oy + sH);
	glEnd();

	//desenha circuferencia
	raio = 0.5*sW;
	glBegin(GL_POLYGON);
	for (i = 0; i <= 150; i++) {
		tetha = PI*(double)i / 150.0;
		x = raio*cos(tetha);
		y = raio*sin(tetha);
		glVertex2f(Ox + raio + x, Oy + 0.55*sH + y);
	}
	glEnd();
}

void desenhaLata(double Ox, double Oy, double sW, double sH) {
	//desenha parte de baixo
	glColor4f(0.5, 0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
		glVertex2f(Ox + 0.2*sW, Oy);
		glVertex2f(Ox + 0.8*sW, Oy);
		glVertex2f(Ox + sW, Oy + 0.1*sH);
		glVertex2f(Ox, Oy + 0.1*sH);
	glEnd();
	//desenha parte de cima
	glBegin(GL_POLYGON);
		glVertex2f(Ox, Oy + 0.9*sH);
		glVertex2f(Ox + sW, Oy + 0.9*sH);
		glVertex2f(Ox + 0.8*sW, Oy + sH);
		glVertex2f(Ox + 0.2*sW, Oy + sH);
	glEnd();
	//desenha meio
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex2f(Ox, Oy + 0.1*sH);
		glVertex2f(Ox + sW, Oy + 0.1*sH);
		glVertex2f(Ox + sW, Oy + 0.9*sH);
		glColor3f(0.8, 0.4, 0.4);
		glVertex2f(Ox, Oy + 0.9*sH);
	glEnd();
}

void desenhaCaixa(double Ox, double Oy, double sW, double sH) {
	//desenha caixa
	glColor4f(0.804, 0.522, 0.247, 1.0);
	glBegin(GL_POLYGON);
		glVertex2f(Ox + 0.05*sW, Oy);
		glVertex2f(Ox + 0.95*sW, Oy);
		glVertex2f(Ox + 0.95*sW, Oy + 0.8*sH);
		glVertex2f(Ox + 0.05*sW, Oy + 0.8*sH);
	glEnd();
	//desenha tampa
	glColor4f(0.824, 0.412, 0.118, 1.0);
	glBegin(GL_POLYGON);
		glVertex2f(Ox, Oy + 0.8*sH);
		glVertex2f(Ox + sW, Oy + 0.8*sH);
		glVertex2f(Ox + sW, Oy + sH);
		glVertex2f(Ox, Oy + sH);
	glEnd();
}

void desenhaFrasco(double Ox, double Oy, double sW, double sH) {
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
		glVertex2f(Ox + 0.05*sW, Oy);
		glVertex2f(Ox + 0.95*sW, Oy);
		glVertex2f(Ox + sW, Oy + 0.05*sH);
		glColor3f(0.5, 0.5, 0.5);
		glVertex2f(Ox + sW, Oy + 0.8*sH);
		glVertex2f(Ox + 0.9*sW, Oy + 0.9*sH);
		glVertex2f(Ox + 0.1*sW, Oy + 0.9*sH);
		glVertex2f(Ox, Oy + 0.8*sH);
		glColor3f(1.0, 1.0, 1.0);
		glVertex2f(Ox, Oy + 0.05*sH);
	glEnd();

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex2f(Ox, Oy + 0.9*sH);
		glVertex2f(Ox + sW, Oy + 0.9*sH);
		glVertex2f(Ox + sW, Oy + sH);
		glVertex2f(Ox, Oy + sH);
	glEnd();
}

void desenhaSol(const int largura, const int altura) {
	int i;
	double raioSol = 100.0, tetha, x, y;
	//desenha sol
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	for (i = 0; i <= 60; i++) {
		tetha = -PI * (double)i / 60.0;
		x = raioSol*cos(tetha);
		y = raioSol*sin(tetha);
		glVertex2f(x, y + altura);
	}
	glEnd();

}

void desenhaNuvens(double nuvemX, double nuvemY, double nuvemRaio, double k) {
	double tetha, x, y;
	int i;
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	for (i = 0; i < 301; i++) {
		tetha = 2.0*PI*(double)i / 300.0;			//as nuvens sao desenhadas usando um epicicloide
		x = (nuvemRaio*(k + 1)*cos(tetha) - nuvemRaio*cos((k + 1)*tetha));
		y = (nuvemRaio*(k + 1)*sin(tetha) - nuvemRaio*sin((k + 1)*tetha));
		if (y >= 0) glVertex2f(nuvemX + x, nuvemY + y);
	}
	glEnd();
}

void desenhaChao(double Oy, double sH, const int largura) {
	int i = 1;
	double Ox;

	//Desenha chao em que estao os ecopontos
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
		glVertex2f(0, Oy);
		glVertex2f(largura, Oy);
		glVertex2f(largura, Oy + sH);
		glVertex2f(0, Oy + sH);
	glEnd();

	//desenha o rodape
	glColor3f(0.545, 0.271, 0.075);
	glBegin(GL_POLYGON);
		glVertex2f(0, Oy);
		glVertex2f(largura, Oy);
		glVertex2f(largura, Oy - 0.2*sH);
		glVertex2f(0, Oy - 0.2*sH);
	glEnd();
	//perspectiva do rodape
	glColor3f(0.0, 0.0, 0.0);
	for (i = 1; i <= 6; i++) {
		Ox = (double)(i*largura) / 6.0;
			glBegin(GL_LINE_STRIP);
			glVertex2f(Ox, Oy - 0.2*sH);
			glVertex2f(Ox, Oy - 0.05*sH);
			glVertex2f(Ox - 10.0, Oy);
		glEnd();
	}

	//desenha asfalto
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex2f(0, Oy - 0.2*sH);
		glVertex2f(largura, Oy - 0.2*sH);
		glVertex2f(largura, 0);
		glVertex2f(0, 0);
	glEnd();

	//faz marcas do asfalto em perspectiva
	glColor3f(1.0, 1.0, 1.0);
	Ox = 1.0 / 16.0*(double)largura;
	for (i = 1; i <= 3; i++) {
		glBegin(GL_POLYGON);
			glVertex2f(Ox, 0.4*(Oy - 0.2*sH));
			glVertex2f(Ox + 0.25*largura, 0.4*(Oy - 0.2*sH));
			glVertex2f(Ox + 0.27*largura, 0.55*(Oy - 0.2*sH));
			glVertex2f(Ox + 0.02*largura, 0.55*(Oy - 0.2*sH));
		glEnd();
		Ox = Ox + 1.0 / 16.0*(double)largura + 0.25*largura;
	}
}

void desenhaBorda(int largura, int altura) {
	glLineWidth(5);
	glColor4f(0.0, 0.0, 0.0, 1.0);

	glBegin(GL_LINE_STRIP);
		glVertex2f(0, altura);
		glVertex2f(largura, altura);
	glVertex2f(largura, 0);
	glEnd();

	glLineWidth(1);
}

void desenhaRetangulo(int largura, int altura) {
	glColor3f(0.663, 0.663, 0.663);
	glBegin(GL_POLYGON);
		glVertex2f(0, 0);
		glVertex2f(largura, 0);
		glVertex2f(largura, altura);
		glVertex2f(0, altura);
	glEnd();
}

//imprime texto dados posicoes, texto e cor
void displayText(const double x, const double y, const char *string, double r, double g, double b) {
	int j = strlen(string);
	glColor3f(r, g, b);
	glRasterPos2i(x, y);
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
	}
}

void displayRoman24(const double x, const double y, const char *string, double r, double g, double b) {
	int j = strlen(string);
	glColor3f(r, g, b);
	glRasterPos2i(x, y);
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

//desenha o botao INSTRUCOES
void botaoInstrucoes(int xBotaoInstrucoes, int yBotaoInstrucoes, int wBotaoInstrucoes, int hBotaoInstrucoes) {
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
		glVertex2d(xBotaoInstrucoes, yBotaoInstrucoes);
		glVertex2d(xBotaoInstrucoes + wBotaoInstrucoes, yBotaoInstrucoes);
		glVertex2d(xBotaoInstrucoes + wBotaoInstrucoes, yBotaoInstrucoes + hBotaoInstrucoes);
		glVertex2d(xBotaoInstrucoes, yBotaoInstrucoes + hBotaoInstrucoes);
	glEnd();

	displayText(xBotaoInstrucoes + wBotaoInstrucoes / 7, yBotaoInstrucoes + hBotaoInstrucoes / 3, "INSTRUCOES", 0, 0, 0);
}
