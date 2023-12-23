/**
 * @file almacenRutas.cpp
 * @brief Fichero de implementación del TDA AlmacenRutas
 *
 *
 * @author Arturo Olivares Martos
 * @author Daniel Hidalgo Chica
 */

#include "almacenRutas.h"
using namespace std;

#define MAGIC_CAD "#Rutas"

AlmacenRutas::AlmacenRutas(const map<string, Ruta> &rutas) {
	this->rutas = rutas;
}

const Ruta& AlmacenRutas::getRuta(string codigo) {
	return rutas[codigo];
}

bool AlmacenRutas::existeRuta(string codigo) {
	return rutas.find(codigo) != rutas.end();
}

void AlmacenRutas::insertarRuta(const Ruta &ruta) {
	rutas.insert(pair<string, Ruta>(ruta.getCodigo(), ruta));
}

void AlmacenRutas::eliminarRuta(string codigo) {
	rutas.erase(codigo);
}

int AlmacenRutas::getNumRutas() const {
	return rutas.size();
}

ostream & operator<<(ostream & os, const AlmacenRutas & ar) {

	//os << MAGIC_CAD << endl;

	AlmacenRutas::const_iterator it;
	for (it = ar.begin(); it != ar.end(); ++it) {
		os << *it << endl;
	}
	return os;
}

istream & operator>>(istream & is, AlmacenRutas & ar) {
	Ruta ruta;

	string cadena;
	is >> cadena;

	if (cadena != MAGIC_CAD) {
		exit (-1);
	}

	while (is >> ruta) {
		ar.insertarRuta(ruta);
	}

	return is;
}