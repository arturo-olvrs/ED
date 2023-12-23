/**
 * @file paises.cpp
 * @brief Fichero de implementación del TDA Paises
 *
 *
 * @author Arturo Olivares Martos
 * @author Daniel Hidalgo Chica
 */

#include "paises.h"
#include <sstream>

const string CAD_MAGS[4] = {"# Latitud", "Longitud", "Pais", "Bandera"};

Paises::Paises(const set<Pais> &paises) {
	datos = paises;
}

int Paises::size() const {
	return datos.size();
}

const set<Pais>& Paises::getDatos() const {
	return datos;
}

void Paises::insertar(const Pais &pais) {
	datos.insert(pais);
}

void Paises::eliminar(const Pais &pais) {
	datos.erase(pais);
}

void Paises::clear() {
    datos.clear();
}

Paises::iterator Paises::find(const Pais &pais) const {
	return datos.find(pais);
}

Paises::iterator Paises::find(const Punto &punto) const {
	Paises::iterator it;
	for (it = this->begin(); it != this->end(); ++it) {
		if ((*it).getPunto()==punto) {
			return it;
		}
	}
	return this->end();
}


ostream &operator<<(ostream &os, const Paises &paises) {

	for (int i = 0; i < 4; i++) {
		os << CAD_MAGS[i] << "\t";
	}
	os << endl;

	Paises::iterator it;
	for (it = paises.begin(); it != paises.end(); ++it) {
		os << *it << endl;
	}
	return os;
}

istream& operator>>(istream& is, Paises& paises) {
    double longitud, latitud;
    string nombre, bandera;

    // Leer una línea del archivo
    string line;
    while (getline(is, line)) {
        if (line.empty() || line[0] == '#') {
            continue;  // Salta las líneas de comentarios o vacías
        }

        // Utilizar un stringstream para extraer campos
        istringstream iss(line);
        // Leer los campos uno por uno
        iss >> latitud >> longitud >> nombre >> bandera;

        // Creamos un objeto Pais y lo añadimos al conjunto
        // de paises
        Punto point(latitud, longitud);
        Pais pais(nombre, bandera, point);
        paises.insertar(pais);
    }
    return is;
}

