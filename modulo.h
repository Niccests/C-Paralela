#ifndef MODULO_C_H_INCLUDE
#define MODULO_C_H_INCLUDE

/*Prototipo de funciones*/
void SampleStart();
void SampleEnd();
float randMM();
void initMatrix(int SZ, double *Ma, double *Mb, double *Mr);
void printMatrix(int SZ, double *M);
void matrixMM1c(int size, double *a, double *b, double *Mr);
void matrixMM1f(int size, double *a, double *b, double *Mr);
#endif


