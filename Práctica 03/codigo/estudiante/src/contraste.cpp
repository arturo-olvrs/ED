/**
 * @file contraste.cpp
 * @brief Modifica el contraste de una imagen.
 *
 * @param FichImagenOriginal Fichero de la imagen original.
 * @param FichImagenDestino Fichero donde se va a guardar el icono.
 * @param a Mínimo del intervalo de contraste de la imagen de entrada.
 * @param b Máximo del intervalo de contraste de la imagen de entrada.
 * @param min Mínimo del intervalo de contraste de la imagen de salida.
 * @param max Máximo del intervalo de contraste de la imagen de salida.
 *
 * @pre 0 <= @a a, @a b, @a min, @a max, 255
 * @pre @a a < @a b
 * @pre @a min < @a max
 *
 * Ejemplo de uso:
 * @code{.sh}
 * ./contraste ./imagen_original.pgm ./imagen_contraste_mod.pgm 64 192 32 224
 * @endcode
 *
 * Este ejemplo muestra cómo utilizar el ejecutable **Contraste** para modificar el contraste de una imagen.
 * La imagen original tenía un contraste en el intervalo [64,192], y la resultante en [32, 224].
 *
 * <div style="text-align: center;">
 *   <div style="display: inline-block; text-align: center; margin: 0 3em;">
 *     <img src="vacas.png" alt="Imagen Original" style="border: none;" />
 *     <br>
 *     <small>Imagen Original</small>
 *   </div>
 *   <div style="display: inline-block; text-align: center; margin: 0 3em;">
 *     <img src="Ex_Contraste.png" alt="Imagen Contraste" style="border: none;" />
 *     <br>
 *     <small>Imagen con el contraste modificado</small>
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
    int a,b;            // Intervalo de origen [a,b]
    int min, max;       // Intervalo final [min, max]

    Image image; // Imagen que cambiamos el contraste

    // Comprobamos validez de la llamada

    cout << "NUMPAR: " << argc << endl;
    if (argc !=7){
        cerr << "Error: Numero incorrecto de parametros.\n";
        cerr << "Uso: contraste <FichImagenOriginal> <FichImagenDestino> <a> <b> <min> <max>";
        exit (1);
    }

    // Recuperamos argumentos
    fich_orig = argv[1];
    fich_rdo = argv[2];
    a = atoi(argv[3]);
    b = atoi(argv[4]);
    min = atoi(argv[5]);
    max = atoi(argv[6]);

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

    // Mostrar los parametros de la Imagen
    cout << endl;
    cout << "Dimensiones de " << fich_orig << ":" << endl;
    cout << "   Imagen   = " << image.get_rows()  << " filas x " << image.get_cols() << " columnas " << endl;

	// Comprobamos los parámetros:
	bool positivos = 0<=a && 0<=min;
	bool dentro_rango = b<=255 && max<=255;
	bool orden = a<b && min<max;
	if (!(positivos && dentro_rango && orden)){
		cerr << "Error: Parametros erroreos." << endl;
		cerr << "El intervalo de entrada es [" << a << ", " << b << "]." << endl;
		cerr << "El intervalo de salida es [" << min << ", " << max << "]." << endl;
		return 1;
	}

    // Modificamos el contraste
    image.AdjustContrast(a, b, min, max);

    if (image.Save(fich_rdo))
        cout  << "La imagen se guardo en " << fich_rdo << endl;
    else{
        cerr << "Error: No pudo guardarse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }
}