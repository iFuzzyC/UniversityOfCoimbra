/******************************************************************************/
/**                                                    ,---------------.     **/
/**    VISUALIZACAO COMPUTACIONAL                      |        .-.    |     **/
/**    Mestrado em Matematica - FCTUC                  |        !o|    |     **/
/**                                                    |>-,   ,-' | ,-<|     **/
/**    AUTORES: - Israel Campiotti...                  |  `---'   `-'  |     **/
/**             - Catarina Quiterio..                  `---------------'     **/
/******************************************************************************/
/* DESCRICAO: As funcoes tem como objetivo auxiliar em tarefas relativamente  */
/*            pequenas, como zerar um vetor, alterar valores de um vetor, ..  */
/*		      imprimir textos e regioes.....................................  */
/******************************************************************************/
//
//	Proteção do ficheiro de interface /////////////////////////////////////////
//
#pragma once

//
//	Funcoes ////////////////////////////////////////////////////////////////////
//

int clean_stdin()
{
	while (getchar() != '\n');
	return 1;
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
//imprime quadrado preto no lado esquerdo da imagem
void displayBlackRegion() {
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(-mult*normalizer, -mult*normalizer, 0);
	glVertex3f(mult*normalizer, -mult*normalizer, 0);
	glVertex3f(mult*normalizer, mult*normalizer, 0);
	glVertex3f(-mult*normalizer, mult*normalizer, 0);
	glEnd();
	glFinish();
}
//zera vetor de int com dimensao n
void zeraVetor(int n, int*v) {
	int i;
	for (i = 0; i < n; i++) v[i] = 0;
}
//redefini as cores para as padroes
void resetColor(double cColors[4][3]) {
	cColors[0][0] = 0.0; cColors[0][1] = 0.0; cColors[0][2] = 1.0;
	cColors[1][0] = 1.0; cColors[1][1] = 0.9; cColors[1][2] = 0.0;
	cColors[2][0] = 1.0; cColors[2][1] = 0.0; cColors[2][2] = 0.0;
	cColors[3][0] = 0.196; cColors[3][1] = 0.804; cColors[3][2] = 0.196;
}
//imprime informacoes sobre astroide
void txtAstroide(double xi, double yi) {
	displayText(xi*normalizer, yi*normalizer, "Astroide - a", cColors[0][0], cColors[0][1], cColors[0][2]);
	glLineWidth(2);
	astroide(60, (xi + 0.10)*normalizer, (yi-0.07)*normalizer, 0);
	glLineWidth(lineSize);
}
//imprime informacoes sobre cardioide
void txtCardioide(double xi, double yi) {
	displayText(xi*normalizer, yi*normalizer, "Cardioide - c", cColors[1][0], cColors[1][1], cColors[1][2]);
	glLineWidth(2);
	cardioide(40, (xi + 0.10)*normalizer, (yi - 0.09)*normalizer, 0);
	glLineWidth(lineSize);
}
//imprime informacoes sobre epicicloide
void txtEpicloide(double xi, double yi) {
	displayText(xi*normalizer, yi*normalizer, "Epicicloide - e", cColors[2][0], cColors[2][1], cColors[2][2]);
	glLineWidth(2);
	epicloide(20, 4, (xi + 0.10)*normalizer, (yi - 0.09)*normalizer, 0);
	epicloide(20, 3.8, (xi + 0.28)*normalizer, (yi - 0.09)*normalizer, 0);
	glLineWidth(lineSize);
}
//imprime informacoes osbre lemniscata de bernoulli
void txtBernoulli(double xi, double yi) {
	displayText(xi*normalizer, (yi-0.05)*normalizer, "Lemniscata de Bernoulli - b", cColors[3][0], cColors[3][1], cColors[3][2]);
	glLineWidth(2);
	bernoulli(60, (xi + 0.10)*normalizer, (yi - 0.1)*normalizer, 0);
	glLineWidth(lineSize);
}
//printa uma curva escolhida pelo usuario com os parametros escolhidos
void printaCurva(char cC, double radius) {
	double x = 0.0, y = 0.0, k;
	double teste;
	char c;
	//escolhe a curva
	printf("\nQual curva deseja desenhar?\n");
	printf("Astroide - a,\nCardioide - c,\nEpicicloide - e,\nLemniscata de Bernoulli - b\n- ");
	scanf(" %c", &cC);
	//checa se curva e possivel
	if (cC != 'a' && cC != 'c' && cC != 'e' && cC != 'b') {
		printf("\nValor nao valido.\n");
		return;
	}
	//escolhe a origem
	printf("Escolha as coordenadas x e y do centro\n(indique valores entre -%d e %d): ", (int)(mult*normalizer), (int)(mult*normalizer));
	//recebe valor valido de x
	do{
		printf("\nValor de x: ");
	} while (((scanf("%lf%c", &x, &c) != 2 || c != '\n') && clean_stdin()));
	//recebe valor valido de y
	do {
		printf("Valor de y: ");
	} while (((scanf("%lf%c", &y, &c) != 2 || c != '\n') && clean_stdin()));
	//escolhe o raio - recebe valor valido
	do
	{
		printf("Escolha o raio:\n- ");

	} while (((scanf("%lf%c", &radius, &c) != 2 || c != '\n') && clean_stdin()) || radius <= 0);

	//desenha a curva certa
	switch (cC)
	{
	case 'a':
		printf("Curva desenhada - Astroide\n");
		astroide(radius, x, y, 1);
		break;
	case 'c':
		printf("Curva desenhada - Cardioide\n");
		cardioide(radius, x, y, 1);
		break;
	case 'e':
		//escolhe o k
		printf("Escolha o k: ");
		scanf("%lf", &k);
		printf("Curva desenhada - Epicicloide\n");
		epicloide(radius, k, x, y, 1);
		break;
	case 'b':
		printf("Curva desenhada - Lemniscata de Bernoulli\n");
		bernoulli(radius, x, y, 1);
		break;
	default:
		break;
	}
}