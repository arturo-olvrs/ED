/**
 * @file pruebapegado.cpp
 *
 * @author Arturo Olivares Martos
 * @author Daniel Hidalgo Chica
 *
 * @brief Archivo de prueba para la clase Imagen, que prueba el método Imagen::PutImagen
 *
 * @param img_fondo Nombre de la imagen de fondo, donde se va a pegar la imagen a pegar.
 * @param img_pegar Nombre de la imagen a pegar.
 * @param mascara Nombre de la máscara de la imagen a pegar.
 * @param img_salida Nombre de la imagen de salida, con la imagen pegada.
 * @param fil Fila donde se va a pegar la imagen.
 * @param col Columna donde se va a pegar la imagen.
 * @param TipoPegado Tipo de pegado. 0: Opaco 1: Blending
 *
 * // Ambos positivos
 * @pre 0<=@a fil
 * @pre 0<=@a col
 *
 * // Que quepa en la imagen
 * @pre fil+img_pegar.getFilas()<=img_fondo.getFilas()
 * @pre col+img_pegar.getColumnas()<=img_fondo.getColumnas()
 *
 * // Que la máscara sea válida
 * @pre img_pegar.getFilas()==mascara.getFilas()
 * @pre img_pegar.getColumnas()==mascara.getColumnas()
 *
 * Un ejemplo de ejecución es:
 * Ejemplo de uso:
 * @code{.sh}
 * pruebapegado fondo.ppm pegar.ppm mascara.pgm salida.ppm 10 10 0
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
 *   // TODO: Poner imagen de salida blending
 *     <img src="Ex_Recortada.png" alt="Imagen Superpuesta Blending" style="border: none;" />
 *     <br>
 *     <small>Imagen Superpuesta usando el tipo de pegado Blending</small>
 *   </div>
 *   <div style="display: inline-block; text-align: center; margin: 0 3em;">
 *   // TODO: Poner imagen de salida opaco
 *     <img src="Ex_Recortada.png" alt="Imagen Superpuesta Opaco" style="border: none;" />
 *     <br>
 *     <small>Imagen Superpuesta usando el tipo de pegado Opaco</small>
 *   </div>
 * </div>
 */

#include "imagen.h"
#include <iostream>
#include <cstdlib>

using namespace std;



int main(int argc, char * argv[]){
	if (argc!=8){
		cout<<"Los parametros son :"<<endl;
		cout<<"1 - La imagen de fondo"<<endl;
		cout<<"2 - La imagen a pegar"<<endl;
		cout<<"3 - La máscara de la imagen a pegar"<<endl;
		cout<<"4 - El nombre de la imagen de salida"<<endl;
		cout<<"5 - La fila donde pegar"<<endl;
		cout<<"6 - La columna donde pegar"<<endl;
		cout<<"7 - 0: Pegado Opaco 1: Pegado Blending"<<endl;
		cout << "Uso: " << argv[0] << " <img_fondo> <img_pegar> <mascara> <img_salida> <fil> <col> <TipoPegado>" << endl;
		return -1;
	}
	Imagen I,Ip;
	I.LeerImagen(argv[1]);  // Imagen donde voy a pegar
	Ip.LeerImagen(argv[2],argv[3]);     // Imagen que voy a pegar

	int i,j;    // Pasamos fila y columnas a enteros
	i=atoi(argv[5]); j=atoi(argv[6]);

	Tipo_Pegado tp; //variable de tipo Tipo_Pegado que es un enumerado con los valores OPACO y BLENDING
	int au= atoi(argv[7]);
	if (au==0) tp=OPACO;
	else if (au==1) tp=BLENDING;
	else {
		cout<<"El valor de pegado debe ser 0 o 1"<<endl;
		return -1;
	}

	// Pegamos la imagen
	I.PutImagen(i,j,Ip,tp);

	// Guardamos la imagen
	I.EscribirImagen(argv[4]);

	return 0;
}  