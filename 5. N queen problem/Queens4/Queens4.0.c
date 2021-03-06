#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 8
#define POPULATION_SIZE 500
#define MUTATION_PROB 0.01


unsigned char POPULATION[POPULATION_SIZE][N];	//the population
unsigned char NEW_POPULATION[POPULATION_SIZE][N];	//next population
float ADD_FITNESS[POPULATION_SIZE];		//additive fitness values for each gene
int MAX_THREATS = 2;			//final result of max_threats is +1
/* COMMENT ABOUT MAX_THREATS
if all genes have max_threats, every single one of them has score 0 and sum_score=0
int that case we devide by zero to find each gene's probabilities
+1 prevents this
*/


void population_init(void);
void max_threats(void);

int evaluation(unsigned char *gene);
int fitness(void);
int select_gene(void);
void crossover(unsigned char *gene1, unsigned char *gene2);
void mutation(unsigned char *gene);
void update_population(void);

void print_gene(int gene, int generation);
void print_population(void);

int main(){
	int generation = 0;
	int gene1, gene2, found;
	
	population_init();
	max_threats();
	//sum must be 1
	ADD_FITNESS[POPULATION_SIZE-1] = 1.0;
	
	while(1){
		found = fitness();
		if(found >= 0) break;
		
		generation++;

		#pragma omp parallel for private(gene1, gene2)
		for(int pair=0;pair<POPULATION_SIZE/2;pair++){
			gene1 = select_gene();
			gene2 = select_gene();
			
			if(gene1 != gene2){
				#pragma omp critical
				crossover(NEW_POPULATION[gene1], NEW_POPULATION[gene2]);
			}
			#pragma omp critical
			{
			mutation(NEW_POPULATION[gene1]);
			mutation(NEW_POPULATION[gene2]);
			}
		}

		update_population();
	}
	print_gene(found, generation);
	return 0;
}

//calculates max threats for linear fitness function
void max_threats(void){
	#pragma omp simd reduction(+:MAX_THREATS)
	for(int i=2;i<N;i++) MAX_THREATS += i;
}

//initializes population. Instead of a string
//a byte array is used --> max(N) = 256 = max(queens)
void population_init(void){
	unsigned char random_row;

	#pragma omp parallel for private(random_row)
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
	int q1, q2;
	
	for(int i=0;i<N-1;i++){
		for(int j=i+1;j<N;j++){
			q1 = gene[i];
			q2 = gene[j];
			if((q1 == q2) ||			//horizontal threat
			(abs(q1-q2) == abs(i-j)))	//diagonial threat
				threats++;
		}
	}
	return threats;
}

//fitness function for each gene
//returns the gene which solves the problem
//returns -1 if no solution is found
int fitness(void){
	int  eval;
	int scores[POPULATION_SIZE], sum_score = 0, gene_score;			//use with linear fitness function
	//float scores[POPULATION_SIZE], sum_score = 0.0, gene_score;	//use with non-linear fitness function
	
	for(int gene=0;gene<POPULATION_SIZE;gene++){
		eval = evaluation(POPULATION[gene]);
		if(eval == 0) return gene;	//solution found
		gene_score = MAX_THREATS - eval;	//linear fitness function
		//gene_score = 1.0/eval;	//non-linear fitness function; eval cannot be 0
		sum_score += gene_score;
		scores[gene] = gene_score;
	}
	
	float acc = 0;
	for(int gene=0;gene<POPULATION_SIZE-1;gene++){	//last one is always 1.0
		acc += 1.0*scores[gene]/sum_score;
		ADD_FITNESS[gene] = acc;
	}

	return -1;
}

//crossover between two genes
void crossover(unsigned char *gene1, unsigned char *gene2){
	int split_point = rand()%N;
	int temp;
	
	if(split_point == N-1) return;	//no point in splitting
	
	#pragma omp simd
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
		//and mutate it into another random symbol
		gene[chosen_symbol] = rand()%N;
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
	#pragma omp parallel for
	for(int i=0;i<POPULATION_SIZE;i++){
		#pragma omp simd
		for(int j=0;j<N;j++){
			POPULATION[i][j] = NEW_POPULATION[i][j];
		}
	}
}

//prints a gene translated into a board
void print_gene(int gene, int generation){
	printf("\n--BOARD FOR GENE: %d IN GENERATION: %d--\n\n", gene, generation);
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			if(POPULATION[gene][j] == i)
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

