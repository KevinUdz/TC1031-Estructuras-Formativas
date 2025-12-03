#ifndef SORTS_H
#define SORTS_H

#include <vector>
#include <iostream>

using namespace std;

template <class T>
class Sorts {
private:
    // Métodos auxiliares para el Merge Sort
    
    // Función que mezcla dos mitades ordenadas en un vector temporal y luego lo copia al original.
    void mergeArray(vector<T> &A, int low, int mid, int high) {
        int i = low;      // Índice para la parte izquierda
        int j = mid + 1;  // Índice para la parte derecha
        int k = low;      // Índice para el vector auxiliar

        // Creare un vector temporal del tamaño necesario
        // Nota: en implementaciones muy optimizadas se pasa un vector temporal por referencia para no crearlo siempre (tip del profe)
        vector<T> B(A.size()); 

        // Comparamos y mezclamos mientras haya elementos en ambas mitades
        while (i <= mid && j <= high) {
            if (A[i] < A[j]) {
                B[k] = A[i];
                i++;
            } else {
                B[k] = A[j];
                j++;
            }
            k++;
        }

        // Si sobraron elementos en la mitad izquierda, los copiamos
        while (i <= mid) {
            B[k] = A[i];
            i++;
            k++;
        }

        // Si sobraron elementos en la mitad derecha, los copiamos
        while (j <= high) {
            B[k] = A[j];
            j++;
            k++;
        }

        // Copiamos los elementos ordenados del auxiliar B de regreso a A
        for (int m = low; m <= high; m++) {
            A[m] = B[m];
        }
    }

    // Función recursiva que divide el vector hasta tener elementos individuales
    void mergeSplit(vector<T> &A, int low, int high) {
        if (low < high) {
            int mid = (high + low) / 2; // Calculamos la mitad

            // Se dvide recursivamente:
            mergeSplit(A, low, mid);      // Ordenamos mitad izquierda
            mergeSplit(A, mid + 1, high); // Ordenamos mitad derecha

            // Mezclamos las dos mitades ordenadas
            mergeArray(A, low, mid, high);
        }
    }

    // Método auxiliar para intercambiar valores (swap)
    void swap(vector<T> &v, int i, int j) {
        T aux = v[i];
        v[i] = v[j];
        v[j] = aux;
    }

public:
    // Algoritmos de Ordenamiento

    /*
     * ordenaSeleccion = Selection Sort
     * Busca el elemento más pequeño y lo pone al principio
     * Por lo visto en clase su Complejidad es O(n^2)
     */
    void ordenaSeleccion(vector<T> &v) {
        // Recorremos todo el vector
        for (int i = 0; i < v.size() - 1; i++) {
            int minIndex = i;
            
            // Buscamos el elemento más pequeño en el resto del vector
            for (int j = i + 1; j < v.size(); j++) {
                if (v[j] < v[minIndex]) {
                    minIndex = j;
                }
            }
            
            // Si encontramos uno más pequeño, lo intercambiamos
            if (minIndex != i) {
                swap(v, i, minIndex);
            }
        }
    }

    /*
     * ordenaBurbuja = Bubble Sort
     * Compara pares adyacentes y "burbujea" el más grande hacia el final
     * Su Complejidad es O(n^2)
     */
    void ordenaBurbuja(vector<T> &v) {
        // El bucle externo controla cuántas pasadas hacemos
        for (int i = v.size() - 1; i > 0; i--) {
            // El bucle interno compara pares y hace los swaps
            for (int j = 0; j < i; j++) {
                if (v[j] > v[j + 1]) {
                    swap(v, j, j + 1);
                }
            }
        }
    }

    /*
     * ordenaMerge = Merge Sort
     * Divide el vector en mitades y luego las mezcla ordenadamente
     * Su complejidad es O(n log n) - Mucho más eficiente para datos grandes (servira para mi proyecto)
     */
    void ordenaMerge(vector<T> &v) {
        // Llamamos a la función auxiliar recursiva pasando los índices extremos
        mergeSplit(v, 0, v.size() - 1);
    }

    // Algoritmos de Búsqueda

    /*
     * busqSecuencial
     * Recorre elemento por elemento hasta encontrar el valor
     * Retorna el índice o -1 si no existe
     */
    int busqSecuencial(const vector<T> &v, T val) {
        for (int i = 0; i < v.size(); i++) {
            if (v[i] == val) {
                return i; // Lo encontramos
            }
        }
        return -1; // No estaba en el vector
    }

    /*
     * busqBinaria
     * Divide el espacio de búsqueda a la mitad repetidamente
     * REQUISITO: El vector debe estar ordenado previamente
     */
    int busqBinaria(const vector<T> &v, T val) {
        int low = 0;
        int high = v.size() - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2; // Evita overflow en índices muy grandes

            if (v[mid] == val) {
                return mid; // Se encontró
            } else if (val < v[mid]) {
                high = mid - 1; // Está en la mitad izquierda
            } else {
                low = mid + 1; // Está en la mitad derecha
            }
        }
        return -1; // No se encontró
    }
};

#endif /* SORTS_H */