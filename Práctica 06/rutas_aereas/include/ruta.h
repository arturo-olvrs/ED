/**
 * @file ruta.h
 * @brief Fichero cabecera del TDA Ruta
 *
 *
 * @author Arturo Olivares Martos
 * @author Daniel Hidalgo Chica
 */

#ifndef PRACTICAFINAL_RUTA_H
#define PRACTICAFINAL_RUTA_H

#include <list>
#include <string>
#include "punto.h"

using namespace std;


/**
 * @brief TDA Ruta
 *
 * Una instancia del tipo de dato abstracto Ruta es un objeto que representa una ruta aerea
 * formada por una lista de puntos y un codigo de ruta.
 */
class Ruta {
private:
	std::list<Punto> puntos;
	string codigo;

public:

	/**
	 * @brief Constructor por defecto de la clase
	 */
	Ruta(){}

	/**
	 * @brief Constructor de la clase
	 * @param codigo Codigo de la ruta
	 * @param puntos Lista de puntos que forman la ruta
	 */
	Ruta(string codigo, const list<Punto> &puntos);

	/**
	 * @brief Método que modifica el codigo de la ruta
	 * @param codigo Nuevo codigo de la ruta
	 */
	void setCodigo(string codigo);

	/**
	 * @brief Método que modifica la lista de puntos de la ruta
	 * @param puntos  Nueva lista de puntos de la ruta
	 */
	void setPuntos(const list<Punto> &puntos);

	/**
	 * @brief Método que devuelve el codigo de la ruta
	 * @return Codigo de la ruta
	 */
	string getCodigo() const;

	/**
	 * @brief Método que devuelve la lista de puntos de la ruta
	 * @return Lista de puntos de la ruta
	 */
	const list<Punto> & getPuntos() const;

	/**
	 * @brief Método que devuelve el numero de puntos de la ruta
	 * @return Numero de puntos de la ruta
	 */
	int getNumPuntos() const;

	/**
	 * @brief Método que inserta un punto en la ruta
	 * @param p Punto a insertar
	 */
	void insertarPunto(const Punto& p);

	/**
	 * @brief Método que elimina un punto de la ruta
	 * @param p Punto a eliminar
	 */
	void eliminarPunto(const Punto& p);


	class const_iterator;

	/**
	 * @brief Clase iterador de la clase ruta
	 */
	class iterator{
	private:
		/**
		 * @brief Iterador de la lista de puntos
		 */
		list<Punto>::iterator it;
	public:
		/**
		 * @brief Constructor por defecto
		 */
		iterator(){}

		/**
		 * @brief Constructor de la clase
		 * @param it Iterador de la lista de puntos
		 */
		iterator(const list<Punto>::iterator& it):it(it){}

		/**
		 * @brief Operador de incremento
		 * @return Iterador incrementado
		 */
		iterator& operator++(){
			++it;
			return *this;
		}

		/**
		 * @brief Operador de decremento
		 * @return Iterador decrementado
		 */
		iterator& operator--(){
			--it;
			return *this;
		}

		/**
		 * @brief Operador de igualdad
		 * @param i Iterador a comparar
		 * @retval true si son iguales
		 * @retval false si son distintos
		 */
		bool operator==(const iterator& i){
			return it==i.it;
		}

		/**
		 * @brief Operador de desigualdad
		 * @param i Iterador a comparar
		 * @retval true si son distintos
		 * @retval false si son iguales
		 */
		bool operator!=(const iterator& i){
			return it!=i.it;
		}

		/**
		 * @brief Operador de acceso
		 * @return Referencia al punto actual
		 */
		Punto& operator*(){
			return *it;
		}

		friend class Ruta;
		friend class const_iterator;
	};

	/**
	 * @brief Devuelve un iterador al principio de la lista de puntos
	 * @return  Iterador al principio de la lista de puntos
	 */
	iterator begin(){
		iterator i;
		i.it=puntos.begin();
		return i;
	}

	/**
	 * @brief Devuelve un iterador al final de la lista de puntos
	 * @return  Iterador al final de la lista de puntos
	 */
	iterator end(){
		iterator i;
		i.it=puntos.end();
		return i;
	}

	/**
	 * @brief Clase iterador constante de la clase ruta
	 */
	class const_iterator{
	private:
		/**
		 * @brief Iterador constante de la lista de puntos
		 */
		list<Punto>::const_iterator it;
	public:
		/**
		 * @brief Constructor por defecto
		 */
		const_iterator(){}

		/**
		 * @brief Constructor de la clase
		 * @param it Iterador constante de la lista de puntos
		 */
		const_iterator(const list<Punto>::const_iterator& it):it(it){}

		/**
		 * @brief Operador de incremento
		 * @return Iterador constante incrementado
		 */
		const_iterator& operator++(){
			++it;
			return *this;
		}

		/**
		 * @brief Operador de decremento
		 * @return Iterador constante decrementado
		 */
		const_iterator& operator--(){
			--it;
			return *this;
		}

		/**
		 * @brief Operador de igualdad
		 * @param i Iterador constante a comparar
		 * @retval true si son iguales
		 * @retval false si son distintos
		 */
		bool operator==(const const_iterator& i){
			return it==i.it;
		}

		/**
		 * @brief Operador de desigualdad
		 * @param i Iterador constante a comparar
		 * @retval true si son distintos
		 * @retval false si son iguales
		 */
		bool operator!=(const const_iterator& i){
			return it!=i.it;
		}

		/**
		 * @brief Operador de acceso
		 * @return Referencia constante al punto actual
		 */
		const Punto& operator*(){
			return *it;
		}
		friend class Ruta;
	};

	/**
	 * @brief Devuelve un iterador constante al principio de la lista de puntos
	 * @return  Iterador constante al principio de la lista de puntos
	 */
	const_iterator begin() const{
		const_iterator i;
		i.it=puntos.begin();
		return i;
	}

	/**
	 * @brief Devuelve un iterador constante al final de la lista de puntos
	 * @return  Iterador constante al final de la lista de puntos
	 */
	const_iterator end() const{
		const_iterator i;
		i.it=puntos.end();
		return i;
	}


	friend ostream& operator<<(ostream& os, const Ruta& r);
	friend istream& operator>>(istream& is, Ruta& r);
};


/**
 * @brief Sobrecarga del operador de salida
 * @param os Flujo de salida
 * @param r Ruta a imprimir
 * @return Flujo de salida
 */
ostream& operator<<(ostream& os, const Ruta& r);

/**
 * @brief Sobrecarga del operador de entrada
 * @param is Flujo de entrada
 * @param r Ruta a leer
 * @return Flujo de entrada
 */
istream& operator>>(istream& is, Ruta& r);


#endif //PRACTICAFINAL_RUTA_H
