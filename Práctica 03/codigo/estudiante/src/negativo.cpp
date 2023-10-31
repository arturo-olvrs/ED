/**
 * @file negativo.cpp
 * @brief Calcula el negativo de una imagen PGM
 *
 * @param FichImagenOriginal Fichero de la imagen original a invertir
 * @param FichImagenDestino Fichero donde se va a guardar la imagen invertida
 *
 * Ejemplo de uso:
 * @code{.sh}
 * ./negativo ./imagen_original.pgm ./imagen_invertida.pgm
 * @endcode
 *
 * Este ejemplo muestra cómo utilizar el ejecutable **Negativo** para invertir una imagen.
 *
 * <div style="text-align: center;">
 *   <div style="display: inline-block; text-align: center; margin: 0 3em;">
 *     <img src="vacas.png" alt="Imagen Original" style="border: none;" />
 *     <br>
 *     <small>Imagen Original</small>
 *   </div>
 *   <div style="display: inline-block; text-align: center; margin: 0 3em;">
 *     <img src="Ex_Negativo.png" alt="Imagen Invertida" style="border: none;" />
 *     <br>
 *     <small>Imagen Invertida</small>
 *   </div>
 * </div>
 *
 */

#include <iostream>
#include <cstdlib>

#include "image.h"

using namespace std;

int main (int argc, char *argv[]){
 
  char *origen, *destino; // nombres de los ficheros
  Image image;

  // Comprobar validez de la llamada
  if (argc != 3){
    cerr << "Error: Numero incorrecto de parametros.\n";
    cerr << "Uso: negativo <FichImagenOriginal> <FichImagenDestino>\n";
    exit (1);
  }

  // Obtener argumentos
  origen  = argv[1];
  destino = argv[2];

  // Mostramos argumentos
  cout << endl;
  cout << "Fichero origen: " << origen << endl;
  cout << "Fichero resultado: " << destino << endl;

  // Leer la imagen del fichero de entrada
  if (!image.Load(origen)){
    cerr << "Error: No pudo leerse la imagen." << endl;
    cerr << "Terminando la ejecucion del programa." << endl;
    return 1;
  }

  // Mostrar los parametros de la Imagen
  cout << endl;
  cout << "Dimensiones de " << origen << ":" << endl;
  cout << "   Imagen   = " << image.get_rows()  << " filas x " << image.get_cols() << " columnas " << endl;

  // Calcular el negativo
  image.Invert();

  // Guardar la imagen resultado en el fichero
  if (image.Save(destino))
    cout  << "La imagen se guardo en " << destino << endl;
  else{
    cerr << "Error: No pudo guardarse la imagen." << endl;
    cerr << "Terminando la ejecucion del programa." << endl;
    return 1;
  }

  return 0;
}
