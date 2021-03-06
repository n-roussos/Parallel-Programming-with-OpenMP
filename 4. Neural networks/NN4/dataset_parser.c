#include <string.h>

void desired_init(void){
	for(int i=0;i<TRAIN_EXAMPLES;i++){
		for(int j=0;j<L2_NEURONS;j++){
			TRAIN_B[i][j] = ACTIVATION_VALUE_FALSE;
		}
	}
}

int parse_train(void){
	FILE *fp ;
	char B[BUFFER_SIZE+1] ;	//include \0
	char *p ;
	unsigned char true_class;
	
	//initialize desired trained outputs with ACTIVATION_VALUE_FALSE
	desired_init();
	
	
	fp = fopen( TRAINSET_PATH, "r" ) ;
	if ( fp == NULL )
		return -1 ;
	
	/* first line deleted manually
	if ( fgets( B, 2000, fp ) != B ) //fgets = fastest --> no data processing
		return -2 ;
	*/
	
	
	for( int i = 0 ; i < TRAIN_EXAMPLES ; i++ ){
		//it stops when either (n-1) characters are read, the newline character is read, or the end-of-file is reached, whichever comes first
		if ( fgets( B, BUFFER_SIZE, fp ) != B )
			return -2 ;
		
		p = strtok(B,",") ;	//replaces , with \0
		if ( p == NULL )
			return -3 ;
		
		true_class = atoi(p) ;
		TRAIN_CLASS[i] = true_class ;
		TRAIN_B[i][true_class] = ACTIVATION_VALUE_TRUE;
		
		for( int j = 0 ; j < PIXELS ; j++ )  {
			p = strtok(NULL,",\n" ) ;
			TRAIN_DATA[i][j] = atof(p) / MAX_PIXEL_VALUE ;	//normalize dataset
		}
	}

	fclose(fp) ;
	return 0;
}

int parse_test(void){
	FILE *fp ;
	char B[BUFFER_SIZE+1] ;	//include \0
	char *p ;
	
	fp = fopen( TESTSET_PATH, "r" ) ;
	if ( fp == NULL )
		return -1 ;
	
	/* first line deleted
	if ( fgets( B, 2000, fp ) != B ) //fgets = fastest --> no data processing
		return -2 ;
	*/
	
	
	for( int i = 0 ; i < TEST_EXAMPLES ; i++ ){
		//it stops when either (n-1) characters are read, the newline character is read, or the end-of-file is reached, whichever comes first
		if ( fgets( B, BUFFER_SIZE, fp ) != B )
			return -2 ;
		
		p = strtok(B,",") ;	//replaces , with \0
		if ( p == NULL )
			return -3 ;
		TEST_CLASS[i] = atoi(p) ;
		
		for( int j = 0 ; j < PIXELS ; j++ )  {
			p = strtok(NULL,",\n" ) ;
			TEST_DATA[i][j] = atof(p) / MAX_PIXEL_VALUE ;	//normalize dataset
			}
	}

	fclose(fp) ;
	return 0;
}



