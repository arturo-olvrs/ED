#include <iostream>
#include <algorithm>
#include <utility>
#include <list>
using namespace std;
/**
 * @author Luis Esteban Valdivieso González
 * @author Jesús Muñoz velasco
 * @author Arturo Olivares Martos
 *
 * @brief Programa que extrae un intervalo de una lista de intervalos
 *
 * Resolver el siguiente ejercicio:
 * Dadas dos listas L1 y L2 de intervalos cerrados de valores enteros [ini, fin], con ini<=fin,
 * 		donde en cada lista los intervalos se encuentran ordenados, verificándose que si un intervalo intervalo1
 * 		está antes que otro intervalo2 en la lista entonces intervalo1.fin < itervalo2.ini.
 *
 * Implementar una función que seleccione un (sub)intervalo x de L1 y lo pase a L2.
 * En este proceso podría ser necesario tanto el dividir un intervalo de L1 como
 * 		fusionar intervalos en L2 cuando ocurran solapamientos.
 * 	Tras seleccionar el intervalo x, los valores inicial y final de x no pertenecerán a ningún intervalo en L1.
 *
 * Tan solo es necesario implementar la función Extraer(), que se encuentra documentada y con la cabecera ya implementada.
 */

typedef pair<int,int> intervalo;


/**
 * @brief Sobrecarga del operador << para imprimir intervalos
 * @param os  flujo de salida
 * @param i  intervalo a imprimir
 * @return  flujo de salida
 */
ostream & operator<<(ostream & os, const intervalo & i) {
    os << "[" << i.first << ", " << i.second << "]";
    return os;
}

/**
 * @brief Sobrecarga del operador << para imprimir listas de intervalos
 * @param os  flujo de salida
 * @param L  lista de intervalos a imprimir
 * @return  flujo de salida
 */
ostream & operator<<(ostream & os, const list<intervalo> & L) {

    os << "<";
    for (list<intervalo>::const_iterator it=L.begin(); it!=L.end(); ++it)
        os << *it << " ";
    os << ">";

    return os;
}


/**
 * @brief Extrae un intervalo de una lista de intervalos
 * @param L1  lista de intervalos de la que extraer
 * @param x  intervalo a extraer. Se extraen también los extremos del intervalo.
 * @param L2  lista de intervalos en la que insertar el intervalo extraído
 * @return @retval true si el intervalo se ha extraído correctamente,
 * 		   @retval false en caso contrario
 * @pre L1 y L2 están ordenadas. Es decir, si un intervalo intervalo1 está antes que otro intervalo2 en la lista entonces intervalo1.fin < itervalo2.ini.
 * @pre El intervalo x está contenido en un único intervalo de L1
 * @post L1 y L2 están ordenadas. Es decir, si un intervalo intervalo1 está antes que otro intervalo2 en la lista entonces intervalo1.fin < itervalo2.ini.
 */
bool Extraer(list<intervalo> & L1, intervalo x, list<intervalo> & L2){

    // Obtenemos el intervalo de x en L1
    list<intervalo>::iterator int_L1 = find_if(L1.begin(), L1.end(), [x](intervalo y){return (y.first <= x.first) && (x.second <= y.second);});

    // Si no está, devolvemos false
    if(int_L1 == L1.end()) return false; // Si no está, devolvemos false

    // Si está, lo eliminamos de L1
    // Añadimos a L1 los intervalos que quedan a la izquierda y a la derecha de x en int_L1
    list<intervalo>::iterator it = int_L1;
    if (int_L1->first < x.first)   it = L1.insert(++it, intervalo(int_L1->first, x.first-1));
    if (x.second < int_L1->second) it = L1.insert(++it, intervalo(x.second+1, int_L1->second));

    // Eliminamos el intervalo de x en L1. Los intervalos de la izquierda y la dcha ya los hemos añadido
    L1.erase(int_L1);

    // Obtenemos el intervalo inferior y superior de x en L2
    list<intervalo>::iterator int_inf_L2 = --find_if_not(L2.begin(), L2.end(), [x](intervalo y){return (y.first <= x.first);});
    list<intervalo>::iterator int_sup_L2 = find_if(L2.begin(), L2.end(), [x](intervalo y){return (x.second < y.second);});


    // Elimina los intervalos de L2 contenidos en x
    while ((it = find_if(L2.begin(), L2.end(), [x](intervalo y){return (x.first <= y.first) && (y.second <= x.second);})) != L2.end())
        L2.erase(it);

    // Insertamos el intervalo x en L2 entre el inferior y el superior
    L2.insert(int_sup_L2, x);

    cout<<"L2: "<<L2<<endl;


    for (it=L2.begin(); it!=--L2.end(); )

        // Si hay dos intervalos adyacentes, los unimos
        if (it->second >= (++it)->first) {
            (--it)->second = (it)->second;

            // Borramos el intervalo que se ha unido
            L2.erase(++it);

            // Volvemos a iniciar, ya que con las uniones puede haber nuevos conjuntos adyacentes
            it = L2.begin();
        }


    return true;
}



int main() {
    list<intervalo> L1 = {{1,7},{10,22}, {25,26}};
    list<intervalo> L2 = {{0,1},{14,16},{20,23}};

    intervalo x = {19, 20};  // Intervalo a extraer

    cout << "L1 inicial: " << L1 << endl;
    cout << "L2 inicial: " << L2 << endl;
    cout << "Intentando extraer el intervalo [" << x.first << ", " << x.second << "] de L1..." << endl << endl;

    if (Extraer(L1, x, L2)) {
        cout << "Extracción exitosa.\nL1 ahora es: " << L1 << endl;
        cout << "L2 ahora es: " << L2 << endl;
    } else {
        cout << "Extracción fallida. El intervalo no puede ser extraído de L1." << endl;
    }

    return 0;
}
