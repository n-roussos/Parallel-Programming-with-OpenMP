#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 10
#define NV 2
#define NC 2
#define THRESHOLD 1.0e-6

//tha einai terastioi -> kakia idea ws orismata (mpainoun sto stack)
float Vec[N][NV];
float Center[NC][NV];
int Class[N];

void vec_init(void);
void center_init(void);
void unique_vects(int *a, int lenA);
void print_vec(void);
float estimate_class(void);
void estimate_center(void);


int main() {
	float tot_dist = 1.0e30;
	float prev_dist;

	vec_init();
	print_vec();
	printf("\n\n");
	center_init();
	do {
		prev_dist = tot_dist;

		tot_dist = estimate_class();
		estimate_center();
	} while (((prev_dist-tot_dist)/tot_dist) > THRESHOLD);
	return 0;
}

void vec_init(void) {
	int i, j;
	for (i = 0; i < N;i++) {
		for (j = 0; j < NV; j++) {
			Vec[i][j] = (1.0*rand()) / RAND_MAX;
		}
	}
}

void center_init(void) {
	int i,j;
	int unique_vector_indices[NC];
	unique_vects(unique_vector_indices, NC);
	for(i=0;i<NC;i++){
		for(j=0;j<NV;j++){
			Center[i][j] = Vec[unique_vector_indices[i]][j];
			printf("%f ", Center[i][j]);
		}
		printf("\n");
	}

}


void unique_vects(int *a, int lenA){
	int i,j;
	bool is_unique;
	a[0] = rand() % N;
	for(i=1;i<lenA;i++){
		while(1){
			a[i] = rand() % N;
			is_unique = true;
			for(j=0;j<i;j++){
				if(a[i] == a[j]){	//vector not unique
					is_unique = false;
					break;
				}
			}
			if(is_unique) break;
		}
	}
}

void print_vec(void) {
	int i, j;
	for (i = 0; i < N; i++) {
		for (j = 0; j < NV; j++) {
			printf("%f ", Vec[i][j]);
		}
		printf("\n");
	}
}

//returns the total minimum distance
float estimate_class(void) {
	//TODO
}

void estimate_center(void) {
	//TODO
}
