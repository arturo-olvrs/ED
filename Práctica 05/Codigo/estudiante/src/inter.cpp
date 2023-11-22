/**
 * @brief Programa que calcula la intersección de dos guías de teléfono.
 *
 * Dadas dos listas telefónicas, calcula la intersección de ambas y la muestra por pantalla.
 * La intersección se define como los elementos comunes a ambas listas.
 * @file inter.cpp
 * @author Arturo Olivares Martos
 * @author Daniel Hidalgo Chica
 */

#include "guiatlf.h"
#include <iostream>
#include <fstream>

using namespace std;

int main (int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Uso: " << argv[0] << " <filename_guia1>" << " <filename_guia2>" << endl;
        exit(1);
    }

    ifstream is1, is2;
    is1.open(argv[1]);
    is2.open(argv[2]);

    if (!(is1.is_open() && is2.is_open())) {
        cerr << "Error al abrir alguno de los ficheros" << argv[1] << "" << argv[2] << endl;
    }
    Guia_Tlf guia1, guia2;
    is1 >> guia1;
    is2 >> guia2;
    Guia_Tlf guia_inter(guia1.interseccion(guia2));
    cout << guia_inter;

    return 0;
}
