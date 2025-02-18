#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <wait.h>

#define MIN_PID 300
#define MAX_PID 5000
int len = MAX_PID - MIN_PID;
int* map;

int allocate_map() {
	map = (int*)malloc(sizeof(int)*len);
	for (int i = 0; i < len; ++i) {
		map[i] = 0;
	}
	return 0;
}

int allocate_pid() {
	// find element that is = 0
	for (int i = 0; i < len; ++i) {
		if (map[i] == 0) {
			map[i] = 1; // set the value of that element to 1
			return i + MIN_PID; // add MIN_PID and return it
		}
	}
	return -1; // Return -1 if all PIDs are in use
}

void release_pid(int pid) {
	// subtract MIN_PID
	int index = pid - MIN_PID;
	// set corresponding index to 0
	map[index] = 0;
}

void* proc(void* param) {
	// simulated process
	// request pid (by calling allocate pid)
	// sleep for some random amount of time
	// release pid by calling release pid
	int pid = allocate_pid();
	int s = rand() % 3;
	printf("PID = %d sleep for %d seconds\n", pid, s);
	sleep(s);
	release_pid(pid);
	pthread_exit(0);
}

int main () {

	// initialize map
	if (allocate_map() < 0) return -1;
	// create 100 threads, simulating 100 processes
	pthread_t t[100];
	for (int i = 0; i < 100; ++i) {
		pthread_create(&(t[i]), NULL, proc, NULL);
	}
	// wait for all 100 threads to finish
	for (int i = 0; i < 100; ++i) {
		pthread_join(t[i], NULL);
	}
	free(map);
	return 0;
}