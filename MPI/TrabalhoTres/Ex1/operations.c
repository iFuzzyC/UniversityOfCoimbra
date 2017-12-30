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

double**alocaMatriz(int rows, int col){
	double**M;
	int i;
	M = malloc(rows*sizeof(double*));
	for(i = 0; i < rows; i++) M[i] = malloc(col*sizeof(double));
	return M;
}

void iniciaVetor(int n, int indice, double*v, double**M){
	int i;
	for(i = 0; i < n; i++){
		v[i] = M[i][indice];
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

void zeroMatriz(int rows, int cols, double**M){
    int i, j;
    for(i = 0; i < rows; i++){
        for(j = 0; j < cols; j++){
            M[i][j] = 0;
        }
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
}
