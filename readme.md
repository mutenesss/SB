## Montador e Simulador - Software Básico

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

#### \- montador.cpp

_Como Compilar_

```plaintext
g++ -Wall -o montador montador.cpp
```

Padrão C++ utilizado

```plaintext
C++20
```

Bibliotecas Necessárias

```plaintext
Bibliotecas padrão C++ e Bibliotecas Boost 
```

_Como Utilizar_
```plaintext
./montador arquivo.asm
```
Ambos os arquivos precisam estar na mesma pasta

Montador do assembly inventado

*   Não possui macro.
*   Arquivos de entrada .asm **não precisam** terminar com enter.
*	Apenas 1 arquivo .asm pode ser passado por vez.
*   Não é permitido o uso de SPACE ou CONST sem label.
*   Não é necessária a existência de secao data separada.
*   Ocorre error caso não tenha secao text.
*   Tab e Espaço são tratados.
*   Todo o program é convertido para minusculo.
*   auto ferreira e auto jorge representam o fim da minha sanidade

**\- simulador.cpp**

_Como Compilar_

```plaintext
g++ -Wall -o simulador simulador.cpp
```

Padrão C++ utilizado

```plaintext
C++20
```

Bibliotecas Necessárias

```plaintext
Bibliotecas padrão C++
```

_Como Utilizar_
```plaintext
./simulador arquivo.obj
```
Ambos os arquivos precisam estar na mesma pasta

Simulador do assembly inventado

*	Tem como entrada os arquivos .obj obtidos do montador.
*   Simulação iterativa do programa.
*   Em casos de invasão da área de memória, o programa encerra automaticamente.
*   Apenas 1 arquivo .obj pode ser passado por vez.
