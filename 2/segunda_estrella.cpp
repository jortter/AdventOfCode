#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <cmath>
#include <algorithm>

// Cuando el código se está complicando, es mejor organizarlo en funciones SÍ O SÍ

void imprimirVector(std::vector<int>& A){
	for(int i = 0; i < A.size(); i++){
		std::cout << A[i];
		std::cout << " ";

	}
	std::cout << std::endl;
}

bool isSafe(std::vector<int>& A){
	for(int i = 0; i < A.size()-1; i++){
		int diferencia = std::abs(A[i]-A[i+1]);
		// Es mejor separar las dos condiciones de validez que juntarlo todo en un mismo if y que éste sea casi ilegible
		if(diferencia < 1 || diferencia > 3){
			return false;
		}
	}
	// El intervalo begin-end es para saber si es creciente, y el intervalo rbegin-rend es para saber si es decreciente
	return std::is_sorted(A.begin(), A.end()) || std::is_sorted(A.rbegin(), A.rend());
}

void numReportsSafe(){

	std::vector<int> report;
	std::string linea;
	int report_safe = 0;

	std::ifstream archivo("input.txt");
	if(!archivo.is_open()){
		throw std::runtime_error("No se ha podido abrir el fichero");
	}

	while(getline(archivo, linea)){
		std::istringstream ss(linea);
		int numero;
		// Reiniciamos el vector para cada línea procesada para que así el push_back() no me añada los nuevos elementos al final del vector, formándome al final un vector
		// con todos los elementos
		report.clear();
		while(ss >> numero){
			report.push_back(numero);	
		}
		imprimirVector(report);

		// A partir de aquí creamos el algoritmo para saber si el report es safe 
		// Para ello, los niveles (elementos) del report deben estar ordenados de forma creciente O decreciente, Y 2 niveles adyacentes cualesquiera difieren en al menos
		// 1 Y como máximo en 3

		// Solo reseteamos la variable booleana y NO el contador porque sino estaríamos incrementando en uno éste y poniendolo a 0 en cada itercación del bucle while
		// Ahora lo que hay que hacer es crearme una copia del vector report (como std::vector<int> report2 = report) e ir eliminando los niveles en la copia
		// viendo cuál de las eliminaciones hace que mi report sea safe.
		if(isSafe(report)){
			report_safe++;
			std::cout << "Report safe" << std::endl;
			// Si el report orginal es safe, avanzamos a la siguiente iteración del bucle usando continue
			continue;
		}
			
		bool es_valido = false;
		// Vamos eliminando uno a uno de forma secuencial los elementos del vector
		for(int j = 0; j < report.size(); j++){	
			std::vector<int> report_copia = report;		
			report_copia.erase(report_copia.begin()+j);
			// Nos imprimimos cada vez que se elimina un componente del vector report_copia (en sus sucesivas copias se va eliminando uno a uno sus componentes)
			imprimirVector(report_copia);
			if(isSafe(report_copia)){
				es_valido = true;
				// En cuanto una de las copias sea válida, nos salimos del bucle porque hemos encontrado el nivel del report a eliminar que hace que éste pase a ser safe.
				break;
			}
					
		}		
		if(es_valido == true){
			report_safe++;
			// Imprimimos las líneas que son válidas
			std::cout << linea << std::endl;
			std::cout << "Report safe" << std::endl;
		} else{
			std::cout << "Report unsafe" << std::endl;
		}

	}
	
	std::cout << std::endl;
	std::cout << report_safe << std::endl;
}

int main(){
	try{
		numReportsSafe();
	} catch(const std::exception& e){
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return 0;
}

