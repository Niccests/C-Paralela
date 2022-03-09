#!/usr/bin/perl 

###############################################
 # Fecha: 17 de febrero de 2022
 # Autor: Nicolas Esteban Gonzalez Ubaque
 # Materia: Parallel Computing
 # Tema: Diseño de experimentos, automatización 
 # de ejecusión (promedio y desviación)
###############################################
$PATH = `pwd`;# el signo pesos ($) para las variables
chomp($PATH);#chomp para que no salte de línea
# Una variable que represente la cantidad de repeticiones
$N = 2;
# Crear un vector de ejecutables y se hace con el simbolo @
@Ejecutables = ("Bench01", "Bench02");#01 es el de c y el 02 es el de cpp
# Crear un vector de dimensiones NxN
@Dimension = ("100", "200"); # el bench 01 de ejecuta N veces
foreach $exe(@Ejecutables){
	foreach $size(@Dimension){
		$File = "$PATH/"."Soluciones/"."$exe"."-$size".".txt";
		
		#print "$File \n";
		for($i=0; $i<$N; $i++){
			system "$PATH/$exe $size >> $File";
			#print "$PATH/$exe $size \n";
		}
		close $File;
	}
}
exit(0);


