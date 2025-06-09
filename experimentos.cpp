#include "minDistance.h"

#include <iostream> 
#include <fstream>        
#include <string>          
#include <iterator>   

int main(int argc, char* argv[]) {
    std::ifstream fa(argv[1]), fb(argv[2]);
    std::string a((std::istreambuf_iterator<char>(fa)), {});
    std::string b((std::istreambuf_iterator<char>(fb)), {});

    #if ALGO == 1
        editDistanceRecursive(a, b, a.length(), b.length());
    #elif ALGO == 2
        editDistanceRecursiveMemo(a, b, a.length(), b.length());
    #elif ALGO == 3
        editDistanceDP(a, b);
    #elif ALGO == 4
        editDistanceDPOptimized(a, b);
    #endif

    return 0;
}
