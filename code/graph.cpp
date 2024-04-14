// Random graph generation with specific number of cities

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <number_of_cities>" << std::endl;
        return 1;
    }

    std::ofstream file("graph.txt"); // output file
    
    int n = atoi(argv[1]); // convert command line argument to integer
    
    int maximumDistance = 1000; // maximum distance
    int graph[n][n];
    
    file << n << std::endl; // write the number of cities to the file
    
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (i == j) {
                graph[i][j] = 0;
            } else {
                graph[i][j] = (rand() % maximumDistance) + 1;
                graph[j][i] = graph[i][j];
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file << graph[i][j] << " ";
        }
        file << std::endl;
    }
    
    file.close();
    return 0;
}

//Compile the program: g++ graph.cpp -o graph.out
//execute the program: ./graph.out
