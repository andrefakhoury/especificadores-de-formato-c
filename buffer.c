#include <stdio.h>
#include <unistd.h>

int main() {
	for (int i = 1; i <= 5; i++) {
		printf("%d", i);
		sleep(1);
	}
	// espera tudo, imprime tudo junto

	for (int i = 1; i <= 5; i++) {
		printf("%d", i);
		fflush(stdout);
		sleep(1);
	}
	// imprime e espera, imprime e espera...

	for (int i = 1; i <= 5; i++) {
		printf("%d\n", i);
		sleep(1);
	}
	// imprime e espera, imprime e espera...
}