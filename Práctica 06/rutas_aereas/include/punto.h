/**
 * @file punto.h
 * @brief Fichero cabecera del TDA Punto
 * @author Arturo Olivares Martos
 * @author Daniel Hidalgo Chica
 */

#ifndef PRACTICAFINAL_PUNTO_H
#define PRACTICAFINAL_PUNTO_H

#include <iostream>
#include <cmath>

using namespace std;

/**
 * @brief TDA Punto
 *
 * Una instancia @e p del tipo de datos abstracto @c Punto es un objeto
 * con dos campos, latitud y longitud, que representan las coordenadas
 * de un punto en el mapa.
 */
class Punto {

private:
	/**
	 * @brief Latitud del punto
	 */
	double latitud;

	/**
	 * @brief Longitud del punto
	 */
	double longitud;



public:

	/**
	 * @brief Constructor por defecto
	 */
	Punto();

	/**
	 * @brief Constructor con parámetros
	 * @param lat Latitud del punto
	 * @param lon Longitud del punto
	 */
	Punto(double lat, double lon);

	/**
	 * @brief Devuelve la latitud del punto
	 * @return Latitud del punto
	 */
	double getLatitud() const;

	/**
	 * @brief Devuelve la longitud del punto
	 * @return Longitud del punto
	 */
	double getLongitud() const;

	/**
	 * @brief Asigna una latitud al punto
	 * @param lat Latitud a asignar
	 */
	void setLatitud(double lat);

	/**
	 * @brief Asigna una longitud al punto
	 * @param lon Longitud a asignar
	 */
	void setLongitud(double lon);

	/**
	 * @brief Sobrecarga del operador ==
	 * @param p Punto a comparar
	 * @retval True si son iguales
	 * @retval False en caso contrario
	 */
	bool operator==(const Punto & p) const;

    /**
     * @brief Pasa de coordenadas geográficas a coordenadas en el mapa
     * @param num_columnas Número de columnas del mapa
     * @param num_filas Número de filas del mapa
     * @return Par de enteros con las coordenadas en el mapa
     */
    pair<int, int> coordenadasMapa(int num_columnas, int num_filas) const;

    /**
     * @brief Punto medio entre dos puntos
     * @param p Punto con el que calcular el punto medio
     * @param num_columnas Número de columnas del mapa
     * @param num_filas Número de filas del mapa
     * @return Par de enteros con las coordenadas en el mapa del punto medio
     */
    pair<int,int> punto_medio_en_mapa(const Punto & p, int num_columnas, int num_filas) const;

    /**
     * @brief Ángulo de la recta que une dos puntos
     * @param p Punto con el que calcular el ángulo
     * @param num_columnas Número de columnas del mapa
     * @param num_filas Número de filas del mapa
     * @return Ángulo orientado de la recta que une los dos puntos
     */
    double angulo_en_mapa(const Punto & p, int num_columnas, int num_filas) const;

	friend ostream & operator<<(ostream & os, const Punto & p);
	friend istream & operator>>(istream & is, Punto & p);
};

/**
 * @brief Sobrecarga del operador >>
 * @param is Flujo de entrada
 * @param p Punto a leer
 * @return Flujo de entrada
 */
istream & operator>>(istream & is, Punto & p);

/**
 * @brief Sobrecarga del operador <<
 * @param os Flujo de salida
 * @param p Punto a escribir
 * @return Flujo de salida
 */
ostream & operator<<(ostream & os, const Punto & p);


#endif //PRACTICAFINAL_PUNTO_H
