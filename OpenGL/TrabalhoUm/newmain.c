/******************************************************************************/
/**                                                    ,---------------.     **/
/**    VISUALIZACAO COMPUTACIONAL                      |        .-.    |     **/
/**    Mestrado em Matematica - FCTUC                  |        !o|    |     **/
/**                                                    |>-,   ,-' | ,-<|     **/
/**    AUTORES: - Israel Campiotti...                  |  `---'   `-'  |     **/
/**             - Catarina Quiterio..                  `---------------'     **/
/******************************************************************************/
/* DESCRICAO: Arquivo principal, tem como objetivo controlar a entrada do ..  */
/*            usuario, a interacao com o programa e exibir as curvas corre-.  */
/*		      tamente.......................................................  */
/******************************************************************************/
// 
//	Bibliotecas a incluir //////////////////////////////////////////////////////
//
#include "curves.h"
#include "auxf.h"
//
//	Variaveis Globais //////////////////////////////////////////////////////////
//
int iColor = -1;
double xTxt = 0.4, yTxt = 0.3;
//
//	Funcoes ////////////////////////////////////////////////////////////////////
//

//funcao vazia apenas para manter o programa funcionando
void display() {
	
}
//printa as condicoes iniciais
void init() {
	//limpa o fundo e o deixa branco
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	//inicia o processo de ortho2D - define coordenadas globais
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-mult*normalizer, normalizer*(nWidht - mult), -mult*normalizer, mult*normalizer);
	//desenha quadrado preto e eixos coordenados
	glLineWidth(1);
	displayBlackRegion();
	displayAxes(normalizer, 10);
	//imprime as possiveis curvas
	txtAstroide(xTxt, yTxt);
	txtCardioide(xTxt, yTxt - 0.15);
	txtEpicloide(xTxt, yTxt - 0.35);
	txtBernoulli(xTxt, yTxt - 0.5);
}
//controla acoes do mouse
void controlaMouse(GLint button, GLint state, GLint x, GLint y) {
	//define a largura da linha para a curva
	glLineWidth(lineSize);
	//caso botao esquerdo pressionado desenha curva
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		switch (dCurv)
		{
		//casos de curvas - imprime somente dentro do quadrado preto
		case 'a':
			if (x <= 2*mult*normalizer) {
				astroide(radius, x - mult*normalizer, mult*normalizer - y, 1);
				printf("\nCurva Desenhada - Astroide - Raio = %.3lf", radius);
				printf("\nCentro: %.3lf, %.3lf\n", x - mult*normalizer, mult*normalizer - y);
			}
			break;
		case 'c':
			if (x <= 2 * mult*normalizer) {
				cardioide(radius, x - mult*normalizer, mult*normalizer - y, 1);
				printf("\nCurva Desenhada - Cardioide - Raio = %.3lf", radius);
				printf("\nCentro: %.3lf, %.3lf\n", x - mult*normalizer, mult*normalizer - y);
			}
			break;
		case 'e':
			if (x <= 2 * mult*normalizer) {
				epicloide(radius, k, x - mult*normalizer, mult*normalizer - y, 1);
				printf("\nCurva Desenhada - Epicicloide - Raio = %.3lf - K = %.2lf", radius, k);
				printf("\nCentro: %.3lf, %.3lf\n", x - mult*normalizer, mult*normalizer - y);
			}
			break;
		case 'b':
			if (x <= 2 * mult*normalizer) {
				bernoulli(radius, x - mult*normalizer, mult*normalizer - y, 1);
				printf("\nCurva Desenhada - Lemniscata de Bernoulli - Raio = %.3lf", radius);
				printf("\nCentro: %.3lf, %.3lf\n", x - mult*normalizer, mult*normalizer - y);
			}
			break;
		default:
			break;
		}
	}
	//caso botao direito pressionado - reinicia imagem
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		printf("\nREINICIADO\n");
		init();
	}
}
//auxilia na mudanca de cor da curva
void changeColor() {
	//muda cor da curva selecionada
	switch (dCurv)
	{
	case 'a':
		iColor = 0;
		printf("\nMudar cor do astroide:");
		break;
	case 'c':
		iColor = 1;
		printf("\nMudar cor do cardioide:");
		break;
	case 'e':
		iColor = 2;
		printf("\nMudar cor de epicicloide:");
		break;
	case 'b':
		iColor = 3;
		printf("\nMudar cor de Lemniscata de Bernoulli:");
		break;
	default:
		break;
	}
	printf("\nCor atual: r = %.3lf  g = %.3lf  b = %.3lf", cColors[iColor][0], cColors[iColor][1], cColors[iColor][2]);
	printf("\nInsira novos valores para r, g e b: ");
	scanf("%lf %lf %lf", &cColors[iColor][0], &cColors[iColor][1], &cColors[iColor][2]);
}
//controla acoes do teclado
void controlaKeyboard(unsigned char key, int x, int y) {
	char c;
	switch (key)
	{
	//escolha da curva
	case 'a':
		dCurv = 'a';
		printf("\nCurva Selecionada - Astroide");
		break;
	case 'c':
		dCurv = 'c';
		printf("\nCurva Selecionada - Cardioide");
		break;
	case 'e':
		dCurv = 'e';
		printf("\nCurva Selecionada - Epicicloide");
		break;
	case 'b':
		dCurv = 'b';
		printf("\nCurva Selecionada - Lemniscata de Bernoulli");
		break;
		//saida do programa
	case 'q':
		exit(0);
		break;
		//casos de aumento de raio
	case '1':
		radius += 5.0;
		printf("\nRaio aumentado - Raio = %.3lf", radius);
		break;
	case '2':
		radius *= 2;
		printf("\nRaio aumentado - Raio = %.3lf", radius);
		break;
		//diminui raio
	case '3':
		radius -= 5;
		printf("\nRaio diminuido - Raio = %.3lf", radius);
		break;
	case '4':
		radius /= 2;
		printf("\nRaio diminuido - Raio = %.3lf", radius);
		break;
		//muda k
	case 'k':
		//recebe valor valido para k
		do
		{
			printf("\nInsira novo valor para k: ");

		} while (((scanf("%lf%c", &k, &c) != 2 || c != '\n') && clean_stdin()) || k <= 0);
		break;
		//muda raio
	case 'r':
		//recebendo raio valido
		do
		{
			printf("\nInsira novo valor para raio: ");

		} while (((scanf("%lf%c", &radius, &c) != 2 || c != '\n') && clean_stdin()) || radius <= 0);
		break;
		//muda espessura
	case 'l':
		//recebe valor valido para espessura
		do
		{
			printf("\nInsira novo valor para espessura da linha: ");

		} while (((scanf("%d%c", &lineSize, &c) != 2 || c != '\n') && clean_stdin()) || lineSize <= 0);
		break;
		//muda cor da curva
	case 'z':
		changeColor();
		break;
		//reseta as cores
	case 'x':
		printf("\nCores reiniciadas\n");
		resetColor(cColors);
		break;
		//escolhe a curva e local para desenhar
	case 'p':
		printaCurva(dCurv, radius);
		break;
	default:
		break;
	}
}
//funcao especial - controla aumento da espessura da linha
void controlaEspessura(int key, int a, int b) {
	switch (key)
	{
		//aumento da espessura
	case GLUT_KEY_F1:
		lineSize += 1;
		printf("\nEspessura aumentada - Espessura = %d", lineSize);
		break;
	case GLUT_KEY_F2:
		lineSize *= 2;
		printf("\nEspessura aumentada - Espessura = %d", lineSize);
		break;
		//diminui espessura
	case GLUT_KEY_F3:
		lineSize -= 1;
		printf("\nEspessura diminuida - Espessura = %d", lineSize);
		break;
	case GLUT_KEY_F4:
		lineSize /= 2;
		printf("\nEspessura diminuida - Espessura = %d", lineSize);
		break;
	default:
		break;
	}
	//evita valores impossiveis
	if (lineSize < 1) {
		lineSize = 1;
	}
}

