# Especificadores de formato em C... e algumas coisas a mais

Nessa aula......
// TODO

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

OBS: Podemos ver a documentação das funções no linux escrevendo ```man <nome_da_função>``` no terminal - porém, o *man* serve para todas as funções do linux, e as vezes as funções tem o mesmo nome em C e em bash, por exemplo. Aí, pode-se escrever ```man 3 <nome_da_função>``` no terminal, que pega a seção 3 do manual, que possui as funções do C.

## scanf

// TODO

## printf

// TODO

### stdin e stdout

// TODO

## sscanf

// TODO

## sprintf

// TODO

## getchar

// TODO

## puts

// TODO

## fgets

// TODO

## Outras

Existem ainda outras funções de leitura e escrita, algumas específicas para algumas coisas e tal. Porém, algumas não são tão úteis no geral, enquanto outras necessitam de um certo conhecimento de arquivos em C para serem entendidas, o que não é o objetivo dessa aula. Porém, vou citar algumas apenas para desencargo de consciência: *gets*, *fgetc*, *fputc*, *fscanf*, *fprintf*, *fread*, ...

# Buffer

// TODO

## Buffer de Entrada

// TODO

## Buffer de Saída

// TODO

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

## Exemplos práticos

Digamos que a entrada do seu programa é um horário no formato *hh:mm:ss*, e você quer salvar a hora, minuto e segundo em 3 inteiros separados. Como podemos fazer isso utilizando o scanf?

```C
int h, m, s; // hora, minuto e segundo
scanf("%d:%d:%d", &h, &m, &s); //le os inteiros ate os `:`
```

Bem de boas, certo? Vamos para outro exemplo agora: você receberá, no seu programa, duas palavras, separadas por um '#', e quer salvar cada palavra em um array de caracteres diferente. Por exemplo, considere a seguinte entrada:

*primeira#segunda*

Eu quero salvar "primeira" em um array, e "segunda" em outro. Também é possível fazer isso utilizando *scanf*, porém temos que tomar alguns cuidados.

Se seguirmos a mesma lógica do exercício anterior, teríamos o seguinte código:

```C
char str1[1024], str2[1024];
scanf("%s#%s", str1, str2);
```

Porém isso não promove o resultado esperado - com o *%s*, ocorreria a leitura de todos os caracteres até algum delimitador de espaço ou quebra de linha (*' ', '\n', '\r', ...*). Portanto, a *str1* receberia a entrada inteira (*primeira#segunda*), enquanto a *str2* ficaria vazia, pois o trick de colocar um *'#'* no meio do scanf foi totalmente inútil. Portanto, teríamos que fazer o seguinte código:

```C
char str1[1024], str2[1024];
scanf("%[^#]#%s", str1, str2);
```

O que essa máscara faz é o seguinte: ele vai lendo todos os caracteres até chegar no *#*. Quando chegar no *#*, ele irá descartar o *#* (perceba que tem um *#* jogado no meio do *scanf*, antes do segundo *%s*). Depois disso, ele vai ler a segunda string, até chegar em um caractere delimitador de espaço ou final de linha.

Isso pode parecer meio confuso no começo, mas vai ficar mais natural conforme se acostumar. Eu também recomendo testar várias combinações diferentes, e observar na prática como cada coisa funciona.

Vamos agora para outro exemplo. Ele será bem parecido com o anterior, mas tem uma diferença: a entrada do seu programa será duas **frases** separadas por *'#'*, e eu quero salvar cada frase em um array diferente. Ou seja, podem ter espaços entre as palavras da mesma frase, e eu quero considerar tudo isso para salvar nos meus arrays. Por exemplo, suponha a seguinte entrada: *primeira string#segunda string*. Veja (um exemplo de) o código para isso:

```C
char str1[1024], str2[1024];
scanf("%[^#]#%[^\n\r] ", str1, str2);
```

A leitura da primeira string não muda nada - ele continuará lendo tudo até chegar em um #. Porém, para a segunda string, perceba a entrada da máscara *[^\n\r]*. O que isso faz é que serão lidos todos os caracteres até que se chegue em um caractere delimitador de quebra de linha (*\n* ou *\r*), ou que a entrada do seu programa tenha acabado (por exemplo, se nao tiver quebra de linha, porem o arquivo chegou no final).

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