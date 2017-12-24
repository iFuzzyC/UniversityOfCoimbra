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
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "objetos.h"
#include "stcObj.h"
#include "resolveLixo.h"
#include "display.h"
//
//	Declaracao de variaveis globais /////////////////////////////////////////////////////////////////
//
/*variaveis que controlam tamanho de janela*/
//tamanho da janela
int altura, largura;
//variaveis do viewportUm - jogo
int viewUmLargura, viewUmAltura;
//viewPort do retangulo de cima
int viewRetCimaAltura, viewRetCimaLargura, viewRetCimaX, viewRetCimaY;
//viewPort do retangulo a direita
int viewRetDirAltura, viewRetDirLargura, viewRetDirX, viewRetDirY;
int newAltura;

/*variaveis que controlam os numeros dos lixos e objetos*/
//numeros dos lixos
int lixoAmarelo, lixoAzul, lixoVerde;
//numero dos objetos
int gafPlast, papel, gafVidro, lata, caixa, frasco;

/*variaveis que controlam mudanca de posicao*/
//variaveis para arrastar os objetos
int moving, startx, starty;
//variaveis que controlam o movimento automatico dos objetos
double lambda, xf, yf;
//variaveis dos deslocamentos das nuvens
int nvX1, nvY1, desqX1, desqY1;
//variaveis que controlam a posicao inicial do desenho dos ecopontos
int lixoW, lixoH, lixoXi, lixoYi;

/*variaveis que cuidam de contar o tempo*/
double tempo, elapsed, elapsedInstrucoes;
char time[200];

/*nivel*/
int nivel; char nivelStr[8];

/*guardam as coordenadas do quadrado para onde o lixo deve ser levado e a largura dos quadrados*/
int quadEcopontos[3][2]; double quadW;

/*variaveis do tipo objeto que guardam informacoes sobre os objetos*/
Objeto lixo0, lixo1, lixo2, gaf, *obj, paper, gafV, tin, box, bottle;

//variavel que indica quando se deve mostrar as instrucoes
int mostraInstrucoes;
//coordenadas, largura e altura do botao das instrucoes
int xBotaoInstrucoes, yBotaoInstrucoes, wBotaoInstrucoes, hBotaoInstrucoes;			
char *nome;
//
////////////////////////////////////////////////////////////////////////////////
//	Programa Principal /////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char**argv) {
	iniciaGlobais();
	iniciaVariaveis();

	// Inicializa o GLUT
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(largura, altura);
	glutInitWindowPosition(50, 20);

	//FreeConsole();
	// Cria a janela GLUT de visualização
	glutCreateWindow("Jogo do Ecoponto");

	// Obrigatório registar uma "callback function", neste caso de visualização
	init();
	glutMouseFunc(controlaMouse);
	glutMotionFunc(controlaArrasto);
	glutKeyboardFunc(controlaKeyboard);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(500, moveNuvemG1, 1);

	//cria submenu
	int subMenu = glutCreateMenu(controlaAutomatico);
	glutAddMenuEntry("Plastico", 0);
	glutAddMenuEntry("Papel", 1);
	glutAddMenuEntry("Vidro", 2);
	//cria menu
	glutCreateMenu(controlaMenu);
	glutAddSubMenu("Resolver Automaticamente", subMenu);
	glutAddMenuEntry("Reiniciar", 1);
	glutAddMenuEntry("Sair", 2);
	//relaciona botao
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// Esperando por eventos
	glutMainLoop();

	return EXIT_SUCCESS;
}
