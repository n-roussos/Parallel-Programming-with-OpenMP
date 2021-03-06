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
void calc_layer(double *vector_in, int dim_in, double *vector_out, int neurons, 
	double *w, double *y_arr);
double sigmoid(double y);

void activate_NN(double *vector_in);

void print_results(void);
void print_weights(void);
void print_array(double *arr, int length);


int main() {
	weights_init();
	print_weights();
	
	activate_NN(X);
	print_results();
	return 0;
}

void weights_init(void) {
	for(int neuron=0;neuron<L1_NEURONS;neuron++){
		for(int input=0;input<L1_DIM;input++){
			WL1[neuron][input] = (2.0 * rand() / RAND_MAX) - 1;	//[-1,1]
		}
	}
	
	for(int neuron=0;neuron<L2_NEURONS;neuron++){
		for(int input=0;input<L2_DIM;input++){
			WL2[neuron][input] = (2.0 * rand() / RAND_MAX) - 1;
		}
	}
}

void calc_layer(double *vector_in, int dim_in, double *vector_out, int neurons, 
	double *w, double *y_arr) {
	double y;
	double *vector_start = vector_in;
	
	for(int neuron=0;neuron<neurons;neuron++){
		//w0 corresponds to extra constant input 1
		y = *w++;	//no point in multiplying by 1
		for(int i=1;i<dim_in;i++){
			y += (*vector_in++) * (*w++);
		}
		//store neuron y and output
		*y_arr++ = y;
		*vector_out++ = sigmoid(y);
		
		//reset vector_in
		vector_in = vector_start;
	}
}

double sigmoid(double y){
	return 1/(1+exp(-y));
}

void activate_NN(double *vector_in) {
	calc_layer(vector_in, L1_DIM, OL1, L1_NEURONS, &WL1[0][0], DL1);
	calc_layer(OL1, L2_DIM, OL2, L2_NEURONS, &WL2[0][0], DL2);
}

void print_results(void){
	printf("\n----------DL1----------\n");
	print_array(DL1, L1_NEURONS);
	printf("\n----------OL1----------\n");
	print_array(OL1, L1_NEURONS);
	printf("\n----------DL2----------\n");
	print_array(DL2, L2_NEURONS);
	printf("\n----------OL2----------\n");
	print_array(OL2, L2_NEURONS);
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
	for(int i=0;i<length;i++){
		printf("%.3f ", arr[i]);
	}
	printf("\n");
}
