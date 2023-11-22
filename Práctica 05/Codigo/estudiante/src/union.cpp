/**
 * @brief Programa que une dos diccionarios.
 *
 * Dados dos diccionarios, se imprimen todos los elementos que pertenecen a alguno de los dos.
 * @file union.cpp
 * @author Arturo Olivares Martos
 * @author Daniel Hidalgo Chica
 */
#include "dictionary.h"
#include <fstream>
#include <cstring>
#include <string>

using namespace std;
int main(int argc, char* argv[]) {
    // Check the arguments
    if (argc != 3) {
        cerr << "Use: " << argv[0] << " <dic_1_file_name>" << " <dic_2_file_name>";
        exit(1);
    }

    Dictionary dic1(argv[1]), dic2(argv[2]);

    dic1.anade(dic2); // Unimos sobre dic1

    cout << "La unión de los diccionarios es: " << endl << dic1 << endl;

    return 0;
}
