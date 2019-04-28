# Scanf, Armazenamento de Dados e outras bruxarias
Um resumão para você, bixão das programações, nunca mais sofrer na hora de ler valores no seu terminal.

## Tópicos da Aula
 - Scanf, o que é? Como vive? Do que se alimenta?
 - A importância dos tipos de dados no C.
 - Um pouco sobre a memória e o endereçamento de variáveis.
 - Botando a mão na massa! Os especificadores de formatos!
 - Buffer de dados e processamento de I/O
 - Utilizando máscaras para leitura de dados
 - Alguns cuidados adicionais

## Scanf, o que é? Como vive? Do que se alimenta?
	
Podemos facilmente definir o scanf, junto com o printf, como as principais ferramentas para leitura e escrita de dados na linguagem C (ambas presentes na biblioteca <stdio.h>). 

O uso dessa função é bastante simples para você, usuário final, pois **a mesma encapsula todo o pipeline de processamento de dados lidos no terminal, restando como sua principal tarefa aprender a utilizar corretamente os especificadores que a mesma define** (mostraremos como fazer isso nos tópicos adiantes).

Porém, apesar de seu uso ser simples, um bom entendimento de seu funcionamento pode facilitar e evitar muitas dores de cabeça que ocorrem frequentemente (e que iremos citar a seguir). Além disso, esses detalhes mais técnicos podem te ajudar a entender temas como o comportamento de variáveis na memória RAM e leitura de arquivos (uma das matérias que vocês verão próximos ao fim do semestre).

Por fim, antes de entrar em detalhes sobre a função em si, vamos relembrar algumas coisas sobre tipos de dados em C e também sobre endereços de memória!

## A importância dos tipos de dados no C
Caso você não lembre, C é uma linguagem de programação com tipagem forte e estática. Em outras palavras, é obrigatório declarar no programa qual será o tipo de dado que determinada variável irá manipular, sendo impossível alterar o tipo da variável no decorrer do programa.

Qual a importância da tipagem de dados? É muito simples, o tipo de dado irá definir algumas características da variável, como por exemplo:

 - **Tamanho da variável:** Quantos bytes de memória uma variável daquele tipo consome da RAM.
 - **Valores:** O tipo de dado define o intervalo de valores que aquele dado representa. Um tipo `char`, por exemplo, consegue representar até 2^8^ valores (vide tabela ASCII), enquanto um `int` consegue representar 2^32^ valores distintos.
 - **Operações:** O tipo de dado também define quais operações o programador poderá realizar com a variável. Valores numéricos, por exemplo, podem realizar operações aritméticas. Contudo, não podemos simplesmente somar dois vetores.

Sabemos, portanto, que mesmo que uma variável do tipo `float` e uma do tipo `int` ocupem o mesmo tamanho de bits na memória, a linguagem C irá interpretar e armazenar seus valores de maneira totalmente distintas na memória RAM. Faça o teste você mesmo:à 

```c
    float a =  4.0;
    int* ptrA = (int*) &a;
    printf("Lendo float como se fosse uma variável int: %d \n", *ptrA);
```

## Um pouco sobre a memória e o endereçamento de variáveis
Agora que lembramos sobre a importância da tipagem de dados para a linguagem C, vamos discutir brevemente sobre como a declaração de variáveis prepara espaços na memória RAM para serem utilizados pelo nosso programa.

Vamos supor que declaremos um conjunto de variáveis na main da seguinte forma:

```c
    int a, b;
    double x;
    char i, j, k;
    printf("%p\n%p\n%p\n%p\n%p\n%p\n", &a, &b, &x, &i, &j, &k);
```

Você irá notar que todos esses endereços são vizinhos e que eles possuem a distancia correspondente ao tamanho em bytes ocupado por cada tipo de dados. Esse comportamento se deve ao fato de suas variáveis declaradas serem inseridas na Stack assim que o programa inicia sua execução (caso queira saber mais, pesquise sobre Memory Layout da linguagem C).

Na tabela a seguir, vamos simular como o programa acima montaria a stack para receber as variáveis declaradas:

|**Endereço**|**Variável**|**Tamanho**|
|--|--|--|
|0x270E|char k|1 byte|
|0x270D|char j|1 byte|
|0x270C|char i|1 byte|
|0x2708|float x|4 bytes|
|0x2704|int b|4 bytes|
|0x2700|int a|4 bytes|

Tendo em mente o conceito de tipos de dados e armazenamento de dados na memória, nós já podemos a começar a explicar como a função scanf() faz para ler os dados do seu terminal e transformá-los em valores para serem inseridos nas variáveis de seu programa.

## Botando a mão na massa! Os especificadores de formatos!
Como vimos anteriormente, ao declararmos variáveis no nosso programa, estamos liberando espaços na memória para que nossos valores sejam lidos. Iremos então utilizar a função `scanf()` para realizar a leitura desses dados. Nossa função terá o seguinte formato: `int scanf(const char* format, ...)`.

No primeiro parâmetro, iremos enviar uma `string` que dirá como os dados vindos do `stdin` devem ser interpretados pela função. Será, portanto, nesse momento que iremos definir quantas variáveis queremos ler, quais serão seus tipos de dados e também quais dados queremos ignorar na nossa leitura (Veja em README.md o tópico "*Especificadores de Formato*").

Do segundo parâmetro em diante, iremos enviar para a função qual o endereço de memória que foi reservado para cada uma das suas variáveis. Como você já deve saber, o operador da linguagem C que acessa o endereço de memória de uma variável é o &.

