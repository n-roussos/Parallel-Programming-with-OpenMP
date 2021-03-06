#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define APLHA 1

#define L1_NEURONS 3
#define L2_NEURONS 2

#define X_DIM 2
#define L1_DIM (X_DIM+1)
#define L2_DIM (L1_NEURONS+1)


double X[X_DIM] = {1,0};
double B[L2_NEURONS] = {0.9, 0.1};

double WL1[L1_NEURONS][L1_DIM];
double WL2[L2_NEURONS][L2_DIM];

double DL1[L1_NEURONS];
double DL2[L2_NEURONS];

double OL1[L1_NEURONS];
double OL2[L2_NEURONS];

double DELTA_L1[L1_NEURONS];
double DELTA_L2[L2_NEURONS];


void weights_init(void);
void calc_layer(double *vector_in, int dim_in, double *vector_out, int neurons, 
	double *w, double *y_arr);
	
double sigmoid(double y);
double sigmoid_derivative(double y);

void activate_NN(double *vector_in);

void update_deltas(void);
void update_weights(void);
void train_NN(double *vector_in, double *desired);

void print_results(void);
void print_weights(void);
void print_array(double *arr, int length);


int main() {
	weights_init();
	print_weights();
	
	activate_NN(X);
	print_results();
	
	update_deltas();
	
	printf("\n----------DELTA_L2----------\n");
	print_array(DELTA_L2, L2_NEURONS);
	printf("\n----------DELTA_L1----------\n");
	print_array(DELTA_L1, L1_NEURONS);

	update_weights();
	
	print_weights();
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

double sigmoid_derivative(double y){
	double temp = exp(-y);
	return temp/((1+temp)*(1+temp));
}

void activate_NN(double *vector_in) {
	calc_layer(vector_in, L1_DIM, OL1, L1_NEURONS, &WL1[0][0], DL1);
	calc_layer(OL1, L2_DIM, OL2, L2_NEURONS, &WL2[0][0], DL2);
}

void update_deltas(void){
	//output neurons
	for(int i=0;i<L2_NEURONS;i++){
		DELTA_L2[i] = sigmoid_derivative(DL2[i]) * (B[i] - OL2[i]); //equation III
	}
	
	//internal neurons
	double acc;
	for(int i=0;i<L1_NEURONS;i++){
		acc = 0.0;
		for(int k=0;k<L2_NEURONS;k++){
			acc += DELTA_L2[k] * WL2[k][i+1];	//NOTE:SIMD will need transpose
		}
		DELTA_L1[i] = sigmoid_derivative(DL1[i]) * acc;	//equation II
	}
}

void update_weights(void){
	double delta_i;

	//layer 1 weights
	for(int i=0;i<L1_NEURONS;i++){
		delta_i = DELTA_L1[i];
		WL1[i][0] += APLHA * delta_i;
		for(int j=1;j<L1_DIM;j++){
			WL1[i][j] += APLHA * delta_i * X[j-1];	//equation I
		}
	}

	//layer 2 weights
	for(int i=0;i<L2_NEURONS;i++){
		delta_i = DELTA_L2[i];
		WL2[i][0] += APLHA * delta_i;
		for(int j=1;j<L2_DIM;j++){
			WL2[i][j] += APLHA * delta_i * OL1[j-1];
		}
	}
}

void train_NN(double *vector_in, double *desired){
	
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
	printf("\n----------ERROR----------\n");
	double sum = 0;
	for(int i=0;i<L2_NEURONS;i++){
		sum += fabs(OL2[i]-B[i]);
	}
	printf("%.3f\n", sum);
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
