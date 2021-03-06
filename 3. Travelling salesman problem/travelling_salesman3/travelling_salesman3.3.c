#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>


#define NUM_CITIES 10000
#define MAX_KM 1000

float CitiesX[NUM_CITIES+1];	//last city equals first
float CitiesY[NUM_CITIES+1];
int Sequence[NUM_CITIES+1];
bool Visited[NUM_CITIES+1];		//initial = false


void cities_init(void);

void print_cities(void);
void print_sequence(void);
void print_results(float final_dist);

bool is_not_visited(int city, int to_visit);

float find_nearest(int to_visit);
float distance(int city1, int city2);


int main(){
	float tot_dist = 0.0;
	
	cities_init();
	for(int to_visit=1;to_visit<NUM_CITIES;to_visit++){
		tot_dist += find_nearest(to_visit);
		if(to_visit%1000==0){
			printf("To visit: %4d Total distance: %.4f\n", to_visit, tot_dist);
		}
	}
	
	//lastly, add distance to return to starting city
	tot_dist += distance(Sequence[NUM_CITIES-1], NUM_CITIES);
	print_results(tot_dist);
	
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
	/*
	int cities_per_line = 15;
	
	for(int i=0;i<NUM_CITIES;i++){
		if((i+1)%cities_per_line != 0){
			printf("%d-->", Sequence[i]);
		}else{
			printf("%d-->\n", Sequence[i]);
		}
		
	}
	printf("%d\n", Sequence[NUM_CITIES]);
	*/
	printf("\nFinal distance: %.4f\n", final_dist);
}

//returns the distance of the last city in the sequence and its
//closest not visited city 
float find_nearest(int to_visit){
	float min_dist = 1e6;
	float dist;
	int nearest_city;
	
	for(int i=1;i<NUM_CITIES;i++){
		if(!Visited[i]){
			dist = distance(i, Sequence[to_visit-1]); //distance from last city on the sequence so far
			if(dist < min_dist){
				min_dist = dist;
				nearest_city = i;
			}
		}
	}
	
	//nearest city found --> update sequence and return distance
	Sequence[to_visit] = nearest_city;
	//mark as visited
	Visited[nearest_city] = true;
	return min_dist;
}


float distance(int city1, int city2){
	return sqrtf((CitiesX[city1] - CitiesX[city2])*(CitiesX[city1] - CitiesX[city2])+\
		(CitiesY[city1] - CitiesY[city2])*(CitiesY[city1] - CitiesY[city2]));
}
