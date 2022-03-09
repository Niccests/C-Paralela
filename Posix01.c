/*********************************************
 	* Universidad Sergio Arboleda
	* Fecha: 01 de marzo de 2022
	* Autor: Nicolas Esteban Gonzalez Ubaque
	* Materia: Parallel Computing
	* Tema: Implementación Posix (Library)
	* Programa para multiplicar 2 matrices sin variables globales.
	* Se requiere que el diseño sea modular.
	* El modulo implementará los hilos que harán el cálculo del producto
**********************************************/

#include "modulo.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

// Se define el número de hilos según la configuración
#define MAX 4

// Se implementa el principal

int main(){
	int mA[MAX][MAX];
	int mB[MAX][MAX];
	//Se crea variables para los indices de las matrices
	int f1=MAX;
	int c1=MAX;
	int f2=MAX;
	int c2=MAX;
	
	//Se generan aleatorios para las matrices
	for(int i=0; i<f1; i++){
		for(int j=0; j<c1; j++){
			mA[i][j] = rand()%10;
			mB[i][j] = rand()%10;
		}
	}
	
	//Presentar la matriz A
		printf("\n");
		printf("Matriz A\n");
	for(int i=0; i<f1; i++){
		for(int j=0; j<c1; j++){
			printf(" %d ",mA[i][j]);
		}
		printf("\n");
	}
	
		printf("\n");
		printf("\n");
		printf("Matriz B\n");
	//Presentar la matriz B
	for(int i=0; i<f1; i++){
		for(int j=0; j<c1; j++){
			printf(" %d ",mB[i][j]);
		}
		printf("\n");
	}
	
	//Declarar un entero que tenga el producto fxc (dimensión de la matriz)
	int maxFC = f1*c1;
	//Se declaran el número de threads de size maxFC
	pthread_t *hilos;
	hilos = (pthread_t *)malloc(maxFC*sizeof(pthread_t));//pthread_t es el tipo de dato de la varible pthread_t
	int contador = 0;
	int* dato = NULL;
	for(int i=0; i<f1; i++){
		for(int j=0; j<c2; j++){
		//Almacenar filas y columnas en data (puntero)
			dato = (int *)malloc((24)*sizeof(int));
			dato[0] = c1;
			for(int k=0; k<c1; k++)
				dato[k+1]=mA[i][k];
			for(int k=0; k<f2; k++)
				dato[k+c1+1]=mB[k][j];
			//Se crean los threads
			pthread_create(&hilos[contador++], NULL, multiplicacion,(void *)(dato));
		
		}
	}
	
	//presentar la matriz resultado
	printf("\n Resultado\n");
	for(int i=0; i<=maxFC; i++){
		//joining de los hilos
		void *k;
		pthread_join(hilos[i], &k);
		//apuntamos p en k
		int *p = (int *)k;
		printf(" %d ",*p);
		if((i+1)%c2==0)
			printf("\n");
		
	
	}
	
	
	return 0;
}










