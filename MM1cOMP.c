/*
* Fecha: 2022-03-16
* Autor: Johan Miranda
* Materia: Computacio paralela y distribuida
*
*/

/*Bibliotecas*/
#include "module.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <omp.h>

/*Variable para reservar espacio de memoria*/
#define DATA_SZ (1024*1024*64*4)

/*Espacio de memoria*/
static double MEM_CHUNK[DATA_SZ];
/*Funcion main*/

int main(int argc, char* argv[]){
    
    int N,Nthreads;

    if (argc!=3){
        printf("Tamaño de matriz <matrix size> y Numero de hilos <# of threads>\n");
        return -1;
    }
    /*Inicializar variables globales*/

    /*Tamaño de matriz*/
    N = atof(argv[1]);    
    /*Numero de hilos*/
    Nthreads = atof(argv[2]);    
    if(Nthreads>omp_get_max_threads()){
        printf("El número de hilos debe ser menor o igual a %d",omp_get_max_threads());
        return -1;
    }
    
	double *Ma, *Mb, *Mc;
	Ma = MEM_CHUNK;
	Mb = Ma + N*N;
	Mc = Mb + N*N;
    initMatrix(N, Ma, Mb, Mc);
    
    /*printMatrix(N, Ma);*/
    /*printMatrix(N, Mb);*/
    
    sampleStart();
    MM1cOMP(Nthreads, N, Ma, Mb, Mc);
    sampleEnd();

    // free(Ma);
    // free(Mb);
    // free(Mc);   
    /*printMatrix(N, Mc);*/
    return EXIT_SUCCESS;
}

