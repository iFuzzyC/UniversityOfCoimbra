#include <mpi.h>
#include "operations.h"

int main(int argc, char*argv[]){
	
	int dim=8, procs, rank, np, i, j;
	//matrices
	double**A,**B,**C,**P;
	//vectors
	double*partial_col,*full_col;
	//initiates MPI
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &procs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	//defines number of rows
	int rows = dim/procs;
	int cols = dim;
	//alocates the matrices
	A = alocaMatriz(rows, cols);
	B = alocaMatriz(rows, cols);
	C = alocaMatriz(rows, cols);
	//iniciates matrices A and B
	iniciaMatriz(rows, cols, A, rank);
	iniciaMatriz(rows, cols, B, rank);
	//vector to alocate the column
	full_col = alocaVetor(dim);
	//vector to alocate the partial column of each rank
	partial_col = alocaVetor(rows);
	//computes the C for each rank
	for(i = 0; i < cols; i++){
		//receives the full column
		iniciaVetor(rows, i, partial_col, B);
		MPI_Allgather(partial_col, rows, MPI_DOUBLE, full_col, rows, MPI_DOUBLE, MPI_COMM_WORLD);
		//computes the C
		for(j = 0; j < rows; j++){
			C[j][i] = VetorxVetor(dim, A[j], full_col);
		}
	}
	//receives everuthing on rank 0
	if(rank == 0){
		P = alocaMatriz(dim, dim);
		for(i = 0; i < rows; i++) P[i] = C[i];
	}	
	if(rank != 0){
		for(i = 0; i < rows; i++){
			MPI_Send(C[i], dim, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
		}
	}else{
		for(i = 1; i < procs; i++){
			for(j = 0; j < rows; j++){
				MPI_Recv(P[i*rows + j], dim, MPI_DOUBLE, i, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			}
		}
	}
	MPI_Barrier(MPI_COMM_WORLD);
	if(rank == 0){
		printM(P, dim, dim);
	}
	MPI_Finalize();
}

