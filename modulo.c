/* 	* Universidad Sergio Arboleda
	* Fecha: 089 de febrero de 2022
	* Autor: Nicolas Esteban Gonzalez Ubaque
	* Materia: Parallel Computing
	* Tema: Implementación de BenchMarck en C
*/
#include "modulo.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <sys/time.h>
#include <errno.h>

/* Se crea una variable con un valor alto para reservar memoria*/
//#define DATA_SZ (1024*1024*64*3)

/* Se reserva el espacio de memoria según el valor */
//static double MEM_CHUNK[DATA_SZ];

/*Definiciòn de constantes*/
struct timespec inicio, fin;

/******************funciones **********/
/*Inicio: medida de tiempo*/
void SampleStart(){
	clock_gettime(CLOCK_MONOTONIC, &inicio); //& està indicando la direcciòn de inicio
}

/*Fin: medida de tiempo*/
void SampleEnd(){
	clock_gettime(CLOCK_MONOTONIC, &fin); //& està indicando la direcciòn de inicio
	/* Se imprime el tiempo*/
	double tiempoTotal;
	tiempoTotal = (fin.tv_sec - inicio.tv_sec)*1e9;//tv_sec es una funciòn de struct//// 1e9 son macrosegundos
	tiempoTotal = (tiempoTotal + (fin.tv_nsec - inicio.tv_nsec))*1e-9;
	printf(" %f \n", tiempoTotal);
	
}

/*Se crea un doble precisiòn aleatorio*/
float randMM(){
	float min = 0.001, max = 9.999;
	static int first = -1;
	if((first =(first<0)))
		srand(time(NULL)+getpid());
	if(min>max)
		return errno=EDOM, NAN;
	return min + (float)rand()/((float)RAND_MAX/(max-min));
}

/* Se crea la funcion para inicializar las matrices*/
void initMatrix(int SZ, double *Ma, double *Mb, double *Mr){
	int i, j;
	for(i=0; i<SZ; ++i){
		for(j=0; j<SZ; ++j){
			Ma[j+i*SZ]= 3.9*(i-j);
			Mb[j+i*SZ]= 2.0*(j+i);
			Mr[j+i*SZ]= 0.0;
		}
	}
}

/* Se implementa la impresión para efectos de validación*/
void printMatrix(int SZ, double *M){
	int i, j;
	for(i=0; i<SZ; ++i){
		for(j=0; j<SZ; ++j){
			printf("%f   ",M[j+i*SZ]);
			
		}
		printf("\n");
	}
}

void matrixMM1c(int size, double *a, double *b, double *Mr){
	int i, j, k;
	for(i=0; i<size; ++i){
		for(j=0; j<size; ++j){
			/*Necesita punteros auxiliares*/
			double *pA, *pB;
			double sumaAuxiliar = 0.0;
			pA = a + (i*size);
			pB = b + j;
			for(k=0; k<size; ++k,pA++,pB+=size){
				sumaAuxiliar += (*pA * *pB);
			}
			Mr[i*size+j]= sumaAuxiliar;
		}	
	}
}

void matrixMM1f(int size, double *a, double *b, double *Mr){
	int i, j, k;
	for(i=0; i<size; ++i){
		for(j=0; j<size; ++j){
			/*Necesita punteros auxiliares*/
			double *pA, *pB;
			double sumaAuxiliar = 0.0;
			pA = a + (i*size);
			pB = b + (j*size);
			for(k=0; k<size; ++k,pA++,pB++){
				sumaAuxiliar += (*pA * *pB);
			}
			Mr[i*size+j]= sumaAuxiliar;
		}	
	}
}



