/*
* Fecha: 2022-03-16
* Autor: Johan Miranda
* Materia: Computacio paralela y distribuida
*
*/

/*Bibliotecas*/

#include "module.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <errno.h>
#include <pthread.h>
#include <omp.h>

struct timespec inicio, fin;

/*Inicia el tiempo*/
void sampleStart()
{
	clock_gettime(CLOCK_MONOTONIC, &inicio);
}
/*Finaliza el tiempo*/
void sampleEnd()
{
	double totalTime;
	clock_gettime(CLOCK_MONOTONIC, &fin);
	totalTime = (fin.tv_sec - inicio.tv_sec) * 1e9;
	totalTime = (totalTime + (fin.tv_nsec - inicio.tv_nsec)) * 1e-9;
	printf("%f\n", totalTime);
}


void *multMM(void *arg)
{
    int i, j, k,idTh,N,Nthreads,portionSize,initRow,endRow;
    double **Ma,**Mb,**Mr,sum;
	idTh = ((strucHilos*)arg)->idThread;
	Ma = ((strucHilos*)arg)->matrixA;
	Mb = ((strucHilos*)arg)->matrixB;
	Mr = ((strucHilos*)arg)->matrixR;
	N = ((strucHilos*)arg)->matrixSize;
	Nthreads = ((strucHilos*)arg)->numThreads;
	/*Posicion para enviar a cada hilo*/
    portionSize = N / Nthreads;		   
    /*Se ubica al inicio de la fila*/
	initRow = idTh * portionSize;	  
    /*Se ubica al final de la fila*/
	endRow = (idTh + 1) * portionSize; 
	for (i = initRow; i < endRow; i++)
	{
		for (j = 0; j < N; ++j)
		{
			sum = 0;
			for (k = 0; k < N; k++)
			{
				sum += Ma[i][k] * Mb[k][j];
			}
			Mr[i][j] = sum;
		}
	}
    return arg;
}

/*Funcion para generar un numero random*/
double randNumber()
{
	float min = 0.001, max = 9.999;
	static int first = -1;
	if (first == (first < 0))
	{
		srand(time(NULL) + getpid());
	}
	if (min >= max)
	{
		const int NAN = -1e9;
		return errno = EDOM, NAN;
	}
	return min + (float)rand() / ((float)RAND_MAX / (max - min));
}


void initMatrix(int SZ, double *Ma, double *Mb, double *Mr)
{
	int i, j;
	for (i = 0; i < SZ; ++i)
	{
		for (j = 0; j < SZ; ++j)
		{
			Ma[j + i * SZ] = 3.2 * (i + j);
			Mb[j + i * SZ] = 2.4 * (i - j);
			/* Ma[j+i*SZ] = randNumber();*/
			/*Mb[j+i*SZ] = randNumber(); */
			Mr[j + i * SZ] = 0.0;
		}
	}
}

void printTransposed(int SZ, double *M)
{
	int i, j;
	for (i = 0; i < SZ; ++i)
	{
		for (j = 0; j < SZ; ++j)
		{
			printf("  %f  ", M[j * SZ + i]);
		}
		printf("\n");
	}
	printf("----------------------------");
	printf("\n");
}

void printMatrix(int SZ, double *M)
{
	int i, j;
	for (i = 0; i < SZ; ++i)
	{
		for (j = 0; j < SZ; ++j)
		{
			printf("  %f  ", M[j + i * SZ]);
		}
		printf("\n");
	}
	printf("----------------------------");
	printf("\n");
}


void MM1c(int size, double *Ma, double *Mb, double *Mr)
{
	int i, j,k;
	for (i = 0; i < size; ++i)
	{
		for (j = 0; j < size; ++j)
		{
			
			double *pA, *pB;
			double sumaAuxiliar = 0.0;
			pA = Ma + (i * size);
			pB = Mb + j;
			for (k = 0; k < size; ++k, pA++, pB += size)
			{
				sumaAuxiliar += (*pA * *pB);
			}
			Mr[i * size + j] = sumaAuxiliar;
		}
	}
}


void MM1cOMP(int hilos, int size, double *Ma, double *Mb, double *Mr){
	omp_set_num_threads(hilos);
#pragma omp parallel
{
	int i, j,k;
#pragma omp for
	for (i = 0; i < size; ++i){
		for (j = 0; j < size; ++j){
			double *pA, *pB;
			double sumaAuxiliar = 0.0;
			pA = Ma + (i * size);
			pB = Mb + j;
			for (k = 0; k < size; ++k, pA++, pB += size)
			{
				sumaAuxiliar += (*pA * *pB);
			}
			Mr[i * size + j] = sumaAuxiliar;
		}
	}
}
}










void MM1f(int size, double *Ma, double *Mb, double *Mr)
{
	int i, j,k;
	for (i = 0; i < size; ++i)
	{
		for (j = 0; j < size; ++j)
		{
			
			double *pA, *pB;
			double sumaAuxiliar = 0.0;
			pA = Ma + (i * size);
			pB = Mb + (j * size);
			for (k = 0; k < size; ++k, pA++, pB++)
			{
				sumaAuxiliar += (*pA * *pB);
			}
			Mr[i * size + j] = sumaAuxiliar;
		}
	}
}


void MM1fOMP(int hilos, int size, double *Ma, double *Mb, double *Mr){
	omp_set_num_threads(hilos);
#pragma omp parallel
{
	int i, j,k;
#pragma omp for
	for (i = 0; i < size; ++i)
	{
		for (j = 0; j < size; ++j)
		{
			
			double *pA, *pB;
			double sumaAuxiliar = 0.0;
			pA = Ma + (i * size);
			pB = Mb + (j * size);
			for (k = 0; k < size; ++k, pA++, pB++)
			{
				sumaAuxiliar += (*pA * *pB);
			}
			Mr[i * size + j] = sumaAuxiliar;
		}
	}
}	
}


double **memReserve(int size)
{
	
	double *val = (double *)malloc(size * size * sizeof(double));
	int i;
	double **ptr = (double **)malloc(size * size * sizeof(double *));
	for (i = 0; i < size; ++i)
	{
		ptr[i] = &val[i * size];
	}
	return ptr;
}

void initMatrix_DoublePointers(double **MA, double **MB, double **MC, int size)
{
	int i, j;
	for (i = 0; i < size; ++i)
	{
		for (j = 0; j < size; ++j)
		{
			MA[i][j] = 3.9 * (i - j);
			MB[i][j] = 2.0 * (j + i);
			MC[i][j] = 0.0;
		}
	}
}

void printMatrix_DoublePointers(double **M, int size)
{
	if(size<5){
		int i, j;
		for (i = 0; i < size; ++i)
	{
		for (j = 0; j < size; ++j)
		{
			printf("%f ", M[i][j]);
		}
		printf("\n");
	}
	printf("-----------------------------\n");
	}
}
