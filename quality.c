#include <stdio.h>
#include <stdlib.h>
#include "demo_shuffle.c"

int main () {
	
	demo_shuffle();
	int i;
	for( i = 5; i < 20; i++ ) {
		average_quality(i,5, 10);
	}

	printf("\n\n Check quality.txt for outout of average_quality()\n");
	return 0;

}

