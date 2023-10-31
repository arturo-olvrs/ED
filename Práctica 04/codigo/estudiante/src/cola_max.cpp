/**
 * @file cola_max.cpp
 * @brief Fichero de ejemplo para el uso de la clase MaxQueue.
 *
 * Muestra el uso del TDA MaxQueue con un ejemplo de cola de enteros.
 * Por cada entero recibido como parámetro lo añade a la cola.
 * Por cada punto recibido como parámetro elimina el frente de la cola.
 *
 * Ejemplo de uso:
 * @code{.sh}
 * ./cola_max 1 2 . 3 4 . . .
 * @endcode
 *
 * La salida será:
 * @code{.sh}
 * (1, 2)
 * (2, 4)
 * (3, 4)
 * (4, 4)
 * @endcode
 *
 *
 * @author Arturo Olivares Martos
 */
#include <iostream>
#include "maxqueue.h"

/**
 * @brief Sobrecarga del operador de salida para pares.
 * @tparam T1  Tipo del primer elemento del par.
 * @tparam T2  Tipo del segundo elemento del par.
 * @param os  Flujo de salida.
 * @param p  Par a mostrar.
 * @return  Referencia al flujo de salida.
 */
template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
	os << "(" << p.first << ", " << p.second << ")";
	return os;
}

using namespace std;

int main(int argc, char *argv[]){

    MaxQueue<int> queue;

    for(int i = 1; i < argc; i++){
		if (argv[i][0] == '.'){
			cout << queue.front() << endl;
			queue.pop();
		} else {
			queue.push(atoi(argv[i]));
		}
	}
	return 0;
}
