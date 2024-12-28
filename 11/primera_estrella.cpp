#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>

void imprimirVector(std::vector<int>& A){
	for(int i = 0; i < A.size(); i++){
		std::cout << A[i];
		std::cout << " ";

	}
	std::cout << std::endl;
}

void imprimirMatriz(std::vector<std::vector<int>>& M) {
    for (int i = 0; i < M.size(); i++) {
        for (int j = 0; j < M[i].size(); j++) {
            std::cout << M[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Esto NO puede ser una función recursiva porque solo queremos que me divida el numero 1 sola vez en dos partes 
std::pair<int, int> divisionPiedra(std::vector<int>& A, int ini, int fin){
	
	int m = ini + (fin - ini) / 2;
	int izquierda = 0, derecha = 0;
	// Reconstruimos los números de forma que en la izquierda estarán los digitos del indice 0 a la mitad del vector de A
	for(int i = ini; i <= m; i++){
		izquierda = izquierda * 10 + A[i];
	}
	for(int i = m+1; i <= fin; i++){
		derecha = derecha * 10 + A[i];
	}

	return {izquierda, derecha};
	
}

// Función para pasar pasar el número A[ini] a un vector cuyas componentes son los dígitos que forman el número A[ini] (numero = A[ini])
std::vector<int> obtenerDigitos(int numero){	
	std::cout << "Numero: " << numero << std::endl;
	std::vector<int> digitos;
	while(numero > 0){
		digitos.insert(digitos.begin(), numero % 10);
		numero /= 10;
	}	
	return digitos;
}

// Función recursiva que me calcula el número de piedras que hay en el vector piedras tras pestañear 25 veces
int numeroPiedras(int num_piedras, int pestanyeos, std::vector<int>& A, int ini, int fin, std::vector<std::vector<int>>& M, std::vector<std::vector<bool>>& visitados){
	
	// CASOS BASE -> Aquel en el que el numero de piedras no aumenta, i.e. solo el caso en el que reemplazamos una piedra con un numero por otra con otro numero
	// En cuanto hemos hecho 25 pestañeos, devolvemos el número de piedras, y ésto es lo que se almacena en prinicipal() al llamar a numeroPiedras()
	// Si ya hemos calculado el número de piedras para un número de pestañeos y un número de piedras, devolvemos el valor almacenado en la matriz
	if(visitados[pestanyeos][A.size()]){
		return M[pestanyeos][A.size()];
	}
	
	if(pestanyeos == 0){
		M[pestanyeos][A.size()] = A.size();
		visitados[pestanyeos][A.size()] = true;
		return A.size();	
	}

	// Cuando acabamos recorremos el vector, lo reiniciamos para que vuelva a comprobar los casos recursivos para los vectores sucesivos y sumamos 1 al número de pestañeos
	// (en este caso restamos 1 porque empezamos en 25 pestañeos y vamos decreciendo hasta llegar a 0)
	if(ini > fin){
		std::cout << "Vector de piedras tras hacer un pestañeo: " << std::endl;
		imprimirVector(A);
		std::cout << "He completado 1 pestañeo, luego reinciamos el vector" << std::endl;
		M[pestanyeos][A.size()] = numeroPiedras(A.size(), pestanyeos-1, A, 0, A.size()-1, M, visitados);
		visitados[pestanyeos][A.size()] = true;
		return M[pestanyeos][A.size()];
	}
	
	// Si el numero de la piedra es 0, reemplazamos el 0 por un 1 y avanzamos en el vector para analizar las siguientes piedras
	if(A[ini] == 0){
		A[ini] = 1;
	    M[pestanyeos][A.size()] = numeroPiedras(A.size(), pestanyeos, A, ini+1, fin, M, visitados);
		visitados[pestanyeos][A.size()] = true;
		return M[pestanyeos][A.size()];
	}

	// CASOS RECURSIVOS-> Aquel en el que sí tenemos que dividir una piedra en 2 y por tanto aumenta el numero de piedras, cambiando así nuestro vector
	
	// Si la piedra tiene un numero par de dígitos, dividimos la piedra en 2, tal que la mitad izquierda de los dígitos estarán en la nueva piedra izquierda, y 
	// la mitad derecha de los digitos estarán en la nueva piedra derecha. Además, los ceros a la derecha adicionales no cuentan al dividir la piedra en 2 (100 
	// pasaría a ser 1 0), y tampoco cuentan los ceros a la izquierda (512072 pasaría a ser 512 72)
	
	// Antes que nada, tengo que saber el numero de digitos de la piedra en la que estoy ahora (A[ini])
	// Puedo crearme un vector de enteros en el que almacene los digitos de A[ini] y aplicar en una función externa recursiva DyV para dividirel numero de la piedra en 2
	std::vector<int> digitos = obtenerDigitos(A[ini]);
	
	if((digitos.size() % 2) == 0){
		std::cout << "Piedra actual: " << A[ini] << std::endl;
		auto[izquierda, derecha] = divisionPiedra(digitos, 0, digitos.size()-1);
		std::cout << "Dividimos en: " << izquierda << " y " << derecha << std::endl;
		// Mi piedra actual va a ser la que tenga los numeros de la izquierda
		A[ini] = izquierda;
		std::cout << "Piedra actualizada: " << A[ini] << std::endl;
		// Tenemos que insertar la parte de la derecha en el vector de piedras, justo después de la piedra que acabamos de dividir
		A.insert(A.begin() + ini + 1, derecha);
		imprimirVector(A);
		// Si el número de piedras supera el tamaño de la matriz, tenemos que redimensionar las 2 matrices
		if (A.size() >= M[0].size()) {
    		for (auto& fila : M) {
        		fila.resize(A.size() + 1, -1); // Ajusta el tamaño y rellena con -1
    		}
    		for (auto& fila : visitados) {
        		fila.resize(A.size() + 1, false); // Ajusta el tamaño y rellena con false
   			 }
		}
		// Al insertar una nueva piedra, hay que actualizar los índices del vector e incrementar el número de piedras	
		M[pestanyeos][A.size()] = numeroPiedras(A.size()+1, pestanyeos, A, ini+2, A.size()-1, M, visitados);
		visitados[pestanyeos][A.size()] = true;
		std::cout << "Matriz de memoria tras 1 pestañeo: " << std::endl;
		imprimirMatriz(M);
		return M[pestanyeos][A.size()];
	} else{
		// Si NO se cumple ni el caso base ni el caso recursivo, multiplicamos el numero de la piedra por 2024 y seguimos viendo los siguientes números
		std::cout << "No se cumple ninguno de los 2 casos, luego hacemos: " << A[ini] << " * 2024: " << A[ini] * 2024 << std::endl;
		A[ini] *= 2024;
		imprimirVector(A);
		M[pestanyeos][A.size()] = numeroPiedras(A.size(), pestanyeos, A, ini+1, fin, M, visitados);
		visitados[pestanyeos][A.size()] = true;
		return M[pestanyeos][A.size()];
	}

}
void principal(){

	std::string linea;
	// El arreglo de las piedras lo almacenamos en un vector de enteros
	std::vector<int> piedras;

	std::ifstream archivo("ejemplo.txt");
	if(!archivo.is_open()){
		throw std::runtime_error("No se ha podido abrir el fichero");
	}

	while(getline(archivo, linea)){
		std::istringstream ss(linea);
		int numero;
		piedras.clear();
		while(ss >> numero){
			piedras.push_back(numero);	
		}
		
	}
	archivo.close();
	std::cout << "Vector de piedras inicial: " << std::endl;
	imprimirVector(piedras);

	// Tenemos que llamar a la función recursiva que me de el número de piedras al hacer 25 pestañeos
	int num_blinking = 10;
	// Mi función de memoria o matriz de memoria será de (num_blinking+1)filas x (piedras.size()+1)columnas y la inicializamos al tamaño del vector de piedras
	std::vector<std::vector<int>> M(num_blinking+1, std::vector<int>(piedras.size()+1, -1));
	// Me creo una matriz booleana que me indique si he tocado una posición de la matriz de memoria y la inicializo a false
	std::vector<std::vector<bool>> visitados(num_blinking+1, std::vector<bool>(piedras.size()+1, false));
	std::cout << "Matriz de memoria inicial: " << std::endl;
	imprimirMatriz(M);
	// El numero de piedras es el tamaño del vector, el cual va incrementandose en la función recursiva
	int numero_piedras_totales = numeroPiedras(piedras.size(), num_blinking, piedras, 0, piedras.size()-1, M, visitados);
	std::cout << "Número de piedras totales: " << numero_piedras_totales << std::endl;

}

int main(){
	try{
		principal();
	} catch(const std::exception& e){
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return 0;
}