////////////////////////////////////////////////////////////////////////////////
//	Programa Principal /////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char**argv) {
	/*informacao sobre as curvas*/
	printf("Este programa pode gerar as seguintes curvas:\n");
	printf("Astroide: - 'a'");
	printf("\n  x = (r / 4) * (3*cos(t) + cos(3*t)) \n  y = (r / 4) * (3*sin(t) - sin(3*t))\n");
	printf("Cardioide: - 'c'");
	printf("\n  x = r * (2*cos(t) + cos(2*t)) \n  y = r * (2*sin(t) - sin(2*t)) \n");
	printf("Epicicloide: - 'e'");
	printf("\n  x = r*(k + 1)*cos(t) - r*cos((k + 1)*t)) \n  y = r*(k + 1)*sin(t) - r*sin((k + 1)*t)) \n");
	printf("Lemniscata de Bernoulli: - 'b'");
	printf("\n  x = (r*(2^(1/2))*cos(t))/(sin^2(t) + 1) \n  y = (r*(2^(1/2))*cos(t)*sin(t))/(sin^2(t) + 1) \n");
	
	//raio - informacoes e comandos
	printf("\nRaio inicial = %.3lf",radius);
	printf("\nPara alterar o raio pressione 'r'.");
	printf("\nPara aumentar o raio pressione:\n");
	printf("1: +5, 2: *2\n");
	printf("Para diminuir o raio pressione:\n");
	printf("3: -5, 4: /2 \n");

	//k - informacao e comandos
	printf("\nK inicial = %.2lf", k);
	printf("\nPara alterar o K pressione 'k'.\n");

	//espessura - informacao e comandos
	printf("\nEspessura inicial = %d", lineSize);
	printf("\nPara alterar a espessura pressione 'l'.");
	printf("\nPara aumentar a espessura da linha pressione:\n");
	printf("F1: +1, F2: *2\n");
	printf("Para diminuir a espessura da linha pressione:\n");
	printf("F3: -1, F4: /2 \n");

	//outras informacoes
	printf("\nPara mudar a cor da curva selecionada pressione 'z'.");
	printf("\nPara redefinir as cores para as padroes pressione 'x'.\n");
	printf("\nPara escolher qual e onde gerar a curva pressione 'p'.\n");
	printf("\nPara apagar as curvas desenhadas pressione o botao direito do rato\n");
	printf("\nPara sair pressionar 'q'.\n");

	//informacao como escolher curva
	printf("\nPara gerar uma curva, usando os valores predefinidos ou os\nalterados, indique o tipo de curva pretendida e, de seguida,");
	printf("coloque o cursor em cima do ponto do grafico que vai servir de centro e carregue no botao esquerdo do rato.");
	printf("\nAlternativamente, pressione 'p' e indique o tipo de curva, as coordenadas do centro, o raio e k, se necessario.");
	printf("\nQuando se pretende alterar a cor ou a espessura da linha,\nindique as alteracoes antes de gerar a curva.");

	printf("\n\n -----Listagem de Comandos-----\n");

	//inicializando as cores
	resetColor(cColors);

	//iniciando o glut
	glutInit(&argc, argv);

	//definindo dimensao da janela - quadrada
	normalizer = glutGet(GLUT_SCREEN_WIDTH) / 2;

	//inciando a janel
	glutInitWindowSize(normalizer*(nWidht), normalizer*nHeight);
	glutInitWindowPosition(500, 10);
	glutCreateWindow("Curvas");

	//prepara a imagem
	init();
	//printa vazio para evitar conflitos
	glutDisplayFunc(display);
	//controla acoes do usuario
	glutKeyboardFunc(controlaKeyboard);
	glutMouseFunc(controlaMouse);
	glutSpecialFunc(controlaEspessura);

	glutMainLoop();

	return EXIT_SUCCESS;
}


