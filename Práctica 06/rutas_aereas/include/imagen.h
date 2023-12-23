/**
 * @file imagen.h
 * @brief Fichero cabecera para el TDA Imagen
 *
 * Permite la manipulación de imágenes
 *
 *
 * @author Arturo Olivares Martos
 * @author Daniel Hidalgo Chica
 */

#ifndef PRACTICAFINAL_IMAGEN_H
#define PRACTICAFINAL_IMAGEN_H

using namespace std;
#include <vector>
#include <string>

/**
 * @brief Estrucutra para representar un pixel de una imagen.
 *
 * Un pixel es un conjunto de 3 componentes RGB y un valor de transparencia.
 */
struct Pixel{
	/**
	 * @brief Componente R de RGB del pixel
	 */
	unsigned char r;

	/**
	 * @brief Componente G de RGB del pixel
	 */
	unsigned char g;

	/**
	 * @brief Componente B de RGB del pixel
	 */
	unsigned char b;

	/**
	 * @brief Transparencia del pixel.
	 *
	 * 0 es totalmente transparente y 255 totalmente opaco
	 */
	unsigned char transp;
};

/**
 * @brief Enumerado para representar el tipo de pegado de una imagen sobre otra
 *
 * OPACO: Se pega la imagen sin transparencia
 * BLENDING: Se pega la imagen con transparencia
 */
enum Tipo_Pegado {OPACO, BLENDING};


/**
 * @brief TDA Imagen
 *
 * Una instancia del tipo de datos abstracto @c Imagen es un objeto
 * que representa una imagen. Este conjunto
 * es un vector de vectores de píxeles.
 *
 */
class Imagen {

private:
    /**
     * @brief Matriz dinámica donde alojaremos los píxeles de la imagen
     */
    Pixel **data;
    /**
     * @brief Número de filas de la imagen
     */
    int nf;
    /**
     * @brief Número de columnas de la imagen
     */
    int nc;
    /**
     * @brief Método privado que borra la imagen
     */
    void borrar();
    /**
     * @brief Método privado que copia una imagen
     * @param img Imagen a copiar
     */
    void copiar(const Imagen &img);

    Pixel media_pixeles(const Pixel &p1, const Pixel &p2) const;
public:

	/**
	 * @brief Constructor por defecto
	 *
	 * Crea una imagen vacía
	 */
	Imagen();

	/**
	 * @brief Constructor con parámetros
	 *
	 * Crea una imagen con el número de filas y columnas indicadas.
	 * Los píxeles se inicializan a 0,0,0,0 (negro y transparente).
	 *
	 * @param filas Número de filas de la imagen
	 * @param columnas Número de columnas de la imagen
	 * @pre @a filas >= 0
	 * @pre @a columnas >= 0
	 */
	Imagen(int filas, int columnas);


    /**
     * @brief Constructor de copia de una imagen
     * @param img
     */
    Imagen(const Imagen &img);

	/**
	 * @brief Operador de acceso
	 *
	 * @param i Fila a acceder
	 * @param j Columna a acceder
	 * @return Referencia al pixel de la posición (i,j)
	 * @pre @a 0<=filas<=getFilas()
	 * @pre @a 0<=columnas<=getColumnas()
	 */
	Pixel & operator()(int i, int j);

	/**
	 * @brief Operador de acceso constante
	 *
	 * @param i Fila a acceder
	 * @param j Columna a acceder
	 * @return Referencia constante al pixel de la posición (i,j)
	 */
	const Pixel & operator()(int i, int j) const;

	/**
	 * @brief Método que informa del número de filas de la imagen
	 * @return Número de filas de la imagen
	 */
	int getFilas() const {return nf;};

	/**
	 * @brief Método que informa del número de columnas de la imagen
	 * @return Número de columnas de la imagen
	 */
	int getColumnas() const{return nc;};

	/**
	 * @brief Método que escribe una imagen en disco en el archivo dado por @a nombre.
	 * @param img_path archivo donde guardar la imagen.
	 */
	void EscribirImagen (const char img_path[]) const;

	/**
	 * @brief Método que lee una imagen del disco desde el archivo dado por @a nombre.
	 * @param img_path archivo desde donde leer la imagen.
	 * @param nombre_mascara archivo donde se encuentra la máscara, en caso de que haya.
	 */
	void LeerImagen (const char img_path[], const string &nombre_mascara="");

	/**
	 * @brief Método que resetea la transparencia de todos los píxeles de la imagen a 255 (opaco)
	 */
	void LimpiarTransparencia();

	/**
	 * @brief Método que pega una imagen sobre otra
	 * @param i Fila superior donde empieza el pegado de la imagen
	 * @param j Columna izquierda donde empieza el pegado de la imagen
	 * @param img Imagen a pegar
	 * @param tp Tipo de pegado. Por defecto es OPACO
	 * @pre @a 0<=i,j
	 * @pre @a 0<=i+img.getFilas()<=getFilas()
	 * @pre @a 0<=j+img.getColumnas()<=getColumnas()
	 */
	void PutImagen(int i, int j, const Imagen &img, Tipo_Pegado tp=OPACO);


	/**
	 * @brief Método que extrae una imagen de la imagen actual
	 * @param i Fila donde empieza la imagen a extraer
	 * @param j Columna donde empieza la imagen a extraer
	 * @param nf Número de filas de la imagen a extraer
	 * @param nc Número de columnas de la imagen a extraer
	 * @return Imagen extraída
	 * @pre @a 0<=i,j
	 * @pre @a 0<=i+nf<=getFilas()
	 * @pre @a 0<=j+nc<=getColumnas()
	 */
	Imagen ExtraerImagen(int i, int j, int nf, int nc) const;

    /**
     * @brief Operador de asignación
     * @param img Imagen a asignar
     * @return
     */
    Imagen &operator=(const Imagen &img);

	/**
	 * @brief Método que rota una imagen
	 * @param rads Radianes a rotar la imagen
	 * @return Imagen rotada
	 */
    Imagen Rota(double rads) const;
};


#endif //PRACTICAFINAL_IMAGEN_H
