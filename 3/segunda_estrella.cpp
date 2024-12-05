#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <regex>

void identificar_mul(){
	std::string linea;
	int total = 0;
	bool enable = true;

	std::ifstream archivo("input.txt");
	if(!archivo.is_open()){
		throw std::runtime_error("No se ha podido abrir el fichero");
	}

	// Para facilitarnos la vida, usaremos expresiones regulares (regex) en este problema. Esto sirve para buscar elementos partuiculares dentro de un gran texto	
	// R crea una cadena "cruda", lo cual evita problemas con el uso de \ en regex
	std::regex patron(R"(mul\((\d{1,3}),(\d{1,3})\)|do\(\)|don't\(\))");
	// Usamos smatch para almacenar los resultados de coincidencias (solo sirve para strings(como linea en nuestro caso))
	std::smatch coincidencias;
	
	while(getline(archivo, linea)){
		// const_iterator nos permite recorrer un vector o un string sin permitir modificar sus elementos durante el recorrido
		std::string::const_iterator inicio = linea.cbegin();
		std::string::const_iterator fin = linea.cend();
		std::cout << "Coincidencias encontradas: " << std::endl;
		// regex_search() busca un patrón dentro de una cadena
		while(std::regex_search(inicio, fin, coincidencias, patron)){
			// coincidencias[0] siempre contiene el texto completo de la coincidencia: si coincidencias[0] es mul(11,8) -> coincidencias[1] = "11" y coincidencias[2] = "8"
			// Sin embargo si coincidencias[0] es do() o don't() -> coincidencias[1] = "" y coincidencias[2] = "", luego no puedo usar stoi(coincidencias[1 ni 2])
			std::cout << "Encontrado: " << coincidencias[0] << std::endl;
			// Avanza el inicio para buscar más coincidencias -> Es un iterador que apunta al texto después de la coincidencia actual	
			if(coincidencias[0].str().find("mul") == 0 && enable == true){
				// coincidencias[1] = X y coincidencias[2] = Y
				int x = std::stoi(coincidencias[1]);
				int y = std::stoi(coincidencias[2]);
				int resultado = x * y;
				total += resultado;
			}
			else if((coincidencias[0].str().find("do()") == 0) && enable == false){
				enable = true;
			}
			else if((coincidencias[0].str().find("don't()") == 0) && enable == true){
				enable = false;
			}

			inicio = coincidencias.suffix().first;
		}
		
	}

	std::cout << total << std::endl;
	archivo.close();
}

int main(){
	try{
		identificar_mul();
	} catch(const std::exception& e){
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return 0;
}

