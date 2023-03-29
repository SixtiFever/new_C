// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test_pig.c"



int main() {
	printf("Running tests:\n");
	run_test();
	printf("\n");

	while(1) {
		char sentence[1000];
		printf("\nEnter a sentence: ");
		fgets(sentence, MAX_SENTENCE_LENGTH, stdin);

		char* word = strtok(sentence, " ");
		while( word != NULL ) {
			char *cipher = pig(word);
			printf("%s ", cipher);
			word = strtok(NULL, " ");
		}
	}
	return 0;
}
 
