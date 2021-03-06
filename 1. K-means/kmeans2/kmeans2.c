#include <stdio.h>
#include <stdlib.h>

#define N 10
#define NV 2
#define NC 2
#define THRESHOLD 1.0e-6

float Vec[N][NV];
float Center[NC][NV];
int Class[N];

void vec_init(void);
void center_init(void);
void print_vec(void);
float estimate_class(void);
void estimate_center(void);


int main() {
	float tot_dist = 1.0e30;
	float prev_dist;

	vec_init();
	print_vec();
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
	//TODO
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