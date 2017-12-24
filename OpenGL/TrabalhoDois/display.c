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
#include <stdio.h>
#include "stcObj.h"
#include "objetos.h"
#include "resolveLixo.h"
#include "display.h"
//
//	Fun��es ////////////////////////////////////////////////////////////////////
//
/*inicia variaveis globais*/
void iniciaGlobais() {
	/*inicia tamanho da janela*/
	altura = 650; largura = 900;
	/*inicia valores para os objetos*/
	//tipo de lixo
	lixoAmarelo = 0; lixoAzul = 1; lixoVerde = 2;
	//objectos
	gafPlast = 3; papel = 4; gafVidro = 5; lata = 6; caixa = 7; frasco = 8;
	/*inicia variaveis que marcam a posicao de desenho dos ecopontos*/
	lixoW = 200; lixoH = 200; lixoXi = 100; lixoYi = 300;
	/*inicia variaveis que controlam movimento automatico*/
	lambda = 0.0;
	/*inicia variaveis dos viewPorts*/
	//view do jogo
	viewUmAltura = altura - (altura / 13.0); viewUmLargura = largura - (largura / 9.0);
	//view do retangulo de cima
	viewRetCimaAltura = altura / 13.0; viewRetCimaLargura = largura;
	viewRetCimaX = 0; viewRetCimaY = viewUmAltura;
	//view do retangulo a direita
	viewRetDirAltura = altura; viewRetDirLargura = largura / 9.0;
	viewRetDirX = viewUmLargura; viewRetDirY = 0;
	newAltura = altura;
	/*inicia posicao das nuvens*/
	nvX1 = 100; nvY1 = altura - 50; desqX1 = 200; desqY1 = 300;

	tempo = 0.0; elapsed = 0.0; elapsedInstrucoes = 0;
	lambda = 0.0;

	xBotaoInstrucoes = 9 * viewRetCimaLargura / 13; yBotaoInstrucoes = 13 * viewRetCimaAltura / 6;
	wBotaoInstrucoes = viewRetCimaLargura / 5; hBotaoInstrucoes = 2 * 13 * viewRetCimaAltura / 3;
	mostraInstrucoes = 1;
	nome = " ";
}

/*inicia a janela - limpa, define cor e ortho2D*/
void init() {
	//Define cor de fundo
	glClearColor(0.529f, 0.808f, 0.922f, 1.0f);
	//limpa a janela
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//define eixos
	gluOrtho2D(0, largura, 0, altura);
	glMatrixMode(GL_MODELVIEW);
}

/*reinicia variaveis que mudam de acordo com o que o utilizador faz*/
void iniciaVariaveis() {

	/*inicia ecopontos*/
	lixo0 = initObj(lixoXi, lixoYi, lixoW, lixoH, 0, 0);
	lixo1 = initObj(lixoXi + lixoW + 2, lixoYi, lixoW, lixoH, 0, 1);
	lixo2 = initObj(lixoXi + 2 * lixoW + 2 * 2, lixoYi, lixoW, lixoH, 0, 2);
	/*inicia objetos*/
	gaf = initObj(50, 0, 20, 50, gafPlast, lixoAmarelo);
	paper = initObj(100, 0, 40, 60, papel, lixoAzul);
	gafV = initObj(150, 0, 20, 50, gafVidro, lixoVerde);
	tin = initObj(200, 0, 25, 35, lata, lixoAmarelo);
	box = initObj(250, 0, 60, 30, caixa, lixoAzul);
	bottle = initObj(320, 0, 25, 35, frasco, lixoVerde);
	obj = &gaf;

	nivel = 1; sprintf(nivelStr, "%d", nivel);
}

/*controla a mudan�a de viewPort devido a mudanca de tamanho de janela*/
void controlaViewPort(int largura, int altura) {
	/*inicia variaveis dos viewPorts*/
	//view do jogo
	viewUmAltura = altura - (altura / 13.0); viewUmLargura = largura - (largura / 9.0);
	//view do retangulo de cima
	viewRetCimaAltura = altura / 13.0; viewRetCimaLargura = largura;
	viewRetCimaX = 0; viewRetCimaY = viewUmAltura;
	//view do retangulo a direita
	viewRetDirAltura = altura; viewRetDirLargura = largura / 9.0;
	viewRetDirX = viewUmLargura; viewRetDirY = 0;

	
}

