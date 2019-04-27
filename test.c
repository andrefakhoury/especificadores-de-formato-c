#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char* argv[]) {
	printf("|%-3d|\n", 10);     // saída: | 10|
printf("|%-5.2f|\n", 3.14); // saída: | 3.14|
printf("|%-5s|\n", "oi");   // saída: | 3.14|

	return 0;

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
	char input[9999] = "010";
	int d, i;
	sscanf(input, "%d", &d); // d = 10
	sscanf(input, "%i", &i); // i = 8

	/** Trabalhando com ponto flutuante */
	double dbl = 1.2345678;

	printf("%lf\n", dbl);  // 6 casas decimais: 1.234568
	printf("|%.*lf|\n", 13, dbl);
	printf("|%15lf|\n", dbl);

	printf("___%3d___\n", 10); // ___ 10___
	printf("___%5.2f___\n", 3.14); // ___ 3.14___

	strcpy(input, "10:22:30");
	int h, m, s;
	sscanf(input, "%d:%d:%d", &h, &m, &s);
	printf("%d %d %d\n", h, m, s);

	strcpy(input, "str1#str2");
	char str1[1024], str2[1024];
	sscanf(input, "%[^#]#%s", str1, str2);
	printf("%s-%s\n", str1, str2);

	char tel1[15] = "(11)11111-1111";
	char tel2[15] = "\0";
	printf("|%-14s|\n", tel1);
	printf("|%-14s|\n", tel2);

	return 0;
}