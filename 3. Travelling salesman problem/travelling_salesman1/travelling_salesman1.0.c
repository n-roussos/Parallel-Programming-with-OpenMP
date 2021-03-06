#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define NUM_CITIES 10
#define MAX_KM 1000
#define MAX_ITERATIONS 10

float Cities[NUM_CITIES+1][2];


void cities_init(void);

void print_cities(void);
void print_sequence(void);

void swap(void);

float update_distance(void);
float total_distance(void);
float distance(int city1, int city2);


int main(){
	cities_init();
	print_cities();
	for (int i=0;i<MAX_ITERATIONS;i++){
		
	}
	return 0;
}

void cities_init(void){
	for (int i=0;i<NUM_CITIES;i++){
		Cities[i][0] = MAX_KM*1.0*rand()/RAND_MAX;
		Cities[i][1] = MAX_KM*1.0*rand()/RAND_MAX;
	}
	//last city is the same as the starting one
	Cities[NUM_CITIES][0] = Cities[0][0];
	Cities[NUM_CITIES][1] = Cities[0][1];
}

void print_cities(void){
	for (int i=0;i<NUM_CITIES;i++){
		printf("City %d: (%.3f, %.3f)\n", i, Cities[i][0], Cities[i][1]);
	}
}

void swap(void){
	
}

float update_distance(void){
	return 0.0;
}

float total_distance(void){
	return 0.0;
}

float distance(int city1, int city2){
	return sqrtf((Cities[city1][0] - Cities[city2][0])*(Cities[city1][0] - Cities[city2][0])+\
		(Cities[city1][1] - Cities[city2][1])*(Cities[city1][1] - Cities[city2][1]));
}
