#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// *********************************************************
int main()
{
FILE *fp ;
char B[20001], *p ;

// Open File ....
fp = fopen( "fashion-mnist_train.csv", "r" ) ;
if ( fp == NULL )
	return -1 ;

// Read first line ....
if ( fgets( B, 20000, fp ) != B ) 
	return -2 ;

// Read second line ....
if ( fgets( B, 20000, fp ) != B ) 
	return -2 ;
//printf( "%s", B ) ;

// read first string before the first ","
p = strtok(B,",") ;
if ( p == NULL )
	return -3 ;
printf( "Class %s\n", p ) ;

// read the following numbers, the pixels intensity separated by ","
for( int i = 0 ; i < 784 ; i++ )  {
	p = strtok(NULL,",\n" ) ;
	printf( "%s ", p ) ;
	}
putchar('\n') ;


// close the file ...
fclose(fp) ;
return 0 ;
}





