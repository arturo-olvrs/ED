/**
 * @brief Programa que muestra las palabras de un diccionario de una longitud dada.
 * @file palabras_longitud.cpp
 * @author Arturo Olivares Martos
 * @author Daniel Hidalgo Chica
 */

#include "dictionary.h"
#include <fstream>

using namespace std;
int main(int argc, char* argv[]) {
    // Check the arguments
    if (argc != 3) {
        cerr << "Use: " << argv[0] << " <filename>" << " <word_length>";
        exit(1);
    }

    int word_length = stoi(argv[2]);
    Dictionary dic(argv[1]);

    vector<string> wol = dic.wordsOfLength(word_length);

    // Print words
    for (int i = 0; i != wol.size(); i++)
        cout << wol[i] << endl;

    return 0;
}