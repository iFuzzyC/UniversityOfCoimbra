#include <mpi.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "operations.h"

void MatMulSqr(double**A, double**B, double**C, int dim){
    int i, j, k;
    double sum = 0;
    for(i = 0; i < dim; i++){
        for(j = 0; j < dim; j++){
        	sum = 0;
        	for(k = 0; k < dim; k++) sum += A[i][k]*B[k][j];
            C[i][j] += sum;
        }
    }
}

void main(int argc, char*argv[]){
    int i, stage, k_bar, j;
    int ndim, *dims, *period, reorder = 0, procdim, *coord;
    int displacement = 1, dir0 = 0, dir1 = 1;
    int dir0_source, dir0_destine, dir1_source, dir1_destine;
    int nprocs, rank;
    int *remain_dims;
    double **A,**B,**C,**tempA;
    //creates global comm
    MPI_Comm world_comm = MPI_COMM_WORLD, grid_comm, row_comm, col_comm;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(world_comm, &nprocs);
    MPI_Comm_rank(world_comm, &rank);

    //variables of topology
	procdim = sqrt(nprocs); 
	ndim = 2; // procdim = cartesian dimension
	dims = malloc(ndim*sizeof(int));
	period = malloc(ndim*sizeof(int));
	coord = malloc(ndim*sizeof(int));
	if(rank == 0){
		period[0] = False; period[1] = True; //define topologia nao periodica
		dims[0] = procdim; dims[1] = dims[0]; //define numero de processos em cada dimensao
	}
	//envia mesma informacao para todas ranks
	MPI_Bcast(period, ndim, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(dims, ndim, MPI_INT, 0, MPI_COMM_WORLD);
	//cria comunicador da topologia
	MPI_Cart_create(MPI_COMM_WORLD, ndim, dims, period, reorder, &grid_comm);
	//recebendo coordenadas de cada rank
	MPI_Cart_coords(grid_comm, rank, ndim, coord);
    // if(rank == 1){
    //     printf("Rank %d sends to %d and receives from %d on direction %d - True %d\n",\
    //             rank, dir0_destine, dir0_source, dir0, True);
    //     printf("Rank %d sends to %d and receives from %d on direction %d - False %d\n",\
    //             rank, dir1_destine, dir1_source, dir1, False);
    // }
    //creates the row communicator
    remain_dims = malloc(ndim*sizeof(int));
    remain_dims[0] = False; remain_dims[1] = True;
    MPI_Cart_sub(grid_comm, remain_dims, &row_comm);
    remain_dims[0] = True; remain_dims[1] = False;
    MPI_Cart_sub(grid_comm, remain_dims, &col_comm);
    int n = 16;
    int N = n/procdim; //dimension of matrix per rank
    //alocate and init matrices
    A = alocaMatriz(N, N); iniciaMatriz(N, N, A, rank);
    B = alocaMatriz(N, N); iniciaMatriz(N, N, B, rank+0.221);
    C = alocaMatriz(N, N); zeroMatriz(N, N, C);
    tempA = alocaMatriz(N, N);

    //Fox
    int rank_row = coord[0], rank_col = coord[1];
    int destine = (rank_row + 1) % procdim;
    int source = (rank_row + procdim - 1) % procdim;
    int bcast_rank;
    for(stage = 0; stage < procdim; stage++){
        bcast_rank = (rank_row + stage) % procdim;
        if(bcast_rank == rank_col){
            //broadcast the lines of A
            for(i = 0; i < N; i++){
                MPI_Bcast(A[i], N, MPI_DOUBLE, bcast_rank, row_comm);
            }
            //perform multiplication in C matrix
            MatMulSqr(A, B, C, N);
        }else{
            //receiveis the lines of A
            for(j = 0; j < N; j++){
                MPI_Bcast(tempA[j], N, MPI_DOUBLE, bcast_rank, row_comm);
            }
            //perform multiplication in C matrix
            MatMulSqr(tempA, B, C, N);
        }
        for(j = 0; j < N; j++){
            MPI_Sendrecv_replace(B[j], N, MPI_DOUBLE, destine, 1, source, 1, col_comm, MPI_STATUS_IGNORE);
        } 
    }
    MPI_Barrier(world_comm);
    double**rowC = alocaMatriz(N, n);
    for(i = 0; i < N; i++) MPI_Gather(C[i], N, MPI_DOUBLE, rowC[i], N, MPI_DOUBLE, 0, row_comm);
    double**fC = alocaMatriz(n, n);
    if(rank == 0){
        for(i = 0; i < N; i++){
            fC[i] = rowC[i];
        }
    }
    MPI_Barrier(world_comm);
    if(rank != 0 ){
        for(i = 0; i < N; i++) MPI_Send(rowC[i], n, MPI_DOUBLE, 0, 1, world_comm);
    }else{
        int other;
        for(other = 1; other < procdim; other++){
            for(i = 0; i < N; i++){
                MPI_Recv(fC[other*N+i], n, MPI_DOUBLE, other*procdim, 1, world_comm, MPI_STATUS_IGNORE);
            }
        }
    }
    MPI_Barrier(world_comm);
    if(rank == 0){
        printM(fC, n, n);
    }
}
