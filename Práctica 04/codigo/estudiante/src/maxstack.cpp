/**
 * @file maxstack.cpp
 * @brief  Archivo de implementación del TDA MaxStack
 * @author Arturo Olivares Martos
 */

#include "maxstack.h"

template <typename T>
const pair<T,T>& MaxStack<T>::top() const{
	return q.front();
}

template <typename T>
void MaxStack<T>::pop(){
	q.pop();
}

template <typename T>
void MaxStack<T>::push(const T& elem){

	// Obtenemos el máximo anterior
	T pre_max = q.front().second;

	// Copiamos en aux;
	while(!q.empty()){
		aux.push(q.front());
		q.pop();
	}

	T new_max = elem > pre_max ? elem : pre_max;
	q.push(pair<T,T>(elem, new_max));

	// Copiamos en q
	while(!aux.empty()){
		q.push(aux.front());
		aux.pop();
	}
}

template <typename T>
int MaxStack<T>::size() const{
	return q.size();
}

template <typename T>
bool MaxStack<T>::empty() const{
	return q.empty();
}