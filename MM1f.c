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
#include <math.h>
#include <unistd.h>
#include <sys/time.h>
#include <errno.h>


/*Variable para reservar espacio de memoria*/
#define DATA_SZ (1024*1024*64*3)

/*Espacio de memoria*/
static double MEM_CHUNK[DATA_SZ];

int main(int argc, char *argv[]) {

	/*Tamaño de matriz*/
	int N = (int) atof(argv[1]);

	/*Creacion de vectores apuntando al espacio de memoria de tamaño NxN */
	double *Ma, *Mb, *Mr;
	Ma = MEM_CHUNK;
	Mb = Ma + N*N;
	Mr = Mb + N*N;
	initMatrix(N, Ma, Mb, Mr);
	sampleStart();
	MM1f(N, Ma, Mb, Mr);
	sampleEnd();
	if (N<4){
		printf("Ma\n");
		printMatrix(N, Ma);
		printf("Mb\n");
		printTransposed(N, Mb);
		printf("Mr\n");
		printMatrix(N, Mr);
	}
		
	return 0;
}