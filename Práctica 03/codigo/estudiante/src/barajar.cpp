/**
 * @file barajar.cpp
 * @brief Baraja una imagen según el método Image::ShuffleRows_eff()
 *
 * @param FichImagenOriginal Fichero de la imagen original.
 * @param FichImagenDestino Fichero donde se va a guardar la imagen barajada.
 *
 * Ejemplo de uso:
 * @code{.sh}
 * ./barajar ./imagen_original.pgm ./imagen_barajada.pgm
 * @endcode
 *
 * Este ejemplo muestra cómo utilizar el ejecutable **Barajar** para barajar una imagen.
 *
 * <div style="text-align: center;">
 *   <div style="display: inline-block; text-align: center; margin: 0 3em;">
 *     <img src="shuffle_9973.png" alt="Imagen Original" style="border: none;" />
 *     <br>
 *     <small>Imagen Original</small>
 *   </div>
 *   <div style="display: inline-block; text-align: center; margin: 0 3em;">
 *     <img src="Ex_Barajada.png" alt="Imagen Barajada" style="border: none;" />
 *     <br>
 *     <small>Imagen Barajada</small>
 *   </div>
 * </div>
 */


#include <iostream>
#include <cstdlib>
#include <cstring>
#include <image.h>

using namespace std;

int main (int argc, char* argv[]) {
    char *fich_orig, *fich_rdo; // Nombres de los ficheros

    Image image; // Imagen que barajamos

    // Comprobamos validez de la llamada

    if (argc !=3){
        cerr << "Error: Numero incorrecto de parametros.\n";
        cerr << "Uso: barajar <FichImagenOriginal> <FichImagenDestino>";
        exit (1);
    }

    // Recuperamos argumentos
    fich_orig = argv[1];
    fich_rdo = argv[2];

    // Mostramos argumentos
    cout << endl;
    cout << "Fichero origen: " << fich_orig << endl;
    cout << "Fichero resultado: " << fich_rdo << endl;

    // Leer la imagen del fichero de entrada
    if (!image.Load(fich_orig)){
        cerr << "Error: No pudo leerse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }
    cout << endl;
    cout << "Dimensiones de " << fich_orig << ":" << endl;
    cout << "   Imagen   = " << image.get_rows()  << " filas x " << image.get_cols() << " columnas " << endl;

    // Barajamos las filas
    Image barajada(image); // Copia de image
    barajada.ShuffleRows_eff();

    if (barajada.MySave(fich_rdo))
        cout  << "La imagen se guardo en " << fich_rdo << endl;
    else{
        cerr << "Error: No pudo guardarse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }
}