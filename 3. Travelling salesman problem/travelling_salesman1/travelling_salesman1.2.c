#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define NUM_CITIES 10
#define MAX_KM 1000
#define MAX_SEQUENCES 10

float CitiesX[NUM_CITIES+1];	//last city equals first
float CitiesY[NUM_CITIES+1];


void cities_init(void);

void print_cities(void);
void print_sequence(void);
void print_results(void);

void pick_cities(int *swapped_indices);
void swap(int *swapped_indices);

void calc_adjacent_dists(int *swapped_indices, float *prev_dists);
float update_distance(int *swapped_indices, float *prev_dists, float old_tot_dist);
float total_distance(void);
float distance(int city1, int city2);


int main(){
	int swapped_indices[2];
	float prev_dists[4];	//only 4 distances are affected by a swap
	
	cities_init();
	print_cities();

	float old_tot_dist = total_distance();
	float new_tot_dist = old_tot_dist;
	printf("Initial distance: %f\n", old_tot_dist);

	for (int i=0;i<MAX_SEQUENCES;i++){
		pick_cities(swapped_indices);
		calc_adjacent_dists(swapped_indices, prev_dists);
		swap(swapped_indices);
		new_tot_dist = update_distance(swapped_indices, prev_dists, old_tot_dist);


		printf("\n---------%d-------------\n", i);
		if(new_tot_dist >= old_tot_dist){	//worse total distance --> revert swap
			swap(swapped_indices);
		}else{
			old_tot_dist = new_tot_dist;	//better total distance --> update old distance
		}


		printf("Distance: %f\n", old_tot_dist);
		print_cities();
	}

	print_results();
	return 0;
}

void cities_init(void){
	for (int i=0;i<NUM_CITIES;i++){
		CitiesX[i] = MAX_KM*1.0*rand()/RAND_MAX;
		CitiesY[i] = MAX_KM*1.0*rand()/RAND_MAX;
	}
	//last city is the same as the starting one
	CitiesX[NUM_CITIES] = CitiesX[0];
	CitiesY[NUM_CITIES] = CitiesY[0];
}

void print_cities(void){
	for (int i=0;i<NUM_CITIES;i++){
		printf("City %d: (%.3f, %.3f)\n", i, CitiesX[i], CitiesY[i]);
	}
}

void print_results(void){

}

void pick_cities(int *swapped_indices){
	int ind1 = 1 + rand()%(NUM_CITIES-1);	//ind1 is in [1,NUM_CITIES-2], first (and last) are never swapped
	int ind2;
	float temp_x, temp_y;
	
	//make sure that the 2 indices selected are different
	do{
		ind2 = 1 + rand()%NUM_CITIES;
	}while(ind2==ind1);

	//store swapped indices
	swapped_indices[0] = ind1;
	swapped_indices[1] = ind2;
}

void calc_adjacent_dists(int *swapped_indices, float *adj_dists){
	for(int i=0;i<2;i++){
		*adj_dists++ = distance(swapped_indices[i], swapped_indices[i]-1);
		*adj_dists++ = distance(swapped_indices[i], swapped_indices[i]+1);
	}
}

void swap(int *swapped_indices){
	int ind1 = swapped_indices[0];
	int ind2 = swapped_indices[1];
	int tempX, tempY;

	tempX = CitiesX[ind1];
	tempY = CitiesY[ind1];
	CitiesX[ind1] = CitiesX[ind2];
	CitiesY[ind1] = CitiesY[ind2];
	CitiesX[ind2] = tempX;
	CitiesY[ind2] = tempY;
}

float update_distance(int *swapped_indices, float *prev_dists, float old_tot_dist){
	float new_dists[4];
	calc_adjacent_dists(swapped_indices, new_dists);	//calculate new neighboring distances




	printf("\nInd1=%d Ind2=%d\n", swapped_indices[0], swapped_indices[1]);
	print_cities();
	printf("\n\nOld distances\tNew distances\n");
	for(int i=0;i<4;i++){
		printf("%5.3f\t\t%5.3f\n", prev_dists[i], new_dists[i]);
	}








	//update total distance from the difference of only the 4 affected distances
	//instead of recalculating every distance
	for(int i=0;i<4;i++){
		old_tot_dist += new_dists[i] - prev_dists[i];	
	}
	return old_tot_dist;
}

float total_distance(void){
	float tot_dist = 0.0;
	for (int i=0;i<NUM_CITIES;i++){
		tot_dist += distance(i, i+1);
	}
	return tot_dist;
}

float distance(int city1, int city2){
	return sqrtf((CitiesX[city1] - CitiesX[city2])*(CitiesX[city1] - CitiesX[city2])+\
		(CitiesY[city1] - CitiesY[city2])*(CitiesY[city1] - CitiesY[city2]));
}
