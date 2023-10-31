/*!
 * @file image.h
 * @brief Cabecera para la clase Image
 */

#ifndef _IMAGEN_H_
#define _IMAGEN_H_


#include <cstdlib>
#include "imageIO.h"


/**
 * @typedef byte
 * @brief Tipo de dato que representa un byte sin signo.
 *
 * Contiene el valor de un pixel de una imagen de la clase Image.
 */
typedef unsigned char byte;


/**
 * @enum LoadResult
 * @brief Enumeración que representa el resultado de cargar una imagen PGM.
 *
 * Esta enumeración se utiliza para indicar el resultado de la operación de carga
 * de una imagen PGM. Puede tener uno de los siguientes valores:
 *
 * - LoadResult::SUCCESS: La operación de carga se realizó con éxito.
 * - LoadResult::NOT_PGM: El archivo no es un archivo PGM válido.
 * - LoadResult::READING_ERROR: Se produjo un error al leer el archivo.
 */
enum LoadResult: unsigned char {
    SUCCESS,
    NOT_PGM,
    READING_ERROR
};


/**
  @brief T.D.A. Imagen

  Una instancia del tipo de dato abstracto Imagen nos permite almacenar imágenes de intensidades.

  El TDA Imagen proporciona además distintas herramientas para la manipulación de dichas imágenes.

  Para poder usar el TDA Imagen se debe incluir el fichero

  \#include <Imagen.h>

**/

class Image{

    /**
         @page page_repImagen Representación del TDA Imagen

         @section sec_Image_A Representación secuencial.

         Para representar una imagen hemos escogido una matriz dinámica de Bytes (unsigned char).

         En particular, de las diferentes implementaciones posibles hemos escogido
         tener dos vectores dinámicos: el vector byte *img[rows] y otro vector de bytes de tamaño
         rows*cols que comience en img[0] (que será, esencialmente, resultado de colocar secuencialmente en memoria
         las filas de la matriz abstracta). Así, en un primer momento, impusimos que el elemento i-ésimo del vector img, apunte
         a la casilla (i*cols)-ésima del otro vector, y tenemos que, para referirnos al elemento (i,j) de nuestra
         matriz abstracta no hacemos más que img[i][j].

         Nos referimos a ésta como la implementación "secuencial" del tipo porque las filas en el vector "desenrollado"
         aparecen en el orden natural: la fila (i)-ésima de la imagen, aparece justo antes de la fila (i+1)-ésima, y justo
         después de la fila (i-1)-ésima.

         Veamos que esto no tiene por qué ser así.

         @section sec_Image_B Representación no necesariamente secuencial.
         Motivados por problemas de eficiencia a la hora de intercambiar unas filas de la matriz por otras,
         decidimos reinterpretar la representación del tipo "desordenando las filas". No reservamos nueva memoria
         (optando por realmente separar la matriz en memoria usando una implementación de matriz dinámica como
         vector de vectores dinámicos) sino que dejamos de imponer que la casilla i-ésima del vector img apuntase
         a la casilla (i*cols)-ésima de la matriz, permitiendo que apunte a cualquier otra de las originales filas.

         Sin embargo, esta idea nos inclina al uso de un nuevo campo de la clase: "origin_ptr", porque de lo contrario
         no tendríamos controlada la primera casilla del vector "desenrrollado", y la necesitamos, al menos, para
         la destrucción del objeto Imagen (también tendríamos la opción de, en el momento en el que necesitásemos
         esa posición, buscarla comparando las direcciones de memoria a las que apuntan las distintas casillas
         del vector img y tomando la primera de ellas, pero esto nos parece un sinsentido por la innecesaria
         ineficiencia que implica).

       **/
private :

    /**
      @brief Puntero a la imagen almacenada

      img apunta a un array-2D dinámico de bytes que contiene la imagen en sí. Almacena tantos bytes como pixeles tenga la imagen.

    **/
    byte **img;

    /**
      @brief Número de filas de la imagen.
    **/
    int rows;


    /**
      @brief Número de columnas de la imagen.
    **/
    int cols;

