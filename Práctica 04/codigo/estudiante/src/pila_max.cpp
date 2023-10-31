/**
 * @file pila_max.cpp
 * @brief  Fichero de ejemplo para el uso de la clase MaxStack.
 *
 * Muestra el uso del TDA MaxStack con un ejemplo de pila de enteros.
 * Por cada entero recibido como parámetro lo añade a la pila.
 * Por cada punto recibido como parámetro elimina el tope de la pila.
 *
 * Ejemplo de uso:
 * @code{.sh}
 * ./pila_max 1 2 . 3 4 . . .
 * @endcode
 *
 * La salida será:
 * @code{.sh}
 * (1, 2)
 * (2, 4)
 * (3, 4)
 * (4, 4)
 * @endcode
 */

#include <iostream>
#include "maxstack.h"
#include "maxstack.cpp"

using namespace std;

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
	os << "(" << p.first << ", " << p.second << ")";
	return os;
}

int main(int argc, char *argv[]){

    MaxStack<int> stack;

    for(int i = 1; i < argc; i++){
        if (argv[i][0] == '.'){
            cout << stack.top() << endl;
			stack.pop();
		} else {
			stack.push(atoi(argv[i]));
		}
	}
	return 0;
}