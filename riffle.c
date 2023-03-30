#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

float quality(int[],int);

// performs one riffle on the given array. Arguments:
// pointer to an array; array length, byte size of each 
// element.
void riffle_once(void* arr, int len, int size) {
    	// cast to char array
	char* temp;
	if( !( temp = malloc(size) ) ) {
		printf("Error assinging memory to temp array.\n");
	}
	int i, j;
	srand(time(NULL));

    for (i = len / 2, j = 0; i < len - 1; i++, j++) {
	// Choose a random cut point between i and len-1
	int cut;
	do {
	    cut = rand() % len - 1;
	} while ( cut == -1 );

	// Swap elements
	memcpy(temp, (char*)arr + i * size, size);
	memcpy((char*)arr + i * size, (char*)arr + cut * size, size);
	memcpy((char*)arr + cut * size, temp, size);

	memcpy(temp, (char*)arr + (cut + 1) * size, size);
	memcpy((char*)arr + (cut + 1) * size, (char*)arr + (len - j - 1) * size, size);
	memcpy((char*)arr + (len - j - 1) * size, temp, size);

    }

    free(temp);
}

// performs riffle_once N times. Takes in an array, 
// length, byte size of elements, and N for shuffle count.
void riffle(void *L, int len, int size, int N) {
int i;
  for( i = 0; i < N; i++ ) {
    riffle_once(L, len, size);
  }
}

// determines the quality of an array by 
// getting the average number of times the
// element on the right is greate than the 
// element on the left. Takes an array of 
// numbers and array length as arguments.
float quality(int numbers[], int len) {
	int sum = 0;
	int i;
	for ( i = 0; i < len; i++ ) {
		if ( numbers[i+1] > numbers[i] ) {
			sum++;
		}
	}
	float quality = (float) sum / (float)(len-1);
	return quality;
}

// Uses quality to determine the average quality of X trials.
// Takes in N to create an array of N elements, shuffles 
// is the number of time each riffle will shuffle the array,
// trials is the number of times riffle will run through.
void average_quality(int N, int shuffles, int trials) {
	// create arr of N numbers
	int arr[N];
	int i, j;
	for( i = 0; i < N; i++ ) {
		arr[i] = i;
	}
	int len = sizeof(arr) / sizeof(arr[0]);
	for( j = 0; j < trials; j++ ) {
		riffle(arr, len, sizeof(int), shuffles);	
	}
		// print quality to file
		float q = quality(arr,len);
		char buffer[32];
		FILE *fp;
		fp = fopen("quality.txt", "a");
		if ( fp == NULL ) {
			printf("Error opening file\n");
		}
		fputs("quality is ", fp);
		sprintf(buffer, "%.2f", q);
		fputs(buffer, fp);
		fputs("\n", fp);
		fclose(fp);
}

