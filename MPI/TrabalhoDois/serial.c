#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

#define PI 3.1415927

double*alocaVetor(int n){
	double *v;
	v = malloc(n*sizeof(double));
	return v;
}

double**alocaMatriz(int n){
	double**M;
	int i;
	M = malloc(n*sizeof(double*));
	for(i = 0; i < n; i++) M[i] = malloc(n*sizeof(double));
	return M;
}

void iniciaVetor(int n, double*v){
	int i;
	for(i = 0; i < n; i++){
		v[i] = i + 1;
	}
}

void iniciaMatriz(int n, double**M){
	int i, j;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			M[i][j] = j + i*PI + 1;
		}
	}
}

void MatrizxVetor(int n, double*v, double**M, double*y){
	int i, j;
	double sum = 0.0;
	for(i = 0; i < n; i++){
		sum = 0.0;
		for(j = 0; j < n; j++){
			sum += M[i][j]*v[j];
		}
		y[i] = sum;
	}
}

void printV(double*v, const int n){
	int i;
	for(i = 0;i < n; i++) printf("%lf ", v[i]);
	printf("\n");
}

void printM(double**A, const int dim){
	int i, j;
	for(i = 0;i < dim; i++){
		for(j = 0; j < dim; j++) printf("%lf ", A[i][j]);
		printf("\n");
	}
}

int main(int argc, char*argv[]){
	
	int n = 8, i;
	double *x, *y, **A;
	double start, end;
	MPI_Init(&argc, &argv);

	while(n < 10030){
		//comeca contagem do tempo
		start = MPI_Wtime();
		//aloca vetores e matriz
		x = alocaVetor(n); y = alocaVetor(n);
		A = alocaMatriz(n);
		//inicia vetor e matriz
		iniciaVetor(n, x); iniciaMatriz(n, A);
		//calcula o produto
		MatrizxVetor(n, x, A, y);
		//termina a contagem do tempo
		end = MPI_Wtime();
		//imprime resultados
		printf("Tempo = %.15lfs para n %d\n", end - start, n);
		//libera memoria
		free(x); free(y);
		for(i = 0; i < n; i++) free(A[i]);
		free(A);
		//adiciona ao n
		n += 80;
	}

}
