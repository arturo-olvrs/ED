/**
 * @file maxstack.h
 * @brief  Archivo de especificación del TDA MaxStack
 * @author Arturo Olivares Martos
 */

#ifndef MAXSTACK_H
#define MAXSTACK_H

#include <queue>
#include <utility>
using namespace std;

/**
 * @brief TDA MaxStack
 *
 * Una instancia @e c del tipo de datos abstracto @c MaxStack
 * es una estructura que almacena una pila de elementos junto con el máximo.
 */
template <typename T>
class MaxStack {
private:
	/**
	 * @brief Cola empleada para almacenar la pila.
	 *
	 * El tope de la pila es el frente de la cola.
	 */
	queue<pair<T,T>> q;

	/**
	 * @brief Cola auxiliar para gestionar las inserciones.
	 */
	queue<pair<T,T>> aux;
public:

	/**
	 * @brief Método que consulta el tope de la pila.
	 * @return El tope de la pila.
	 */
	const pair<T,T>& top() const;


	/**
	 * @brief Elimina el tope de la pila.
	 */
	void pop();

	/**
	 * @brief Método que añade en el frente de la pila.
	 * @param elem Elemento a añadir.
	 */
	void push(const T& elem);

	/**
	 * @brief Método que calcula el número de elementos de una pila.
	 * @return El número de elementos de la pila.
	 */
	int size() const;


	/**
	 * @brief Método que comprueba si la pila está vacía.
	 * @return @retval true si la pila está vacía.
	 * @return @retval false si la pila no está vacía.
	 */
	bool empty() const;

};


#endif // MAXSTACK_H