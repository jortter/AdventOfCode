#include <iostream>
#include <vector>
#include <queue>
#include <stdexcept>
#include <sstream>
#include <fstream>

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
		// Por ejemplo, inicializamos el vector grado_entrada con n nodos, todos ellos con el valor 0, ya que para que al menos haya un nodo con grado de entrada 0
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
			// Finalmente, lanzamos excepción si el grafo es acíclico, i.e. si el tamaño de orden_topologico es distinto de el numero de nodos
			if(orden_topologico.size() != num_nodos){
				throw std::runtime_error("El grafo es cíclico, luego NO se puede calcular el orden topológico");
			}
			// Acabamos devolviendo el vector solucion del orden topológico
			return orden_topologico;

		}

		// Podemos añadir una función a la clase que nos imprima el grafo
		void printGrafo(){
			for(int i = 0 ; i < num_nodos; i++){
				std::cout << "Nodo " << i << "-> ";
				for(int j = 0; j < lista_enlazada[i].size(); j++){
					int vecino = lista_enlazada[i][j];
					std::cout << vecino << " ";
				}
				std::cout << std::endl;
			}
		}

};

int main() {
    try {
        // Crear un grafo con 6 nodos (numerados de 0 a 5)
        Grafo g(6);

        // Agregar enlaces: un enlace es un par (u, v) que pertenece a un conjunto de nodos V
        g.anyadirEnlace(5, 2);
        g.anyadirEnlace(5, 0);
        g.anyadirEnlace(4, 0);
        g.anyadirEnlace(4, 1);
        g.anyadirEnlace(2, 3);
        g.anyadirEnlace(3, 1);

        // Imprimir el grafo
        std::cout << "El grafo es: " << std::endl;
        g.printGrafo();
        std::cout << std::endl;

        // Calcular el orden topológico
        std::vector<int> topOrder = g.ordenTopologico();
        std::cout << "El orden topológico es: ";
        for (int i = 0; i < topOrder.size(); i++) {
            std::cout << topOrder[i] << " ";
        }
        std::cout << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

