#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int nTotal;
int nCircle = 0;

void* count(void* param) {
	// repeat nTotal times
		// generate x and y in range of [-1,1]
		// if (x,y) is in circle of radius 1, nCircle += 1
	double x,y;

	for (int i = 0; i < nTotal; ++i) {
		x = (double) rand() / RAND_MAX * 2.0 - 1.0;		// rand()/max = num from 0 and 1
		y = (double) rand() / RAND_MAX * 2.0 - 1.0;		// We need [-1,1]

		if (sqrt((x*x)+(y*y)) < 1.0) {
			++nCircle;
		}
	}
}

int main (int argc, char** argv) {
	nTotal = atoi(argv[1]);

	pthread_t tid1;
	pthread_create(&tid1, NULL, count, NULL);
	pthread_join(tid1,NULL);

	printf("Pi estimate = %f\n", 4.0 * nCircle / nTotal);
	return 0;
}