#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>

// Problema muy candidato a aplicar Programación Dinámica
void imprimirMatriz(std::vector<std::vector<char>>& A){
	for(int i = 0; i < A.size(); i++){
		for(int j = 0; j < A.size(); j++){
			std::cout << A[i][j];
		}

		std::cout << std::endl;
	}
}

enum Direccion{
	ARRIBA,
	ABAJO,
	IZQUIERDA,
	DERECHA
};

void rutaGuardia(){
	// El guardia comienza mirando hacia arriba tal que ^
	Direccion direccion;
	std::string linea;
	int contador_ruta_guardia = 0;

	// Una matriz es un vector de vectores
	std::vector<std::vector<char>> matriz_ruta;
	std::pair<int, int> posicion_guardia; 

	std::ifstream archivo("ejemplo.txt");
	if(!archivo.is_open()){
		throw std::runtime_error("No se ha podido abrir el fichero");
	}

	while(getline(archivo, linea)){
		std::vector<char>fila(linea.begin(), linea.end());
		matriz_ruta.push_back(fila);
	}

	imprimirMatriz(matriz_ruta);

	// Mientras recorremos la matriz debemos identificar los obstáculos (definidos por el carácter '#')
	for(int i = 0; i < matriz_ruta.size(); i++){
		for(int j = 0; j < matriz_ruta.size(); j++){
			if(matriz_ruta[i][j] == '^'){	
				direccion = ARRIBA;
				// Nos guardamos la posición inicial del guardia porque estaremos trabajando con ella a partir de este momento
				posicion_guardia = {i, j};
				std::cout << "Posición inicial del guardia: " << "(" << posicion_guardia.first << "," << posicion_guardia.second << ")" << std::endl;			
				while(posicion_guardia.first > 0 && posicion_guardia.first < matriz_ruta.size()-1 && posicion_guardia.second > 0 && 
				posicion_guardia.second < matriz_ruta.size()-1){
					// Dentro del bucle vemos si el guardia ha llegado a los bordes de la matriz
					if(posicion_guardia.first == 0 || posicion_guardia.first == matriz_ruta.size()-1 || 
					posicion_guardia.second == 0 || posicion_guardia.second == matriz_ruta.size()-1){
						// Nos salimos del bucle si llegamos a los bordes
						break;
					}

					// Una vez ha chocado contra el obstáculo, tenemos que cambiar la dirección del guardia girando 90º hacia la derecha y avanzar en esa dirección -> arriba
					// (i.e. retrasar solo en posicion_guardia.first)
					if(direccion == ARRIBA) 
					{	
						if(matriz_ruta[posicion_guardia.first-1][posicion_guardia.second] != '#'){
							posicion_guardia.first--;
							std::cout << posicion_guardia.first << std::endl;
							contador_ruta_guardia ++;
							matriz_ruta[posicion_guardia.first][posicion_guardia.second] = 'X';
							std::cout << matriz_ruta[posicion_guardia.first][posicion_guardia.second] << std::endl;
						}
						// Si chocamos contra un objeto yendo hacia arriba, cambiamos la dirección y vamos hacia la derecha
						else{
							direccion = DERECHA;
						}
					}
					std::cout << "Posición actual del guardia tras moverse hacia arriba: " << "(" << posicion_guardia.first << "," << posicion_guardia.second << ")" << std::endl;
					// Una vez ha chocado contra el obstáculo, tenemos que cambiar la dirección del guardia girando 90º hacia la derecha y avanzar en esa dirección -> derecha
					// (i.e. avanzar solo en posicion_guardia.second)
					if(direccion == DERECHA && matriz_ruta[posicion_guardia.first][posicion_guardia.second+1] != '#')
					{
						posicion_guardia.second++;
						std::cout << posicion_guardia.second << std::endl;
						contador_ruta_guardia ++;
						matriz_ruta[posicion_guardia.first][posicion_guardia.second] = 'X';
						std::cout << matriz_ruta[posicion_guardia.first][posicion_guardia.second] << std::endl;
					} else{
						direccion = ABAJO;
					}
					std::cout << "Posición actual del guardia tras moverse hacia arriba: " << "(" << posicion_guardia.first << "," << posicion_guardia.second << ")" << std::endl;
					// Una vez ha chocado contra el obstáculo, tenemos que cambiar la dirección del guardia girando 90º hacia la derecha y avanzar en esa dirección -> abajo
					// (i.e. avanzar solo en posicion_guardia.first)
					if(direccion == ABAJO && matriz_ruta[posicion_guardia.first+1][posicion_guardia.second] != '#')
					{
						posicion_guardia.first++;
						std::cout << posicion_guardia.first << std::endl;
						contador_ruta_guardia ++;
						matriz_ruta[posicion_guardia.first][posicion_guardia.second] = 'X';
						std::cout << matriz_ruta[posicion_guardia.first][posicion_guardia.second] << std::endl;
					}
					else{
						direccion = IZQUIERDA;
					}
					std::cout << "Posición actual del guardia tras moverse hacia arriba: " << "(" << posicion_guardia.first << "," << posicion_guardia.second << ")" << std::endl;
					// Una vez ha chocado contra el obstáculo, tenemos que cambiar la dirección del guardia girando 90º hacia la derecha y avanzar en esa dirección -> izquierda
					// (i.e. retrasar solo en posicion_guardia.second)
					if(direccion == IZQUIERDA && matriz_ruta[posicion_guardia.first][posicion_guardia.second-1] != '#')
					{
						posicion_guardia.second--;
						std::cout << posicion_guardia.second << std::endl;
						contador_ruta_guardia ++;
						matriz_ruta[posicion_guardia.first][posicion_guardia.second] = 'X';
						std::cout << matriz_ruta[posicion_guardia.first][posicion_guardia.second] << std::endl;
					} else{
						direccion = ARRIBA;
					}
					std::cout << "Posición actual del guardia tras moverse hacia arriba: " << "(" << posicion_guardia.first << "," << posicion_guardia.second << ")" << std::endl;

				}
			}
				
		}
	}
	std::cout << std::endl;
	std::cout << "Número de posiciones a las que se ha movido el guardia: " << contador_ruta_guardia << std::endl;
	archivo.close();
}

int main(){
	try{
		rutaGuardia();
	} catch(const std::exception& e){
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return 0;
}
