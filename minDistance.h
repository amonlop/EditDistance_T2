#ifndef MINDISTANCE_H
#define MINDISTANCE_H

#include <string>
#include <vector>
#include <math.h>

using namespace std;


//costo minimo para convertir s1 en s2
int editDistanceRecursive(string s1, string s2, int size_s1, int size_s2) {

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
int editDistanceRecursiveMemoization(string s1, string s2, int size_s1, int size_s2, vector<vector<int>> &matriz) {
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



#endif