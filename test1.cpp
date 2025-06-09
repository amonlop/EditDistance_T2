#include <string>
#include <iostream>
#include "minDistance.h"  
#include <chrono>
#include <fstream>    

using namespace std;

//archivo para comprobar tiempos de salida. Se utiliza una función para calcular la memoria

//RAM memory peak
size_t getMemoryFromProc() {
    std::ifstream status("/proc/self/status");
    std::string line;
    while (std::getline(status, line)) {
        if (line.find("VmHWM:") == 0) {
            size_t kb;
            std::sscanf(line.c_str(), "VmHWM: %zu kB", &kb);
            return kb;
        }
    }
    return 0;
}


vector<string> cargar_textos(const string &carpeta) {
    vector<string> textos;
    for (int i = 1; i <= 4; ++i) {
        string path = carpeta + "/texto" + to_string(i) + ".txt";
        ifstream in(path);
        if (!in.is_open()) {
            cerr << "No se pudo abrir: " << path << endl;
            exit(1);
        }
        string contenido((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
        textos.push_back(contenido);
    }
    return textos;
}

int main() {

    vector<string> cadenas = cargar_textos("textos");

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i != j) {
                string palabra1 = cadenas[i];
                string palabra2 = cadenas[j];

                size_t mem_peak_before = getMemoryFromProc();
                std::chrono::duration<double, std::milli> elapsed_time;

                cout << "cadena 1: " << palabra1.length() << endl;
                cout << "cadena 2: " << palabra2.length() << endl;

                for(int k = 0; k < 5; k++) {

                    auto begin_time = std::chrono::high_resolution_clock::now();
                    //editDistanceRecursiveMemo(palabra1, palabra2, palabra1.length(), palabra2.length());
                    editDistanceDPOptimized(palabra1, palabra2);
                    auto end_time = std::chrono::high_resolution_clock::now();

                    elapsed_time = end_time - begin_time;
                    
                }

                size_t mem_peak_after = getMemoryFromProc();
                size_t mem_peak = max(mem_peak_before, mem_peak_after);

                cout << elapsed_time.count() << " " << mem_peak << " KB " << endl;
            }
        }
    }

}

