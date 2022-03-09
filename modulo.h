/*********************************************
 	* Universidad Sergio Arboleda
	* Fecha: 01 de marzo de 2022
	* Autor: Nicolas Esteban Gonzalez Ubaque
	* Materia: Parallel Computing
	* Tema: Implementación Posix (Library)
	* interfaz del modulo para multiplicar 2 matrices sin variables globales.
	* Se requiere que el diseño sea modular.
	* El modulo implementará los hilos que harán el cálculo del producto
**********************************************/
#ifndef MODULO_H_INCLUDED
#define MODULO_H_INCLUDED

/*Prototipos de las funciones a presentar como interfaz del modulo.c*/

void *multiplicacion(void *arg);

#endif
