//TRABALHO 3 - EXERCICIO 4 - COMPUTACAO PARALELA
//ALUNO - ISRAEL CAMPIOTTI

#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

//recebe dimensao e indices de forma matricial para calcula indice de forma vetorial
int calculaIndice(int dimension, int i, int j, int k){
	return i*pow(dimension,2) + j*dimension + k; 
}
//recebe vetor, indice de inicio e de fim, dimensao, valor a se colocar
//y, x e z sao variaveis boolean - 1 para true, 0 para false- somente uma pode ser verdadeira
//dada variavel boolean verdadeira faz esta igual a coordV e coloca neste plano os valores de v_border
void defineBorda(double *vetor, int start_index, int end_index, int dimension, double v_border, int coordV, int y, int x, int z){
	int i, j, index;	
	if(y == 1){
		for(i = start_index; i < end_index; i++){
			for(j = start_index; j < end_index; j++){
				index = calculaIndice(dimension, coordV, i, j);
				vetor[index] = v_border;
			}
		}
	}else if(x == 1){
		for(i = start_index; i < end_index; i++){
			for(j = start_index; j < end_index; j++){
				index = calculaIndice(dimension, i, coordV, j);
				vetor[index] = v_border;
			}
		}
	}else if(z == 1){
		for(i = start_index; i < end_index; i++){
			for(j = start_index; j < end_index; j++){
				index = calculaIndice(dimension, i, j, coordV);
				vetor[index] = v_border;
			}
		}
	}
}
//recebe o vetor, a dimensao e os valores a se colocar no cubo pequeno central
void montaCubo_Especial(double *vetor, int dimension, double v_border, double v_inside){
	int i, j, k, index, start = dimension/3, end = start + dimension/3 + 1; 
	for(i = start; i < end; i++){
		for(j = start; j < end; j++){
			for(k = start; k < end; k++){
				index = calculaIndice(dimension, i, j, k);
				vetor[index] = v_inside;
			}
		}
	}
	i = start; //y 
	defineBorda(vetor, start, end, dimension, v_border, i, 1, 0, 0);
	i = end-1; //y
	defineBorda(vetor, start, end, dimension, v_border, i, 1, 0, 0);
	j = start; //x
	defineBorda(vetor, start, end, dimension, v_border, j, 0, 1, 0);
	j = end-1; //z
	defineBorda(vetor, start, end, dimension, v_border, j, 0, 1, 0);
	k = start; //z
	defineBorda(vetor, start, end, dimension, v_border, k, 0, 0, 1);
	k = end-1; //z
	defineBorda(vetor, start, end, dimension, v_border, k, 0, 0, 1);	
}
//recebe cubo e o preenche com o chute inicial
void montaCubo_Inteiro(double *vetor, int dimension, double v_inside){
	int i, j, k, index;
	for(i = 0; i < dimension; i++){
		for(j = 0; j < dimension; j++){
			for(k = 0; k < dimension; k++){
				index = i*pow(dimension,2) + j*dimension + k;
				vetor[index] = v_inside;
			}
		}
	}
}
//imprime cubo
void imprimeCubo(double *vetor, int dimension){
	int i, j, k, index;
	for(i = 0; i < dimension; i++){
		//printf("linha %d\n", i);
		for(j = 0; j < dimension; j++){
			//printf("linha %d\n", j);
			for(k = 0; k < dimension; k++){
				//printf("linha %d\n", k);
				index = i*pow(dimension,2) + j*dimension + k;
				printf("index %d = %.2lf \n", index, vetor[index]);
			}
			printf("\n");
		}
	}
}
//igual dois vetores do cubo
void igualaCubos(double *vetorA, double *vetorB, int dimension){
	int i;
	for(i = 0; i < dimension; i++){
		vetorB[i] = vetorA[i];
	}
}
//calcula o erro relativo
double calculaErroRelativo(double *v_new, double *v_old, int dimension){
	int i, j, k, index;
	double sum = 0.0;
	sum = 0.0;
	for(i = 1; i < dimension-1; i++){
		for(j = 1; j < dimension-1; j++){
			for(k = 1; k < dimension-1; k++){
				index = calculaIndice(dimension, i, j, k);
				if(v_old[index] != 0.0)	sum += fabs((v_new[index] - v_old[index]) / v_old[index]);  
			}
		}
	}
	return sum;
}

