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

    std::ifstream archivo("ejemplo.txt");
    if(!archivo.is_open()){
    	throw std::runtime_error("No se puede abrir el fichero");
	}

    // En este bucle 
    while(getline(archivo, linea)){
        // Extraer los valores numéricos de un string (lineas del fichero) uno por uno
        std::istringstream ss(linea);
        int numero1, numero2;
        ss >> numero1;
        n1.push_back(numero1);
        
        ss >> numero2;
        n2.push_back(numero2);
    }

    for(int i = 0; i < n1.size() && i < n2.size(); i++){
        std::cout << n1[i];
        std::cout << "    ";
        std::cout << n2[i] << std::endl;
    }

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