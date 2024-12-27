#include <iostream>
#include <vector>
#include <queue>
#include <stdexcept>
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>

// En este problema hay que aplicar	ORDEN TOPOLÓGICO 100%: si un nodo (vi) tiene un enlace a otro nodo (vj), debe aperecer antes en el orden vi que vj.
// REQUISITOS: el grafo ha de ser acíclico (no se puede repetir un elemento en un camino) y debe de haber al menos un nodo con grado de entrada 0
// Además, el nodo con grado de salida 0 debe ser el último del orden topológico

// En C++, una lista enlazada es como un vector de vectores, lo cual a su vez es como una matriz
class Grafo{
	private:
		// Atributos privados
		std::vector<int> grado_entrada;						// Grado de entrada de cada nodo almacenados en un vector
		std::vector<std::vector<int>> lista_enlazada;		// Lista enlazada que almacena los vecinos de cada nodo
		int num_nodos;										// Nº total de nodos
	public:
		// Métodos públicos

		// Constructor para inicializar el grafo
		// Por ejemplo, inicializamos el vector grado_entrada con n nodos, todos ellos con el valor 0, para que al menos haya un nodo con grado de entrada 0
		// Inicializamos la lista enlazada a los nodos iniciales (n)
		Grafo(int nodos) : grado_entrada(nodos, 0),  lista_enlazada(nodos), num_nodos(nodos) {}
		
		// Método para agregar un enlace(origen, destino)
		void anyadirEnlace(int origen, int destino){
			// Agregar destino como vecino de origen, y luego incrementar el grado de entrada de destino (pues es un nuevo vecino de otro nodo [origen])
			lista_enlazada[origen].push_back(destino);
			grado_entrada[destino]++;
		}

		// Método para calcular el orden topológico (funcion topSort)
		std::vector<int> ordenTopologico(){
			// Cola en la que almacenaremos los nodos con grado de entrada 0
			std::queue<int> q;
			// El resultado del orden topológico lo almacenaremos en un vector y será lo que devuelva la función
			std::vector<int> orden_topologico;

			// 1º Recorremos los nodos y si éstos tienen grado de entrada 0, los metememos en la cola q
			for(int i = 0; i < num_nodos; i++){
				if(grado_entrada[i] == 0){
					q.push(i);	
				}
			}
			// Ahora debemos procesar la cola q mientras que ésta NO esté vacía
			while(!q.empty()){
				// 2º Eliminamos el nodo actual que tenga grado de entrada a 0 y lo almacenamos en el vector resultado (orden_topologico)
				int v = q.front();
				q.pop();	
				orden_topologico.push_back(v);

				// Al eliminar un nodo del grafo, tenemos que reducir en 1 el grado de entrada de sus vecinos (pues nos cargamos la flecha que unía al vecino con el nodo eliminado)
				// Como los vecinos del nodo están almacenados en lista_enlazada, debemos recorrer dicha lista enlazada (que en verdad es una matriz)
				for(int i = 0; i < lista_enlazada[v].size(); i++){
					// El vecino es un nodo, luego es un elemento de la matriz que contiene a los nodos que están en la cola
					int vecino = lista_enlazada[v][i];	
					grado_entrada[vecino]--;
					// Mientras recorremos la lista, si encontramos un vecino que tenga grado de entrada 0 lo añadimos a la cola q
					if(grado_entrada[vecino] == 0){
						q.push(vecino);
					}
				}
			}	
			
			// Finalmente, lanzamos una excepción si todos los nodos NO fueron provesados
    		if(orden_topologico.size() != num_nodos){
        		throw std::runtime_error("El grafo es acíclico, luego NO se puede aplicar el orden topológico");
    		}
			
			// Acabamos devolviendo el vector solucion del orden topológico
			return orden_topologico;

		}

};

// Le pasamos a la función las filas de la matriz de updates y el vector de orden topologico (q)
bool updateValido(std::vector<int>& posicion_orden_topologico, std::vector<int>& update){
	// Si la posición de rules[i].first es < que la posición de rules[i].second en un update, entonces ese update es válido porque cumpliría todas las reglas
	// Debemos recorrer la fila del update y ver si la posición del elemento actual de q es < que la posición del elemento
	// siguiente de q, así hasta comprobar toda la fila del update
	for(int i = 0; i < update.size(); i++){
		for(int j = i+1; j < update.size(); j++){
			if(posicion_orden_topologico[update[i]] > posicion_orden_topologico[update[j]]){
				return false;
			}
		}
	}
	// Si tras recorrer el update vemos que se cumplen todas las reglas, entonces el update es válido 
	return true;
}

