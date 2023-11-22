/**
 * @file guiatlf.cpp
 * @brief Implementación TDA guia de teléfonos
 * @author Arturo Olivares Martos
 * @author Daniel Hidalgo Chica
 * */

#include "guiatlf.h"

/**
 * @brief Sobrecarga del operador de entrada para el pair de strings.

 * @param is Flujo de entrada.
 * @param d Par de strings.
 * @return Referencia al flujo de entrada.
 */
istream & operator>>(istream &is,pair<string,string> &d){
	  
	  getline(is,d.first,'\t');
	  getline(is,d.second);
	  return is;
}	  

/**
 * @brief Sobrecarga del operador de salida para el pair de strings.
 * @param os  Flujo de salida.
 * @param d  Par de strings.
 * @return  Referencia al flujo de salida.
 */
ostream & operator<<(ostream &os,const pair<const string,string> &d){
	  
	  os<<d.first<<'\t'<<d.second<<endl;
	  return os;
}	  


//Acceso a un elemento con operador
string & Guia_Tlf::operator[](const string &nombre) {
   return datos[nombre];
}
		    
//acceso a un elemento con iteradores	    
string Guia_Tlf::gettelefono(const string & nombre){
   map<string,string>::iterator it=datos.find(nombre);
   if (it==datos.end()) 
      return string("");
   else return it->second;
}
		     
// Insert un nuevo telefono 
pair<map<string,string>::iterator,bool>  Guia_Tlf::insert(string nombre, string tlf){
   pair<string,string> p (nombre,tlf);
   pair<map<string,string> ::iterator,bool> ret;

   ret=datos.insert(p); //datos.insert(datos.begin(),p); tambien funcionaría
   return ret;
}
		    
// Insert un nuevo telefono 
pair<map<string,string>::iterator,bool>  Guia_Tlf::insert(pair<string,string> p){
   pair<map<string,string> ::iterator,bool> ret;

   ret=datos.insert(p); //datos.insert(datos.begin(),p); tambien funcionaría
   return ret;     
}
		    
//Borrar un telefono
void Guia_Tlf::borrar(const string &nombre){
   map<string,string>::iterator itlow = datos.lower_bound(nombre);//el primero que tiene dicho nombre
   map<string,string>::iterator itupper = datos.upper_bound(nombre);//el primero que ya no tiene dicho nombre
   datos.erase(itlow,itupper);//borramos todos aquellos que tiene dicho nombre
	//OTRA ALTERNATIVA
	// pair<map<string,string>::iterator,map<string,string>::iterator>ret;
	//ret = datos.equal_range(nombre
	//datos.erase(ret.first,ret.second);   
}
		    
// Borrar un telefono otro
//con map siempre hay uno con multimap puede existir mas de uno
void Guia_Tlf::borrar(const string &nombre,const string &tlf){
   map<string,string>::iterator itlow = datos.lower_bound(nombre);//el primero que tiene dicho nombre
   map<string,string>::iterator itupper = datos.upper_bound(nombre);//el primero que ya no tiene dicho nombre
   map<string,string>::iterator it;
   bool salir =false;
   for (it=itlow; it!=itupper && !salir;++it){
      if (it->second==tlf){
         datos.erase(it);
         salir =true;
      }		
   }
}
      
//Union de guias de telefonos
Guia_Tlf Guia_Tlf::operator+(const Guia_Tlf & g){
   Guia_Tlf aux(*this);
   map<string,string>::const_iterator it;
   for (it=g.datos.begin();it!=g.datos.end();++it){
      aux.insert(it->first,it->second);
   }	  

   return aux;
}	   
		    	      
//Diferencia de guias de telefonos
Guia_Tlf Guia_Tlf::operator-(const Guia_Tlf & g){
   Guia_Tlf aux(*this);
   map<string,string>::const_iterator it;
   for (it=g.datos.begin();it!=g.datos.end();++it){
      aux.borrar(it->first,it->second);
   }	  

   return aux;		
}

//Obtiene una guia con los nombre previos a uno dado
Guia_Tlf Guia_Tlf::previos(const string &nombre,const string &tlf){
   map<string,string>::value_compare vc=datos.value_comp(); //map<string,string>::key_compare vc=datos.key_comp()
   Guia_Tlf aux;
   pair<string,string>p(nombre,tlf);
   map<string,string>::iterator it=datos.begin();
   while (vc(*it,p)){
      aux.insert(*it++);	  
   }
   
   return aux;
}

Guia_Tlf Guia_Tlf::interseccion(const Guia_Tlf &guia) {
    Guia_Tlf guia_inter; // Guia para la interasección

    map<string,string>::const_iterator it = this->datos.cbegin();
    while (it != this->datos.cend()) {
       string nombre_que_comparten = it->first;
       string telefono_del_elemento = it->second;

       // Par con iteradores que determinan el rango de elementos en la guia que tienen ese nombre
       pair<map<string,string>::const_iterator, map<string,string>::const_iterator> ret;
       ret = guia.datos.equal_range(nombre_que_comparten);
       map<string,string>::const_iterator itb = ret.first;

       while (itb != ret.second) { // Metemos solo aquellos en los que el telefono tambien coindicida
           if (itb->second == telefono_del_elemento) guia_inter.insert(nombre_que_comparten,telefono_del_elemento);
           itb++;
       }
       it++;
    }
    return guia_inter;
}

bool Guia_Tlf::cambiar_tlf(const std::string &nombre, const std::string &tlf) {
    // Asumimos que se usa map, si fuese multimap usamos equal_range e iteramos
    bool encontrado = (bool)this->datos.count(nombre);
    if (encontrado) this->datos[nombre] = tlf;
    return encontrado;
}

Guia_Tlf Guia_Tlf::guia_con_nombres_comenzando(const std::string &str) {
    Guia_Tlf guia_ret;
    size_t found;
    map<string,string>::iterator it = this->datos.begin();
    while (it != this->datos.end()) {
        string nombre = it->first;
        found = nombre.find(str);
        if (found != string::npos && found == 0) guia_ret.insert(nombre,it->second);
        it++;
    }
    return guia_ret;
}


// Escritura de una guia de telefonos      
ostream & operator<<(ostream & os, const Guia_Tlf & g){
   map<string,string>::const_iterator it;
   for (it=g.datos.begin(); it!=g.datos.end();++it)
      os<<it->first<<"\t"<<it->second<<endl;
			      			      
   return os;
}		    

// Lectura de una guia de telefonos
istream & operator>>(istream & is, Guia_Tlf & g){
   pair<string,string> p;
   Guia_Tlf aux;
			      
   while (is>>p)
      aux.insert(p);
   
   g=aux;
   return is;
}


