/**
 * @file Casilla.h
 * @brief Fichero cabecera del TDA Casilla
 *
 * @author Joaquín Avilés de la Fuente
 * @author Daniel Hidalgo Chica
 * @author Arturo Olivares Martos
 */

#ifndef SUDOKU_CASILLA_H
#define SUDOKU_CASILLA_H

#include <utility>
#include <vector>
using namespace std;

/**
 * @brief TDA Casilla
 * Representa una única posición de sudoku que puede contener un único valor numérico
 *
 * Una instancia @e cas del tipo de dato abstracto @c Casilla es un objeto
 * dotado de un par de enteros positivos que representan sus coordenadas
 * en un tablero 9x9 de Sudoku, y el valor que identifica al número que guarda
 * esa casilla
 * Lo representaremos como una estructura de un objeto de tipo pair<int> y un entero
 * @invariant 0 < casilla.coord.first(), casilla.coord.second() <= 9
 * @invariant 0 <= valor <= 9 (Solo valdrá 0 si la casilla no está escrita aún)
 */
class Casilla {
private:
    /**
     * @brief Un dato pair que indica la posición en el tablero
     * mediante la fila y la columna en este orden
     * @pre 0 < casilla.coord.first(), casilla.coord.second() <= 9
     */
    pair<int, int> coord;

    /**
     * @brief Número de la casilla
     * @pre 1 <= @c valor <= 9 (Solo puede tener valor si no esta escrita aún)
     */
    int valor;
public:
    /**
     * @brief Constructor de la clase con unas coordenadas y con un valor preciso
     * @param coord Coordenadas de la casilla en el tablero
     * @param valor Valor que guarda la casilla
     * @return Crea la casilla precisada
     * @pre @a 0 <= coord.first(), coord.second() < 9
     * @pre @a valor 1 <= valor <= 9
     */
    Casilla(pair<int,int> coord, int valor=0);

    /**
     * @brief Constructor sin argumentos
     * @return Objeto por defecto de la clase Casilla
     */
    Casilla();

    /**
     * @brief Recupera coordenadas de la casilla
     * @return Par de enteros con las coordenadas
     */
    pair<int,int> getCoord() const;
    /**
     * @brief Recupera valor de la casilla
     * @return Valor que guarda la casilla
     */
    int getValor() const;
    /**
     * @brief Fija coordenadas de la casilla
     * @param coord Coordenadas que se pasan
     * @pre Las coordenadas son válidas en un Sudoku
     */
     void setCoord(pair<int,int> coord);

    /**
     * @brief Fija valor de la casilla
     * @param valor Valor que se escribirá en la casilla
     * @pre 1<=valor<=9
     */
    void setValor(int valor);

};


#endif //SUDOKU_CASILLA_H