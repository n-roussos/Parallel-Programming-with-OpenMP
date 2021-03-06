#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 4
#define POPULATION_SIZE 4
#define MUTATION_PROB 0.01
#define NON_LINEARITY_COEFF 0.1


unsigned char POPULATION[POPULATION_SIZE][N];	//the population
unsigned char NEW_POPULATION[POPULATION_SIZE][N];	//next population
unsigned char POOL[N];			//all possible rows in the board
float ADD_FITNESS[POPULATION_SIZE];		//additive fitness values for each gene
int MAX_THREATS = 2;			//final result of max_threats is +1
/* COMMENT ABOUT MAX_THREATS
if all genes have max_threats, every single one of them has score 0 and sum_score=0
int that case we devide by zero to find each gene's probabilities
+1 prevents this
*/


void pool_init(void);
void population_init(void);
void max_threats(void);

int evaluation(unsigned char *gene);
void fitness(void);
int select_gene(void);
void crossover(unsigned char *gene1, unsigned char *gene2);
void mutation(unsigned char *gene);
void update_population(void);

void verbose(int generation);
void print_gene(int gene);
void print_population(void);

int main(){
	int generation = 0;
	int gene1, gene2, found = -1;
	
	pool_init();
	population_init();
	max_threats();
	
	print_population();
	while(1){
		printf("\n---GENERATION: %d---\n", ++generation);
		fitness();
		for(int j=0;j<POPULATION_SIZE;j++){
			printf("%.3f ",ADD_FITNESS[j]);
		}
		printf("\n\n\n");
	
		for(int pair=0;pair<POPULATION_SIZE/2;pair++){
			printf("PAIR: %d\n", pair+1);
			gene1 = select_gene();
			gene2 = select_gene();
			printf("Gene1: %d ", gene1);
			printf("Gene2: %d\n", gene2);
			
			if(gene1 != gene2){
				crossover(NEW_POPULATION[gene1], NEW_POPULATION[gene2]);
			}
			mutation(NEW_POPULATION[gene1]);
			mutation(NEW_POPULATION[gene2]);

			if(evaluation(NEW_POPULATION[gene1]) == 0)
				found = gene1;
			if(evaluation(NEW_POPULATION[gene2]) == 0)
				found = gene2;
		}

		update_population();
		print_population();
		if(found >= 0){
			print_gene(found);
			break;
		}
	}
	
	return 0;
}

//initializes pool (encoding). Instead of a string
//a byte array is used --> max(N) = 256 = max(queens)
void pool_init(void){
	for(int i=0;i<N;i++){
		POOL[i] = i;
	}
}

//calculates max threats for linear fitness function
void max_threats(void){
	for(int i=2;i<N;i++) MAX_THREATS += i;
}

//initializes population
void population_init(void){
	unsigned char random_row;

	for(int i=0;i<POPULATION_SIZE;i++){		//each gene
		for(int j=0;j<N;j++){				//each column
			random_row = (unsigned char)rand()%N;	//random row
			POPULATION[i][j] = random_row;
			NEW_POPULATION[i][j] = random_row;
		}
	}
}

//evaluation function
//calculates queen threats for a gene
int evaluation(unsigned char *gene){
	int threats = 0;
	
	for(int i=0;i<N-1;i++){
		for(int j=i+1;j<N;j++){
			if((gene[j] == gene[i]) ||	//horizontal threat
			(abs(gene[j]-gene[i]) == abs(j-i)))	//diagonial threat
				threats++;
		}
	}
	return threats;
}

//fitness function for each gene
void fitness(void){
	int scores[POPULATION_SIZE], gene_score;
	int sum_score = 0;			//use with linear fitness function
	//float sum_score = 0.0;	//use with non-linear fitness function
	
	for(int gene=0;gene<POPULATION_SIZE;gene++){
		gene_score = MAX_THREATS - evaluation(POPULATION[gene]);	//linear fitness function
		//gene_score = 1.0/(evaluation(POPULATION[gene])+NON_LINEARITY_COEFF)	//non-linear fitness function
		sum_score += gene_score;
		scores[gene] = gene_score;
	}
	
	float acc = 0;
	for(int gene=0;gene<POPULATION_SIZE;gene++){
		acc += 1.0*scores[gene]/sum_score;
		ADD_FITNESS[gene] = acc;
	}
}

//crossover between two genes
void crossover(unsigned char *gene1, unsigned char *gene2){
	int split_point = rand()%N;
	int temp;
	
	printf("\nSplit point: %d\n", split_point);
	if(split_point == N-1) return;	//no point in splitting
	for(int i=0;i<=split_point;i++){
		//swap
		temp = gene1[i];
		gene1[i] = gene2[i];
		gene2[i] = temp;
	}
}

//mutation of gene
void mutation(unsigned char *gene){
	int chosen_symbol;
	
	//with a MUTATION_PROB chance
	if(1.0*rand()/RAND_MAX <= MUTATION_PROB){
		//choose a random symbol in gene
		chosen_symbol = rand()%N;
		printf("chosen: %d\n", chosen_symbol);
		//and mutate it into another random symbol
		gene[chosen_symbol] = POOL[rand()%N];
	}	
}

//selects a gene based on its probability
int select_gene(void){
	float random_prob = 1.0*rand()/RAND_MAX;
	int i = 0;
	
	while(random_prob > ADD_FITNESS[i]) i++;
	return i;
}

//updates population after crossover and mutation
void update_population(void){
	//population = new population
	for(int i=0;i<POPULATION_SIZE;i++){
		for(int j=0;j<N;j++){
			POPULATION[i][j] = NEW_POPULATION[i][j];
		}
	}
}

//prints results for each generation
void verbose(int generation){
	printf("\n--GENERATION: %d--\n", generation);
	
}

//prints a gene translated into a board
void print_gene(int gene){
	printf("\n--BOARD FOR GENE: %d--\n\n", gene);
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			if(NEW_POPULATION[gene][j] == i)
				printf("* ");
			else
				printf("- ");
		}
		printf("\n");
	}
	printf("\n* = QUEEN\n");
}

void print_population(void){
	for(int i=0;i<POPULATION_SIZE;i++){
		for(int j=0;j<N;j++){
			printf("%d ", POPULATION[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

