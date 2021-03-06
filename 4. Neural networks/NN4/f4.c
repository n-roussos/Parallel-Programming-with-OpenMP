#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double Data[60000][784] ;
unsigned char Class[60000] ;

// *****************************************************
int main()
{
FILE *fp ;
char B[20001], *p ;
int j ;

fp = fopen( "fashion-mnist_train.csv", "r" ) ;
if ( fp == NULL )
	return -1 ;

/* first line deleted
if ( fgets( B, 20000, fp ) != B ) 
	return -2 ;
*/


for( j = 0 ; j < 60000 ; j++ )
{
if ( fgets( B, 20000, fp ) != B ) 
	return -2 ;

p = strtok(B,",") ;
if ( p == NULL )
	return -3 ;
Class[j] = atoi(p) ;

for( int i = 0 ; i < 784 ; i++ )  {
	p = strtok(NULL,",\n" ) ;
	Data[j][i] = atof(p) ;
	}
}

printf( "%d\n", j ) ;
printf("%d\n", Class[0]);
fclose(fp) ;
return 0 ;
}





