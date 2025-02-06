#include <sys/types.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>

const int SIZE = 4096;
const char *mailbox = "COLLATZ";
int shm_fd;
void *ptr;

int main(int argc, char** argv) {
	int n = atoi(argv[1]);
	pid_t id = fork();

	shm_fd = shm_open(mailbox, O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd, SIZE);
	ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

	// child will do calculations, send results to shared memory. child finishes, parent reads from shared memory and reads it out
	if (id == 0) { 			// child
		printf("Beginning child operations...\n");
		while (n > 1) {
			sprintf(ptr, "%d ", n);
			ptr += strlen(itoa(n));
			if (n % 2 == 0) {
				n = n/2;
			}
			else {
				n = 3*n + 1;
			}
		}
		printf(ptr, "%d\n", n);
		ptr += strlen(itoa(n));
		printf("Child complete\n");
	}
	else {					// parent
		wait(NULL);
		printf("Beginning parent operations...\n");

		ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
		printf("%s",(char *)ptr);
		shm_unlink(mailbox);
		printf("Parent complete\n");
	}
	return 0;
}