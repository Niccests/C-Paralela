/*********************************************
 	* Universidad Sergio Arboleda
	* Fecha: 01 de marzo de 2022
	** Autor: Nicolas Esteban Gonzalez Ubaque
	* Materia: Parallel Computing
	* Tema: Implementación Posix (Library)
	* Modulo para multiplicar 2 matrices sin variables globales.
	* Se requiere que el diseño sea modular.
	* El modulo implementará los hilos que harán el cálculo del producto
**********************************************/
#include "modulo.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

// Función cada thread calcula un solo elemento sobre la matriz resultado

/* Se pasa como argumento el puntero al vector de datos 
   El vestor de datosserá la porción enviada para el cálculo del elemento sobre la matriz resultado*/
void *multiplicacion(void *arg){
//la variable 'datos' de tipo entero apunta al vector argumeto
	int *datos = (int *)arg;
	int i=0, j, k=0;
	//**-> c¿var que contenga el priero valor de v
	int x = datos[0];
	for(i=1; i<=x; i++)
		k+=datos[i]*datos[i+x];

	int *p = (int *)malloc(sizeof(int));//malloc es una reserva de memoria 
	*p = k;
	// Se usa para terminar el hilo y retornar el valor pasado como puntero
	pthread_exit(p);
	
}
