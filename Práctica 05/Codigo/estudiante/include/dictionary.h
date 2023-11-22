/**
 * @file dictionary.h
 * @brief TDA Dictionary.
 * @author Arturo Olivares Martos
 * @author Daniel Hidalgo Chica
 */

#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

#include <iostream>
#include <set>
#include <vector>
#include <string>

using namespace std;

/**
 * @brief TDA Dictionary
 *
 * Una instancia @e d del tipo de dato abstracto Dictionary sobre el tipo @c string es un objeto
 * formado por un conjunto de palabras de tipo @c string ordenadas alfabéticamente no repetidas.
 */

class Dictionary {
private:
	/**
	 * @brief Conjunto de palabras ordenadas alfabéticamente no repetidas.
	 */
    set <string> words;
public:
	/**
	 * @brief Constructor por defecto de la clase.
	 *
	 *  Crea un diccionario vacío.
	 */
    Dictionary();

	/**
	 * @brief Constructor de copia de la clase.
	 *
	 * Crea un diccionario a partir de otro.
	 * @param othr  Diccionario a copiar.
	 */
    Dictionary(const Dictionary& othr);

	/**
	 * @brief Constructor de la clase a partir de un fichero.
	 * @param file_name Nombre del fichero.
	 */
	Dictionary	(const string & file_name);


	/**
	 * @brief Comprueba si una palabra existe en el diccionario.
	 * @param s  Palabra a buscar.
	 * @retval true Si la palabra existe en el diccionario.
	 * @retval false Si la palabra no existe en el diccionario.
	 */
	bool exists(const string &s) const;

	/**
	 * @brief Inserta una palabra en el diccionario.
	 * @param s  Palabra a insertar.
	 * @retval true Si la palabra se ha insertado (no existía).
	 * @retval false Si la palabra no se ha insertado (ya existía).
	 */
    bool insert(const string &s);

	/**
	 * @brief Borra un elemento del diccionario.
	 * @param s  Palabra a borrar.
	 * @retval true Si la palabra se ha borrado (ya existía).
	 * @retval false Si la palabra no se ha borrado.
	 */
    bool erase(const string &s);

	/**
	 * @brief Borra todos los elementos del diccionario.
	 *
	 * Elimina todos los elementos del diccionario, dejándolo vacío.
	 *
	 * @post El diccionario es vacío.
	 */
    void clear();

	/**
	 * @brief Comprueba si el diccionario está vacío.
	 *
	 * @retval true Si el diccionario está vacío.
	 * @retval false Si el diccionario no está vacío.
	 */
    bool empty() const;

	/**
	 * @brief Devuelve el número de palabras del diccionario.
	 * @return  Número de palabras del diccionario.
	 */
    unsigned int size() const;

	/**
	 * @brief Devuelve un vector con las palabras de una longitud dada.
	 * @param length  Longitud de las palabras a buscar.
	 * @return  Vector con las palabras de la longitud dada.
	 */
    vector<string> wordsOfLength(int length) const;

	/**
	 * @brief Devuelve el número de ocurrencias de un carácter en el diccionario.
	 * @param c  Carácter a buscar.
	 * @return  Número de ocurrencias del carácter en el diccionario.
	 */
    int getOcurrences(char c) const;

	/**
	 * @brief Une dos diccionarios en uno.
	 * @param dic  Diccionario a unir.
	 * @post El diccionario actual es la unión de los dos diccionarios.
	 */
    void anade(const Dictionary &dic);

	/**
	 * @brief Sobrecarga del operador de lectura de flujo.
	 * @param is  Flujo de entrada.
	 * @param dic  Diccionario en el que se almacenan las palabras leídas.
	 * @return  Referencia al flujo de entrada.
	 */
    friend istream& operator>>(istream &is, Dictionary &dic);

	/**
	 * @brief Sobrecarga del operador de escritura de flujo.
	 * @param os  Flujo de salida.
	 * @param dic  Diccionario del que se escriben las palabras.
	 * @return Referencia al flujo de salida.
	 */
	friend ostream& operator<<(ostream &os, const Dictionary& dic);

	/**
	 * @brief Clase para iterar sobre el diccionario
	 */
	class iterator{
		private:
			set<string>::iterator it;
		public:
			iterator & operator++(){++it;return *this;}
			iterator & operator--(){--it;return *this;}
			bool operator==(const iterator &i) const{return it==i.it;}
			bool operator!=(const iterator &i) const{return it!=i.it;}
			const string& operator* (){return *it;}
			friend class Dictionary;
	};

	/**
	 * @brief Devuelve un iterador al principio del diccionario.
	 * @return  Iterador al principio del diccionario.
	 */
	iterator begin() const {
		iterator i;
		i.it = words.begin();
		return i;
	}

	/**
	 * @brief Devuelve un iterador al final del diccionario.
	 * @return  Iterador al final del diccionario.
	 */
	iterator end() const {
		iterator i;
		i.it = words.end();
		return i;
	}

private:

	/**
	 * @brief Carga el diccionario desde un fichero.
	 * @param file_name  Nombre del fichero.
	 */
	void LoadDictionary(const string &file_name);
};


/**
 * @brief Función que cuenta el número de ocurrencias de un carácter en una palabra.
 * @param c Carácter a buscar.
 * @param word Palabra en la que buscar.
 * @param pos Posición a partir de la cual buscar.
 * @return Número de ocurrencias del carácter en la palabra.
 */
int count_ocurrences(char c, const string& word, size_t pos = 0);

#endif
