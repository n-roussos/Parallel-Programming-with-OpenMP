#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 4


int ROWS_PLACED[N];	//only rows are needed, cols are incrementing
//example: ROWS_PLACED[4]={2,4,1,3} --> Coordinates={{2,0}, {4,1}, {1,2}, {3,2}}

bool VALID_ROWS[N][N] = {false};	//valid rows per column


void board_init();

void calc_next_valid(int col);
int get_next_valid(int col);
bool isvalid(int row, int col);

void print_board(void);


int main(){
	board_init();

	int tries = 1;	//first queen placed
	int valid_row;

	for(int col=0;col<N-1;){
		calc_next_valid(col);
		valid_row = get_next_valid(col);
		if(valid_row >=0){
			ROWS_PLACED[col++] = valid_row;		//place new queen
			tries++;
		}else{
			if(col == 0){
				printf("NO SOLUTION EXISTS\n");
				break;
			}
			col--;	//backtrack to previous column
		}
	}

	print_board();
	return 0;
}


void board_init(){
	for(int i=0;i<N;i++){
		ROWS_PLACED[i] = -1;	//no queens are placed
		VALID_ROWS[0][i] = true;	//all rows of the first column are valid
	}
	ROWS_PLACED[0] = 0;		//first queen is placed @(0,0)
}


//calculates valid rows of next column
void calc_next_valid(int col){

}


//checks whether coordinates (row, col) are valid
bool isvalid(int row, int col){
	return true;
}


//returns next valid row of current column
//returns -1 if no valid row is found
int get_next_valid(int col){
	return 0;
}

void print_board(void){
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			if(ROWS_PLACED[j] == i){
				printf("* ");
			}else{
				printf("- ");
			}
		}
		printf("\n");
	}
	printf("\nQUEEN = *\n");
}