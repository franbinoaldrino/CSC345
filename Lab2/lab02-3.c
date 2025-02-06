#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char** argv) {
	pid_t pid = fork();
	if (pid > 0) {	// parent
		sleep(30);
	}
	return 0;
}