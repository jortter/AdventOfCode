#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
	
void numReportsSafe(){
	
	std::string linea;
	std::ifstream archivo("ejemplo.txt");
	if(!archivo.is_open()){
		throw std::runtime_error("No se ha podido abrir el fichero");
	}

	while(getline(archivo, linea)){
		
	}

}

int main(){
	try{
		numReportsSafe();
	} catch(const std::exception& e){
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return 0;
}
