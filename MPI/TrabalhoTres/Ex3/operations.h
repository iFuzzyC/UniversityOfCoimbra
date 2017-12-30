#ifndef OPERATIONS_H
#define OPERATIONS_H

#define PI 3.1415927
#define False 0
#define True 1

double*alocaVetor(int n);
double**alocaMatriz(int rows, int col);
void iniciaVetor(int n, int rank, double*v);
void iniciaMatriz(int rows, int col, double**M, int rank);
void zeroMatriz(int rows, int cols, double**M);
void zeroVetor(int n, double*v);
void infMatriz(int rows, int cols, double**M);
double VetorxVetor(int n, double*a, double*b);
void MinPlusSqr(double**A, double**B, double**C, int N);
double MinPlusVetor(int n, double*a, double*b);
void printM(double**A, const int rows, const int col);
void printV(double*v, int n);
int Stop(int n, double tol, double*old, double*b);
void igualaVetor(int n, double*a, double*b);
#endif