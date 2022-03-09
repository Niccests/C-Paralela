/* 	* Universidad Sergio Arboleda
	* Fecha: 089 de febrero de 2022
	* Autor: Nicolas Esteban Gonzalez Ubaque
	* Materia: Parallel Computing
	* Tema: Implementaci�n de BenchMarck en C
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <sys/time.h>
#include <errno.h>

/* Se crea una variable con un valor alto para reservar memoria*/
#define DATA_SZ (1024*1024*64*3)

/* Se reserva el espacio de memoria seg�n el valor */
static double MEM_CHUNK[DATA_SZ];

/*Definici�n de constantes*/
struct timespec inicio, fin;

/******************funciones **********/
/*Inicio: medida de tiempo*/
void SampleStart(){
	clock_gettime(CLOCK_MONOTONIC, &inicio); //& est� indicando la direcci�n de inicio
}

/*Fin: medida de tiempo*/
void SampleEnd(){
	clock_gettime(CLOCK_MONOTONIC, &fin); //& est� indicando la direcci�n de inicio
	/* Se imprime el tiempo*/
	double tiempoTotal;
	tiempoTotal = (fin.tv_sec - inicio.tv_sec)*1e9;//tv_sec es una funci�n de struct//// 1e9 son macrosegundos
	tiempoTotal = (tiempoTotal + (fin.tv_nsec - inicio.tv_nsec))*1e-9;
	printf(" %f \n", tiempoTotal);
	
}

/*Se crea un doble precisi�n aleatorio*/
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
	int i, j ,k;
	for(i=0; i<SZ; ++i){
		for(j=0; j<SZ; ++j){
			Ma[j+i*SZ]= randMM();
			Mb[j+i*SZ]= randMM();
			Mr[j+i*SZ]= randMM();
		}
	}
}

/* Se implementa la impresi�n para efectos de validaci�n*/
void printMatrix(int SZ, double *M){
	int i, j ,k;
	for(i=0; i<SZ; ++i){
		for(j=0; j<SZ; ++j){
			printf("%f   ",M[j+i*SZ]);
			
		}
		printf("\n");
	}
}

void matrixMM(int size, double *a, double *b, double *Mr){
	int i, j, k;
	for(i=0; i<size; ++i){
		for(j=0; j<size; ++j){
			/*Necesita punteros auxiliares*/
			double *pA, *pB;
			double sumaAuxiliar = 0.0;
			pA = a + i;
			pB = b + (j*size);
			for(k=0; k<size; ++k,pA+=size,pB++){
				sumaAuxiliar += (*pA * *pB);
			}
			Mr[j*size+i]= sumaAuxiliar;
		}
	}
}


/* Se implementa paso a paso benchmark Multiplicai�n de Matrices
	Algoritmo cl�sico ( filas x columnas) de matrices
	de igual dimensi�n*/

int main(int argc, char *argv[]) {
	
	/* Se calcula la dimensi�n de la matriz*/
	int N = (int) atof(argv[1]);
	//printf("Valor ingresado %d", N);
	
	/* Apuntamos los vectores (creaci�n) al espacio de memoeria reservado, con dimension NxN*/
	double *Ma, *Mb, *Mr; // * el aster�sco se refiere al puntero de memoria
	Ma = MEM_CHUNK;//Ma tiene el espacio de memoria de mem_chunk
	Mb = Ma + N*N;//Ma
	Mr = Mb + N*N;
	
	initMatrix(N, Ma, Mb, Mr);
	
	SampleStart();
	matrixMM(N, Ma, Mb, Mr);
	SampleEnd();
	
	
	return 0;
}
