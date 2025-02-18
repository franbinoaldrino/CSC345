#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main (int argc, char** argv) {
	int nTotal = atoi(argv[1]);
	double x,y;
	int nCircle;

	#pragma omp parallel for
	for (int i = 0; i < nTotal; ++i) {
		x = (double) rand() / RAND_MAX * 2.0 - 1.0;		// rand()/max = num from 0 and 1
		y = (double) rand() / RAND_MAX * 2.0 - 1.0;		// We need [-1,1]

		if (sqrt((x*x)+(y*y)) < 1.0) {
			++nCircle;
		}
	}

	// top in terminal, 1 to see all cpus

	printf("Pi estimate = %f\n", 4.0 * nCircle / nTotal);
	return 0;
}