```c
    int* ptrA = &a;       // ptrA recebe 0x0000
    scanf("%d", &a);      // Ambas chamadas estão recebendo um valor do terminal e armazenando
    scanf("%d", ptrA);    // no  espaço de memória reservado para a varíável a;
    
    int vetor[5];	  // Não se esqueça que vetor[i] é do tipo int, e vetor é do tipo int*  
    scanf("%d", &vetor[3]);
    scanf("%d", vetor + 3 ); // Aritmética de ponteiro, 3 = 3 * sizeof(int)
```   

Por fim, o valor retornado pela função scanf indica a quantidade de variáveis que foram lidas corretamente. Isso pode não parecer claro no momento, mas no próximo tópico irei exemplificar diversas situações.

Na prática, podemos dividir as ações que a função que a scanf realiza em duas etapas:
  
 1. Processar os dados do Buffer do stdin até preencher todas as variáveis definidas pelos especificadores.
 2. Salvar os valores lidos nos endereços recebidos do segundo parâmetro em diante.

## Buffer e processamento de I/O
O Buffer é um local que irá armazenar todos os dados recebidos por uma Stream de dados (Ex.: stdin, stdout). Portanto, todos os dados que são recebidos pelo terminal são inseridos em formato de string no Buffer. Para exemplificar, digamos que você tenha colocado os seguintes comandos no seu programa: 

```c
    int   x;
    char  c;
    int lidos = scanf("%d%c", &x, &c);
```

O que será recebido  pelo buffer caso você tenha receba as seguintes entradas a seguir:

|**$ Entrada no Terminal**|**Inserido no Buffer**|
|--|--|
|$ 12345 I|"12345 I\n"|
|$ 123K45|"123K45\n"| 
|$ 127.3 J|"127.3 J\n"|
|$ 12|"12\n"|
|$ ola mundo!|"ola mundo!\n"|

O que irá acontecer em cada caso é que o scanf irá verificar, da esquerda para a direita, quais especificadores você utilizou e, a partir do início do Buffer, ir consumindo valores que correspondam ao tipo desejado de dados. Caso o que estiver escrito no buffer não faça sentido para o tipo de dado desejado o scanf irá interromper a leitura.

|**Inserido no Buffer**|**Lido em x**|**Lido em c**|**Não processado**|
|--|--|--|--|
|"12345 I\n"|12345|' '|"I\n"|
|"123K45\n"|123|'K'|"45\n"|
|"127.3 J\n"|127|'.'|"3 J\n"|
|"12\n"|12|'\n'|""|
|"ola mundo!\n"|não muda|não muda|"ola mundo!\n"|

Perceba que, na primeira linha, o valor recebido pela variável `char c` não foi o valor `'I'`, mas sim o espaço em branco. Isso se deve ao fato de na função scanf não termos colocado nenhum espaço em branco no meio dos especificadores %d e %c. Portanto, o valor que a variável c receberá será sempre o valor imediato no buffer após o fim da leitura do inteiro (O mesmo ocorre na 4ª linha da tabela em que c recebe o '\n').

Na 5ª linha da tabela, vemos que o valor de entrada é um texto mas o valor esperado é numérico. O programa irá verificar que o primeiro char do buffer não é numérico e, portanto, não irá processar mais nenhum valor, retornando ao usuário que 0 variáveis foram lidas e não irá alterar os valores das variáveis.

Outro detalhe importante, os trechos não processados no buffer não são descartados. Portanto, caso em algum momento futuro você dê outra chamada à função scanf(), os valores lidos no terminal serão processados após o restante que sobrou das chamadas anteriores. Caso você queira limpar esses dados remanescentes, você poderá usar a função da biblioteca stdio.h `fflush(stdin)`.


## Utilizando máscaras para leituras de dados
Com esse conhecimento de como funciona o Buffer, fica bem mais simples entender como funcionam as máscaras de leitura de strings (Ex.: `scanf("%[^\n\r]);`). Você pode ver como elas atuam no tópico "Leitura de Strings" no README.md.


## Alguns cuidados adicionais
Apesar de o compilador fazer a verificação para validar se o tipo de variável recebida pelo scanf corresponde ao que foi configurado no especificador, é sim possível burlar essa funcionalidade e fazer acessos de leitura e escritas atípicas utilizando o scanf.

Relembrando, quando declaramos as variáveis no nosso programa o computador irá reservar espaço de memória suficiente para que os valores desejados sejam armazenados. Porém, como a ideia de variável é abstrata, nada nos impede de, por exemplo, salvar 1 byte de dados diretamente no endereço de memória desejada. Veja no caso a seguir:

```c
    int  x = 0;
    scanf("%c", ((char*) &x) + 1); // Converte endereço de x para char* e soma uma posição de memória.
```

No caso acima, o valor recebido pelo terminal será interpretado como um valor ASCII de 1 byte e, em seguida, esse valor será inserido na segunda posição de memória da variável x.

Ok, mas para que serve isso? Apenas para te lembrar que, por mais que a função `scanf()` faça a validação dos dados que entram no terminal, ela não valida se os endereços recebidos nos seus parâmetros são de fato acessíveis pela sua aplicação ou até mesmo se eles deveriam receber o tipo de dado que estão recebendo. Logo, uma simples conversão do tipo de ponteiro já seria suficiente para enganar tanto compilador e executar códigos atípicos.

Obs: Caso sua função tente acessar uma posição de memória que não seja acessível pelo seu programa, irá ocorrer um erro de execução e seu programa irá parar de executar.

## Considerações finais
Chegamos ao fim e eu espero que as informações que eu coloquei aqui tenham te ajudado de alguma forma a compreender com mais detalhes como funciona a leitura de dados do scanf. 

Caso alguns detalhes tenham ficados confusos, recomendo que você teste os códigos e também faça diferentes testes. Declare variáveis de diferentes tipos e veja como o scanf irá se comportar ao receber diferentes tipos de inputs via terminal. 
