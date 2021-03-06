#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>


#define NUM_CITIES 10
#define MAX_KM 1000

float CitiesX[NUM_CITIES+1];	//last city equals first
float CitiesY[NUM_CITIES+1];
int Sequence[NUM_CITIES+1];


void cities_init(void);

void print_cities(void);
void print_sequence(void);
void print_results(float final_dist);

bool is_not_visited(int city, int visited);

float find_nearest(int visited);
float distance(int city1, int city2);


int main(){
	float tot_dist = 0.0;
	
	cities_init();
	for(int visited=1;visited<=NUM_CITIES;visited++){
		tot_dist += find_nearest(visited);
	}
	
	
	return 0;
}

void cities_init(void){
	Sequence[0] = 0;
	for(int i=0;i<NUM_CITIES;i++){
		CitiesX[i] = MAX_KM*1.0*rand()/RAND_MAX;
		CitiesY[i] = MAX_KM*1.0*rand()/RAND_MAX;
	}
	//last city is the same as the starting one
	CitiesX[NUM_CITIES] = CitiesX[0];
	CitiesY[NUM_CITIES] = CitiesY[0];
	Sequence[NUM_CITIES] = 0;
}

void print_cities(void){
	for(int i=0;i<NUM_CITIES;i++){
		printf("City %d: (%.3f, %.3f)\n", i, CitiesX[i], CitiesY[i]);
	}
}

void print_results(float final_dist){

}

//returns the distance of the last city in the sequence and its
//closest not visited city 
float find_nearest(int visited){
	float min_dist = 1e6;
	float dist;
	int nearest_city;
	
	for(int i=1;i<NUM_CITIES;i++){
		if(is_not_visited(i, visited)){
			dist = distance(i, Sequence[visited-1]); //distance from last city on the sequence so far
			if(dist < min_dist){
				min_dist = dist;
				nearest_city = i;
			}
		}
	}
	
	//nearest city found --> update sequence and return distance
	Sequence[visited] = nearest_city;
	return min_dist;
}

bool is_not_visited(int city, int visited){
	for(int j=0;j<visited;j++){
		if(city == Sequence[j]) return false;
	}
	return true;
}


float distance(int city1, int city2){
	return sqrtf((CitiesX[city1] - CitiesX[city2])*(CitiesX[city1] - CitiesX[city2])+\
		(CitiesY[city1] - CitiesY[city2])*(CitiesY[city1] - CitiesY[city2]));
}
