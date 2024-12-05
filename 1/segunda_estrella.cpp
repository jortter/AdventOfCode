#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>

void distVect(){
    // Variables y estructuras de datos a usar
    std::vector<int> n1, n2;
    std::string linea;
    int total = 0;
	bool repetido = false;
	int contador = 0;

    std::ifstream archivo("ejemplo.txt");
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

    // Mostrar los vectores
    for(int i = 0; i < n1.size() && i < n2.size(); i++){
        std::cout << n1[i];
        std::cout << "    ";
        std::cout << n2[i] << std::endl;
    }
    std::cout << std::endl;
    // Buscar cuántas veces se repite un elemento de la lista izquierda en la lista derecha, y multiplicar dicho numero por su numero de repeticiones
    for(int i = 0; i < n1.size(); i++){
		repetido = false;
		contador = 0;
		// Esta parte se puede resolver usando una tabla hash, en la cual mi key seria cada numero del vector n1 y mi value sería el contador asociado a dicho numero de n1
		// Comprobar si el elemento de n1 en el que estamos ahora es repetido (si lo es nos salimos del bucle)
		for(int k = 0; k < i; k++){
			if(n1[i] == n1[k] && repetido == false){
				repetido = true;
				break;
			}
		}	
		for(int j = 0; j < n2.size(); j++){
			if(n1[i] == n2[j]){
				contador++;
			}	
		}    
		
		std::cout << "Numero: " << n1[i] << " con repeticiones en n2: " << contador << std::endl;
		total += n1[i] * contador;

	}
      
	std::cout << total << std::endl; 
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
