#include <stdio.h>
#include <stdlib.h>
#include "demo_shuffle.c"

int main () {
	
	demo_shuffle();
	for( int i = 5; i < 20; i++ ) {
		average_quality(i,5, 10);
	}
	return 0;

}

