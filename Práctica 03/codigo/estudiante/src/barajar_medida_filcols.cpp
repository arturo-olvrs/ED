/**
 * @file barajar_medida_filcols.cpp
 * @brief Fichero usado para medir la eficiencia empírica al llamar
 * 			a Image::ShuffleRows_eff con una imagen de distinto número de filas y columnas
 *
 * @param NumeroDeFilas Número de filas de la imagen con la que se trabaja.
 * @param NumeroDeColumnas Número de columnas de la imagen con la que se trabaja.
 *
 * @pre 0 <= @a NumeroDeFilas, @a NumeroDeColumnas
 */
#include <iostream>
#include <cstdlib>
#include <image.h>
#include <ctime>

/**
 * @page eff_barajar Eficiencia del método para barajar en la clase Image.
 *
 * El objetivo de esta página es analizar el método que baraja las filas de la imagen.
 * Veremos la diferencia entre los métodos Image::Shuffle_Rowsnoeff y Image::ShuffleRows_eff,
 * 		analizaremos por qué decimos que uno es más eficiente que otro, y haremos hincapié en
 * 		por qué se implementó en primer lugar el método no eficiente y, posteriormente, se hizo el eficiente.
 *
 * Como se explica en @ref page_repImagen, en un primer lugar para el TDA imagen,
 * 		mediante la clase Image se usaba una representación secuencial en memoria.
 * 		No obstante, como veremos a continuación esto provocaba que el método Image::ShuffleRows_noeff
 * 		fuese muy poco eficiente, por lo que se optó por modificar la representación en memoria y
 * 		terminar usando el método Image::ShuffleRows_eff. Como veremos, este cambio supuso variar
 * 		la representación interna, pero aumentó en gran medida la eficiencia.
 *
 * 	A continuación, vamos a analizar la eficiencia para ambas representaciones en el caso de variar:
 * 	- El número de filas
 * 	- El número de columnas
 * 	- El número de llamadas al método para una misma imagen
 *
 * @section rep_secuencial Uso de la representación secuencial.
 *
 * En este caso, usamos el método Image::ShuffleRows_noeff. Como podemos ver en el código, este tiene
 * una eficiencia teórica de orden @f$O(nfils*ncols)@f$:
 * @f[ \sum_{r=0}^{nfils-1} \sum_{c=0}^{ncols-1} 1 = nfils \cdot ncols \Longrightarrow O(nfils \cdot ncols) @f]
 * donde:
 * - @f$nfils@f$: Número de filas.
 * - @f$ncols@f$: Número de columnas.
 *
 * @subsection filas_sec Distinto número de filas
 *
 * En este caso, mantenemos constante el número de columnas (@f$ncols=300@f$) y el número
 *		de veces que se llama al método Image::ShuffleRows_noeff (@f$nreps=1@f$). No obstante, variamos el número de filas
 *		desde @f$100@f$ a @f$100000@f$ con incrementos de @f$500@f$.
 *		La gráfica que representa el número de filas frente número de segundos que tarda en ejecutarse es la siguiente:
 *
 * 	@image html Gr_Filas_Noeff.png "Número de filas frente a tiempo de ejecución con el método Image::ShuffleRows_noeff"
 * 	@image latex Gr_Filas_Noeff.png "Número de filas frente a tiempo de ejecución con el método Image::ShuffleRows_noeff"
 *
 * Como podemos ver, manteniendo todos los parámetros fijos, tenemos que depende linealmente del número de filas.
 * Esto coincide con lo predicho por la eficiencia teórica, ya que tenemos que sería @f$O(nfils*ncols)=O(300*nfils)=O(nfils)@f$.
 *
 * @subsection cols_sec Distinto número de columnas
 *
 * En este caso, mantenemos constante el número de filas (@f$nfils=300@f$) y el número
 *		de veces que se llama al método Image::ShuffleRows_noeff (@f$nreps=1@f$). No obstante, variamos el número de columnas
 *		desde @f$100@f$ a @f$100000@f$ con incrementos de @f$500@f$. La gráfica que representa el número de columnas frente
 *		número de segundos que tarda en ejecutarse es la siguiente:
 *
 * 	@image html Gr_Columnas_Noeff.png "Número de columnas frente a tiempo de ejecución con el método Image::ShuffleRows_noeff"
 * 	@image latex Gr_Columnas_Noeff.png "Número de columnas frente a tiempo de ejecución con el método Image::ShuffleRows_noeff"
 *
 * Como podemos ver, manteniendo todos los parámetros fijos, tenemos que depende linealmente del número de columnas.
 * Esto coincide con lo predicho por la eficiencia teórica, ya que tenemos que sería @f$O(nfils*ncols)=O(300*ncols)=O(ncols)@f$.
 *
 * @subsection nreps_sec Distinto número de repeticiones
 * En este caso, mantenemos constante el número de filas (@f$nfils=300@f$) y el número
 *		de columnas (@f$ncols=300@f$). No obstante, variamos el número de veces que se llama
 *		al método Image::ShuffleRows_noeff tras haber cargado la imagen con Image::Load
 *		y antes de guardarla con Image::Save . Este número varía desde @f$100@f$ a @f$46100@f$ con incrementos de @f$500@f$.
 *		La gráfica que representa el número de repeticiones frente número de segundos que tarda en ejecutarse es la siguiente:
 *
 * 	@image html Gr_Repeticiones_Noeff.png "Número de columnas frente a tiempo de ejecución con el método Image::ShuffleRows_noeff"
 * 	@image latex Gr_Repeticiones_Noeff.png "Número de columnas frente a tiempo de ejecución con el método Image::ShuffleRows_noeff"
 *
 * Como podemos ver, manteniendo todos los parámetros fijos, tenemos que depende linealmente del número de repeticiones.
 * Esto es evidente, ya que una sola ejecución sería @f$O(nfils*ncols)=O(300*300)=O(1)@f$. Por tanto, al repetirla @f$nreps@f$ veces, tenemos que es @f$O(nreps)@f$.
 *
 * Además, cabe destacar que este es el caso en el que más tarda, viendo que llega incluso a valores cercanos a los 200s.
 * Esto se debe a que este método es muy poco eficiente, ya que internamente hace copias de imágenes, etc.
 * Entonces, al llamarlo un gran número de veces tarda mucho más.
 *
 * El número de repeticiones no ha llegado hasta valores más altos por el alto coste de recursos del ordenador que requiere.
 *
 * @section rep_NO_secuencial Uso de la representación no secuencial.
 *
 * En este caso, usamos el método Image::ShuffleRows_eff. Como podemos ver en el código, este tiene
 * una eficiencia teórica de orden @f$O(nfils)@f$:
 * @f[ \sum_{i=0}^{nfils-1} k = k \cdot nfils \Longrightarrow O(nfils) @f]
 * donde:
 * - @f$nfils@f$: Número de filas.
 * - @f$ncols@f$: Número de columnas.
 *
 * @subsection filas_NO_sec Distinto número de filas
 *
 * En este caso, mantenemos constante el número de columnas (@f$ncols=300@f$) y el número
 *		de veces que se llama al método Image::ShuffleRows_eff (@f$nreps=1@f$). No obstante, variamos el número de filas
 *		desde @f$100@f$ a @f$100000@f$ con incrementos de @f$500@f$.
 *		La gráfica que representa el número de filas frente número de segundos que tarda en ejecutarse es la siguiente:
 *
 * 	@image html Gr_Filas_eff.png "Número de filas frente a tiempo de ejecución con el método Image::ShuffleRows_eff"
 * 	@image latex Gr_Filas_eff.png "Número de filas frente a tiempo de ejecución con el método Image::ShuffleRows_eff"
 *
 * Como podemos ver, manteniendo todos los parámetros fijos, tenemos que depende linealmente del número de filas.
 * Esto coincide con lo predicho por la eficiencia teórica, ya que tenemos que sería @f$O(nfils)@f$.
 *
 * @subsection cols_NO_sec Distinto número de columnas
 *
 * En este caso, mantenemos constante el número de filas (@f$nfils=300@f$) y el número
 *		de veces que se llama al método Image::ShuffleRows_eff (@f$nreps=1@f$). No obstante, variamos el número de columnas
 *		desde @f$100@f$ a @f$100000@f$ con incrementos de @f$500@f$. La gráfica que representa el número de columnas frente
 *		número de segundos que tarda en ejecutarse es la siguiente:
 *
 * 	@image html Gr_Columnas_eff.png "Número de columnas frente a tiempo de ejecución con el método Image::ShuffleRows_eff"
 * 	@image latex Gr_Columnas_eff.png "Número de columnas frente a tiempo de ejecución con el método Image::ShuffleRows_eff"
 *
 * Como podemos ver, manteniendo todos los parámetros fijos, tenemos que **NO** depende del número de columnas.
 * Esto coincide con lo predicho por la eficiencia teórica, ya que tenemos que sería @f$O(nfils)=O(300)=O(1)@f$.
 *
 * Este hecho es de destacar, ya que con la representación secuencial hemos visto en el apartado @ref cols_sec
 * 		que el tiempo de ejecución dependía del número de columnas, mientras que en este caso no.
 * 		Además, es importante notar que en este caso ha sido necesario hacer la media de 1000 ejecuciones de este método,
 * 		ya que el programa tardaba menos que la precisión de la librería **ctime** proporciona, al verse los tiempos situados en franjas horizontales.
 * 		Por tanto, optamos por hacer la media de 1000 ejecuciones para calcular el tiempo.
 *
 * @subsection nreps_NO_sec Distinto número de repeticiones
 * En este caso, mantenemos constante el número de filas (@f$nfils=300@f$) y el número
 *		de columnas (@f$ncols=300@f$). No obstante, variamos el número de veces que se llama
 *		al método Image::ShuffleRows_eff tras haber cargado la imagen con Image::Load
 *		y antes de guardarla con Image::MySave. Notemos que empleamos este método en lugar de
 *		Image::Save ya que hemos empleado la representación no secuencial.
 *
 *		Este número de repeticiones varía desde @f$100@f$ a @f$100000@f$ con incrementos de @f$500@f$.
 *		La gráfica que representa el número de repeticiones frente número de segundos que tarda en ejecutarse es la siguiente:
 *
 * 	@image html Gr_Repeticiones_eff.png "Número de columnas frente a tiempo de ejecución con el método Image::ShuffleRows_eff"
 * 	@image latex Gr_Repeticiones_eff.png "Número de columnas frente a tiempo de ejecución con el método Image::ShuffleRows_eff"
 *
 * Como podemos ver, manteniendo todos los parámetros fijos, tenemos que depende linealmente del número de repeticiones.
 * Esto es evidente, ya que una sola ejecución sería @f$O(nfils*ncols)=O(300*300)=O(1)@f$. Por tanto, al repetirla @f$nreps@f$ veces, tenemos que es @f$O(nreps)@f$.
 *
 * También es importante notar que, debido al cambio en la representación, este método es mucho más rápido.
 * Basta con compararlo con la gráfica de @ref nreps_sec para ver la diferencia de tiempo tan notoria.
 *
 */

using namespace std;

int main(int argc, char *argv[]) {
	int nfils, ncols;

	// Comprobamos validez de la llamada
	if (argc != 3) {
		cerr << "Error: Numero incorrecto de parametros.\n";
		cerr << "Uso: barajar_medida_filcols <NumeroDeFilas> <NumeroDeColumnas>";
		exit(1);
	}

	// Recuperamos argumentos
	nfils = stoi(argv[1]);
	ncols = stoi(argv[2]);

	Image image(nfils, ncols, 0); // Imagen vamos a barajar

	// Comprobar el parámetro nreps
	if (nfils <= 0 || ncols <= 0) {
		cerr << "Error: Numero de filas o columnas no valido." << endl;
		cerr << "Terminando la ejecucion del programa." << endl;
		return 1;
	}

	const int NUM_VECES = 1e3; // Media eficiencia

	clock_t tini = clock;    // Anotamos el tiempo de inicio

	for (int n = 0; n < NUM_VECES; n++)
		image.ShuffleRows_eff;

	clock_t tfin = clock;   // Anotamos el tiempo de finalización

	// Mostramos resultados
	cout << (tfin - tini) / (double) CLOCKS_PER_SEC / NUM_VECES << endl;
}