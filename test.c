#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char* argv[]) {

	/** Convertendo numeros diretamente */
	int dec = 10; // dec = 10
	int oct = 010; // oct = 8
	int hex = 0x10; // hex = 16
	printf("%d %d %d\n", dec, oct, hex);

	long long bin = 0b10; // bin = 2
	printf("Binario: %lld\n", bin);

	printf("%d\n", 020); // 16
	printf("%i\n", 020); // 16

	/** Fazendo simulacao da leitura */
	char input[] = "010";
	int d, i;
	sscanf(input, "%d", &d); // d = 10
	sscanf(input, "%i", &i); // i = 8

	/** Trabalhando com ponto flutuante */
	printf("%lf\n", acos(-1.0)); // 6 casas decimais: 3.141593
	printf("%lf\n", 1.2345678);  // 6 casas decimais: 1.234568

	double dbl = 1.2345678;
	printf("|%15lf|\n", dbl);
	printf("|%.*lf|\n", 10, dbl);

	/** Erros de precisao... */
	double t1 = 1, t2 = 0;
	for (int i = 1; i <= 10; i++) t2 += 0.1;
	printf("t1: %.5lf t2: %.5lf == %d\n", t1, t2, t1 == t2);

	return 0;
}