/*controla a mudanca de tamanho da janela*/
void reshape(int w, int h) {
	controlaViewPort(w, h);
	newAltura = h;
}

/*muda o nivel do jogo*/
void mudancaNivel() {
	if (nivel == 1) {
		nivel = 2; sprintf(nivelStr, "%d", nivel);
		elapsed = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
		elapsedInstrucoes = 0;
	}
	if (tempo < 2.0 && nivel == 2) {
		displayRoman24(largura / 3, altura / 3 + 20, "NIVEL DOIS", 1.0, 1.0, 1.0);
	}
}

/*termina o jogo*/
void fimDeJogo() {
	nivel = 3;
	elapsed = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	elapsedInstrucoes = 0;
	if (tempo < 3.0) {
		displayRoman24(largura / 3, altura / 3 + 20, "FIM DE JOGO! - PARABENS!", 1.0, 1.0, 1.0);
	}

}

/*cronometra o tempo dentro do nivel*/
void cronometro(int s) {
	tempo = glutGet(GLUT_ELAPSED_TIME) / 1000.0 - elapsed - elapsedInstrucoes;
	sprintf(time, "%.2lf", tempo);
	displayText(9 * largura / 18, altura / 3, time, 1.0, 1.0, 1.0);
	glutPostRedisplay();
}

