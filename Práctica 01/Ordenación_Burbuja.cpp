#include <iostream>
#include <ctime>    // Recursos para medir tiempos
#include <cstdlib>  // Para generación de números pseudoaleatorios
using namespace std;


/**
 * @brief Función que implementa la ordenación mediante el algoritmo de burbuja en un vector.
 * @param v Vector en el que se realiza la ordenación.
 * @param n Número de elementos del vector.
 */
void ordenar_burbuja(int *v, int n) {
    for (int i=0; i<n-1; i++)
        for (int j=0; j<n-i-1; j++)
            if (v[j]>v[j+1]) {
                int aux = v[j];
                v[j] = v[j+1];
                v[j+1] = aux;
            }
}

/**
 * @brief Función que implementa la ordenación mediante el algoritmo de burbuja en un vector. Implementación mejorada.
 * @param v Vector en el que se realiza la ordenación.
 * @param n Número de elementos del vector.
 */
void ordenar_burbuja_mejorada(int *v, int n) {
    bool cambio = true;
    for (int i=0; i<n-1 && cambio; i++) {
        cambio = false;
        for (int j = 0; j < n - i - 1; j++)
            if (v[j] > v[j + 1]) {
                cambio = true;
                int aux = v[j];
                v[j] = v[j + 1];
                v[j + 1] = aux;
            }
    }
}


/**
 * @brief Función que rellena el vector con números aleatorios en el intervalo [0,n].
 * @param v Vector a rellenar.
 * @param n Número de elementos del vector.
 */
void rellenar_normal(int *v, int n) {
    srand(time(0));        // Inicialización generador números pseudoaleatorios
    for (int i=0; i<n; i++)  // Recorrer vector
        v[i] = rand() % n;    // Generar aleatorio [min,max[
}


/**
 * @brief Función que rellena el vector con números ordenados en el intervalo [0,n].
 * @param v Vector a rellenar.
 * @param n Número de elementos del vector.
 */
void rellenar_ordenado(int *v, int n) {

    for (int i=0; i<n; i++)  // Recorrer vector
        v[i] = i;
}

/**
 * @brief Función que rellena el vector con números ordenados en el orden inverso en el intervalo [0,n].
 * @param v Vector a rellenar.
 * @param n Número de elementos del vector.
 */
void rellenar_inverso(int *v, int n) {

    for (int i=0; i<n; i++)  // Recorrer vector
        v[i] = n-i;
}


void sintaxis() {
    cerr << "Sintaxis:" << endl;
    cerr << "  TAM: Tamaño del vector (>0)" << endl;
    cerr << "  VMAX: Valor máximo (>0)" << endl;
    cerr << "Genera un vector de TAM números aleatorios en [0,VMAX[" << endl;
    exit(EXIT_FAILURE);
}


int main(int argc, char * argv[]) {
    if (argc!=3)               // Lectura de parámetros
        sintaxis();

    int tam=atoi(argv[1]);     // Tamaño del vector
    int vmax=atoi(argv[2]);    // Valor máximo
    if (tam<=0 || vmax<=0)
        sintaxis();


    // Generación del vector aleatorio
    int *v=new int[tam];   //Reserva de memoria
    rellenar_ordenado(v, tam);

    clock_t tini;    // Anotamos el tiempo de inicio
    tini=clock();

    ordenar_burbuja_mejorada(v,tam); // de esta forma forzamos el peor caso

    clock_t tfin;    // Anotamos el tiempo de finalización
    tfin=clock();

    // Mostramos resultados (Tamaño del vector y tiempo de ejecución en seg.)
    cout << tam << "\t" << (tfin-tini)/(double)CLOCKS_PER_SEC << endl;

    delete [] v;     // Liberamos memoria dinámica
}