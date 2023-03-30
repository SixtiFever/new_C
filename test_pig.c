/* testing examples */
#include <stdio.h>
#include <stdlib.h>
#include "pig.c"

#define Y 7
#define N 10

// runs a simple test case
void run_test() {
	char testCases[Y][N] = {"happy", "duck", "glove", "evil", "eight", "yowler", "crystal"};

    int i;
    for(i = 0; i < Y; i++){
        printf("%s => %s\n", testCases[i], pig(testCases[i]));
    }

}
