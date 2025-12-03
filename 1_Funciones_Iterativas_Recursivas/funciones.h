#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>

class Funciones {
public:

    // suma iterativa: Realiza la suma usando un ciclo for
    long sumaIterativa(int n) {
        long suma = 0;
        // Empezamos desde 1 hasta n acumulando el valor
        for (int i = 1; i <= n; i++) {
            suma += i;
        }
        return suma;
    }

    // suma Recursiva: Realiza la suma llamándose a sí misma
    long sumaRecursiva(int n) {
        // Caso base: si n llega a 0, dejamos de sumar y regresamos 0
        if (n <= 0) {
            return 0;
        }
        // Llamada recursiva: n actual + la suma del anterior (n-1)
        return n + sumaRecursiva(n - 1);
    }

    // sumaDirecta: Se usa la fórmula matemática de la suma de Gauss (n*(n+1)/2)

     long sumaDirecta(int n) {
        return (long)n * (n + 1) / 2;
    }
};

#endif /* FUNCIONES_H */