    /**
      @brief Puntero inicializado en img[0] que almacena el inicio de la representación en memoria.
    **/
    byte * orgn_ptr;

    /**
      @brief Initialize una imagen.
      @param nrows Número de filas que tendrá la imagen. Por defecto, 0
      @param ncols Número de colwnnas que tendrá la imagen. Por defecto, 0
      @param buffer Puntero a un buffer de datos con los que rellenar los píxeles de la imagen. Por defecto, 0.
      @pre filas >= O y columnas >= O
      @post Reserva memoria para almacenar la imagen y la prepara para usarse.
    **/
    void Initialize (int nrows= 0, int ncols= 0, byte *buffer= 0);

    /**
      @brief Lee una imagen PGM desde un archivo.
      @param file_path Ruta del archivo a leer
      @return LoadResult

      @see LoadResult
    **/
    LoadResult LoadFromPGM(const char * file_path);

    /**
      @brief Copy una imagen .
      @param orig Referencia a la imagen original que vamos a copiar
      @pre Asume que no hay memoria reservada o se ha llamado antes a Destroy()
      @pre Asume this != &orig
    **/
    void Copy(const Image &orig);

    /**
      @brief Reserva o copia en memoria una imagen.
      @param nrows Número de filas que tendrá la imagen.
      @param ncols Número de colwnnas que tendrá la imagen.
      @param buffer Puntero a un buffer de datos con los que rellenar los píxeles de la imagen. Por defecto, 0.
      @pre nrows >= O y ncols >= O
      @post Reserva memoria para almacenar la imagen y la prepara para usarse.
    **/
    void Allocate(int nrows, int ncols, byte * buffer = 0);

    /**
      * @brief Destroy una imagen
      *
      * Libera la memoria reservada en la que se almacenaba la imagen que llama a la función.
      * Si la imagen estaba vacía no hace nada .
      */
    void Destroy();

public :

    /**
      * @brief Constructor por defecto .
      * @post Genera una instancia de la clase Imagen con O filas y O columnas.
      * @return Imagen, el objeto imagen creado.
      */
    Image();

    /**
      * @brief Constructor con parámetros.
      * @param nrows Número de filas de la imagen.
      * @param ncols Número de columnas de la imagen.
      * @param value defecto Valor con el que inicializar los píxeles de la imagen . Por defecto O.
      * @pre @p nrows > O y @p ncols > O
      * @post La imagen creada es de @p nrows y @p ncols columnas. Estará inicializada al valor por defecto.
      * @return Imagen, el objeto imagen creado.
      */
    Image(int nrows, int ncols, byte value=0);

    /**
      * @brief Constructor de copias.
      * @param orig Referencia a la imagen original que se quiere copiar.
      * @return Imagen, el objeto imagen creado.
      */
    Image (const Image & orig);

    /**
      * @brief Oper ador de tipo destructor.
      * @return void
      * @post El objeto Imagen destruido no puede usarse salvo que se haga sobre él una operacion Imagen().
      */
    ~Image() ;

    /**
      * @brief Operador de asignación .
      * @param orig Referencia a la imagen original que desea copiarse.
      * @return Una referencia al objeto imagen modificado.
      * @post Destroy cualquier información que contuviera previamente la imagen que llama al operador de asignación.
      */
    Image & operator= (const Image & orig);

    /**
      * @brief Funcion para conocer si una imagen está vacía.
      * @return Si la imagene está vacía
      * @post la imagen no se modifica.
      */
    bool Empty() const;

    /**
      * @brief Filas de la imagen .
      * @return El número de filas de la i magen.
      * @post la imagen no se modifica.
      */
    int get_rows() const;

    /**
      * @brief Columnas de la imagen.
      * @return El número de columnas de la imagen.
      * @post la imagen no se modifica.
      */
    int get_cols() const;

