# Parallel Programming with OpenMP

This repository lists 4 problems solved using C. Each problem has its own serial and parallel implementations. For the latter, the OpenMP API was utilized.
The source code of this repository was developed for the "Parallel Programming for Machine Learning Problems" course conducted at the Department of Electrical and Computer Engineering, University of Patras, Greece.

## The repository outline is as follows:
### 1. **[K-means](https://en.wikipedia.org/wiki/K-means_clustering) serial implementation**
##### The algorithm
- **Step 0:** Create N random vectors: Vec[N][Nv].
- **Step 1:** Initialiaze the centers. Choose Nc unique vectors from Vec: Center[Nc][Nv].
- **Step 2:** For each Vec[N][Nv], calculate the minimum Euclidean distance from Center[Nc][Nv] and update Classes[N] based on the minimum distance.
- **Step 3:** Update Center[Nc][Nv] by calculating the average of the vectors that belong to the same class.
- **Step 4:** If the sum of the vector distances from their corresponding centers is less than a certain threshold, the algorithm finishes. If not go to step 2.
##### Versions
   - *Version 1:* Program outline.
   - *Versions 2-4:* Gradual implementation of each function.
   - *Version 5:* First working version. Global version uses global arrays.
   - *Version 6:* Elimination of printf calls.
   - *Version 7:* Added [SIMD](https://en.wikipedia.org/wiki/SIMD) (vector processing) directives.
### 2. **K-means with OpenMP:** A parallel implementation of the K-Means clustering algorithm
##### Versions
   - *Version 1:* Initial serial version.
   - *Version 2:* Added "omp parallel for" pragmas.
   - *Version 3:* Added "schedule" pragma.
   - *Version 4:* Added SIMD (vector processing), compiled with -O3.
### 3. **[Travelling salesman problem](https://en.wikipedia.org/wiki/Travelling_salesman_problem)**
##### Algorithm #1: Random search
- **Step 0:** Define a random route.
- **Step 1:** Calculate the total distance: tot_dist.
- **Step 2:** Swap two random cities.
- **Step 3:** Calculate the new total distance: tot_dist_new.
- **Step 4:** If tot_dist_new > tot_dist: undo the swap.
- **Step 5:** Repeat Step 2 to 4 for a fixed number of times.
##### Algorithm #2a: Heinritz-Hsiao Algorithm
- **Step 0:** Start from the initial city.
- **Step 1:** Find the nearest not-visited city. Travel to this city and update the current total travelled distance.
- **Step 2:** If you have visited every city add the distance from the city you are currently at to the initial city, to the total travelled distance. In this case, the algorithm finishes, otherwise go to Step 1.
##### Algorithm #2b
This algorithm is the same as Algorithm #2a except for:
- **Step 1:** Find the two nearest cities. Choose whether to travel to the nearest or the second nearest city with a probability other than 50%. Travel to the city of choice and
##### Versions
- *Version 1:* Serial implementation of Algorithm #1.
- *Version 2:* Parallel implementation of Algorithm #1.
- *Version 3:* Serial implementation of Algorithm #2a.
- *Version 4:* Serial implementation of Algorithm #2b.
- *Version 5:* Parallel implementation of Algorithm #2b.
### 4. **Neural networks** 
##### Neural network structure
The neural network is a fully-connected network consisting of 2 layers with 100 and 10 neurons, respectively. The input vector holds 12 values. The weights are stored in WL1[100][12+1] (+1 is for the bias) and WL2[10][100+1] for layer 1 and 2, respectively. The internal states of the neurons are stored in DL1[100] for layer 1 and DL2[10] for layer 2, whereas their corresponding outputs in OL1[100] and OL2[10].
##### Versions
   - *Version 1:* Serial implementation of the inference of the neural net.
   - *Version 2:* Serial implementation of the [error back-propagation](https://en.wikipedia.org/wiki/Backpropagation) algorithm for training the neural net.
   - *Version 3:* Parallel implementation of the error back-propagation algorithm.
   - *Version 4:* Added support to train the neural network using the  [Fashion MNIST](https://www.kaggle.com/zalando-research/fashionmnist) dataset and calculate its accuracy.
### 5. **[N queens problem](https://en.wikipedia.org/wiki/Eight_queens_puzzle)** 
##### The algorithm
- **Step 0:** Place a queen to (1,1), first row and first column, that is.
- **Step 1:** Place the next queen to the next column without being neither diagonally nor on the same row with another queen.
- **Step 2:** If Step 1 is not possible, move the queen of the previous column to a new row without violating the "not diagonal, not on tha same row" constraints. Then, proceed to Step 1.
- **Step 3:** The algorithm finishes either when a queen has been placed in every column, or when there is no position on the first column for the first queen. In the second case, there is no solution for the specific NxN chessboard.
##### Versions
   - *Version 1:* Serial implementation of the above algorithm.
   - *Version 2:* Parallel implementation of the above algorithm.
   - *Version 3:* Serial implementation of a [genetic algorithm](https://en.wikipedia.org/wiki/Genetic_algorithm) for solving the problem.
   - *Version 4:* Parallel implementation of the previous genetic algorithm.

---

### Author
Nick Roussos (Dipl. Eng. Electrical and Computer Engineering Department, Univ. of Patras, Greece)
  - Email: nroussos97 [at] gmail.com
