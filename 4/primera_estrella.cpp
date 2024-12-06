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

	std::ifstream archivo("ejemplo.txt");
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
			// Horizontal derecha
			if(j + 3 < matriz_letras.size() && matriz_letras[i][j] == 'X' && matriz_letras[i][j+1] == 'M' && matriz_letras[i][j+2] == 'A' && matriz_letras[i][j+3] == 'S'){
				contador_XMAS++;
			}
			// Horizontal izquierda
			if(j - 3 >= 0 && matriz_letras[i][j] == 'X' && matriz_letras[i][j-1] == 'M' && matriz_letras[i][j-2] == 'A' && matriz_letras[i][j-3] == 'S'){
				contador_XMAS++;
			}

			// Vertical arriba
			if(i + 3 < matriz_letras.size() && matriz_letras[i][j] == 'X' && matriz_letras[i+1][j] == 'M' && matriz_letras[i+2][j] == 'A' && matriz_letras[i+3][j] == 'S'){
				contador_XMAS++;
			}

			// Vertical abajo
			if(i - 3 >= 0 && matriz_letras[i][j] == 'X' && matriz_letras[i-1][j] == 'M' && matriz_letras[i-2][j] == 'A' && matriz_letras[i-3][j] == 'S'){
				contador_XMAS++;
			}

			// Diagonal arriba derecha
			if(i - 3 >= 0 && j + 3 < matriz_letras.size() && matriz_letras[i][j] == 'X' && matriz_letras[i-1][j+1] == 'M' && matriz_letras[i-2][j+2] == 'A' &&
			matriz_letras[i-3][j+3] == 'S'){
				contador_XMAS++;
			}

			// Diagonal arriba izquierda
			if(i - 3 >= 0 && j -3 >= 0 && matriz_letras[i][j] == 'X' && matriz_letras[i-1][j-1] == 'M' && matriz_letras[i-2][j-2] == 'A' &&
			matriz_letras[i-3][j-3] == 'S'){
				contador_XMAS++;
			}

			// Diagonal abajo derecha
			if(i + 3 < matriz_letras.size() && j + 3 < matriz_letras.size() && matriz_letras[i][j] == 'X' && matriz_letras[i+1][j+1] == 'M' && matriz_letras[i+2][j+2] == 'A' &&
			matriz_letras[i+3][j+3] == 'S'){
				contador_XMAS++;
			}

			// Diagonal abajo izquierda
			if(i + 3 < matriz_letras.size() && j - 3 >= 0 && matriz_letras[i][j] == 'X' && matriz_letras[i+1][j-1] == 'M' && matriz_letras[i+2][j-2] == 'A' &&
			matriz_letras[i+3][j-3] == 'S'){
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
