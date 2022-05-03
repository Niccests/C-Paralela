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


/*Funcion main*/

int main(int argc, char* argv[]){
    double **Ma,**Mb,**Mc;
    int N,Nthreads,i;
    pthread_t *threads;
    strucHilos *theArguments;
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

    threads=(pthread_t*)malloc(N*sizeof(pthread_t));
    theArguments= (strucHilos*)malloc(Nthreads*sizeof(strucHilos));
    
    Ma = memReserve(N); 
    Mb = memReserve(N);
    Mc = memReserve(N);
    initMatrix_DoublePointers (Ma, Mb, Mc, N);
    
    printMatrix_DoublePointers (Ma, N);
    printMatrix_DoublePointers (Mb, N);
    
    sampleStart();
    for (i = 0; i < Nthreads; ++i){
         theArguments[i].numThreads=Nthreads;
         theArguments[i].matrixSize=N;
         theArguments[i].matrixA=Ma;
         theArguments[i].matrixB=Mb;
         theArguments[i].matrixR=Mc;
         theArguments[i].idThread=i;
         pthread_create(&threads[i],NULL,multMM,&theArguments[i]);
    }
     for (i = 0; i < Nthreads; ++i){
         pthread_join(threads[i],NULL);
     }
    sampleEnd();

    free(Ma);
    free(Mb);
    free(Mc);   
    printMatrix_DoublePointers(Mc, N);
    return EXIT_SUCCESS;
}

