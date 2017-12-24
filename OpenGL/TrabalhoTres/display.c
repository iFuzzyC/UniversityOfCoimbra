/******************************************************************************/
/**                                                    ,---------------.     **/
/**    VISUALIZACAO COMPUTACIONAL                      |        .-.    |     **/
/**    Mestrado em Matemática - FCTUC                  |        !o|    |     **/
/**                                                    |>-,   ,-' | ,-<|     **/
/**    AUTORES: - Catarina Quiterio                    |  `---'   `-'  |     **/
/**             - Israel Campiotti                     `---------------'     **/
/******************************************************************************/
/* DESCRICAO: Ficheiro com funcoes que controlam o funcionamento do jogo....  */
/*            ...............................................................  */
/*		      ..............................................................  */
/******************************************************************************/
// 
//	Bibliotecas a incluir //////////////////////////////////////////////////////
//
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
//#include <mmsystem.h>
#include "obstaculos.h"
#include "display.h"
//
//	Funções ////////////////////////////////////////////////////////////////////
//
//inicia parametros de exibicao
void iniciar(void)
{
	//toca musica em loop
	//sndPlaySoundA("song.wav", SND_LOOP | SND_ASYNC);
	//inicia sistema de coordenadas
	glClearColor(0.6, 0.2, 0.2, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, largura, 0, altura, 0, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gera vetores normais automaticamente
	glEnable(GL_NORMALIZE);
	//parametros de iluminacao
	float mat_brilho[] = { 1.0 };
	float pos_luz[] = { largura, altura, 0.0, 0.0 };
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_brilho);
	glLightfv(GL_LIGHT0, GL_POSITION, pos_luz);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	
}
//move o boneco de neve
void timerMoveEsfera(int pos) {
	if (lambda >= 1.0) return;
	else {
		lambda += 0.1;
		//move da posicao de cima 
		if (pos == 1) {
			ball.y = lambda*yDif_BALL + ball.yCima;
		}
		//move da posicao do meio
		else if (pos == 2) {
			ball.y = lambda*yDif_BALL + ball.yMeio;
		}
		//move da posicao de baixo
		else if (pos == 3) {
			ball.y = lambda*yDif_BALL + ball.yBaixo;
		}
		glutPostRedisplay();
		glutTimerFunc(40, timerMoveEsfera, pos);
	}
}
//decide qual a nova posicao do boneco em movimento para cima
void decideMovimentoEsfera_Cima() {
	//esta no meio - move para cima
	if (abs(ball.y - ball.yMeio) <= 100.0) {
		yDif_BALL = ball.yCima - ball.yMeio;
		timerMoveEsfera(2);
	}
	//esta em baixo -  move para o meio
	else if (abs(ball.y - ball.yBaixo) <= 100.0) {
		yDif_BALL = ball.yMeio - ball.yBaixo;
		timerMoveEsfera(3);
	}
}
//decide qual a nova posicao do boneco em movimento para baixo
void decideMovimentoEsfera_Baixo() {
	//esta no meio - move para baixo
	if (abs(ball.y - ball.yMeio) <= 100.0) {
		yDif_BALL = ball.yBaixo - ball.yMeio;
		timerMoveEsfera(2);
	}
	//esta em cima - move para o meio
	else if (abs(ball.y - ball.yCima) <= 100.0) {
		yDif_BALL = ball.yMeio - ball.yCima;
		timerMoveEsfera(1);
	}
}
//decide em qual posicao em y o obstaculo sera gerado
void setPlace(int pos) {
	switch (pos) {
	case 1:
		obj->y = obj->yCima;
		break;
	case 2:
		obj->y = obj->yMeio;
		break;
	case 3:
		obj->y = obj->yBaixo;
		break;
	default:
		break;
	}
}
//checa se o boneco se chocou com algum objeto
void FuncaoDeChoque() {
	//checa se obstaculo esta fora da tela e gera novo obstaculo
	if (obj->x <= -50) {
		//decide o objeto que sera gerado
		randomID = rand() % 2 + 1;
		//decide a posicao em y do objeto
		randomPos = rand() % 3 + 1;
		switch (randomID)
		{
		case 1:
			obj = &box;
			setPlace(randomPos);
			break;
		case 2:
			obj = &cone;
			setPlace(randomPos);
			break;
		default:
			break;
		}
		//reinicia posicao de x
		obj->x = obj->Ox;
	}
	//ve se houve choque
	else if (abs(obj->x - ball.x - ball.radius) <= 10.0  && (int)ball.y / 100 == (int)obj->y / 100) {
		//se chocou termina o jogo
		gameover = 1;
		glutPostRedisplay();
	}
}
//controla o movimento do boneco automaticamente
void iaMovimento() {
	if ((int)ball.y / 100 == (int)obj->y / 100) {
		lambda = 0.0;
		if ((int)ball.y / 100 == 0) {
			decideMovimentoEsfera_Cima();
		}
		else if ((int)ball.y / 100 == 1) {
			decideMovimentoEsfera_Cima();
		}
		else if ((int)ball.y / 100 == 2) {
			decideMovimentoEsfera_Baixo();
			lambda = 1.0;
		}
	}
}
//desenha elementos da cena
void Desenhar(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//desenha jogo
	if (verInstrucoes == 0) {
		//resolve automaticamente caso ia esteja ligada
		if (ia == 1 && obj->x <= 800) {
			iaMovimento();
		}
		//desenha e movimenta o cenario
		glPushMatrix();
		glTranslatef(-tx, 0, 0);
		desenhaVariasCasas();
		dChao();
		glPopMatrix();
		//desenha jogo e obstaculos
		if (gameover == 0) {
			//desenha obstaculo caixa
			if (obj->id == BOX) {
				desenhaObj();
			}
			//desenha obstaculo cone
			else if (obj->id == CONE) {
				desenhaCone();
			}
			//checa se houve choque
			FuncaoDeChoque();
			//desenha boneco
			desenhaBoneco();
		}
		//termina o jogo
		else if (gameover == 1) {
			desenhaBoneco();
			displayRoman24(largura * 2 / 3, altura / 3, "FIM DE JOGO", 1.0, 0.0, 0.0);
		}
		//informa sobre ia ligada
		if (ia == 1) {
			displayRoman24(largura * 2 / 3, altura / 8, "I.A. Ligada", 1.0, 1.0, 0.0);
		}
		//desenha neve
		desenhaNeve();
	}
	//mostra instrucoes
	else if (verInstrucoes == 1) {
		desenhaInstrucoes();
	}
	glutSwapBuffers();
}
//move a cena atualizando tx e a posicao do objeto
void moveCena(int s) {
	if (verInstrucoes == 0) {
		if (tx < largura) tx += speed;
		else {
			tx = 0;
		}
		obj->x -= speed;
	}
	glutPostRedisplay();
	glutTimerFunc(40, moveCena, s);
}
//controla input do teclado
void Teclado(unsigned char key, int x, int y)
{
	switch (key)
	{
		//move boneco para cima
	case 'w':
		lambda = 0.0;
		if(ia != 1) decideMovimentoEsfera_Cima();
		break;
		//move boneco para baixo
	case 's':
		lambda = 0.0;
		if(ia != 1) decideMovimentoEsfera_Baixo();
		break;
		//sai das instrucoes
	case 27:                              
		verInstrucoes = 0;
		break;
	}
}
//controla input do menu
void controlaMenu(GLint entry) {
	switch (entry) {
		//reinicia jogo
	case 1:
		gameover = 0;
		break;
		//sai do jogo
	case 3:
		exit(0);
		break;
		//ativa ou desativa ia
	case 2:
		if (ia == 1) ia = 0;
		else ia = 1;
		break;
		//exibe instrucoes
	case 4:
		verInstrucoes = 1;
		break;
	}
}
//desenha flocos de neve
void desenhaNeve() {
	for (i = 0; i < n;i++) {
		for (j = 0;j < m;j++) {
			//decide se a neve ja passou pela cena, se sim gera novo floco
			if (linha[i].floco[j].y <= 0) iniciaPosicaoFloco(i, j);
			//desenha neve
			else {
				glPushMatrix();
				glColor3f(1.0, 1.0, 1.0);
				glTranslatef(linha[i].floco[j].x, linha[i].floco[j].y, 0);
				glutSolidSphere(5, 20, 16);
				glPopMatrix();
			}
			//atualiza posicao do floco
			linha[i].floco[j].y -= 5;
		}
	}
}
//gera posicao aleatoria para floco de neve
void iniciaPosicaoFloco(int i, int j) {
	linha[i].floco[j].x = i*n;
	linha[i].floco[j].y = (rand() % (5 * m)) + (j + 5)*m + altura;
}
//inicia a estrutura dos flocos de neve
void iniciaNeve() {
	n = largura / 30, m = altura / 30;
	m = 2 * m;
	int i, j;
	linha = malloc(n * sizeof(Neve));
	for (i = 0; i < n;i++) linha[i].floco = malloc(m * sizeof(Neve));
	//inicia posicao
	for (i = 0; i < n;i++) {
		for (j = 0;j < m;j++) {
			iniciaPosicaoFloco(i, j);
		}
	}
}
//desenha instrucoes 
void desenhaInstrucoes() {
	displayText(largura / 3, 4 * altura / 5, "INSTRUCOES", 1, 1, 1);
	displayText(largura / 10, 7 * altura / 10, "Aperte w para mover o boneco para cima.", 1, 1, 1);
	displayText(largura / 10, 6 * altura / 10, "Aperte s para mover o boneco para baixo.", 1, 1, 1);
	displayText(largura / 10, 5 * altura / 10, "Desvie dos obstaculos conforme estes aparecem.", 1, 1, 1);
	displayText(largura / 10, 4 * altura / 10, "Voce pode ligar a inteligencia artificial para que o boneco mova sozinho.", 1, 1, 1);
	displayText(largura / 10, 2 * altura / 10, "Carregue na tecla ESC para voltar ao jogo.", 1, 1, 1);
}
//exibe texto em roman 24
void displayRoman24(const double x, const double y, const char *string, double r, double g, double b) {
	int j = strlen(string);
	glColor3f(r, g, b);
	glRasterPos2i(x, y);
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
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