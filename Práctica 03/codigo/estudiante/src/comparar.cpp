/**
 * @file comparar.cpp
 * @brief Dadas dos imágenes, informa si son iguales o no pixel a pixel.
 *
 * @param FichImagen1 Fichero de la imagen1.
 * @param FichImagen2 Fichero de la imagen2.
 *
 * Ejemplo de uso:
 * @code{.sh}
 * ./comparar ./imagen_1.pgm ./imagen_1.pgm
 * Las imágenes son iguales: true
 *
 * ./comparar ./imagen_1.pgm ./imagen_2.pgm
 * Las imágenes son iguales: false
 * @endcode
 *
 * Este ejemplo muestra cómo utilizar el ejecutable **Comparar** para comparar dos imágenes.
 */

#include <iostream>
#include <cstring>
#include <cstdlib>

#include <image.h>

using namespace std;

int main (int argc, char *argv[]){
 
  char *origen1, *origen2; // nombres de los ficheros
  Image img1, img2;

  // Comprobar validez de la llamada
  if (argc != 3){
    cerr << "Error: Numero incorrecto de parametros.\n";
    cerr << "Uso: comparar <FichImagen1> <FichImagen2>\n";
    exit (1);
  }

  // Obtener argumentos
  origen1  = argv[1];
  origen2  = argv[2];

  // Mostramos argumentos
  cout << endl;
  cout << "Fichero origen1: " << origen1 << endl;
  cout << "Fichero origen2: " << origen2 << endl;

  // Leer la imagen1 del fichero de entrada 1
  if (!img1.Load(origen1)){
    cerr << "Error: No pudo leerse la imagen 1." << endl;
    cerr << "Terminando la ejecucion del programa." << endl;
    return 1;
  }

  // Leer la imagen2 del fichero de entrada 2
  if (!img2.Load(origen2)){
    cerr << "Error: No pudo leerse la imagen 2." << endl;
    cerr << "Terminando la ejecucion del programa." << endl;
    return 1;
  }


  cout << "Las imágenes son iguales: " << boolalpha << (img1==img2) << endl;

  return 0;
}
