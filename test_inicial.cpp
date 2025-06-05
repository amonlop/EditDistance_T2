#include <string>
#include <iostream>
#include "minDistance.h"  

using namespace std;

int main() {

    string palabras[] = {"listen", "silent", "kitten", "sitting"};

    cout << "=== Pruebas con función recursiva sin memoization ===" << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i != j) {  // Evita comparaciones con la misma palabra
                string s1 = palabras[i];
                string s2 = palabras[j];
                int result = editDistanceRecursive(s1, s2, s1.size(), s2.size());
                cout << "Edit Distance Recursive (" << s1 << ", " << s2 << ") = " << result << endl;
            }
        }
    }

    cout << "\n=== Pruebas con función recursiva con memoization ===" << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i != j) {  // Evita comparaciones con la misma palabra
                string s1 = palabras[i];
                string s2 = palabras[j];
                int result2 = editDistanceRecursiveMemoization(s1, s2, s1.size(), s2.size());
                cout << "Edit Distance Recursive Memoization (" << s1 << ", " << s2 << ") = " << result2 << endl;
            }
        }
    }


    return 0;
}