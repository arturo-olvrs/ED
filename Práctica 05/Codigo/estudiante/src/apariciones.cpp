/**
 * @brief Programa que calcula el número de apariciones de un carácter en un diccionario
 * @file apariciones.cpp
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
    if (argc != 3 || strlen(argv[2]) != 1) {
        cerr << "Use: " << argv[0] << " <filename>" << " <char_to_find>";
        exit(1);
    }

    char char_to_find = *argv[2]; // Como es un puntero a char que guarda el caracter, deferenciamos

    Dictionary dic(argv[1]);

    cout << "El carácter " << char_to_find << " aparece " << dic.getOcurrences(char_to_find) << " veces en el diccionario "
         << argv[0] << "." << endl;

    return 0;
}