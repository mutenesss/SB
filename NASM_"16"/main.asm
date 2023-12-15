section .bss
    nome        resb 20         ; Espaco para inserir o nome
    tam_nome    resb 5          ; Tamanho do nome

    arg1        resb 12         ; Maior inteiro 32 bits possivel + sinal + enter
    arg2        resb 12         ; Maior inteiro 32 bits possivel + sinal + enter
    arg3        resb 12         ; Ponteiro para string final
    num1        resd 1          ; Arg1 convertido para inteiro
    num2        resd 1          ; Arg2 convertido para inteiro
    resp        resd 1          ; Resposta pos processamento

    option      resb 1          ; Opcao da calculadora

section .data
    msg1 db 'Bem-vindo. Digite seu nome:', 0dh, 0ah
    msg1_size EQU $-msg1

    msg2 db 'Hola, '
    msg2_size EQU $-msg2

    msg3 db ', bem-vindo ao programa de CALC IA-32', 0dh, 0ah
    msg3_size EQU $-msg3

    opcao db 'ESCOLHA UMA OPCAO:', 0dh, 0ah
    opcao_size EQU $-opcao

    op1 db '- 1: SOMA', 0dh, 0ah
    op1_size EQU $-op1

    op2 db '- 2: SUBTRACAO', 0dh, 0ah
    op2_size EQU $-op2

    op3 db '- 3: MULTIPLICACAO', 0dh, 0ah
    op3_size EQU $-op3

    op4 db '- 4: DIVISAO', 0dh, 0ah
    op4_size EQU $-op4

    op5 db '- 5: EXPONENCIACAO', 0dh, 0ah
    op5_size EQU $-op5

    op6 db '- 6: MOD', 0dh, 0ah
    op6_size EQU $-op6

    op7 db '- 7: SAIR', 0dh, 0ah
    op7_size EQU $-op7

    val1 db 'Por favor, insira o primeiro numero:', 0dh, 0ah
    val1_size EQU $-val1

    val2 db 'Por favor, insira o segundo numero:', 0dh, 0ah
    val2_size EQU $-val2

    ovf db 'Ocorreu Overflow', 0dh, 0ah
    ovf_size EQU $-ovf


section .text
global _start
    %define Limpa2 add esp, 8
    %define Limpa3 add esp, 12

    extern get_string
    extern print_string
    extern end

    extern string_to_int
    extern int_to_string
    extern add_int
    extern sub_int
    extern mul_int
    extern div_int
    extern exp_int
    extern mod_int
    extern compair

_start:
    ; Print da mensagem de abertura do programa
    push msg1_size
    push msg1
    call print_string
    Limpa2 ; Limpa a pilha dos dois enderecos inseridos

    ; Pega o nome da pessoa
    push 20
    push nome
    call get_string
    Limpa2

    ; Salva o tamanho do nome da pessoa
    mov dword [tam_nome], eax
    mov dword [nome + eax - 1], 0x0

    ; Escrita da mensagem de bem vindo
    push msg2_size
    push msg2
    call print_string
    Limpa2

    push tam_nome
    push nome
    call print_string
    Limpa2

    push msg3_size
    push msg3
    call print_string
    Limpa2

    ; Chama o menu
        ; SOMA
menu:   push op1_size
        push op1
        call print_string
        Limpa2
            ; SUBTRACAO
        push op2_size
        push op2
        call print_string
        Limpa2
            ; MULTIPLICACAO
        push op3_size
        push op3
        call print_string
        Limpa2
            ; DIVISAO
        push op4_size
        push op4
        call print_string
        Limpa2
            ; EXPONENCIACAO
        push op5_size
        push op5
        call print_string
        Limpa2
            ; MOD
        push op6_size
        push op6
        call print_string
        Limpa2
            ; SAIR
        push op7_size
        push op7
        call print_string
        Limpa2

        ; Leitura da opcao do menu
        push 2
        push option
        call get_string
        Limpa2

        cmp byte [option], 0x31
        je _soma

        cmp byte [option], 0x32
        je _subtracao

        cmp byte [option], 0x33
        je _multiplicacao

        cmp byte [option], 0x34
        je _divisao

        cmp byte [option], 0x35
        je _exponenciacao

        cmp byte [option], 0x36
        je _mod

        call end

