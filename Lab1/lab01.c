#include <stdio.h>

int function1(int a, int b) {
	
	// returns a + b + 3
	int i = 0;
	int c = a + b;

	while (i < 3) {
		c = c + i;
		++i;
	}

	printf("function1 returns: %d\n", c);
	return c;
}

int main () {
	int result;
	int i = 0;
	
	result = function1(3,5); // returns 11

	while (i < 2) {
		result = result * 2;
		++i;
	}	// returns 44

	printf("main returns: %d\n", result); 
}