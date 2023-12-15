section .text

%define VAL1 dword[ebp + 8]
%define VAL2 dword[ebp + 12]
%define VAL3 dword[ebp + 16]
%define VAL4 dword[ebp + 20]
%define OVER0 0x00000000
%define OVER1 0xFFFFFFFF

extern print_string

extern end

global string_to_int
global int_to_string
global add_int
global sub_int
global mul_int
global div_int
global exp_int
global mod_int

string_to_int:
    enter 0,0
    ; EBP + 8  = Ponteiro para String
    ; EBP + 12 = Tamanho da String

    ; Coloca tamanho da string em ESI, retirando enter final
    mov esi, VAL2
    dec esi

    ; Coloca o ponteiro da string em ECX
    mov ecx, VAL1

    ; Zera EAX e coloca a base 10 em EBX
    xor eax, eax
    mov ebx, 10
    ; Compara o primeiro caractere da string com o sinal -
    cmp byte[ecx], '-'
    ; Caso seja diferente de -, pula para o loop de transformacao
    jne int_loop
    ; Caso igual, pula o caractere
    inc ecx
    dec esi

    int_loop:
        ; Multiplica EAX por 10
        mul ebx
        movzx edx, byte[ecx]
        ; Subtrai o ASCII de 0 de EDX e soma EDX a EAX
        sub edx, 0x30
        add eax, edx
        ; Continua o loop ate esi=0
        inc ecx
        dec esi
        jnz int_loop
        ; Compara novamente se o sinal - existe, se sim, transforma o numero em seu complemento de 2
        mov ecx, VAL1
        cmp byte[ecx], '-'
        jne int_end
        neg eax
    int_end:
        leave
        ret

int_to_string:
    enter 0,0
    ; EBP + 8  = Valor Inteiro
    ; EBP + 12 = Ponteiro onde a string vai ser salva
    ; Empilha o valor que representa o final da string
    push 0

    ; Coloca o numero em eax
    mov eax, VAL1
    mov ecx, 10
    ; Compara se o numero eh positivo ou negativo
    cmp eax, 0
    jge _loop_int

    ; Obtem a representacao em complemento de 2 caso negativo
    neg eax

    _loop_int:
        ; Extende o sinal de eax e o divide por 10
        cdq
        idiv ecx
        ; Converte o resto da divisao para ascii e adiciona o valor a pilha
        add edx, 0x30
        push edx
        ; Verifica que o quociente = 0
        cmp eax, 0
        jne _loop_int

        cmp VAL1, 0
        jge _pointer

        ; Adiciona o sinal - a pilha
        push '-'

    _pointer:
        ; Coloca o ponteiro da string em ebx
        mov ebx, VAL2
    _string:
        ; Desempilha caracter a caracter e coloca na string
        pop eax
        mov byte [ebx], al
        inc ebx
        ; Ao chegar no final da string sai do loop
        cmp eax, 0
        jne _string

    leave
    ret

add_int:
    ; EBP + 8   = Primeiro valor a ser somado
    ; EBP + 12  = Segundo valor a ser somado
    ; Resultado eh retornado em EAX
    enter 0,0
    mov eax, VAL1
    add eax, VAL2
    leave
    ret

sub_int:
    ; EBP + 8   = Primeiro valor a ser subtraido
    ; EBP + 12  = Segundo valor a ser subtraido
    ; Resultado eh retornado em EAX
    enter 0,0
    mov eax, VAL2
    sub eax, VAL1
    leave
    ret

mul_int:
    ; EBP + 8   = Primeira parcela
    ; EBP + 12  = Segunda parcela
    ; EBP + 20 = Tamanho da msg de overflow
    ; EBP + 16 = Ponteiro mensagem de overflow
    ; Produto eh retornado em EAX
    enter 0,0
    mov eax, VAL1
    imul VAL2

    cmp edx, OVER0
    je _not_overflow

    cmp edx, OVER1
    je _not_overflow

    push VAL4
    push VAL3
    call print_string

    call end

_not_overflow:
    leave
    ret

exp_int:
    ; EBP + 8   = Primeira parcela
    ; EBP + 12  = Segunda parcela
    ; Produto eh retornado em EAX
    enter 0,0
    mov eax, VAL2
    mov ebx, VAL1

    _loop:
        imul VAL2
        sub ebx, 1

        cmp edx, OVER0
        je _not_oflow

        cmp edx, OVER1
        je _not_oflow

        push VAL4
        push VAL3
        call print_string

        call end

    _not_oflow:
        cmp ebx, 1
        jne _loop
        leave
        ret

div_int:
    enter 0,0
    mov eax, VAL2
    cdq
    idiv VAL1
    leave
    ret

mod_int:
    enter 0,0
    mov eax, VAL2
    cdq
    idiv VAL1
    mov eax, edx
    leave
    ret
