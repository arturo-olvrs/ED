/**
 * @file pais.h
 * @brief Fichero cabecera del TDA Pais
 *
 * @author Arturo Olivares Martos
 * @author Daniel Hidalgo Chica
 */

#ifndef PRACTICAFINAL_PAIS_H
#define PRACTICAFINAL_PAIS_H

#include <string>
#include "punto.h"

/**
 * @brief TDA Pais
 *
 * Clase que representa un país.
 * Un objeto de esta clase está compuesto por un nombre, la ubicación de su bandera en el sistema de archivos y un punto que representa su posición en el mapa.
 *
 *
 */
class Pais {
private:

	/**
	 * @brief Nombre del país
	 */
	string nombre;

	/**
	 * @brief Bandera del país. String que representa el filename de la bandera en el sistema de archivose
	 */
	string bandera;

	/**
	 * @brief Punto que representa la posición del país en el mapa
	 */
	Punto p;

public:

	/**
	 * @brief Constructor por defecto
	 */
	Pais(){}

	/**
	 * @brief Constructor con parámetros
	 * @param nombre Nombre del país
	 * @param bandera Ubicación de la bandera del país en el sistema de archivos
	 * @param p Punto que representa la posición del país en el mapa
	 */
	Pais(string nombre, string bandera, const Punto &p);

	/**
	 * @brief Devuelve el nombre del país
	 * @return Nombre del país
	 */
	string getNombre() const;

	/**
	 * @brief Devuelve la ubicación de la bandera del país en el sistema de archivos
	 * @return Filename de la bandera en el sistema de archivos
	 */
	string getBandera() const;

	/**
	 * @brief Devuelve el punto que representa la posición del país en el mapa
	 * @return Punto que representa la posición del país en el mapa
	 */
	const Punto & getPunto() const;

	/**
	 * @brief Modifica el nombre del país
	 * @param nombre Nuevo nombre del país
	 */
	void setNombre(string nombre);

	/**
	 * @brief Modifica la ubicación de la bandera del país en el sistema de archivos
	 * @param bandera Nueva filename de la bandera del país en el sistema de archivos
	 */
	void setBandera(string bandera);

	/**
	 * @brief Modifica el punto que representa la posición del país en el mapa
	 * @param p Nuevo punto que representa la posición del país en el mapa
	 */
	void setPunto(const Punto &p);

	/**
	 * @brief Sobrecarga del operador de < para ordenar los paises por nombre
	 * @param p Pais con el que se compara
	 * @return True si el pais es menor que p, false en caso contrario
	 */
	bool operator<(const Pais &p) const;


	friend ostream & operator<<(ostream & os, const Pais & p);
	friend istream & operator>>(istream & is, Pais & p);
};

/**
 * @brief Sobrecarga del operador de salida
 * @param os Flujo de salida
 * @param p País del que se obtiene la información
 * @return Flujo de salida
 */
ostream & operator<<(ostream & os, const Pais & p);

/**
 * @brief Sobrecarga del operador de entrada
 * @param is Flujo de entrada
 * @param p País en el que se almacena la información
 * @return Flujo de entrada
 */
istream & operator>>(istream & is, Pais & p);


#endif //PRACTICAFINAL_PAIS_H
