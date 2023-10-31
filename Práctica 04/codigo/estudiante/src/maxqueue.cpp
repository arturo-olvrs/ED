/**
 * @file maxqueue.cpp
 * @brief  Archivo de implementación del TDA MaxQueue
 * @author Arturo Olivares Martos
 */

#include "maxqueue.h"

template <typename T>
const pair<T,T>& MaxQueue<T>::front() const{
	return s.top();
}

template <typename T>
void MaxQueue<T>::pop(){
	s.pop();
}
template <typename T>
void MaxQueue<T>::push(const T& elem){

	// Copiamos en aux;
	while(!s.empty()){
		aux.push(s.top());
		s.pop();
	}

	s.push(pair<T,T>(elem, elem));

	// Copiamos en s modificando el máximo mientras que sea menor.
	while(!aux.empty() && (aux.top().second < elem)){

		// Añadimos el aux.top() pero con el nuevo máximo (elem)
		s.push(pair<T,T>(aux.top().first, elem));
		aux.pop();
	}

	while(!aux.empty()){
		// El máximo ya no hay que modificarlo,
		s.push(aux.top());
		aux.pop();
	}
}

template <typename T>
int MaxQueue<T>::size() const{
	return s.size();
}

template <typename T>
bool MaxQueue<T>::empty() const{
	return s.empty();
}
