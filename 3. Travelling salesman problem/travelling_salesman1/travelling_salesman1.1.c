#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define NUM_CITIES 10
#define MAX_KM 1000
#define MAX_SEQUENCES 10

float Cities[NUM_CITIES+1][2];	//last city equals first


void cities_init(void);

void print_cities(void);
void print_sequence(void);

void swap(int *swapped_indices);

float update_distance(int *swapped_indices);
float total_distance(void);
float distance(int city1, int city2);


int main(){
	int swapped_indices[2];

	cities_init();
	print_cities();
	float tot_dist = total_distance();
	printf("Initial distance: %f\n", tot_dist);
	for (int i=0;i<MAX_SEQUENCES;i++){
		swap(swapped_indices);
		tot_dist = update_distance(swapped_indices);

		printf("\n---------%d-------------\n", i);
		printf("Distance: %f\n", tot_dist);
		print_cities();
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

void swap(int *swapped_indices){
	int ind1 = 1 + rand()%NUM_CITIES;
	int ind2;
	float temp_x, temp_y;
	
	//make sure that the 2 indices selected are different
	do{
		ind2 = 1 + rand()%NUM_CITIES;
	}while(ind2==ind1);
	
	//store swapped indices
	swapped_indices[0] = ind1;
	swapped_indices[1] = ind2;
	
	//perform the swap
	temp_x = Cities[ind1][0];
	temp_y = Cities[ind1][1];
	Cities[ind1][0] = Cities[ind2][0];
	Cities[ind1][1] = Cities[ind2][1];
	Cities[ind2][0] = temp_x;
	Cities[ind2][1] = temp_y;
}

float update_distance(int *swapped_indices){
	
	return 0.0;
}

float total_distance(void){
	float tot_dist = 0.0;
	for (int i=0;i<NUM_CITIES;i++){
		tot_dist += distance(i, i+1);
	}
	return tot_dist;
}

float distance(int city1, int city2){
	return sqrtf((Cities[city1][0] - Cities[city2][0])*(Cities[city1][0] - Cities[city2][0])+\
		(Cities[city1][1] - Cities[city2][1])*(Cities[city1][1] - Cities[city2][1]));
}
