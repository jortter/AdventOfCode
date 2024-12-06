#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>

void imprimirMatriz(std::vector<std::vector<char>>& A){
	for(int i = 0; i < A.size(); i++){
		for(int j = 0; j < A.size(); j++){
			std::cout << A[i][j];
		}
	
		std::cout << std::endl;
	}
}

void identificar_XMAS(){

	std::string linea;
	int contador_XMAS = 0;
	// Una matriz es un vector de vectores
	std::vector<std::vector<char>> matriz_letras;

	std::ifstream archivo("input.txt");
	if(!archivo.is_open()){
		throw std::runtime_error("No se ha podido abrir el fichero");
	}

	while(getline(archivo, linea)){
		std::vector<char>fila(linea.begin(), linea.end());
		matriz_letras.push_back(fila);
	}
	
	imprimirMatriz(matriz_letras);
	
	for(int i = 0; i < matriz_letras.size(); i++){	// filas
		for(int j = 0; j < matriz_letras.size(); j++){	// columnas
			// MAS -> MSMS
			if(i+2 < matriz_letras.size() && j+2 < matriz_letras.size() && matriz_letras[i][j] == 'M' && matriz_letras[i+2][j] == 'M' && matriz_letras[i][j+2] == 'S' &&
			matriz_letras[i+2][j+2] == 'S' && matriz_letras[i+1][j+1] == 'A'){
				contador_XMAS++;
			}
			// MAS -> SSMM
			if(i+2 < matriz_letras.size() && j+2 < matriz_letras.size() && matriz_letras[i][j] == 'S' && matriz_letras[i+2][j] == 'M' && matriz_letras[i][j+2] == 'S' &&
			matriz_letras[i+2][j+2] == 'M' && matriz_letras[i+1][j+1] == 'A'){
				contador_XMAS++;
			}
			// MAS -> SMSM
			if(i+2 < matriz_letras.size() && j+2 < matriz_letras.size() && matriz_letras[i][j] == 'S' && matriz_letras[i+2][j] == 'S' && 
			matriz_letras[i][j+2] == 'M' && matriz_letras[i+2][j+2] == 'M' && matriz_letras[i+1][j+1] == 'A'){
				contador_XMAS++;
			}
			// MAS -> MMSS
			if(i+2 < matriz_letras.size() && j+2 < matriz_letras.size() && matriz_letras[i][j] == 'M' && matriz_letras[i+2][j] == 'S' && 
			matriz_letras[i][j+2] == 'M' && matriz_letras[i+2][j+2] == 'S' && matriz_letras[i+1][j+1] == 'A'){
				contador_XMAS++;
			}
	
		}	
	}
	std::cout << contador_XMAS << std::endl;
	archivo.close();
}

int main(){
	try{
		identificar_XMAS();
	} catch(const std::exception& e){
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return 0;
}

