/**
 * @file Tablero.h
 * @brief Fichero cabecera del TDA Tablero
 *
 * @author Joaquín Avilés de la Fuente
 * @author Daniel Hidalgo Chica
 * @author Arturo Olivares Martos
 */

#ifndef SUDOKU_TABLERO_H
#define SUDOKU_TABLERO_H

#include <vector>
#include "Grupo.h"

/**
 * @brief TDA Tablero
 * Representa al sudoku en sí; es decir, al tablero 9x9 con las casillas y los grupos.
 *
 *
 * Una instancia @e tab del tipo de dato abstracto @c Tablero es una matriz
 * 9x9 con casillas que identifican las distintas estructuras, es decir, a las filas, columnas
 * y cubo. Esto es de vital importancia, pues tomaremos en muchas ocasiones
 * el nombre estructura para identificar estos tres términos, ya que en ninguno de ellos
 * se podrán repetir casillas con mismo @c valor.
 *
 * Lo representaremos como un vector de grupos, que a su vez identifica todas las
 * casillas que tiene el Tablero del Sudoku Killer.
 *
 * @invariant Todas las casillas deben ser válidas
 * @invariant Num_Casillas = 81
 * @invariant Todos los grupos del vector deben cumplir con su invariante de representación
 */

class Tablero {
private:

	/**
	 * @brief Vector de los grupos que quedan en el sudoku.
	 *
	 * Inicialmente, abarca el tablero completo.
	 */
    vector<Grupo> grupos;

	/**
	 * @brief Matriz de Casillas que representan el tablero del sudoku en sí.
	 */
    vector<vector<Casilla>> sudoku;
public:
    /**
     * @brief Constructor sin argumentos
     */
    Tablero();

    /**
     * @brief Constructor con vector de grupos y vector de vectores de casillas
     * @param grupos Vector de grupos del tablero
     * @param sdk Tabla de casillas del tablero
     */
    Tablero(const vector<Grupo> &grupos, const vector<vector<Casilla>>& sdk);

    /**
     * @brief Devuelve el grupo correspondiente a la posición
     * de este en el vector @c sudoku
     * @param pos Posición del grupo que se quiere tener
     * @return Objeto de la clase Grupo, que ocupa dicha @c pos
     */
    const Grupo &get_grupo (int pos) const;

    /**
     * @brief Modifica el grupo de la casilla que escribe eliminándola de este,
     * con el metodo quitar_casilla (Casilla cas) de la clase Grupo y modifica el sudoku
     * colocando el valor a la casilla correspondiente.
     *
     * Además, llamará a limpiar (por defecto) para quitar las combinaciones posibles de otros grupos.
     * @param casilla_escrita Casilla cuyo valor se escribe
     * @param limpiar Por defecto limpia. En el caso que no queramos, pasar un booleano igual a false.
     */
    void set_casilla(const Casilla &casilla_escrita, bool limpiar = true);

	/**
	 * @brief Escribe un vector de casillas en el tablero. Llama a Tablero::set_casilla()
	 * @param a_escribir Vector de casillas a escribir en el sudoku.
	 */
	void escribir_vector(const vector<Casilla> &a_escribir);

    /**
     * @brief Escribe las casillas inmediatas obtenidas:
     * - Usando el método del 45 para el sudoku killer (y derivados con estructuras mayores). Tablero::metodo_45()
     * - Rellenando grupos con una única casilla. Tablero::rellenar_unitarias()
     */
    void escribir_inmediatos();

    /**
     * @brief Rellena todas las combinaciones posibles (cada una con todas sus posiciones).
     * LLama a calcular combinaciones de cada grupo de la clase Grupo
     */
    void calcular_todas_combinaciones();

    /**
     * @brief Actualiza el tablero. LLama a:
     *  - limpiar_basico(const Casilla &cas)
     *  - limpiar_unic_comb(const Casilla &cas)
     *
     * @param cas Casilla cuyo valor se limpiará
     */
    void limpiar(const Casilla &cas);

