/*  * Fecha: 3 de febrero de 2022
	* Autor: Nicolas Esteban Gonzalez Ubaque
	* Materia: Computaci�n paralela y distribuida
	* Tema: Construcci�n del primer Benchmark
	* Benchmark: Aplicaci�n de juguete que permite evaluar rendimiento de un aspecto en espec�fico de la computadora
*/
#include	<iostream>
#include	<vector>
#include	<random>
#include	<ctime>
#include	<cstdlib>
#include	<chrono>
#include	<unistd.h>
#include	<math.h>
#include	<cstring>

/*declaraci�n de espacio de dominio*/
using namespace std;

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

/*Se cra un doble precisi�n aleatorio*/
float randMM(){
	float min = 0.001, max = 9.999;
	static int first = -1;
	if((first =(first<0)))
		srand(time(NULL)+getpid());
	if(min>max)
		return errno=EDOM, NAN;
	return min + (float)rand()/((float)RAND_MAX/(max-min));
}
/*Funci�n que genera numero random*/
double randomNumer(double fMin, double fMax){
	double	f = (double)rand()	/ RAND_MAX;
	return fMin + f * (fMax - fMin);
}

/*Funci�n que genera la matriz*/
vector<vector<double>>	generateMatrix(int size){
	vector<vector<double>>	MInicializada(size, vector<double>(size,0));
	int i, j;
	
	for(i=0; i<size; ++i){	
		for(j=0; j<size; ++j){
			MInicializada[i][j] = randMM();
		}
	}
	return MInicializada;
	
}
/* Funci�n multiplicaci�n matrices: Se requiere multiplicar las 2 matrices: adicionalmente los ingenieros deben verificar y validar que realmente se cumple el algoritmo de multiplicaci�n*/
void multiMatriz(vector<vector<double>> Ma, vector<vector<double>> Mb){
	int i,j,k;
	
	//Hacemos una punta de prueba para tomar tiempo inicial
	vector<vector<double>> MResultado(Ma.size(),	vector<double>	(Ma.size(),0));
	for(i=0; i<Ma.size(); ++i){
		for(j=0; j<Ma.size(); ++j){
			for(k=0; k<Ma.size(); ++k){
				MResultado[i][j] += Ma[i][k]*Mb[k][j];
			}
		}
	}

}

/* Funci�n inicializada: Se requiere inicializar las matrices con n�meros aleatorios*/
vector<vector<double>> inicializarMatriz(vector<vector<double>> M){
	int i,j;
	float limInf = 0.001, limSup = 9.999;
	vector<vector<double>> MInicializada(M.size(),	vector<double>	(M.size(),0));
	random_device rd; //se usa para inicializar la semilla
	mt19937 gen(rd());
	uniform_real_distribution<> dis(limInf, limSup);
	//cout	"Valor aletorio -->	"	<<	dis(gen)	<<	"\n\n\n\n"
	
	for(i=0; i<M.size(); ++i){	
		for(j=0; j<M.size(); ++j){
			MInicializada[i][j]	=	dis(gen);
		}
	}
	return MInicializada;
}

/* Se crea la funci�n para imprimir matrices*/
void imprimirMatriz(vector<vector<double>> M){
	int i,j;
	for(i=0; i<M.size(); ++i){	
		for(j=0; j<M.size(); ++j){
			cout	<<	M[i][j]	<<"\t";
		}
		cout	<<	"\n";
	}
}


/*  Se requiere implementar una aplicaci�n que multiplique dos matrices. El algoritmo a usar sera el cl�sico (filas por columnas). */
int main(int argc, char** argv) {
	int i,j,k;
	int	N	=	atoi(argv[1]); // Convertir la cadena de caracteres en n�mero entero con la funci�n atoi()"castear" argv es una variable de tipo caracter
	
	/* Se una la clase vector  para crear las matrices */
					//vector<int> vector01{1,2,3}; vector 1, 2, 3
					//vector<int> vector01(3,-10);matriz 3 veces el n�mero -10
	vector<vector<double>> M1(N,	vector<double>	(N,0));
	vector<vector<double>> M2(N,	vector<double>	(N,0));
	vector<vector<double>> MR(N,	vector<double>	(N,0));
	
	M1 = generateMatrix(N);
	M2 = generateMatrix(N);
	
	SampleStart();
	/* Se hace la multiplicacci�n de las matrices*/
	multiMatriz(M1,M2);
	SampleEnd();
	
	
	return 0;
}
