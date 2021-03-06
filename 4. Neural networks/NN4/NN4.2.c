//DISCLAIMER: -fno-unsafe-math-optimizations me O3
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#include "consts.h"
#include "dataset_parser.c"



void weights_init(void);
	
double sigmoid(double y);
double sigmoid_derivative(double y);

void activate_NN(double *vector_in);

void update_deltas(double *desired);
void update_weights(double *vector_in);
void train_NN(double *vector_in, double *desired);

void print_results(void);
void print_weights(void);
void print_array(double *arr, int length);

double train_accuracy(void);
double test_accuracy(void);

int main() {
	double err;
	weights_init();
	printf("WEIGHTS INITIALIZED SUCCESSFULLY\n");
	
	int return_code = parse_train();
	int return_code2 = parse_test();
	if(return_code<0 || return_code2<0){
		printf("PARSE ERROR. EXITING...\n");
		return -1;
	}
	printf("FILES PARSED SUCCESSFULLY\n");

	for(int i=0;i<NUM_TRAIN;i++){
		train_NN(TRAIN_DATA[rand() % TRAIN_EXAMPLES], TRAIN_B[i]);
		/*
		if((i+1)%100000==0){
			print_array(OL2, L2_NEURONS);
			err = 0.0;
			#pragma omp simd
			for(int j=0;j<L2_NEURONS;j++){
				err += fabs(OL2[j] - TRAIN_B[i][j]);
			}
			printf("TRAIN: %3d ERROR: %.4f\n", i+1, err);
		}
		*/
	}
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

double sigmoid(double y){
	return 1/(1+exp(-y));
}

double sigmoid_derivative(double y){
	double temp = exp(-y);
	return temp/((1+temp)*(1+temp));
}

void activate_NN(double *vector_in) {
	double y;

	//internal layer
	#pragma omp parallel for private(y)
	for(int i=0;i<L1_NEURONS;i++){
		//w0 corresponds to extra constant input 1
		y = WL1[i][0];	//no point in multiplying by 1
		#pragma omp simd
		for(int j=1;j<L1_DIM;j++){
			y += vector_in[j-1] * WL1[i][j];
		}
		//store neuron y and output
		DL1[i] = y;
		OL1[i] = sigmoid(y);
	}

	//output layer
	for(int i=0;i<L2_NEURONS;i++){
		//w0 corresponds to extra constant input 1
		y = WL2[i][0];	//no point in multiplying by 1
		#pragma omp simd
		for(int j=1;j<L2_DIM;j++){
			y += OL1[j-1] * WL2[i][j];
		}
		//store neuron y and output
		DL2[i] = y;
		OL2[i] = sigmoid(y);
	}
}

void update_deltas(double *desired){
	double temp[L2_DIM][L2_NEURONS];
	
	//transpose WL2 for simd
	for(int i=0;i<L2_NEURONS;i++){
		for(int j=0;j<L2_DIM;j++){
			temp[j][i] = WL2[i][j]; 
		}
	}
	
	//output neurons
	for(int i=0;i<L2_NEURONS;i++){
		DELTA_L2[i] = sigmoid_derivative(DL2[i]) * (desired[i] - OL2[i]); //equation III
	}
	
	//internal neurons
	double acc;
	#pragma omp parallel for private(acc)
	for(int i=0;i<L1_NEURONS;i++){
		acc = 0.0;
		#pragma omp simd
		for(int k=0;k<L2_NEURONS;k++){
			acc += DELTA_L2[k] * temp[i+1][k];
		}
		DELTA_L1[i] = sigmoid_derivative(DL1[i]) * acc;	//equation II
	}
}

void update_weights(double *vector_in){
	double delta_i;

	//layer 1 weights
	#pragma omp parallel for private(delta_i)
	for(int i=0;i<L1_NEURONS;i++){
		delta_i = DELTA_L1[i];
		WL1[i][0] += ALPHA * delta_i;
		#pragma omp simd
		for(int j=1;j<L1_DIM;j++){
			WL1[i][j] += ALPHA * delta_i * vector_in[j-1];	//equation I
		}
	}

	//layer 2 weights
	for(int i=0;i<L2_NEURONS;i++){
		delta_i = DELTA_L2[i];
		WL2[i][0] += ALPHA * delta_i;
		#pragma omp simd
		for(int j=0;j<L2_DIM;j++){
			WL2[i][j] += ALPHA * delta_i * OL1[j-1];	//equation I
		}
	}
}

void train_NN(double *vector_in, double *desired){
	activate_NN(vector_in);
	update_deltas(desired);
	update_weights(vector_in);
}

double train_accuracy(void){
	double max;
	int predicted_class, correct = 0;

	//#pragma omp parallel for private(max,predicted_class, OL1, OL2)
	for(int i=0;i<TRAIN_EXAMPLES;i++){
		activate_NN(TRAIN_DATA[i]);	//predict
		max = OL2[0];
		predicted_class = 0;
		for(int j=1;j<L2_NEURONS;j++){
			if(OL2[j] > max){
				max = OL2[j];
				predicted_class = j;
			}
		}
		if(predicted_class == TRAIN_CLASS[i]){
			//#pragma omp atomic update
			correct++;
		}
	}
	return (1.0*correct/TRAIN_EXAMPLES)*100.0;
}

double test_accuracy(void){
	double max;
	int predicted_class, correct = 0;
	
	for(int i=0;i<TEST_EXAMPLES;i++){
		activate_NN(TEST_DATA[i]);	//predict
		max = OL2[0];
		predicted_class = 0;
		for(int j=1;j<L2_NEURONS;j++){
			if(OL2[j] > max){
				max = OL2[j];
				predicted_class = j;
			}
		}
		if(predicted_class == TEST_CLASS[i]) correct++;
	}
	return (1.0*correct/TEST_EXAMPLES)*100.0;
}

void print_results(void){
	printf("\n----------EVALUATION----------\n");
	printf("Train accuracy: %.3f%%\n", train_accuracy());
	printf("Test accuracy: %.3f%%\n", test_accuracy());
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