    /**
     * @brief Itera sobre cada grupo llamando a escribe_determinados()
     */
    void escribir_determinados();
private:
    /**
     * @brief Devuelve el grupo al que esta casilla pertenece
     * @param cas Casilla cuyo grupo se devuelve
     * @return Referencia al grupo al que @a cas pertenece
     */
    Grupo &get_grupo(const Casilla &cas) const;
    /**
     * @brief Devuelve un vector de los grupos que tienen al menos una casilla
     * en esa fila
     * @param fila Fila del sudoku en la que buscar grupos
     * @return Vector de Grupos que cumplen dicha condicion.
     */
    vector<Grupo>  getGrupos_fila(const Casilla &fila) const;

    /**
     * @brief Devuelve un vector de los grupos que tienen al menos una casilla
     * en esa columna
     * @param col Columna del sudoku en la que buscar grupos
     * @return Vector de Grupos que cumplen dicha condicion.
     */
    vector<Grupo>  getGrupos_col(const Casilla &col) const;

    /**
     * @brief Devuelve un vector de los grupos que tienen al menos una casilla
     * en ese cubo
     * @param cubo Cubo del sudoku en el que buscar grupos
     * @return Vector de Grupos que cumplen dicha condicion.
     */
    vector<Grupo>  getGrupos_cubo(const Casilla &cubo) const;

    /**
     * @brief Rellena los grupos que tienen una sola casilla.
     *
     * Las guarda en un vector y las escribe con Tablero::escribir_vector()
     */
    void rellenar_unitarias();

    /**
    * @brief Escribe las casillas determinadas por el método del 45 (o derivados inmediatos).
     *
    * MÉTODO DE LOS 45
     *
    * Iterando sobre cada una de las estructuras del tablero (todas las filas, columnas y cubos de 3x3)
    * examinamos si todos los grupos con casillas en esa estructura están totalmente contenidos menos
    * uno de ellos. En ese caso, si el grupo no-enteramente-contenido tiene fuera de la estructura
    * 1 sola casilla, o size_grupo-1 casillas, podremos determinar de manera inmediata una casilla
    * del grupo. (Tablero::unico_casillas_fuera_{estructura})
    * - En el caso de una sola casilla fuera:
    * 		- casilla = suma_todos_grupos_de_la_estructura - 45
    * - En el caso de size-1 casillas fuera:
    * 		- casilla = 45 - suma_grupos_enteros_dentro
    *
    * Nótese que el método es fácilmente aplicable al caso en el que tengamos una estructura
    * compuesta de dos o más de las estructuras anteriormente consideradas (sea n) usando
    * 45*n en las fórmulas.
     *
     * Obtiene un vector con las casillas a escribir y las escribe con Tablero::escribir_vector.
    */
    void metodo_45();

    // Para obtener inmediatas, devuelven casilla (identificando grupo)
    // nula si no hay uno solo en la estructura
    // Devuelve precisamente la casilla que se puede calcular (única fuera o única dentro)
    /**
     * @brief Devuelve la casilla que se puede calcular (única fuera o única dentro). Devuelve casilla
     * nula si no existe una única fuera o dentro de la estructura
     * @param fila Casilla de la cual solo tomaremos la primera coordenada
     * @param desp Número de filas que hemos utilizado en el método 45 (@see metodo_45())
     * @return Casilla que se puede calcular
     */
    const Casilla& unico_casillas_fuera_fil(const Casilla &fila, int desp=0) const;

    /**
     * @brief Devuelve la casilla que se puede calcular (única fuera o única dentro). Devuelve casilla
     * nula si no existe una única fuera o dentro de la estructura
     * @param col Casilla de la cual solo tomaremos la segunda coordenada
     * @param desp Número de columnas que hemos utilizado en el método 45. (@see metodo_45())
     * @return Casilla que se puede calcular
     */
    const Casilla& unico_casillas_fuera_col(const Casilla &col, int desp=0) const;

    /**
     * @brief Devuelve la casilla que se puede calcular (única fuera o única dentro). Devuelve casilla
     * nula si no existe una única fuera o dentro de la estructura
     * @param cubo Casilla que utilizaremos para identificar el cubo
     * @param desp_dcha Predeterminado false, ya que solo en el caso de querer tomar dos grupos hacia la derecha la
     * llamaremos con booleano igual a true. (@see metodo_45())
     * @param desp_abj Predeterminado false, ya que solo en el caso de querer tomar dos grupos hacia abajo la
     * llamaremos con booleano igual a true. (@see metodo_45())
     * @return Casilla que se puede calcular
     */
    const Casilla& unico_casillas_fuera_cubo(Casilla cubo, bool desp_dcha=false, bool desp_abj=false) const;


