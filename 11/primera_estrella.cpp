#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>

// Vamos a implementar árboles binarios para poder hacer eficiente la matriz de memoria de una puta vez
class Nodo{	
	public:
		// Atributos
		int numero;
		Nodo* left;
		Nodo* right;

		// Métodos
		// Constructor
		Nodo(int n) : numero(n), left(nullptr), right(nullptr){}

		// Métodos para dividir la piedra en 2 y para pasar a digitos un número (necesario para dividir la piedra en 2)
		// Función para pasar pasar el número A[ini] a un vector cuyas componentes son los dígitos que forman el número A[ini] (numero = A[ini])
		std::vector<int> obtenerDigitos(int numero){	
			std::cout << "Numero: " << numero << std::endl;
			std::vector<int> digitos;
			while(numero > 0){
				digitos.insert(digitos.begin(), numero % 10);
				numero /= 10;
			}	
			return digitos;
		}		

		// Esto NO puede ser una función recursiva porque solo queremos que me divida el numero 1 sola vez en dos partes 
		std::pair<int, int> divisionPiedra(){	
			int digitos = numero;
        	std::vector<int> digitosVec = obtenerDigitos(digitos);
        	int m = digitosVec.size() / 2;

        	int izquierda = 0, derecha = 0;
        	for (int i = 0; i < m; ++i) {
            	izquierda = izquierda * 10 + digitosVec[i];
        	}
        	for (int i = m; i < digitosVec.size(); ++i) {
            	derecha = derecha * 10 + digitosVec[i];
        	}

        	return {izquierda, derecha};
    	}
		
};

class BSTree{
	public:
		// Atributos
		Nodo* root;
		
		// Métodos
		// Constructor
		BSTree(int valor_inicial){
			root = new Nodo(valor_inicial);
		}
		
		// Borramos el árbol en memoria en forma de cascada
		void delete_cascade(Nodo* n){
			// Caso base -> Si no hay más nodos que procesar
			if(n == nullptr)
				return;
			// Casos recursivos
			// Antes de liberar el nodo actual n usando delete, primero debemos liberar los subárboles izquierdo y derecho, para que así los nodos descendientes sean
			// liberados antes que el actual
			delete_cascade(n->left);
			delete_cascade(n->right);
			// Liberamos la memoria dinámica del nodo actual usando delete
			delete n;
		}
		// Destructor -> Liberar la memoria que ocupa el arbol en forma de cascada
		~BSTree(){
			delete_cascade(root);
		}
		
		// Método para dividir el nodo en 2
		void dividirNodo(Nodo *nodo){
			auto[izquierda, derecha] = nodo->divisionPiedra();
			nodo->numero = izquierda;
			nodo->left = new Nodo(izquierda);
			nodo->right = new Nodo(derecha);
		}

		// Método para crear el árbol binario con los casos recursivos
		void crearArbol(Nodo* nodo){
			if (nodo == nullptr) {
				return;
			}
			// Si el número tiene un valor par de dígitos, lo dividimos en dos
			std::vector<int> digitos = nodo->obtenerDigitos(nodo->numero);
			if ((digitos.size() % 2) == 0) {
				auto [izquierda, derecha] = nodo->divisionPiedra();
				nodo->left = new Nodo(izquierda);  	// Crea el subárbol izquierdo
				nodo->right = new Nodo(derecha);	// Crea el subárbol derecho
				crearArbol(nodo->left);		// Llamada recursiva para el subárbol izquierdo
				crearArbol(nodo->right);	// Llamada recursiva para el subárbol derecho
			} else if (nodo->numero == 0) {
				// Si es 0, lo reemplazamos por 1
				nodo->numero = 1;
			} else {
				// Si no es divisible ni es 0, multiplicamos por 2024
				nodo->numero *= 2024;
			}

		}


		// Método RECURSIVO que recorre el árbol en postorden para calcular el número de piedras del último pestañeo y evitar recalculos guradandome las ramas de los nodos en una
		// matriz (funcion) de memoria
		int postordenCalculoPiedras(Nodo* nodo, int pestanyeos, int index, std::vector<std::vector<int>>& M, std::vector<std::vector<bool>>& visitados){
			 // Caso base: Si el nodo es nulo, no hacemos nada
			if (nodo == nullptr || pestanyeos < 0) {
				return 0;
			}

			// Si ya hemos visitado este nodo para este número de pestañeos, devolvemos el valor almacenado
			if (visitados[pestanyeos][index]) {
				 std::cout << "Nodo ya visitado: " << nodo->numero 
                  << ", Pestanyeos: " << pestanyeos 
                  << ", idx: " << index
                  << ", Valor almacenado: " << M[pestanyeos][index] 
                  << std::endl;
				return M[pestanyeos][index];
			}
			
			int resultado = 0;
			if(pestanyeos > 0){
				// Primero, recorremos el subárbol izquierdo y derecho (postorden)
				int izquierda = postordenCalculoPiedras(nodo->left, pestanyeos - 1, index*2, M, visitados);
				int derecha = postordenCalculoPiedras(nodo->right, pestanyeos - 1, index*2+1, M, visitados);
				// Calculamos el número de piedras en este nodo para el pestañeo actual
				int resultado = izquierda + derecha + 1;
			} else{
				resultado = 1;
			}
			// Solo almacenamos el resultado para el último pestañeo
			M[pestanyeos][index] = resultado;
			visitados[pestanyeos][index] = true;
			  std::cout << "Nodo: " << nodo->numero
              << ", Resultado calculado: " << resultado
              << ", idx: " << index
              << std::endl;
			

			return resultado;
    }

};

void principal(){

	std::string linea;
	// El arreglo de las piedras lo almacenamos en un vector de enteros
	std::vector<int> piedras;

	std::ifstream archivo("ejemplo.txt");
	if(!archivo.is_open()){
		throw std::runtime_error("No se ha podido abrir el fichero");
	}

	while(getline(archivo, linea)){
		std::istringstream ss(linea);
		int numero;
		piedras.clear();
		while(ss >> numero){
			piedras.push_back(numero);	
		}
		
	}
	archivo.close();

	// Tenemos que llamar a la función recursiva que me de el número de piedras al hacer 25 pestañeos
	int num_blinking = 2;

	// Creación del árbol binario para cada piedra
    std::vector<BSTree*> arboles;
    for (int piedra : piedras) {
        BSTree* arbol = new BSTree(piedra);
    	arbol->crearArbol(arbol->root);
		arboles.push_back(arbol);
	}

	// Mi función de memoria o matriz de memoria será de (num_blinking+1)filas x (piedras.size()+1)columnas y la inicializamos al tamaño del vector de piedras
	std::vector<std::vector<int>> M(num_blinking+1, std::vector<int>(piedras.size()*1024, -1));
	// Me creo una matriz booleana que me indique si he tocado una posición de la matriz de memoria y la inicializo a false
	std::vector<std::vector<bool>> visitados(num_blinking+1, std::vector<bool>(piedras.size()*1024, false));


    // Calculamos el número de piedras al final (en el último pestañeo)
    int numero_piedras_totales = 0;
    for (size_t i = 0; i < arboles.size(); ++i) {
        numero_piedras_totales += arboles[i]->postordenCalculoPiedras(arboles[i]->root, num_blinking, 1, M, visitados);
    }

    std::cout << "Número total de piedras en el último pestañeo: " << numero_piedras_totales << std::endl;

    for (BSTree* arbol : arboles) {
        delete arbol;
   	}
}

int main(){
	try{
		principal();
	} catch(const std::exception& e){
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return 0;
}
