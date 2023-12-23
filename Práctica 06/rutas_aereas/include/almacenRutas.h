/**
 * @file almacenRutas.h
 * @brief Fichero cabecera del TDA AlmacenRutas
 *
 *
 * @author Arturo Olivares Martos
 * @author Daniel Hidalgo Chica
 */

#ifndef PRACTICAFINAL_ALMACENRUTAS_H
#define PRACTICAFINAL_ALMACENRUTAS_H

#include <map>
#include <string>
#include <iostream>
#include "ruta.h"

using namespace std;

/**
 * @brief TDA AlmacenRutas
 *
 * Una instancia del tipo de datos abstracto @c AlmacenRutas es un objeto
 * que representa un conjunto de rutas aéreas. Este conjunto
 * es un mapa que contiene como clave el código de la ruta
 * y como valor la ruta.
 */
class AlmacenRutas {
private:
	/**
	 * @brief Mapa que contiene las rutas
	 *
	 * El mapa contiene como clave el código de la ruta y como valor la ruta
	 */
	map<string, Ruta> rutas;

public:

	/**
	 * @brief Constructor por defecto de la clase
	 */
	AlmacenRutas(){}

	/**
	 * @brief Constructor de la clase
	 * @param rutas Mapa que contiene las rutas
	 */
	AlmacenRutas(const map<string, Ruta> &rutas);

	/**
	 * @brief Método que devuelve la ruta correspondiente a un código
	 * @param codigo Código de la ruta
	 * @return Ruta correspondiente al código
	 * @pre existeRuta(codigo) == true
	 */
	const Ruta& getRuta(string codigo);

	/**
	 * @brief Método que comprueba si existe una ruta en el almacén
	 * @param codigo  Código de la ruta
	 * @retval true Si existe
	 * @retval false Si no existe
	 */
	bool existeRuta(string codigo);

	/**
	 * @brief Método que añade una ruta al almacén
	 * @param ruta Ruta a añadir
	 */
	void insertarRuta(const Ruta &ruta);

	/**
	 * @brief Método que elimina una ruta del almacén
	 * @param codigo Código de la ruta a eliminar
	 */
	void eliminarRuta(string codigo);

	/**
	 * @brief Método que devuelve el número de rutas del almacén
	 * @return Número de rutas del almacén
	 */
	int getNumRutas() const;

	class const_iterator;

	/**
	 * @brief Clase iterador de la clase AlmacenRutas
	 */
	 class iterator {
	 private:
		 map<string, Ruta>::iterator it;
	 public:
		 /**
		  * @brief Constructor por defecto de la clase
		  */
		 iterator() {}

		 /**
		  * @brief Constructor de la clase
		  * @param it Iterador de la clase map
		  */
		 iterator(map<string, Ruta>::iterator it) : it(it) {}

		 /**
		  * @brief Sobrecarga del operador de incremento
		  * @return Iterador incrementado
		  */
		 iterator &operator++() {
			 ++it;
			 return *this;
		 }

		 /**
		  * @brief Sobrecarga del operador de decremento
		  * @return Iterador decrementado
		  */
		 iterator &operator--() {
			 --it;
			 return *this;
		 }

		 /**
		  * @brief Sobrecarga del operador de acceso
		  * @return Ruta apuntada por el iterador
		  */
		 Ruta &operator*() {
			 return it->second;
		 }

		 /**
		  * @brief Sobrecarga del operador de comparación
		  * @param i Iterador con el que se compara
		  * @return True si son iguales, false en caso contrario
		  */
		 bool operator==(const iterator &i) {
			 return it == i.it;
		 }

		 /**
		  * @brief Sobrecarga del operador de comparación
		  * @param i Iterador con el que se compara
		  * @return True si son distintos, false en caso contrario
		  */
		 bool operator!=(const iterator &i) {
			 return it != i.it;
		 }

		 friend class AlmacenRutas;
		 friend class const_iterator;
	 };

	 /**
	  * @brief Devuelve un iterador al principio del mapa
	  * @return Iterador al principio del mapa
	  */
	 iterator begin() {
		 iterator i;
		 i.it = rutas.begin();
		 return i;
	 }

	 /**
	  * @brief Devuelve un iterador al final del mapa
	  * @return Iterador al final del mapa
	  */
	 iterator end() {
		 iterator i;
		 i.it = rutas.end();
		 return i;
	 }

	 /**
	  * @brief Clase iterador constante de la clase AlmacenRutas
	  */
	 class const_iterator {
     private:
		 /**
		  * @brief Iterador constante de la clase map
		  */
		 map<string, Ruta>::const_iterator it;
     public:

		 /**
		  * @brief Constructor por defecto de la clase
		  */
		 const_iterator() {}

		 /**
		  * @brief Constructor de la clase
		  * @param it Iterador constante de la clase map
		  */
		 const_iterator(const map<string, Ruta>::const_iterator &it) : it(it) {}

		 /**
		  * @brief Sobrecarga del operador de incremento
		  * @return Iterador incrementado
		  */
		 const_iterator &operator++() {
			 ++it;
			 return *this;
		 }

		 /**
		  * @brief Sobrecarga del operador de decremento
		  * @return Iterador decrementado
		  */
		 const_iterator &operator--() {
			 --it;
			 return *this;
		 }

		 /**
		  * @brief Sobrecarga del operador de acceso
		  * @return Ruta apuntada por el iterador
		  */
		 const Ruta &operator*() {
			 return it->second;
		 }

		 /**
		  * @brief Sobrecarga del operador de igualdad
		  * @param i Iterador con el que se compara
		  * @retval true Si son iguales
		  * @retval false Si son distintos
		  */
		 bool operator==(const const_iterator &i) {
			 return it == i.it;
		 }

		 /**
		  * @brief Sobrecarga del operador de desigualdad
		  * @param i Iterador con el que se compara
		  * @retval true Si son distintos
		  * @retval false Si son iguales
		  */
		 bool operator!=(const const_iterator &i) {
			 return it != i.it;
		 }

		 friend class AlmacenRutas;
     };

	/**
	 * @brief Devuelve un iterador constante al principio del mapa
	 * @return  Iterador constante al principio del mapa
	 */
	 const_iterator begin() const {
		 const_iterator i;
		 i.it = rutas.begin();
		 return i;
	 }

	 /**
	  * @brief Devuelve un iterador constante al final del mapa
	  * @return Iterador constante al final del mapa
	  */
	 const_iterator end() const {
		 const_iterator i;
		 i.it = rutas.end();
		 return i;
	 }

	friend ostream & operator<<(ostream & os, const AlmacenRutas& ar);
	friend istream & operator>>(istream & is, AlmacenRutas& ar);
};

/**
 * @brief Sobrecarga del operador de salida para la clase AlmacenRutas
 * @param os  Stream de salida
 * @param ar  Almacén de rutas
 * @return  Stream de salida
 */
ostream & operator<<(ostream& os, const AlmacenRutas& ar);

/**
 * @brief Sobrecarga del operador de entrada
 * @param is  Stream de entrada
 * @param ar  Almacén de rutas
 * @return  Stream de entrada
 */
istream & operator>>(istream& is, AlmacenRutas& ar);


#endif //PRACTICAFINAL_ALMACENRUTAS_H
