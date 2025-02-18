#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

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
	for (int i=0; i<len; ++i) {
		total += nums[i];
	}
	g_avg = (double) total / len;
	pthread_exit(0);
}

void* my_med(void* param) {
	int tmp;

	// Editing nums directly only because the order of elements is irrelevant otherwise
	for (int i = 0; i < len-1; ++i) {
		for (int j = 0; j < len-i-1; ++j) {
			if (nums[j] > nums[j+1]) {
				tmp = nums[j];
				nums[j] = nums[j+1];
				nums[j+1] = tmp;
			}
		}
	}

	if (len % 2 == 0) {
		g_med = (float)(nums[(len) / 2 - 1] + nums[(len) / 2]) / 2.0;
	}
	else {
		g_med = (float)nums[(len) / 2];
	}

	pthread_exit(0);	
}

void* my_std(void* param) {
	float tmp = 0.0;

	for (int i=0; i < len; ++i){
		tmp += (nums[i]- g_avg)*(nums[i]- g_avg);
	}

	g_std = (float)sqrt(tmp/len);

	pthread_exit(0);	
}

int main (int argc, char** argv) {

	len = argc-1;
	nums = (int*)malloc(sizeof(int)*len);
	for (int i=0; i<len; ++i) {
		nums[i] = atoi(argv[i+1]);
	}

	pthread_t tid1, tid2, tid3, tid4, tid5;
	pthread_create(&tid1, NULL, my_min, NULL);
	pthread_create(&tid2, NULL, my_max, NULL);
	pthread_create(&tid3, NULL, my_avg, NULL);
	pthread_create(&tid4, NULL, my_med, NULL);
	pthread_create(&tid5, NULL, my_std, NULL);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_join(tid3,NULL);
	pthread_join(tid4,NULL);
	pthread_join(tid5,NULL);
	printf("Min is %d\n", g_min);
	printf("Max is %d\n", g_max);
	printf("Avg is %f\n", g_avg);
	printf("Median is %f\n", g_med);
	printf("Std Dev is %f\n", g_std);

	free(nums);
	return 0;
}