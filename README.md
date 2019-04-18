# Formatando números inteiros

Em C, podemos declarar um *int* da seguinte forma:

```C
int dec = 10; // dec = 10
int oct = 010; // oct = 8
int hex = 0x10; // hex = 16
```

Ou seja, se colocarmos um valor sem *0* a esquerda, ele será convertido para a base 10. Se colocarmos *0* antes do número, ele será convertido para a base 8. Se colocarmos *0x* antes do número, ele será convertido para a base 16.

Também existe uma [extensão do GCC](https://gcc.gnu.org/onlinedocs/gcc/Binary-constants.html) que faz a mesma coisa para binário, e podemos escrever o seguinte código:

```C
int bin = 0b10; // bin = 2
```

# Principais funções para *scan* e *print* em C

Padrão: *scanf* e *printf*.

Podemos ver a documentação das funções no linux escrevendo ```man <nome_da_função>``` no terminal.

# Especificadores de Formato

Vou falar rapidão aqui sobre especificadores de formato da linguagem C, utilizados, principalmente, nas funções de *scanf* e *printf*.

Bom começamos do básico. Podemos formular essa pequena tabela, que por si só já consegue nos dar uma boa noção das coisas.

| Format specifier | Description                                    |  Supported Data Types                       |
|------------------|------------------------------------------------|---------------------------------------------|
| %c               | Character                                      |  char unsigned char                         |
| %d               | Signed Integer                                 |  short unsigned short int long              |
| %e or %E         | Scientific notation of float values            |  float double                               |
| %f               | Floating point                                 | float                                       |
| %g or %G         | Similar as %e or %E                            |  float double                               |
| %hi              | Signed Integer (Short)                         | short                                       |
| %hu              | Unsigned Integer (Short)                       | unsigned short                              |
| %i               | Signed Integer                                 |  short unsigned short int long              |
| %l or %ld or %li | Signed integer                                 |  long                                       |
| %lf              | Floating point                                 | double                                      |
| %Lf              | Floating point                                 | long double                                 |
| %lu              | Unsigned integer                               |  unsigned int unsigned long                 |
| %lli or %lld     | Signed integer                                 | long long                                   |
| %llu             | Unsigned integer                               | unsigned long long                          |
| %o               | Octal representation of Integer                |  short unsigned short int unsigned int long |
| %p               | Address of pointer to void void*               | void *                                      |
| %s               | String                                         | char *                                      |
| %u               | Unsigned Integer                               |  unsigned int unsigned long                 |
| %x or %X         | Hexadecimal representation of Unsigned Integer |  short unsigned short int unsigned int long |
| %n               | Prints nothing                                 |                                             |
| %%               | Prints % character                             |                                             |

## Alguns exemplos no scanf

![Exemplos do scanf - valeu Braulio](https://i.imgur.com/Sj4uSsb.jpg)

## Diferença entre %i e %d

Eles são a mesma coisa quando usados no output, como no *printf*.

```C
printf("%d\n", 020); //Saida: 16
printf("%i\n", 020); //Saida: 16
```

Porém, quando utilizadas como especificadoras de input, como no *scanf*, as máscaras são diferentes. *%d* faz a leitura de um integer como um número decimal normal, porem o *%i*, além de ler um número decimal, também converte a entrada para octal ou hexadecimal, de acordo com os prefixos *0* (octal) e *0x* (hexadecimal).

Ou seja, suponha a entrada *020* no código abaixo:
```c
scanf("%d", &n); // n = 20
scanf("%i", &n); // n = 16
```

# Referências

https://en.cppreference.com/w/cpp/language/types

https://www.geeksforgeeks.org/format-specifiers-in-c/

https://www.lix.polytechnique.fr/~liberti/public/computing/prog/c/C/FUNCTIONS/format.html

http://a4academics.com/tutorials/77-c-programming/690-c-format-specifiers

http://www.cplusplus.com/reference/cstdio/scanf/

https://wpollock.com/CPlus/PrintfRef.htm

http://www.mobidev.com/shalan/scanf_printf.htm

https://homepages.dcc.ufmg.br/~rodolfo/aedsi-2-10/printf_scanf/printfscanf.html

https://stackoverflow.com/questions/2611764/can-i-use-a-binary-literal-in-c-or-c

https://codeforwin.org/2015/05/list-of-all-format-specifiers-in-c-programming.html
