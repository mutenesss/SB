#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    int i; 
    double vlr;
    for (i = 1; i < argc; i++){
        switch (argv[i][0])
        {
        case '\0':
            printf("Linha de argumento vazia");
            exit(0);
            break;
        /*Operandos*/
        case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
            vlr = atoi(argv[i]);
            break;
        /*Operadores*/
        case '+':
            break;
        case '-':
            break;
        case '*':
            break;
        case '/':
            break;

        /*Erro*/
        default:
            printf("Operador %s desconhecido\n", argv[i]);
            exit(0);
        }
    }
}