//PROGRAMA PRINCIPAL
int main(int argc, char*argv[]){
	//variavel para arquivo .txt
	FILE *out;
	//variaveis dos cubos e processos
	int global_cube_dimension = 10, cube_volume, cube_x, cube_y, cube_z, cube_index;
	double *cube_vector, cube_v1 = 5.0, cube_v2 = 10.0, cube_insidev1 = 0.0, cube_v0 = 6.0;
	double *cube_previous, *cube_all;
	int rank, nprocs, tag = 0;
	int rank_cube_dimension, rank_cube_index;
	int max_iterations = 1000, count_iterations;
	int i, j, k, p;
	double dif = 0.0, tol = 0.00001, dif_reduce;
	//variaveis da topologia virtual
	int *coord;
	int ndim, *dims, *period, reorder = 0, procdim;
	int src, dest, proc_null = MPI_PROC_NULL;
	int dir0_source, dir0_destine, dir1_source, dir1_destine, dir2_source, dir2_destine;
	int displacement = 1, dir0 = 0, dir1 = 1, dir2 = 2;
	MPI_Comm cube_comm;

//INICIA MPI
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	//inicia variaveis da topologia
	procdim = cbrt(nprocs); 
	ndim = 3; // procdim = raiz cubica de nprocs - 3 devido ndim = 3
	dims = malloc(ndim*sizeof(int));
	period = malloc(ndim*sizeof(int));
	coord = malloc(ndim*sizeof(int));
	if(rank == 0){
		period[0] = 0; period[1] = period[0]; period[2] = period[0]; //define topologia nao periodica
		dims[0] = procdim; dims[1] = dims[0]; dims[2] = dims[0];	//define numero de processos em cada dimensao
	}
	//envia mesma informacao para todas ranks
	MPI_Bcast(period, ndim, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(dims, ndim, MPI_INT, 0, MPI_COMM_WORLD);
	//cria comunicador da topologia
	MPI_Cart_create(MPI_COMM_WORLD, ndim, dims, period, reorder, &cube_comm);
	//recebendo coordenadas de cada rank
	MPI_Cart_coords(cube_comm, rank, ndim, coord);

	/*recebendo sources e destinos em cada direcao*/
	//direcao 0
	MPI_Cart_shift(cube_comm, dir0, displacement, &dir0_source, &dir0_destine);
	//direcao 1
	MPI_Cart_shift(cube_comm, dir1, displacement, &dir1_source, &dir1_destine);
	//direcao 2
	MPI_Cart_shift(cube_comm, dir2, displacement, &dir2_source, &dir2_destine);

	/*construindo o cubo maior*/
	cube_volume = pow(global_cube_dimension, 3);
	cube_all = malloc(cube_volume*sizeof(double));
	//construindo o cubo todo em rank 0
	if(rank == 0){
	//preenche o cubo com o chute inicial v0
		montaCubo_Inteiro(cube_all, global_cube_dimension, cube_v0);
	//arruma as bordas do cubo
		cube_y = 0; //y = 0
		defineBorda(cube_all, 0, global_cube_dimension, global_cube_dimension, cube_v2, cube_y, 1, 0, 0);
		cube_y = global_cube_dimension - 1; //y = global_cube_dimension - 1
		defineBorda(cube_all, 0, global_cube_dimension, global_cube_dimension, cube_v2, cube_y, 1, 0, 0);
		cube_x = 0; //x = 0
		defineBorda(cube_all, 0, global_cube_dimension, global_cube_dimension, cube_v2, cube_x, 0, 1, 0);
		cube_x = global_cube_dimension - 1; //z = global_cube_dimension - 1
		defineBorda(cube_all, 0, global_cube_dimension, global_cube_dimension, cube_v2, cube_x, 0, 1, 0);
		cube_z = 0; //z = 0
		defineBorda(cube_all, 0, global_cube_dimension, global_cube_dimension, cube_v2, cube_z, 0, 0, 1);
		cube_z = global_cube_dimension - 1; //z = global_cube_dimension - 1
		defineBorda(cube_all, 0, global_cube_dimension, global_cube_dimension, cube_v2, cube_z, 0, 0, 1);			
	//monta o cubo do meio
		montaCubo_Especial(cube_all, global_cube_dimension, cube_v1, cube_insidev1);
		//imprimeCubo(cube_all, global_cube_dimension);
	}
	//compartilha cubo com todos processos
	MPI_Bcast(cube_all, cube_volume, MPI_DOUBLE, 0, cube_comm);
	MPI_Barrier(cube_comm);
	//if(rank == 2) imprimeCubo(cube_all, global_cube_dimension);
	/*construindo os cubos para cada rank*/
	rank_cube_dimension = global_cube_dimension / procdim + 1;
	cube_vector = malloc(pow(rank_cube_dimension,3)*sizeof(double));
	//usando as coordenadas para decidir a parte do cubo a se receber
	cube_y = coord[0]*(rank_cube_dimension - 2);
	cube_x = coord[1]*(rank_cube_dimension - 2);
	cube_z = coord[2]*(rank_cube_dimension - 2);
	rank_cube_index = 0;
	for(i = cube_y; i < cube_y + rank_cube_dimension; i++){
		for(j = cube_x; j < cube_x + rank_cube_dimension; j++){
			for(k = cube_z; k < cube_z + rank_cube_dimension; k++){
				cube_index = calculaIndice(global_cube_dimension, i, j, k);
				cube_vector[rank_cube_index++] = cube_all[cube_index];
			}
		}
	}
	//liberando memoria
	free(cube_all);

	/*iniciando o metodo de jacobi*/
	//alocando cubo anterior
	cube_previous = malloc(pow(rank_cube_dimension, 3)*sizeof(double));
	igualaCubos(cube_vector, cube_previous, pow(rank_cube_dimension,3));
	//realizando iteracoes
	for(count_iterations = 0; count_iterations < max_iterations; count_iterations++){
		//realiza iteracao atual
		for(i = 1; i < rank_cube_dimension-1; i++){
			for(j = 1; j < rank_cube_dimension-1; j++){
				for(k = 1; k < rank_cube_dimension-1; k++){
					cube_index = calculaIndice(rank_cube_dimension, i, j, k);
					if(cube_vector[cube_index] != cube_v1 && cube_vector[cube_index] != cube_insidev1){
						cube_vector[cube_index] = cube_previous[calculaIndice(rank_cube_dimension, i-1, j, k)];
						cube_vector[cube_index] += cube_previous[calculaIndice(rank_cube_dimension, i+1, j, k)];
						cube_vector[cube_index] += cube_previous[calculaIndice(rank_cube_dimension, i, j-1, k)];
						cube_vector[cube_index] += cube_previous[calculaIndice(rank_cube_dimension, i, j+1, k)];
						cube_vector[cube_index] += cube_previous[calculaIndice(rank_cube_dimension, i, j, k-1)];
						cube_vector[cube_index] += cube_previous[calculaIndice(rank_cube_dimension, i, j, k+1)];
						cube_vector[cube_index] /= 6.0;
					}				
				}
			}
		}
		/*inicia processo de send e receive*/
	
		//ENVIANDO NA DIRECAO 0 - DOWN
		if(dir0_destine != MPI_PROC_NULL){
			cube_index = calculaIndice(rank_cube_dimension, rank_cube_dimension-2, 0, 0); 
			MPI_Send(cube_vector+cube_index, pow(rank_cube_dimension,2), MPI_DOUBLE, dir0_destine, tag, cube_comm);
		}
		//RECEBENDO DA DIRECAO 0 - UP
		else if(dir0_source != MPI_PROC_NULL){
			cube_index = calculaIndice(rank_cube_dimension, 0, 0, 0);
			MPI_Recv(cube_vector+cube_index, pow(rank_cube_dimension,2), MPI_DOUBLE, dir0_source, tag, cube_comm, MPI_STATUS_IGNORE); 
		}
		//ENVIANDO DA DIRECAO 0 - UP
		if(dir0_source != MPI_PROC_NULL){
			cube_index = calculaIndice(rank_cube_dimension, 1, 0, 0); 
			MPI_Send(cube_vector+cube_index, pow(rank_cube_dimension,2), MPI_DOUBLE, dir0_source, tag, cube_comm);
		}
		//RECEBENDO DA DIRECAO 0 - DOWN
		else if(dir0_destine != MPI_PROC_NULL){
			cube_index = calculaIndice(rank_cube_dimension, rank_cube_dimension-1, 0, 0);
			MPI_Recv(cube_vector+cube_index, pow(rank_cube_dimension,2), MPI_DOUBLE, dir0_destine, tag, cube_comm, MPI_STATUS_IGNORE); 
		}
		//ENVIANDO NA DIRECAO 1 - RIGHT
		if(dir1_destine != MPI_PROC_NULL){
			for(i = 0; i < rank_cube_dimension; i++){
				cube_index = calculaIndice(rank_cube_dimension, i, rank_cube_dimension-2, 0); 
				MPI_Send(cube_vector+cube_index, rank_cube_dimension, MPI_DOUBLE, dir1_destine, tag, cube_comm);
			}
		}
		//RECEBENDO NA DIRECAO 1 - LEFT
		if(dir1_source != MPI_PROC_NULL){
			for(i = 0; i < rank_cube_dimension; i++){
				cube_index = calculaIndice(rank_cube_dimension, i, 0, 0);
				MPI_Recv(cube_vector+cube_index, rank_cube_dimension, MPI_DOUBLE, dir1_source, tag, cube_comm, MPI_STATUS_IGNORE);
			}
		}
		//ENVIANDO NA DIRECAO 1 - LEFT
		if(dir1_source != MPI_PROC_NULL){
			for(i = 0; i < rank_cube_dimension; i++){
				cube_index = calculaIndice(rank_cube_dimension, i, 1, 0); 
				MPI_Send(cube_vector+cube_index, rank_cube_dimension, MPI_DOUBLE, dir1_source, tag, cube_comm);
			}
		}
		//RECEBENDO NA DIRECAO 1 - RIGHT
		if(dir1_destine != MPI_PROC_NULL){
			for(i = 0; i < rank_cube_dimension; i++){
				cube_index = calculaIndice(rank_cube_dimension, i, rank_cube_dimension-1, 0);
				MPI_Recv(cube_vector+cube_index, rank_cube_dimension, MPI_DOUBLE, dir1_destine, tag, cube_comm, MPI_STATUS_IGNORE);
			}
		}
		//ENVIANDO NA DIRECAO 2 - IN
		if(dir2_destine != MPI_PROC_NULL){
			for(i = 0; i < rank_cube_dimension; i++){
				for(j = 0; j < rank_cube_dimension; j++){
					cube_index = calculaIndice(rank_cube_dimension, i, j, rank_cube_dimension-1);
					MPI_Send(&cube_vector[cube_index], 1, MPI_DOUBLE, dir2_destine, tag, cube_comm);
				}
			}
		}
		//RECEBENDO NA DIRECAO 2 - OUT
		if(dir2_source != MPI_PROC_NULL){
			for(i = 0; i < rank_cube_dimension; i++){
				for(j = 0; j < rank_cube_dimension; j++){
					cube_index = calculaIndice(rank_cube_dimension, i, j, 0);
					MPI_Recv(&cube_vector[cube_index], 1, MPI_DOUBLE, dir2_source, tag, cube_comm, MPI_STATUS_IGNORE);
				}
			}
		}
		//ENVIANDO NA DIRECAO 2 - OUT
		if(dir2_source != MPI_PROC_NULL){
			for(i = 0; i < rank_cube_dimension; i++){
				for(j = 0; j < rank_cube_dimension; j++){
					cube_index = calculaIndice(rank_cube_dimension, i, j, 1);
					MPI_Send(&cube_vector[cube_index], 1, MPI_DOUBLE, dir2_source, tag, cube_comm);
				}
			}
		}
		//RECEBENDO NA DIRECAO 2 - IN
		if(dir2_destine != MPI_PROC_NULL){
			for(i = 0; i < rank_cube_dimension; i++){
				for(j = 0; j < rank_cube_dimension; j++){
					cube_index = calculaIndice(rank_cube_dimension, i, j, rank_cube_dimension-1);
					MPI_Recv(&cube_vector[cube_index], 1, MPI_DOUBLE, dir2_destine, tag, cube_comm, MPI_STATUS_IGNORE);
				}
			}
		}
		//calcula erro relativo
		dif = calculaErroRelativo(cube_vector, cube_previous, rank_cube_dimension);
		MPI_Barrier(cube_comm);
		//faz reduce em dif
		MPI_Allreduce(&dif, &dif_reduce, 1, MPI_DOUBLE, MPI_SUM, cube_comm);
		//checa se criterio de parada foi atingido
		if(dif_reduce < tol) break;
		//salva o novo cubo
		igualaCubos(cube_vector, cube_previous, pow(rank_cube_dimension,3));
	} //FIM DO METODO DE JACOBI
	free(cube_previous);
	

	/*remontando o cubo final em rank 0*/
	if(rank != 0) {
		//enviando para rank 0 a informacao das coordenadas da rank e do cubo
		MPI_Send(coord, ndim, MPI_INT, 0, tag, cube_comm);
		MPI_Send(cube_vector, pow(rank_cube_dimension, 3), MPI_DOUBLE, 0, tag, cube_comm);
	}
	if(rank == 0) {
		cube_all = malloc(cube_volume*sizeof(double));
	//escreve o cubo em rank 0
		for(i = 0; i < rank_cube_dimension; i++){
			for(j = 0; j < rank_cube_dimension; j++){
				for(k = 0; k < rank_cube_dimension; k++){
					rank_cube_index = calculaIndice(rank_cube_dimension, i, j, k);
					cube_index = calculaIndice(global_cube_dimension, cube_y+i, cube_x+j, cube_z+k);
					cube_all[cube_index] = cube_vector[rank_cube_index];
				}
			}
		}
	//recebe das outras ranks e monta o cubo	
		for(p = 1; p < nprocs; p++){
			MPI_Recv(coord, ndim, MPI_INT, p, tag, cube_comm, MPI_STATUS_IGNORE);
			cube_y = coord[0]*(rank_cube_dimension - 2);
			cube_x = coord[1]*(rank_cube_dimension - 2);
			cube_z = coord[2]*(rank_cube_dimension - 2);
			MPI_Recv(cube_vector, pow(rank_cube_dimension, 3), MPI_DOUBLE, p, tag, cube_comm, MPI_STATUS_IGNORE);
			for(i = 0; i < rank_cube_dimension; i++){
				for(j = 0; j < rank_cube_dimension; j++){
					for(k = 0; k < rank_cube_dimension; k++){
						rank_cube_index = calculaIndice(rank_cube_dimension, i, j, k);
						cube_index = calculaIndice(global_cube_dimension, cube_y+i, cube_x+j, cube_z+k);
						cube_all[cube_index] = cube_vector[rank_cube_index];
					}
				}
			}	
		}
	//escrevendo o cubo final em um ficheiro
		out = fopen("cubo.txt", "w+");
		fprintf(out,"Numero de Iteracoes feitas por cada processo: %d\nValor final de dif: %.16lf\n", count_iterations, dif_reduce);
		for(i = 0; i < global_cube_dimension; i++){
			for(j = 0; j < global_cube_dimension; j++){
				for(k = 0; k < global_cube_dimension; k++){
					cube_index = calculaIndice(global_cube_dimension, i, j, k);
					fprintf(out, "(%d, %d, %d) = %.3lf\n", i, j, k, cube_all[cube_index]);
				}
			}
		}
	//liberando memoria
	fclose(out); free(cube_all);	
	}
	free(cube_vector);

	MPI_Finalize();
}
