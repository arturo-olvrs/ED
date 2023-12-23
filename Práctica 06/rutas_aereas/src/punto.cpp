/**
 * @file punto.cpp
 * @brief Fichero de implementacion del TDA Punto
 *
 * @author Arturo Olivares Martos
 * @author Daniel Hidalgo Chica
 */

#include "punto.h"

Punto::Punto(): latitud(0), longitud(0){}

Punto::Punto(double lat, double lon): latitud(lat), longitud(lon){}

double Punto::getLatitud() const{
	return latitud;
}

double Punto::getLongitud() const{
	return longitud;
}

void Punto::setLatitud(double lat){
	latitud = lat;
}

void Punto::setLongitud(double lon){
	longitud = lon;
}

bool Punto::operator==(const Punto &p) const{
    bool igual_long = (abs(longitud - p.longitud) < 1e-5);
    bool igual_lat = (abs(latitud - p.latitud) < 1e-5);
    return(igual_long && igual_lat);
}

ostream & operator<<(ostream & os, const Punto &p){
	os << "(" << p.getLatitud() << "," << p.getLongitud() << ")";
	return os;
}

istream & operator>>(istream & is, Punto &p){
	double lat, lon;
	char c;
	is >> c >> lat >> c >> lon >> c;
	p.setLatitud(lat);
	p.setLongitud(lon);
	return is;
}

pair<int, int> Punto::coordenadasMapa(int num_columnas, int num_filas) const {
    int col = (int) ((longitud + 180) * num_columnas / 360);
    int fila = (int) ((90 - latitud) * num_filas / 180);
    return pair<int, int>(fila, col);
	// TODO: Modificar Columnas filas
}

pair<int,int> Punto::punto_medio_en_mapa(const Punto & p, int num_columnas, int num_filas) const{
    pair<int,int> p1 = coordenadasMapa(num_columnas, num_filas);
    pair<int,int> p2 = p.coordenadasMapa(num_columnas, num_filas);
    return pair<int,int>((p1.first+p2.first)/2,(p1.second+p2.second)/2);
}

double Punto::angulo_en_mapa(const Punto & p, int num_columnas, int num_filas) const{
    double angle;
    pair<int,int> p1 = coordenadasMapa(num_columnas, num_filas);
    pair<int,int> p2 = p.coordenadasMapa(num_columnas, num_filas);
    if (p1.second != p2.second) angle = atan((p2.first-p1.first)/(double)(p2.second-p1.second));
    else if (p2.first > p1.first) angle = M_PI/2;
    else angle = -M_PI/2;

	if (p2.second < p1.second) angle += M_PI;
    return angle;
}