    /**
      * @brief Devuelve el número de píxeles de la imagen.
      * @return número de píxeles de la imagen.
      * @post la imagen no se modifica.
      */
    int size() const;

/**
  * @brief Asigna el valor valor al píxel (@p i, @p j) de la imagen.
  * @param i Fila de la imagen en la que se encuentra el píxel a escribir .
  * @param j Columna de la imagen en la que se encuentra el píxel a escribir.
  * @param value Valor que se escribirá en el píxel (@p i, @p j) .
  * @pre O <= @p i < get_rows()
  * @pre O <= @p j < get_cols()
  * @pre O <= @p value <= 255
  * @post El píxel (@p i, @p j) de la imagen se modificará y contendrá valor @p value.
  * Los demás píxeles permanecerán iguales.
  */
void set_pixel (int i, int j, byte value);

    /**
      * @brief Consulta el valor del píxel (fil, col) de la imagen.
      * @param i Fila de la imagen en la que se encuentra el píxel a consultar.
      * @param j Columna de la imagen en la que se encuentra el píxel a consultar.
      * @pre O <= fil < I.Num_ Filas() II O <= col < I.Num Columnas()
      * @return el valor del píxel contenido en (fil,col)
      * @post La imagen no se modifica.
      */
    byte get_pixel (int i, int j) const;

    /**
      * @brief Consulta el valor del píxel k de la imagen desenrrollada.
      * @param k Índice del píxel
      * @pre 0 <= k < filas*columnas
      * @return el valor del píxel contenido en (k/filas,k%filas)
      * @post La imagen no se modifica.
      */
    byte get_pixel (int k) const;

    /**
      * @brief Asigna el valor valor al píxel k de la imagen desenrollada.
      * @param k Índice del píxel a escribir .
      * @param value Valor que se escribirá en el píxel k.
      * @pre 0 <= k < filas*columnas && O <= valor <= 255
      * @post El píxel k se modificará con el valor de value.
      */
    void set_pixel (int k, byte value);

    /**
      * @brief Almacena imágenes en disco.
      * 	La diferencia con Image::MySave() es que usa la representación secuencial en memoria,
	  * 			por lo que no funciona con la representación modificada.
      * @param file_path Ruta donde se almacenará la imagen.
      * @pre file path debe ser una ruta válida donde almacenar el fichero de salida.
      * @return Devuelve true si la imagen se almacenó con éxito y false en caso contrario.
      * @post La imagen no se modifica.
      */
    bool Save (const char * file_path) const;

	/**
	 * @brief Almacena imágenes en disco.
	 * 		La diferencia con Image::Save() es que no usa la representación secuencial en memoria,
	 * 			por lo que funciona con la representación modificada.
     * @param file_path Ruta donde se almacenará la imagen.
     * @pre file path debe ser una ruta válida donde almacenar el fichero de salida.
     * @return Devuelve true si la imagen se almacenó con éxito y false en caso contrario.
     * @post La imagen no se modifica.
	 */
	bool MySave (const char *file_path) const;

    /**
      * @brief Carga en memoria una imagen de disco .
      * @param file_path Ruta donde se encuentra el archivo desde el que cargar la imagen.
      * @pre @p file_path debe ser una ruta válida que contenga un fichero . pgm
      * @return Devuelve @b true si la imagen se carga con éxito y @b false en caso contrario.
      * @post La imagen previamente almacenada en el objeto que llama a la función se destruye.
      */
    bool Load (const char * file_path);

      /**
      * @brief Calcula el negativo de la imagen llamadora
      * @post Cada byte de la imagen queda correspondido a su opuesto en la escala de grises
      */
    void Invert();

    /**
     * @brief Modifica el contraste de una Imagen mediante un ajuste lineal.
     *
     * Los nuevos valores de los píxeles estarán en el rango:
     * - [0,out1] si sus valores iniciales están en [0,in1],
     * - [out1, out2] si sus valores iniciales están en [in1,in2], y
     * - [out2,255] si sus valores iniciales están en [in2,255].
     *
     * @image html Doc_Contraste.png "Explicación del método Image::AdjustContrast"
     * @image latex Doc_Contraste.png "Explicación del método Image::AdjustContrast"
     *
     * @param in1 Extremo superior del primer rango de la imagen de entrada (@f$e_1@f$ en la imagen).
     * @param in2 Extremo superior del segundo rango de la imagen de entrada (@f$e_2@f$ en la imagen).
     * @param out1 Extremo superior del primer rango de la imagen de salida (@f$s_1@f$ en la imagen).
     * @param out2 Extremo superior del segundo rango de la imagen de salida (@f$s_2@f$ en la imagen).
     *
     * @pre 0 <= in1, in2, out1, out2 <= 255
     * @pre in1 < in2
     * @pre out1 < out2
     *
     * @post El objeto que llama a la función es modificado.
     */
    void AdjustContrast (byte in1, byte in2, byte out1, byte out2);


