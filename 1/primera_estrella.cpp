#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>

// DyV

int total = 0;

int particion(std::vector<int>& A, int ini, int fin);

 void quickSort(std::vector<int>& A, int ini, int fin){
	if (ini < fin){
		int pivote = particion(A, ini, fin);
		quickSort(A, ini, pivote-1);
		quickSort(A, pivote+1, fin);
	}
}

int particion(std::vector<int>& A, int ini, int fin){
    int i = ini;
	for(int j = ini; j <= fin-1; j++){
		if(A[j] <= A[fin]){
			// Intercambiamos A[i] con A[j]
			std::swap(A[i], A[j]);
			// Avanzamos i
			i++;
		}
	}
	// Tras llegar al último elemento del array, intercambiamos el pivote(A[fin]) con nuestro A[i]
	std::swap(A[i], A[fin]);
	// Como en A[i] tengo mi pivote, devuelvo la posición i 
	return i;
}

void printVect(std::vector<int>& A, std::vector<int>& B){
    for(int i = 0; i < A.size() && i < B.size(); i++){
        std::cout << A[i];
        std::cout << "    ";
        std::cout << B[i] << std::endl;
    }
    std::cout << std::endl;
}

void distVect(){
    // Variables y estructuras de datos a usar
    std::vector<int> n1, n2;
    std::string linea;

    // Abrir el fichero
    std::ifstream archivo("input.txt");
    if(!archivo.is_open()){
    	throw std::runtime_error("No se puede abrir el fichero");
	}

    // En este bucle pondremos el algoritmo del problema
    while(getline(archivo, linea)){
        // Extraer los valores numéricos de un string (lineas del fichero) uno por uno
        std::istringstream ss(linea);
        int numero1, numero2;

        ss >> numero1;
        n1.push_back(numero1);
        
        ss >> numero2;
        n2.push_back(numero2);
    }

    // Imprimir los vectores
    printVect(n1, n2);

    std::cout << std::endl;
    // Ordenar el vector n1 y n2 con selection sort 
    quickSort(n1, 0, n1.size()-1);	
    quickSort(n2, 0, n2.size()-1);	

    // Imprimir los vectores ordenados
    printVect(n1, n2);

    for(int i = 0; i < n1.size() && i < n2.size(); i++){
        total += abs(n1[i] - n2[i]);
    }
    
    std::cout << "La diferencia es: " << total << std::endl;

    archivo.close();

}

int main(){
	try{
    	distVect();
	}
	catch(const std::exception& e){
		std::cerr << "Error: " << e.what() << std::endl;
	}
    return 0;
}

// Para ejecutar c++ 1_1.cpp -o 1_1 && ./1_1
