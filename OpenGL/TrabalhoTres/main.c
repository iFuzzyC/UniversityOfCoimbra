/******************************************************************************/
/**                                                    ,---------------.     **/
/**    VISUALIZACAO COMPUTACIONAL                      |        .-.    |     **/
/**    Mestrado em Matemática - FCTUC                  |        !o|    |     **/
/**                                                    |>-,   ,-' | ,-<|     **/
/**    AUTORES: - Catarina Quiterio                    |  `---'   `-'  |     **/
/**             - Israel Campiotti                     `---------------'     **/
/******************************************************************************/
/* DESCRICAO: Ficheiro que contem o programa principal para iniciar o jogo..  */
/*            ..............................................................  */
/*		      ..............................................................  */
/******************************************************************************/
//
//	Bibliotecas a incluir //////////////////////////////////////////////////////
//
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <GL/glut.h>
#include <math.h>
//#include <mmsystem.h>
#include <string.h>
#include "obstaculos.h"
#include "display.h"
//
//  Declaracao de variaveis globais ////////////////////////////////////////////////////
//
//objetos
Objeto *obj = NULL, box, ball, cone;
int BOX = 1, CONE = 2;
int speed = 15;
//caixa
int x_BOX, yCima_BOX, yMeio_BOX, yBaixo_BOX;
//cone
int x_CONE, yCima_CONE, yMeio_CONE, yBaixo_CONE;
//ball
int x_BALL, yCima_BALL, yMeio_BALL, yBaixo_BALL;
//aleatorias
int randomID, randomPos;
//inteligencia artificial
int ia = 0;
//movimento do boneco
double yDif_BALL, lambda;
//auxiliares
int tx = 0, gameover = 0, verInstrucoes = 1;
int largura = 900, altura = 600;
double corCasa1[3], corLuz1[3];
double corCasa2[3], corLuz2[3];

////////////////////////////////////////////////////////////////////////////////
//  Programa Principal /////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
	srand(time(NULL));
	iniciaNeve();
	iniciaGlobais();
	ball = iniciaObj(0, x_BALL, yMeio_BALL, 60, yCima_BALL, yMeio_BALL, yBaixo_BALL);
	box = iniciaObj(BOX, x_BOX, yCima_BOX, 0, yCima_BOX, yMeio_BOX, yBaixo_BOX);
	cone = iniciaObj(CONE, x_CONE, yMeio_CONE, 0, yCima_CONE, yMeio_CONE, yBaixo_CONE);
	obj = &box;

	glutInit(&argc, argv);

	//FreeConsole();			

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(largura, altura);
	glutCreateWindow("Jogo do Boneco de Neve");

	iniciar();

	glutDisplayFunc(Desenhar);

	glutKeyboardFunc(Teclado);

	glutTimerFunc(40, moveCena, 1);

	glutCreateMenu(controlaMenu);
	glutAddMenuEntry("Reiniciar", 1);
	glutAddMenuEntry("I.A.", 2);
	glutAddMenuEntry("Instrucoes", 4);
	glutAddMenuEntry("Sair", 3);
	//relaciona botao
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();

	return EXIT_SUCCESS;
}