    /**
     * @brief Calcula la media de los píxeles de una imagen entera o de un fragmento de ésta.
     * @param i Fila de la esquina superior izquierda desde donde empieza el recorte
     * @param j Columna de la esquina superior izquierda desde donde empieza el recorte
     * @param height Número de filas que ocupa el recorte.
     * @param width Número de columnas que ocupa el recorte.
     * @return La media de los píxeles del fragmento buscado.
     * @pre 0 < @p height, @p width, @p i, @p j
     * @pre 0<= @p i+height <= get_rows()
     * @pre 0<= @p j+width  <= get_cols()
     */
    double Mean (int i, int j, int height, int width) const;

    /**
     * @brief Genera un icono como reducción de una imagen.
     * @param factor Factor de reducción de la imagen original respecto al icono
     * @return La imagen iconizada
     * @pre factor > 0
     * @post la imagen no se modifica
     * @post La imagen resultante tendrá tamaño int(filas/factor) X int(columnas/factor),
     *              descartando los decimales de la división.
     */
    Image Subsample(int factor) const;

    /**
     * @brief Hace un recorte de una imagen
     * @param nrow Fila inicial para recortar
     * @param ncol Columna inicial para recortar
     * @param height Número de filas del recorte
     * @param width Número de columnas del recorte
     * @return La imagen recortada
     * @pre 0 <= nrow, ncol, height, width
     * @pre 0 <= nrow + height <= rows
     * @pre 0 <= ncols + width <= cols
     * @post la imagen llamadora no se modifica
     * @post La imagen devuelta tendrá el tamaño especificado en los parámetros
     */
    Image Crop(int nrow, int ncol, int height, int width) const;

    /**
     * @brief Genera una imagen aumentada 2x.
     * @return La imagen generada aumentada 2x.
     */
    Image Zoom2X() const;



    /**
	 * @brief Método que baraja pseudoaleatoriamente las filas de una imagen.
     * 			Código de eficiencia de orden rows*cols.
	 * @pre get_rows() < 9973
	 * @post El objeto implícito contiene la misma imagen pero con las filas cambiadas
	 * 			según el siguiente algoritmo:
	 * 			r' = r*p mod( get_rows() )
	 *
	 * 			donde r' es el nuevo índice de la fila r y p es un coprimo de rows.
	 * 			En este algoritmo usamos p=9973, pero se podría modificar.
	 */
    void ShuffleRows_noeff();

	/**
	 * @brief Método que baraja pseudoaleatoriamente las filas de una imagen.
	 * 			Código de eficiencia de orden rows.
	 * 			Más eficiente, pero a costa de variar la representación de nuestro tipo.
	 * @pre get_rows() < 9973
	 * @post El objeto implícito contiene la misma imagen pero con las filas cambiadas
	 * 			según el siguiente algoritmo:
	 * 			r' = r*p mod(get_rows())
	 *
	 * 			donde r' es el nuevo índice de la fila r y p es un coprimo de rows.
	 * 			En este algoritmo usamos p=9973, pero se podría modificar.
	 */
	 void ShuffleRows_eff();


    /**
     * @brief Operador ==, para comparar dos imágenes
     * @param other Imagen con la que comparar
     * @retval  true si ambas imágenes son iguales pixel a pixel
     * @retval false si, al menos, hay un pixel distinto o tienen dimensiones distintas.
     */
    bool operator==(const Image & other) const;
} ;


#endif // _IMAGEN_H_

