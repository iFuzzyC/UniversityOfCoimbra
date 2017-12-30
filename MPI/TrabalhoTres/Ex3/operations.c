#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "operations.h"

double*alocaVetor(int n){
	double *v;
	v = malloc(n*sizeof(double));
	return v;
}

void MinPlusSqr(double**A, double**B, double**C, int N){
    int i, j, k;
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            for(k = 0; k < N; k++){
                if(C[i][j] > A[i][k] + B[k][j]) C[i][j] = A[i][k] + B[k][j];
            }
        }
    }
}

double MinPlusVetor(int n, double*a, double*b){
    int i;
    double v = a[0] + b[0];
    for(i = 1; i < n; i++){
        if(v > a[i] + b[i]) v = a[i] + b[i];
    }
    return v;
}

double**alocaMatriz(int rows, int col){
	double**M;
	int i;
	M = malloc(rows*sizeof(double*));
	for(i = 0; i < rows; i++) M[i] = malloc(col*sizeof(double));
	return M;
}

void iniciaVetor(int n, int rank, double*v){
	int i;
	for(i = 0; i < n; i++){
		v[i] = i*PI + rank;
	}
}

void iniciaMatriz(int rows, int col, double**M, int rank){
	int i, j;
	for(i = 0; i < rows; i++){
        M[i][i+rank*rows] = j + 1 + (i + rows*rank)*PI;
	}
}

void zeroMatriz(int rows, int cols, double**M){
    int i, j;
    for(i = 0; i < rows; i++){
        for(j = 0; j < cols; j++){
            M[i][j] = 0;
        }
    }
}

void zeroVetor(int n, double*v){
    int i;
    for(i = 0; i < n; i++) v[i] = 0;
}

void infMatriz(int rows, int cols, double**M){
    int i, j;
    double v = 99999999.0;
    for(i = 0; i < rows; i++){
        for(j = 0; j < cols; j++) M[i][j] = v;
    }
}

double VetorxVetor(int n, double*a, double*b){
	int i;
	double sum = 0;
	for(i = 0; i < n; i++){
		sum += a[i]*b[i];
	}
	return sum;
}

void printM(double**A, const int rows, const int col){
	int i, j;
	for(i = 0;i < rows; i++){
		for(j = 0; j < col; j++) printf("%lf ", A[i][j]);
		printf("\n");
	}
}

void printV(double*v, int n){
    int i;
    for(i = 0; i < n; i++){
        printf("%lf ",v[i]);
    }
    printf("\n");
}

int Stop(int n, double tol, double*old, double*b){
    double sum = 0;
    int i;
    for(i = 0; i < n; i++) sum += pow(b[i] - old[i], 2);
    sum = sqrt(sum);
    if(sum < tol){
        return True;
    }else{
        return False;
    }
}

void igualaVetor(int n, double*a, double*b){
    int i;
    for(i = 0; i < n; i++) b[i] = a[i]; 
}