/**
 * @file maxqueue.h
 * @brief  Archivo de especificación del TDA MaxQueue
 * @author Arturo Olivares Martos
 */

#ifndef MAXQUEUE_H
#define MAXQUEUE_H

#include <stack>
#include <utility>

using namespace std;

/**
 * @brief TDA MaxQueue
 *
 * Una instancia @e c del tipo de datos abstracto @c MaxQueue
 * es una estructura que almacena una cola de elementos junto con el máximo.
 */
template <typename T>
class MaxQueue {
private:
	/**
	 * @brief Pila empleada para almacenar la cola.
	 *
	 * El frente de la cola es el tope de la pila.
	 */
	stack<pair<T,T>> s;

	/**
	 * @brief Pila auxiliar para gestionar las inserciones.
	 */
	stack<pair<T,T>> aux;

public:

	/**
	 * @brief Método que consulta el frente de la cola.
	 * @return El frente de la cola.
	 */
	const pair<T,T>& front() const;

	/**
	 * @brief Elimina el frente de la cola.
	 */
	void pop();

	/**
	 * @brief Método que añade en el final de la cola.
	 * @param elem Elemento a añadir.
	 */
	void push(const T& elem);

	/**
	 * @brief Método que calcula el número de elementos de una cola.
	 * @return El número de elementos de la cola.
	 */
	int size() const;

	/**
	 * @brief Informa sobre si la cola está vacía o no.
	 * @retval true Si la cola está vacía.
	 * @retval false Si hay algún elemento en la cola.
	 */
	bool empty() const;
};

#include "maxqueue.cpp"
#endif // MAXQUEUE_H