#include "helpers.h"
#include <chrono>
#include <fstream>

int main(int argc, char* argv[]) {
  int i, j, counter, ant_counter, cities_counter;
  int *graph = NULL;
  double *pheromones;
  int *bestPath;
  int *currentPath;
  long bestCost = 999999999;
  long nRandomNumbers = 0;
  long* randomNumbers;
  long random_counter = 0;
  char* graphFile = argv[1];
  char* randomFile = argv[2];
  int nAnts = atoi(argv[3]);;
  long iterations = atol(argv[4]);
  double alpha = 1;
  double beta = 1;
  double evaporation = 0.9;
  int nCities = 0;
  printf("Number of Iterations: %ld\n", iterations);
  printf("Number of Ants: %d\n", nAnts);
  start_time = time();

  std::ifstream in;
  in.open(graphFile);
  char out[12];
  in >> out;
  nCities = atoi(out);
  printf("Number of cities : %d\n", nCities);
  graph = (int*) malloc(nCities*nCities*sizeof(int));
  in.close();
  loadGraph(graphFile, graph); // Load the graph from graph.txt
  in.open(randomFile);
  in >> out;
  nRandomNumbers = atol(out);
  randomNumbers = (long*) malloc(nRandomNumbers*sizeof(long));
  i = 0;
  while (!in.eof()) {
    in >> out;
    randomNumbers[i] = atol(out); // load random.txt
    i++;
  }
  in.close();

  pheromones = (double*) malloc(nCities*nCities*sizeof(double));
  bestPath = (int*) malloc(nCities*sizeof(int));
  currentPath = (int*) malloc(nCities*sizeof(int));
  for (i = 0; i < nCities; i++) {
    currentPath[i] = -1;
    bestPath[i] = -1;
  }
  // initial pheromones value between cities with 0.1
  for (j = 0; j < nCities*nCities; j++) {
    pheromones[j] = 0.1;
  }

  // Create output file
  std::ofstream output_file("serial.txt", std::ios::out);

  counter = 0;
  long antsBestCost = 999999999;
  while (counter < iterations) {
    auto start = std::chrono::high_resolution_clock::now();
    for (ant_counter = 0; ant_counter < nAnts; ant_counter++) {
      for (i = 0; i < nCities; i++) {
        currentPath[i] = -1;
      }
      long rand = randomNumbers[random_counter];
      int currentCity = rand % nCities; // select a random start city
      random_counter = (random_counter + 1) % nRandomNumbers;
      currentPath[currentCity] = 0;
      for (cities_counter = 1; cities_counter < nCities; cities_counter++) {
        rand = randomNumbers[random_counter];
        currentCity = findNextCity(currentCity, currentPath, graph, nCities, pheromones, alpha, beta, rand); // Find next city
        random_counter = (random_counter + 1) % nRandomNumbers;
        currentPath[currentCity] = cities_counter;	// select next city
      }
      long oldCost = bestCost;
      bestCost = computeBestCost(bestCost, bestPath, currentPath, graph, nCities);
      if (oldCost > bestCost) {
        copyIntegerArray(currentPath, bestPath, nCities);
      }
    }
    if (bestCost < antsBestCost) {
      antsBestCost = bestCost;
    } 
    for (j = 0; j < nCities*nCities; j++) {
      pheromones[j] *= evaporation;
    }
    // Update pheromones
    updatePheromones(pheromones, bestPath, bestCost, nCities);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    // Write output to file
    output_file << "Iteration " << counter << ":" << std::endl;
    output_file << "Best cost: " << bestCost << std::endl;
    output_file << "Best path: ";
    for (int i = 0; i < nCities; i++) {
        output_file << bestPath[i] << " ";
    }
    output_file << std::endl;
    output_file << "Time consumed: " << duration << " ms" << std::endl;
    output_file << std::endl;

    counter++;
  }

  printf("Best Cost : %ld\n", bestCost);
  end_time = time();
  printf("Execution Time : %f\n", (end_time-start_time));

  // Close output file
  output_file.close();
  
  free(graph);
  free(pheromones);
  free(bestPath);
  free(currentPath);
  free(randomNumbers);
  return 0;
}