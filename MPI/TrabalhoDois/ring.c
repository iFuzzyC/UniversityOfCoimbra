#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

#define PI 3.1415927

//dado n aloca vetor
double*alocaVetor(int n){
	double *v;
	v = malloc(n*sizeof(double));
	return v;
}
//dado numero de linhas e colunas aloca matriz
double**alocaMatriz(int rows, int col){
	double**M;
	int i;
	M = malloc(rows*sizeof(double*));
	for(i = 0; i < rows; i++) M[i] = malloc(col*sizeof(double));
	return M;
}
//da valores ao vetor
void iniciaVetor(int n, double*v, int rank){
	int i;
	for(i = 0; i < n; i++){
		v[i] = i + 1 + n*rank;
	}
}
//da valores a matriz
void iniciaMatriz(int rows, int col, double**M, int rank){
	int i, j;
	for(i = 0; i < rows; i++){
		for(j = 0; j < col; j++){
			M[i][j] = j + 1 + (i + rows*rank)*PI;
		}
	}
}
//faz o produto de matriz e vetor
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
//imprime vetor
void printV(double*v, const int n){
	int i;
	for(i = 0;i < n; i++) printf("%lf ", v[i]);
	printf("\n");
}
//faz a troca de informacao
void allgatherRing(double*x, int tamanho, double*y, MPI_Comm ringComm){
	int i, procs, rank;
	int proximo, anterior;
	int envia, recebe;
	MPI_Status status;

	MPI_Comm_size(ringComm, &procs);
	MPI_Comm_rank(ringComm, &rank);

	for(i = 0; i < tamanho; i++) y[i + rank*tamanho] = x[i];

	proximo = (rank + 1) % procs;
	anterior = (rank - 1 + procs) % procs;

	for(i = 0; i < procs - 1; i++){
		envia = ((rank - i + procs) % procs)*tamanho;
		recebe = ((rank - i - 1 + procs) % procs)*tamanho;
		MPI_Send(y + envia, tamanho, MPI_DOUBLE, proximo, 0, ringComm);
		MPI_Recv(y + recebe, tamanho, MPI_DOUBLE, anterior, 0, ringComm, &status);
	}
}
//imprime matriz
void printM(double**A, const int rows, const int col){
	int i, j;
	for(i = 0;i < rows; i++){
		for(j = 0; j < col; j++) printf("%lf ", A[i][j]);
		printf("\n");
	}
}
//funcao principal
int main(int argc, char*argv[]){
	
	int n = 8, procs, rank, dim, i;
	double *x, *y, **A, *ring, *b;
	double start, end;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &procs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

while(n < 10030){
	//determina ordem da matriz dividida por numero de processadores
	dim = n / procs;
	start = MPI_Wtime();
	//aloca x
	x = alocaVetor(dim);
	iniciaVetor(dim, x, rank);
	//aloca A
	A = alocaMatriz(dim, n);
	iniciaMatriz(dim, n, A, rank);
	//aloca ring
	ring = alocaVetor(n);
	//recebendo informacao por anel
	allgatherRing(x, dim, ring, MPI_COMM_WORLD);
	//alocando vetor b
	b = alocaVetor(dim);
	//calculando o produto
	MatrizxVetor(dim, n, ring, A, b);
	//aloca vetor resultado em rank 0
	if(rank == 0){
		y = alocaVetor(n);
	}
	//coloca o resultado de todas multiplicacoes em y de rank 0
	MPI_Gather(b, dim, MPI_DOUBLE, y, dim, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	//termina contagem do tempo
	end = MPI_Wtime();
	//imprime os resultados
	if(rank == 0){
		printf("\nVetor y calculado em %lfs de ordem %d\n", end - start, n);
		//libera y
		free(y);
	}
	//libera resto das variaveis
	free(x); free(b); free(ring);
	for(i = 0; i<dim; i++) free(A[i]);
	free(A);
	//adiciona ao n
	n += 80;
}
	//finaliza
	MPI_Finalize();

}
