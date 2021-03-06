#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 100000
#define NV 1000
#define NC 100
#define THRESHOLD 1.0e-6

float Vec[N][NV];
float Center[NC][NV];
int Class[N];

void vec_init(void);
void center_init(void);
void unique_vects(int *a, int lenA);
void print_vec(void);
float estimate_class(void);
float distance(float *vector, float *center);
void estimate_center(void);
void vect1D_init(float *a, int lenA);
void vector_add(float *vect_dest, float *vect_src, int len);
void vector_average(int n_center, float *vect_src, int len, int divisor);
void print_centers(void);


// *******************************************************************
#pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline", "unsafe-math-optimizations")
#pragma GCC option("arch=native","tune=native","no-zero-upper")
//************************************************************


int main() {
	float tot_dist = 1.0e30;
	float prev_dist;
	int step = 1;

	vec_init();
	//print_vec();
	//printf("\n\n");
	center_init();
	do {
		prev_dist = tot_dist;
		tot_dist = estimate_class();
		printf("Step: %d\tTotal distance: %f\n", step++, tot_dist);
		estimate_center();
		//print_centers();
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
			//printf("%f ", Center[i][j]);
		}
		//printf("\n");
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

//**************************MODIFIED*********************
//returns the total minimum distance
float estimate_class(void) {
	float tot_dist = 0.0;
	float min_dist, dist;
	int cnt, class_num;
	float * i_ptr, *j_ptr;
	int *class_ptr=Class;
	for(i_ptr=Vec[0];i_ptr<=Vec[N-1];i_ptr+=NV){
		min_dist = distance(i_ptr, Center[0]);	//distance from first center = initial min
		class_num = 0;							//corresponding classification is 0
		cnt = 0;
		for(j_ptr=Center[1];j_ptr<=Center[NC-1];j_ptr+=NV){
			dist = distance(i_ptr, j_ptr);
			cnt++;
			if(dist < min_dist){
				min_dist = dist;	//update min distance
				class_num = cnt;	//update classification
			}
		}
		tot_dist += min_dist;		//add final min_dist
		*class_ptr++ = class_num;	//update Class array with the final ith vector classification
	}
	return tot_dist;
}

//**************************MODIFIED*********************
//returns the square of the Euclidian distance of a vector & a center
float distance(float *vector, float *center){
	float dist = 0.0, temp, *last = &vector[NV-1];
	while(vector<=last){
		temp = *vector++ - *center++;
		dist+=temp*temp;
	};
	return dist;
}

void estimate_center(void) {
	int n_center,n_vector,vector_dim;
	int cnt = 0;
	float vector_sum[NV];
	for(n_center=0;n_center<NC;n_center++){
		vect1D_init(vector_sum, NV);	//accumulator = 0
		cnt = 0;						//num of class members = 0
		for(n_vector=0;n_vector<N;n_vector++){
			if(Class[n_vector] == n_center){
				vector_add(vector_sum, Vec[n_vector], NV);	//update accumulator
				cnt++;										//+1 class member
			}
		}
		vector_average(n_center, vector_sum, NV, cnt);
	}
}

void vect1D_init(float *a, int lenA){
	int i;
	for(i=0;i<lenA;i++){
		a[i] = 0;
	}
}

void vector_add(float *vect_dest, float *vect_src, int len){
	int i;
	for(i=0;i<len;i++){
		vect_dest[i] += vect_src[i];
	}
}

void vector_average(int n_center, float *vect_src, int len, int divisor){
	int i;
	for(i=0;i<len;i++){
		Center[n_center][i] = vect_src[i] / divisor;
	}
}

void print_centers(void){
	int i, j;
	for (i = 0; i < NC; i++) {
		for (j = 0; j < NV; j++) {
			printf("%f ", Center[i][j]);
		}
		printf("\n");
	}
}
