#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define L1_NEURONS 3
#define L2_NEURONS 2

#define X_DIM 2
#define L1_DIM (X_DIM+1)
#define L2_DIM (L1_NEURONS+1)


double X[X_DIM] = {1,0};

double WL1[L1_NEURONS][L1_DIM];
double WL2[L2_NEURONS][L2_DIM];

double DL1[L1_NEURONS];
double DL2[L2_NEURONS];

double OL1[L1_NEURONS];
double OL2[L2_NEURONS];


void weights_init(void);
void calc_layer(double *vector_in, double *vector_out);
void activate_NN(double *vector_in);

void print_weights(void);
void print_array(double *arr, int length);


int main() {
	weights_init();
	print_weights();
	return 0;
}

void weights_init(void) {
	for(int neuron=0;neuron<L1_NEURONS;neuron++){
		for(int input=0;input<L1_DIM;input++){
			WL1[neuron][input] = (2.0 * rand() / RAND_MAX) - 1;
		}
	}
	
	for(int neuron=0;neuron<L2_NEURONS;neuron++){
		for(int input=0;input<L2_DIM;input++){
			WL2[neuron][input] = (2.0 * rand() / RAND_MAX) - 1;
		}
	}
}

void calc_layer(double *vector_in, double *vector_out) {

}

void activate_NN(double *vector_in) {

}

void print_weights(void) {
	printf("----------WL1----------\n");
	for(int neuron=0;neuron<L1_NEURONS;neuron++){
		for(int input=0;input<L1_DIM;input++){
			printf("%.3f ", WL1[neuron][input]);
		}
		printf("\n");
	}
	
	printf("\n----------WL2----------\n");
	for(int neuron=0;neuron<L2_NEURONS;neuron++){
		for(int input=0;input<L2_DIM;input++){
			printf("%.3f ", WL2[neuron][input]);
		}
		printf("\n");
	}
}

void print_array(double *arr, int length) {

}
