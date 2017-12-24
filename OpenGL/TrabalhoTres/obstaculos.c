/******************************************************************************/
/**                                                    ,---------------.     **/
/**    VISUALIZACAO COMPUTACIONAL                      |        .-.    |     **/
/**    Mestrado em Matemática - FCTUC                  |        !o|    |     **/
/**                                                    |>-,   ,-' | ,-<|     **/
/**    AUTORES: - Catarina Quiterio                    |  `---'   `-'  |     **/
/**             - Israel Campiotti                     `---------------'     **/
/******************************************************************************/
/* DESCRICAO: Ficheiro com funcoes para desenhar a cena ....................  */
/*            ..............................................................  */
/*		      ..............................................................  */
/******************************************************************************/
// 
//	Bibliotecas a incluir //////////////////////////////////////////////////////
//
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "obstaculos.h"
//
//	Definições /////////////////////////////////////////////////////////////////
//
#define PI 3.1415
//
//	Funções ////////////////////////////////////////////////////////////////////
//
/*inicia variaveis globais*/
void iniciaGlobais() {
	//caixa
	x_BOX = 990;
	yCima_BOX = 230; yMeio_BOX = 145; yBaixo_BOX = 40;

	//cone
	x_CONE = 950;
	yCima_CONE = 220; yMeio_CONE = 150; yBaixo_CONE = 50;

	//ball
	x_BALL = 100;
	yCima_BALL = 290; yMeio_BALL = 198; yBaixo_BALL = 98;

	//cores das casas e luzes
	corCasa1[0] = 1.0; corCasa1[1] = 1.0; corCasa1[2] = 1.0;
	corLuz1[0] = 1.0; corLuz1[1] = 0.0; corLuz1[2] = 0.0;
	corCasa2[0] = 0.0; corCasa2[1] = 0.0; corCasa2[2] = 1.0;
	corLuz2[0] = 1.0; corLuz2[1] = 1.0; corLuz2[2] = 0.0;
}
//inicia variavel do tipo Objeto
Objeto iniciaObj(int n, double ox, double oy, double r, double cimaY, double meioY, double baixoY) {
	Objeto aux;
	aux.id = n;
	aux.Ox = ox;
	aux.x = ox;
	aux.y = oy;
	aux.radius = r;
	aux.yCima = cimaY;
	aux.yMeio = meioY;
	aux.yBaixo = baixoY;
	return aux;
}
//desenha asfalto
void dChao() {
	int i;
	double Ox, sH, Oy;
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	//desenha asfalto
	glBegin(GL_POLYGON);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(2 * largura, 0.0, 0.0);
	glNormal3f(0, 1, 0);
	glVertex3f(2 * largura, altura / 2, 0.0);
	glVertex3f(0.0, altura / 2, 0.0);
	glEnd();
	//desenha faixas
	glColor3f(1.0, 1.0, 1.0);
	Ox = 1.0 / 16.0*(double)largura;
	for (i = 1; i <= 3; i++) {
		glBegin(GL_POLYGON);
		glVertex2f(Ox, 0.4*altura / 2.0);
		glVertex2f(Ox + 0.25*largura, 0.4*altura / 2.0);
		glNormal3f(0, 1, 0);
		glVertex2f(Ox + 0.27*largura, 0.55*altura / 2.0);
		glNormal3f(0, 0, 0);
		glVertex2f(Ox + 0.02*largura, 0.55*altura / 2.0);
		glEnd();
		Ox = Ox + 1.0 / 16.0*(double)largura + 0.25*largura;
	}
	Ox = 1.0 / 16.0*(double)largura + largura;
	for (i = 1; i <= 3; i++) {
		glBegin(GL_POLYGON);
		glVertex2f(Ox, 0.4*altura / 2.0);
		glVertex2f(Ox + 0.25*largura, 0.4*altura / 2.0);
		glNormal3f(0, 1, 0);
		glVertex2f(Ox + 0.27*largura, 0.55*altura / 2.0);
		glNormal3f(0, 0, 0);
		glVertex2f(Ox + 0.02*largura, 0.55*altura / 2.0);
		glEnd();
		Ox = Ox + 1.0 / 16.0*(double)largura + 0.25*largura;
	}
	//desenha o rodape
	glColor3f(0.545, 0.271, 0.075);
	glBegin(GL_POLYGON);
	glVertex3f(0, altura / 2, 0);
	glVertex3f(2 * largura, altura / 2, 0);
	glVertex3f(2 * largura, altura / 2 + altura / 20, 0);
	glVertex3f(0, altura / 2 + altura / 20, 0);
	glEnd();
	//perspectiva do rodape
	glColor3f(0.0, 0.0, 0.0);
	for (i = 1; i <= 12; i++) {
		Ox = (double)(i*largura) / 6.0;
		glBegin(GL_LINE_STRIP);
		glVertex3f(Ox, altura / 2, 0);
		glVertex3f(Ox, altura / 2 + altura / 23, 0);
		glVertex3f(Ox - 10.0, altura / 2 + altura / 20, 0);
		glEnd();
	}
	glPopMatrix();
}
//desenha obstaculos caixa
void desenhaObj() {
	glPushMatrix();
	glColor3d(1.0, 0.0, 0.0);
	glTranslatef(obj->x, obj->y, -50.0);
	glScalef(6.0, 6.0, 6.0);
	glRotatef(211, 0, 1, 0);
	glRotatef(47, 1, 0, 0);
	glTranslatef(5, 5, 0);
	glutSolidCube(10.0);
	glPopMatrix();
}
//desenha esferas
void desenhaEsfera(double radius, double *corEsfera) {
	glPushMatrix();
	glColor3f(corEsfera[0], corEsfera[1], corEsfera[2]);
	glutSolidSphere(radius, 20, 16);
	glPopMatrix();
}
//desenha cones
void desenhaCone() {
	glPushMatrix();
	glColor3f(1.0, 1.0, 0.0);
	glTranslatef(obj->x, obj->y, 0);
	glRotatef(246, 1, 0, 0);
	glutWireCone(40, 60, 20, 16);
	glPopMatrix();
}
//desenha casa
void desenhaCasa(double *corCasa, double *corLuz) {
	int i;
	glPushMatrix();
	glColor3f(corCasa[0], corCasa[1], corCasa[2]);
	glTranslatef(0, altura / 2 + altura / 20, 0);
	glScalef(largura / 3, altura / 2, 1);
	glTranslatef(0.50, 0.50, 0);
	glutSolidCube(1);
	glPopMatrix();
	//porta
	glPushMatrix();
	glTranslatef(30, altura / 2 + altura / 20, 0);
	glScalef(largura / 3, altura / 2, 1);
	glColor3f(0.804, 0.522, 0.247);
	glBegin(GL_POLYGON);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.3, 0.0, 0.0);
	glVertex3f(0.3, 0.6, 0.0);
	glVertex3f(0.0, 0.6, 0.0);
	glEnd();
	glPopMatrix();
	//macaneta
	glPushMatrix();
	glColor3f(0.3, 0.3, 0.3);
	glTranslatef(95, altura / 2 + altura / 5, 0);
	glutSolidSphere(8,20,16);
	glPopMatrix();
	//janela
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(150, altura / 2 + altura / 20 + 100, 0);
	glScalef(largura / 3, altura / 2, 1);
	glBegin(GL_POLYGON);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.4, 0.0, 0.0);
	glVertex3f(0.4, 0.25, 0.0);
	glVertex3f(0.0, 0.25, 0.0);
	glEnd();
	glPopMatrix();
	//vidro
	glPushMatrix();
	glColor3f(0.529, 0.808, 0.980);
	glTranslatef(157, altura / 2 + altura / 20 + 107, 0);
	glScalef(largura / 3, altura / 2, 1);
	glBegin(GL_POLYGON);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.35, 0.0, 0.0);
	glNormal3f(0, 1, 0);
	glVertex3f(0.35, 0.2, 0.0);
	glNormal3f(0, 0, 0);
	glVertex3f(0.0, 0.2, 0.0);
	glEnd();
	glPopMatrix();
	//desenha fio das luzes
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(0, altura - 20, 0);
	glRotatef(180, 1, 0, 0);
	glScalef(32, 20, 1);
	glBegin(GL_LINE_STRIP);
	for (i = 0;i <= 300;i++) {
		glVertex3f((double)i*PI / 100.0, fabs(sin((double)i*PI / 100.0)), 0.0);
	}
	glEnd();
	glPopMatrix();
	//desenhandos luzes
	//luz 1
	glPushMatrix();
	glTranslatef(PI*32, altura - 20, 0);
	desenhaEsfera(6, corLuz);
	glPopMatrix();
	//luz 2
	glPushMatrix();
	glTranslatef(2 * PI * 32, altura - 20, 0);
	desenhaEsfera(6, corLuz);
	glPopMatrix();
	//luzes
	for (i = 1;i < 12;i += 2) {
		glPushMatrix();
		glTranslatef(i * 32 * PI / 4, altura - 20 - 20 * fabs(sin((double)PI / 4)), 0.0);
		desenhaEsfera(6, corLuz);
		glPopMatrix();
	}
}
//desenha boneco de neve
void desenhaBoneco() {
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	double comprimento_skate = 3 * ball.radius, largura_skate = ball.radius, altura_skate = ball.radius / 10;

	glPushMatrix();
	glTranslatef(ball.x, ball.y, 0);
	glTranslatef(ball.radius, -ball.radius - 4 * altura_skate, 0);
	glRotatef(178, 0, 0, 1);
	glRotatef(148, 0, 1, 0);
	glColor3f(1, 0.843, 0);
	gluCylinder(quadratic, ball.radius / 10, ball.radius / 10, ball.radius / 7, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(ball.x, ball.y, 0);
	glTranslatef(-ball.radius, -ball.radius - 4 * altura_skate, 0);
	glRotatef(178, 0, 0, 1);
	glRotatef(148, 0, 1, 0);
	glColor3f(1, 0.843, 0);
	gluCylinder(quadratic, ball.radius / 10, ball.radius / 10, ball.radius / 7, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(ball.x, ball.y, 0);
	glTranslatef(0, -ball.radius - altura_skate / 5, 0);
	glRotatef(70, 1, 0, 0);
	glRotatef(1, 0, 1, 0);
	glScalef(comprimento_skate, largura_skate, altura_skate);
	glColor3f(0.627, 0.322, 0.176);
	glutSolidCube(1);
	glColor3f(0.545, 0.271, 0.075);
	glutWireCube(1.0005);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(ball.x, ball.y, 0);
	glutSolidSphere(ball.radius, 20, 16);
	glTranslatef(0, ball.radius + 2 * ball.radius / 5, 0);
	glutSolidSphere(2 * ball.radius / 3, 20, 16);
	glRotatef(90, 0, 1, 0);
	glTranslatef(0, 0, 1.9 * ball.radius / 3);
	glColor3f(1, 0.549, 0);
	glutSolidCone(ball.radius / 7, ball.radius / 2, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(ball.x, ball.y, 0);
	glTranslatef(0, ball.radius + 2 * ball.radius / 5, 0);
	glTranslatef(sqrt(2 * ball.radius * ball.radius / 9), 0, 0);
	glTranslatef(0, sqrt(4 * ball.radius*ball.radius / 9 - 2 * ball.radius*ball.radius / 9), 0);
	glColor3f(0, 0, 0);
	glutSolidSphere(ball.radius / 10, 20, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(ball.x, ball.y, 0);
	glRotatef(337, 0, 1, 0);
	glRotatef(194, 1, 0, 0);
	glColor3f(0.545, 0.271, 0.075);
	gluCylinder(quadratic, ball.radius / 15, ball.radius / 10, 3 * ball.radius, 100, 100);
	glPopMatrix();

}
//desenha 6 casas
void desenhaVariasCasas() {
		glPushMatrix();
		desenhaCasa(corCasa1, corLuz1);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(largura / 3, 0, 0);
		desenhaCasa(corCasa2, corLuz2);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(2*largura / 3, 0, 0);
		desenhaCasa(corCasa1, corLuz1);
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(3*largura / 3, 0, 0);
		desenhaCasa(corCasa1, corLuz1);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(4*largura / 3, 0, 0);
		desenhaCasa(corCasa2, corLuz2);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(5 * largura / 3, 0, 0);
		desenhaCasa(corCasa1, corLuz1);
		glPopMatrix();
		
}