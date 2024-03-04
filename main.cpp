#include <iostream>
#include "DisjointSet.h"
#include <fstream>
#include <string>
int main() {
    /*
    DisjointSet DisjointSet(9);
    DisjointSet.union_sets(1,3);
    DisjointSet.union_sets(1,5);
    DisjointSet.union_sets(1,7);
    DisjointSet.print_sets();
    DisjointSet.final_sets();
    //DisjointSet.union_sets(1,2);
    DisjointSet.print_sets();
     */

    std::string filename = "../face.img.txt"; // Adjust the path as necessary
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl; // Print each line to the console
    }

    file.close();
    return 0;

}
