#ifndef MINDISTANCE_H
#define MINDISTANCE_H

#include <string>
#include <vector>
#include <cmath>

using namespace std;


//costo minimo para convertir s1 en s2
int editDistanceRecursive(const string &s1, const string &s2, const int size_s1, const int size_s2) {

    //costo de insertar todo lo que falta en s2
    if(size_s1 == 0) {
        return size_s2;
    }

    //costo de eliminar todo lo que sobra de s1
    if(size_s2 == 0) {
        return size_s1;
    }

    //si los caracteres son iguales
    if (s1[size_s1 - 1] == s2[size_s2 - 1]) {
        return editDistanceRecursive(s1, s2, size_s1 - 1, size_s2 - 1);
    }

    return 1 + min( editDistanceRecursive(s1, s2, size_s1 - 1, size_s2),    //costo eliminar
                    editDistanceRecursive(s1, s2, size_s1, size_s2 -1 ));   //costo insercion
}


//Con memoization, enfoque top-down
int editDistanceRecursiveMemoization(const string &s1, const string &s2, const int size_s1, const int size_s2, vector<vector<int>> &matriz) {
    //costo de insertar todo lo que falta en s2
    if(size_s1 == 0) {
        return size_s2;
    }

    //costo de eliminar todo lo que sobra de s1
    if(size_s2 == 0) {
        return size_s1;
    }

    //si ya calculamos el subproblema con anterioridad se retorna
    if(matriz[size_s1][size_s2] != -1) {
        return matriz[size_s1][size_s2];
    }

    //si los caracteres son iguales
    if (s1[size_s1 - 1] == s2[size_s2 - 1]) {
        return matriz[size_s1][size_s2] = editDistanceRecursiveMemoization(s1, s2, size_s1 - 1, size_s2 - 1, matriz);
    }

    //si los caracteres son distintos
    return matriz[size_s1][size_s2] = 1 + min( editDistanceRecursiveMemoization(s1, s2, size_s1 - 1, size_s2, matriz),    //costo eliminar
                                               editDistanceRecursiveMemoization(s1, s2, size_s1, size_s2 -1, matriz));   //costo insercion
                                            
}

//funcion auxiliar para declarar la matriz
int editDistanceRecursiveMemoization(string s1, string s2, int size_s1, int size_s2) {
    //se crea una matriz inicializada en -1
    vector<vector<int>> matriz(size_s1 + 1, vector<int>(size_s2 + 1, -1));

    return editDistanceRecursiveMemoization(s1, s2, size_s1, size_s2, matriz);
}

// A continuacion las funciones con programacion dinamica

int editDistanceDP(const string &s1, const string &s2) {
    const int s1_size = s1.length();
    const int s2_size = s2.length();

    const int FILAS = s1_size + 1;
    const int COLUMNAS = s2_size + 1;
    vector<vector<int>> matriz(FILAS, vector<int>(COLUMNAS));

    for (int i = 0; i < FILAS; i++) {
        matriz[i][0] = i;
    }
    for (int j = 0; j < COLUMNAS; j++) {
        matriz[0][j] = j;
    }

    for (int i = 1; i < FILAS; i++) {
        for (int j = 1; j < COLUMNAS; j++) {
            if (s1[i-1] == s2[j-1]) {
                matriz[i][j] = matriz[i-1][j-1];
            } else {
                matriz[i][j] = 1 + min(matriz[i-1][j],matriz[i][j-1]);
            }
        }
    }

    return matriz[s1_size][s2_size];
}

// Bajamos espacio de (s1_size + 1)(s2_size + 1) a 2 * (s2_size + 1)
// O(S * T) -> O(T)

// v2 Correcion: ahora las columnas son del tamano de la str mas corta, por lo que
// O(T) -> O(min(S,T))
int editDistanceDPOptimized(const string &s1, const string &s2) {

    const string* s1_ptr = &s1;
    const string* s2_ptr = &s2;

    if (s1_ptr->length() < s2_ptr->length()) {
        swap(s1_ptr, s2_ptr);
    }

    // Aca swapeamos los punteros para tomar la str de menor valor
    const int s1_size = s1_ptr->length();
    const int s2_size = s2_ptr->length();

    const int FILAS = 2;
    const int COLUMNAS = s2_size + 1;
    vector<vector<int>> matriz(FILAS, vector<int>(COLUMNAS));

    for (int i = 0; i < FILAS; i++) {
        matriz[i][0] = i;
    }
    for (int j = 0; j < COLUMNAS; j++) {
        matriz[0][j] = j;
    }

    for (int i = 1; i < s1_size + 1; i++) {
        int actual = i % 2;
        int prev = (i - 1) % 2;
        matriz[actual][0] = i;
        for (int j = 1; j < COLUMNAS; j++) {
            if ((*s1_ptr)[i-1] == (*s2_ptr)[j-1]) {
                matriz[actual][j] = matriz[prev][j-1];
            } else {
                matriz[actual][j] = 1 + min(matriz[prev][j],matriz[actual][j-1]);
            }
        }
    }

    return matriz[s1_size % 2][s2_size];
}

#endif