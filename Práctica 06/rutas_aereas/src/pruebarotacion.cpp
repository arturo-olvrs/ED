/**
 * @file pruebarotacion.cpp
 *
 * @author Arturo Olivares Martos
 * @author Daniel Hidalgo Chica
 *
 *
 * @brief Archivo de prueba para la clase Imagen, que prueba el método Imagen::Rota
 *
 * @param img_entrada Nombre de la imagen de entrada, a rotar.
 * @param angulo_grados Ángulo de rotación en grados.
 * @param img_salida Nombre de la imagen de salida, rotada.
 *
 * Un ejemplo de ejecución es:
 * Ejemplo de uso:
 * @code{.sh}
 * pruebarotacion avion.ppm 45 avion_45.ppm
 * @endcode
 *
 * Este ejemplo muestra cómo utilizar el ejecutable **pruebarotacion** para rotar una imagen dada.
 *
 * <div style="text-align: center;">
 *   <div style="display: inline-block; text-align: center; margin: 0 3em;">
 *   //TODO: Poner imagen de entrada
 *     <img src="vacas.png" alt="Imagen Original" style="border: none;" />
 *     <br>
 *     <small>Imagen Original</small>
 *   </div>
 *   <div style="display: inline-block; text-align: center; margin: 0 3em;">
 *   // TODO: Poner imagen de salida
 *     <img src="Ex_Recortada.png" alt="Imagen Rotada" style="border: none;" />
 *     <br>
 *     <small>Imagen Rotada</small>
 *   </div>
 * </div>
 */
#include "imagen.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;


int main(int argc, char * argv[]){

	if (argc!=4){
		cout<<"Los parametros son :"<<endl;
		cout<<"1 - La imagen de entrada"<<endl;
		cout<<"2 - El angulo de rotación en grados"<<endl;
		cout<<"3 - El nombre de la imagen de salida"<<endl;
		cout << "Uso: " << argv[0] << " <img_entrada> <angulo_grados> <img_salida>" << endl;
		return -1;
	}

	Imagen I;
	I.LeerImagen(argv[1]);

	double angulo=atof(argv[2]);
	angulo = angulo*(M_PI)/180;
	Imagen Iout=I.Rota(angulo);
	Iout.EscribirImagen(argv[3]);
}