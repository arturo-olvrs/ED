/**
 * @file   guiatlf.h
 * @brief  TDA guia de teléfonos
 * @author Arturo Olivares Martos
 * @author Daniel Hidalgo Chica
 * */

#ifndef _GUIA_TLF_H
#define _GUIA_TLF_H
#include <map>
#include <iostream>
#include <string>
using namespace std;

/**
  *  @brief TDA Guia_Tlf
  *
  * Una instancia @e c del tipo de datos abstracto @c Guia_Tlf es un objeto
  * formado por una colección de pares {(e11,e21),(e12,e22),(e13,e23),...,(e1n-1,e2n-1)}
  * ordenados por la el primer elemento del par denominado clave o key. No existen
  * elementos repetidos. 
  *
  * @invariant Para todo \e i y \e j tal que i<j entonces \e e1i y e1j son distintos.
  */

class Guia_Tlf{
private:
	/**
	 * @brief Diccionario de nombres junto con sus teléfonos
	 */
	map<string,string> datos; //si admites que haya nombres repetidos tendrías que usar un
					     //multimap
					     
public:
		    
  /**
  @brief Acceso a un elemento.

  Si el element con ese nombre como clave no existe, lo crea con valor "".

  @param nombre  nombre del elemento a acceder
  @return devuelve el valor asociado a un nombre, es decir el teléfono.
  */
  //si fuese un multimap no podriamos usar []. Ademas que deberiamos devolver p.e un vector con todos
  // los teléfonos asociados a dicho nombre
string & operator[](const string &nombre);
		    
	/**
	 * @brief Acceso a un elemento
	 *
	 * Si el element con ese nombre como clave no existe, no lo crea.
	 *
	 * @param nombre Nombre del elemento a buscar.
	 * @return Devuelve el valor asociado a un nombre, es decir, el teléfono.
	 *
	 * Si el element con ese nombre como clave no existe, devuelve "".
	 */
string  gettelefono(const string & nombre);
		     
  /**
  @brief Insert un nuevo teléfono 
  @param nombre  nombre clave del nuevo teléfono
  @param tlf  numero de teléfono
  @return  Un pair donde first apunta al nuevo elemento insertado y bool es true si se ha
  insertado el nuevo tlf o false en caso contrario.
  */
pair<map<string,string>::iterator,bool>  insert(string nombre, string tlf);
		    
  /**
  @brief Insert un nuevo teléfono 
  @param p  pair con el nombre y el teléfono asociado
  @return  Un pair donde first apunta al nuevo elemento insertado y bool es true si se ha
  insertado el nuevo tlf o false en caso contrario.
  */
pair<map<string,string>::iterator,bool>  insert(pair<string,string> p);
		    
  /**
  @brief Borrar un teléfono
  @param nombre  nombre que se quiere borrar
  @note  en caso de que fuese un multimap borraria todos con ese nombre
  */
void borrar(const string &nombre);
		    
  /**
  @brief Borrar un teléfono
  @param nombre  nombre que se quiere borrar y teléfono asociado
  @param tlf  teléfono asociado a dicho nombre
  @note  esta función nos permite borrar solamente aquel que coincida en nombre y tlf
  */
  //con map siempre hay uno con multimap puede existir mas de uno
void borrar(const string &nombre,const string &tlf);

  /**
  @brief  Numero de teléfonos 
  @return el numero de teléfonos asociados
  */
int size()const{return datos.size();}	      
		    
  /**
  @brief Contabiliza cuantos teléfonos tenemos asociados a un nombre
  @param nombre  nombre sobre el que queremos consultar
  @return numero de teléfonos asociados a un nombre		      
  */
//al ser un map debe de ser 0 o 1. Si fuese un multimap podríamos tener mas de uno
unsigned int contabiliza(const string &nombre){return datos.count(nombre);}
		    
  /**
  @brief Limpia la guia
  */
void clear(){datos.clear();}
	      
  /**
  @brief Union de guias de teléfonos
  @param g  guia que se une
  @return  una nueva guia resultado de unir el objeto al que apunta this y g
  */
Guia_Tlf operator+(const Guia_Tlf & g);
	    	      
  /**
  @brief Diferencia de guias de teléfonos
  @param g  guia a restar
  @return  una nueva guia resultado de la diferencia del objeto al que apunta this y g
  */
Guia_Tlf operator-(const Guia_Tlf & g);

  /**
  @brief  Obtiene una guia con los nombre previos a uno dado
  @param nombre  nombre delimitador
  @param tlf  teléfono asociado a nombre
  @return Nueva guia sin nombres mayores que \a  nombre
  */
Guia_Tlf previos(const string &nombre,const string &tlf);

/**
 * @brief Obtiene una guía con los datos comunes a this y guia.
 * @param guia Guía con la que se interseca.
 * @return Guía con los datos comunes a this y guia.
 */
Guia_Tlf interseccion(const Guia_Tlf & guia);

/**
 * @brief Cambia el teléfono asociado a un nombre
 * @param nombre Nombre al que se le cambia el teléfono
 * @param tlf Nuevo teléfono
 * @retval true si se encuentra el nombre y, por tanto, se ha podido cambiar el teléfono.
 * @retval false si no se encuentra el nombre.
 */
bool cambiar_tlf(const string& nombre, const string& tlf);

/**
 * @brief Obtiene una guía con los nombres que empiezan por una cadena.
 * @param str Cadena a buscar.
 * @return Guía con los nombres que empiezan por @e str.
 */
Guia_Tlf guia_con_nombres_comenzando(const string & str);



  /**
  @brief Escritura de la guia de teléfonos
  @param os  flujo de salida. Es MODIFICADO
  @param g  guia de teléfonos que se escribe
  @return el flujo de salida
  */    
friend ostream & operator<<(ostream & os, const Guia_Tlf & g);
		    
  /**
  @brief Lectura de  la guia de teléfonos
  @param is  flujo de entrada. ES MODIFICADO
  @param g  guia de teléfonos. ES MODIFICADO
  @return el flujo de entrada
  */
friend istream & operator>>(istream & is, Guia_Tlf & g);
		    
  /**
  * @brief clase para iterar sobre la guia
  * */
class iterator{
   private:
   map<string,string>::iterator it;

   public:
   iterator & operator++(){++it;return *this;}
   iterator & operator--(){--it;return *this;}
   pair<const string,string> &operator *(){return *it;}
   bool operator ==(const iterator &i){return i.it==it;}	  		       
   bool operator !=(const iterator &i){return i.it!=it;}
   friend class Guia_Tlf;
};
		    
  /**
  * @brief Inicializa un iterator al comienzo de la guia
  * */
iterator  begin(){
   iterator i;
   i.it=datos.begin();
   return i;
}
  /**
  * @brief Inicializa un iterator constante al comienzo de la guia
  * */
iterator  cbegin() {
    begin();
}

  /**
  * @brief Inicializa un iterator al final de la guia
  * */
iterator  end(){
   iterator i;
   i.it=datos.end();
   return i;
}  

}; //del class Guia_Tlf
#endif