void correctUpdate(){
	std::string linea;
	int total = 0;
	bool leyendo_rules = true;
	// Nos creamos un vector de pares X, Y llamado rules
	std::vector<std::pair<int, int>> rules;
	// Nos creamos un vector de vectores (una matriz) para los updates. Hacemos esto y NO usamos un vector normal porque cada update tiene un tamaño diferente
	std::vector<std::vector<int>> updates;

	std::ifstream archivo("ejemplo.txt");
	if(!archivo.is_open()){
		throw std::runtime_error("No se ha podido abrir el fichero");
	}

	while(getline(archivo, linea)){
		// Si encontramos una línea vacía, ya no estamos leyendo rules sino orden, luego pasamos a la siguiente iteración del while con continue
		if(linea.empty()){
			leyendo_rules = false;
			continue;
		}

		if(leyendo_rules == true){
			std::istringstream ss(linea);
			int x, y;
			ss >> x;
			ss.ignore(1, '|'); 		// Ignora el delimitador '|'
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

	// Nos creamos ahora una instancia de la clase Grafo
	// Para ello, la cantidad de nodos del grafo debe ser suficientemente grande para incluir todos los elementos que aparecen en rules y en updates
	int max_nodos = 0;
	for(int i = 0; i < rules.size(); i++){
		int origen = rules[i].first;
		int destino = rules[i].second;
		std::cout << "Rule: " << origen << '|' << destino << std::endl;
		max_nodos = std::max(max_nodos, std::max(origen, destino));
	}

	// Creamos la instancia del grafo con la cantidad correcta de nodos (le ponemos un +1 porque los nodos comienzan en 0)
	Grafo grafo(max_nodos + 1);

	// 1º Añadir las rules como enlaces al grafo
	for(int i = 0; i < rules.size(); i++){
		int origen = rules[i].first;
		int destino = rules[i].second;
		grafo.anyadirEnlace(origen, destino);
	}

	// 2º Comprobar si un update es válido -> Debe cumplir el orden topológico -> Hacemos las comprobaciones necesarias en una función aparte mejor (seguimos la logica de 
	// fuerza bruta)
	// Para ello, necesito saber las posiciones de cada elemento que hay en el vector del orden topoligico
	std::vector<int> topSort = grafo.ordenTopologico();
	
	// Tenemos que ver cuando llamar a updateValido() y, si se cumple la función (devuelve true), calcular el eemento del medio de topSort(q)
	// Tenemos que pasarle a la función la posicion del vector de ordenTopologico(topSort) para que compare posiciones y no elementos
	std::vector<int> topSortPosicion(topSort.size());
	for(int i = 0; i < topSort.size(); i++){
		topSortPosicion[topSort[i]] = i;
	}

	// Ahora debemos recorrer la matriz de updates y ver y llamar a la funcion para comprobar si éste es válido o no
	// Bucle que recorre las rules para cada update
	for(int i = 0; i < updates.size(); i++){
		if(updateValido(topSortPosicion, updates[i])){
			// Si el update es válido, lo imprimimos por pantalla
			std::cout << "El update: ";
			// Ahora tenemos que obtener el elemento situado en la posición media de los updates correctos
			for(int j = 0; j < updates[i].size(); j++){
				std::cout << updates[i][j];
				if(j != updates[i].size()-1){
					std::cout << ',';
				}
			}
			std::cout << " es válido porque cumple todas las condiciones" << std::endl;
			int pos_medio = updates[i].size() / 2;
			std::cout << updates[i][pos_medio] << std::endl;
			total += updates[i][pos_medio];
		}
		else{
			std::cout << "El update: "; 
			for(int j = 0; j < updates[i].size(); j++){
				std::cout << updates[i][j];
				if(j != updates[i].size()-1){
					std::cout << ',';
				}
			}
			std::cout << " NO es válido porque NO cumple todas las condiciones" << std::endl;
		}
	}
	std::cout << total << std::endl;
}

int main() {   
	try{
		correctUpdate();
	} catch(const std::exception& e){
		std::cerr << "Error: " << e.what() << std::endl;
	}
    return 0;
}


