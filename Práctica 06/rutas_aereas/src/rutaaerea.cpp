/**
 * @file rutaaerea.cpp
 *
 * @author Arturo Olivares Martos
 * @author Daniel Hidalgo Chica
 *
 * @brief Programa que muestra por pantalla las rutas aereas de una aerolinea.
 *
 * Como argumento, recibe un almacen de rutas,
 * y permite al usuario elegir una de ellas para mostrarla en un mapa del mundo.
 *
 * Se muestra por pantalla el nombre de los paises por los que pasa la ruta y, en la imagen del mapa del mundo,
 * se muestran las banderas de los paises por los que pasa la ruta y un avion que va de un pais a otro.
 *
 * @param fichero_paises Fichero con la informacion de los paises
 * @param mapa_mundo Nombre de la imagen con el mapa del mundo
 * @param dir_banderas Directorio con las banderas
 * @param almacen_rutas Fichero con el almacen de rutas
 * @param avion Nombre de la imagen con el avion. Tipo PPM
 * @param mascara_avion Nombre de la imagen de la mascara del avion. Tipo PGM
 *
 *
 * Un ejemplo de ejecución es:
 * Ejemplo de uso:
 * @code{.sh}
 * ./rutaaerea ./datos/paises.txt ./datos/imagenes/mapas/mapa1.ppm ./datos/imagenes/banderas/ ./datos/almacen_rutas.txt ./datos/imagenes/aviones/avion3.ppm ./datos/imagenes/aviones/mascara_avion3.pgm
 * Las rutas:
 * R1 5 (34.5204,69.2008) (52.5079,13.4261) (7.40665,12.3446) (-0.186596,-78.4305) (40.4005,-3.59165)
 * R2 8 (58.6954,-96) (35.0869,-103.723) (-12.0553,-77.0452) (40.4005,-3.59165) (37.9438,104.136) (-27.7871,133.281) (35.6735,139.71) (62.8865,61.5512)
 * R3 5 (17.2464,-19.6706) (4.28364,-74.224) (51.5289,-0.101599) (62.8865,61.5512) (37.9438,104.136)
 * R4 11 (14.4225,-87.6343) (48.8589,2.34706) (24.7259,46.8225) (58.6954,-96) (35.0869,-103.723) (-12.0553,-77.0452) (40.4005,-3.59165) (37.9438,104.136) (-27.7871,133.281) (35.6735,139.71) (62.8865,61.5512)
 * R5 5 (52.7608,8.74761) (-19.0519,29.1528) (-34.6159,-58.4333) (58.6954,-96) (52.7608,8.74761)
 *
 * Introduzca el codigo de una ruta
 * R1
 * Afganistan Alemania Camerun Ecuador España
 *
 * @endcode
 *
 * El programa genera la siguiente imagen:
 *
 * <div style="display: inline-block; text-align: center; margin: 0 3em;">
 *   <img src="R1_Mapa.png" alt="Imagen Ruta 1" style="border: none;" />
 *   <br>
 *   <small>Imagen Generada para la Ruta 1</small>
 * </div>
 */

#include "almacenRutas.h"
#include "paises.h"
#include "imagen.h"
#include <fstream>

#define RESULT_PATH "./output/"

int main (int argc, char* argv[]) {
    if (argc!=7){
        cout<<"Los parametros son:"<<endl;
        cout<<"1 - Fichero con la informacion de los paises"<<endl;
        cout<<"2 - Nombre de la imagen con el mapa del mundo"<<endl;
        cout<<"3 - Directorio con las banderas"<<endl;
        cout<<"4 - Fichero con el almacen de rutas"<<endl;
        cout<<"5 - Nombre de la imagen con el avion"<<endl;
        cout<<"6 - Nombre de la imagen de la mascara del avion"<<endl;

		cout << "Uso: " << argv[0] << " <fichero_paises> <mapa_mundo> <dir_banderas> <almacen_rutas> <avion> <mascara_avion>" << endl;

        return -1;
    }

	ifstream file;
	file.open(argv[1]);
	Paises paises; // Leemos los paises
	if (file)
		file >> paises;
	else {
		cout << "Error de apertura del fichero" << argv[1] << endl;
		return -1;
	}
	file.close();


	Imagen mapa;
	mapa.LeerImagen(argv[2]);

	Imagen avion;
	avion.LeerImagen(argv[5], argv[6]); // Leemos con la máscara


    AlmacenRutas Ar; // Leemos el almacen de rutas
    file.open (argv[4]);
	if (file){
		file >> Ar;
	}
	else {
		cout << "Error de apertura del fichero " << argv[4] << endl;
		return -1;
	}
	file.close();

	// Muestra todas las rutas disponibles
    cout<<"Las rutas: "<<endl;
	cout << Ar << endl;
    cout<<"Introduzca el codigo de una ruta"<<endl;
    string id_ruta; // Ruta
    cin>>id_ruta;
    // Comprobación de que "id_ruta" es una ruta valida
    if (!Ar.existeRuta(id_ruta)) {
        cout << "La ruta no existe" << endl;
        return 1;
    }
    Ruta route=Ar.getRuta(id_ruta);

    // Ya tenemos la ruta, ahora vamos a mostrarla
    string dir_banderas = argv[3];

    Ruta::iterator it_r=route.begin();
    Punto point1, point2;
    pair<int,int> coord_point1, coord_point2, coord_point_midpoint;
    double orientation_angle;
    Imagen avion_rotado;
    Pais pais;
    Imagen bandera;

    while (it_r != route.end()) {
        point1=*it_r;
        coord_point1 = point1.coordenadasMapa(mapa.getColumnas(), mapa.getFilas());

        // Extraigo país
        Paises::iterator pos_pais_point1 = paises.find(point1);
        if (pos_pais_point1 == paises.end()) {
            cout << "No pudo encontrarse el pais que tiene como punto " << point1 << endl;
            exit(-1);
        }
        pais = *(paises.find(point1));

        // Pongo bandera en el mapa
        string nombre_bandera = dir_banderas + "/" + pais.getBandera();
        bandera.LeerImagen(nombre_bandera.c_str());
        Tipo_Pegado tp_bl = BLENDING;
        mapa.PutImagen(coord_point1.first, coord_point1.second, bandera, tp_bl);
        // Imprimo por pantalla el nombre del país
        cout << pais.getNombre() << " ";

        // Leo siguiente punto
        ++it_r;
        if (it_r != route.end()) {
            point2=*it_r;
            coord_point2 = point2.coordenadasMapa(mapa.getColumnas(), mapa.getFilas());
            coord_point_midpoint = point1.punto_medio_en_mapa(point2, mapa.getColumnas(), mapa.getFilas());
            orientation_angle = point1.angulo_en_mapa(point2, mapa.getColumnas(), mapa.getFilas());

            // Pego los 3 aviones correspondientes
            Tipo_Pegado tp_op = OPACO;
            avion_rotado = avion.Rota(orientation_angle);
            mapa.PutImagen(coord_point_midpoint.first, coord_point_midpoint.second, avion_rotado, tp_op);
            mapa.PutImagen(coord_point1.first, coord_point1.second, avion_rotado, tp_op);
            mapa.PutImagen(coord_point2.first, coord_point2.second, avion_rotado, tp_op);
        } // if (it_r != route.end())
    } // while (it_r != route.end())

    string result_path = RESULT_PATH + route.getCodigo() + string("_Mapa.ppm");
    mapa.EscribirImagen(result_path.c_str());


	cout << endl << endl;
    return 0;
}