_soma:
    ; Entrada do primeiro valor
    push val1_size
    push val1
    call print_string
    Limpa2

    push 11     ; Tamanho maximo de uma string de 32 bits + sinal
    push arg1   ; Ponteiro para salvar a string
    call get_string
    Limpa2

    ; Conversao do arg1 para int
    push eax    ; Tamanho da string lida
    push arg1   ; Ponteiro para string
    call string_to_int
    mov dword [num1], eax
    Limpa2
    push dword[num1]
    call compair

    ; Entrada do segundo valor
    push val2_size
    push val2
    call print_string
    Limpa2

    push 11     ; Tamanho maximo de uma string de 32 bits + sinal
    push arg2   ; Ponteiro para salvar a string
    call get_string
    Limpa2

    ; Conversao do arg2 para int
    push eax    ; Tamanho da string lida
    push arg2   ; Ponteiro para string
    call string_to_int
    mov dword [num2], eax
    Limpa2
    push dword[num2]
    call compair

    ; Executa a operacao
    push dword [num1]
    push dword [num2]
    call add_int
    ; Coloca o valor da operacao na memoria
    mov dword[resp], eax
    Limpa2
    push dword[resp]
    call compair

    ; Converte o resultado da operacao para string

    push arg3
    push dword [resp]
    call int_to_string
    Limpa3

    ; Print do resultado
    push 12
    push arg3
    call print_string
    Limpa2

    call end

_subtracao:
    ; Entrada do primeiro valor
    push val1_size
    push val1
    call print_string
    Limpa2

    push 11     ; Tamanho maximo de uma string de 32 bits + sinal
    push arg1   ; Ponteiro para salvar a string
    call get_string
    Limpa2

    ; Conversao do arg1 para int
    push eax    ; Tamanho da string lida
    push arg1   ; Ponteiro para string
    call string_to_int
    mov dword [num1], eax
    Limpa2
    push dword[num1]
    call compair

    ; Entrada do segundo valor
    push val2_size
    push val2
    call print_string
    Limpa2

    push 11     ; Tamanho maximo de uma string de 32 bits + sinal
    push arg2   ; Ponteiro para salvar a string
    call get_string
    Limpa2

    ; Conversao do arg2 para int
    push eax    ; Tamanho da string lida
    push arg2   ; Ponteiro para string
    call string_to_int
    mov dword [num2], eax
    Limpa2
    push dword[num2]
    call compair

    ; Executa a operacao
    push dword [num1]
    push dword [num2]
    call sub_int
    ; Coloca o valor da operacao na memoria
    mov dword[resp], eax
    Limpa2
    push dword[resp]
    call compair

    ; Converte o resultado da operacao para string

    push arg3
    push dword [resp]
    call int_to_string
    Limpa3

    ; Print do resultado
    push 12
    push arg3
    call print_string
    Limpa2

    call end


_multiplicacao:
    push ovf_size
    push ovf
    ; Entrada do primeiro valor
    push val1_size
    push val1
    call print_string
    Limpa2

    push 11     ; Tamanho maximo de uma string de 32 bits + sinal
    push arg1   ; Ponteiro para salvar a string
    call get_string
    Limpa2

    ; Conversao do arg1 para int
    push eax    ; Tamanho da string lida
    push arg1   ; Ponteiro para string
    call string_to_int
    mov dword [num1], eax
    Limpa2
    push dword[num1]
    call compair

    ; Entrada do segundo valor
    push val2_size
    push val2
    call print_string
    Limpa2

    push 11     ; Tamanho maximo de uma string de 32 bits + sinal
    push arg2   ; Ponteiro para salvar a string
    call get_string
    Limpa2

    ; Conversao do arg2 para int
    push eax    ; Tamanho da string lida
    push arg2   ; Ponteiro para string
    call string_to_int
    mov dword [num2], eax
    Limpa2
    push dword[num2]
    call compair

    ; Executa a operacao
    push dword [num1]
    push dword [num2]
    call mul_int
    ; Coloca o valor da operacao na memoria
    mov dword[resp], eax
    Limpa2
    push dword[resp]
    call compair

    ; Converte o resultado da operacao para string

    push arg3
    push dword [resp]
    call int_to_string
    Limpa3

    ; Print do resultado
    push 12
    push arg3
    call print_string
    Limpa2

    call end


