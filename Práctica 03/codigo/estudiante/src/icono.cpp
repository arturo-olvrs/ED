/**
 * @file icono.cpp
 * @brief Obtiene un icono (reducción) a partir de una imagen.
 *
 * Se obtiene una reducción de un factor @a factor.
 *
 * @param FichImagenOriginal Fichero de la imagen original.
 * @param FichImagenDestino Fichero donde se va a guardar el icono.
 * @param factor el factor de reducción que se le va a aplicar a la imagen.
 *
 * @pre factor > 0
 * @post La imagen resultante tendrá floor(Image::get_rows()/factor) x floor(Image::get_cols()/factor)
 *
 * Ejemplo de uso:
 * @code{.sh}
 * ./icono ./imagen_original.pgm ./imagen_icono.pgm 2
 * @endcode
 *
 * Este ejemplo muestra cómo utilizar el ejecutable **Icono** para obtener un icono a partir de una imagen.
 * En este caso, el factor de reducción es 2.
 *
 * <div style="text-align: center;">
 *   <div style="display: inline-block; text-align: center; margin: 0 3em;">
 *     <img src="vacas.png" alt="Imagen Original" style="border: none;" />
 *     <br>
 *     <small>Imagen Original</small>
 *   </div>
 *   <div style="display: inline-block; text-align: center; margin: 0 3em;">
 *     <img src="Ex_Icono.png" alt="Imagen Icono" style="border: none;" />
 *     <br>
 *     <small>Icono</small>
 *   </div>
 * </div>
 */

#include <iostream>
#include <cstring>
#include <cstdlib>

#include <image.h>

using namespace std;

int main (int argc, char *argv[]){
 
  char *origen, *destino; // nombres de los ficheros
  Image image;

  // Comprobar validez de la llamada
  if (argc != 4){
    cerr << "Error: Numero incorrecto de parametros.\n";
    cerr << "Uso: icono <FichImagenOriginal> <FichImagenDestino> <factor>\n";
    exit (1);
  }

  // Obtener argumentos
  origen   = argv[1];
  destino  = argv[2];
  int factor  = stoi(argv[3]);

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

  // Mostrar los parámetros de la Imagen
  cout << endl;
  cout << "Dimensiones de " << origen << ":" << endl;
  cout << "   Imagen   = " << image.get_rows()  << " filas x " << image.get_cols() << " columnas " << endl;



  // Comprobar el parámetro factor
  if (factor <= 0){
    cerr << "Error: Factor no valido." << endl;
    cerr << "Terminando la ejecucion del programa." << endl;
    return 1;
  }

  // Aplicar el icono
  Image icono = image.Subsample(factor);

  // Guardar la imagen resultado en el fichero
  if (icono.Save(destino))
    cout  << "La imagen se guardo en " << destino << endl;
  else{
    cerr << "Error: No pudo guardarse la imagen." << endl;
    cerr << "Terminando la ejecucion del programa." << endl;
    return 1;
  }

  return 0;
}
