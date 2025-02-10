#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int g_min, g_max, len;
float g_avg, g_med, g_std;
int* nums;

void* my_min(void* param) {
	// fill later
	pthread_exit(0);
}

int main (int argc, char** argv) {

	len = argc-1;
	nums = (int*)malloc(sizeof(int)*len);
	for (int i=0; i<len; ++i) {
		nums[i] = atoi(argv[i+1]);
	}

	pthread_t tid;
	pthread_create(&tid, NULL, my_min, NULL);
	pthread_join(tid,NULL);
	printf("Min is %d/n", g_min);

	return 0;
}