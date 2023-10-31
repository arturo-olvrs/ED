/**
 * @file zoom.cpp
 * @brief Aplica un zoom 2x de una imagen PGM
 *
 * Merece la pena detallar el proceso de obtención de la imagen "zoomeada".
 *
 * La idea reside en expandir la imagen al doble de su tamaño original y
 * rellenar los bytes correspondientes con la media de aquellos que le rodean.
 *
 * Así, por ejempolo, si tenemos en cierta fila dos bytes de valores 1 y 255 se colocará
 * en esa misma fila y entre esos dos un byte de valor 128. Esto resulta natural,
 * y funciona para todos los píxeles salvo para aquellos nuevos bytes de la matriz
 * que no estén rodeados ni en su fila ni en so columna por bytes originales. Usaremos
 * el método Image::Mean() para tratarlos.
 *
 * En primer lugar, el método Image::Zoom2X() generará una imagen que tendrá el doble
 * de filas y de columnas (-1) que la original. Tras esto, comenzamos a rellenar la matriz
 * distinguiendo casos:
 *
 * Iterando sobre la matriz ampliada:
 *
 * - Si tanto la fila en la que se encuentra el elemento como su columna son pares:
 * En ese caso ese byte es de los originales de la matriz, y por tanto su valor se cooresponde
 * con el colocado en la matriz original con la mitad de sus coordenadas.
 *
 * - Si la fila o la columna son impares: Entonces la casilla no es de las originales.
 * Por tanto, lo rellenaremos con el "píxel medio" correspondiente:
 * average_pixel = (byte)round(Mean((int)(fil/2), (int)(col/2), 1+fil%2, 1+col%2));
 *
 * Este cálculo obtiene lo que queremos tanto en el caso en el que el píxel esté "rodeado" en su
 * fila o columna por originales como en el contrario, veamos cómo:
 *
 * (Téngase en cuenta que el método Image::Mean() recibe una casilla (fila/columna) y dos desplazamientos, uno horizontal
 * y otro vertical, devuelviendo el píxel medio de los contenidos en el rectángulo cuya
 * esquina superior izquierda es la casilla dada y se extiende con los desplazamientos
 * indicados).
 *
 * - Si el píxel está rodeado (la fila o la columna son pares):
 * Tratemos por ejemplo el caso de que la fila sea par y la columna impar (el contrario
 * es totalmente análogo). Los píxeles cuya media nos da el que buscamos insertar
 * son los dos que estén en la misma fila que éste y cada uno a un lado (nótese
 * que siempre tenemos uno a cada lado porque en los casos de las columnas laterales
 * si se diese que la fila es par, entonces tanto fila como columna serían pares
 * y no estaríamos en este caso). Por tanto, el método nos tomaría la media del rectángulo
 * cuya esquina superior izquierda (en la imagen original) tiene su fila en fil/2 y su columna
 * en (col-1)/2 (truncamiento), y que se extiende 1 fila verticalmente (no se extiende)
 * y 2 columnas horizontalmente (se expande una columna). Y esas son precisamente las dos
 * casillas cuya media buscábamos.
 *
 * - Si el píxel no está rodeado (su fila y su columna son impares):
 * En esta situación, querremos que el píxel que insertamos reciba su valor
 * de la media de los 4 píxeles originales que toca en sus "esquinas". Veamos
 * que nuestro método también consigue este propósito.
 *
 * Procediendo análogamente, tomaríamos la media del cuadrado
 * en la matriz original cuya esquina superior izquierda está en ( (fil-1)/2 , (col-1)/2 )
 * y se extiende hacia abajo y hacia la derecha en 2 líneas. Así, la media
 * para nuestro píxel insertado sería la de los cuatro píxeles que tocan
 * sus esquinas, como buscábamos.
 *

 *
 * @param FichImagenOriginal Fichero de la imagen original.
 * @param FichImagenDestino Fichero donde se va a guardar la imagen con el zoom aplicado.
 * @param fila Fila de la esquina superior izquierda de la zona de recorte.
 * @param columna Columna de la esquina superior izquierda de la zona de recorte.
 * @param Lado Longitud del lado del cuadrado a recortar.
 *
 * @pre (@a fila, @a columna) debe ser una posición válida.
 * @pre @a Lado > 0
 * @pre La zona a aplicar el zoom debe estar entera incluida en la imagen original.
 *
 * Ejemplo de uso:
 * @code{.sh}
 * ./zoom ./imagen_original.pgm ./imagen_ampliada.pgm 85 145 60
 * @endcode
 *
 * Este ejemplo muestra cómo utilizar el ejecutable **Zoom** para ampliar x2 una imagen.
 * Se amplía x2 la imagen desde la esquina (85,145) un cuadrado de lado 60 píxeles.
 *
 * <div style="text-align: center;">
 *   <div style="display: inline-block; text-align: center; margin: 0 3em;">
 *     <img src="vacas.png" alt="Imagen Original" style="border: none;" />
 *     <br>
 *     <small>Imagen Original</small>
 *   </div>
 *   <div style="display: inline-block; text-align: center; margin: 0 3em;">
 *     <img src="Ex_Ampliada.png" alt="Imagen Ampliada" style="border: none;" />
 *     <br>
 *     <small>Imagen Ampliada</small>
 *   </div>
 * </div>
 */

#include <iostream>
#include <cstdlib>
#include "image.h"

using namespace std;

int main (int argc, char *argv[]){
 
  char *origen, *destino; // nombres de los ficheros
  Image image;

  // Comprobar validez de la llamada
  if (argc != 6){
    cerr << "Error: Numero incorrecto de parametros.\n";
    cerr << "Uso: zoom <FichImagenOriginal> <FichImagenDestino> <fila> <columna> <lado>\n";
    exit (1);
  }

  // Obtener argumentos
  origen   = argv[1];
  destino  = argv[2];
  int fil  = stoi(argv[3]);
  int col  = stoi(argv[4]);
  int lado = stoi(argv[5]);

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



  // Comprobar los parámetros

  // Coordenada de inicio
  bool fil_ok = 0<= fil && fil < image.get_rows();
  bool col_ok = 0<= col && col < image.get_cols();
  if (!(fil_ok && col_ok)){
    cerr << "Error: Coordenada de inicio no valida." << endl;
    cerr << "Terminando la ejecucion del programa." << endl;
    return 1;
  }

  // Coordenada final
  fil_ok = 0<= fil+lado && fil+lado <= image.get_rows();
  col_ok = 0<= col+lado && col+lado <= image.get_cols();
  if (!(fil_ok && col_ok)){
      cerr << "Error: Zona descrita no está totalmente incluida." << endl;
      cerr << "Terminando la ejecucion del programa." << endl;
      return 1;
  }

  // Aplicar el crop
  Image recortada = image.Crop(fil, col, lado, lado);

  // Aplicar el zoom
  Image ampliada = recortada.Zoom2X();

  // Guardar la imagen resultado en el fichero
  if (ampliada.Save(destino))
    cout  << "La imagen se guardo en " << destino << endl;
  else{
    cerr << "Error: No pudo guardarse la imagen." << endl;
    cerr << "Terminando la ejecucion del programa." << endl;
    return 1;
  }

  return 0;
}
