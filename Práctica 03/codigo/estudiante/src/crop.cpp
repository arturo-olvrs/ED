/**
 * @file crop.cpp
 * @brief Recorta una imagen dada.
 *
 * @param FichImagenOriginal Fichero de la imagen original.
 * @param FichImagenDestino Fichero donde se va a guardar la imagen con el zoom aplicado.
 * @param fila Fila de la esquina superior izquierda de la zona de recorte.
 * @param columna Columna de la esquina superior izquierda de la zona de recorte.
 * @param filas_sub altura en filas del recorte
 * @param columnas_sub anchura en columnas del recorte
 *
 * @pre (@a fila, @a columna) debe ser una posición válida.
 * @pre @a Lado > 0
 * @pre La zona de recorte debe estar entera incluida en la imagen original.
 *
 * Ejemplo de uso:
 * @code{.sh}
 * ./crop ./imagen_original.pgm ./imagen_recortada.pgm 85 145 60 80
 * @endcode
 *
 * Este ejemplo muestra cómo utilizar el ejecutable **Crop** para recortar una imagen.
 * Se recorta desde la esquina (85, 145), y se recortan 60 filas de altura y 80 columnas de anchura.
 *
 * <div style="text-align: center;">
 *   <div style="display: inline-block; text-align: center; margin: 0 3em;">
 *     <img src="vacas.png" alt="Imagen Original" style="border: none;" />
 *     <br>
 *     <small>Imagen Original</small>
 *   </div>
 *   <div style="display: inline-block; text-align: center; margin: 0 3em;">
 *     <img src="Ex_Recortada.png" alt="Imagen Recortada" style="border: none;" />
 *     <br>
 *     <small>Imagen Recortada</small>
 *   </div>
 * </div>
 */

#include <iostream>
#include <cstdlib>
#include <image.h>

using namespace std;

int main (int argc, char* argv[]) {
    char *fich_orig, *fich_rdo; // Nombres de los ficheros
    int fila,col; // Fila y columna donde empezar el recorte
    int filas_sub, cols_sub;

    Image image; // Imagen que recortamos
    Image recorte; // Recorte que devuelve el programa

    // Comprobamos validez de la llamada

    if (argc !=7){
        cerr << "Error: Numero incorrecto de parametros.\n";
        cerr << "Uso: crop <FichImagenOriginal> <FichImagenDestino> <fila> <col> <filas_sub> <cols_sub>";
        exit (1);
    }

    // Recuperamos argumentos
    fich_orig = argv[1];
    fich_rdo = argv[2];
    fila = atoi(argv[3]);
    col = atoi(argv[4]);
    filas_sub = atoi(argv[5]);
    cols_sub = atoi(argv[6]);

    // Mostramos argumentos
    cout << endl;
    cout << "Fichero origen: " << fich_orig << endl;
    cout << "Fichero resultado: " << fich_rdo << endl;
    cout << "Fila donde comienza el recorte:" << fila << endl;
    cout << "Columna donde comienza el recorte:" << col << endl;
    cout << "Altura en filas del recorte:" << filas_sub << endl;
    cout << "Anchura en columnas del recorte:" << cols_sub << endl;

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


	// Comprobar los parámetros

	// Coordenada de inicio
	bool fil_ok = 0<= fila && fila < image.get_rows();
	bool col_ok = 0<= col && col < image.get_cols();
	if (!(fil_ok && col_ok)){
		cerr << "Error: Coordenada de inicio no valida." << endl;
		cerr << "Terminando la ejecucion del programa." << endl;
		return 1;
	}

	// Coordenada final
	fil_ok = 0<= fila+filas_sub && fila+filas_sub <= image.get_rows();
	col_ok = 0<= col+cols_sub && col+cols_sub <= image.get_cols();
	if (!(fil_ok && col_ok)){
		cerr << "Error: Zona descrita no está totalmente incluida." << endl;
		cerr << "Terminando la ejecucion del programa." << endl;
		return 1;
	}

    // Calculamos el recorte
    recorte = image.Crop(fila, col, filas_sub, cols_sub);

    if (recorte.Save(fich_rdo))
        cout  << "La imagen se guardo en " << fich_rdo << endl;
    else{
        cerr << "Error: No pudo guardarse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }
}