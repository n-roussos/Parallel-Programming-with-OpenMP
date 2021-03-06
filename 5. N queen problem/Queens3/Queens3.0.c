#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 4
#define POPULATION_SIZE 10
#define MUTATION_PROB 0.01


char POOL[POPULATION_SIZE][N];	//the population
float EVAL[POPULATION_SIZE];	//evaluation values for each gene

void pop_init(void);

void evaluation(void);
void crossover(void);
void mutation(void);
void update_pool(void);

void verbose(int generation);

int main(){
	int generation = 0;
	
	
	return 0;
}


//initializes population
void pop_init(void){
	
}

//evaluation function for each gene
void evaluation(void){
	
}

//crossover between two random genes
void crossover(void){
	
}

//mutation of gene
void mutation(void){
	
}

//updates pool according to EVAL values
void update_pool(void){
	
}

//prints results for each generation
void verbose(int generation){
	
}
