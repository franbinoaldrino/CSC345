#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int g_min, g_max, len;
float g_avg, g_med, g_std;
int* nums;

void* my_min(void* param) {
	g_min = nums[0];
	for (int i=1; i<len; ++i) {
		if (g_min > nums[i])
			g_min = nums[i];
	}
	pthread_exit(0);
}

void* my_max(void* param) {
	g_max = nums[0];
	for (int i=1; i<len; ++i) {
		if (g_max < nums[i])
			g_max = nums[i];
	}
	pthread_exit(0);
}
void* my_avg(void* param) {
	int total = 0;
	for (int i=1; i<len; ++i) {
		total += nums[i];
	}
	g_avg = total / len;
	pthread_exit(0);
}

int main (int argc, char** argv) {

	len = argc-1;
	nums = (int*)malloc(sizeof(int)*len);
	for (int i=0; i<len; ++i) {
		nums[i] = atoi(argv[i+1]);
	}

	pthread_t tid1, tid2, tid3;
	pthread_create(&tid1, NULL, my_min, NULL);
	pthread_create(&tid2, NULL, my_max, NULL);
	pthread_create(&tid3, NULL, my_avg, NULL);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_join(tid3,NULL);
	printf("Min is %d\n", g_min);
	printf("Max is %d\n", g_max);
	printf("Avg is %f\n", g_avg);

	free(nums);
	return 0;
}