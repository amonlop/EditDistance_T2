#include <string>
#include <iostream>
#include "minDistance.h"  

using namespace std;

const string palabras[] = {"listen", "silent", "kitten", "sitting"};

void test_EditDistanceRecursive() {
    cout << "=== Pruebas con funcion recursiva sin memoization ===" << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i != j) {
                string palabra1 = palabras[i];
                string palabra2 = palabras[j];
                int resultado = editDistanceRecursive(palabra1, palabra2, palabra1.size(), palabra2.size());
                cout << "Edit Distance Recursive (" << palabra1 << ", " << palabra2 << ") = " << resultado << endl;
            }
        }
    }
}

void test_EditDistanceRecursiveMemoization() {

    cout << "\n=== Pruebas con funcion recursiva con memoization ===" << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i != j) {
                string palabra1 = palabras[i];
                string palabra2 = palabras[j];
                int resultado = editDistanceRecursiveMemo(palabra1, palabra2, palabra1.size(), palabra2.size());
                cout << "Edit Distance Recursive Memoization (" << palabra1 << ", " << palabra2 << ") = " << resultado << endl;
            }
        }
    }
}

void test_EditDistanceDP() {

    cout << "\n=== Pruebas con programacion dinamica ===" << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i != j) {
                string palabra1 = palabras[i];
                string palabra2 = palabras[j];
                int resultado = editDistanceDP(palabra1, palabra2);
                cout << "Edit Distance DP (" << palabra1 << ", " << palabra2 << ") = " << resultado << endl;
            }
        }
    }
}

// Placeholder para la cuarta función futura
void test_EditDistanceDPOptimized() {

    cout << "\n=== Pruebas con programacion dinamica optimizada ===" << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i != j) {
                string palabra1 = palabras[i];
                string palabra2 = palabras[j];
                int resultado = editDistanceDPOptimized(palabra1, palabra2);
                cout << "Edit Distance DP Optimized (" << palabra1 << ", " << palabra2 << ") = " << resultado << endl;
            }
        }
    }
}

void test_all() {
    test_EditDistanceRecursive();
    test_EditDistanceRecursiveMemoization();
    test_EditDistanceDP();
    test_EditDistanceDPOptimized();
}

void test_ResultConsistency() {

    cout << "\n=== Unit Test: Consistencia entre las 4 funciones ===" << endl;
    bool aprobado = true;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i != j) {
                string palabra1 = palabras[i];
                string palabra2 = palabras[j];
                int r1 = editDistanceRecursive(palabra1, palabra2, palabra1.size(), palabra2.size());
                int r2 = editDistanceRecursiveMemo(palabra1, palabra2, palabra1.size(), palabra2.size());
                int r3 = editDistanceDP(palabra1, palabra2);
                int r4 = editDistanceDPOptimized(palabra1, palabra2);
                if (r1 != r2 || r1 != r3 || r1 != r4) {
                    cout << "Error: Resultados distintos para (" << palabra1 << ", " << palabra2 << "): "
                         << "Recursive=" << r1 << ", Memoization=" << r2 << ", DP=" << r3 << ", DPOptimized=" << r4 << endl;
                    aprobado = false;
                }
            }
        }
    }
    if (aprobado) {
        cout << "Las 4 funciones dan el mismo resultado." << endl;
    }
}

int main(void) {
    test_all();
    test_ResultConsistency();
}