/*controla seleccao do menu*/
void controlaMenu(GLint entry) {
	switch (entry) {
	case 1:
		iniciaVariaveis();
		elapsed = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
		elapsedInstrucoes = 0;
		break;
	case 2:
		exit(0);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

//controla o teclado, reconhecendo a tecla ESC
void controlaKeyboard(unsigned char key, int x, int y) {
	if (key == 27) {
		mostraInstrucoes = 0;
		elapsedInstrucoes += glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	}
}

/*controla o movimento das nuvens*/
void moveNuvemG1(int suc) {
	//retorna as nuvens ao inicio da janela quando chegam ao fim da janela
	if (nvX1 >= largura + desqX1) {
		nvX1 = -3 * desqX1;
	}
	//move as nuvens
	nvX1 += 1;
	glutPostRedisplay();
	glutTimerFunc(40, moveNuvemG1, suc);
}

/*desenha na janela*/
void display(void) {
	//limpa fundo
	glClear(GL_COLOR_BUFFER_BIT);

	/*retangulo de cima*/
	glViewport(viewRetCimaX, viewRetCimaY, viewRetCimaLargura, viewRetCimaAltura);
	desenhaRetangulo(largura, altura);
	displayText(largura / 18, altura / 3, "NIVEL: ", 0.0, 0.0, 0.0);
	displayText(13 * largura / 90, altura / 3, nivelStr, 1.0, 1.0, 1.0);
	displayText(7 * largura / 18, altura / 3, "TEMPO: ", 0.0, 0.0, 0.0);
	cronometro(1);
	botaoInstrucoes(xBotaoInstrucoes, yBotaoInstrucoes, wBotaoInstrucoes, hBotaoInstrucoes);
	/*retangulo da direita*/
	//define viewport
	glViewport(viewRetDirX, viewRetDirY, viewRetDirLargura, viewRetDirAltura);
	//desenha fundo
	desenhaRetangulo(largura, altura);
	displayText(50, 582, "PLASTICO", 1.0, 0.95, 0.0);
	//desenha objetos no lixo amarelo
	if (gaf.noEcoponto == 1) desenhaGafPlast(200, 582 - gaf.sH - 20, 9 * gaf.sW, gaf.sH);
	if (tin.noEcoponto == 1) desenhaLata(250, 562 - tin.sH - 20, 9 * tin.sW, tin.sH);
	displayText(200, 382, "PAPEL", 0.118, 0.565, 1.0);
	//esenha objetos no lixo azul
	if (paper.noEcoponto == 1) desenhaFolha(200, 382 - 20 - paper.sH, 9 * paper.sW, paper.sH);
	if (box.noEcoponto == 1) desenhaCaixa(250, 352 - 20 - box.sH, 9 * box.sW, box.sH);
	displayText(150, 182, "VIDRO", 0.133, 0.545, 0.133);
	//desenha objetos no lixo verde

	//salva a matriz - translada e reescala o objeto garrafa de vidro
	glPushMatrix();
	glTranslatef(200, 182 - gafV.sH - 20, 0);
	glScalef(9.0, 1.0, 1.0);
	glTranslatef(-200, -182 + gafV.sH + 20, 0);
	if (gafV.noEcoponto == 1) desenhaGafVidro(200, 182 - gafV.sH - 20, gafV.sW, gafV.sH);
	glPopMatrix();
	if (bottle.noEcoponto == 1) desenhaFrasco(250, 162 - bottle.sH - 20, 9 * bottle.sW, bottle.sH);

	/*area de interacao com o usuario*/
	//define viewport
	glViewport(0, 0, viewUmLargura, viewUmAltura);
	//desenha paisagem
	desenhaSol(largura, altura);
	//desenha nuvens
	glPushMatrix();
	glTranslatef(nvX1, nvY1, 0);
	glScalef(0.5f, 0.3f, 1.0f);
	glTranslatef(-nvX1, -nvY1, 0);
	desenhaNuvens(nvX1, nvY1, 20, 6);
	desenhaNuvens(nvX1 + desqX1, nvY1 - desqY1, 20, 8);
	desenhaNuvens(nvX1 + 3 * desqX1, nvY1 - 0.5*desqY1, 20, 10);
	glPopMatrix();
	//desenhando o chao
	desenhaChao(lixoYi - 0.4*lixoH, 0.6*lixoH, largura);
	//desenha ecopontos
	desenhaEcoponto(1.0, 0.95, 0.0, lixo0.Ox, lixo0.Oy, lixo0.sW, lixo0.sH, 0);
	desenhaEcoponto(0.118, 0.565, 1.0, lixo1.Ox, lixo1.Oy, lixo1.sW, lixo1.sH, 1);
	desenhaEcoponto(0.196, 0.804, 0.196, lixo2.Ox, lixo2.Oy, lixo2.sW, lixo2.sH, 2);
	//desenha garrafa de plastico
	if (gaf.noEcoponto == 0) desenhaGafPlast(gaf.dX, gaf.dY, gaf.sW, gaf.sH);

	//desenha folha de papel
	if (paper.noEcoponto == 0) desenhaFolha(paper.dX, paper.dY, paper.sW, paper.sH);

	//desenha garrafa de vidro
	if (gafV.noEcoponto == 0) desenhaGafVidro(gafV.dX, gafV.dY, gafV.sW, gafV.sH);


	if (gaf.noEcoponto == 1 && paper.noEcoponto == 1 && gafV.noEcoponto == 1) {
		mudancaNivel();
		//desenha lata
		if (tin.noEcoponto == 0) desenhaLata(tin.dX, tin.dY, tin.sW, tin.sH);
		//desenha caixa de cartao
		if (box.noEcoponto == 0) desenhaCaixa(box.dX, box.dY, box.sW, box.sH);
		//desenha frasco de vidro
		if (bottle.noEcoponto == 0) desenhaFrasco(bottle.dX, bottle.dY, bottle.sW, bottle.sH);

		if (bottle.noEcoponto == 1 && tin.noEcoponto == 1 && box.noEcoponto == 1) fimDeJogo();
	}

	displayText(7 * viewUmLargura / 10, 0.5 * viewUmAltura / 10, nome, 1, 1, 1);

	/*desenha borda separanda as regioes*/
	desenhaBorda(largura, altura);

	if (mostraInstrucoes == 1) {
		glClear(GL_COLOR_BUFFER_BIT);
		glViewport(0, 0, largura, altura);
		displayText(largura / 3, 4 * altura / 5, "INSTRUCOES", 1, 1, 1);
		displayText(largura / 10, 7 * altura / 10, "Arraste o lixo ate ao ecoponto certo carregando no botao esquerdo do rato.", 1, 1, 1);
		displayText(largura / 10, 6 * altura / 10, "Largue o lixo no quadrado colorido do ecoponto correcto.", 1, 1, 1);
		displayText(largura / 10, 5 * altura / 10, "Quando carrega num objecto, aparece uma descricao no canto inferior direito.", 1, 1, 1);
		displayText(largura / 10, 4 * altura / 10, "Carregue no botao direito do rato para consultar o menu.", 1, 1, 1);
		displayText(largura / 10, 3 * altura / 10, "Atraves do menu, pode resolver automaticamente e reiniciar ou sair do jogo.", 1, 1, 1);
		displayText(largura / 10, 2 * altura / 10, "Carregue na tecla ESC para voltar ao jogo.", 1, 1, 1);


	}

	//gera a imagem
	glutSwapBuffers();
}