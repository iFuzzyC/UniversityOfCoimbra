#include <mpi.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "operations.h"


void main(int argc, char*argv[]){
    int n = 16;
    if(argc == 1){
        n = 16;
    }else if(argc == 2){
        n = atoi(argv[1]);
    }else{
        printf("You passed too many arguments! Using the first as matrix dimension\n");
    }
    int finished = False;
    double *x_new, *x_old,**A,*b;
    double *x_rank; 
    double tol = 0.01;
    int rank_dim;
    int nprocs, rank;
    int i, j, k;
    double sum = 0;
    MPI_Comm comm = MPI_COMM_WORLD;
    //initiate MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_size(comm, &nprocs);
    MPI_Comm_rank(comm, &rank);

    if(rank == 0){
        if(n %nprocs != 0){
            printf("Choose number of processes multiple of matrix dimension\n");
            printf("Dimension = %d, #Processes = %d\n", n, nprocs);
            exit(0);
        }
    }
    rank_dim = n/nprocs;

    // //alocating vector
    x_rank = alocaVetor(rank_dim); 
    zeroVetor(rank_dim, x_rank);
    x_old = alocaVetor(n); 
    iniciaVetor(n, rank, x_old);
    b = alocaVetor(n); 
    iniciaVetor(n, PI, b);
    // //alocating matrix
    A = alocaMatriz(rank_dim, n); zeroMatriz(rank_dim, n, A);
    iniciaMatriz(rank_dim, n, A, rank);
    int diag;
    if(rank == 0){
        x_new = alocaVetor(n);
    }
    while (finished != True){
        //doing the jacobi for the x_rank
        for (i = 0; i < rank_dim; i++){
            diag = rank_dim * rank + i;
            sum = 0;
            for (j = 0; j < n; j++)
                sum += A[i][j] * x_old[j];
            x_rank[i] = (b[diag] - (sum - A[i][diag]*x_old[diag]))/A[i][diag];
        }
        // //doing gather at rank 0
        MPI_Gather(x_rank, rank_dim, MPI_DOUBLE, x_new, rank_dim, MPI_DOUBLE, 0, comm);
        // checking if we are finished
        if(rank == 0){
            finished = Stop(n, tol, x_old, x_new);
            igualaVetor(n, x_new, x_old);
        }
        MPI_Barrier(comm);
        //now we broadcast finished and x_new as x_old
        MPI_Bcast(&finished, 1, MPI_INT, 0, comm);
        MPI_Bcast(x_old, n, MPI_DOUBLE, 0, comm);
        MPI_Barrier(comm);
    }
    if(rank == 0){
        printV(x_old, n);
    }
}