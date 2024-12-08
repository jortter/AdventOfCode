#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <sstream>

void imprimirRules(std::vector<std::pair<int, int>>& A){
	if(A.empty()) return;
	for(int i = 0; i < A.size(); i++){
		// A[i].first nos da el primer elemento del par, que es X. A[i].second nos da el segundo elemento del par, que es Y
		// Con este cout conseguimos que cada par se imprima de la forma X|Y
		std::cout << A[i].first << '|' << A[i].second << std::endl;	
	}
	std::cout << std::endl;
}

void imprimirUpdates(std::vector<std::vector<int>>& A){
	if(A.empty()) return;
	for(int i = 0; i < A.size(); i++){
		// Iteramos hasta A[i].size() porque cada subvector update tiene un tamaño diferente (A[i])
		for(int j = 0; j < A[i].size(); j++){
			std::cout << A[i][j];
			if(j != A[i].size()-1){
				std::cout << ',';
			}
		}
		// Cada subvector de updates debe imprimirse en una linea separada
		std::cout << std::endl;
	}
}

void correctUpdate(){
	std::string linea;
	int contador = 0;
	int total = 0;
	bool leyendo_rules = true;
	// Nos creamos un vector de pares X, Y llamado rules
	std::vector<std::pair<int, int>> rules;
	// Nos creamos un vector de vectores (una matriz) para los updates. Hacemos esto y NO usamos un vector normal porque cada update tiene un tamaño diferente
	std::vector<std::vector<int>> updates;

	std::ifstream archivo("input.txt");
	if(!archivo.is_open()){
		throw std::runtime_error("No se ha podido abrir el fichero");
	}

	while(getline(archivo, linea)){
		if(linea.empty()){
			leyendo_rules = false;
			//std::cout << std::endl;
			continue;
		}
		
		if(leyendo_rules == true){
			std::istringstream ss(linea);
			int x, y;
			ss >> x;
			ss.ignore(1, '|'); // Ignora el delimitador '|'
			ss >> y;
			rules.push_back({x, y});	
		}
		else{
			std::istringstream ss(linea);
			// Nos creamos un vector que almacene cada linea de updates en el que vamos a ir metiendo cada numero dentro de la linea
			std::vector<int> update;
			int num;
			while(ss >> num){
				update.push_back(num);
				// Si miramos una coma, la ignoramos
				if(ss.peek() == ','){	
					ss.ignore();
				} 
			}
			// Una vez metidos todos los numeros de la linea, metemos la linea en la matriz updates
			updates.push_back(update);
		}
	}

	imprimirRules(rules);
	imprimirUpdates(updates);
	std::cout << std::endl;
		
	// Hay que identificar qué updates están en el orden correcto y cuales en orden incorrecto
	// Para ello, para cada update se han de recorrer todas las rules. Tras esto, si cada numero de un update cumple las rules en las qué este número sale
	// el update será correcto, sino será incorrecto
	// Primero, lo más fácil sería identificar las rules en las que aparece cada elemento del update
	for(int j = 0; j < updates.size(); j++){	// Bucle que recorre las rules para cada update (por eso lo ponemos antes que el bucle de los updates)
		bool update_valido = true;
		for(int i = 0; i < rules.size(); i++){	// Bucle que recorre los updates (filas de la matriz)
			// Dentro del bucle que recorre los updates inicializamos dos variables que almacenarán las posiciones de rules[i].first y rules[i].second
			// Como 0 es una posible posición dentro de un vector, mejor las inicializamos a -1 que es una posición inalcanzable
			// Inicializamos estas variables dentro del bucle de los updates para que se reinicien cada vez que pasen a un nuevo update
			int pos_x = -1;
		 	int pos_y = -1;
			for(int k = 0; k < updates[j].size(); k++){	// Bucle que recorre los elementos de cada update (columnas de la matriz)
				// Debemos ver si X e Y aparecen en un update (rules[i].first y rules[i].second)
				// Si hayamos X en un update y la posicion de rules[i].first en dicho update sigue siendo -1
				if(rules[i].first == updates[j][k] && pos_x == -1){	
					pos_x = k;
				}
				if(rules[i].second == updates[j][k] && pos_y == -1){
					pos_y = k;
				}
			
			}
			// Si la posición de rules[i].first es < que la posición de rules[i].second en un update(i.e. operamos en el bucle que recorre los updates),
			// entonces ese update es válido porque cumpliría todas las reglas
			// Primero hay que ver si las posiciones han sido encontradas
			if(pos_x != -1 && pos_y != -1){
				// Si la posicion de X es < que la posicion de Y en el update, técnicamente el update es correcto. Sin embargo, esto quiere decir que con que 
				// solo se cumpla una de las reglas, el update es correcto, lo cual es falso: se deben cumplir todas las reglas para que el update sea correcto
				if(pos_x >= pos_y){	
					std::cout << "El update: " << j << " NO es válido porque " << rules[i].first << " va después que " << rules[i].second <<  std::endl;	
					update_valido = false;
					break;
				}
						
			 }	
		}
		if(update_valido == true){
			std::cout << "El update: ";
			// Ahora tenemos que obtener el elemento situado en la posición media de los updates correctos
			for(int m = 0; m < updates[j].size(); m++){	
				std::cout << updates[j][m];
				if(m != updates[j].size()-1){
					std::cout << ',';
				}	
			}
			std::cout << " es válido porque cumple todas las condiciones" << std::endl;
			int pos_medio = updates[j].size() / 2;
			std::cout << updates[j][pos_medio] << std::endl;
			total += updates[j][pos_medio];

		}
	}
	
	
	std::cout << total << std::endl;
	archivo.close();

}


int main(){
	try{
		correctUpdate();
	} catch(const std::exception& e){
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return 0;
}
