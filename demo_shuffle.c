#include <stdio.h>
#include <stdlib.h>
#include "riffle.c"

// demonstrates the shuffle functionality on both an integer and string array.
// The shuffled arrays are printed out.
// The average quality of the integer array is printed out.
void demo_shuffle() {
	printf("** From demo_shuffle() **\n");
	int int_arr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
	char* str_arr[] = {"alpha","beta","gamme","delta","epsilon","zeta","eta","theta","iota","kappa","lambda","mu"};
	int i;
	riffle(int_arr, 20, sizeof(int), 2);
	printf("Shuffled integer array:\n");
	for( i = 0; i < 20; i++ ) {
		printf("%d ", int_arr[i]);
	}
	printf("\n\n");

	printf("Shuffled string array of greek letter names:\n");
	riffle(str_arr, 12, sizeof(char*), 19);	
	for( i = 0; i < 12; i++ ) {
		printf("%s ", str_arr[i]);
	}
	printf("\n\n");

	float q = quality(int_arr, 20);
	printf("The quality of shuffle for integer array is is %.2f\n", q);
}


