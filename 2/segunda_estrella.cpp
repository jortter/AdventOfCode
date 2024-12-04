#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <cmath>

void imprimirVector(std::vector<int>& A){
	for(int i = 0; i < A.size(); i++){
		std::cout << A[i];
		std::cout << " ";

	}
	std::cout << std::endl;
}
	
void numReportsSafe(){

	std::vector<int> report;
	std::vector<int> report_copia;
	std::string linea;
	int report_safe = 0;
	bool es_valido = true;

	std::ifstream archivo("ejemplo.txt");
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
		es_valido = true;
		// Ahora lo que hay que hacer es crearme una copia del vector report (como std::vector<int> report2 = report) e ir eliminando los niveles en la copia
		// viendo cuál de las eliminaciones hace que mi report sea safe.
		for(int i = 0; i < report.size()-1; i++){
			report_copia = report;
			for(int j = 0; j < report_copia.size()-1; j++){
				report_copia.erase(report_copia.begin(), report_copia.end());
				// Tengo que comparar si estoy subiendo en mi posicion actual con que si ya he subido antes en el vector
				if(!((((report_copia[1] > report_copia[0]) && (report_copia[j+1] > report_copia[j])) || ((report_copia[1] < report_copia[0]) &&
				(report_copia[j+1] < report_copia[j])))&&(((std::abs(report_copia[j]-report_copia[j+1])) >= 1) && ((std::abs(report_copia[j]-report_copia[j+1])) <= 3)))){
				// Debemos incrementar el contador por cada report válido, no por cada par válido
					es_valido = false;
				}

			}
					
		}
		if(es_valido == true){
			report_safe++;
			// Imprimimos las líneas que son válidas
			std::cout << linea << std::endl;
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

