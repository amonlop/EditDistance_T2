#include "minDistance.h"

#include <iostream> 
#include <fstream>        
#include <string>          
#include <iterator>   

//si se desea utilizar para realizar experimentos con el script .sh, borrar los cout y colocar solo la función

int main(int argc, char* argv[]) {
    std::ifstream fa(argv[1]), fb(argv[2]);
    std::string a((std::istreambuf_iterator<char>(fa)), {});
    std::string b((std::istreambuf_iterator<char>(fb)), {});

    #if ALGO == 1
        std::cout << "Resultado (Recursivo): " << editDistanceRecursive(a, b, a.length(), b.length()) << std::endl;
    #elif ALGO == 2
        std::cout << "Resultado (Memoization): " << editDistanceRecursiveMemo(a, b, a.length(), b.length()) << std::endl;
    #elif ALGO == 3
        std::cout << "Resultado (DP): " << editDistanceDP(a, b) << std::endl;
    #elif ALGO == 4
        std::cout << "Resultado (DP Optimizado): " << editDistanceDPOptimized(a, b) << std::endl;
    #endif

    return 0;
}
