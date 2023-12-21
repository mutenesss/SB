## Calculadora IA-32 - Software Básico

### Alunos:

Nome: Erick Rodrigues Fraga

Matricula: 190086815




Nome: Arthur Barreiros de Oliveira Mota

Matriculas: 190102829


### Sistemas Testados:
```plaintext
Linux:
Manjaro - 2 versões
Ubuntu 22.01
```

### Descrição dos Arquivos:

#### \- calc_16

_Como Compilar_

```plaintext
Executar o arquivo compile_16.sh
```

ou ir para a pasta NASM_16 e executar os comandos

```plaintext
./nasm -f elf -o io.o io.asm && ./nasm -f elf -o main.o main.asm && ./nasm -f elf -o op.o op.asm &&  ld -m elf_i386 -o calc_16 main.o io.o op.o

```

#### \- calc_32

_Como Compilar_

```plaintext
Executar o arquivo compile_16.sh
```

ou ir para a pasta NASM_16 e executar os comandos

```plaintext
./nasm -f elf -o io.o io.asm && ./nasm -f elf -o main.o main.asm && ./nasm -f elf -o op.o op.asm &&  ld -m elf_i386 -o calc_32 main.o io.o op.o
```


_Como Utilizar_

```plaintext
./calc_16 ou ./calc_32
```

Calculadora NASM 
*   Executa as operações de
	* Soma
	* Subtração
	* Multiplicação
	* Divisão
	* Exponenciação
	* Mod
*   Todas as operações são feitas utilizando **_precisão_** de 16 ou 32 bits (dependendo de qual a calculadora executada).
* Overflow é sinalizado apenas nas operações de Multiplicação e Divisão.
* Em 16 bits, se um valor ultrapassar o máximo ou o mínimo da precisão, o programa é interrompido.
* Executa apenas uma operação e finaliza o programa.
* São permitidos nomes de até 20 caracteres.
* Operações de entrada e saída de dados estão definidas no arquivo io.asm
* Outras operações estão definidas no arquivo op.asm
* O arquivo main.asm faz a chamada as operações definidas nos outros arquivos, controlando o escopo de pilha.
* Multiplos comentários no programa podem estar errados, devido a mudanças efetuadas em código mas não alteradas nos comentários.