_divisao:
; Entrada do primeiro valor
    push val1_size
    push val1
    call print_string
    Limpa2

    push 11     ; Tamanho maximo de uma string de 32 bits + sinal
    push arg1   ; Ponteiro para salvar a string
    call get_string
    Limpa2

    ; Conversao do arg1 para int
    push eax    ; Tamanho da string lida
    push arg1   ; Ponteiro para string
    call string_to_int
    mov dword [num1], eax
    Limpa2
    push dword[num1]
    call compair

    ; Entrada do segundo valor
    push val2_size
    push val2
    call print_string
    Limpa2

    push 11     ; Tamanho maximo de uma string de 32 bits + sinal
    push arg2   ; Ponteiro para salvar a string
    call get_string
    Limpa2

    ; Conversao do arg2 para int
    push eax    ; Tamanho da string lida
    push arg2   ; Ponteiro para string
    call string_to_int
    mov dword [num2], eax
    Limpa2
    push dword[num2]
    call compair

    ; Executa a operacao
    push dword [num1]
    push dword [num2]
    call div_int
    ; Coloca o valor da operacao na memoria
    mov dword[resp], eax
    Limpa2
    push dword[resp]
    call compair

    ; Converte o resultado da operacao para string

    push arg3
    push dword [resp]
    call int_to_string
    Limpa3

    ; Print do resultado
    push 12
    push arg3
    call print_string
    Limpa2

    call end


_exponenciacao:
    push ovf_size
    push ovf
   ; Entrada do primeiro valor
    push val1_size
    push val1
    call print_string
    Limpa2

    push 11     ; Tamanho maximo de uma string de 32 bits + sinal
    push arg1   ; Ponteiro para salvar a string
    call get_string
    Limpa2

    ; Conversao do arg1 para int
    push eax    ; Tamanho da string lida
    push arg1   ; Ponteiro para string
    call string_to_int
    mov dword [num1], eax
    Limpa2
    push dword[num1]
    call compair

    ; Entrada do segundo valor
    push val2_size
    push val2
    call print_string
    Limpa2

    push 11     ; Tamanho maximo de uma string de 32 bits + sinal
    push arg2   ; Ponteiro para salvar a string
    call get_string
    Limpa2

    ; Conversao do arg2 para int
    push eax    ; Tamanho da string lida
    push arg2   ; Ponteiro para string
    call string_to_int
    mov dword [num2], eax
    Limpa2
    push dword[num2]
    call compair

    ; Executa a operacao
    push dword [num1]
    push dword [num2]
    call exp_int
    ; Coloca o valor da operacao na memoria
    mov dword[resp], eax
    Limpa2
    push dword[resp]
    call compair

    ; Converte o resultado da operacao para string

    push arg3
    push dword [resp]
    call int_to_string
    Limpa3

    ; Print do resultado
    push 12
    push arg3
    call print_string
    Limpa2

    call end


_mod:
    ; Entrada do primeiro valor
    push val1_size
    push val1
    call print_string
    Limpa2

    push 11     ; Tamanho maximo de uma string de 32 bits + sinal
    push arg1   ; Ponteiro para salvar a string
    call get_string
    Limpa2

    ; Conversao do arg1 para int
    push eax    ; Tamanho da string lida
    push arg1   ; Ponteiro para string
    call string_to_int
    mov dword [num1], eax
    Limpa2
    push dword[num1]
    call compair

    ; Entrada do segundo valor
    push val2_size
    push val2
    call print_string
    Limpa2

    push 11     ; Tamanho maximo de uma string de 32 bits + sinal
    push arg2   ; Ponteiro para salvar a string
    call get_string
    Limpa2

    ; Conversao do arg2 para int
    push eax    ; Tamanho da string lida
    push arg2   ; Ponteiro para string
    call string_to_int
    mov dword [num2], eax
    Limpa2
    push dword[num2]
    call compair

    ; Executa a operacao
    push dword [num1]
    push dword [num2]
    call mod_int
    ; Coloca o valor da operacao na memoria
    mov dword[resp], eax
    Limpa2
    push dword[resp]
    call compair

    ; Converte o resultado da operacao para string

    push arg3
    push dword [resp]
    call int_to_string
    Limpa3

    ; Print do resultado
    push 12
    push arg3
    call print_string
    Limpa2

    call end

