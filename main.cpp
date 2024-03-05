#include <iostream>
#include "DisjointSet.h"
#include <fstream>
#include <string>
#include <map>


int print_image(){

    std::string filename = "./face.img.txt"; // Adjust the path as necessary
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


std::vector<std::vector<int> > readImage(const std::string& filename) { // Fixed angle brackets
    std::vector<std::vector<int> > image; // Fixed angle brackets
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::vector<int> row;
        for (size_t i = 0; i < line.length(); ++i) {
            char ch = line[i];
            row.push_back(ch == '+' ? 1 : 0);
        }
        image.push_back(row);
    }

    return image;
}


void findConnectedComponents(const std::vector<std::vector<int> >& image, DisjointSet& ds) { // Fixed angle brackets
    int M = image.size();    // Image height
    int N = image[0].size(); // Image width

    // Iterate through each pixel in the image
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            if (image[i][j] == 1) { // If it's a foreground pixel
                int current = i * N + j; // Convert 2D position to 1D in the DisjointSet

                // Check all 8 surrounding pixels for 8-way connectivity
                for (int di = -1; di <= 1; ++di) {
                    for (int dj = -1; dj <= 1; ++dj) {
                        if (di == 0 && dj == 0) continue; // Skip the current pixel itself

                        int ni = i + di; // New row index
                        int nj = j + dj; // New column index

                        // Check if the new indices are within the bounds of the image and it's a foreground pixel
                        if (ni >= 0 && ni < M && nj >= 0 && nj < N && image[ni][nj] == 1) {
                            int neighbor = ni * N + nj;
                            ds.union_sets(current, neighbor); // Fixed function name to match typical C++ naming conventions
                        }
                    }
                }
            }
        }
    }

    // Map each root to a component ID and count the sizes
    std::map<int, int> componentSizes;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            if (image[i][j] == 1) {
                int root = ds.find_set(i * N + j); // Fixed function name to match typical C++ naming conventions
                if (componentSizes.count(root) == 0) {
                    componentSizes[root] = 1;
                } else {
                    componentSizes[root]++;
                }
            }
        }
    }



    // Create a new image to label the components
    std::vector<std::vector<char> > labeledImage(M, std::vector<char>(N, ' ')); // Fixed angle brackets
    char label = 'a';
    for (std::map<int, int>::iterator it = componentSizes.begin(); it != componentSizes.end(); ++it) {
        if (it->second > 2) { // Filter out small components if needed
            for (int i = 0; i < M; ++i) {
                for (int j = 0; j < N; ++j) {
                    if (image[i][j] == 1 && ds.find_set(i * N + j) == it->first) {
                        labeledImage[i][j] = label;
                    }
                }
            }
            label++;
        }
    }



    // Output the labeled image
    for (size_t i = 0; i < labeledImage.size(); ++i) {
        for (size_t j = 0; j < labeledImage[i].size(); ++j) {
            std::cout << labeledImage[i][j] << " ";
        }
        std::cout << "\n";
    }


}

























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

    std::vector<std::vector<int> > image = readImage("./face.img.txt");

    //print_image();
    std::cout << image.size() << " ";
    DisjointSet ds(image.size() * image[0].size());

    // Find and label the connected components
    findConnectedComponents(image, ds);









    return 0;

}
