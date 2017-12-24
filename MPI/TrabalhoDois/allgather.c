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

double**alocaMatriz(int rows, int col){
	double**M;
	int i;
	M = malloc(rows*sizeof(double*));
	for(i = 0; i < rows; i++) M[i] = malloc(col*sizeof(double));
	return M;
}

void iniciaVetor(int n, double*v, int rank){
	int i;
	for(i = 0; i < n; i++){
		v[i] = i + 1 + n*rank;
	}
}

void iniciaMatriz(int rows, int col, double**M, int rank){
	int i, j;
	for(i = 0; i < rows; i++){
		for(j = 0; j < col; j++){
			M[i][j] = j + 1 + (i + rows*rank)*PI;
		}
	}
}

void MatrizxVetor(int rows, int col, double*v, double**M, double*y){
	int i, j;
	double sum = 0.0;
	for(i = 0; i < rows; i++){
		sum = 0.0;
		for(j = 0; j < col; j++){
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

void printM(double**A, const int rows, const int col){
	int i, j;
	for(i = 0;i < rows; i++){
		for(j = 0; j < col; j++) printf("%lf ", A[i][j]);
		printf("\n");
	}
}

int main(int argc, char*argv[]){
	
	int n = 8, procs, rank, dim, i;
	double *xminus, *x, *b, *y, **A;
	double start, end;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &procs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

while(n < 10030){
	//determina valor da ordem da matriz divida pela quantidade de ranks
	dim = n / procs;
	//comecando a contagem do tempo
	start = MPI_Wtime();
	//aloca e inicia matriz A
	A = alocaMatriz(dim, n);	
	iniciaMatriz(dim, n, A, rank);	
	//aloca e inicia vetor xminus
	xminus = alocaVetor(dim);
	iniciaVetor(dim, xminus, rank);
	//aloca vetor x
	x = alocaVetor(n);
	//allgather enviando xminus para todos
	MPI_Allgather(xminus, dim, MPI_DOUBLE, x, dim, MPI_DOUBLE, MPI_COMM_WORLD);	
	//aloca b
	b = alocaVetor(dim);
	//calculando o produto vetor e matriz
	MatrizxVetor(dim, n, x, A, b);
	//coloca todos no y de rank 0
	if(rank == 0){
		y = alocaVetor(n);
	}
	MPI_Gather(b, dim, MPI_DOUBLE, y, dim, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	//termina de contar o tempo
	end = MPI_Wtime();
	MPI_Barrier(MPI_COMM_WORLD);
	//imprime resultados
	if(rank == 0){
		printf("\nVetor y calculado em %lfs para matriz de ordem %d\n", end - start, n);
		free(y);
	}
	//libera memoria
	free(x); free(xminus); free(b);
	for(i = 0; i<dim; i++) free(A[i]);
	free(A);
	//adiciona ao n
	n += 80;		
}
	MPI_Finalize();

}
