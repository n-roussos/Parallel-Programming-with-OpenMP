#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
FILE *fp ;
char B[20001], *p ;
int j ;

fp = fopen( "fashion-mnist_train.csv", "r" ) ;
if ( fp == NULL )
	return -1 ;

if ( fgets( B, 20000, fp ) != B ) 
	return -2 ;



for( j = 0 ; j < 60000 ; j++ )
{
if ( fgets( B, 20000, fp ) != B ) 
	return -2 ;

p = strtok(B,",") ;
if ( p == NULL )
	return -3 ;

for( int i = 0 ; i < 784 ; i++ )  {
	p = strtok(NULL,",\n" ) ;
	}
}

printf( "%d\n", j ) ;

fclose(fp) ;
return 0 ;
}





