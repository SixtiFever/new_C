#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

float quality(int[],int);

void riffle_once(void* arr, int len, int size) {
    char* temp = malloc(size);
    int i, j;
    srand(time(NULL));

    for (i = len / 2, j = 0; i < len - 1; i++, j++) {
        // Choose a random cut point between i and len-1
        int cut;
        do {
            cut = rand() % len - 1;
        } while ( cut == -1 );

        // Swap the elements between i and cut and between cut+1 and j
        memcpy(temp, (char*)arr + i * size, size);
        memcpy((char*)arr + i * size, (char*)arr + cut * size, size);
        memcpy((char*)arr + cut * size, temp, size);

        memcpy(temp, (char*)arr + (cut + 1) * size, size);
        memcpy((char*)arr + (cut + 1) * size, (char*)arr + (len - j - 1) * size, size);
        memcpy((char*)arr + (len - j - 1) * size, temp, size);
        
    }

    free(temp);
}

void riffle(void *L, int len, int size, int N) {
int i;
  for( i = 0; i < N; i++ ) {
    riffle_once(L, len, size);
  }
}

float quality(int numbers[], int len) {
	int sum = 0;
	for ( int i = 0; i < len; i++ ) {
		if ( numbers[i+1] > numbers[i] ) {
			sum++;
		}
	}
	float quality = (float) sum / (float)(len-1);
	return quality;
}

void average_quality(int N, int shuffles, int trials) {
	// create arr of N numbers
	int arr[N];
	for( int i = 0; i < N; i++ ) {
		arr[i] = i;
	}
	int len = sizeof(arr) / sizeof(arr[0]);
	for( int j = 0; j < trials; j++ ) {
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

	//printf("\nAfter %d trials with %d shuffles each, the avg quality was %.2f\n", trials, shuffles, quality(arr,len));
}