    // Para la limpieza

    /**
     * @brief Dada la última casilla escrita en el tablero, limpia todas las combinaciones y
     * posiciones de cada estructura que contenga a @a cas
     *
     * LLama a Tablero::limp_{estructura}(Casilla cas)
     *
     * @param cas Última casilla escrita
     */
    void limpiar_basico(const Casilla &cas);


    /**
    * @brief Dada la última casilla escrita en el tablero (o simulada), itera sobre todos los grupos
    * con casillas dentro de la fila a la que @a cas pertenece
    *
    * - LLama a Grupo::limp_comb_en_fila(const Casilla& cas)
    * - LLama a Grupo::limp_comb_no_en_fila(const Casilla& cas)
    *
    * Esto se da porque la manera de limpiar un grupo de imposibilidades es
    * notablemente distinta en los casos en los que los grupos afectados estén
    * o no enteramente contenidos dentro de la estructura afectada
    *
    * @param cas última casilla escrita (o simulada)
    */
    void limpiar_fila(const Casilla &cas);

    /**
    * @brief Dada la última casilla escrita (o simulada) en el tablero, itera sobre todos los grupos
    * con casillas dentro de la col a la que @a cas pertenece
     *
    * - LLama a Grupo::limp_comb_en_col(const Casilla& cas)
    * - LLama a Grupo::limp_comb_no_en_col(const Casilla& cas)
    *
    * Esto se da porque la manera de limpiar un grupo de imposibilidades es
    * notablemente distinta en los casos en los que los grupos afectados estén
    * o no enteramente contenidos dentro de la estructura afectada
    *
    * @param cas última casilla escrita (o simulada)
    */
    void limpiar_col(const Casilla &cas);

    /**
    * @brief Dada la última casilla escrita (o simulada) en el tablero, itera sobre todos los grupos
    * con casillas dentro del cubo al que @a cas pertenece
    *
    * - LLama a Grupo::limp_comb_en_cubo(const Casilla& cas)
    * - LLama a Grupo::limp_comb_no_en_cubo(const Casilla& cas)
    *
    * Esto se da porque la manera de limpiar un grupo de imposibilidades es
    * notablemente distinta en los casos en los que los grupos afectados estén
    * o no enteramente contenidos dentro de la estructura afectada
    *
    * @param cas última casilla escrita (o simulada)
    */
    void limpiar_cubo(const Casilla &cas);

    /**
    * @brief
    *  Sobre cada uno de los grupos tocados por las estructuras a las que @a cas pertenece se comprobará:
    *      - Si ese grupo está contenido entero dentro de una estructura
    *      - Si ese grupo tan solo conserva una de sus combinaciones
    *  Si ambas condiciones se cumplen, ejecutará este método de la siguiente
    *  manera:
     *
     * @code
    *  for (int i = 0; i < tam_unica_comb; i++) {
    *      Casilla cas(grupo[0].getCoord(),grupo.getComb[0][i]); // Solo hay una comb. ([0]) (con i sumandos)
    *      limpiar_{esctructura}(cas); // Donde {estructura} será la fila, col. o cubo
     *                                 // en el que grupo esté enteramente contenido (guión 1)
    *  }
     *  @endcode
    *
    * La motivación de este uso del método reside en que si en cierta estructura encontramos
    * un grupo con una única combinación, aunque no sepamos el orden en el que esta
    * aparecerá (su posición) y por tanto no podamos escribirla, sabemos que todos
    * esos dígitos aparecerán en las casillas asociadas al grupo, y por tanto no aparecerán
    * en ninguna otra casilla de la estructura que lo contenga
     * Por tanto, llamamos a limpiar_{estructura} con una casilla simulada
     *
     * @param cas Úlima casilla escrita
     */

    void limpiar_unic_comb(const Casilla &cas);
};


#endif //SUDOKU_TABLERO_H
