#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//*****************************************************
int main()
{
FILE *fp ;
char B[20001] ;

fp = fopen( "fashion-mnist_train.csv", "r" ) ;
if ( fp == NULL )
	return -1 ;
if ( fgets( B, 20000, fp ) != B ) 
	return -2 ;
if ( fgets( B, 20000, fp ) != B ) 
	return -2 ;
printf( "%s", B ) ;
fclose(fp) ;
return 0 ;
}





