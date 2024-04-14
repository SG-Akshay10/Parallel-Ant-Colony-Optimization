# Parallel-Ant-Colony-Optimization
Implementation of Ant Colony Optimization (ACO) algorithm in both serial and parallel versions to solve the Traveling Salesman Problem (TSP).

The project consists of four main files: graph.cpp, random.cpp, helpers.h, serial.cpp, and parallel.cpp.

The **graph.cpp** file is responsible for generating a random graph matrix that represents the distances between cities. It takes a command-line argument specifying the number of cities (e.g., 500) and generates a symmetric adjacency matrix with random distances between 1 and 1000 kilometers. The generated matrix is then saved to the graph.txt file, where the first line contains the number of cities, and the subsequent lines represent the adjacency matrix.

The **random.cpp** file generates a set of random numbers that will be used to select random starting cities for the ants in the Ant Colony Optimization (ACO) algorithm. It takes a command-line argument specifying the number of random numbers to generate (e.g., 100,000) and writes them to the random.txt file. The first line of the file contains the number of random numbers, and the subsequent lines represent the generated random numbers.

The **helpers.h** file is a header file that contains common functions used in both the serial and parallel implementations of the ACO algorithm. These functions include:

* **loadGraph**: Loads the graph matrix from the graph.txt file.
* **findNextCity**: Selects the next city to visit based on the pheromone trails and heuristic information.
* **computeBestCost**: Computes the cost of a given path.
* **updatePheromones**: Updates the pheromone trails based on the best path found.
* **copyIntegerArray and copyDoubleArray**: Helper functions for copying integer and double arrays.
    
The **serial.cpp** file contains the implementation of the serial version of the ACO algorithm. It starts by loading the graph and random numbers from the respective files. It then initializes the pheromone trails, best path, and current path. The algorithm then enters a loop, where for each iteration, a group of ants are sent to find the best path. The pheromone trails are updated based on the best path found, and the results (best cost and path) are written to the serial.txt file after each iteration. Finally, the best cost and execution time are printed.

The **parallel.cpp** file contains the implementation of the parallel version of the ACO algorithm using the Message Passing Interface (MPI). In this version, the graph and random numbers are first loaded in the master process (rank 0) and then broadcasted to all other processes. The ants are then distributed among the different nodes, and each node runs the ACO algorithm locally for a specified number of iterations. After the local iterations, the nodes exchange their best paths, and the master process updates the global pheromone trail. The master process then collects the best path from all the nodes and reports the overall best path. The results (best cost and path) are written to the parallel.txt file after each external iteration, and the final best cost and execution time are printed.

The parallel implementation allows for faster computation compared to the serial version by distributing the workload among the available nodes and leveraging the exchange of best paths to explore the search space more efficiently. The output files (serial.txt and parallel.txt) can be used for further analysis and comparison of the two versions.

## Performance Analysis

The main.py script is used to analyze the performance of the serial and parallel implementations of the Ant Colony Optimization algorithm.
How it Works

    The script reads the "Time consumed" values from the serial.txt and parallel.txt files and stores them in separate lists, serial_times and parallel_times, respectively.
    The script calculates the speedup and parallel efficiency using the following formulas:
        Speedup: speedup = [st / pt for st, pt in zip(serial_times, parallel_times)]
        Parallel Efficiency: parallel_efficiency = [s / len(parallel_times) for s in speedup]
    The script then creates a figure with two subplots using Matplotlib:
        The first subplot (Graph 1) displays the speedup on the y-axis and the number of processing elements (iterations) on the x-axis.
        The second subplot (Graph 2) displays the parallel efficiency on the y-axis and the number of processing elements (iterations) on the x-axis.
    The plots are labeled with appropriate titles, x-axis, and y-axis labels.
    Finally, the script displays the figure using plt.show().

## Output

The output of this script is a figure with two plots:

    Graph 1: N vs Speed Up
        This plot shows the speedup achieved by the parallel implementation compared to the serial implementation as the number of processing elements (iterations) increases.
        The speedup is calculated as the ratio of the serial execution time to the parallel execution time for each iteration.
    Graph 2: N vs Parallel Efficiency
        This plot shows the parallel efficiency of the parallel implementation as the number of processing elements (iterations) increases.
        The parallel efficiency is calculated as the ratio of the speedup to the number of processing elements (iterations).
        
![Performance Analysis Plots](https://github.com/SG-Akshay10/Parallel-Ant-Colony-Optimization/blob/bdf4943d7c427031ec30a854557d250a80bf320b/Output/Screenshot%20from%202024-04-14%2020-17-21.png)

![Performance Analysis Plots](https://github.com/SG-Akshay10/Parallel-Ant-Colony-Optimization/blob/main/Output/Screenshot%20from%202024-04-14%2021-09-34.png)



These plots can be used to analyze the performance and scalability of the parallel implementation of the Ant Colony Optimization algorithm. The speedup graph shows how much faster the parallel version is compared to the serial version, while the parallel efficiency graph indicates how well the parallel implementation is utilizing the available resources.

## Folder Description 

Ant Colony Optimization Algorithm

This project implements the Ant Colony Optimization (ACO) algorithm in both serial and parallel versions to solve the Traveling Salesman Problem (TSP).

The project consists of four main files: graph.cpp, random.cpp, helpers.h, serial.cpp, and parallel.cpp.

The graph.cpp file is responsible for generating a random graph matrix that represents the distances between cities. It takes a command-line argument specifying the number of cities (e.g., 500) and generates a symmetric adjacency matrix with random distances between 1 and 1000 kilometers. The generated matrix is then saved to the graph.txt file, where the first line contains the number of cities, and the subsequent lines represent the adjacency matrix.

## Folder Structure:

```
├── graph.cpp: Generates a random graph matrix (graph.txt)
├── graph.txt: Contains the input map (matrix) for the program
├── helpers.h: Header file with common functions for serial and parallel programs
├── parallel.cpp: Implementation of the parallel version of the Ant Colony algorithm using MPI
├── random.cpp: Generates a set of random numbers
├── random.txt: Contains the input random numbers for choosing random cities in each iteration
├── serial.cpp: Implementation of the serial version of the Ant Colony algorithm
```

## Compile and Run

### Generate input files

To compile and run this project first need to run graph.cpp and random.cpp that will generates the input files for the program.

Generates graph.txt file for the given number of cities (n=100) with maximum distance between two cities(1000kms)
```
g++ graph.cpp -o graph.out
./graph.out
```

Generates random.txt that utilizes for choosing random city in each iteration
```
g++ random.cpp -o random.out
./random.out <random_number>
```

### Run serial version of program

Given number of ants travel on all the city and most used edges are passed to the next iteration. After all iterations optimum path is provided. 
```
g++ serial.cpp -o serial.out
./serial.out <graph_file> <random_number_file> <number_of_ants> <number_of_iteration> 
e.g. ./serial.out graph.txt random.txt 32 150 1
```

### Run parallel version of program

In each external iteration every node iterates locally and provides optimum path to the master process. Finally master process decide optimum path after all external iterations.
```
mpic++ parallel.cpp -o parallel.out
./parallel.out <graph_file> <random_number_file> <number_of_ants> <number_of_external_iteration> <number_of_iteration_on_each_node>
e.g. ./parallel.out graph.txt random.txt 32 150 1
```


